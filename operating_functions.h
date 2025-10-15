//
// Operating_functions.h
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// operating_functions.cpp header.
//
#pragma once
#include "side_functions.h"
#include <cstdlib>
#include <cstdio>
#include <type_traits> // For is_same

bool is_correct_input(const char* ch_dirt_input, bool allow_fraction);

// Numeric input handler
// Writes user input into variable
template <class T>
bool input_handler(const char* ch_text_to_display, T& T_input_variable) {
	char ch_input[17];


	while (1) {
		printf("%s", ch_text_to_display);                          // Displays call to input
		scanf_s("%16s", ch_input, 17);

		if (buffer_clean()) {                                      // Cleans buffer, if there was more than 16 bytes, and giving exception
			printf("\nSorry, low memory machine does not support more than 16 bytes input :(\nInput supported value.");
			continue;
		}

		bool allow_fraction = std::is_same<T, double>::value;      // Checks whether it's double

		if (quit(ch_input)) return false;

		else if (is_correct_input(ch_input, allow_fraction)) {
			if (allow_fraction) T_input_variable = atof(ch_input); // double - atof

			else				T_input_variable = atoi(ch_input); // int - atoi

			return true;
		}
	}
}
// END

// Array input handler
// Writes user input into array
// 0 - number is good
// 1 - quit
// 2 - not valid size
// 3 - not valid number
int array_input_handler(int& iter, int* p_i_input_array, int i_array_size, int max_element_size);