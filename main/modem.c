
#include "modem.h"
#include "esp_log.h"
/**==========================================================================
 *Setup the modem and obtain a PDP Context and IP Address
 *
 * @inputs:
 * @outputs:
 *
 * @description: ripped from FreeRTOS Cellular Demo
 *
 * @called_by: main
 * ==========================================================================**/
int setupCellular(void)
{
    uint8_t CellularSocketPdnContextId = CELLULAR_PDN_CONTEXT_ID;
    int cellularRet = 1;
    CellularError_t cellularStatus = CELLULAR_SUCCESS;
    CellularSimCardStatus_t simStatus = {0};
    CellularServiceStatus_t serviceStatus = {0};
    CellularCommInterface_t *pCommIntf = &CellularCommInterface;
    uint8_t tries = 0;
    CellularPdnConfig_t pdnConfig = {CELLULAR_PDN_CONTEXT_IPV4, CELLULAR_PDN_AUTH_NONE, CELLULAR_APN, "", ""};
    CellularPdnStatus_t PdnStatusBuffers = {0};
    char localIP[CELLULAR_IP_ADDRESS_MAX_SIZE] = {'\0'};
    uint32_t timeoutCountLimit = (CELLULAR_PDN_CONNECT_TIMEOUT / CELLULAR_PDN_CONNECT_WAIT_INTERVAL_MS) + 1U;
    uint32_t timeoutCount = 0;
    uint8_t NumStatus = 1;
    CellularPsmSettings_t psmSettings = {0};

    /* Initialize Cellular Comm Interface. */
    cellularStatus = Cellular_Init(&CellularHandle, pCommIntf);

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        /* wait until SIM is ready */
        for (tries = 0; tries < CELLULAR_MAX_SIM_RETRY; tries++) // 5 tries
        {
            cellularStatus = Cellular_GetSimCardStatus(CellularHandle, &simStatus);

            if ((cellularStatus == CELLULAR_SUCCESS) &&
                ((simStatus.simCardState == CELLULAR_SIM_CARD_INSERTED) &&
                 (simStatus.simCardLockState == CELLULAR_SIM_CARD_READY)))
            {
                /* Turn of PSM because this is demo to showcase MQTT instead of PSM mode. */
                psmSettings.mode = 0;
                // cellularStatus = Cellular_SetPsmSettings(CellularHandle, &psmSettings);

                if (cellularStatus != CELLULAR_SUCCESS)
                {
                    configPRINTF((">>>  Cellular_SetPsmSettings failure  <<<\r\n"));
                }
                else
                {
                    configPRINTF((">>>  Cellular SIM okay  <<<\r\n"));
                }

                break;
            }
            else
            {
                configPRINTF((">>>  Cellular SIM card state %d, Lock State %d <<<\r\n",
                              simStatus.simCardState,
                              simStatus.simCardLockState));
            }

            vTaskDelay(pdMS_TO_TICKS(CELLULAR_SIM_CARD_WAIT_INTERVAL_MS));
        }
    }

    /* Setup the PDN config. */
    if (cellularStatus == CELLULAR_SUCCESS)
    {
        cellularStatus = Cellular_SetPdnConfig(CellularHandle, CellularSocketPdnContextId, &pdnConfig);
    }
    else
    {
        configPRINTF((">>>  Cellular SIM failure  <<<\r\n"));
    }

    /* Rescan network. */
    if (cellularStatus == CELLULAR_SUCCESS)
    {
        cellularStatus = Cellular_RfOff(CellularHandle);
    }

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        cellularStatus = Cellular_RfOn(CellularHandle);
    }

    /* Get service status. */
    if (cellularStatus == CELLULAR_SUCCESS)
    {
        while (timeoutCount < timeoutCountLimit)
        {
            ESP_LOGW("SETUP_CELL", "%ul, %ul", timeoutCount, timeoutCountLimit);
            cellularStatus = Cellular_GetServiceStatus(CellularHandle, &serviceStatus);

            if ((cellularStatus == CELLULAR_SUCCESS) &&
                ((serviceStatus.psRegistrationStatus == REGISTRATION_STATUS_REGISTERED_HOME) ||
                 (serviceStatus.psRegistrationStatus == REGISTRATION_STATUS_ROAMING_REGISTERED)))
            {
                configPRINTF((">>>  Cellular module registered  <<<\r\n"));
                break;
            }
            else
            {
                configPRINTF((">>>  Cellular GetServiceStatus failed %d, ps registration status %d  <<<\r\n",
                              cellularStatus, serviceStatus.psRegistrationStatus));
            }

            timeoutCount++;

            if (timeoutCount >= timeoutCountLimit)
            {
                cellularStatus = CELLULAR_INVALID_HANDLE;
                configPRINTF((">>>  Cellular module can't be registered  <<<\r\n"));
            }

            vTaskDelay(pdMS_TO_TICKS(CELLULAR_PDN_CONNECT_WAIT_INTERVAL_MS));
        }
    }

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        cellularStatus = Cellular_ActivatePdn(CellularHandle, CellularSocketPdnContextId);
    }

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        cellularStatus = Cellular_GetIPAddress(CellularHandle, CellularSocketPdnContextId, localIP, sizeof(localIP));
    }

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        cellularStatus = Cellular_GetPdnStatus(CellularHandle, &PdnStatusBuffers, CellularSocketPdnContextId, &NumStatus);
    }

    if ((cellularStatus == CELLULAR_SUCCESS) && (PdnStatusBuffers.state == 1))
    {
        configPRINTF((">>>  Cellular module registered, IP address %s  <<<\r\n", localIP));
        ESP_LOGI("SETUP_CELL", ">>>  Cellular module registered, IP address %s  <<<\r\n", localIP);
        cellularRet = 1;
    }
    else
    {
        cellularRet = 0;
    }

    return cellularRet;
}

/*-----------------------------------------------------------*/

int mbedtls_platform_send(void *ctx,
                          const unsigned char *buf,
                          size_t len)
{
    Socket_t socket;

    configASSERT(ctx != NULL);
    configASSERT(buf != NULL);

    socket = (Socket_t)ctx;

    return Sockets_Send(socket, buf, len);
}

/*-----------------------------------------------------------*/

int mbedtls_platform_recv(void *ctx,
                          unsigned char *buf,
                          size_t len)
{
    Socket_t socket;

    configASSERT(ctx != NULL);
    configASSERT(buf != NULL);

    socket = (Socket_t)ctx;

    return (int)Sockets_Recv(socket, buf, len);
}
/*-----------------------------------------------------------*/
