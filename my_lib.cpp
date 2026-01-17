//
// my_lib.cpp
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Library of rewritten banned functions.
// May not work outside the project.
// Depends on input logic that is in Зачарованные_лабы.cpp.
//
#include "my_lib.h"
#include <limits.h>
#include <windows.h>


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



int my_abs(int var) {
	if (var == 0) return 0;
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



// Random
static unsigned int* seed_storage() {          // Pointer returns address of seed_storage{}
	static unsigned int seed_storage{};        // Actual unchanging storage, because of static
	return &seed_storage;                      // This is address
}

void generate_seed() {
	unsigned int* p_set_seed = seed_storage(); // Setting pointer on storage cell
	*p_set_seed = GetTickCount64();            // Writing value by this address
}

int my_random(int max_decade, int minus_chance) {
	unsigned int* p_seed = seed_storage();
	unsigned int minus = *p_seed;              // Writing seed to calculate minus
	*p_seed = *p_seed * 1103515245 + 12345;    // Getting value from pointer and CHANGING it (numbers, calculated by smart people)
	minus = minus * 12345 + 1103515245;
	int tick = (*p_seed / 65536) % max_decade;
	if (minus % 1000 > minus_chance * 10) {
		tick = -tick;
	}
	return tick;
}
// END