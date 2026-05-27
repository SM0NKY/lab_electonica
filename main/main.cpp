// Programa principal para los motores utilizando LORA -> ESP32 -> PWM
// Se utiliza CMAKE y se hace la build con esp-idf v5.5.3, flasheo con esptool.py

//Drivers//
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Motor.h"
#include "Button.h"

//Pin motor PWM
#define MOTOR_PWM1 GPIO_NUM_26
#define MOTOR_PWM2 GPIO_NUM_27
//Pin del botón
#define BUTTON GPIO_NUM_32

static const char *TAG = "Button";

extern "C" void app_main(void) 
{
    Driver1 motors(MOTOR_PWM1); //Inicializar la clase del motor con el pin PWM1
    Driver1 motors2(MOTOR_PWM2); //Inicializar la clase del motor con el pin PWM2
    Button button(BUTTON); //Inicializar la clase del botón con el pin del botón
    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Pequeña demora para evitar lecturas rápidas del botón

        motors.motor_angular_movement(0.0); // Inicializar el motor en 0 grados

        vTaskDelay(1000 / portTICK_PERIOD_MS); // Pequeña demora para evitar lecturas rápidas del botón

        motors.motor_angular_movement(90.0); // Mover el motor a 90 grados

        vTaskDelay(1000 / portTICK_PERIOD_MS); // Pequeña demora para evitar lecturas rápidas del botón
        
        motors2.motor_angular_movement(0.0); // Inicializar el motor en 0 grados
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Pequeña demora para evitar lecturas rápidas del botón
        motors2.motor_angular_movement(180.0); // Mover el motor a 180 grados

    }
        
}