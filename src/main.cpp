#include <Arduino.h>
#include <servo.h>
#include "../include/haptic_hand.h"

int left_hand_servo_linear = 2;
int left_hand_servo_rotational = 3;
int left_hand_vibe = 12;

int right_hand_servo_linear = 25;
int right_hand_servo_rotational = 26;
int right_hand_vibe = 2;

HapticHand left_hand;
HapticHand right_hand;

void setup(){
  Serial.begin(115200);
  left_hand.initialize_hand(left_hand_servo_linear, left_hand_servo_rotational, left_hand_vibe);
  right_hand.initialize_hand(right_hand_servo_linear, right_hand_servo_rotational, right_hand_vibe);
}

void loop(){
  // Example usage of the HapticHand class
  left_hand.translate_z_ms('u', 1000); // Move up for 1 second
  // left_hand.rotate_x(45.0);          // Rotate to 45 degrees
  // left_hand.vibe_ms(2000);
  // left_hand.enable_z();
  // delay(1000);
  // left_hand.enable_vibe();
  Serial.println("Move down");
  left_hand.translate_z_ms('d', 1000); // Move down for 1 second
  // left_hand.rotate_x(-45.0);         // Rotate back to -45 degrees
  // left_hand.vibe_ms(500);               // Vibrate for 500 milliseconds
  delay(1000);
  left_hand.enable_z();
}