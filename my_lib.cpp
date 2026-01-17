//
// my_lib.cpp
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Library of rewritten banned functions.
// Use with caution, may not work outside the project.
// Depends on numeric input logic that is in Зачарованные_лабы.cpp.
//
#include "my_lib.h"
#include <limits.h>


inline bool is_near_zero(double var) {
	return var > -EPSILON && var < EPSILON;
}



double my_fmod(double var1, double var2) {
	if (is_near_zero(var2)) return my_NaN;
	int whole_part = (int)(var1 / var2);
	return var1 - var2 * whole_part;
}



double my_fabs(double var) {
	if (is_near_zero(var)) return 0;
	return var < 0 ? -var : var;
}



int my_strlen(const char* ch_array) {
	int i_string_len = 0;
	for (int i = 0; ch_array[i] != '\0'; ++i, ++i_string_len);
	return i_string_len;
}



bool my_strcmp(const char* ch_array1, const char* ch_array2) {
	for (int i = 0; ch_array1[i] == ch_array2[i]; ++i) {
		if (ch_array1[i] == '\0') return true;
	}
	return false;
}