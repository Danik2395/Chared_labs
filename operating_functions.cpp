//
// Operating_functions.cpp
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Main functions for for laboratory work.
//


#include "my_lib.h"
#include "side_functions.h"
#include "operating_functions.h"
#include <cstdlib>
#include <cstdio>
#include <malloc.h>
#include <windows.h>


// Input checker
bool is_correct_input(const char* ch_dirt_input, bool allow_fraction) {
	int len = my_strlen(ch_dirt_input);
	int i_dot_count = 0;

	if (len == 0) {                                                                      // Checking if there is something to check
		printf("\nNo input. Input number.");
		return false;
	}

	if (ch_dirt_input[0] == '-' && len == 1 || ch_dirt_input[0] == '-' && (ch_dirt_input[1] < '0' || ch_dirt_input[1] > '9')) {
		printf("\nNot valid input. Enter valid number.");                                // Checks if it is not only minus in input (or -. for example)
		return false;
	}

	// isdigit() is slower (may be) because firstly it needs to find given symbol in table and only then it sees prewritten "isdigit" instruction to this symbol

	if (ch_dirt_input[0] == '-' || ch_dirt_input[0] >= '0' && ch_dirt_input[0] <= '9') { // Checks if first item in usr_inpt[] is '-' and digit after it
		for (int i = 1; i < len; ++i) {                                                  // Iterating from 1 (second of usr_inpt) to length of ch_dirt_input

			if (ch_dirt_input[i] >= '0' && ch_dirt_input[i] <= '9') continue;            // If item is number continues iterating

			if (allow_fraction) {
				if (ch_dirt_input[i] == '.') {                                           // If item is dot adding it to i_dot_count
					++i_dot_count;
					if (i_dot_count > 1) {                                               // And if there is more then one dot throws "Not valid input" code
						printf("\nNot valid input. Enter valid number.");
						return false;
					}
				}
				else if (ch_dirt_input[i] == ',') {                                      // If item is coma throws "not valid coma" code
					printf("\nChar ',' not for float. Use '.' instead.");
					return false;
				}
				else {                                                                   // If item is not number or dot throws "Not valid input" code
					printf("\nNot valid input. Enter valid number.");
					return false;
				}
			}
			else {
				printf("\nNot valid input. Enter whole number.");
				return false;
			}
			
		}
	}
	else {
		printf("\nNot valid input. Enter valid number.");
		return false;
	}
	return true;
}
// END



// Array input handler
Operation_code array_input_handler(int& iter, int* p_i_input_array, int i_array_size, int i_max_element_size) {
	char ch_input[17];

	scanf_s("%16s", ch_input, 17);

	Operation_code check_change_trigger = change_menu(ch_input);
	if (check_change_trigger) return check_change_trigger;

	bool valid_element_size = true;
	if (is_correct_input(ch_input, 0) && (valid_element_size = my_abs(atoi(ch_input)) <= i_max_element_size)) {
		p_i_input_array[iter] = atoi(ch_input);
	}
	else {
		if (!valid_element_size) {
			return Not_val_size;
		}
		return Not_val_num;
	}
	return Good;
}
// END



// String input handler
int string_input_handler(char** p_ch_destination, size_t& string_size, size_t type_size) { // Pointer on pointer to not to lose array start, when reallocating it
	bool b_memory_inicialize_fail = false;

	char buffer[129];                                                                      // Chunk of user input
	char* copy_string{};                                                                   // To catch realloc fail

	while (fgets(buffer, 129, stdin)) {
		size_t buffer_size = strlen(buffer);

		string_size += buffer_size;

		copy_string = (char*)realloc(*p_ch_destination, string_size * type_size);          // Resizing string container

		if (copy_string == NULL) {
			b_memory_inicialize_fail = true;
			break;
		}

		*p_ch_destination = copy_string;

		strcat_s(*p_ch_destination, string_size, buffer);                                  // Safely putting chunk after last element in it
	}

	return b_memory_inicialize_fail ? 1 : 0;
}
// END