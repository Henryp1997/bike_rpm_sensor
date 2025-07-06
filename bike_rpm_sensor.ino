/*
TODO: new display integration - need driver
*/

#include "variables.hpp"

// setup function - called once at the start
void setup() {
    init_all_pins();
    Serial.begin(9600);
}

void set_display(value) {
    return;
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
