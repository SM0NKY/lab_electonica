#include "Motor.h"
#include "freertos/task.h"
#include <stdio.h>
#include <string.h>
#include "driver/mcpwm_prelude.h"

static const char *TAG = "MotorControl";

//Parametros para el control del motor
#define SERVO_MIN_PULSEWIDTH_US 500  // Ancho de pulso mínimo en microsegundos
#define SERVO_MAX_PULSEWIDTH_US 2500  // Ancho de pulso máximo en microsegundos
#define SERVO_MIN_DEGREE        0.0f     // Ángulo mínimo
#define SERVO_MAX_DEGREE        180.0f      // Ángulo máximo
        // GPIO conectado a la línea de señal PWM
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000  // 1MHz, 1us por tick
#define SERVO_TIMEBASE_PERIOD        20000    // 20000 ticks, 20ms

//Cambiar las funciones del ledc por mcpwm

Driver1::Driver1(gpio_num_t nmt1) {
    PWM1 = nmt1;

    ESP_LOGI(TAG, "Timer y operador creados");

    //Configuración del timer
    this->timer = NULL;
    mcpwm_timer_config_t timer_config = {};
        timer_config.group_id = 0;
        timer_config.clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT;
        timer_config.resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ;
        timer_config.period_ticks = SERVO_TIMEBASE_PERIOD;
        timer_config.count_mode = MCPWM_TIMER_COUNT_MODE_UP;

    ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &this->timer));
    //Configuración del operador

    this->oper = NULL;
    mcpwm_operator_config_t operator_config = {};
    operator_config.group_id = 0; // El operador debe estar en el mismo grupo que el timer
    
    ESP_ERROR_CHECK(mcpwm_new_operator(&operator_config, &this->oper));
    ESP_LOGI(TAG, "Timer y operador conectados");
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(this->oper, this->timer));

    ESP_LOGI(TAG, "Comparador y generador creados a partir del operador");
    
    
    this->comparator = NULL;
    
    mcpwm_comparator_config_t comparator_config = {};
    comparator_config.flags.update_cmp_on_tez = true;
    ESP_ERROR_CHECK(mcpwm_new_comparator(this->oper, &comparator_config, &this->comparator));
    
    
    this->generator = NULL;
    mcpwm_generator_config_t generator_config = {};
    generator_config.gen_gpio_num = this->PWM1; // GPIO conectado 

    ESP_ERROR_CHECK(mcpwm_new_generator(this->oper, &generator_config, &this->generator));

    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(this->comparator, this->example_angle_to_compare(0.0f))); // Valor de comparación inicial, el servo se moverá a la posición central

    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(this->generator, MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP,MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));

    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(this->generator, MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP,this->comparator ,MCPWM_GEN_ACTION_LOW)));

    ESP_LOGI(TAG, "Acción del generador establecida en eventos de timer y comparación");

    ESP_ERROR_CHECK(mcpwm_timer_enable(this->timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(this->timer, MCPWM_TIMER_START_NO_STOP));
}

void Driver1::motor_angular_movement(float angle) {
    // Utilizar un comparator
    if (angle < SERVO_MIN_DEGREE) angle = SERVO_MIN_DEGREE;
    if (angle > SERVO_MAX_DEGREE) angle = SERVO_MAX_DEGREE;

    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(this->comparator, this->example_angle_to_compare(angle)));
    return;
};


uint32_t Driver1::example_angle_to_compare(float angle) {
    float pulse_us = (angle - SERVO_MIN_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (SERVO_MAX_DEGREE - SERVO_MIN_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
    return (uint32_t)(pulse_us + 0.5f);
};