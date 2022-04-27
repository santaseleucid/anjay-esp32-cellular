#ifndef _MAIN_H
#define _MAIN_H
#include <stdio.h>
#include <stdint.h>
#include "string.h"
#include <stdlib.h>
#include <sys/time.h>
#include <sys/unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#include "modem.h"
#include "tls_transport.h"

#define CELLULAR
#define CELLULAR_APN "m2minternet.apn"

#endif