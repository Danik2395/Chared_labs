//
// Зачарованные_лабы.cpp
//
//      Author:  Kalenkovich Daniil Alekseevich
//
// Main file of Зачарованные лабы project.
//


#include "my_lib.h"
#include "side_func.h"
#include <cstdio> 
#include <cmath>
#include <cstdlib>		// For atoi(), atof()
#include <windows.h>	// For operationts with console
#include <conio.h>		// For _getch
using namespace std;


// Input checkers

bool correct_input_double(const char* ch_dirt_inp) {
	int i_dot_count = 0;
	int len = my_strlen(ch_dirt_inp);


	if (len == 0) {       // Checking if there is something to check
		printf("\nNo input. Input number. 6");
		return false;
	}

	if (buffer_clean()) { // Cleans buffer, if there was more than 16 bytes, and giving exception
		printf("\nSorry, low memory machine does not support more than 16 bytes input :(\nInput supported value.");
		return false;
	}

	if (ch_dirt_inp[0] == '-' || ch_dirt_inp[0] >= '0' && ch_dirt_inp[0] <= '9') { // Checks if first item in usr_inpt[] is '-' or number
		for (int i = 1; i < len; ++i) {                                            // Iterating from 1 (second of usr_inpt) to length of ch_dirt_inp
			char ch_current = ch_dirt_inp[i];

			if (ch_current >= '0' && ch_current <= '9') continue;                  // If item is number continues iterating

			else if (ch_current == '.') {                                          // If item is dot adding it to i_dot_count
				++i_dot_count;
				if (i_dot_count > 1) {                                             // And if there is nome then one dot throws "Not valid input" code
					printf("\nNot valid input. Enter valid number. 1");
					return false;
				}
			}
			else if (ch_current == ',') {                                          // If item is coma throws "not valid coma" code
				printf("\nChar ',' not for float. Use '.' instead. 2");
				return false;
			}
			else {                                                                 // If item is not number or dot throws "Not valid input" code
				printf("\nNot valid input. Enter valid number. 3");
				return false;
			}
		}
	}
	else {
		printf("\nNot valid input. Enter valid number. 4");
		return false;
	}
	return true;
}


bool correct_input_int(const char* ch_dirt_inp) {
	int len = my_strlen(ch_dirt_inp);


	if (len == 0) {       // Checking if there is something to check
		printf("\nNo input. Input number. 6");
		return false;
	}

	if (buffer_clean()) { // Cleans buffer, if there was more than 64 bytes, and giving exception
		printf("\nSorry, low memory machine does not support more than 16 bytes input :(\nInput supported value.");
		return false;
	}

	if (ch_dirt_inp[0] == '-' || ch_dirt_inp[0] >= '0' && ch_dirt_inp[0] <= '9') { // Checks if first item in usr_inpt[] is '-' or number
		for (int i = 1; i < len; ++i) {                                            // Iterating from 1 (second of usr_inpt) to length of ch_dirt_inp
			char ch_current = ch_dirt_inp[i];

			if (ch_current >= '0' && ch_current <= '9') continue;                  // If item is number continues iterating

			else {                                                                 // If item is not number throws "Not valid input" code
				printf("\nNot valid input. Enter whole number. 3");
				return false;
			}
		}
	}
	else {
		printf("\nNot valid input. Enter whole number. 4");
		return false;
	}
	return true;
}
// END



// Input handlers
bool input_handler(const char *ch_text, double& d_outside_var) { // For doubles
	char ch_input[17];

	
	while (1) {
		printf("%s", ch_text);            // Displays text from another function
		scanf_s("%16s", ch_input, 17);

		if (quit(ch_input)) return false;

		else if (correct_input_double(ch_input)) {
			d_outside_var = atof(ch_input); // If input is valid converts ch_inpt to double parametr
			return true;
		}
	}
}


bool input_handler(const char *ch_text, int& d_outside_var) { // For ints
	char ch_input[17];


	while (1) {
		printf("%s", ch_text);            // Displays text from another function
		scanf_s("%16s", ch_input, 17);

		if (quit(ch_input)) return false;

		else if (correct_input_int(ch_input)) {
			d_outside_var = atoi(ch_input); // If input is valid converts ch_inpt to int parametr
			return true;
		}
	}
}
// END



// Laboratory work 1, variant 3
void lab_1() {
	while (1) {
		double d_x{};
		if (!input_handler("\nInput X (or quit [q]):\n", d_x)) {
			system("cls");
			break;
		}
		system("cls");

		double d_y{};
		if (!input_handler("\nInput Y (or quit [q]):\n", d_y)) {
			system("cls");
			break;
		}
		system("cls");

		double d_z{};
		while (2) {
			if (!input_handler("\nInput Z (or quit [q]):\n", d_z)) {
				system("cls");
				return;
			}
			
			if (d_z == 0) {
				puts("\nDeterminator can not be zero. Input non zero number.");
			}
			else {
				system("cls");
				break;
			}
		}
		
		
		double d_dwn1{};
		if ((d_dwn1 = 1 + d_x * d_x * d_y * d_y) == 0) { // Calculates determinator to check if it's not zero and gives it to d_dwn1
			printf("\nDenominator equals zero when X and Y is %.5f and %.5f.", d_x, d_y);

			puts("\n\n\nWant to continue? [Y/N]");
			if (YN()) {
				system("cls");
				continue;
			}
			else {
				system("cls");
				break;
			} 
		}

		double d_dwn2{};
		if ((d_dwn2 = fabs(d_x - 2 * d_y / d_dwn1)) == 0) { // Calculates determinator to check if it's not zero and gives it to d_dwn1
			printf("\nDenominator equals zero when X and Y is %.5f and %.5f.", d_x, d_y);

			puts("\n\n\nWant to continue? [Y/N]");
			if (YN()) {
				system("cls");
				continue;
			}
			else {
				system("cls");
				break;
			}
		}


		printf("\nCalculate [1 + sin(X + Y)^2] * X^|Y|  /  |X - 2Y / 1 + X^2 * Y^2|  +  cos[arctg(1 / Z)]^2? [Y/N]\n\n"
				 "Your X = %10.5f\n"
				 "Your Y = %10.5f\n"
				 "Your Z = %10.5f\n", d_x, d_y, d_z);

		if (YN()) {
			// V = [1 + sin(X + Y)^2] * X^|Y|  /  |X - 2Y / 1 + X^2 * Y^2|  +  cos[arctg(1 / Z)]^2
			double d_v = (1 + pow(sin(d_x + d_y), 2)) * pow(d_x, fabs(d_y)) / d_dwn2 + pow(cos(atan(1 / d_z)), 2);

			system("cls");
			Sleep(700);
			printf(".");
			Sleep(100);
			printf(".");
			Sleep(100);
			printf(".");
			system("cls");

			printf("\nV = [1 + sin(X + Y) ^ 2] * X ^ | Y|  /  |X - 2Y / 1 + X ^ 2 * Y ^ 2 | + cos[arctg(1 / Z)] ^ 2\n\n"
				   "X = %10.5f\n"
				   "Y = %10.5f\n"
				   "Z = %10.5f\n", d_x, d_y, d_z);
			printf("\nHere is your answer: %.5f", d_v);
		}
		else {
			system("cls");
			break;
		}

		puts("\n\n\nWant to continue? [Y/N]");
		if (YN()) {
			system("cls");
			continue;
		}
		else {
			system("cls");
			break;
		}
	}
}
// END



// Laboratory work 2, variant 12
void lab_2() {
	while (1) {
		double d_z{}, d_x{};
		const char* ch_x_shw = "";
		if (!input_handler("\nX_1 = Z^2 + 1;         Z <= 1\nX_2 = 1 / sqrt(Z - 1); Z >  1\n\nInput Z (or quit [q]):\n", d_z)) {
			system("cls");
			break;
		}
		else {
			printf("%f", d_z);
			if (d_z > 1) {
				d_x = 1 / sqrt(d_z - 1);
				ch_x_shw = "X = 1 / sqrt(Z - 1)";
			}			
			else {
				d_x = d_z * d_z + 1;
				ch_x_shw = "X = Z^2 + 1";
			}
		}
		system("cls");

		double d_fx{};
		const char* ch_fx_shw = "";
		while (2) {
			puts("\nChoose function for X (or quit [q])\n\nf(2X)  [1]\nf(X^2) [2]\nf(X/3) [3]\n\nFunction:");
			
			switch (_getch()) {
			case '1':
				d_fx = d_x * 2;
				ch_fx_shw = "(2X)";
				break;

			case '2':
				d_fx = d_x * d_x;
				ch_fx_shw = "(X^2)";
				break;

			case '3':
				d_fx = d_x / 3;
				ch_fx_shw = "(X/3)";
				break;

			case 'q':
			case 'Q':
				system("cls");
				return;

			default:
				printf("\nNot valid input.");
				continue;
			}
			break;
		}
		system("cls");
		
		// Another variant of switch
		/*
		//Пишу русскими буквами, почему я так не сделал:
		//	Пример: Вы работаете на заводе по производству джинс и оперируете стиральными машинами.
		//	   Но, когда нужно было выбрать режим стирки, чтобы получить определённый вид джинс, вы случайно
		//	   нажали не ту кнопку или что-то другое, а стиралка вам выдаёт: "Вы нажади не туда, поэтому будем стирать по циклу номер 1!" --,
		//	   хотя вам нужен был цикл номер 3. 
		//	   И вся партия джинс получилась не такой, как хотел заказчик, потому что какой-то программист добавил режим стирки по умолчанию, при неверном вводе.
		//	   Вас уволят.

		//Я могу сделать так, но не понимаю зачем. Как по мне, программа должна быть понятна пользователю, а не за него выбирать, что считать.
		

		puts("\nChoose function for X (or quit [q])\n\nf(2X)  [1]\nf(X^2) [2]\nf(X/3) [3]\n\nFunction:");

		double d_fx{};
		const char* ch_fx_shw = "";
		switch (_getch()) {
		case '1':
			d_fx = d_x * 2;
			ch_fx_shw = "Your function is f(2X)";
			break;

		case '2':
			d_fx = d_x * d_x;
			ch_fx_shw = "Your function is f(X^2)";
			break;

		case '3':
			d_fx = d_x / 3;
			ch_fx_shw = "Your function is f(X/3)";
			break;

		case 'q':
		case 'Q':
			system("cls");
			break;

		default:
			d_fx = d_x * 2;
			ch_fx_shw = "Your function is f(2X)";
			system("cls");
			puts("\nNot valid input. Default will be f(2X).\n\nEnter to continue");
			(void)_getch();
		}
		system("cls");*/

		double d_a{};
		if (!input_handler("\nInput A (or quit [q]):\n", d_a)) {
			system("cls");
			break;
		}
		system("cls");

		double d_c{};
		if (!input_handler("\nInput C (or quit [q]):\n", d_c)) {
			system("cls");
			break;
		}
		system("cls");

		printf("\nCalculate A * sin(%s^2 - 1)^3 + c * ln(|X|) + e^X ? [Y/N]\n\n"
			"Your A = %10.5f\n"
			"Your C = %10.5f\n"
			"Your Z = %10.5f\n\n"
			"Your %s\n"
			"Your function is f%s\n", ch_fx_shw, d_a, d_c, d_z, ch_x_shw, ch_fx_shw);

		if (YN()) {
			// a * sin(f_x ^ 2 - 1)^3 + c * ln(|x|) + e^x
			double d_y = d_a * pow(sin(d_fx * d_fx - 1), 3) + d_c * log(fabs(d_x)) + exp(d_x);

			system("cls");
			Sleep(100);
			printf(".");
			Sleep(1200);
			printf(".");
			Sleep(1200);
			printf(".");
			Sleep(200);
			system("cls");

			printf("\nY = A * sin(%s^2 - 1)^3 + c * ln(|X|) + e^X\n\n"
				   "A = %10.5f\n"
				   "C = %10.5f\n"
				   "Z = %10.5f\n\n"
				   "%s\n"
				   "Function is f%s\n", ch_fx_shw, d_a, d_c, d_z, ch_x_shw, ch_fx_shw);
			printf("\nHere is your answer: %.5f", d_y);
		}
		else {
			system("cls");
			break;
		}

		puts("\n\n\nWant to continue? [Y/N]");
		if (YN()) {
			system("cls");
			continue;
		}
		else {
			system("cls");
			break;
		}
	}
}
// END



// Laboratory work 3, variant 12 (and fourth also)

void Out_Rez_lab_3(double d_x, double d_b, double d_h, int i_n) {
	printf("\nHere is S(X), Y(X) and |Y(X) - S(X)| for every X from A to B with H step till N member\n\n"
		"A = %10.5f\n"
		"B = %10.5f\n"
		"H = %10.5f\n"
		"N = %4d\n\n\n", d_x, d_b, d_h, i_n);

	puts("   X           Y(X)          S(X)          |Y(X) - S(X)|\n");

	for (int i = 1; i = (d_b - d_x) / d_h + 1; ++i) { // Handling stacking of float numbers inaccuracies (ex. 0.100000000000000000000000561563254732169347...)
		double d_s{}, d_y{}, d_fabs{}, d_dwn1{};      // d_fabs{} for |Y(X) - S(x)|, d_dwn1{} for (2k)! in S(X)


		d_y = (1 - d_x * d_x / 2) * cos(d_x) - d_x * sin(d_x) / 2;

		for (int k = 0; k <= i_n; ++k) {              // Internal 'for' for sigma Σ
			d_dwn1 = 1;

			for (int i = 2 * k; i > 0; --i) {         // From 2*k to 1 with step 1 multiplying every number. Aka factorial
				d_dwn1 *= i;
			}

			d_s += pow(-1, k) * (2 * k * k + 1) * pow(d_x, 2 * k) / d_dwn1;
		}

		d_fabs = fabs(d_y - d_s);

		printf("%7.3f   %11.5f   %11.5f   %11.5f\n\n", d_x, d_y, d_s, d_fabs);

		d_x += d_h;
	}

	//for (d_x; d_x <= d_b; d_x += d_h) {          // External 'for' for every x
	//	double d_s{}, d_y{}, d_fabs{}, d_dwn1{}; // d_fabs{} for |Y(X) - S(x)|, d_dwn1{} for (2k)! in S(X)


	//	d_y = (1 - d_x * d_x / 2) * cos(d_x) - d_x * sin(d_x) / 2;

	//	for (int k = 0; k <= i_n; ++k) {         // Internal 'for' for sigma Σ
	//		d_dwn1 = 1;

	//		for (int i = 2 * k; i > 0; --i) {    // From 2*k to 1 with step 1 multiplying every number. Aka factorial
	//			d_dwn1 *= i;
	//		}

	//		d_s += pow(-1, k) * (2 * k * k + 1) * pow(d_x, 2 * k) / d_dwn1;
	//	}

	//	d_fabs = fabs(d_y - d_s);

	//	printf("%7.3f   %11.5f   %11.5f   %11.5f\n\n", d_x, d_y, d_s, d_fabs);
	//}
}


void lab_3() {
	while (1) {
		double d_a{};
		if (!input_handler("\nInput A (or quit[q]) :\n", d_a)) {
			system("cls");
			break;
		}
		system("cls");
		
		double d_b{};
		if (!input_handler("\nInput B (or quit[q]) :\n", d_b)) { // Very cross variable!!!  d_b
			system("cls");
			break;
		}
		system("cls");

		double d_h{};
		if (!input_handler("\nInput H (or quit[q]) :\n", d_h)) {
			system("cls");
			break;
		}
		system("cls");

		int i_n{};
		while (2) {
			if (!input_handler("\nInput N (or quit[q]) :\n", i_n)) {
				system("cls");
				return;
			}
			else if (i_n < 3 || i_n > 9) {
				printf("\nInvalid range. For better results 3 <= N <= 9 ");
			}
			else break;
		}
		system("cls");

		printf("\nFor conditions check .txt\n\n"
			   "Calculate S(X), Y(X) and |Y(X) - S(X)| for every X from A to B with H step till N member? [Y/N]\n\n"
			   "Your A = %10.5f\n"
			   "Your B = %10.5f\n"
			   "Your H = %10.5f\n"
			   "Your N = %4d\n",   d_a, d_b, d_h, i_n);

		if (YN()) {
			system("cls");
			Sleep(500);
			printf(".");
			Sleep(800);
			printf(".");
			Sleep(900);
			printf(".");
			Sleep(400);
			system("cls");

			Out_Rez_lab_3(d_a, d_b, d_h, i_n);
		}
		else {
			system("cls");
			break;
		}

		puts("\n\n\nWant to continue? [Y/N]");
		if (YN()) {
			system("cls");
			continue;
		}
		else {
			system("cls");
			break;
		}
	}
}
// END



// Main -- menu
int main() {
	while (1) {
		puts("\nlab 1(3) [1], lab 2(12) [2], lab 3(12) [3], exit [esc]");
		
		switch (_getch()) {
		case '1':
			system("cls");
			lab_1();
			break;

		case '2':
			system("cls");
			lab_2();
			break;

		case '3':
			system("cls");
			lab_3();
			break;

		case 27:
			system("cls");
			puts("\nDo you want to exit? [Y/N]");

			if (YN()) exit(0);

			else {
				system("cls");
				continue;
			}

		default:
			system("cls");
			printf("\nNot valid input.");
		}
	}
}
// END