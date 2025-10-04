//
// my_lib.h
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Library of banned functions header.
//
#pragma once

constexpr double EPSILON = 1e-12; // Equivalent of zero
#define my_NaN (double)INT_MAX

// Checks if double is near zero
inline bool is_near_zero(double);

// Gives fractional part of double
double my_fmod(double var1, double var2);

// Reverces negative double
double my_fabs(double var);

// Returns string length
int my_strlen(const char*);

// Returns true if strings are equal
bool my_strcmp(const char*, const char*);