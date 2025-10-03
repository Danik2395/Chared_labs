//
// sideFunc.cpp
//
//      Author:  Kalenkovich Daniil Alekseevich
//
// Side functions for laboratory works.
//


#include "side_func.h"
#include "my_lib.h"
#include <cstdio>
#include <conio.h>


// Rerurns true if input "q" or "Q"
bool quit(const char* ch_t) {
	if (my_strcmp(ch_t, "q") || my_strcmp(ch_t, "Q")) return true;
	else return false;
}
// END



// "Eats" buffer and, if it's overfilled, returns true
bool buffer_clean() {
	int i_c, i_dbg_value = 0;


	while ((i_c = getchar()) != '\n' && i_c != EOF) ++i_dbg_value;

	if (i_dbg_value == 0) return false;

	else return true;
}
// END



// _getch()
// Y = true, N = false
bool YN() {
	while (1) {
		switch (_getch()) {
		case 'y':
		case 'Y':
			return true;

		case 'n':
		case 'N':
			return false;

		default:
			printf("\nNot valid input.\n");
			continue;
		}
	}
}
// END