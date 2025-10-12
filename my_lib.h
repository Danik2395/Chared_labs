//
// my_lib.h
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Library of banned functions header.
//
#pragma once

// Equivalent of zero
constexpr double EPSILON = 1e-12; // constexpr for defining on compilation stage
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
int my_strlen(const char*);

// Returns true if strings are equal
bool my_strcmp(const char*, const char*);

void generate_seed();

// Generates "random" number.
// To use, call generate_seed() first.
int my_random(int, int);