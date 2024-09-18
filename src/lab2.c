#include "lab2.h"
#include "pico/cyw43_arch.h"

char toggle_char(char c) {
    char toggledChar;
    if (c <= 'z' && c >= 'a') toggledChar = c - 32;
    else if (c >= 'A' && c <= 'Z') toggledChar = c + 32;
    else toggledChar = c;
    return toggledChar;
}

void blink(bool *on, int *count) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, *on);
    if ((*count)++ % 11) {
        *on = !(*on);
    }
}