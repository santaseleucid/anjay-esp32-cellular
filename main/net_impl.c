#include <netdb.h>
// #include <poll.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <avsystem/commons/avs_socket_v_table.h>
#include "esp_log.h"
#include "modem.h"
#include "main.h"
#include <arpa/inet.h>
#include <inttypes.h>
// ...
#include <avsystem/commons/avs_utils.h>
// #include "sockets_wrapper.h"
// #include "cellular_api.h"
#define SO_DOMAIN 1 // what is this ?
#ifdef AVS_COMMONS_NET_WITH_POSIX_AVS_SOCKET
#error "Custom implementation of the network layer conflicts with AVS_COMMONS_NET_WITH_POSIX_AVS_SOCKET"
#endif // AVS_COMMONS_NET_WITH_POSIX_AVS_SOCKET
// static char *address = "";
// static int port = 0;

//====================================================================================================
#ifndef CELLULAR // ie use WIFI(LwIP Sockets)

typedef union
{
    struct sockaddr addr;
    struct sockaddr_in in;
    struct sockaddr_in6 in6;
    struct sockaddr_storage storage;
} sockaddr_union_t;

avs_error_t _avs_net_initialize_global_compat_state(void);
void _avs_net_cleanup_global_compat_state(void);
avs_error_t _avs_net_create_tcp_socket(avs_net_socket_t **socket,
                                       const void *socket_configuration);
avs_error_t _avs_net_create_udp_socket(avs_net_socket_t **socket,
                                       const void *socket_configuration);

avs_error_t _avs_net_initialize_global_compat_state(void)
{
    return AVS_OK;
}
avs_error_t
avs_net_resolved_endpoint_get_host_port(const avs_net_resolved_endpoint_t *endp,
                                        char *host,
                                        size_t hostlen,
                                        char *serv,
                                        size_t servlen)
{
    avs_error_t ret = {0};
    return ret;
}

void _avs_net_cleanup_global_compat_state(void) {}

typedef struct
{
    const avs_net_socket_v_table_t *operations;
    int socktype;
    int fd;
    avs_time_duration_t recv_timeout;
} net_socket_impl_t;

/*****************************************************************************
 *
 * net_connect
 *
 ***************************************************************************** */
static avs_error_t
net_connect(avs_net_socket_t *sock_, const char *host, const char *port)
{
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    struct addrinfo hints = {
        .ai_socktype = sock->socktype};
    if (sock->fd >= 0)
    {
        getsockopt(sock->fd, SOL_SOCKET, SO_DOMAIN, &hints.ai_family,
                   &(socklen_t){sizeof(hints.ai_family)});
    }
    struct addrinfo *addr = NULL;
    avs_error_t err = AVS_OK;
    if (getaddrinfo(host, port, &hints, &addr) || !addr)
    {
        err = avs_errno(AVS_EADDRNOTAVAIL);
    }
    else if (sock->fd < 0 && (sock->fd = socket(addr->ai_family, addr->ai_socktype,
                                                addr->ai_protocol)) < 0)
    {
        err = avs_errno(AVS_UNKNOWN_ERROR);
    }

    else if (connect(sock->fd, addr->ai_addr, addr->ai_addrlen))
    {
        err = avs_errno(AVS_ECONNREFUSED);
    }
    printf("addr: %d -%s\n", addr->ai_addrlen, addr->ai_addr->sa_data);
    for (int i = 0; i < addr->ai_addr->sa_len; i++)
    {
        printf("%02x", (uint8_t)addr->ai_addr->sa_data[i]);
    }
    printf("\nprotoocl: %d\n", addr->ai_protocol);
    printf("socktype: %d\n", addr->ai_socktype);
    freeaddrinfo(addr);
    return err;
}
/*****************************************************************************
 *
 * net_send
 *
 ***************************************************************************** */
static avs_error_t
net_send(avs_net_socket_t *sock_, const void *buffer, size_t buffer_length)
{
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    ssize_t written = send(sock->fd, buffer, buffer_length, MSG_NOSIGNAL);
    printf("In net send\n");
    // char *s = (char *)buffer;

    // for (int i = 0; i < buffer_length; i++)
    // {
    //     printf("%02x ", s[i]);
    // }
    // printf("\n");
    if (written >= 0 && (size_t)written == buffer_length)
    {
        return AVS_OK;
    }
    return avs_errno(AVS_EIO);
}

/*****************************************************************************
 *
 * net_receive
 *
 ***************************************************************************** */
static avs_error_t net_receive(avs_net_socket_t *sock_,
                               size_t *out_bytes_received,
                               void *buffer,
                               size_t buffer_length)
{
    ESP_LOGW("NET", "In net_receive");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    struct pollfd pfd = {
        .fd = sock->fd,
        .events = POLLIN};
    int64_t timeout_ms;
    if (avs_time_duration_to_scalar(&timeout_ms, AVS_TIME_MS,
                                    sock->recv_timeout))
    {
        timeout_ms = -1;
    }
    else if (timeout_ms < 0)
    {
        timeout_ms = 0;
    }
    if (poll(&pfd, 1, (int)timeout_ms) == 0)
    {
        printf("poll\n");
        return avs_errno(AVS_ETIMEDOUT);
    }
    else
    {
        printf("poll else\n");
    }
    ssize_t bytes_received = read(sock->fd, buffer, buffer_length);
    if (bytes_received < 0)
    {
        return avs_errno(AVS_EIO);
    }
    *out_bytes_received = (size_t)bytes_received;
    if (buffer_length > 0 && sock->socktype == SOCK_DGRAM && (size_t)bytes_received == buffer_length)
    {
        return avs_errno(AVS_EMSGSIZE);
    }
    printf("data received!\n");
    char *s = (char *)buffer;
    for (int i = 0; i < bytes_received; i++)
    {
        printf("%02x ", s[i]);
    }
    printf("\n");
    return AVS_OK;
}
/*****************************************************************************
 *
 * net_close
 *
 ***************************************************************************** */
static avs_error_t net_close(avs_net_socket_t *sock_)
{
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    avs_error_t err = AVS_OK;
    if (sock->fd >= 0)
    {
        if (close(sock->fd))
        {
            err = avs_errno(AVS_EIO);
        }
        sock->fd = -1;
    }
    return err;
}
/*****************************************************************************
 *
 * net_cleanup
 *
 ***************************************************************************** */
static avs_error_t net_cleanup(avs_net_socket_t **sock_ptr)
{
    avs_error_t err = AVS_OK;
    if (sock_ptr && *sock_ptr)
    {
        err = net_close(*sock_ptr);
        avs_free(*sock_ptr);
        *sock_ptr = NULL;
    }
    return err;
}
/*****************************************************************************
 *
 * net_system_socket
 *
 ***************************************************************************** */
static const void *net_system_socket(avs_net_socket_t *sock_)
{
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    return &sock->fd;
}
/*****************************************************************************
 *
 * net_get_opt
 *
 ***************************************************************************** */
static avs_error_t net_get_opt(avs_net_socket_t *sock_,
                               avs_net_socket_opt_key_t option_key,
                               avs_net_socket_opt_value_t *out_option_value)
{
    // ESP_LOGW("NET", "In net_get_opt");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    switch (option_key)
    {
    case AVS_NET_SOCKET_OPT_RECV_TIMEOUT:
        out_option_value->recv_timeout = sock->recv_timeout;
        return AVS_OK;
    case AVS_NET_SOCKET_OPT_STATE:
        if (sock->fd < 0)
        {
            out_option_value->state = AVS_NET_SOCKET_STATE_CLOSED;
        }
        else
        {
            sockaddr_union_t addr;
            if (!getpeername(sock->fd, &addr.addr,
                             &(socklen_t){sizeof(addr)}) &&
                ((addr.in.sin_family == AF_INET && addr.in.sin_port != 0) || (addr.in6.sin6_family == AF_INET6 && addr.in6.sin6_port != 0)))
            {
                out_option_value->state = AVS_NET_SOCKET_STATE_CONNECTED;
            }
            else
            {
                out_option_value->state = AVS_NET_SOCKET_STATE_BOUND;
            }
        }
        return AVS_OK;
    case AVS_NET_SOCKET_OPT_INNER_MTU:
        out_option_value->mtu = 1464;
        return AVS_OK;
    default:
        return avs_errno(AVS_ENOTSUP);
    }
}
/*****************************************************************************
 *
 * net_set_opt
 *
 ***************************************************************************** */
static avs_error_t net_set_opt(avs_net_socket_t *sock_,
                               avs_net_socket_opt_key_t option_key,
                               avs_net_socket_opt_value_t option_value)
{
    ESP_LOGW("NET", "In net_set_opt");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    switch (option_key)
    {
    case AVS_NET_SOCKET_OPT_RECV_TIMEOUT:
        sock->recv_timeout = option_value.recv_timeout;
        return AVS_OK;
    default:
        return avs_errno(AVS_ENOTSUP);
    }
}

// ...

static avs_error_t stringify_sockaddr_host(const sockaddr_union_t *addr,
                                           char *out_buffer,
                                           size_t out_buffer_size)
{
    if ((addr->in.sin_family == AF_INET && inet_ntop(AF_INET, &addr->in.sin_addr, out_buffer,
                                                     (socklen_t)out_buffer_size)) ||
        (addr->in6.sin6_family == AF_INET6 && inet_ntop(AF_INET6, &addr->in6.sin6_addr, out_buffer,
                                                        (socklen_t)out_buffer_size)))
    {
        return AVS_OK;
    }
    return avs_errno(AVS_UNKNOWN_ERROR);
}

// ...

static avs_error_t net_remote_host(avs_net_socket_t *sock_,
                                   char *out_buffer,
                                   size_t out_buffer_size)
{
    ESP_LOGW("NET", "In net_remote_host");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    sockaddr_union_t addr;
    if (getpeername(sock->fd, &addr.addr, &(socklen_t){sizeof(addr)}))
    {
        return avs_errno(AVS_UNKNOWN_ERROR);
    }
    return stringify_sockaddr_host(&addr, out_buffer, out_buffer_size);
}

static avs_error_t stringify_sockaddr_port(const sockaddr_union_t *addr,
                                           char *out_buffer,
                                           size_t out_buffer_size)
{
    if ((addr->in.sin_family == AF_INET && avs_simple_snprintf(out_buffer, out_buffer_size, "%" PRIu16,
                                                               ntohs(addr->in.sin_port)) >= 0) ||
        (addr->in6.sin6_family == AF_INET6 && avs_simple_snprintf(out_buffer, out_buffer_size, "%" PRIu16,
                                                                  ntohs(addr->in6.sin6_port)) >= 0))
    {
        return AVS_OK;
    }
    return avs_errno(AVS_UNKNOWN_ERROR);
}

// ...

static avs_error_t net_remote_port(avs_net_socket_t *sock_,
                                   char *out_buffer,
                                   size_t out_buffer_size)
{
    ESP_LOGW("NET", "In net_remote_port");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    sockaddr_union_t addr;
    if (getpeername(sock->fd, &addr.addr, &(socklen_t){sizeof(addr)}))
    {
        return avs_errno(AVS_UNKNOWN_ERROR);
    }
    return stringify_sockaddr_port(&addr, out_buffer, out_buffer_size);
}
static avs_error_t
net_bind(avs_net_socket_t *sock_, const char *address, const char *port)
{
    ESP_LOGW("NET", "In net_bind");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    struct addrinfo hints = {
        .ai_flags = AI_PASSIVE,
        .ai_socktype = sock->socktype};
    if (sock->fd >= 0)
    {
        getsockopt(sock->fd, SOL_SOCKET, SO_DOMAIN, &hints.ai_family,
                   &(socklen_t){sizeof(hints.ai_family)});
    }
    struct addrinfo *addr = NULL;
    avs_error_t err = AVS_OK;
    if (getaddrinfo(address, port, &hints, &addr) || !addr)
    {
        err = avs_errno(AVS_EADDRNOTAVAIL);
    }
    else if ((sock->fd < 0 && (sock->fd = socket(addr->ai_family, addr->ai_socktype,
                                                 addr->ai_protocol)) < 0) ||
             setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, &(int){1},
                        sizeof(int)))
    {
        err = avs_errno(AVS_UNKNOWN_ERROR);
    }
    else if (bind(sock->fd, addr->ai_addr, addr->ai_addrlen))
    {
        err = avs_errno(AVS_ECONNREFUSED);
    }
    if (avs_is_err(err) && sock->fd >= 0)
    {
        close(sock->fd);
        sock->fd = -1;
    }
    freeaddrinfo(addr);
    return err;
}
/*****************************************************************************
 *
 * net_local_port
 *
 ***************************************************************************** */
static avs_error_t net_local_port(avs_net_socket_t *sock_,
                                  char *out_buffer,
                                  size_t out_buffer_size)
{
    ESP_LOGW("NET", "In net_local_port");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    sockaddr_union_t addr;
    if (getsockname(sock->fd, &addr.addr, &(socklen_t){sizeof(addr)}))
    {
        return avs_errno(AVS_UNKNOWN_ERROR);
    }
    avs_error_t ret = stringify_sockaddr_port(&addr, out_buffer, out_buffer_size);
    printf("Out Buffer: %s\n", out_buffer);
    return AVS_OK;
}
/*****************************************************************************
 *
 * avs_net_socket_v_table_t
 *
 ***************************************************************************** */
static const avs_net_socket_v_table_t NET_SOCKET_VTABLE = {
    .connect = net_connect,
    .send = net_send,
    .receive = net_receive,
    .bind = net_bind,
    .close = net_close,
    .cleanup = net_cleanup,
    .get_system_socket = net_system_socket,
    .get_remote_host = net_remote_host,
    .get_remote_port = net_remote_port,
    .get_local_port = net_local_port,
    .get_opt = net_get_opt,
    .set_opt = net_set_opt};

/*****************************************************************************
 *
 * net_create_socket
 *
 ***************************************************************************** */
static avs_error_t
net_create_socket(avs_net_socket_t **socket_ptr,
                  const avs_net_socket_configuration_t *configuration,
                  int socktype)
{
    assert(socket_ptr);
    assert(!*socket_ptr);
    (void)configuration; // unused config
    net_socket_impl_t *socket =
        (net_socket_impl_t *)avs_calloc(1, sizeof(net_socket_impl_t));
    if (!socket)
    {
        return avs_errno(AVS_ENOMEM);
    }
    socket->operations = &NET_SOCKET_VTABLE;
    socket->socktype = socktype;
    socket->fd = -1;
    socket->recv_timeout = avs_time_duration_from_scalar(30, AVS_TIME_S);
    *socket_ptr = (avs_net_socket_t *)socket;
    return AVS_OK;
}

/*****************************************************************************
 *
 * _avs_net_create_udp_socket
 *
 ***************************************************************************** */
avs_error_t _avs_net_create_udp_socket(avs_net_socket_t **socket_ptr,
                                       const void *configuration)
{
    printf("create_udp\n");
    return net_create_socket(
        socket_ptr, (const avs_net_socket_configuration_t *)configuration,
        SOCK_DGRAM);
}
/*****************************************************************************
 *
 * _avs_net_create_tcp_socket
 *
 ***************************************************************************** */
avs_error_t _avs_net_create_tcp_socket(avs_net_socket_t **socket_ptr,
                                       const void *configuration)
{
    printf("create_tcp\n");
    return net_create_socket(
        socket_ptr, (const avs_net_socket_configuration_t *)configuration,
        SOCK_STREAM);
}
//====================================================================================================
#else // USE CELLULAR (i.e. frertos cellular socket wrapper)
avs_error_t _avs_net_initialize_global_compat_state(void);
void _avs_net_cleanup_global_compat_state(void);
avs_error_t _avs_net_create_tcp_socket(avs_net_socket_t **socket,
                                       const void *socket_configuration);
avs_error_t _avs_net_create_udp_socket(avs_net_socket_t **socket,
                                       const void *socket_configuration);

avs_error_t _avs_net_initialize_global_compat_state(void)
{
    return AVS_OK;
}
avs_error_t
avs_net_resolved_endpoint_get_host_port(const avs_net_resolved_endpoint_t *endp,
                                        char *host,
                                        size_t hostlen,
                                        char *serv,
                                        size_t servlen)
{
    avs_error_t ret = {0};
    return ret;
}

void _avs_net_cleanup_global_compat_state(void) {}

typedef struct
{
    const avs_net_socket_v_table_t *operations;
    int socktype;
    int fd;
    avs_time_duration_t recv_timeout;
    // avs_time_duration_t send_timeout;
    Socket_t *cell_socket;
} net_socket_impl_t;

typedef struct xSOCKET
{
    CellularSocketHandle_t cellularSocketHandle;
    uint32_t ulFlags;

    TickType_t receiveTimeout;
    TickType_t sendTimeout;

    EventGroupHandle_t socketEventGroupHandle;
} cellularSocketWrapper_t;

/*****************************************************************************
 *
 * net_connect
 *
 ***************************************************************************** */
static avs_error_t net_connect(avs_net_socket_t *sock_, const char *host, const char *port)
{
    ESP_LOGW("NET", "In net_connect");
    avs_error_t err = AVS_OK;
    BaseType_t cell_ret = SOCKETS_ERROR_NONE;
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    uint16_t port_int = atoi(port);
    int64_t timeout; //
    avs_time_duration_to_scalar(&timeout, AVS_TIME_MS, sock->recv_timeout);
    char *resolved_ip = malloc(40); // = malloc(30);
    Cellular_GetHostByName(CellularHandle,
                           CellularSocketPdnContextId,
                           host,
                           resolved_ip);
    ESP_LOGI("NET", "Connecting to host: %s with IP addr: %s on port %d with timeout of %d", host, resolved_ip, port_int, (uint32_t)timeout);
    cell_ret = Sockets_Connect(sock->cell_socket, resolved_ip, port_int, (uint32_t)timeout, (uint32_t)timeout);
    ESP_LOGI("NET", "Sockets_Connect returned: %d", cell_ret);
    return err;
}

/*****************************************************************************
 *
 * net_send
 *
 ***************************************************************************** */
static avs_error_t
net_send(avs_net_socket_t *sock_, const void *buffer, size_t buffer_length)
{
    ESP_LOGW("NET", "In net_send");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    // ssize_t written = send(sock->fd, buffer, buffer_length, MSG_NOSIGNAL);
    int32_t written = Sockets_Send(*sock->cell_socket, buffer, buffer_length);
    char *s = (char *)buffer;
    // for (int i = 0; i < buffer_length; i++)
    // {
    //     printf("%02x ", s[i]);
    // }
    // printf("\n");
    if (written >= 0 && (size_t)written == buffer_length)
    {
        return AVS_OK;
    }
    return avs_errno(AVS_EIO);
}
/*****************************************************************************
 *
 * net_receive
 *
 ***************************************************************************** */
static avs_error_t net_receive(avs_net_socket_t *sock_,
                               size_t *out_bytes_received,
                               void *buffer,
                               size_t buffer_length)
{
    ESP_LOGW("NET", "In net_receive");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    int32_t bytes_received = Sockets_Recv(*sock->cell_socket, buffer, buffer_length);
    if (bytes_received < 0)
    {
        printf("AVS_EIO\n");
        return avs_errno(AVS_EIO);
    }

    printf("data received!\n");
    char *buf = (char *)buffer;
    *out_bytes_received = (size_t)bytes_received;
    if (buffer_length > 0 && sock->socktype == SOCK_DGRAM && (size_t)bytes_received == buffer_length)
    {
        printf("AVS_EMSGSIZE\n");
        return avs_errno(AVS_EMSGSIZE);
    }
    return AVS_OK;
}
/*****************************************************************************
 *
 * net_close
 *
 ***************************************************************************** */
static avs_error_t net_close(avs_net_socket_t *sock_)
{
    ESP_LOGW("NET", "In net_close");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    avs_error_t err = AVS_OK;
    if (sock->fd >= 0)
    {
        if (close(sock->fd))
        {
            err = avs_errno(AVS_EIO);
        }
        sock->fd = -1;
    }
    return err;
}
/*****************************************************************************
 *
 * net_cleanup
 *
 ***************************************************************************** */
static avs_error_t net_cleanup(avs_net_socket_t **sock_ptr)
{
    ESP_LOGW("NET", "In net_cleanup");
    avs_error_t err = AVS_OK;
    if (sock_ptr && *sock_ptr)
    {
        err = net_close(*sock_ptr);
        avs_free(*sock_ptr);
        *sock_ptr = NULL;
    }
    return err;
}
/*****************************************************************************
 *
 * net_get_opt
 *
 ***************************************************************************** */
static avs_error_t net_get_opt(avs_net_socket_t *sock_,
                               avs_net_socket_opt_key_t option_key,
                               avs_net_socket_opt_value_t *out_option_value)
{

    // ESP_LOGW("NET", "In net_get_opt");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    cellularSocketWrapper_t *pCellularSocketContext = (cellularSocketWrapper_t *)(*sock->cell_socket);

    switch (option_key)
    {
    case AVS_NET_SOCKET_OPT_RECV_TIMEOUT:
        // printf("AVS_NET_SOCKET_OPT_RECV_TIMEOUT\n");
        out_option_value->recv_timeout = sock->recv_timeout;
        return AVS_OK;
    case AVS_NET_SOCKET_OPT_STATE:
        // printf("AVS_NET_SOCKET_OPT_STATE: %d\n", pCellularSocketContext->cellularSocketHandle->socketState);

        if (pCellularSocketContext->cellularSocketHandle->socketState != 2)
        {
            out_option_value->state = AVS_NET_SOCKET_STATE_CLOSED;
        }
        else
        {
            // if (!address || !port)
            // {
            out_option_value->state = AVS_NET_SOCKET_STATE_CONNECTED;
            // }
            // else
            // {
            //     out_option_value->state = AVS_NET_SOCKET_STATE_BOUND;
            // }
        }
        return AVS_OK;
    case AVS_NET_SOCKET_OPT_INNER_MTU:
        printf("AVS_NET_SOCKET_OPT_INNER_MTU\n");
        out_option_value->mtu = 1464;
        return AVS_OK;
    default:
        printf("AVS_ENOTSUP\n");
        return avs_errno(AVS_ENOTSUP);
    }
}
/*****************************************************************************
 *
 * net_set_opt
 *
 ***************************************************************************** */
static avs_error_t net_set_opt(avs_net_socket_t *sock_,
                               avs_net_socket_opt_key_t option_key,
                               avs_net_socket_opt_value_t option_value)
{
    ESP_LOGW("NET", "In net_set_opt");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    switch (option_key)
    {
    case AVS_NET_SOCKET_OPT_RECV_TIMEOUT:
        // printf("AVS_NET_SOCKET_OPT_RECV_TIMEOUT: %d\n", option_value.recv_timeout);
        // sock->recv_timeout = option_value.recv_timeout;
        return AVS_OK;

    default:
        return avs_errno(AVS_ENOTSUP);
    }
}

/*****************************************************************************
 *
 * net_system_socket
 *
 ***************************************************************************** */
static const void *net_system_socket(avs_net_socket_t *sock_)
{
    // ESP_LOGW("NET", "In net_system_socket");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    return &sock->fd;
}
/*****************************************************************************
 *
 * net_system_socket
 *
 * NOT IMPLEMENTED
 *
 ***************************************************************************** */
static avs_error_t net_bind(avs_net_socket_t *sock_, const char *address, const char *port)
{
    ESP_LOGW("NET", "In net_bind");
    printf("Address: %s \n Port: %s\n", address, port);
    avs_error_t err = AVS_OK;
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    return err;
}
/*****************************************************************************
 *
 * net_local_port
 *
 * NOT IMPLEMENTED
 *
 ***************************************************************************** */
static avs_error_t net_local_port(avs_net_socket_t *sock_,
                                  char *out_buffer,
                                  size_t out_buffer_size)
{
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;

    ESP_LOGW("NET", "In net_local_port");
    avs_error_t err = AVS_OK;
    snprintf(out_buffer, out_buffer_size, "%" PRIu16,
             5684);
    return err;
    // stringify_sockaddr_port(&addr, out_buffer, out_buffer_size);
}
/*****************************************************************************
 *
 * net_remote_port
 *
 *  NOT IMPLEMENTED
 *
 ***************************************************************************** */
static avs_error_t net_remote_host(avs_net_socket_t *sock_,
                                   char *out_buffer,
                                   size_t out_buffer_size)
{
    ESP_LOGW("NET", "In net_remote_port");
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    // sockaddr_union_t addr;
    // if (getpeername(sock->fd, &addr.addr, &(socklen_t){sizeof(addr)}))
    // {
    //     return avs_errno(AVS_UNKNOWN_ERROR);
    // }
    return AVS_OK; // stringify_sockaddr_host(&addr, out_buffer, out_buffer_size);
}
/*****************************************************************************
 *
 * net_remote_port
 *
  NOT IMPLEMENTED
 *
 ***************************************************************************** */
static avs_error_t net_remote_port(avs_net_socket_t *sock_,
                                   char *out_buffer,
                                   size_t out_buffer_size)
{
    ESP_LOGW("NET", "In net_remote_port");
    avs_error_t err = AVS_OK;
    net_socket_impl_t *sock = (net_socket_impl_t *)sock_;
    snprintf(out_buffer, out_buffer_size, "%" PRIu16,
             5684);
    // sockaddr_union_t addr;
    // if (getpeername(sock->fd, &addr.addr, &(socklen_t){sizeof(addr)}))
    // {
    //     return avs_errno(AVS_UNKNOWN_ERROR);
    // }
    return err;
    // stringify_sockaddr_port(&addr, out_buffer, out_buffer_size);
}
/*****************************************************************************
 *
 * avs_net_socket_v_table_t
 *
 ***************************************************************************** */
static const avs_net_socket_v_table_t NET_SOCKET_VTABLE = {
    .connect = net_connect,
    .send = net_send,
    .receive = net_receive,
    .close = net_close,
    .cleanup = net_cleanup,
    .get_system_socket = net_system_socket,
    .get_opt = net_get_opt,
    .set_opt = net_set_opt,
    // .get_remote_host = net_remote_host,
    // .get_remote_port = net_remote_port,
    // .bind = net_bind,
    // .get_local_port = net_local_port,
    //.shutdown = net_shutdown,
    //.get_remote_hostname = net_remote_hostname,
};
/*****************************************************************************
 *
 * net_create_socket
 *
 ***************************************************************************** */
static avs_error_t
net_create_socket(avs_net_socket_t **socket_ptr,
                  const avs_net_socket_configuration_t *configuration,
                  int socktype)
{
    assert(socket_ptr);
    assert(!*socket_ptr);
    ESP_LOGW("NET", "In net_create_socket");
    (void)configuration; // unused config
    net_socket_impl_t *socket =
        (net_socket_impl_t *)avs_calloc(1, sizeof(net_socket_impl_t));
    if (!socket)
    {
        return avs_errno(AVS_ENOMEM);
    }
    // printf("Sizoef Socket_t: %d\n", sizeof(Socket_t));
    // printf("Sizoef cellularSocketWrapper_t: %d\n", sizeof(cellularSocketWrapper_t));
    Socket_t *udpSocket = (Socket_t *)malloc(sizeof(Socket_t));
    socket->operations = &NET_SOCKET_VTABLE;
    socket->socktype = socktype;
    socket->fd = -1;
    socket->recv_timeout = avs_time_duration_from_scalar(30, AVS_TIME_S);
    socket->cell_socket = udpSocket;
    *socket_ptr = (avs_net_socket_t *)socket;
    return AVS_OK;
}
/*****************************************************************************
 *
 * _avs_net_create_udp_socket
 *
 ***************************************************************************** */
avs_error_t _avs_net_create_udp_socket(avs_net_socket_t **socket_ptr,
                                       const void *configuration)
{
    return net_create_socket(
        socket_ptr, (const avs_net_socket_configuration_t *)configuration,
        SOCK_DGRAM);
}
/*****************************************************************************
 *
 * _avs_net_create_tcp_socket
 *
 ***************************************************************************** */
avs_error_t _avs_net_create_tcp_socket(avs_net_socket_t **socket_ptr,
                                       const void *configuration)
{
    return net_create_socket(
        socket_ptr, (const avs_net_socket_configuration_t *)configuration,
        SOCK_STREAM);
}
#endif
