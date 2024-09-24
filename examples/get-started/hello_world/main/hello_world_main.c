/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

void vATaskFunction( void *pvParameters )
{
    while(1){
        printf("Llamada desde task A: reinicio en %d msegundos...\n", CONFIG_TASKA_PERIOD);
        vTaskDelay(CONFIG_TASKA_PERIOD / portTICK_PERIOD_MS);
        printf("Llamada desde task A: reiniciando...\n");
    }
}


void vBTaskFunction( void *pvParameters )
{
    while(1){
        printf("Llamada desde task B: reinicio en %d msegundos...\n", CONFIG_TASKB_PERIOD);
        vTaskDelay(CONFIG_TASKB_PERIOD / portTICK_PERIOD_MS);
        printf("Llamada desde task B: reiniciando...\n");
    }
}

void app_main(void)
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    printf("Chip has 2.4GHz WiFi: %s\n", CHIP_FEATURE_WIFI_BGN ? "true" : "false");

    xTaskCreate( vATaskFunction, "taskA", 2048, NULL, 5, NULL );

    xTaskCreate( vBTaskFunction, "taskB", 2048, NULL, 5, NULL );


    // for (int i = 10; i > 0; i-=2) {
    //     printf("Restarting in %d seconds...\n", i);
    //     vTaskDelay(2000 / portTICK_PERIOD_MS);
    // }
    // printf("Restarting now.\n");
    // fflush(stdout);
    // esp_restart();
}