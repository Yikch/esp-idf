/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * OpenThread Radio Co-Processor (RCP) Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#pragma once

#include "esp_openthread_types.h"
#define ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG()                   \
    {                                                           \
        .radio_mode = RADIO_MODE_NATIVE,                        \
    }

#if CONFIG_OPENTHREAD_UART_PIN_MANUAL
#define OPENTHREAD_RCP_UART_RX_PIN CONFIG_OPENTHREAD_UART_RX_PIN
#define OPENTHREAD_RCP_UART_TX_PIN CONFIG_OPENTHREAD_UART_TX_PIN
#else
#define OPENTHREAD_RCP_UART_RX_PIN UART_PIN_NO_CHANGE
#define OPENTHREAD_RCP_UART_TX_PIN UART_PIN_NO_CHANGE
#endif

#define ESP_OPENTHREAD_DEFAULT_HOST_CONFIG()                    \
    {                                                           \
        .host_connection_mode = HOST_CONNECTION_MODE_RCP_UART,  \
        .host_uart_config = {                                   \
            .port = 0,                                          \
            .uart_config =                                      \
                {                                               \
                    .baud_rate =  115200,                       \
                    .data_bits = UART_DATA_8_BITS,              \
                    .parity = UART_PARITY_DISABLE,              \
                    .stop_bits = UART_STOP_BITS_1,              \
                    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,      \
                    .rx_flow_ctrl_thresh = 0,                   \
                    .source_clk = UART_SCLK_DEFAULT,            \
                },                                              \
            .rx_pin = OPENTHREAD_RCP_UART_RX_PIN,               \
            .tx_pin = OPENTHREAD_RCP_UART_TX_PIN,               \
        },                                                      \
    }

#define ESP_OPENTHREAD_DEFAULT_PORT_CONFIG()    \
    {                                           \
        .storage_partition_name = "ot_storage", \
        .netif_queue_size = 10,                 \
        .task_queue_size = 10,                  \
    }
