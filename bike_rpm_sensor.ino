int zero[8] = {1, 1, 1, 1, 1, 1, 0};
int one[8] = {0, 1, 1, 0, 0, 0, 0};
int two[8] = {1, 1, 0, 1, 1, 0, 1};
int three[8] = {1, 1, 1, 1, 0, 0, 1};
int four[8] = {0, 1, 1, 0, 0, 1, 1};
// int four[8] = {0, 0, 0, 0, 0, 0, 0};
int five[8] = {1, 0, 1, 1, 0, 1, 1};
int six[8] = {1, 0, 1, 1, 1, 1, 1};
int seven[8] = {1, 1, 1, 0, 0, 0, 0};
int eight[8] = {1, 1, 1, 1, 1, 1, 1};
int nine[8] = {1, 1, 1, 1, 0, 1, 1};

int digit_pins[4] = {2, 3, 4, 5};
int segment_pins[8] = {6, 7, 8, 9, 10, 11, 12, 13};

int update_display = 0;
int digit1 = 0; int digit2 = 0; int digit3 = 0;

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

void set_all_low() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segment_pins[i], 0);
  }
}

void setup() {
  init_all_pins();
  Serial.begin(9600);
}

void loop () {
  if (update_display == 200) {
    // first read voltage from analog pin A6
    float voltage = (analogRead(A6) * 5.0) / 1024.0;

    digit1 = floor(voltage);
    digit2 = floor((voltage - digit1) * 10);
    digit3 = floor((((voltage - digit1) * 10) - digit2) * 10);
    update_display = 0;
  }
  else {
    update_display++;
  }

  set_digit_pos(0, 1, 1, 1);
  set_number(digit1, true);
  set_all_low();

  set_digit_pos(1, 0, 1, 1);
  set_number(digit2, false);
  set_all_low();
  
  set_digit_pos(1, 1, 0, 1);
  set_number(digit3, false);
  set_all_low();

}

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