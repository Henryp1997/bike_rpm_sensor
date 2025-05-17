// #include <chrono>
// using namespace std::chrono;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
int timer_lcd_voltage = 0;
int measuring_rpm = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
float prev_voltage = 0;
const float noise_voltage = 0.05;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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
