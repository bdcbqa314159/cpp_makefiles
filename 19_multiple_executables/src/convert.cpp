#include "convert.hpp"

double celsius_to_fahrenheit(double c) { return c * 9.0 / 5.0 + 32.0; }
double fahrenheit_to_celsius(double f) { return (f - 32.0) * 5.0 / 9.0; }

double km_to_miles(double km) { return km * 0.621371; }
double miles_to_km(double miles) { return miles / 0.621371; }
