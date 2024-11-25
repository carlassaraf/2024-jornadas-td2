# multicore v3

En este ejemplo se combina una aplicación con FreeRTOS con una en baremetal. El core 0 corre FreeRTOS leyendo el sensor de temperatura interno con el ADC y mandándolo por una queue al core 1. Además, tiene una tarea permanentemente conmutando el LED de la placa. El core 0 corre un programa baremetal que imprime lo recibido del core 0 y además corre una interrupción por Timer que envía por consola el tiempo transcurrido desde que inició el programa.

- `main.c` tiene el punto de entrada del programa.
- `core_0.c` tiene el programa que corre en el procesador principal.
- `core_1.c` tiene el programa que corre en el segundo procesador.
- `common.h` tiene algunos prototipos y definiciones comunes para ambos procesadores.
- `freertos` tiene toda la biblioteca de FreeRTOS para un Cortex-M0+.
