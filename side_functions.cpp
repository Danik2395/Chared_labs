//
// sideFunc.cpp
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Side functions for laboratory work.
//
#include "side_functions.h"
#include "my_lib.h"
#include <cstdio>
#include <conio.h>


bool quit(const char* ch_t) {
	if (my_strcmp(ch_t, "q") || my_strcmp(ch_t, "Q")) return true;
	else return false;
}



bool buffer_clean() {
	int i_c{}, i_dbg_value = 0;


	while ((i_c = getchar()) != '\n' && i_c != EOF) ++i_dbg_value;

	if (i_dbg_value == 0) return false;

	else return true;
}



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
			//continue;
		}
	}
}