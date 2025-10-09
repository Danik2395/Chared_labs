//
// sideFunc.h
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Side functions header.
//
#pragma once

#define user_continue_usage()\
puts("\n\n\nWant to continue? [Y/N]");\
if (YN()) {\
	system("cls");\
	continue;\
}\
else {\
	system("cls");\
	break;\
}\


// Returns true if input "q" or "Q"
bool quit(const char*);

// "Eats" buffer and, if it's overfilled, returns true
bool buffer_clean();

// _getch()
// Y = true, N = false
bool YN();