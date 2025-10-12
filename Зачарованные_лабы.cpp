//
// Зачарованные_лабы.cpp
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Main file of Зачарованные лабы project.
//


#include "my_lib.h"
#include "side_functions.h"
#include "operating_functions.h"
#include <cstdio>       // For _getchar()
#include <cmath>
#include <cstdlib>		// For atoi(), atof()
#include <windows.h>	// For operationts with console
#include <conio.h>		// For _getch()
#include <limits>
using namespace std;


// Laboratory work 1, variant 3
static void lab_1() {
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

		if (is_near_zero(d_x) && d_y < 0) {           // We cannot power zero in negative number
			system("cls");
			printf("\nZero can not be in negative power.");
			continue;
		}

		double d_fraction_of_Y = my_fmod(d_y, 1);     // We cannot take root of negative number
		if (d_x < 0 && my_fabs(d_fraction_of_Y) > 0 && d_fraction_of_Y != my_NaN) {
			system("cls");
			printf("\nCan not take root of negative number.\nTry again with another values.");
			continue;
		}
		else if (d_fraction_of_Y == my_NaN) {
			system("cls");
			printf("\nInternal error occurred.\nTry again with another values.");
		}

		double d_power_X_in_Y = pow(d_x, fabs(d_y));  // If powering is too large, error
		if (d_power_X_in_Y > DBL_MAX) {
			system("cls");
			printf("\nX^Y is too large.\nTry again with another values.");
			continue;
		}

		double d_z{};
		while (2) {
			if (!input_handler("\nInput Z (or quit [q]):\n", d_z)) {
				system("cls");
				return;
			}
			
			if (is_near_zero(d_z)) {
				puts("\nDeterminator can not be zero. Input non zero number.");
			}
			else {
				system("cls");
				break;
			}
		}
				
		double d_dwn1{};
		if (is_near_zero(d_dwn1 = 1 + d_x * d_x * d_y * d_y)) { // Calculates determinator to check if it's not zero and gives it to d_dwn1
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
		if (is_near_zero(d_dwn2 = fabs(d_x - 2 * d_y / d_dwn1))) { // Calculates determinator to check if it's not zero and gives it to d_dwn1
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

		if (!YN()) {
			system("cls");
			break;
		}
		
		// V = [1 + sin(X + Y)^2] * X^|Y|  /  |X - 2Y / 1 + X^2 * Y^2|  +  cos[arctg(1 / Z)]^2
		double d_v = (1 + pow(sin(d_x + d_y), 2)) * d_power_X_in_Y / d_dwn2 + pow(cos(atan(1 / d_z)), 2);

		system("cls");
		Sleep(700);
		printf(".");
		Sleep(100);
		printf(".");
		Sleep(100);
		printf(".");
		system("cls");

		printf("\nV = [1 + sin(X + Y) ^ 2] * X ^ |Y|  /  |X - 2Y / 1 + X ^ 2 * Y ^ 2 | + cos[arctg(1 / Z)] ^ 2\n\n"
			"X = %10.5f\n"
			"Y = %10.5f\n"
			"Z = %10.5f\n", d_x, d_y, d_z);
		printf("\nHere is your answer: %.5f", d_v);

		USER_CONTINUE_USAGE()
	}
}
// END



// Laboratory work 2, variant 12
static void lab_2() {
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
				if (d_z < -25) {
					system("cls");
					printf("\nUndefined calculations. Z could be approximately -25.\nInput again for better results.");
					continue;
				}
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
		//	   нажали не ту кнопку или что-то другое, а стиралка вам выдаёт: "Вы нажали не туда, поэтому будем стирать по циклу номер 1!" --,
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

		printf("\nCalculate A * sin(%s^2 - 1)^3 + C * ln(|X|) + e^X ? [Y/N]\n\n"
			"Your A = %10.5f\n"
			"Your C = %10.5f\n"
			"Your Z = %10.5f\n\n"
			"Your %s\n"
			"Your function is f%s\n", ch_fx_shw, d_a, d_c, d_z, ch_x_shw, ch_fx_shw);

		if (!YN()) {
			system("cls");
			break;
		}

		// a * sin(f_x ^ 2 - 1)^3 + c * ln(|x|) + e^x
		double d_y = d_a * pow(sin(d_fx * d_fx - 1), 3) + d_c * log(fabs(d_x)) + exp(d_x);

		system("cls");
		Sleep(700);
		printf(".");
		Sleep(200);
		printf(".");
		Sleep(150);
		printf(".");
		system("cls");

		printf("\nY = A * sin(%s^2 - 1)^3 + C * ln(|X|) + e^X\n\n"
			"A = %10.5f\n"
			"C = %10.5f\n"
			"Z = %10.5f\n\n"
			"%s\n"
			"Function is f%s\n", ch_fx_shw, d_a, d_c, d_z, ch_x_shw, ch_fx_shw);
		printf("\nHere is your answer: %.5f", d_y);

		USER_CONTINUE_USAGE()
	}
}
// END



// Laboratory work 3, variant 12 (and fourth also)

static void Out_Rez_lab_3(double d_x, double d_y, double d_s, double d_fabs, int view_answer) {
	switch (view_answer) {
	case 1: // All
		printf("%7.3f   %11.5f   %11.5f   %11.5f\n\n", d_x, d_y, d_s, d_fabs);
		break;

	case 2: // S(X)
		printf("%7.3f   %11.5f\n\n", d_x, d_s);
		break;

	case 3: // Y(X)
		printf("%7.3f   %11.5f\n\n", d_x, d_y);
		break;

	case 4: // |Y(X) - S(X)|
		printf("%7.3f   %11.5f\n\n", d_x, d_fabs);
		break;
	}
}


static void lab_3() {
	while (1) {
		double d_a{};
		if (!input_handler("\nInput A (or quit[q]) :\n", d_a)) {
			system("cls");
			break;
		}
		system("cls");

		if (d_a > 1000 || d_a < -1000) {
			printf("For better results A and B range is +-1000\nTry again with valid range.");
			continue;
		}
		
		double d_b{};
		while (2) {
			if (!input_handler("\nInput B (or quit[q]) :\n", d_b)) { // Very cross variable!!!  d_b
				system("cls");
				return;
			}

			if (d_b > 1000 || d_b < -1000) {
				printf("For better results A and B range is +-1000\nTry again with valid range.");
				continue;
			}
			break;
		}
		system("cls");

		if (is_near_zero(my_fabs(d_b - d_a))) {             // If a = b, error
			system("cls");
			printf("\nNot valid range. There must be a gap between A and B.");
			continue;
		}

		double d_h{};
		while (2) {
			if (!input_handler("\nInput H (or quit[q]) :\n", d_h)) {
				system("cls");
				return;
			}

			if (d_b > d_a && d_h < 0 || d_b < d_a && d_h > 0) { // If a <-h- b, error
				system("cls");
				printf("\nNot valid input. Steps moving backwards. Need to move from A to B");
				continue;
			}
			break;
		}
		system("cls");

		double d_fraction = my_fmod(d_b - d_a, d_h);        // If steps is mot whole number, error
		if (d_fraction != my_NaN && my_fabs(d_fraction) > 0) {
			system("cls");
			printf("\nNot valid input. Incorrect steps set.\nTry again with another values.");
			continue;
		}
		else if (d_fraction == my_NaN) {
			system("cls");
			printf("\nInternal error occurred.\nTry again with another values.");
			continue;
		}

		int i_n{};
		while (2) {
			if (my_fabs(d_a) >= 1 || my_fabs(d_b) >= 4) {
				printf("\nFor better results N > 7");
			}

			if (!input_handler("\nInput N (or quit[q]) :\n", i_n)) {
				system("cls");
				return;
			}
			else if (i_n <= 0) {
				system("cls");
				printf("\nNot valid number of members. N can not be zero or below it.");
				continue;
			}
			break;
		}
		system("cls");

		printf("\nS(X), Y(X) or |Y(X) - S(X)| for every X from A to B with H step till N member.\n\n"
			   "Your A = %10.5f\n"
			   "Your B = %10.5f\n"
			   "Your H = %10.5f\n"
			   "Your N = %4d\n\n\n"
			   "What to calculate? (or quit [q])\n\n"
			   "All           [1]\n"
			   "S(X)          [2]\n"
			   "Y(X)          [3]\n"
			   "|Y(X) - S(X)| [4]\n", d_a, d_b, d_h, i_n);

		int view_answer{};
		const char* text_for_answer = "";
		const char* text_for_table = "";
		while(2) {
			switch (_getch()) {
			case '1': // All
				view_answer = 1;
				text_for_answer = "S(X), Y(X) and |Y(X) - S(X)|";
				text_for_table = "   X           Y(X)          S(X)          |Y(X) - S(X)|";
				break;

			case '2': // S(X)
				view_answer = 2;
				text_for_answer = "S(X)";
				text_for_table = "   X           S(X)";
				break;

			case '3': // Y(X)
				view_answer = 3;
				text_for_answer = "Y(X)";
				text_for_table = "   X           Y(X)";
				break;

			case '4':  // |Y(X) - S(X)|
				view_answer = 4;
				text_for_answer = "|Y(X) - S(X)|";
				text_for_table = "   X           |Y(X) - S(X)|";
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
		Sleep(700);
		printf(".");
		Sleep(200);
		printf(".");
		Sleep(100);
		printf(".");
		system("cls");

		printf("\nHere is %s for every X from A to B with H step till N member\n\n"
			"A = %10.5f\n"
			"B = %10.5f\n"
			"H = %10.5f\n"
			"N = %4d\n\n\n", text_for_answer, d_a, d_b, d_h, i_n);

		printf("%s\n\n", text_for_table);

		double steps = (d_b - d_a) / d_h + 1;
		for (int i = 1; i <= steps; ++i, d_a += d_h) {
			double d_m{ 1 }, d_s{}, d_y{}, d_fabs{}; // d_fabs{} for |Y(X) - S(x)|

			if (view_answer == 1 || view_answer == 3 || view_answer == 4) {
				d_y = (1 - d_a * d_a / 2) * cos(d_a) - d_a * sin(d_a) / 2;
			}

			if (view_answer == 1 || view_answer == 2 || view_answer == 4) {
				for (int k = 1; k <= i_n; ++k) {         // Internal 'for' for sigma Σ. k = 1, because, when k = 0 first member d_m = 1
					d_s += d_m;

					// M_n = -1 * X^2 * (2 * K^2 + 1) / (4 * K^2 - 2 * K) / (2 * K^2 - 4 * K + 3) * M_n-1
					d_m *= -1 * d_a * d_a * (2 * k * k + 1) / (4 * k * k - 2 * k) / (2 * k * k - 4 * k + 3);
				}
			}
		
			if (view_answer == 1 || view_answer == 4) {
				d_fabs = fabs(d_y - d_s);
			}

			Out_Rez_lab_3(d_a, d_y, d_s, d_fabs, view_answer);
		}

		USER_CONTINUE_USAGE()
	}
}
// END



// Laboratory work 5, variant 12
static void lab_5() {
	while (1) {
		int i_array_size{};
		if (!input_handler("\nInput size of array (or quit[q]) :\n", i_array_size)) {
			system("cls");
			break;
		}
		system("cls");

		if (i_array_size > 10000 || i_array_size <= 0) {
			puts("\nInvalid size. Supported size is from 1 to 10000");
			continue;
		}
	
		puts("How you want to create array? (or quit [q])\n\n"
			"Manually [1]\n"
			"Randomly [2]");

		bool manual_input = false;
		while (2) {
			switch (_getch()) {
			case '1':
				manual_input = true;
				break;

			case '2':
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

		if (manual_input && i_array_size > 12) {
			printf("\nYou want to enter %d element(s) manually? [Y/N]\n", i_array_size);

			if (!YN()) manual_input = false;
		}
		system("cls");
				
		int* p_i_array = (int*)calloc(i_array_size, sizeof(int)); // Points on array start. Calloc for minimizing errors
		if (p_i_array == NULL) {
			system("cls");

			printf("Internal error occurred. Try again.\n");

			Sleep(1000);

			continue;
		}

		if (!manual_input) {
			generate_seed();

			puts("\nGenerating...");

			Sleep(1000);

			system("cls");

			puts("");

			for (int i = 0; i < i_array_size; ++i) {
				p_i_array[i] = my_random(100, 68);

				printf("%d ", p_i_array[i]);
			}
			Sleep(1000);
		}
		else {
			if (!array_input_handler("\nPrefer Enter after every member."
									 "\nWill clear all input after mistaken number, if input with Space."
									 "\n\nInput array. (or quit [q])\n\n", p_i_array, i_array_size, 200000)) {
				system("cls");
				free(p_i_array);
				break;
			}
		}
		system("cls");

		puts("Calculate sum of elements in array from first positive member? [Y/N]\n");

		printf("[");
		for (int i = 0; i < i_array_size - 1; ++i) {
			printf("%d, ", p_i_array[i]);
		}
		printf("%d", p_i_array[i_array_size - 1]);
		printf("]\n");

		if (!YN()) {
			system("cls");
			free(p_i_array);
			break;
		}
		
		system("cls");
		Sleep(500);
		printf(".");
		Sleep(100);
		printf(".");
		Sleep(450);
		printf(".");
		system("cls");
		
		bool has_positive = false;
		bool has_afters = false;
		int i_sum_from_positive{};
		for (int i = 0; i < i_array_size; ++i) {
			if (p_i_array[i] > 0) {
				has_positive = true;

				if (i + 1 < i_array_size) {
					has_afters = true;

					for (++i; i < i_array_size; ++i) {
						i_sum_from_positive += p_i_array[i];
					}
				}
			}
		}

		if (!has_positive) {
			puts("\nArray has not got positive numbers.\n");
		}
		else if (!has_afters && has_positive) {
			puts("\nPositive number is the last element in the array\n");
		}
		else {
			puts("Sum of elements in the array from first positive member.\n");

			printf("[");
			for (int i = 0; i < i_array_size - 1; ++i) {
				printf("%d, ", p_i_array[i]);
			}
			printf("%d", p_i_array[i_array_size - 1]);
			printf("]\n");

			printf("\nHere is your answer: %d", i_sum_from_positive);
		}

		USER_CONTINUE_USAGE();
	}
}
// END



// Main -- menu
int main() {
	while (1) {
		puts("\nlab 1(3)  [1]\n"
			   "lab 2(12) [2]\n"
			   "lab 3(12) [3]\n"
			   "lab 5(12) [5]\n"
			   "exit      [esc]\n");

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

		case '5':
			system("cls");
			lab_5();
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