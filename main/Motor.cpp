#include "Motor.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include <stdio.h>
#include <string.h>

#define MOTOR_FREQ 50
#define MOTOR_RESOLUTION LEDC_TIMER_13_BIT
#define MOTOR_MODE LEDC_LOW_SPEED_MODE
#define TIMER LEDC_TIMER_0

Driver1::Driver1(gpio_num_t nmt1) {
    PWM1 = nmt1;

    gpio_reset_pin(PWM1);

    ledc_timer_config_t timer_config = {};
    timer_config.speed_mode = MOTOR_MODE;
    timer_config.duty_resolution = MOTOR_RESOLUTION;
    timer_config.timer_num = TIMER;
    timer_config.freq_hz = MOTOR_FREQ;
    timer_config.clk_cfg = LEDC_AUTO_CLK;

    ledc_timer_config(&timer_config);

    ledc_channel_config_t channel1_config = {};
    channel1_config.gpio_num = PWM1;
    channel1_config.speed_mode = MOTOR_MODE;
    channel1_config.channel = LEDC_CHANNEL_0;
    channel1_config.timer_sel = TIMER;
    channel1_config.duty = 0;
    channel1_config.hpoint = 0;

    ledc_channel_config(&channel1_config);
}

float Driver1::motor_angular_pwm(float angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    // Para SG90 suele funcionar mejor 1.0 ms a 2.0 ms
    float dutyCycle = 410.0 + (angle / 180.0) * (819.0 - 410.0);

    return dutyCycle;
}

void Driver1::motor_angular_movement(float angle) {
    uint32_t pwm_value = (uint32_t)motor_angular_pwm(angle);

    ledc_set_duty(MOTOR_MODE, LEDC_CHANNEL_0, pwm_value);
    ledc_update_duty(MOTOR_MODE, LEDC_CHANNEL_0);

    printf("Servo 1 en %.2f grados (Duty: %lu)\n", angle, (unsigned long)pwm_value);
}