//
// my_lib.h
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Library of banned functions header.
//
#pragma once

// constexpr for defining on compilation stage
constexpr double EPSILON = 1e-12; // Equivalent of zero
#define my_NaN 128101010.010101821

// Checks if double is near zero
inline bool is_near_zero(double var);

// Gives fractional part of devision two doubles
double my_fmod(double var1, double var2);

// Reverses negative double
double my_fabs(double var);

// Reverses negative int
int my_abs(int var);

// Returns string length
int my_strlen(const char* ch_array);

// Returns true if strings are equal
bool my_strcmp(const char* ch_array1, const char* ch_array2);

void generate_seed();

// Generates "random" number.
// To use, call generate_seed() first.
// Range for max_number is +-65536
int my_random(int max_number, int minus_chance);