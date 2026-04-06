// Programa principal para los motores utilizando LORA -> ESP32 -> PWM
// Se utiliza CMAKE y se hace la build con esp-idf v5.5.3, flasheo con esptool.py

//Drivers//
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Motor.h"
#include "Button.h"

//Pin motor PWM
#define MOTOR_PWM1 GPIO_NUM_32
//Pin del botón
#define BUTTON GPIO_NUM_26

static const char *TAG = "Button";

extern "C" void app_main(void) 
{
    Driver1 motors(MOTOR_PWM1); //Inicializar la clase del motor con el pin PWM1
    Button button(BUTTON); //Inicializar la clase del botón con el pin del botón
    while (1) {
        int button_state = gpio_get_level(BUTTON);
        ESP_LOGI(TAG, "Estado del botón: %d", button_state);

        if (button_state == 0) {
            ESP_LOGI(TAG, "Botón presionado, cambiando estado del motor");
            button.button_state_flip(); // Cambia el estado del botón
            if (button.button_state) {
                ESP_LOGI(TAG, "Motor a un angulo de 90 grados");
                motors.motor_angular_movement(90.0);
            } else {
                ESP_LOGI(TAG, "Motor a un angulo de 0 grados");
                motors.motor_angular_movement(0.0);
            }
            vTaskDelay(pdMS_TO_TICKS(200));
        }
        
    }
}