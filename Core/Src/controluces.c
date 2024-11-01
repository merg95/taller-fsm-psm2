#include "main.h"

void semaforo(void) {
    uint32_t tiempo_actual = HAL_GetTick();

    switch (estado) {
        case 0:  // Luz verde encendida, esperando una solicitud
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);  // Encender luz verde
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Apagar luz roja

            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
                solicitud = 1;  // Se marca la solicitud
            }

            if (solicitud == 1) {
                estado = 1;  // Cambiar a estado de verde parpadeante
                tiempo_inicio = tiempo_actual;
                solicitud = 0;
            }
            break;

        case 1:  // Verde parpadeando durante 1 segundo
            if (tiempo_actual - tiempo_inicio >= 1000) {
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);  // Apagar luz verde
                estado = 2;
                tiempo_inicio = tiempo_actual;
            } else if ((tiempo_actual - tiempo_inicio) % 200 < 100) {
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);  // Encender luz verde
            } else {
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);  // Apagar luz verde
            }
            break;

        case 2:  // Luz roja encendida durante 3 segundos
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Encender luz roja
            if (tiempo_actual - tiempo_inicio >= 3000) {
                estado = 3;
                tiempo_inicio = tiempo_actual;
            }
            break;

        case 3:  // Rojo parpadeando durante 1 segundo
            if (tiempo_actual - tiempo_inicio >= 1000) {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Apagar luz roja
                estado = 0;
                tiempo_inicio = tiempo_actual;
            } else if ((tiempo_actual - tiempo_inicio) % 200 < 100) {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Encender luz roja
            } else {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Apagar luz roja
            }
            break;
    }
}
