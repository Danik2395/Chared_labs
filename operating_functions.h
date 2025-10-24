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
#include <stdarg.h>    // For changing number of arguments in function

// Mind that macro takes not derefernced pointer
#define FORMAT_D(p) (*p == '%' && *(p + 1) == 'd')
#define FORMAT_F(p) (*p == '%' && *(p + 1) == 'f')
#define FORMAT_PERC(p) (*p == '%' && *(p + 1) == '%')

// Input checker
bool is_correct_input(const char* ch_dirt_input, bool allow_fraction);

// Numeric input handler
// Writes user input into variable
// Support %d %f and %% formats in ch_message. Put corresponding arguments in '...'
template <class T>
bool number_input_handler(const char* ch_message, T& T_input_variable, ...) {
	char ch_input[17];
	va_list argument;
	
	while (1) {
		va_start(argument, &T_input_variable);                         // Setting va_start on last predicted argument. And updating it in every cycle

		// Displays call to input
		for (const char* p = ch_message; *p; ++p) {                    // Moving 'p' on ch_message while *p has symbol under it (if (*p == \0) stop;)
			if (FORMAT_D(p)) printf("%d", va_arg(argument, int)), ++p; // ++p to not to print format letter

			else if (FORMAT_F(p)) printf("%.2f", va_arg(argument, double)), ++p;

			else if (FORMAT_PERC(p)) putchar('%'), ++p;

			else putchar(*p);
		}

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

			va_end(argument);
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

// String input handler
// Writes user input into array-string
// 0 - all is good
// 1 - memory initialize fail
int string_input_handler(char** p_ch_destination, size_t& string_size, size_t type_size);