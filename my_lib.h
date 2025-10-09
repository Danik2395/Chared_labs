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
#define my_NaN (double)INT_MAX

// Checks if double is near zero
inline bool is_near_zero(double);

// Gives fractional part of devision two doubles
double my_fmod(double var1, double var2);

// Reverses negative double
double my_fabs(double var);

// Returns string length
int my_strlen(const char*);

// Returns true if strings are equal
bool my_strcmp(const char*, const char*);