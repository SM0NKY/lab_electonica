// Programa principal para los motores utilizando LORA -> ESP32 -> PWM
// Se utiliza CMAKE y se hace la build con esp-idf v5.5.3, flasheo con esptool.py

//Drivers//
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Motor.h"

//Pin motor PWM
#define MOTOR_PWM1 GPIO_NUM_18

extern "C" void app_main(void) 
{
    //Setear el motor a on al inicio 
    Driver1 motors(MOTOR_PWM1); //Inicializar la clase del motor con el pin PWM1
    
    while (1) {
        motors.motor_angular_movement(0.0);
        vTaskDelay(pdMS_TO_TICKS(2000));

        motors.motor_angular_movement(90.0);
        vTaskDelay(pdMS_TO_TICKS(2000));

        motors.motor_angular_movement(180.0);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}