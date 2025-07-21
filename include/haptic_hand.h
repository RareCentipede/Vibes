#ifndef HAPTIC_HAND_H
#define HAPTIC_HAND_H

#include <servo.h>

class HapticHand{
    private:
        int servo_pin_1; // Pin for the first servo
        int servo_pin_2; // Pin for the second servo
        int vibe_pin;    // Pin for the vibration motor
        float duty_cycle_percent = 0.5; // Default duty cycle percentage for vibration motor
        unsigned long int start_time_ms_vibe = 0; // Start time for vibration
        unsigned long int start_time_ms_z = 0; // Start time for Z translation
        int time_ms = 0; // Duration for vibration in milliseconds

        Servo servo_l;     // Servo object for controlling the servo motors
        Servo servo_r;     // Servo object for controlling the servo motors
        
    public:
        bool vibrate = false;
        bool is_vibrating = false; // Flag to check if vibration is active
        bool do_translate_z = true;
        bool is_translating_z = false;

        HapticHand();
        void init_vibe(int vibe_pin, int frequency = 65);
        void enable_vibe();
        void disable_vibe(int vibe_pin);
        void initialize_hand(int servo_pin_1, int servo_pin_2, int vibe_pin);
        void translate_z(char direction);
        void translate_z_ms(char direction, uint16_t duration_ms);
        void enable_z();
        void rotate_x(float angle);
        void vibe(float duty_cycle_percent = 0.5);
        void vibe_ms(uint16_t duration_ms, float duty_cycle_percent = 0.5);
        // ~HapticHand();
        
    };

#endif