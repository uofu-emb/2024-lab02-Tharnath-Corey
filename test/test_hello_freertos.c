#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "pico/cyw43_arch.h"
#include "hello_freertos.h"

void setUp(void) {}

void tearDown(void) {}

void test_blink_regular(void) {
    bool on = false;
    int count = 0;

    blink(&on, &count);

    TEST_ASSERT_FALSE_MESSAGE(cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN), "LED was not set properly");
    TEST_ASSERT_TRUE_MESSAGE(on, "On value did not toggle");
    TEST_ASSERT_TRUE_MESSAGE(count == 1, "Count did not increment properly.");
}

void test_blink_skipped(void) {
    bool on = true;
    int count = 10;

    blink(&on, &count);

    TEST_ASSERT_TRUE_MESSAGE(cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN), "LED was not set properly");
    TEST_ASSERT_TRUE_MESSAGE(on, "On value toggled when it should have been skipped");
    TEST_ASSERT_TRUE_MESSAGE(count == 11, "Count did not increment properly.");
}

int main (void)
{
    stdio_init_all();
    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_blink_regular);
    RUN_TEST(test_blink_skipped);
    sleep_ms(5000);
    return UNITY_END();
}
