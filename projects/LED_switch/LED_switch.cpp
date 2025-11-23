#include "pico/stdlib.h"

#define BLUE_PIN   2
#define GREEN_PIN  5
#define RED_PIN    28
#define BUTTON_PIN 10

void always_on(uint pin, uint32_t elapsed_ms) {
    (void)elapsed_ms;
    gpio_put(pin, 1);
}

void blink_half_second(uint pin, uint32_t elapsed_ms) {
    uint32_t phase = elapsed_ms % 1000;
    gpio_put(pin, (phase < 250));
}

void flash_1s_every_5s(uint pin, uint32_t elapsed_ms) {
    uint32_t phase = elapsed_ms % 2500;
    gpio_put(pin, (phase < 1250));
}

typedef void (*PatternFunc)(uint pin, uint32_t elapsed_ms);

int main() {
    stdio_init_all();

    gpio_init(BLUE_PIN);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);

    gpio_init(GREEN_PIN);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);

    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    const uint led_pins[3] = { BLUE_PIN, GREEN_PIN, RED_PIN };

    PatternFunc patterns[3] = {
        always_on,
        blink_half_second,
        flash_1s_every_5s
    };

    int pattern_idx_for_led[3] = { 0, 1, 2 };

    uint32_t elapsed_ms = 0;

    bool last_button_state = true;

    while (true) {
        bool button_state = gpio_get(BUTTON_PIN);

        if (!button_state && last_button_state) {

            int temp = pattern_idx_for_led[0];
            pattern_idx_for_led[0] = pattern_idx_for_led[1];
            pattern_idx_for_led[1] = pattern_idx_for_led[2];
            pattern_idx_for_led[2] = temp;

            sleep_ms(200);
        }

        last_button_state = button_state;

        for (int i = 0; i < 3; i++) {
            int pat_index = pattern_idx_for_led[i];
            PatternFunc f = patterns[pat_index];
            f(led_pins[i], elapsed_ms);
        }

        sleep_ms(50);
        elapsed_ms += 50;
    }
}
