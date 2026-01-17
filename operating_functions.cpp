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
	short i_dot_count = 0;

	if (len == 0) {       // Checking if there is something to check
		printf("\nNo input. Input number.");
		return false;
	}

	//if (buffer_clean()) { // Cleans buffer, if there was more than 16 bytes, and giving exception
	//	printf("\nSorry, low memory machine does not support more than 16 bytes input :(\nInput supported value.");
	//	return false;
	//}

	if (ch_dirt_input[0] == '-' && len == 1 || ch_dirt_input[0] == '-' && (ch_dirt_input[1] < '0' || ch_dirt_input[1] > '9')) {
		printf("\nNot valid input. Enter valid number."); // Checks if it is not only minus in input (or -. for example)
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
int array_input_handler(int& iter, int* p_i_input_array, int i_array_size, int i_max_element_size) {
	char ch_input[17];

	scanf_s("%16s", ch_input, 17);

	if (quit(ch_input)) return 1;

	bool valid_element_size = true;
	if (is_correct_input(ch_input, 0) && (valid_element_size = my_abs(atoi(ch_input)) <= i_max_element_size)) {
		p_i_input_array[iter] = atoi(ch_input);
	}
	else {
		if (!valid_element_size) {
			return 2;
		}
		return 3;
	}
	return 0;
}







//bool array_input_handler(const char* ch_text_to_display, int* p_i_input_array, int i_array_size, int i_max_element_size) {
//	char ch_input[17];
//
//	printf("%s", ch_text_to_display);
//
//	for (int i = 0; i < i_array_size; ++i) {
//		scanf_s("%16s", ch_input, 17);
//
//		if (quit(ch_input)) return false;
//
//
//		bool valid_element_size = true;
//		if (is_correct_input(ch_input, 0) && (valid_element_size = my_abs(atoi(ch_input)) <= i_max_element_size)) {
//			p_i_input_array[i] = atoi(ch_input);
//		}
//		else {
//			(void)buffer_clean();
//
//			if (!valid_element_size) {
//				printf("\nNot valid element size. Valid size is +-%d", i_max_element_size);
//			}
//
//			while (1) {
//				printf("\nInput from %d element again:\n", i + 1);
//				
//				scanf_s("%16s", ch_input, 17);
//
//				if (quit(ch_input)) return false;
//
//				if (is_correct_input(ch_input, 0) && (valid_element_size = my_abs(atoi(ch_input)) <= i_max_element_size)) {
//					p_i_input_array[i] = atoi(ch_input);
//					system("cls");
//					break;
//				}
//			}
//		}
//
//		system("cls");
//
//		printf("%s", ch_text_to_display);
//
//		for (int j = 0; j <= i; ++j) {
//			printf("%3d ", p_i_input_array[j]);
//		}
//	}
//
//	(void)buffer_clean();
//
//	return true;
//}
// END