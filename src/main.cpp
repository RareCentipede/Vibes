#include <Arduino.h>
#include <servo.h>
#include "../include/haptic_hand.h"

int left_hand_servo_linear = 10;
int left_hand_servo_rotational = 3;
int left_hand_vibe = 12;

int right_hand_servo_linear = 4;
int right_hand_servo_rotational = 5;
int right_hand_vibe = 2;

HapticHand left_hand;
HapticHand right_hand;

int freq = 65;
float force = 0.0;

void setup(){
  Serial.begin(115200);
  left_hand.initialize_hand(left_hand_servo_linear, left_hand_servo_rotational, left_hand_vibe);
  right_hand.initialize_hand(right_hand_servo_linear, right_hand_servo_rotational, right_hand_vibe);
}

void loop(){
  left_hand.actuate_bat(force);
  right_hand.actuate_bat(force);
  if (Serial.available()){
    char cmd = Serial.read();
    switch (cmd){
      case '0':
        force = 0.0;
        break;

      case '1':
        force = 10;
        break;
  
      case '2':
        force = 30;
        break;

      case '3':
        force = 65;
        break;
  
      case '4':
        force = 70;
        break;

      case '5':
        force = 100;
        break;

      case 'e':
        left_hand.enable_vibe();
        left_hand.enable_z();
        right_hand.enable_vibe();
        right_hand.enable_z();
        break;

      case 'r':
        left_hand.reset();
        right_hand.reset();
        break;

      default:
        Serial.println("Unknown command");
        break;
    }
  }
}