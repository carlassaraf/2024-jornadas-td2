#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"
#include "hardware/adc.h"

#include "common.h"

/**
 * @brief Programa principal del core_0
 */
int core_0(void){
    // Inicializacion de USB
    stdio_init_all();
    sleep_ms(1000);
    // Inicializacion del ADC para el sensor interno de temperatura
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
    // Inicializacion de cola para multicore
    queue_init(&queue, sizeof(sensor_data_t), 1);
    // Arranca el core 1
    multicore_launch_core1(core_1);

    while(true) {
        // Lectura de ADC y conversion a voltaje y temperatura
        uint16_t raw = adc_read();
        float voltage = raw * 3.3 / (1 << 12);
        float temperature = 27 - (voltage - 0.706) / 0.001721;
        // Estructura para mandar al otro core
        sensor_data_t data = { 
            .raw = raw,
            .voltage = voltage,
            .temperature = temperature
        };
        // Mensaje y mando
        printf("core %d: Lectura lista, enviando al otro core\n", get_core_num());
        queue_add_blocking(&queue, &data);
        sleep_ms(500);
    }

    return 0;
}
