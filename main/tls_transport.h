#ifndef _TLS_TRANSPORT_H
#define _TLS_TRANSPORT_H
// #include "core_mqtt.h"
// #include "mqtt_demo.h"
// #include "esp_tls.h"
#include "sockets_wrapper.h"
#include "mbedtls/ssl.h"
//
typedef struct NetworkContext
{
    mbedtls_ssl_context pTlsContext;
    // This should also have the socket in here
    Socket_t tcpSocket;
} NetworkContext_t;
int32_t EspTls_Send(NetworkContext_t *pNetworkContext, const void *pBuffer, size_t bytesToSend);

int32_t EspTls_Recv(NetworkContext_t *pNetworkContext, void *pBuffer, size_t bytesToRecv);
#endif