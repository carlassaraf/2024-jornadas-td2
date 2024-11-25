# multicore v2

En este ejemplo se corren dos programas en baremetal en ambos procesadores. El core 0 se encarga de hacer una lectura del sensor de temperatura interno con el ADC y envía por una queue el dato al core 1 que se encarga de mandar la información por consola.

- `main.c` tiene el punto de entrada del programa.
- `core_0.c` tiene el programa que corre en el procesador principal.
- `core_1.c` tiene el programa que corre en el segundo procesador.
- `common.h` tiene algunos prototipos y definiciones comunes para ambos procesadores.
