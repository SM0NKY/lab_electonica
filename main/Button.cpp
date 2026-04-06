#include "Button.h"


static const char *TAG = "Button";

Button::Button(gpio_num_t button_pin){
    this->button_pin = button_pin;
    this->button_state = false; //Estado inicial del botón

    //Configurar el boton
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << button_pin);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    ESP_ERROR_CHECK(gpio_config(&io_conf));

    ESP_LOGI(TAG, "Botón configurado en GPIO %d", button_pin);
}

void Button::button_state_flip() {
    this->button_state = !this->button_state; // Cambia el estado del botón
    ESP_LOGI(TAG, "Estado del botón cambiado a: %s", this->button_state ? "ON" : "OFF");
}