#ifndef MOTOR_H
#define MOTOR_H

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/mcpwm_prelude.h"
#include "esp_log.h"

class Driver1 {
    public:
        explicit Driver1(gpio_num_t PWM1); //Constructor con argumento del pin
        
        // Funciones para el control del motor
        void motor_angular_movement(float angle);   
        
    private:
        //Pines para darle corriente los motores 
        gpio_num_t PWM1;
        
        
        //Variables para el control del motor con mcpwm_prelude
        mcpwm_timer_handle_t timer;
        mcpwm_oper_handle_t oper;
        mcpwm_cmpr_handle_t comparator;
        mcpwm_gen_handle_t generator;


        uint32_t example_angle_to_compare(float angle);
};

#endif