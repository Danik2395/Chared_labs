//
// my_lib.cpp
//
//      Author:  Kalenkovich Daniil Alekseevich
//
// Library of rewritten banned functions.
//


#include "my_lib.h"


// Returns string length
int my_strlen(const char* ch_array) {
	int i_string_len = 0;
	for (int i = 0; ch_array[i] != '\0'; ++i, ++i_string_len);
	return i_string_len;
}
//END



// Returns true if strings are equal
bool my_strcmp(const char* ch_array1, const char* ch_array2) {
	for (int i = 0; ch_array1[i] != '\0' && ch_array2[i] != '\0'; ++i) {
		if (ch_array1[i] != ch_array2[i]
			|| ch_array1[i] == '\0' && ch_array2[i] != '\0'
			|| ch_array2[i] == '\0' && ch_array1[i] != '\0') return false;
	}
	return true;
}
//END