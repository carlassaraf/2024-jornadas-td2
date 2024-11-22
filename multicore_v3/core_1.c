#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"

#include "common.h"

/**
 * @brief Callback para el Timer
 */
bool timer_cb(repeating_timer_t *t) {
    // Muestra cuantos us pasaron desde que booteo el microcontrolador
    uint64_t time = time_us_64();
    printf("core %d: Pasaron %.2f ms desde el boot\r\n", get_core_num(), (float)(time / 1000.0));
    return true;
}

/**
 * @brief Programa principal del core 1
 */
void core_1(void) {
    // Configuro Timer e interrupcion en este core
    repeating_timer_t timer;
    add_repeating_timer_ms(1000, timer_cb, NULL, &timer);
    irq_set_mask_enabled(TIMER_IRQ_MASK, true);

    while(1) {
        // Datos para leer del otro core
        sensor_data_t data;
        // Espero a poder leer de la cola
        queue_remove_blocking(&queue, &data);
        // Muestra datos de la cola por consola
        printf("core %d: Raw value: 0x%03x\r\n", get_core_num(), data.raw);
        printf("core %d: Voltage value: %.2f\r\n", get_core_num(), data.voltage);
        printf("core %d: Temperature vlaue: %.2f\r\n\n", get_core_num(), data.temperature);
    }
}