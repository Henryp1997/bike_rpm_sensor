<<<<<<< HEAD
// #include <chrono>
// using namespace std::chrono;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
int timer_lcd_voltage = 0;
int measuring_rpm = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
float prev_voltage = 0;
const float noise_voltage = 0.05;
=======
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
>>>>>>> 65bc69e7d82b0a28ad084540be1645f2efdcd8b8

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
<<<<<<< HEAD
  prev_voltage = get_sensor_voltage(analogRead(A0));
  delay(1000);
}

int test() {
  int rpms[100];
  int i = 0;
  while (i < 100) {
    rpms[i] = i;
    i ++;
  }
=======
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
>>>>>>> 65bc69e7d82b0a28ad084540be1645f2efdcd8b8
}

float get_sensor_voltage(float volt_bits) {
  return (volt_bits * 5.0) / 1024.0;
}

// int calculate_rpm(int start_time, )

void loop() {
  int rpms = test();

  // read HEF sensor voltage
  float voltage = get_sensor_voltage(analogRead(A6));
  Serial.println(voltage);

  // 0.05V is about the maximum I could consider to be noise
  Serial.println(noise_voltage);
  if (abs(voltage - prev_voltage) > noise_voltage) {
    // magnet detected, start measuring time from here
    Serial.println("Magnet detected");
    // int start_time = high_resolution_clock::now();
    // if (measuring_rpm = 1) {
      
    // }
    // measuring_rpm = 1;
  }

  // check if voltage has returned to the initial value
  // i.e., magnet not close to sensor
  if (abs(voltage - prev_voltage) < noise_voltage) {
    // stop measuring time. Now calculate the difference in
    // time from when the peak was detected to now, this is
    // the time taken for one full revolution i.e. the RPM
    Serial.println("Magnet no longer detected");
  }

  // only update LCD every 50th pass through this function
  if (timer_lcd_voltage == 50) {
    timer_lcd_voltage = -1;
  }

  // update variables
  timer_lcd_voltage ++;
  prev_voltage = voltage;
  }
