/*
TODO: new display integration
*/

// only update speed periodically to reduce fluctuations
int update_speed = 0;

// magnet pole direction. 0 for reducing voltage and 1 for increasing voltage
int magnet_pole_dir = 0;

// background voltage fluctuations of hall effect sensor
float noise_voltage = 0.05;

// voltage of hall effect sensor data pin when no magnet present
float off_voltage = 0;

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
float wheel_diameter = 0.7;

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
float speed_const = 11309760 * wheel_diameter / (1 + magnet_placement);
// (this assumes no-slip)

// the three digits that will become the rpm on the display
int digit1 = 0; int digit2 = 0; int digit3 = 0; int digit4 = 0;
