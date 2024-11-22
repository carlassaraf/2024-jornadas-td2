#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "common.h"

/**
 * @brief Programa principal del core_0
 */
int core_0(void){
    // Inicializacion de USB
    stdio_init_all();
    sleep_ms(1000);
    // Arranca el core 1
    multicore_launch_core1(core_1);

    while(true) {
        // Mensaje y mando
        uint32_t core_num = get_core_num();
        printf("core %d: Hola desde el core %d\n", core_num, core_num);
        sleep_ms(500);
    }

    return 0;
}
