# multicore v1

En este ejemplo se corren dos programas en baremetal en ambos procesadores. En ambos programas, se imprime un mensaje por consola.

- `main.c` tiene el punto de entrada del programa.
- `core_0.c` tiene el programa que corre en el procesador principal.
- `core_1.c` tiene el programa que corre en el segundo procesador.
- `common.h` tiene algunos prototipos y definiciones comunes para ambos procesadores.
