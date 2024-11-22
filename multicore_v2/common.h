#ifndef _COMMON_H_
#define _COMMON_H_

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