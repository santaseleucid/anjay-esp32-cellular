#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "cellular_comm_interface.h"
#include "driver/uart.h"
#include "esp_intr_alloc.h"
#include "driver/gpio.h"
#include "ESP_LOG.h"
#define TAG "COMM_INTERFACE"
#define BUF_SIZE 512

/**
 * @brief Comm events.
 */
#define COMM_EVT_MASK_TX_DONE (0x0001U)
#define COMM_EVT_MASK_TX_ERROR (0x0002U)
#define COMM_EVT_MASK_TX_ABORTED (0x0004U)
#define COMM_EVT_MASK_RX_DONE (0x0008U)
#define COMM_EVT_MASK_RX_ERROR (0x0010U)
#define COMM_EVT_MASK_RX_ABORTED (0x0020U)
#define UART_RXFIFO_FULL_INT_CLR (BIT(0))
#define UART_RXFIFO_FULL_INT_CLR_M (BIT(0))
#define UART_RXFIFO_FULL_INT_CLR_V 0x1
#define UART_RXFIFO_FULL_INT_CLR_S 0
#define UART_RXFIFO_TOUT_INT_CLR (BIT(8))
#define UART_RXFIFO_TOUT_INT_CLR_M (BIT(8))
#define UART_RXFIFO_TOUT_INT_CLR_V 0x1
#define UART_RXFIFO_TOUT_INT_CLR_S 8
/*-----------------------------------------------------------*/
static intr_handle_t handle_console;
/**
 * @brief A context of the communication interface.
 */
typedef struct CellularCommInterfaceContextStruct
{
    EventGroupHandle_t pEventGroup;                 /**< Event group for TX or RX callback event to wakeup receiver's thread. */
    uint8_t uartRxChar[1];                          /**< 1 byte receive buffer. */
    CellularCommInterfaceReceiveCallback_t pRecvCB; /**< CellularCommInterfaceReceiveCallback_t callback function set in open function. */
    // IotUARTHandle_t uartHandle;                     /**< Common IO uart handler. */
    void *pUserData;      /**< pUserData in CellularCommInterfaceReceiveCallback_t callback function. */
    uint8_t uartBusyFlag; /**< Flag for whether the physical interface is busy or not. */

    // IotFifo_t rxFifo;             /**< Internal FIFO for recevied data from UART. */
    uint8_t fifoBuffer[BUF_SIZE]; /**< FIFO buffer for internal FIFO. */
    uint8_t rxFifoReadingFlag;    /**< Indicate the reader is reading the FIFO in recv function. */
    bool ifOpen;                  /**< Communicate interface open status. */
    QueueHandle_t uart_queue;
    // intr_handle_t uart_intr_handle;
} CellularCommInterfaceContext;

/*-----------------------------------------------------------*/
static CellularCommInterfaceError_t prvCellularOpen(CellularCommInterfaceReceiveCallback_t receiveCallback,
                                                    void *pUserData,
                                                    CellularCommInterfaceHandle_t *pIotCommIntfCtx);
static CellularCommInterfaceError_t prvCellularClose(CellularCommInterfaceHandle_t commInterfaceHandle);
static CellularCommInterfaceError_t prvCellularReceive(CellularCommInterfaceHandle_t commInterfaceHandle,
                                                       uint8_t *pBuffer,
                                                       uint32_t bufferLength,
                                                       uint32_t timeoutMilliseconds,
                                                       uint32_t *pDataReceivedLength);
static CellularCommInterfaceError_t prvCellularSend(CellularCommInterfaceHandle_t commInterfaceHandle,
                                                    const uint8_t *pData,
                                                    uint32_t dataLength,
                                                    uint32_t timeoutMilliseconds,
                                                    uint32_t *pDataSentLength);
/*-----------------------------------------------------------*/
CellularCommInterface_t CellularCommInterface =
    {
        .open = prvCellularOpen,
        .send = prvCellularSend,
        .recv = prvCellularReceive,
        .close = prvCellularClose};
/*-----------------------------------------------------------*/
static CellularCommInterfaceContext _iotCommIntfCtx = {0};
/*-----------------------------------------------------------*/
static CellularCommInterfaceContext *_getCellularCommContext(void)
{
    return &_iotCommIntfCtx;
}
/*-----------------------------------------------------------*/

static void uart_event_task(void *pvParameters)
{
    uart_event_t event;
    size_t buffered_size;
    uint8_t *dtmp = (uint8_t *)malloc(1024 * 10);
    CellularCommInterfaceError_t retComm = IOT_COMM_INTERFACE_SUCCESS;
    CellularCommInterfaceContext *pCellularCommContext = _getCellularCommContext();
    for (;;)
    {
        if (xQueueReceive(pCellularCommContext->uart_queue, (void *)&event, (portTickType)portMAX_DELAY))
        {
            switch (event.type)
            {
            case UART_DATA:
                // //ESP_LOGI(TAG, "[UART DATA]: %d", event.size);
                retComm = pCellularCommContext->pRecvCB(pCellularCommContext->pUserData,
                                                        (CellularCommInterfaceHandle_t)pCellularCommContext);
                break;
            case UART_BREAK:
                // ESP_LOGI(TAG, "[UART BREAK]: %d", event.size);
                break;
            default:
                // ESP_LOGI(TAG, "uart event type: %d", event.type);
                break;
            }
        }
    }
}

/*-----------------------------------------------------------*/
static CellularCommInterfaceError_t prvCellularOpen(CellularCommInterfaceReceiveCallback_t receiveCallback,
                                                    void *pUserData,
                                                    CellularCommInterfaceHandle_t *pCommInterfaceHandle)
{
    QueueHandle_t uart_queue;
    const uart_port_t uart_num = UART_NUM_2;
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, 23, 22, 4, 2));
    const int uart_buffer_size = (1024 * 20);
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, uart_buffer_size,
                                        uart_buffer_size, 20, &uart_queue, 0));

    _iotCommIntfCtx.pEventGroup = xEventGroupCreate();
    _iotCommIntfCtx.uart_queue = uart_queue;
    /* Set the callback function. */
    _iotCommIntfCtx.pRecvCB = receiveCallback;
    _iotCommIntfCtx.pUserData = pUserData;
    xTaskCreate(uart_event_task, "uart_event_task", 2048, NULL, 12, NULL);

    *pCommInterfaceHandle = (CellularCommInterfaceHandle_t)&_iotCommIntfCtx;
    return IOT_COMM_INTERFACE_SUCCESS;
}
static CellularCommInterfaceError_t prvCellularClose(CellularCommInterfaceHandle_t commInterfaceHandle)
{
    return IOT_COMM_INTERFACE_SUCCESS;
}
static CellularCommInterfaceError_t prvCellularReceive(CellularCommInterfaceHandle_t commInterfaceHandle,
                                                       uint8_t *pBuffer,
                                                       uint32_t bufferLength,
                                                       uint32_t timeoutMilliseconds,
                                                       uint32_t *pDataReceivedLength)
{
    // //ESP_LOGI(TAG, "buffer length: %d", bufferLength);
    int length;
    int len;
    uint8_t data[1024];
    uart_get_buffered_data_len(2, (size_t *)pDataReceivedLength);
    // //ESP_LOGI(TAG, "rcv'd data length: %d", *pDataReceivedLength);
    len = uart_read_bytes(2, pBuffer, *pDataReceivedLength, portMAX_DELAY);
    // printf("In cellular receive\n");
    // for (int i = 0; i < *pDataReceivedLength; i++)
    // {
    //     printf("%02x ", pBuffer[i]);
    // }
    // printf("\n");

    // ESP_LOGI("UART RCV", "%.*s", *pDataReceivedLength, pBuffer);
    return IOT_COMM_INTERFACE_SUCCESS;
}
static CellularCommInterfaceError_t prvCellularSend(CellularCommInterfaceHandle_t commInterfaceHandle,
                                                    const uint8_t *pData,
                                                    uint32_t dataLength,
                                                    uint32_t timeoutMilliseconds,
                                                    uint32_t *pDataSentLength)
{
    int length;
    int len;
    CellularCommInterfaceError_t ret = IOT_COMM_INTERFACE_BUSY;
    CellularCommInterfaceContext *pIotCommIntfCtx = (CellularCommInterfaceContext *)commInterfaceHandle;
    uint8_t *const pLocalData = (uint8_t *const)pData;
    // printf("In cellular sending \n");
    // for (int i = 0; i < dataLength; i++)
    // {
    //     printf("%02x ", pLocalData[i]);
    // }
    // printf("\n");
    // ESP_LOGI("UART SEND", "%s", pLocalData);
    *pDataSentLength = (uint32_t *)uart_write_bytes(2, (const void *)pLocalData, dataLength);
    uart_wait_tx_done(2, portMAX_DELAY);
    return IOT_COMM_INTERFACE_SUCCESS;
}
