/*
 * Copyright 2017-2021 AVSystem <avsystem@avsystem.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANJAY_CONFIG_LOG_H
#define ANJAY_CONFIG_LOG_H

#include <anjay_modules/anjay_utils_core.h>

VISIBILITY_PRIVATE_HEADER_BEGIN

// clang-format off
static inline void _anjay_log_feature_list(void) {
    _anjay_log(anjay, TRACE, "ANJAY_DTLS_SESSION_BUFFER_SIZE = " AVS_QUOTE_MACRO(ANJAY_DTLS_SESSION_BUFFER_SIZE));
    _anjay_log(anjay, TRACE, "ANJAY_MAX_DOUBLE_STRING_SIZE = " AVS_QUOTE_MACRO(ANJAY_MAX_DOUBLE_STRING_SIZE));
    _anjay_log(anjay, TRACE, "ANJAY_MAX_PK_OR_IDENTITY_SIZE = " AVS_QUOTE_MACRO(ANJAY_MAX_PK_OR_IDENTITY_SIZE));
    _anjay_log(anjay, TRACE, "ANJAY_MAX_SECRET_KEY_SIZE = " AVS_QUOTE_MACRO(ANJAY_MAX_SECRET_KEY_SIZE));
    _anjay_log(anjay, TRACE, "ANJAY_MAX_URI_QUERY_SEGMENT_SIZE = " AVS_QUOTE_MACRO(ANJAY_MAX_URI_QUERY_SEGMENT_SIZE));
    _anjay_log(anjay, TRACE, "ANJAY_MAX_URI_SEGMENT_SIZE = " AVS_QUOTE_MACRO(ANJAY_MAX_URI_SEGMENT_SIZE));
#ifdef ANJAY_WITHOUT_DEREGISTER
    _anjay_log(anjay, TRACE, "ANJAY_WITHOUT_DEREGISTER = ON");
#else // ANJAY_WITHOUT_DEREGISTER
    _anjay_log(anjay, TRACE, "ANJAY_WITHOUT_DEREGISTER = OFF");
#endif // ANJAY_WITHOUT_DEREGISTER
#ifdef ANJAY_WITHOUT_IP_STICKINESS
    _anjay_log(anjay, TRACE, "ANJAY_WITHOUT_IP_STICKINESS = ON");
#else // ANJAY_WITHOUT_IP_STICKINESS
    _anjay_log(anjay, TRACE, "ANJAY_WITHOUT_IP_STICKINESS = OFF");
#endif // ANJAY_WITHOUT_IP_STICKINESS
#ifdef ANJAY_WITHOUT_PLAINTEXT
    _anjay_log(anjay, TRACE, "ANJAY_WITHOUT_PLAINTEXT = ON");
#else // ANJAY_WITHOUT_PLAINTEXT
    _anjay_log(anjay, TRACE, "ANJAY_WITHOUT_PLAINTEXT = OFF");
#endif // ANJAY_WITHOUT_PLAINTEXT
#ifdef ANJAY_WITHOUT_TLV
    _anjay_log(anjay, TRACE, "ANJAY_WITHOUT_TLV = ON");
#else // ANJAY_WITHOUT_TLV
    _anjay_log(anjay, TRACE, "ANJAY_WITHOUT_TLV = OFF");
#endif // ANJAY_WITHOUT_TLV
#ifdef ANJAY_WITH_ACCESS_CONTROL
    _anjay_log(anjay, TRACE, "ANJAY_WITH_ACCESS_CONTROL = ON");
#else // ANJAY_WITH_ACCESS_CONTROL
    _anjay_log(anjay, TRACE, "ANJAY_WITH_ACCESS_CONTROL = OFF");
#endif // ANJAY_WITH_ACCESS_CONTROL
#ifdef ANJAY_WITH_BOOTSTRAP
    _anjay_log(anjay, TRACE, "ANJAY_WITH_BOOTSTRAP = ON");
#else // ANJAY_WITH_BOOTSTRAP
    _anjay_log(anjay, TRACE, "ANJAY_WITH_BOOTSTRAP = OFF");
#endif // ANJAY_WITH_BOOTSTRAP
#ifdef ANJAY_WITH_CBOR
    _anjay_log(anjay, TRACE, "ANJAY_WITH_CBOR = ON");
#else // ANJAY_WITH_CBOR
    _anjay_log(anjay, TRACE, "ANJAY_WITH_CBOR = OFF");
#endif // ANJAY_WITH_CBOR
#ifdef ANJAY_WITH_COAP_DOWNLOAD
    _anjay_log(anjay, TRACE, "ANJAY_WITH_COAP_DOWNLOAD = ON");
#else // ANJAY_WITH_COAP_DOWNLOAD
    _anjay_log(anjay, TRACE, "ANJAY_WITH_COAP_DOWNLOAD = OFF");
#endif // ANJAY_WITH_COAP_DOWNLOAD
#ifdef ANJAY_WITH_COAP_OSCORE
    _anjay_log(anjay, TRACE, "ANJAY_WITH_COAP_OSCORE = ON");
#else // ANJAY_WITH_COAP_OSCORE
    _anjay_log(anjay, TRACE, "ANJAY_WITH_COAP_OSCORE = OFF");
#endif // ANJAY_WITH_COAP_OSCORE
#ifdef ANJAY_WITH_CON_ATTR
    _anjay_log(anjay, TRACE, "ANJAY_WITH_CON_ATTR = ON");
#else // ANJAY_WITH_CON_ATTR
    _anjay_log(anjay, TRACE, "ANJAY_WITH_CON_ATTR = OFF");
#endif // ANJAY_WITH_CON_ATTR
#ifdef ANJAY_WITH_CORE_PERSISTENCE
    _anjay_log(anjay, TRACE, "ANJAY_WITH_CORE_PERSISTENCE = ON");
#else // ANJAY_WITH_CORE_PERSISTENCE
    _anjay_log(anjay, TRACE, "ANJAY_WITH_CORE_PERSISTENCE = OFF");
#endif // ANJAY_WITH_CORE_PERSISTENCE
#ifdef ANJAY_WITH_DISCOVER
    _anjay_log(anjay, TRACE, "ANJAY_WITH_DISCOVER = ON");
#else // ANJAY_WITH_DISCOVER
    _anjay_log(anjay, TRACE, "ANJAY_WITH_DISCOVER = OFF");
#endif // ANJAY_WITH_DISCOVER
#ifdef ANJAY_WITH_DOWNLOADER
    _anjay_log(anjay, TRACE, "ANJAY_WITH_DOWNLOADER = ON");
#else // ANJAY_WITH_DOWNLOADER
    _anjay_log(anjay, TRACE, "ANJAY_WITH_DOWNLOADER = OFF");
#endif // ANJAY_WITH_DOWNLOADER
#ifdef ANJAY_WITH_EST
    _anjay_log(anjay, TRACE, "ANJAY_WITH_EST = ON");
#else // ANJAY_WITH_EST
    _anjay_log(anjay, TRACE, "ANJAY_WITH_EST = OFF");
#endif // ANJAY_WITH_EST
#ifdef ANJAY_WITH_EVENT_LOOP
    _anjay_log(anjay, TRACE, "ANJAY_WITH_EVENT_LOOP = ON");
#else // ANJAY_WITH_EVENT_LOOP
    _anjay_log(anjay, TRACE, "ANJAY_WITH_EVENT_LOOP = OFF");
#endif // ANJAY_WITH_EVENT_LOOP
#ifdef ANJAY_WITH_HTTP_DOWNLOAD
    _anjay_log(anjay, TRACE, "ANJAY_WITH_HTTP_DOWNLOAD = ON");
#else // ANJAY_WITH_HTTP_DOWNLOAD
    _anjay_log(anjay, TRACE, "ANJAY_WITH_HTTP_DOWNLOAD = OFF");
#endif // ANJAY_WITH_HTTP_DOWNLOAD
#ifdef ANJAY_WITH_LEGACY_CONTENT_FORMAT_SUPPORT
    _anjay_log(anjay, TRACE, "ANJAY_WITH_LEGACY_CONTENT_FORMAT_SUPPORT = ON");
#else // ANJAY_WITH_LEGACY_CONTENT_FORMAT_SUPPORT
    _anjay_log(anjay, TRACE, "ANJAY_WITH_LEGACY_CONTENT_FORMAT_SUPPORT = OFF");
#endif // ANJAY_WITH_LEGACY_CONTENT_FORMAT_SUPPORT
#ifdef ANJAY_WITH_LOGS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_LOGS = ON");
#else // ANJAY_WITH_LOGS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_LOGS = OFF");
#endif // ANJAY_WITH_LOGS
#ifdef ANJAY_WITH_LWM2M11
    _anjay_log(anjay, TRACE, "ANJAY_WITH_LWM2M11 = ON");
#else // ANJAY_WITH_LWM2M11
    _anjay_log(anjay, TRACE, "ANJAY_WITH_LWM2M11 = OFF");
#endif // ANJAY_WITH_LWM2M11
#ifdef ANJAY_WITH_LWM2M_JSON
    _anjay_log(anjay, TRACE, "ANJAY_WITH_LWM2M_JSON = ON");
#else // ANJAY_WITH_LWM2M_JSON
    _anjay_log(anjay, TRACE, "ANJAY_WITH_LWM2M_JSON = OFF");
#endif // ANJAY_WITH_LWM2M_JSON
#ifdef ANJAY_WITH_MODULE_ACCESS_CONTROL
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_ACCESS_CONTROL = ON");
#else // ANJAY_WITH_MODULE_ACCESS_CONTROL
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_ACCESS_CONTROL = OFF");
#endif // ANJAY_WITH_MODULE_ACCESS_CONTROL
#ifdef ANJAY_WITH_MODULE_ATTR_STORAGE
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_ATTR_STORAGE = ON");
#else // ANJAY_WITH_MODULE_ATTR_STORAGE
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_ATTR_STORAGE = OFF");
#endif // ANJAY_WITH_MODULE_ATTR_STORAGE
#ifdef ANJAY_WITH_MODULE_AT_SMS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_AT_SMS = ON");
#else // ANJAY_WITH_MODULE_AT_SMS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_AT_SMS = OFF");
#endif // ANJAY_WITH_MODULE_AT_SMS
#ifdef ANJAY_WITH_MODULE_BG96_NIDD
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_BG96_NIDD = ON");
#else // ANJAY_WITH_MODULE_BG96_NIDD
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_BG96_NIDD = OFF");
#endif // ANJAY_WITH_MODULE_BG96_NIDD
#ifdef ANJAY_WITH_MODULE_BOOTSTRAPPER
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_BOOTSTRAPPER = ON");
#else // ANJAY_WITH_MODULE_BOOTSTRAPPER
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_BOOTSTRAPPER = OFF");
#endif // ANJAY_WITH_MODULE_BOOTSTRAPPER
#ifdef ANJAY_WITH_MODULE_FW_UPDATE
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_FW_UPDATE = ON");
#else // ANJAY_WITH_MODULE_FW_UPDATE
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_FW_UPDATE = OFF");
#endif // ANJAY_WITH_MODULE_FW_UPDATE
#ifdef ANJAY_WITH_MODULE_IPSO_OBJECTS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_IPSO_OBJECTS = ON");
#else // ANJAY_WITH_MODULE_IPSO_OBJECTS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_IPSO_OBJECTS = OFF");
#endif // ANJAY_WITH_MODULE_IPSO_OBJECTS
#ifdef ANJAY_WITH_MODULE_OSCORE
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_OSCORE = ON");
#else // ANJAY_WITH_MODULE_OSCORE
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_OSCORE = OFF");
#endif // ANJAY_WITH_MODULE_OSCORE
#ifdef ANJAY_WITH_MODULE_SECURITY
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_SECURITY = ON");
#else // ANJAY_WITH_MODULE_SECURITY
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_SECURITY = OFF");
#endif // ANJAY_WITH_MODULE_SECURITY
#ifdef ANJAY_WITH_MODULE_SERVER
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_SERVER = ON");
#else // ANJAY_WITH_MODULE_SERVER
    _anjay_log(anjay, TRACE, "ANJAY_WITH_MODULE_SERVER = OFF");
#endif // ANJAY_WITH_MODULE_SERVER
#ifdef ANJAY_WITH_NET_STATS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_NET_STATS = ON");
#else // ANJAY_WITH_NET_STATS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_NET_STATS = OFF");
#endif // ANJAY_WITH_NET_STATS
#ifdef ANJAY_WITH_NIDD
    _anjay_log(anjay, TRACE, "ANJAY_WITH_NIDD = ON");
#else // ANJAY_WITH_NIDD
    _anjay_log(anjay, TRACE, "ANJAY_WITH_NIDD = OFF");
#endif // ANJAY_WITH_NIDD
#ifdef ANJAY_WITH_OBSERVATION_STATUS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_OBSERVATION_STATUS = ON");
#else // ANJAY_WITH_OBSERVATION_STATUS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_OBSERVATION_STATUS = OFF");
#endif // ANJAY_WITH_OBSERVATION_STATUS
#ifdef ANJAY_WITH_OBSERVE
    _anjay_log(anjay, TRACE, "ANJAY_WITH_OBSERVE = ON");
#else // ANJAY_WITH_OBSERVE
    _anjay_log(anjay, TRACE, "ANJAY_WITH_OBSERVE = OFF");
#endif // ANJAY_WITH_OBSERVE
#ifdef ANJAY_WITH_SEND
    _anjay_log(anjay, TRACE, "ANJAY_WITH_SEND = ON");
#else // ANJAY_WITH_SEND
    _anjay_log(anjay, TRACE, "ANJAY_WITH_SEND = OFF");
#endif // ANJAY_WITH_SEND
#ifdef ANJAY_WITH_SENML_JSON
    _anjay_log(anjay, TRACE, "ANJAY_WITH_SENML_JSON = ON");
#else // ANJAY_WITH_SENML_JSON
    _anjay_log(anjay, TRACE, "ANJAY_WITH_SENML_JSON = OFF");
#endif // ANJAY_WITH_SENML_JSON
#ifdef ANJAY_WITH_SMS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_SMS = ON");
#else // ANJAY_WITH_SMS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_SMS = OFF");
#endif // ANJAY_WITH_SMS
#ifdef ANJAY_WITH_SMS_MULTIPART
    _anjay_log(anjay, TRACE, "ANJAY_WITH_SMS_MULTIPART = ON");
#else // ANJAY_WITH_SMS_MULTIPART
    _anjay_log(anjay, TRACE, "ANJAY_WITH_SMS_MULTIPART = OFF");
#endif // ANJAY_WITH_SMS_MULTIPART
#ifdef ANJAY_WITH_THREAD_SAFETY
    _anjay_log(anjay, TRACE, "ANJAY_WITH_THREAD_SAFETY = ON");
#else // ANJAY_WITH_THREAD_SAFETY
    _anjay_log(anjay, TRACE, "ANJAY_WITH_THREAD_SAFETY = OFF");
#endif // ANJAY_WITH_THREAD_SAFETY
#ifdef ANJAY_WITH_TRACE_LOGS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_TRACE_LOGS = ON");
#else // ANJAY_WITH_TRACE_LOGS
    _anjay_log(anjay, TRACE, "ANJAY_WITH_TRACE_LOGS = OFF");
#endif // ANJAY_WITH_TRACE_LOGS
    _anjay_log(anjay, TRACE, "AVS_COAP_UDP_NOTIFY_CACHE_SIZE = " AVS_QUOTE_MACRO(AVS_COAP_UDP_NOTIFY_CACHE_SIZE));
#ifdef AVS_COMMONS_BIG_ENDIAN
    _anjay_log(anjay, TRACE, "AVS_COMMONS_BIG_ENDIAN = ON");
#else // AVS_COMMONS_BIG_ENDIAN
    _anjay_log(anjay, TRACE, "AVS_COMMONS_BIG_ENDIAN = OFF");
#endif // AVS_COMMONS_BIG_ENDIAN
#ifdef AVS_COMMONS_COMPAT_THREADING_PTHREAD_HAVE_PTHREAD_CONDATTR_SETCLOCK
    _anjay_log(anjay, TRACE, "AVS_COMMONS_COMPAT_THREADING_PTHREAD_HAVE_PTHREAD_CONDATTR_SETCLOCK = ON");
#else // AVS_COMMONS_COMPAT_THREADING_PTHREAD_HAVE_PTHREAD_CONDATTR_SETCLOCK
    _anjay_log(anjay, TRACE, "AVS_COMMONS_COMPAT_THREADING_PTHREAD_HAVE_PTHREAD_CONDATTR_SETCLOCK = OFF");
#endif // AVS_COMMONS_COMPAT_THREADING_PTHREAD_HAVE_PTHREAD_CONDATTR_SETCLOCK
#ifdef AVS_COMMONS_COMPAT_THREADING_WITH_ATOMIC_SPINLOCK
    _anjay_log(anjay, TRACE, "AVS_COMMONS_COMPAT_THREADING_WITH_ATOMIC_SPINLOCK = ON");
#else // AVS_COMMONS_COMPAT_THREADING_WITH_ATOMIC_SPINLOCK
    _anjay_log(anjay, TRACE, "AVS_COMMONS_COMPAT_THREADING_WITH_ATOMIC_SPINLOCK = OFF");
#endif // AVS_COMMONS_COMPAT_THREADING_WITH_ATOMIC_SPINLOCK
#ifdef AVS_COMMONS_COMPAT_THREADING_WITH_PTHREAD
    _anjay_log(anjay, TRACE, "AVS_COMMONS_COMPAT_THREADING_WITH_PTHREAD = ON");
#else // AVS_COMMONS_COMPAT_THREADING_WITH_PTHREAD
    _anjay_log(anjay, TRACE, "AVS_COMMONS_COMPAT_THREADING_WITH_PTHREAD = OFF");
#endif // AVS_COMMONS_COMPAT_THREADING_WITH_PTHREAD
#ifdef AVS_COMMONS_HAVE_BUILTIN_ADD_OVERFLOW
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HAVE_BUILTIN_ADD_OVERFLOW = ON");
#else // AVS_COMMONS_HAVE_BUILTIN_ADD_OVERFLOW
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HAVE_BUILTIN_ADD_OVERFLOW = OFF");
#endif // AVS_COMMONS_HAVE_BUILTIN_ADD_OVERFLOW
#ifdef AVS_COMMONS_HAVE_BUILTIN_MUL_OVERFLOW
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HAVE_BUILTIN_MUL_OVERFLOW = ON");
#else // AVS_COMMONS_HAVE_BUILTIN_MUL_OVERFLOW
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HAVE_BUILTIN_MUL_OVERFLOW = OFF");
#endif // AVS_COMMONS_HAVE_BUILTIN_MUL_OVERFLOW
#ifdef AVS_COMMONS_HAVE_DLSYM
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HAVE_DLSYM = ON");
#else // AVS_COMMONS_HAVE_DLSYM
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HAVE_DLSYM = OFF");
#endif // AVS_COMMONS_HAVE_DLSYM
#ifdef AVS_COMMONS_HAVE_NET_IF_H
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HAVE_NET_IF_H = ON");
#else // AVS_COMMONS_HAVE_NET_IF_H
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HAVE_NET_IF_H = OFF");
#endif // AVS_COMMONS_HAVE_NET_IF_H
#ifdef AVS_COMMONS_HAVE_PRAGMA_DIAGNOSTIC
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HAVE_PRAGMA_DIAGNOSTIC = ON");
#else // AVS_COMMONS_HAVE_PRAGMA_DIAGNOSTIC
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HAVE_PRAGMA_DIAGNOSTIC = OFF");
#endif // AVS_COMMONS_HAVE_PRAGMA_DIAGNOSTIC
#ifdef AVS_COMMONS_HAVE_VISIBILITY
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HAVE_VISIBILITY = ON");
#else // AVS_COMMONS_HAVE_VISIBILITY
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HAVE_VISIBILITY = OFF");
#endif // AVS_COMMONS_HAVE_VISIBILITY
#ifdef AVS_COMMONS_HTTP_WITH_ZLIB
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HTTP_WITH_ZLIB = ON");
#else // AVS_COMMONS_HTTP_WITH_ZLIB
    _anjay_log(anjay, TRACE, "AVS_COMMONS_HTTP_WITH_ZLIB = OFF");
#endif // AVS_COMMONS_HTTP_WITH_ZLIB
#ifdef AVS_COMMONS_LOG_MAX_LINE_LENGTH
    _anjay_log(anjay, TRACE, "AVS_COMMONS_LOG_MAX_LINE_LENGTH = ON");
#else // AVS_COMMONS_LOG_MAX_LINE_LENGTH
    _anjay_log(anjay, TRACE, "AVS_COMMONS_LOG_MAX_LINE_LENGTH = OFF");
#endif // AVS_COMMONS_LOG_MAX_LINE_LENGTH
#ifdef AVS_COMMONS_LOG_USE_GLOBAL_BUFFER
    _anjay_log(anjay, TRACE, "AVS_COMMONS_LOG_USE_GLOBAL_BUFFER = ON");
#else // AVS_COMMONS_LOG_USE_GLOBAL_BUFFER
    _anjay_log(anjay, TRACE, "AVS_COMMONS_LOG_USE_GLOBAL_BUFFER = OFF");
#endif // AVS_COMMONS_LOG_USE_GLOBAL_BUFFER
#ifdef AVS_COMMONS_LOG_WITH_DEFAULT_HANDLER
    _anjay_log(anjay, TRACE, "AVS_COMMONS_LOG_WITH_DEFAULT_HANDLER = ON");
#else // AVS_COMMONS_LOG_WITH_DEFAULT_HANDLER
    _anjay_log(anjay, TRACE, "AVS_COMMONS_LOG_WITH_DEFAULT_HANDLER = OFF");
#endif // AVS_COMMONS_LOG_WITH_DEFAULT_HANDLER
#ifdef AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GAI_STRERROR
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GAI_STRERROR = ON");
#else // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GAI_STRERROR
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GAI_STRERROR = OFF");
#endif // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GAI_STRERROR
#ifdef AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GETIFADDRS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GETIFADDRS = ON");
#else // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GETIFADDRS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GETIFADDRS = OFF");
#endif // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GETIFADDRS
#ifdef AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GETNAMEINFO
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GETNAMEINFO = ON");
#else // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GETNAMEINFO
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GETNAMEINFO = OFF");
#endif // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_GETNAMEINFO
#ifdef AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_IN6_IS_ADDR_V4MAPPED
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_IN6_IS_ADDR_V4MAPPED = ON");
#else // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_IN6_IS_ADDR_V4MAPPED
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_IN6_IS_ADDR_V4MAPPED = OFF");
#endif // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_IN6_IS_ADDR_V4MAPPED
#ifdef AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_INET_NTOP
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_INET_NTOP = ON");
#else // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_INET_NTOP
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_INET_NTOP = OFF");
#endif // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_INET_NTOP
#ifdef AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_POLL
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_POLL = ON");
#else // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_POLL
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_POLL = OFF");
#endif // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_POLL
#ifdef AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_RECVMSG
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_RECVMSG = ON");
#else // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_RECVMSG
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_RECVMSG = OFF");
#endif // AVS_COMMONS_NET_POSIX_AVS_SOCKET_HAVE_RECVMSG
#ifdef AVS_COMMONS_NET_WITH_DTLS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_DTLS = ON");
#else // AVS_COMMONS_NET_WITH_DTLS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_DTLS = OFF");
#endif // AVS_COMMONS_NET_WITH_DTLS
#ifdef AVS_COMMONS_NET_WITH_IPV4
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_IPV4 = ON");
#else // AVS_COMMONS_NET_WITH_IPV4
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_IPV4 = OFF");
#endif // AVS_COMMONS_NET_WITH_IPV4
#ifdef AVS_COMMONS_NET_WITH_IPV6
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_IPV6 = ON");
#else // AVS_COMMONS_NET_WITH_IPV6
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_IPV6 = OFF");
#endif // AVS_COMMONS_NET_WITH_IPV6
#ifdef AVS_COMMONS_NET_WITH_MBEDTLS_LOGS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_MBEDTLS_LOGS = ON");
#else // AVS_COMMONS_NET_WITH_MBEDTLS_LOGS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_MBEDTLS_LOGS = OFF");
#endif // AVS_COMMONS_NET_WITH_MBEDTLS_LOGS
#ifdef AVS_COMMONS_NET_WITH_POSIX_AVS_SOCKET
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_POSIX_AVS_SOCKET = ON");
#else // AVS_COMMONS_NET_WITH_POSIX_AVS_SOCKET
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_POSIX_AVS_SOCKET = OFF");
#endif // AVS_COMMONS_NET_WITH_POSIX_AVS_SOCKET
#ifdef AVS_COMMONS_NET_WITH_PSK
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_PSK = ON");
#else // AVS_COMMONS_NET_WITH_PSK
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_PSK = OFF");
#endif // AVS_COMMONS_NET_WITH_PSK
#ifdef AVS_COMMONS_NET_WITH_SOCKET_LOG
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_SOCKET_LOG = ON");
#else // AVS_COMMONS_NET_WITH_SOCKET_LOG
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_SOCKET_LOG = OFF");
#endif // AVS_COMMONS_NET_WITH_SOCKET_LOG
#ifdef AVS_COMMONS_NET_WITH_TLS_SESSION_PERSISTENCE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_TLS_SESSION_PERSISTENCE = ON");
#else // AVS_COMMONS_NET_WITH_TLS_SESSION_PERSISTENCE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_NET_WITH_TLS_SESSION_PERSISTENCE = OFF");
#endif // AVS_COMMONS_NET_WITH_TLS_SESSION_PERSISTENCE
#ifdef AVS_COMMONS_POSIX_COMPAT_HEADER
    _anjay_log(anjay, TRACE, "AVS_COMMONS_POSIX_COMPAT_HEADER = ON");
#else // AVS_COMMONS_POSIX_COMPAT_HEADER
    _anjay_log(anjay, TRACE, "AVS_COMMONS_POSIX_COMPAT_HEADER = OFF");
#endif // AVS_COMMONS_POSIX_COMPAT_HEADER
#ifdef AVS_COMMONS_SCHED_THREAD_SAFE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_SCHED_THREAD_SAFE = ON");
#else // AVS_COMMONS_SCHED_THREAD_SAFE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_SCHED_THREAD_SAFE = OFF");
#endif // AVS_COMMONS_SCHED_THREAD_SAFE
#ifdef AVS_COMMONS_STREAM_WITH_FILE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_STREAM_WITH_FILE = ON");
#else // AVS_COMMONS_STREAM_WITH_FILE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_STREAM_WITH_FILE = OFF");
#endif // AVS_COMMONS_STREAM_WITH_FILE
#ifdef AVS_COMMONS_UNIT_POSIX_HAVE_BACKTRACE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_UNIT_POSIX_HAVE_BACKTRACE = ON");
#else // AVS_COMMONS_UNIT_POSIX_HAVE_BACKTRACE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_UNIT_POSIX_HAVE_BACKTRACE = OFF");
#endif // AVS_COMMONS_UNIT_POSIX_HAVE_BACKTRACE
#ifdef AVS_COMMONS_UTILS_WITH_POSIX_AVS_TIME
    _anjay_log(anjay, TRACE, "AVS_COMMONS_UTILS_WITH_POSIX_AVS_TIME = ON");
#else // AVS_COMMONS_UTILS_WITH_POSIX_AVS_TIME
    _anjay_log(anjay, TRACE, "AVS_COMMONS_UTILS_WITH_POSIX_AVS_TIME = OFF");
#endif // AVS_COMMONS_UTILS_WITH_POSIX_AVS_TIME
#ifdef AVS_COMMONS_UTILS_WITH_STANDARD_ALLOCATOR
    _anjay_log(anjay, TRACE, "AVS_COMMONS_UTILS_WITH_STANDARD_ALLOCATOR = ON");
#else // AVS_COMMONS_UTILS_WITH_STANDARD_ALLOCATOR
    _anjay_log(anjay, TRACE, "AVS_COMMONS_UTILS_WITH_STANDARD_ALLOCATOR = OFF");
#endif // AVS_COMMONS_UTILS_WITH_STANDARD_ALLOCATOR
#ifdef AVS_COMMONS_WITHOUT_64BIT_FORMAT_SPECIFIERS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITHOUT_64BIT_FORMAT_SPECIFIERS = ON");
#else // AVS_COMMONS_WITHOUT_64BIT_FORMAT_SPECIFIERS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITHOUT_64BIT_FORMAT_SPECIFIERS = OFF");
#endif // AVS_COMMONS_WITHOUT_64BIT_FORMAT_SPECIFIERS
#ifdef AVS_COMMONS_WITHOUT_FLOAT_FORMAT_SPECIFIERS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITHOUT_FLOAT_FORMAT_SPECIFIERS = ON");
#else // AVS_COMMONS_WITHOUT_FLOAT_FORMAT_SPECIFIERS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITHOUT_FLOAT_FORMAT_SPECIFIERS = OFF");
#endif // AVS_COMMONS_WITHOUT_FLOAT_FORMAT_SPECIFIERS
#ifdef AVS_COMMONS_WITH_AVS_ALGORITHM
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_ALGORITHM = ON");
#else // AVS_COMMONS_WITH_AVS_ALGORITHM
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_ALGORITHM = OFF");
#endif // AVS_COMMONS_WITH_AVS_ALGORITHM
#ifdef AVS_COMMONS_WITH_AVS_BUFFER
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_BUFFER = ON");
#else // AVS_COMMONS_WITH_AVS_BUFFER
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_BUFFER = OFF");
#endif // AVS_COMMONS_WITH_AVS_BUFFER
#ifdef AVS_COMMONS_WITH_AVS_COMPAT_THREADING
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_COMPAT_THREADING = ON");
#else // AVS_COMMONS_WITH_AVS_COMPAT_THREADING
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_COMPAT_THREADING = OFF");
#endif // AVS_COMMONS_WITH_AVS_COMPAT_THREADING
#ifdef AVS_COMMONS_WITH_AVS_CRYPTO
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_CRYPTO = ON");
#else // AVS_COMMONS_WITH_AVS_CRYPTO
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_CRYPTO = OFF");
#endif // AVS_COMMONS_WITH_AVS_CRYPTO
#ifdef AVS_COMMONS_WITH_AVS_CRYPTO_ADVANCED_FEATURES
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_CRYPTO_ADVANCED_FEATURES = ON");
#else // AVS_COMMONS_WITH_AVS_CRYPTO_ADVANCED_FEATURES
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_CRYPTO_ADVANCED_FEATURES = OFF");
#endif // AVS_COMMONS_WITH_AVS_CRYPTO_ADVANCED_FEATURES
#ifdef AVS_COMMONS_WITH_AVS_CRYPTO_ENGINE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_CRYPTO_ENGINE = ON");
#else // AVS_COMMONS_WITH_AVS_CRYPTO_ENGINE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_CRYPTO_ENGINE = OFF");
#endif // AVS_COMMONS_WITH_AVS_CRYPTO_ENGINE
#ifdef AVS_COMMONS_WITH_AVS_CRYPTO_PKI
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_CRYPTO_PKI = ON");
#else // AVS_COMMONS_WITH_AVS_CRYPTO_PKI
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_CRYPTO_PKI = OFF");
#endif // AVS_COMMONS_WITH_AVS_CRYPTO_PKI
#ifdef AVS_COMMONS_WITH_AVS_CRYPTO_VALGRIND
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_CRYPTO_VALGRIND = ON");
#else // AVS_COMMONS_WITH_AVS_CRYPTO_VALGRIND
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_CRYPTO_VALGRIND = OFF");
#endif // AVS_COMMONS_WITH_AVS_CRYPTO_VALGRIND
#ifdef AVS_COMMONS_WITH_AVS_HTTP
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_HTTP = ON");
#else // AVS_COMMONS_WITH_AVS_HTTP
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_HTTP = OFF");
#endif // AVS_COMMONS_WITH_AVS_HTTP
#ifdef AVS_COMMONS_WITH_AVS_LIST
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_LIST = ON");
#else // AVS_COMMONS_WITH_AVS_LIST
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_LIST = OFF");
#endif // AVS_COMMONS_WITH_AVS_LIST
#ifdef AVS_COMMONS_WITH_AVS_LOG
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_LOG = ON");
#else // AVS_COMMONS_WITH_AVS_LOG
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_LOG = OFF");
#endif // AVS_COMMONS_WITH_AVS_LOG
#ifdef AVS_COMMONS_WITH_AVS_NET
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_NET = ON");
#else // AVS_COMMONS_WITH_AVS_NET
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_NET = OFF");
#endif // AVS_COMMONS_WITH_AVS_NET
#ifdef AVS_COMMONS_WITH_AVS_PERSISTENCE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_PERSISTENCE = ON");
#else // AVS_COMMONS_WITH_AVS_PERSISTENCE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_PERSISTENCE = OFF");
#endif // AVS_COMMONS_WITH_AVS_PERSISTENCE
#ifdef AVS_COMMONS_WITH_AVS_RBTREE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_RBTREE = ON");
#else // AVS_COMMONS_WITH_AVS_RBTREE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_RBTREE = OFF");
#endif // AVS_COMMONS_WITH_AVS_RBTREE
#ifdef AVS_COMMONS_WITH_AVS_SCHED
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_SCHED = ON");
#else // AVS_COMMONS_WITH_AVS_SCHED
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_SCHED = OFF");
#endif // AVS_COMMONS_WITH_AVS_SCHED
#ifdef AVS_COMMONS_WITH_AVS_STREAM
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_STREAM = ON");
#else // AVS_COMMONS_WITH_AVS_STREAM
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_STREAM = OFF");
#endif // AVS_COMMONS_WITH_AVS_STREAM
#ifdef AVS_COMMONS_WITH_AVS_UNIT
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_UNIT = ON");
#else // AVS_COMMONS_WITH_AVS_UNIT
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_UNIT = OFF");
#endif // AVS_COMMONS_WITH_AVS_UNIT
#ifdef AVS_COMMONS_WITH_AVS_URL
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_URL = ON");
#else // AVS_COMMONS_WITH_AVS_URL
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_URL = OFF");
#endif // AVS_COMMONS_WITH_AVS_URL
#ifdef AVS_COMMONS_WITH_AVS_UTILS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_UTILS = ON");
#else // AVS_COMMONS_WITH_AVS_UTILS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_UTILS = OFF");
#endif // AVS_COMMONS_WITH_AVS_UTILS
#ifdef AVS_COMMONS_WITH_AVS_VECTOR
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_VECTOR = ON");
#else // AVS_COMMONS_WITH_AVS_VECTOR
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_AVS_VECTOR = OFF");
#endif // AVS_COMMONS_WITH_AVS_VECTOR
#ifdef AVS_COMMONS_WITH_CUSTOM_TLS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_CUSTOM_TLS = ON");
#else // AVS_COMMONS_WITH_CUSTOM_TLS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_CUSTOM_TLS = OFF");
#endif // AVS_COMMONS_WITH_CUSTOM_TLS
#ifdef AVS_COMMONS_WITH_EXTERNAL_LOGGER_HEADER
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_EXTERNAL_LOGGER_HEADER = ON");
#else // AVS_COMMONS_WITH_EXTERNAL_LOGGER_HEADER
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_EXTERNAL_LOGGER_HEADER = OFF");
#endif // AVS_COMMONS_WITH_EXTERNAL_LOGGER_HEADER
#ifdef AVS_COMMONS_WITH_INTERNAL_LOGS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_INTERNAL_LOGS = ON");
#else // AVS_COMMONS_WITH_INTERNAL_LOGS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_INTERNAL_LOGS = OFF");
#endif // AVS_COMMONS_WITH_INTERNAL_LOGS
#ifdef AVS_COMMONS_WITH_INTERNAL_TRACE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_INTERNAL_TRACE = ON");
#else // AVS_COMMONS_WITH_INTERNAL_TRACE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_INTERNAL_TRACE = OFF");
#endif // AVS_COMMONS_WITH_INTERNAL_TRACE
#ifdef AVS_COMMONS_WITH_MBEDTLS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_MBEDTLS = ON");
#else // AVS_COMMONS_WITH_MBEDTLS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_MBEDTLS = OFF");
#endif // AVS_COMMONS_WITH_MBEDTLS
#ifdef AVS_COMMONS_WITH_MBEDTLS_PKCS11_ENGINE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_MBEDTLS_PKCS11_ENGINE = ON");
#else // AVS_COMMONS_WITH_MBEDTLS_PKCS11_ENGINE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_MBEDTLS_PKCS11_ENGINE = OFF");
#endif // AVS_COMMONS_WITH_MBEDTLS_PKCS11_ENGINE
#ifdef AVS_COMMONS_WITH_MBEDTLS_PSA_ENGINE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_MBEDTLS_PSA_ENGINE = ON");
#else // AVS_COMMONS_WITH_MBEDTLS_PSA_ENGINE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_MBEDTLS_PSA_ENGINE = OFF");
#endif // AVS_COMMONS_WITH_MBEDTLS_PSA_ENGINE
#ifdef AVS_COMMONS_WITH_MBEDTLS_PSA_ENGINE_PROTECTED_STORAGE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_MBEDTLS_PSA_ENGINE_PROTECTED_STORAGE = ON");
#else // AVS_COMMONS_WITH_MBEDTLS_PSA_ENGINE_PROTECTED_STORAGE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_MBEDTLS_PSA_ENGINE_PROTECTED_STORAGE = OFF");
#endif // AVS_COMMONS_WITH_MBEDTLS_PSA_ENGINE_PROTECTED_STORAGE
#ifdef AVS_COMMONS_WITH_MICRO_LOGS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_MICRO_LOGS = ON");
#else // AVS_COMMONS_WITH_MICRO_LOGS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_MICRO_LOGS = OFF");
#endif // AVS_COMMONS_WITH_MICRO_LOGS
#ifdef AVS_COMMONS_WITH_OPENSSL
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_OPENSSL = ON");
#else // AVS_COMMONS_WITH_OPENSSL
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_OPENSSL = OFF");
#endif // AVS_COMMONS_WITH_OPENSSL
#ifdef AVS_COMMONS_WITH_OPENSSL_PKCS11_ENGINE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_OPENSSL_PKCS11_ENGINE = ON");
#else // AVS_COMMONS_WITH_OPENSSL_PKCS11_ENGINE
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_OPENSSL_PKCS11_ENGINE = OFF");
#endif // AVS_COMMONS_WITH_OPENSSL_PKCS11_ENGINE
#ifdef AVS_COMMONS_WITH_POISONING
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_POISONING = ON");
#else // AVS_COMMONS_WITH_POISONING
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_POISONING = OFF");
#endif // AVS_COMMONS_WITH_POISONING
#ifdef AVS_COMMONS_WITH_TINYDTLS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_TINYDTLS = ON");
#else // AVS_COMMONS_WITH_TINYDTLS
    _anjay_log(anjay, TRACE, "AVS_COMMONS_WITH_TINYDTLS = OFF");
#endif // AVS_COMMONS_WITH_TINYDTLS
#ifdef WITH_AVS_COAP_BLOCK
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_BLOCK = ON");
#else // WITH_AVS_COAP_BLOCK
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_BLOCK = OFF");
#endif // WITH_AVS_COAP_BLOCK
#ifdef WITH_AVS_COAP_DIAGNOSTIC_MESSAGES
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_DIAGNOSTIC_MESSAGES = ON");
#else // WITH_AVS_COAP_DIAGNOSTIC_MESSAGES
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_DIAGNOSTIC_MESSAGES = OFF");
#endif // WITH_AVS_COAP_DIAGNOSTIC_MESSAGES
#ifdef WITH_AVS_COAP_LOGS
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_LOGS = ON");
#else // WITH_AVS_COAP_LOGS
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_LOGS = OFF");
#endif // WITH_AVS_COAP_LOGS
#ifdef WITH_AVS_COAP_OBSERVE
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_OBSERVE = ON");
#else // WITH_AVS_COAP_OBSERVE
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_OBSERVE = OFF");
#endif // WITH_AVS_COAP_OBSERVE
#ifdef WITH_AVS_COAP_OBSERVE_PERSISTENCE
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_OBSERVE_PERSISTENCE = ON");
#else // WITH_AVS_COAP_OBSERVE_PERSISTENCE
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_OBSERVE_PERSISTENCE = OFF");
#endif // WITH_AVS_COAP_OBSERVE_PERSISTENCE
#ifdef WITH_AVS_COAP_OSCORE
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_OSCORE = ON");
#else // WITH_AVS_COAP_OSCORE
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_OSCORE = OFF");
#endif // WITH_AVS_COAP_OSCORE
#ifdef WITH_AVS_COAP_OSCORE_DRAFT_8
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_OSCORE_DRAFT_8 = ON");
#else // WITH_AVS_COAP_OSCORE_DRAFT_8
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_OSCORE_DRAFT_8 = OFF");
#endif // WITH_AVS_COAP_OSCORE_DRAFT_8
#ifdef WITH_AVS_COAP_POISONING
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_POISONING = ON");
#else // WITH_AVS_COAP_POISONING
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_POISONING = OFF");
#endif // WITH_AVS_COAP_POISONING
#ifdef WITH_AVS_COAP_STREAMING_API
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_STREAMING_API = ON");
#else // WITH_AVS_COAP_STREAMING_API
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_STREAMING_API = OFF");
#endif // WITH_AVS_COAP_STREAMING_API
#ifdef WITH_AVS_COAP_TCP
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_TCP = ON");
#else // WITH_AVS_COAP_TCP
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_TCP = OFF");
#endif // WITH_AVS_COAP_TCP
#ifdef WITH_AVS_COAP_TRACE_LOGS
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_TRACE_LOGS = ON");
#else // WITH_AVS_COAP_TRACE_LOGS
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_TRACE_LOGS = OFF");
#endif // WITH_AVS_COAP_TRACE_LOGS
#ifdef WITH_AVS_COAP_UDP
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_UDP = ON");
#else // WITH_AVS_COAP_UDP
    _anjay_log(anjay, TRACE, "WITH_AVS_COAP_UDP = OFF");
#endif // WITH_AVS_COAP_UDP
}
// clang-format on

VISIBILITY_PRIVATE_HEADER_END

#endif /* ANJAY_CONFIG_LOG_H */
