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


// Input checker
bool is_correct_input(const char* ch_dirt_input, bool allow_fraction, bool error_message_true) {
	int len = my_strlen(ch_dirt_input);
	short i_dot_count = 0;

	if (len == 0) {       // Checking if there is something to check
		display_error_message("\nNo input. Input number.", error_message_true);
		return false;
	}

	if (buffer_clean()) { // Cleans buffer, if there was more than 16 bytes, and giving exception
		display_error_message("\nSorry, low memory machine does not support more than 16 bytes input : (\nInput supported value.", error_message_true);
		return false;
	}

	if (ch_dirt_input[0] == '-' && len == 1 || ch_dirt_input[0] == '-' && (ch_dirt_input[1] < '0' || ch_dirt_input[1] > '9')) {
		display_error_message("\nNot valid input. Enter valid number.", error_message_true); // Checks if it is not only minus in input (or -. for example)
		return false;
	}

	// Is digit is slower because firstly it needs to find given symbol in table and only then it sees prewritten "isdigit" instruction to this symbol

	if (ch_dirt_input[0] == '-' || ch_dirt_input[0] >= '0' && ch_dirt_input[0] <= '9') { // Checks if first item in usr_inpt[] is '-' and digit after it
		for (int i = 1; i < len; ++i) {                                                  // Iterating from 1 (second of usr_inpt) to length of ch_dirt_input

			if (ch_dirt_input[i] >= '0' && ch_dirt_input[i] <= '9') continue;            // If item is number continues iterating

			if (allow_fraction) {
				if (ch_dirt_input[i] == '.') {                                           // If item is dot adding it to i_dot_count
					++i_dot_count;
					if (i_dot_count > 1) {                                               // And if there is more then one dot throws "Not valid input" code
						display_error_message("\nNot valid input. Enter valid number.", error_message_true);
						return false;
					}
				}
				else if (ch_dirt_input[i] == ',') {                                      // If item is coma throws "not valid coma" code
					display_error_message("\nChar ',' not for float. Use '.' instead.", error_message_true);
					return false;
				}
				else {                                                                   // If item is not number or dot throws "Not valid input" code
					display_error_message("\nNot valid input. Enter valid number.", error_message_true);
					return false;
				}
			}
			else {
				display_error_message("\nNot valid input. Enter whole number.", error_message_true);
				return false;
			}
			
		}
	}
	else {
		display_error_message("\nNot valid input. Enter valid number.", error_message_true);
		return false;
	}
	return true;
}
// END