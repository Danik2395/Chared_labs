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
	No_code = -1,
	Good,
	First_iter,
	Quit,
	Quit_s,
	Back,
	Not_val_size,
	Not_val_num,
	Read_error
};

// Returns Quit if input "q" or "Q"
// Returns Back if input "b" or "B"
inline Operation_code change_menu(const char* ch_t, int i_allow_back = 0) {
	if (my_strcmp(ch_t, "q") || my_strcmp(ch_t, "Q")) return Quit;
	else if (i_allow_back && my_strcmp(ch_t, "b") || my_strcmp(ch_t, "B")) return Back;
	return Good;
}

// "Eats" buffer and, if it's overfilled, returns true
bool buffer_clean();

// _getch()
// Y = true, N = false
bool YN();

int clean_fgets(char* ch_str);