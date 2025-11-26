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
#include <string.h>
#include <iostream>
using namespace std;

#define IS_CHAR_BINARY(ch_c) (ch_c == '0' || ch_c == '1')
#define IS_CHAR_SPLITTER(ch_c) (ch_c == '\n' || ch_c == ' ' || ch_c == '\t')


// Laboratory work 1, variant 3
static void lab_1() {
	while (1) {
		double d_x{};
		if (number_input_handler("\nInput X (or quit [q]):\n", d_x) != Good) {
			system("cls");
			break;
		}
		system("cls");

		double d_y{};
		if (number_input_handler("\nInput Y (or quit [q]):\n", d_y) != Good) {
			system("cls");
			break;
		}
		system("cls");

		if (is_near_zero(d_x) && d_y < 0) {           // We cannot power zero in negative number
			system("cls");
			printf("\nZero can not be in negative power.\n\n");
			Sleep(1500);
			continue;
		}

		double d_fraction_of_Y = my_fmod(d_y, 1);     // We cannot take root of negative number
		if (d_x < 0 && my_fabs(d_fraction_of_Y) > 0 && d_fraction_of_Y != my_NaN) {
			system("cls");
			printf("\nCan not take root of negative number.\nTry again with another values.\n\n");
			Sleep(1000);
			continue;
		}
		else if (d_fraction_of_Y == my_NaN) {
			system("cls");
			printf("\nInternal error occurred.\nTry again with another values.\n\n");
			Sleep(1000);
		}

		double d_power_X_in_Y = pow(d_x, fabs(d_y));  // If powering is too large, error
		if (d_power_X_in_Y > DBL_MAX) {
			system("cls");
			printf("\nX^Y is too large.\nTry again with another values.\n\n");
			Sleep(1000);
			continue;
		}

		double d_z{};
		while (2) {
			if (number_input_handler("\nInput Z (or quit [q]):\n", d_z) != Good) {
				system("cls");
				return;
			}
			
			if (is_near_zero(d_z)) {
				printf("\nDeterminator can not be zero. Input non zero number.\n\n");
			}
			else {
				system("cls");
				break;
			}
		}
		
		bool b_denominator_is_zero = false;
		double d_dwn1{};
		if (is_near_zero(d_dwn1 = 1 + d_x * d_x * d_y * d_y)) b_denominator_is_zero = true; // Calculates determinator to check if it's not zero and gives it to d_dwn1

		double d_dwn2{};
		if (is_near_zero(d_dwn2 = fabs(d_x - 2 * d_y / d_dwn1))) b_denominator_is_zero = true; // Calculates determinator to check if it's not zero and gives it to d_dwn2

		if (b_denominator_is_zero) {
			printf("\nDenominator equals zero when X and Y is %.5f and %.5f.", d_x, d_y);
			Sleep(1000);

			USER_CONTINUE_USAGE()
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
		if (number_input_handler("\nX_1 = Z^2 + 1;         Z <= 1\nX_2 = 1 / sqrt(Z - 1); Z >  1\n\n\nInput Z (or quit [q]):\n", d_z) != Good) {
			system("cls");
			break;
		}
		else {
			if (d_z > 1) {
				d_x = 1 / sqrt(d_z - 1);
				ch_x_shw = "X = 1 / sqrt(Z - 1)";
			}			
			else {
				if (d_z < -25) {
					system("cls");
					printf("\nUndefined calculations. Z could be approximately -25.\nInput again for better results.\n\n");
					continue;
				}
				d_x = d_z * d_z + 1;
				ch_x_shw = "X = Z^2 + 1";
			}
		}
		system("cls");

		double d_fx{};
		const char* ch_fx_shw = "";
		puts("\nChoose function for X (or quit [q])\n\nf(2X)  [1]\nf(X^2) [2]\nf(X/3) [3]\n\nFunction:");
		while (2) {		
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
		//	   нажали не ту кнопку или что-то другое, а стиралка вам выдаёт: "Вы нажали не туда, поэтому будем стирать по циклу номер 1!" -,
		//	   хотя вам нужен был цикл номер 3. 
		//	   И вся партия джинс получилась не такой, как хотел заказчик, потому что какой-то программист добавил режим стирки по умолчанию, при неверном вводе.
		//	   Вас уволят.

		//Можно сделать так, но не понимаю зачем. Как по мне, программа должна быть понятна пользователю, а не за него выбирать, что считать.
		

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
		if (number_input_handler("\nInput A (or quit [q]):\n", d_a) != Good) {
			system("cls");
			break;
		}
		system("cls");

		double d_c{};
		if (number_input_handler("\nInput C (or quit [q]):\n", d_c) != Good) {
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

static void Out_Rez_lab_3(double d_x, double d_y, double d_sum, double d_fabs, int i_view_answer) {
	switch (i_view_answer) {
	case 1: // All
		printf("%7.3f   %11.5f   %11.5f   %11.5f\n\n", d_x, d_y, d_sum, d_fabs);
		break;

	case 2: // S(X)
		printf("%7.3f   %11.5f\n\n", d_x, d_sum);
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
		if (number_input_handler("\nInput A (in range +-20) (or quit[q/b]) :\n", d_a) != Good) {
			system("cls");
			break;
		}
		system("cls");

		if (d_a > 20 || d_a < -20) {
			printf("For better results A and B are limited\nTry again with valid range.\n\n");
			continue;
		}
		
		double d_b{};
		while (2) {
			if (number_input_handler("\nInput B (in range +-20) (or quit[q/b]) :\n", d_b) != Good) { // Very cross variable!!!  d_b
				system("cls");
				return;
			}

			if (d_b > 20 || d_b < -20) {
				system("cls");
				printf("For better results A and B are limited\nTry again with valid range.\n\n");
				continue;
			}
			break;
		}
		system("cls");

		if (is_near_zero(my_fabs(d_b - d_a))) {                 // If a = b, error
			system("cls");
			printf("\nNot valid range. There must be a gap between A and B.\n\n");
			Sleep(1500);
			continue;
		}

		double d_h{};
		while (2) {
			if (number_input_handler("\nInput H (or quit[q/b]) :\n", d_h) != Good) {
				system("cls");
				return;
			}

			if (d_b > d_a && d_h < 0 || d_b < d_a && d_h > 0) { // If a <-h- b, error
				system("cls");
				printf("\nNot valid input. Steps moving backwards. Need to move from A to B\n\n");
				continue;
			}
			break;
		}
		system("cls");

		double d_fraction = my_fmod(d_b - d_a, d_h);            // If steps is mot whole number, error
		if (d_fraction != my_NaN && my_fabs(d_fraction) > 0) {
			system("cls");
			printf("\nNot valid input. Incorrect steps set.\nTry again with another values.\n\n");
			Sleep(1500);
			continue;
		}
		else if (d_fraction == my_NaN) {
			system("cls");
			printf("\nInternal error occurred.\nTry again with another values.\n\n");
			Sleep(1500);
			continue;
		}

		int i_n{};
		while (2) {
			if (my_fabs(d_a) >= 1 || my_fabs(d_b) >= 4) {
				printf("\nFor better results 10 < N <= 40");
			}

			if (number_input_handler("\nInput N from 1 to 20 (or quit[q/b]) :\n", i_n) != Good) {
				system("cls");
				return;
			}
			else if (i_n <= 0) {
				system("cls");
				printf("\nNot valid number of members. N can not be zero or below it.\n\n");
				continue;
			}
			else if (i_n > 40) {
				system("cls");
				printf("\nNot valid number of members. For better results N is limited.\n\n");
				continue;
			}
			break;
		}
		system("cls");
		
		int i_calculation_variant{ 0 };
		bool b_first_input = true;
		while (2) {                                             // Scope to calculate different thing
			if (b_first_input) {
				 printf("\nS(X), Y(X) or |Y(X) - S(X)| for every X from A to B with H step till N member.\n\n"
					    "Your A = %10.5f\n"
					    "Your B = %10.5f\n"
					    "Your H = %10.5f\n"
					    "Your N = %4d\n\n\n"
					    "What to calculate? (or quit [q])\n\n", d_a, d_b, d_h, i_n);
			}
			else printf("\nCalculate something else?\n\n");

				 printf("All           [1]\n"
				 	    "S(X)          [2]\n"
					    "Y(X)          [3]\n"
					    "|Y(X) - S(X)| [4]\n");
			if(!b_first_input){
				 puts("\n\nWant to begin again? [Y/N]");
			}

			int i_view_answer{};
			const char* text_for_answer = "";
			const char* text_for_table = "";
			bool b_start_again_mark{};
			while (3) {
				switch (_getch()) {
				case '1': // All
					i_view_answer = 1;
					text_for_answer = "S(X), Y(X) and |Y(X) - S(X)|";
					text_for_table = "   X           Y(X)          S(X)          |Y(X) - S(X)|";
					break;

				case '2': // S(X)
					i_view_answer = 2;
					text_for_answer = "S(X)";
					text_for_table = "   X           S(X)";
					break;

				case '3': // Y(X)
					i_view_answer = 3;
					text_for_answer = "Y(X)";
					text_for_table = "   X           Y(X)";
					break;

				case '4':  // |Y(X) - S(X)|
					i_view_answer = 4;
					text_for_answer = "|Y(X) - S(X)|";
					text_for_table = "   X           |Y(X) - S(X)|";
					break;

				case 'q':
				case 'Q':
					if (b_first_input) {
						system("cls");
						return;
					}
					else continue;

				case 'y':
				case 'Y':
					if (!b_first_input) b_start_again_mark = true;
					else continue;
					system("cls");
					break;

				case 'n':
				case 'N':
					if (!b_first_input) return;
					else continue;

				default:
					continue;
				}
				break;
			}
			b_first_input = false;
			if (b_start_again_mark) break;

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
			double d_x = d_a;
			for (int i = 1; i <= steps; ++i, d_x += d_h) {
				double d_member{ 1 }, d_sum{}, d_y{}, d_fabs{}; // d_fabs{} for |Y(X) - S(x)|

				if (i_view_answer == 1 || i_view_answer == 3 || i_view_answer == 4) {
					d_y = (1 - d_x * d_x / 2) * cos(d_x) - d_x * sin(d_x) / 2;
				}

				if (i_view_answer == 1 || i_view_answer == 2 || i_view_answer == 4) {
					for (int k = 1; k <= i_n; ++k) {         // Internal 'for' for sigma Σ. k = 1, because, when k = 0 first member d_m = 1
						d_sum += d_member;

						// M_n = -1 * X^2 * (2 * K^2 + 1) / (4 * K^2 - 2 * K) / (2 * K^2 - 4 * K + 3) * M_n-1
						d_member *= -1 * d_x * d_x * (2 * k * k + 1) / (4 * k * k - 2 * k) / (2 * k * k - 4 * k + 3);
					}
				}

				if (i_view_answer == 1 || i_view_answer == 4) {
					d_fabs = fabs(d_y - d_sum);
				}

				Out_Rez_lab_3(d_x, d_y, d_sum, d_fabs, i_view_answer);
			}
		}
	}
}
// END



// Laboratory work 5, variant 5 and 12
static void lab_5() {
	while (1) {
		int i_array_size{};
		if (number_input_handler("\nInput size of array (from 1 to 10000) (or quit[q/b]) :\n", i_array_size) != Good) {
			system("cls");
			break;
		}
		system("cls");

		if (i_array_size > 10000 || i_array_size <= 0) {
			printf("\nInvalid size. Input with supported size.\n\n");
			continue;
		}
	
		puts("How do you want to create array? (or quit [q])\n\n"
			"Manually [1]\n"
			"Randomly [2]");

		bool b_manual_input = false;
		while (2) {
			switch (_getch()) {
			case '1':
				b_manual_input = true;
				break;

			case '2': break;

			case 'q':
			case 'Q':
				system("cls");
				return;

			default: continue;
			}
			break;
		}
		system("cls");

		if (b_manual_input && i_array_size > 12) {
			printf("\nYou want to enter %d element(s) manually? [Y/N]\n", i_array_size);

			if (!YN()) b_manual_input = false;
		}
		system("cls");
				
		int* p_i_array = (int*)calloc(i_array_size, sizeof(int)); // Points on array start. Calloc for minimizing errors
		if (p_i_array == NULL) {
			system("cls");

			printf("\nInternal error occurred. Try again.\n\n");

			Sleep(1000);

			continue;
		}


		if (!b_manual_input) {
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
			int iter{0};
			Operation_code operation_code{First_iter};                                      // For array_input_handler errors
			while (iter < i_array_size) {
				system("cls");

				printf("\nPrefer [Enter] after every member."
					   "\nWill clear all input after mistaken number, if input with [Space]."
					   "\nRange is +-200000."
					   "\n\n\nInput array. (or quit [q])\n\n");

				if (operation_code != First_iter) {                                         // Doesn't show anything on first iteration
					for (int j = 0; j < iter; ++j) {
						printf("%d ", p_i_array[j]);
					}
				}

				operation_code = array_input_handler(iter, p_i_array, i_array_size, 200000);

				if (operation_code == Quit) {                                               // Quit
					system("cls");
					return;
				}

				while (operation_code == Not_val_size || operation_code == Not_val_num) {
					if(operation_code != Good) (void)buffer_clean();                                               // If number isn't valid again "eats" buffer to not to just skip invalid input


					if (operation_code == Not_val_size) {
						printf("\nNot valid element range. Input in valid range.");
					}

					printf("\nInput from %d element again:\n", iter + 1);
						
					operation_code = array_input_handler(iter, p_i_array, i_array_size, 200000);

				}
				++iter;
			}
			(void)buffer_clean();
		}
		system("cls");

		puts("What to calculate? (or quit [q])\n\n"
			 "Sum of elements in array from first positive member [1]\n"
			 "Sum of elements between first and last zero members [2]\n\n");

		printf("[");
		for (int i = 0; i < i_array_size - 1; ++i) {
			printf("%d, ", p_i_array[i]);
		}
		printf("%d", p_i_array[i_array_size - 1]);
		printf("]\n");

		int i_variant{};
		while (2) {
			switch (i_variant = _getch()) {
			case '1':
			case '2':
				break;
			case 'q':
			case 'Q':
				return;

			default: continue;
			}
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
		
		// Variant 12
		if (i_variant == '1') {
			bool b_has_positive = false;
			bool b_has_afters = false;
			int i_sum_from_positive{};
			for (int i = 0; i < i_array_size; ++i) {
				if (p_i_array[i] > 0) {
					b_has_positive = true;

					if (i + 1 < i_array_size) {
						b_has_afters = true;

						for (++i; i < i_array_size; ++i) {
							i_sum_from_positive += p_i_array[i];
						}
					}
				}
			}

			if (!b_has_positive) {
				puts("\nArray has not got positive numbers.\n");
			}
			else if (!b_has_afters && b_has_positive) {
				puts("\nPositive number is the last element in the array\n");
			}
			else {
				puts("\nSum of elements in the array from first positive member.\n");

				printf("[");
				for (int i = 0; i < i_array_size - 1; ++i) {
					printf("%d, ", p_i_array[i]);
				}
				printf("%d", p_i_array[i_array_size - 1]);
				printf("]\n");

				printf("\nHere is your answer: %d", i_sum_from_positive);
			}
		}
		// Variant 2
		else {
			int i_first_zero_position{};
			int i_last_zero_position{};

			bool b_is_zero_in_array{};
			bool b_one_zero_in_array = false;
			bool b_space_between_zeros = true;

			do {                                              // Scope to catch exceptions
				for (int i = 0; i < i_array_size; ++i) {      // Searching for the first zero
					if (p_i_array[i] == 0) {
						b_is_zero_in_array = true;
						i_first_zero_position = i;
						break;
					}
				}
				if (!b_is_zero_in_array) break;

				for (int i = i_array_size - 1; i >= 0; --i) { // Searching for the last zero
					if (p_i_array[i] == 0) {
						i_last_zero_position = i;
						break;
					}
				}
				if (i_first_zero_position == i_last_zero_position) {
					b_one_zero_in_array = true;
					break;
				}
				else if (i_last_zero_position == i_first_zero_position + 1) {
					b_space_between_zeros = false;
					break;
				}

			} while (0);

			if (!b_is_zero_in_array) {
				puts("\nNo zero elements in the array.");
			}
			else if (b_one_zero_in_array) {
				puts("\nThere is only one zero in the array.");
			}
			else if (!b_space_between_zeros) {
				puts("\nNo elements between zeros.");
			}
			else {
				puts("\nSum of the elements between two first zero elements in array.\n");

				printf("[");
				for (int i = 0; i < i_array_size - 1; ++i) {
					printf("%d, ", p_i_array[i]);
				}
				printf("%d", p_i_array[i_array_size - 1]);
				printf("]\n");

				int i_sum_between_zeros{};
				for (int i = i_first_zero_position; i <= i_last_zero_position; ++i) {
					i_sum_between_zeros += p_i_array[i];
				}

				printf("\nHere is your answer: %d", i_sum_between_zeros);
			}
		}

		free(p_i_array);

		USER_CONTINUE_USAGE();
	}
}
// END



// Laboratory work 6, variant 4 and 12

// Puts element into container in "%3d" format 
static void put_element_into_container(char* ch_matrix_container, int i_matrix_element, int container_index) {
	if (i_matrix_element >= 10) {
		ch_matrix_container[container_index] = ' ';
		ch_matrix_container[container_index + 1] = i_matrix_element / 10 + '0';
		ch_matrix_container[container_index + 2] = i_matrix_element % 10 + '0';
	}
	else if (i_matrix_element >= 0 && i_matrix_element < 10) {
		ch_matrix_container[container_index] = ' ';
		ch_matrix_container[container_index + 1] = ' ';
		ch_matrix_container[container_index + 2] = i_matrix_element + '0';
	}
	else if (i_matrix_element <= -10) {
		i_matrix_element = -i_matrix_element;
		ch_matrix_container[container_index] = '-';
		ch_matrix_container[container_index + 1] = i_matrix_element / 10 + '0';
		ch_matrix_container[container_index + 2] = i_matrix_element % 10 + '0';
	}
	else if (i_matrix_element < 0 && i_matrix_element > -10) {
		i_matrix_element = -i_matrix_element;
		ch_matrix_container[container_index] = ' ';
		ch_matrix_container[container_index + 1] = '-';
		ch_matrix_container[container_index + 2] = i_matrix_element + '0';
	}
}

static void lab_6() {
	while (1) {
		puts("What to calculate? (or quit [q])\n\n"
			 "Product of elements above side diagonal [1]\n"
			 "Special elements in columns             [2]");

		int i_variant{};
		while (2) {
			switch (i_variant = _getch()) {
			case '1':
			case '2':
				break;

			case 'q':
			case 'Q':
				return;

			default: continue;
			}
			system("cls");
			break;
		}
		
		int i_matrix_rows{};
		int i_matrix_cols{};
		while (1) {
			if (i_variant == '1') {
				if (number_input_handler("\nInput square matrix size (from 2 to 10) (or quit[q/b]) :\n", i_matrix_rows) != Good) {
					system("cls");
					return;
				}
			}
			else {
				if (number_input_handler("\nInput number of matrix rows (from 2 to 10) (or quit[q/b]) :\n", i_matrix_rows) != Good) {
					system("cls");
					return;
				}
			}			
			system("cls");

			if (i_matrix_rows > 10 || i_matrix_rows < 2) {
				printf("\nInvalid size. Input valid size.\n\n");
				continue;
			}
			break;
		}
		if (i_variant == '2') {             // Setting arbitrary matrix for variant 4
			while (2) {
				if (number_input_handler("\nInput number of matrix columns (from 2 to 10) (or quit[q/b]) :\n", i_matrix_cols) != Good) {
					system("cls");
					return;
				}
				system("cls");

				if (i_matrix_cols > 10 || i_matrix_cols < 2) {
					printf("\nInvalid size. Input valid size.\n\n");
					continue;
				}
				break;
			}
		}
		else i_matrix_cols = i_matrix_rows; // And if it's variant 12 setting square matrix

		puts("How do you want to create matrix? (or quit [q])\n\n"
			"Manually               [1]\n"
			"Randomly               [2]\n"
			"Randomly without zeros [3]");

		bool b_manual_input = false;
		bool b_zero_in_random = true;
		while (2) {
			switch (_getch()) {
			case '1':
				b_manual_input = true;
				break;

			case '2': break;

			case '3':
				b_zero_in_random = false;
				break;

			case 'q':
			case 'Q':
				system("cls");
				return;

			default: continue;

			}
			break;
		}
		system("cls");

		if (b_manual_input && (i_matrix_cols > 4 || i_matrix_rows > 4)) {
			printf("\nYou want to enter %d rows and %d cols manually? [Y/N]\n", i_matrix_rows, i_matrix_cols);

			if (!YN()) b_manual_input = false;
		}
		system("cls");

		bool b_memory_inicialize_fail = false;

		int** p_i_matrix = (int**)calloc(i_matrix_rows, sizeof(int*));     // Creating pointer to array of pointers
		
		if (p_i_matrix == NULL) b_memory_inicialize_fail = true;

		int i_bad_row{};
		if (!b_memory_inicialize_fail) {
			for (int i = 0; i < i_matrix_rows; ++i) {
				p_i_matrix[i] = (int*)calloc(i_matrix_cols, sizeof(int));  // Giving every pointer in array of pointers it's own pointer on start of array
				if (p_i_matrix[i] == NULL) {
					i_bad_row = i;                                         // To free() every row before the bad row
					b_memory_inicialize_fail = true;
					break;
				}
			}
		}

		char* ch_matrix_container{};
		if (!b_memory_inicialize_fail) {
			ch_matrix_container = (char*)calloc(4 * i_matrix_cols * i_matrix_rows + i_matrix_rows * 2 - 1, sizeof(char));
			// Four bytes for every number, two for new lines after every line, except last, one for \0

			if (ch_matrix_container == NULL) b_memory_inicialize_fail = true;
		}

		if (b_memory_inicialize_fail) {
			if (p_i_matrix != NULL) {
				for (int i = 0; i < i_bad_row; ++i) {
					free(p_i_matrix[i]);
				}
			}
			
			free(p_i_matrix);

			system("cls");

			printf("\nInternal error occurred. Try again.\n");

			Sleep(1000);

			continue;
		}

		int container_index{ 0 };
		if (!b_manual_input) {
			generate_seed();

			puts("\nGenerating...");

			Sleep(1000);

			system("cls");

			puts("");

			for (int i = 0; i < i_matrix_rows; ++i) {
				for (int j = 0; j < i_matrix_cols; ++j) {
					do {
						p_i_matrix[i][j] = my_random(20, 48);
					} while (!b_zero_in_random && p_i_matrix[i][j] == 0);

					put_element_into_container(ch_matrix_container, p_i_matrix[i][j], container_index);
					container_index += 3;                       // Every element width is four positions
					ch_matrix_container[container_index] = ' '; // This is fourth
					++container_index;
					printf("%3d ", p_i_matrix[i][j]);
				}
				if (i != i_matrix_rows - 1) {                   // For the last row not displaying "\n\n"
					ch_matrix_container[container_index] = '\n';
					ch_matrix_container[container_index + 1] = '\n';
					container_index += 2;
				}
				puts("\n");
			}
			ch_matrix_container[container_index] = '\0';
			Sleep(1000);
		}
		else {
			int operation_code{ -1 }; // Shows first iteration
			for (int row = 0; row < i_matrix_rows; ++row) {
				for (int col = 0; col < i_matrix_cols; ++col) {
					system("cls");

					if (operation_code == 1) {
						for (int i = 0; i < i_matrix_rows; ++i) {
							free(p_i_matrix[i]);
						}
						free(p_i_matrix);
						free(ch_matrix_container);
						system("cls");
						return;
					}

					printf("\nPrefer [Enter] after every member."
						   "\nWill clear all input after mistaken number, if input with [Space]."
						   "\nRange is +-20."
						   "\n\n\nInput matrix. (or quit [q])\n\n");

					if (operation_code != -1) {
						for (int i = 0; i <= row; ++i) {
							int col_limit = (i == row) ? col : i_matrix_cols; // For all i, that are not current row, printing all elements.
							for (int j = 0; j < col_limit; ++j) {             // Else printing elements till current column 
								printf("%3d ", p_i_matrix[i][j]);
								if (j == i_matrix_cols -1) printf("\n\n");
							}
						}
					}

					operation_code = array_input_handler(col, p_i_matrix[row], i_matrix_cols, 20);


					if (operation_code == 2 || operation_code == 3) {
						(void)buffer_clean();

						if (operation_code == 2) {
							printf("\nNot valid element range. Input in valid range.");
						}

						while (operation_code == 2 || operation_code == 3) {
							printf("\nInput from %d row and %d column again:\n", row + 1, col + 1);

							operation_code = array_input_handler(col, p_i_matrix[row], i_matrix_cols, 20);

							(void)buffer_clean();
						}
					}
					put_element_into_container(ch_matrix_container, p_i_matrix[row][col], container_index);
					container_index += 3;
					ch_matrix_container[container_index] = ' ';
					++container_index;
				}
				if (row != i_matrix_rows - 1) {
					ch_matrix_container[container_index] = '\n';
					ch_matrix_container[container_index + 1] = '\n';
					container_index += 2;
				}
				puts("\n");
			}
			ch_matrix_container[container_index] = '\0';
		}
		system("cls");

		if (i_variant == '1') {
			printf("\nMultiply elements above side diagonal? [Y/N]\n\n\n%s", ch_matrix_container);
		}
		else printf("\nCalculate number of elements, that are bigger then sum of the rest elements in column? [Y/N]\n\n\n%s", ch_matrix_container);

		if (!YN()) {
			for (int i = 0; i < i_matrix_rows; ++i) {
				free(p_i_matrix[i]);
			}
			free(p_i_matrix);
			free(ch_matrix_container);
			system("cls");
			break;
		}

		long long int lli_product_above_dioganal{ 1 };
		int i_number_of_special_elements{};
		if (i_variant == '1') {                        // Variant 12
			int column_for_diagonal = i_matrix_cols - 1;
			for (int i = 0; i < i_matrix_rows; ++i, --column_for_diagonal) {
				for (int j = 0; j < column_for_diagonal; ++j) {
					lli_product_above_dioganal *= p_i_matrix[i][j];
				}
			}
		}
		else {                                         // Variant 4
			int i_sum_in_col{};
			for (int j = 0; j < i_matrix_cols; ++j) {

				// Calculating sum in the column
				for (int i = 0; i < i_matrix_rows; ++i) {
					i_sum_in_col += p_i_matrix[i][j];
				}

				for (int i = 0; i < i_matrix_rows; ++i) {
					if (p_i_matrix[i][j] > i_sum_in_col - p_i_matrix[i][j]) ++i_number_of_special_elements; 
				}

				i_sum_in_col = 0;
			}
		}

		system("cls");
		Sleep(300);
		printf(".");
		Sleep(200);
		printf(".");
		Sleep(350);
		printf(".");
		system("cls");

		if (i_variant == '1') printf("\nMultiplied elements above side diagonal.\n\n\n%s\n\n\nHere is your answer: %lld", ch_matrix_container, lli_product_above_dioganal);

		else printf("\nNumber of elements, that are bigger then sum of the rest elements in column.\n\n\n%s\n\n\nHere is your answer: %d", ch_matrix_container, i_number_of_special_elements);

		for (int i = 0; i < i_matrix_rows; ++i) {
			free(p_i_matrix[i]);
		}
		free(p_i_matrix);
		free(ch_matrix_container);

		USER_CONTINUE_USAGE()
	}
}
// END



// Laboratory work 7, variant 2 and 12
inline static bool is_char_punctuation(char ch_c) {
	return strchr(".,?!/|\\:;@#№$%^&*(){}[]<>~`\"'", ch_c) != nullptr; // has pointer - true, no pointer - false
}

static void lab_7() {
	while (1) {
		puts("What do you want to check? (or quit [q])\n\n"
			"Shortest binary code group   [1]\n"
			"Word information by position [2]");

		int i_variant{};
		while (2) {
			switch (i_variant = _getch()) {
			case '1':
			case '2':
				break;

			case 'q':
			case 'Q':
				return;

			default: continue;
			}
			system("cls");
			break;
		}

		while (2) {
			if (i_variant == '1') {
				printf("\nPut only [Ctrl + Z] on new line and then [Enter] to end input.\nInput only [q] to quit.\n\n\nInput your binary code:\n\n");
			}
			else {
				printf("\nPut only [Ctrl + Z] on new line and then [Enter] to end input.\nInput only [q] to quit.\n\n\nWrite a poem:\n\n");
			}

			bool b_memory_inicialize_fail = false;

			size_t sz_user_text_size{ 1 }; // 1 cell for zero bit
			char* p_ch_user_text = (char*)calloc(sz_user_text_size, sizeof(char));
			if (p_ch_user_text == NULL) b_memory_inicialize_fail = true;

			if (b_memory_inicialize_fail) {
				system("cls");

				printf("\nInternal error occurred. Try again.\n");

				Sleep(1000);

				continue;
			}

			int operation_code = string_input_handler(&p_ch_user_text, sz_user_text_size, sizeof(char));

			if (sz_user_text_size == 1) {
				printf("\nYou need to input something.");
				Sleep(1000);
				continue;
			}
			else if ((p_ch_user_text[0] == 'q' || p_ch_user_text[0] == 'Q') && sz_user_text_size == 3) return;

			if (operation_code != 0) {
				free(p_ch_user_text);
				b_memory_inicialize_fail = true;
			}

			// Variant 2
			if (i_variant == '1') {

				int i_size_of_shortest{ -1 };                // Minus one shows, that it is firts etaration, and puts first block as shortest
				int i_shortest_position{};

				bool b_is_binary = true;
				bool b_has_binary = true;

				int i_user_text_length = strlen(p_ch_user_text);
				for (int i = 0; i < i_user_text_length; ++i) {
					if (p_ch_user_text[i] == '\n') {
						++i;
						continue;
					}
					else if (!IS_CHAR_BINARY(p_ch_user_text[i])) {
						b_is_binary = false;
						b_has_binary = false;
						break;
					}

					char ch_I_O = p_ch_user_text[i];		 // One or zero

					int i_block_start = i;

					int i_size_of_current = 0;
					 	                                     // Then counting current size and moving 'i' to the next block
					for (i; p_ch_user_text[i] == ch_I_O; ++i, ++i_size_of_current);
					--i;

					if (i_size_of_shortest == -1 || i_size_of_current < i_size_of_shortest) {
						i_shortest_position = i_block_start;

						i_size_of_shortest = i_size_of_current;
					}
				}

				if (!b_is_binary) {
					free(p_ch_user_text);
					system("cls");
					printf("\nIt is not binary code. Input again.\n\n");
					Sleep(1500);
					continue;
				}
				else if (!b_has_binary) {
					free(p_ch_user_text);
					system("cls");
					printf("\nNo binary code. Input again.\n\n");
					Sleep(1500);
					continue;
				}

				system("cls");
				printf("\nSearching for shortest block...");
				Sleep(1000);
				system("cls");

				printf("\nIn your binary code:\n%s\nThe shortest binary block is: ", p_ch_user_text);

				for (int i = i_shortest_position; i < i_shortest_position + i_size_of_shortest; ++i) {
					printf("%c", p_ch_user_text[i]);
				}
			}
			// Variant 12
			else {
				system("cls");
				int i_position_to_dispaly{};
				while (3) {
					if (number_input_handler("\nInput position in poem (from 1 to %d) (or quit [q]) :\n", i_position_to_dispaly, (int)sz_user_text_size - 2) != Good) {
						system("cls");
						return;
					}
					if (i_position_to_dispaly <= 0 || i_position_to_dispaly > sz_user_text_size - 2) {
						system("cls");
						printf("Not valid position. Input valid position.\n\n");
						continue;
					}
					break;
				}


				int i_position = i_position_to_dispaly - 1;

				int i_word_count{ 0 };
				for (int i = 0; i <= i_position; ++i) { // Counting words. Every "first step" on the word counts one word
					if (!IS_CHAR_SPLITTER(p_ch_user_text[i]) && !is_char_punctuation(p_ch_user_text[i])){
						++i_word_count;
						                                // Moving 'i' to the next splitter or end of the text
						while (p_ch_user_text[i] != '\0' && !IS_CHAR_SPLITTER(p_ch_user_text[i]) && !is_char_punctuation(p_ch_user_text[i])) ++i;
					}
				}

				bool b_position_is_on_word = !IS_CHAR_SPLITTER(p_ch_user_text[i_position]) && !is_char_punctuation(p_ch_user_text[i_position]);

				                                        // Moving position to the end of the word
				while (i_position >= 0 && (IS_CHAR_SPLITTER(p_ch_user_text[i_position]) || is_char_punctuation(p_ch_user_text[i_position]))) {
					--i_position;
				}

				int i_word_start = i_position;          // Calculating, where word starts and wether it in start of text 
				for (i_word_start; i_word_start >= 0 && !IS_CHAR_SPLITTER(p_ch_user_text[i_word_start]) && !is_char_punctuation(p_ch_user_text[i_word_start]); --i_word_start);
				++i_word_start;

				system("cls");
				printf("\nSearching for word...");
				Sleep(1000);
				system("cls");
				
				printf("\n-----------------------------------\n%s-----------------------------------", p_ch_user_text);

				printf("\n\nHere is information for position %d:\n\n", i_position_to_dispaly);

				printf("Position:     "); b_position_is_on_word ? printf("on word\n") : printf("not on word\n");
				printf("Word:         ");
				for (int i = i_word_start; !IS_CHAR_SPLITTER(p_ch_user_text[i]) && !is_char_punctuation(p_ch_user_text[i]); ++i) {
					printf("%c", p_ch_user_text[i]);
				}
				printf("\n");
				printf("Word index:   %d", i_word_count);
			}
			free(p_ch_user_text);
			break;
		}
		USER_CONTINUE_USAGE()
	}
}
// END



// Laboratory work 8, variant 12
enum Name_type {FirstN, LastN};
enum Command {Regen_database_manual, Regen_database_random, Sh_all, Sh_group, Sh_best};

struct Student_form {
	int number{};
	char name[16];
	char surname[16];
	int mark_physics[16];
	int mark_math[16];
};

// FirstN - first name
// LastN  - last name
static const char* get_name(Name_type name_type, size_t i_name_position) {
	static const char* ch_first_names[] = {
		"James",   "Mary",    "John",    "Patricia",  "Robert",  "Jennifer",
		"Michael", "Linda",   "William", "Elizabeth", "David",   "Susan",
		"Richard", "Jessica", "Joseph",  "Sarah",     "Thomas",  "Karen",
		"Charles", "Nancy",   "Daniel",  "Lisa",      "Matthew", "Betty",
		"Anthony", "Emily",   "Mark",    "Sandra",    "Donald",  "Ashley",
		"Steven",  "Kimberly","Paul",    "Donna",     "Andrew",  "Michelle",
		"Joshua",  "Dorothy", "Kevin",   "Carol",     "Brian",   "Amanda",
		"George",  "Melissa", "Edward",  "Deborah",   "Ronald",  "Stephanie",
		"Timothy", "Rebecca", "Jason",   "Sharon",    "Jeffrey", "Laura",
		"Ryan",    "Cynthia", "Jacob",   "Amy",       "Gary",    "Kathleen",
		"Nicholas","Angela",  "Eric",    "Shirley",   "Stephen", "Brenda",
		"Jonathan","Pamela",  "Larry",   "Emma",      "Justin",  "Nicole",
		"Scott",   "Helen",   "Brandon", "Anna",      "Benjamin","Samantha",
		"Samuel",  "Katherine","Frank", "Christine", "Gregory", "Debra",
		"Raymond", "Rachel",  "Patrick", "Carolyn",   "Alexander","Janet",
		"Jack",    "Maria",   "Dennis",  "Heather",   "Jerry",   "Catherine",
		"Tyler",   "Diane",   "Aaron",   "Olivia",    "Henry",   "Julie",
		"Jose",    "Joyce",   "Adam",    "Victoria",  "Peter",   "Kelly"
	};

	static const char* ch_last_names[] = {
		"Smith",  "Johnson",  "Williams",  "Brown",    "Jones",     "Garcia",
		"Miller", "Davis",    "Rodriguez", "Martinez", "Hernandez", "Walker",
		"Lopez",  "Gonzalez", "Wilson",    "Anderson", "Thomas",    "Taylor",
		"Moore",  "Jackson",  "Martin",    "Lee",      "Perez",     "Thompson",
		"White",  "Harris",   "Sanchez",   "Clark",    "Lewis",     "Robinson",
		"Hall",   "Allen",    "Young",     "King",     "Wright",    "Scott",
		"Green",  "Baker",    "Adams",     "Nelson",   "Hill",      "Ramirez",
		"Campbell","Mitchell","Roberts",   "Carter",   "Phillips",  "Evans",
		"Turner", "Torres",   "Parker",    "Collins",  "Edwards",   "Stewart",
		"Flores", "Morris",   "Nguyen",    "Murphy",   "Rivera",    "Cook",
		"Rogers", "Morgan",   "Peterson",  "Cooper",   "Reed",      "Bailey",
		"Bell",   "Gomez",    "Kelly",     "Howard",   "Ward",      "Cox",
		"Diaz",   "Richardson","Wood",     "Watson",   "Brooks",    "Bennett",
		"Gray",   "James",    "Reyes",     "Cruz",     "Hughes",    "Price",
		"Myers",  "Long",     "Foster",    "Sanders",  "Ross",      "Morales",
		"Powell", "Sullivan", "Russell",   "Ortiz",    "Jenkins",   "Gutierrez",
		"Perry",  "Butler",   "Barnes",    "Fisher",   "Henderson", "Coleman",
		"Patterson","Jordan", "Graham",    "Reynolds", "Hamilton",  "Ford"
	};
	static size_t sz_firsts_amount = sizeof(ch_first_names) / sizeof(ch_first_names[0]);
	static size_t sz_lasts_amount = sizeof(ch_last_names) / sizeof(ch_last_names[0]);
	static size_t sz_max_name_position = sz_firsts_amount >= sz_lasts_amount ? sz_lasts_amount - 1 : sz_firsts_amount - 1;

	if (i_name_position >= sz_max_name_position) i_name_position = sz_max_name_position; // More or equals zero because in names 0-29 positions, not 30
	else if (i_name_position < 0) i_name_position = 0;

	return name_type == FirstN ? ch_first_names[i_name_position] : ch_last_names[i_name_position];
}

static void print_student_marks(int* p_i_marks_array, const char* ch_subject_name) {
	printf("\n  %-14s", ch_subject_name);

	for (int j = 0; j < 16; ++j) {
		if (p_i_marks_array[j] == -1) {
			printf("  ");
			continue;
		}
		printf("%d ", p_i_marks_array[j]);
	}
}

static void print_student_form(Student_form& student_form) {
	printf("\n---------------------------------------------------\nStudent number: %d\nName:           %s\nSurname:        %s\nMarks:", student_form.number, student_form.name, student_form.surname);

	print_student_marks(student_form.mark_math, "Math:");
	print_student_marks(student_form.mark_physics, "Physics:");
}

static void generate_marks(int* p_i_marks_array, int i_strength) {
	int i_marks_count = 4 + my_random(8, 0);

	for (int j = 0; j < 16; ++j) {               // Replacing marks with debug values
		p_i_marks_array[j] = -1;
	}

	int i_placed_count = 0;
	
	while (i_placed_count < i_marks_count) {     // Would place i_marks_count amount of marks
		int i_random_index = my_random(16, 0);

		if (p_i_marks_array[i_random_index] == -1) { // Continue if index already has mark
			if (i_strength > 865) {
				p_i_marks_array[i_random_index] = 5 + my_random(5, 0);
			}
			else if (i_strength < 327) {
				p_i_marks_array[i_random_index] = 2 + my_random(4, 0);
			}
			else {
				p_i_marks_array[i_random_index] = 3 + my_random(5, 0);
			}


			++i_placed_count;
		}
	}
}


#define ENTER_DATABASE_PARAMS(i_number_of_parameter, i_min_range, i_max_range, ch_message)\
	while (1) {\
		Operation_code cod_screen_backwards = number_input_handler(ch_message, i_number_of_parameter);\
		if (cod_screen_backwards == Quit) {\
			fclose(Students_database);\
			system("cls");\
			return;\
		}\
		else if (cod_screen_backwards == Back) {\
			system("cls");\
			fclose(Students_database);\
			break;\
		}\
		if (i_number_of_parameter < i_min_range || i_number_of_parameter > i_max_range) {\
			system("cls");\
			printf("\nNot valid range.\n\n");\
			Sleep(1500);\
			continue;\
		}\
		break;\
	}\

static void lab_8() {
	while (1) {
		puts("\nStudents sample database generator.\n\n"
			 "[1] - recreate database randomly\n"
			 "[2] - recreate database manually (amount of groups and students)\n"
			 "[3] - show all students\n"
			 "[4] - show students in group\n"
			 "\n[q] - quit\n"
			);

		Command cmd_main{};
		while (2) {
			switch (_getch()) {
			case '1':
				system("cls");
				cmd_main = Regen_database_random;
				break;

			case '2':
				system("cls");
				cmd_main = Regen_database_manual;
				break;

			case '3':
				cmd_main = Sh_all;
				break;

			case '4':
				cmd_main = Sh_group;
				break;

			case 'q':
			case 'Q':
				system("cls");
				return;

			default: continue;
			}
			system("cls");
			break;
		}

		Student_form student_form = { 0, "", "", 0, 0 };

		FILE* Students_database = NULL;
		
		bool b_no_database = false;
		while (2) {
			if (cmd_main == Regen_database_random || cmd_main == Regen_database_manual) {
				if (fopen_s(&Students_database, "C:\\Users\\ASUS\\Desktop\\OAiP\\Chared labs\\databases\\students_data.dat", "w+b")) {
					b_no_database = true;
					break;
				}

				generate_seed();

				int i_number_of_groups{};
				int i_number_of_students{};

				if (cmd_main == Regen_database_random) {
					int i_number_of_groups = 2; //+ my_random(4, 0);
					int i_number_of_students = 2;
				}
				else {       // Regen_database_manual

					// Could return here!!!
					ENTER_DATABASE_PARAMS(i_number_of_groups, 1, 6, "\nInput amount of groups from 1 to 6 (quit [q], back [b]) :\n")
					system("cls");
					ENTER_DATABASE_PARAMS(i_number_of_students, 1, 10, "\nInput amount of students from 1 to 10 (quit [q], back [b]) :\n")
				}

				for (int g = 1; g <= i_number_of_groups; ++g) {      // Generate groups
					int i_groupe = my_random(482, 0) * 1000 + my_random(432, 0);

					for (int i = 0; i < i_number_of_students; ++i) { // Generate students
						int i_strength = my_random(1001, 0);

						student_form.number = i_groupe + i;

						const char* ch_random_name{};

						ch_random_name = get_name(FirstN, my_random(119, 0));
						strcpy_s(student_form.name, sizeof(student_form.name), ch_random_name);

						ch_random_name = get_name(LastN, my_random(119, 0));
						strcpy_s(student_form.surname, sizeof(student_form.surname), ch_random_name);

						generate_marks(student_form.mark_math, my_random(1000, 0));
						generate_marks(student_form.mark_physics, my_random(1000, 0));


						fwrite((char*)&student_form, sizeof(Student_form), 1, Students_database);
					}
				}

				fclose(Students_database);

				system("cls");
				printf("\nRecreating...");
				Sleep(1000);
				system("cls");
				printf("\nDone.");
				Sleep(800);
				system("cls");

				break;
			}

			if (cmd_main == Sh_all || cmd_main == Sh_group) {
				if (fopen_s(&Students_database, "C:\\Users\\ASUS\\Desktop\\OAiP\\Chared labs\\databases\\students_data.dat", "r+b")) {
					b_no_database = true;
					break;
				}
			}

			Command cmd_show_branch{}; // Level lower after main choise
			if (cmd_main == Sh_all) {
				bool b_back = false;
				while (3) {
					puts("\nShow all students\n\n"
						"[1] - show all students\n"
						"[2] - show best students\n"
						"\n[q] - quit\n"
						"[b] - back to start\n\n\n"
						);

					while (4) {
						switch (_getch()) {
						case '1':
							cmd_show_branch = Sh_all;
							break;

						case '2':
							cmd_show_branch = Sh_best;
							break;

						case 'b':
						case 'B':
							b_back = true;
							fclose(Students_database);
							break;

						case 'q':
						case 'Q':
							fclose(Students_database);
							return;

						default: continue;
						}
						system("cls");
						break;
					}
					if (b_back) break;

					if (cmd_show_branch == Sh_all) {
						fseek(Students_database, 0, 0);
						while (fread((char*)&student_form, sizeof(Student_form), 1, Students_database)) {
							print_student_form(student_form);
						}
						printf("\n\n\n");
					}
					else {              // Sh_best
						fseek(Students_database, 0, 0);
						int i_good_students_amount = 0;
						while (fread((char*)&student_form, sizeof(Student_form), 1, Students_database)) {
							bool b_good_student = false;

							for (int i = 0; i < 16; ++i) {
								if (student_form.mark_math[i] > 9 || student_form.mark_physics[i] == 7 || student_form.mark_physics[i] == 8) {
									b_good_student = true;
									++i_good_students_amount;
									break;
								}
							}

							if (b_good_student) print_student_form(student_form);
						}

						if (i_good_students_amount == 0) {
							printf("\nNo good students :(\n\n\n");
						}
						else {
							printf("\nAmount of good students in all groups is %d", i_good_students_amount);
						}
					}
				}
				if (b_back) break;

				
			}
			//else {       // Sh_group
			//	

			//	if (cmd_show_best == Sh_all_best) {

			//	}
			//	else {            // Sh_group_best

			//	}

			//	break;
			//}
			break;
		}
		if (b_no_database) {
			printf("No database\n");
			Sleep(1000);
			system("cls");
			continue;
		}
	}
}
// END



// Main -- menu
int main() {
	while (1) {
		printf(
			"      __       _                     _                   \n"
			"     / /  __ _| |__   ___  _ __ __ _| |_ ___  _ __ _   _       Kalenkovich Daniil Alekseevich\n"
			"    / /  / _` | '_ \\ / _ \\| '__/ _` | __/ _ \\| '__| | | |\n"
			"   / /__| (_| | |_) | (_) | | | (_| | || (_) | |  | |_| |      568405\n"
			"   \\____/\\__,_|_.__/ \\___/|_|  \\__,_|\\__\\___/|_|   \\__, |\n"
			"           __    __           _                    |___/\n"
			"          / / /\\ \\ \\___  _ __| | _____                   \n"
			"          \\ \\/  \\/ / _ \\| '__| |/ / __|                  \n"
			"           \\  /\\  / (_) | |  |   <\\__ \\                  \n"
			"            \\/  \\/ \\___/|_|  |_|\\_\\___/                  \n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"Linear calculations                  [1]                Strings usage               [7]\n"
			"\n"
			"Branching algorithms                 [2]  Arrays   [5]  Structure handling in files [8]\n"
			"\n"
			"Cycled algorithms and user functions [3]  Matrixes [6]  Plotting functions          [9]\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"Exit [Esc]"
		);

		while (2) {
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

			case '6':
				system("cls");
				lab_6();
				break;

			case '7':
				system("cls");
				lab_7();
				break;

			case '8':
				system("cls");
				lab_8();
				break;

			case 27:
				printf("     Press [Esc] again to exit.");

				if (_getch() == 27) exit(0);

				else {
					system("cls");
					break;
				}

			default: continue;
			}
			break;
		}
	}
}
// END