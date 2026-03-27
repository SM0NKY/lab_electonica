#ifndef MOTOR_H
#define MOTOR_H

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

class Driver1 {
    public:
        Driver1(gpio_num_t PWM1);//Constructor with pin arguments
        
        //Establece una funcion para encender los motores y establecer una velocidad
        //En este caso para detener el motor se puede poner una velocidad de 0 
        void motor_angular_movement(float angle); //Establece la velocidad del motor 1    
        
        float motor_angular_pwm(float angle); //Convierte el ángulo en un duty cycle para el PWM donde el ángulo es en grados
        
    private:
        //Pines para darle corriente los motores 
        gpio_num_t PWM1;
        
        //Variables para el canal 
        ledc_channel_t ledcChannel1;
};

#endif