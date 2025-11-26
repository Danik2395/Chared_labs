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

		default: continue;
		}
	}
}