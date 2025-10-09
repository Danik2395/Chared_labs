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

// For displaying error messages 
inline void DISPLAY_ERROR_MESSAGE(const char* message, bool error_message_true) {
	if (error_message_true) printf("%s", message);
}

bool is_correct_input(const char*, bool, bool);

// Input handler
// If you need to display error message, error_message_true = true
template <class T>
bool input_handler(const char* ch_text_to_display, T& d_input_variable, bool error_message_true) {
	char ch_input[17];


	while (1) {
		printf("%s", ch_text_to_display);                          // Displays call to input
		scanf_s("%16s", ch_input, 17);

		bool allow_fraction = std::is_same<T, double>::value;      // Checks whether it's double

		if (quit(ch_input)) return false;

		else if (is_correct_input(ch_input, allow_fraction, error_message_true)) {
			if (allow_fraction) d_input_variable = atof(ch_input); // double - atof

			else				d_input_variable = atoi(ch_input); // int - atoi

			return true;
		}
	}
}
// END