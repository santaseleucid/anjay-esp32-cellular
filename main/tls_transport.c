
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "tls_transport.h"
#include "mbedtls/ssl.h"
#define mbedtls
#ifdef mbedtls
int32_t
EspTls_Send(NetworkContext_t *pNetworkContext, const void *pBuffer, size_t bytesToSend)
{
    ssize_t tlsStatus;
    tlsStatus = mbedtls_ssl_write(&pNetworkContext->pTlsContext, pBuffer, bytesToSend);
    if (tlsStatus == MBEDTLS_ERR_SSL_TIMEOUT || tlsStatus == MBEDTLS_ERR_SSL_WANT_READ || tlsStatus == MBEDTLS_ERR_SSL_WANT_WRITE)
    {
        tlsStatus = 0;
    }
    return tlsStatus;
}

int32_t EspTls_Recv(NetworkContext_t *pNetworkContext, void *pBuffer, size_t bytesToRecv)
{
    ssize_t tlsStatus;
    tlsStatus = mbedtls_ssl_read(&pNetworkContext->pTlsContext, pBuffer, bytesToRecv);
    if (tlsStatus == MBEDTLS_ERR_SSL_TIMEOUT || tlsStatus == MBEDTLS_ERR_SSL_WANT_READ || tlsStatus == MBEDTLS_ERR_SSL_WANT_WRITE || tlsStatus == MBEDTLS_ERR_SSL_CONN_EOF)
    {
        tlsStatus = 0;
    }
    return tlsStatus;
}
#else
int32_t
EspTls_Send(NetworkContext_t *pNetworkContext, const void *pBuffer, size_t bytesToSend)
{
    ssize_t tlsStatus;
    tlsStatus = esp_tls_conn_write(pNetworkContext->pTlsContext, pBuffer, bytesToSend);
    if (tlsStatus == MBEDTLS_ERR_SSL_TIMEOUT || tlsStatus == MBEDTLS_ERR_SSL_WANT_READ || tlsStatus == MBEDTLS_ERR_SSL_WANT_WRITE)
    {
        tlsStatus = 0;
    }
    return tlsStatus;
}

int32_t EspTls_Recv(NetworkContext_t *pNetworkContext, void *pBuffer, size_t bytesToRecv)
{
    ssize_t tlsStatus;
    tlsStatus = esp_tls_conn_read(pNetworkContext->pTlsContext, pBuffer, bytesToRecv);
    if (tlsStatus == MBEDTLS_ERR_SSL_TIMEOUT || tlsStatus == MBEDTLS_ERR_SSL_WANT_READ || tlsStatus == MBEDTLS_ERR_SSL_WANT_WRITE)
    {
        tlsStatus = 0;
    }
    return tlsStatus;
}
#endif