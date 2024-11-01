// main.h
#ifndef __MAIN_H
#define __MAIN_H
#define GPIOC_PIN_13 GPIO_PIN_13
#define GPIOC_PORT GPIOC

#include <stdint.h>
// Otras inclusiones necesarias...

extern int estado;  // Estado del semáforo
extern int solicitud;  // Bandera para la solicitud

#endif /* __MAIN_H */
