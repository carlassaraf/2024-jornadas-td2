#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/util/queue.h"

#include "common.h"

// Cola para datos entre cores
queue_t queue;

/**
 * @brief Programa principal
 */
int main(void){
    return core_0();
}