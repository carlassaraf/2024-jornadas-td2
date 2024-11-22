#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"

#include "common.h"

/**
 * @brief Programa principal del core_1
 */
void core_1(void) {

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