/*
     6
    ---
11|     |7
  |  12 |
    ---
10|     |8
  |     |
    ---
     9

  pin 13 is decimal point (probably don't need)

  D1 = 2
  D2 = 3
  D3 = 4
  D4 = 5

*/

#include "variables.hpp"

// setup function - called once at the start
void setup() {
  init_all_pins();
  Serial.begin(9600);
}

// main loop
void loop() {
  set_display(speed);

  if (init_loop) {
    // read voltage across hall effect 
    // sensor data pin to initialise variable
    off_voltage = dac_to_volts(analogRead(A6));
    init_loop = 0;
  }

  float voltage = dac_to_volts(analogRead(A6));
  if (magnet_detected(voltage)) {
    // magnet detected, start measuring time
    if (!measuring) {
      // first detection of magnet
      start_time = micros();
    }
    else {
      // second detection of magnet
      end_time = micros();
      time_diff = end_time - start_time;

      // calculated 50Hz as the maximum possible rotation speed
      if ((time_diff / 1000000.0) > 0.1) {
        measuring = 0;
        speed = calculate_speed(time_diff);
        update_speed = 0;
      }

    }
  }
  else {
    // ensure that the analog pin went LOW at some point to count a valid revolution
    if ((micros() - start_time) / 1000000.0 < 10) {
      measuring = 1;
    }
    else {
      measuring = 0;
      // set_display(0.00);
    }
  }
}

int init_all_pins() {
  for (int i = 0; i < 9; i++) {
    if (i < 4) {
      pinMode(digit_pins[i], OUTPUT);
    };
    pinMode(segment_pins[i], OUTPUT);
  }
}

int set_digit_pos(int d1, int d2, int d3, int d4){
  digitalWrite(digit_pins[0], d1);
  digitalWrite(digit_pins[1], d2);
  digitalWrite(digit_pins[2], d3);
  digitalWrite(digit_pins[3], d4);
}

void set_number_from_pin_vals(int pin_vals[7]) {
  for (int i = 0; i < 7; i++) {
      digitalWrite(segment_pins[i], pin_vals[i]);
  }
}

int set_number(int num, int decimal) {
  int pin_vals[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  if (num == 0) {
    set_number_from_pin_vals(zero);
  }
  else if (num == 1) {
    set_number_from_pin_vals(one);
  }
  else if (num == 2) {
    set_number_from_pin_vals(two);
  }
  else if (num == 3) {
    set_number_from_pin_vals(three);
  }
  else if (num == 4) {
    set_number_from_pin_vals(four);
  }
  else if (num == 5) {
    set_number_from_pin_vals(five);
  }
  else if (num == 6) {
    set_number_from_pin_vals(six);
  }
  else if (num == 7) {
    set_number_from_pin_vals(seven);
  }
  else if (num == 8) {
    set_number_from_pin_vals(eight);
  }
  else if (num == 9) {
    set_number_from_pin_vals(nine);
  }

  digitalWrite(segment_pins[7], decimal);
}

void set_display(float value) {
  digit1 = floor(value);
  if (value > 10) {
    // for values greater than or equal to 10, the digit1 value
    // is actually the first two digits
    int digit1_new = floor(digit1 / 10);
    int digit2_new = digit1 % 10;
    int digit3_new = floor((value - digit1) * 10);
    int digit4_new = floor((((value - digit1) * 10) - digit3_new) * 10);
    digit1 = digit1_new; digit2 = digit2_new; digit3 = digit3_new; digit4 = digit4_new;
  }
  else {
    digit2 = floor((value - digit1) * 10);
    digit3 = floor((((value - digit1) * 10) - digit2) * 10);
  }
  
  // set first digit
  set_digit_pos(0, 1, 1, 1);
  if (value > 10) {
    set_number(digit1, false);
  }
  else {
    set_number(digit1, true);
  }
  set_all_low();

  // set second digit
  set_digit_pos(1, 0, 1, 1);
  if (value > 10) {
    set_number(digit2, true);
  }
  else {
    set_number(digit2, false);
  }
  set_all_low();
  
  // set third digit
  set_digit_pos(1, 1, 0, 1);
  set_number(digit3, false);
  set_all_low();

  // set fourth digit if needed
  set_digit_pos(1, 1, 1, 0);
  if (value > 10) {
    set_number(digit4, false);
    set_all_low();
  }
}

void set_all_low() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segment_pins[i], 0);
  }
}

float dac_to_volts(float dac) {
  return dac * 5.0 / 1024.0;
}

bool magnet_detected(float voltage) {
  if (magnet_pole_dir == 1) {
    return voltage - off_voltage > noise_voltage;
  }
  return off_voltage - voltage > noise_voltage;
}

float calculate_speed(unsigned long time_diff) {
  // see variables.h for derivation of speed_const
  return speed_const / time_diff;
}
