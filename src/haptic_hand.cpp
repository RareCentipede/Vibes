#include <../include/haptic_hand.h>
#include <Servo.h>
#include <Arduino.h>

HapticHand::HapticHand() {
    ;
}

void HapticHand::initialize_hand(int servo_pin_1, int servo_pin_2, int vibe_pin){
    this->servo_pin_1 = servo_pin_1;
    this->servo_pin_2 = servo_pin_2;
    this->vibe_pin = vibe_pin;

    this->servo_l = Servo();
    this->servo_l.attach(servo_pin_1);


    this->servo_r = Servo();
    this->servo_r.attach(servo_pin_2);

    this->init_vibe(vibe_pin);
}

void HapticHand::init_vibe(int vibe_pin) {
    this->vibe_pin = vibe_pin;
    pinMode(vibe_pin, OUTPUT);

    switch (vibe_pin){
        case 12: // PB6, OC1B
            TCCR1A = _BV(COM1B1) | _BV(WGM11);
            TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11); // Prescaler = 8
            ICR1 = 0;
            OCR1B = 0;
            break;

        case 2: // PE3, OC3B
            TCCR3A = _BV(COM3B1) | _BV(WGM31);
            TCCR3B = _BV(WGM33) | _BV(WGM32) | _BV(CS31); // Prescaler = 8
            ICR3 = 0;
            OCR3B = 0;
            break;

        default:
            Serial.println("Invalid vibe pin. Use pin 12 (OC1B) or 2 (OC3B).");
            return;
    }

    vibrate = true;
}

void HapticHand::disable_vibe(int vibe_pin){
    switch (vibe_pin){
        case 12: // PB6
            OCR1B = 0; // Disable Timer1
            break;

        case 2: // PE3
            OCR3B = 0; // Disable Timer3
            break;

        default:
            Serial.println("Invalid vibe pin specified. Use PB6 (pin 12) or PH6 (pin 9).");
            return;
    }

    // digitalWrite(vibe_pin, LOW); // Turn off the vibration motor
    vibrate = false;
}

void HapticHand::translate_z(char direction){
    Serial.println(direction);
    switch (direction){
        case 'u':
            servo_l.write(180);
            break;
        case 'd':
            servo_l.write(60);
            break;
        default:
            Serial.println("Invalid direction for translate_z");
            break;
    }
}

void HapticHand::translate_z_ms(char direction, uint16_t duration_ms){
    unsigned long now = millis();

    if (!is_translating_z && do_translate_z) {
        Serial.println("Starting translation in Z direction");
        start_time_ms_z = now;

        is_translating_z = true;
        translate_z(direction);
    }

    if (is_translating_z && ((now - start_time_ms_z) >= duration_ms)) {
        Serial.println("Stopping translation in Z direction");
        Serial.println(start_time_ms_z);
        Serial.println(now);
        is_translating_z = false;
        servo_l.write(90); // Reset servo position
        do_translate_z = false; // Stop further translations
        start_time_ms_z = 0;
    }
}

void HapticHand::rotate_x(float angle){
    // Assuming angle is in degrees and we map it to servo range
    this->servo_r.write(angle); // Servo expects angle in degrees
}

void HapticHand::vibe(int frequency){
    switch (vibe_pin){
        case 12: // PB6
            ICR1 = compute_register_freq_value(frequency); // Set frequency
            OCR1B = ICR1 * duty_cycle_percent; // Set duty cycle
            break;

        case 2: // PE3
            ICR3 = compute_register_freq_value(frequency); // Set frequency
            OCR3B = ICR3 * duty_cycle_percent; // Set duty cycle
            break;

        default:
            Serial.println("Invalid vibe pin specified. Use PB6 (pin 12) or PH6 (pin 9).");
            return;
    }
}

void HapticHand::vibe_ms(uint16_t duration_ms, int frequency) {
    unsigned long now = millis();

    if (!is_vibrating && vibrate) {
        Serial.println("Starting vibration");
        start_time_ms_vibe = now;
        is_vibrating = true;
        vibe(frequency);
    }

    if (is_vibrating && ((now - start_time_ms_vibe) >= duration_ms)) {
        Serial.println("Stopping vibration");
        Serial.println(start_time_ms_vibe);
        Serial.println(now);
        disable_vibe(vibe_pin);
        is_vibrating = false;
        start_time_ms_vibe = 0;
    }
}

void HapticHand::enable_vibe() {
    // digitalWrite(vibe_pin, HIGH); // Turn on the vibration motor
    vibrate = true;
}

void HapticHand::enable_z(){
    do_translate_z = true;
}

int compute_register_freq_value(int frequency) {
    return 16000000 / (8 * frequency); // Assuming a 16MHz clock and prescaler of 8
}