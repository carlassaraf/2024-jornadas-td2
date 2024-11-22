#ifndef _COMMON_H_
#define _COMMON_H_

#include "pico/util/queue.h"

// GPIO del LED de la placa
#define LED 25
// Mascara para interrupcion de Timer
#define TIMER_IRQ_MASK  (1 << TIMER_IRQ_0 | 1 << TIMER_IRQ_1 | 1 << TIMER_IRQ_2 | 1 << TIMER_IRQ_3)

/**
 * Estructura para mandar datos del ADC
 */
typedef struct sensor {
    uint16_t raw;
    float voltage;
    float temperature;
} sensor_data_t;

// Cola para datos entre cores
extern queue_t queue;

// Prototipos
int core_0(void);
void core_1(void);

#endif