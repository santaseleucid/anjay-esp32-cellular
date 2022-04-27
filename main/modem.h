#ifndef _MODEM_H
#define _MODEM_H
#include "main.h"
#include "cellular_config_defaults.h"
#include "cellular_types.h"
#include "cellular_api.h"
#include "cellular_comm_interface.h"
#include "cellular_platform.h"
#include "cellular_common.h"
#include "cellular_bg96.h"
#include "sockets_wrapper.h"

#define CELLULAR_SIM_CARD_WAIT_INTERVAL_MS (500UL)
#define CELLULAR_MAX_SIM_RETRY (5U)
#define CELLULAR_PDN_CONNECT_WAIT_INTERVAL_MS (1000UL)
#define CELLULAR_PDN_CONTEXT_ID_MIN (1U)
#define CELLULAR_PDN_CONTEXT_ID CELLULAR_PDN_CONTEXT_ID_MIN
#define CELLULAR_PDN_CONNECT_TIMEOUT (10000UL)

// config - edit me

#define mqttexampleTRANSPORT_SEND_RECV_TIMEOUT_MS (20000U)
#define CELLULAR_SIM_CARD_WAIT_INTERVAL_MS (500UL)
#define CELLULAR_MAX_SIM_RETRY (5U)
#define CELLULAR_PDN_CONNECT_WAIT_INTERVAL_MS (1000UL)

extern CellularCommInterface_t CellularCommInterface;
extern CellularHandle_t CellularHandle;    // = NULL;
extern uint8_t CellularSocketPdnContextId; // = CELLULAR_PDN_CONTEXT_ID;
// extern Socket_t tcpSocket;                 // = {0};
// extern Socket_t tcpSocket_bs;              // = {0};
// extern Socket_t tcpSocket_http;            // = {0};
int setupCellular(void);
int mbedtls_platform_send(void *ctx,
                          const unsigned char *buf,
                          size_t len);
int mbedtls_platform_recv(void *ctx,
                          unsigned char *buf,
                          size_t len);

#endif