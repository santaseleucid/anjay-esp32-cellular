#include "./firmware_update.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <esp_https_ota.h>
#include <esp_log.h>
#include <esp_ota_ops.h>
#include <sys/param.h>
#include "nvs_flash.h"
#include "nvs.h"

static const char *TAG = "ESP_OTA";
// static struct fw_state_t
// {
//     FILE *firmware_file;
// } FW_STATE;
typedef enum
{
    ESP_OTA_INIT,
    ESP_OTA_BEGIN,
    ESP_OTA_IN_PROGRESS,
    ESP_OTA_SUCCESS,
} esp_ota_state;

struct esp_ota_anjay_handle
{
    esp_ota_handle_t update_handle;
    const esp_partition_t *update_partition;
    // esp_http_client_handle_t http_client;
    char *ota_upgrade_buf;
    size_t ota_upgrade_buf_size;
    int binary_file_len;
    esp_ota_state state;
    bool bulk_flash_erase;
};

typedef struct esp_ota_anjay_handle ota_handle_t;

static const char *FW_IMAGE_DOWNLOAD_NAME = "/tmp/firmware_image.bin";
ota_handle_t *ota_handle;

static int fw_stream_open(void *user_ptr,
                          const char *package_uri,
                          const struct anjay_etag *package_etag)
{
    printf("fw_stream_open\n");
    ota_handle = calloc(1, sizeof(ota_handle_t));
    if (!ota_handle)
    {
        ESP_LOGE(TAG, "Couldn't allocate memory to upgrade data buffer");

        return ESP_ERR_NO_MEM;
    }
    ota_handle->update_partition = NULL;
    ESP_LOGI(TAG, "Starting OTA...");
    ota_handle->update_partition = esp_ota_get_next_update_partition(NULL);
    if (!ota_handle->update_partition)
    {
        ESP_LOGE(TAG, "Update Partition is Null");
    }
    else
    {
        ESP_LOGI(TAG, "Writing to partition subtype %d at offset 0x%x", ota_handle->update_partition->subtype, ota_handle->update_partition->address);
    }

    ota_handle->state = ESP_OTA_BEGIN;
    esp_err_t err;
    err = esp_ota_begin(ota_handle->update_partition, OTA_SIZE_UNKNOWN, &ota_handle->update_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "esp_ota_begin failed (%s)", esp_err_to_name(err));
        return err;
    }
    ota_handle->state = ESP_OTA_IN_PROGRESS;
    // // For a moment, we don't need to care about any of the arguments passed.
    // (void)user_ptr;
    // (void)package_uri;
    // (void)package_etag;

    // // It's worth ensuring we start with a NULL firmware_file. In the end
    // // it would be our responsibility to manage this pointer, and we want
    // // to make sure we never leak any memory.
    // assert(FW_STATE.firmware_file == NULL);
    // // We're about to create a firmware file for writing
    // FW_STATE.firmware_file = fopen(FW_IMAGE_DOWNLOAD_NAME, "wb");
    // if (!FW_STATE.firmware_file)
    // {
    //     fprintf(stderr, "Could not open %s\n", FW_IMAGE_DOWNLOAD_NAME);
    //     return -1;
    // }
    // // We've succeeded
    return 0;
}

static int fw_stream_write(void *user_ptr, const void *data, size_t length)
{
    printf("fw_stream_write\n");
    ESP_LOGI(TAG, "Got data of length %zu", length);
    esp_err_t err = esp_ota_write(ota_handle->update_handle, data, length);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Error: esp_ota_write failed! err=0x%x", err);
    }
    else
    {
        ota_handle->binary_file_len += length;
        ESP_LOGI(TAG, "Written image length %d", ota_handle->binary_file_len);
        err = ESP_ERR_HTTPS_OTA_IN_PROGRESS;
    }
    // (void)user_ptr;
    // // We only need to write to file and check if that succeeded
    // if (fwrite(data, length, 1, FW_STATE.firmware_file) != 1)
    // {
    //     fprintf(stderr, "Writing to firmware image failed\n");
    //     return -1;
    // }
    return 0;
}

static int fw_stream_finish(void *user_ptr)
{
    printf("fw_stream_finish\n");
    esp_err_t err = esp_ota_end(ota_handle->update_handle);
    err = esp_ota_set_boot_partition(ota_handle->update_partition);
    // (void)user_ptr;
    // assert(FW_STATE.firmware_file != NULL);

    // if (fclose(FW_STATE.firmware_file))
    // {
    //     fprintf(stderr, "Closing firmware image failed\n");
    //     FW_STATE.firmware_file = NULL;
    //     return -1;
    // }
    // FW_STATE.firmware_file = NULL;
    return 0;
}

static void fw_reset(void *user_ptr)
{
    printf("fw_reset\n");
    // // Reset can be issued even if the download never started.
    // if (FW_STATE.firmware_file) {
    //     // We ignore the result code of fclose(), as fw_reset() can't fail.
    //     (void) fclose(FW_STATE.firmware_file);
    //     // and reset our global state to initial value.
    //     FW_STATE.firmware_file = NULL;
    // }
    // // Finally, let's remove any downloaded payload
    // unlink(FW_IMAGE_DOWNLOAD_NAME);
}

// A part of a rather simple logic checking if the firmware update was
// successfully performed.
static const char *FW_UPDATED_MARKER = "/tmp/fw-updated-marker";

static int fw_perform_upgrade(void *user_ptr)
{
    printf("fw_perform_upgrade\n");
    // Open
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    }
    else
    {
        err = nvs_set_i32(my_handle, "fw_updated", 1);
        printf("Committing updates in NVS ... ");
        err = nvs_commit(my_handle);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

        // Close
        nvs_close(my_handle);
    }
    esp_restart();
    // if (chmod(FW_IMAGE_DOWNLOAD_NAME, 0700) == -1)
    // {
    //     fprintf(stderr,
    //             "Could not make firmware executable: %s\n",
    //             strerror(errno));
    //     return -1;
    // }
    // // Create a marker file, so that the new process knows it is the "upgraded"
    // // one
    // FILE *marker = fopen(FW_UPDATED_MARKER, "w");
    // if (!marker)
    // {
    //     fprintf(stderr, "Marker file could not be created\n");
    //     return -1;
    // }
    // fclose(marker);

    // assert(ENDPOINT_NAME);
    // // If the call below succeeds, the firmware is considered as "upgraded",
    // // and we hope the newly started client registers to the Server.
    // (void)execl(FW_IMAGE_DOWNLOAD_NAME, FW_IMAGE_DOWNLOAD_NAME, ENDPOINT_NAME,
    //             NULL);
    // fprintf(stderr, "execl() failed: %s\n", strerror(errno));
    // // If we are here, it means execl() failed. Marker file MUST now be removed,
    // // as the firmware update failed.
    // unlink(FW_UPDATED_MARKER);
    return -1;
}

static const anjay_fw_update_handlers_t HANDLERS = {
    .stream_open = fw_stream_open,
    .stream_write = fw_stream_write,
    .stream_finish = fw_stream_finish,
    .reset = fw_reset,
    .perform_upgrade = fw_perform_upgrade

};

const char *ENDPOINT_NAME = NULL;

int fw_update_install(anjay_t *anjay)
{
    printf("fw_update_install\n");
    anjay_fw_update_initial_state_t state;
    memset(&state, 0, sizeof(state));
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
    int fw_updated = 0;
    if (err != ESP_OK)
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    }
    else
    {
        err = nvs_get_i32(my_handle, "fw_updated", &fw_updated);
        printf("Reading from NVS ... ");
        err = nvs_commit(my_handle);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        // Close
        nvs_close(my_handle);
    }
    if (fw_updated)
    {
        state.result = ANJAY_FW_UPDATE_INITIAL_SUCCESS;
        ESP_LOGI(TAG, "Firmware updated");
    }
    else
    {
        ESP_LOGI(TAG, "factory firmware. I.e., not updated");
    }
    return anjay_fw_update_install(anjay, &HANDLERS, NULL, &state);
}