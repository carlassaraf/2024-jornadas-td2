#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "common.h"

/**
 * @brief Programa principal del core_1
 */
void core_1(void) {

    while(1) {
        // Muestra datos de la cola por consola
        uint32_t core_num = get_core_num();
        printf("core %d: Hola desde core %d\n", core_num, core_num);
        sleep_ms(750);
    }
}