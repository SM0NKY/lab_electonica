#ifndef BUTTON_H
#define BUTTON_H

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "esp_log.h"

class Button {
    public:
        explicit Button(gpio_num_t button_pin); //Constructor con argumento del pin
        bool button_state;
        //Función para cambiar el estado del botón
        void button_state_flip(); 
        
    private:
        //Pin para el botón
        gpio_num_t button_pin;

};
#endif