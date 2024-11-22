#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"
#include "hardware/adc.h"

#include "FreeRTOS.h"
#include "task.h"

#include "common.h"

/**
 * @brief Tarea de inicializacion
 */
void task_init(void *params) {
    // Inicializacion de USB
    stdio_init_all();
    sleep_ms(1000);
    // Inicializacion del ADC para el sensor interno de temperatura
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
    // Inicializacion de GPIO para el LED
    gpio_init(LED);
    gpio_set_dir(LED, true);
    gpio_put(LED, false);
    // Arranca el core 1
    multicore_launch_core1(core_1);
    // Deshabilito interrupcion de Timer en este core
    irq_set_mask_enabled(TIMER_IRQ_MASK, false);

    vTaskDelete(NULL);
}

/**
 * @brief Tarea que hace parpadear el LED
 */
void task_blink(void *params) {

    while(1) {
        gpio_put(LED, !gpio_get(LED));
        vTaskDelay(500);
    }
}

/**
 * @brief Tarea que lee el sensor de temperatura y manda al otro core
 */
void task_adc(void *params) {

    while(1) {
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
        vTaskDelay(1000);
    }
}

/**
 * @brief Programa principal del core 0
 */
int core_0(void) {

    // Inicializacion de cola para multicore
    queue_init(&queue, sizeof(sensor_data_t), 1);

    // Creacion de tareas

    xTaskCreate(
        task_init,
        "Init",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 2UL,
        NULL
    );

    xTaskCreate(
        task_blink,
        "Blinky",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 1UL,
        NULL
    );

    xTaskCreate(
        task_adc,
        "ADC",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 1UL,
        NULL
    );

    // Arranca el RTOS
    vTaskStartScheduler();
}