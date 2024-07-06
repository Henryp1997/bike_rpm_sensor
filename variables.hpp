// arrays of HIGHs and LOWs to define seven-segment numbers
int zero[8] = {1, 1, 1, 1, 1, 1, 0};
int one[8] = {0, 1, 1, 0, 0, 0, 0};
int two[8] = {1, 1, 0, 1, 1, 0, 1};
int three[8] = {1, 1, 1, 1, 0, 0, 1};
int four[8] = {0, 1, 1, 0, 0, 1, 1};
int five[8] = {1, 0, 1, 1, 0, 1, 1};
int six[8] = {1, 0, 1, 1, 1, 1, 1};
int seven[8] = {1, 1, 1, 0, 0, 0, 0};
int eight[8] = {1, 1, 1, 1, 1, 1, 1};
int nine[8] = {1, 1, 1, 1, 0, 1, 1};

// pins controlling the four digits
int digit_pins[4] = {2, 3, 4, 5};

// pins controlling the eight segments (8th is decimal point)
int segment_pins[8] = {6, 7, 8, 9, 10, 11, 12, 13};

// only update display when this value reaches a set value
int update_display = 0;

// background voltage fluctuations of hall effect sensor
float noise_voltage = 0.05;

// initialise prev_voltage variable
float prev_voltage = 0;

// flag to allow parameter initialisation in the main loop only one time
int init_loop = 1;

// flag to tell whether the magnet was just detected and a timer has started
int measuring = 0;

// times used for measuring speed
unsigned long start_time = 0;
unsigned long end_time = 0;
unsigned long time_diff = 0;

// speed of bike wheel
float speed = 0.000;

// diameter of typical 700c wheel. You might want to measure
// this yourself to improve accuracy or if you are using a different
// type of bike. Make sure the tyre is pumped up before measuring
float wheel_diameter = 0.622;

// calculate maximum speed of magnet given max travel speed of 120km/h
// the max travel speed is only valid for the center of the wheel. At the top
// of the wheel, the speed is 2V. So at the magnet_placement fraction,
// which is defined as the ratio of the magnet radius to full wheel radius, the speed
// is between V and 2V. The max_speed variable is calculated in a such a way
// to account for this.
float magnet_placement = 0.5;
float max_speed = 120 * (1 + magnet_placement);

// speed = (2 * pi * r) / T
// need to multiply this by (1 + magnet_placement) for the same reasoning as given above:
// speed = (2 * pi * r) * (1 + MP) / T
// also use diameter so factor of 0.5 needed: 2 and 0.5 cancel
// speed = (pi * d) * (1 + MP) / T
// time difference is in microseconds, so need to divide it by 1e6. This puts
// factor of 1e6 on the top of the fraction. So the factor is just 3.1416 * 1000000
// then to convert to km/h, multiply by 3.6: factor is 11309760. Therefore, the full
// constant that needs to be divided by time_diff value is:
float speed_const = 11309760 * wheel_diameter * (1 + magnet_placement);
// (this assumes no-slip)

// the three digits that will become the rpm on the display
int digit1 = 0; int digit2 = 0; int digit3 = 0; int digit4 = 0;
