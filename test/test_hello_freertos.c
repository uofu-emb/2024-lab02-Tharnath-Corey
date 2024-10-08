#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "pico/cyw43_arch.h"
#include "lab2.h"

void setUp(void)
{
}

void tearDown(void) {}

void test_blink_regular(void)
{
    bool on = false;
    int count = 1;

    blink(&on, &count);

    TEST_ASSERT_FALSE_MESSAGE(cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN), "LED was not set properly");
    TEST_ASSERT_TRUE_MESSAGE(on, "On value did not toggle");
    TEST_ASSERT_TRUE_MESSAGE(count == 2, "Count did not increment properly.");
}

void test_blink_skipped(void)
{
    bool on = true;
    int count = 11;

    blink(&on, &count);

    TEST_ASSERT_TRUE_MESSAGE(cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN), "LED was not set properly");
    TEST_ASSERT_TRUE_MESSAGE(on, "On value toggled when it should have been skipped");
    TEST_ASSERT_TRUE_MESSAGE(count == 12, "Count did not increment properly.");
}

void test_toggle_char(void)
{
    TEST_ASSERT_TRUE_MESSAGE(toggle_char('A') == 'a', "Invalid output while toggling to lowercase.");
    TEST_ASSERT_TRUE_MESSAGE(toggle_char('x') == 'X', "Invalid output while toggling to uppercase.");
    TEST_ASSERT_TRUE_MESSAGE(toggle_char('*') == '*', "Invalid output for special character.");
}

int main(void)
{
    stdio_init_all();
    sleep_ms(5000); // Give time for TTY to attach.
    hard_assert(cyw43_arch_init() == PICO_OK); // Init should only occur once
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_blink_regular);
    RUN_TEST(test_blink_skipped);
    RUN_TEST(test_toggle_char);
    sleep_ms(5000);
    return UNITY_END();
}
