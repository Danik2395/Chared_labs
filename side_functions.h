//
// sideFunc.h
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Side functions header.
//
#pragma once
#include "my_lib.h"

enum Operation_code {
	Good,
	First_iter,
	Quit,
	Back,
	Not_val_size,
	Not_val_num
};

#define USER_CONTINUE_USAGE()\
puts("\n\n\nWant to begin again? [Y/N]");\
if (YN()) {\
	system("cls");\
	continue;\
}\
else {\
	system("cls");\
	break;\
}\


// Returns Quit if input "q" or "Q"
// Returns Back if input "b" or "B"
inline Operation_code change_menu(const char* ch_t) {
	if (my_strcmp(ch_t, "q") || my_strcmp(ch_t, "Q")) return Quit;
	else if (my_strcmp(ch_t, "b") || my_strcmp(ch_t, "B")) return Back;
}

// "Eats" buffer and, if it's overfilled, returns true
bool buffer_clean();

// _getch()
// Y = true, N = false
bool YN();