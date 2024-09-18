/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "hello_freertos.h"

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

#include "hello_freertos.h"

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void blink_task(__unused void *params) {
    hard_assert(cyw43_arch_init() == PICO_OK);

    int count = 0;
    bool on = false;

    while (true) {
        blink(&on, &count);
        vTaskDelay(500); // Don't need to unit test the delay
    }
}

void blink(bool *on, int *count) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, *on);
    if ((*count)++ % 11) {
        *on = !(*on);
    }
}

void main_task(__unused void *params) {
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    char c;
    while(c = getchar()) {
        putchar(toggle_char(c));
    }
}

char toggle_char(char c) {
    char toggledChar;
    if (c <= 'z' && c >= 'a') toggledChar = c - 32;
    else if (c >= 'A' && c <= 'Z') toggledChar = c + 32;
    else toggledChar = c;
    return toggledChar;
}

int main( void )
{
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    vTaskStartScheduler();
    return 0;
}
