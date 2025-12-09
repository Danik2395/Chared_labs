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
#include <io.h>         // For _chsize
#include <time.h>
using namespace std;


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
			printf("\nAn internal error has occurred.\nTry again with another values.\n\n");
			Sleep(1000);
			continue;
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
		if (number_input_handler("\nInput A (in range +-20) (or quit [q]) :\n", d_a) != Good) {
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
			if (number_input_handler("\nInput B (in range +-20) (or quit [q]) :\n", d_b) != Good) { // Very cross variable!!!  d_b
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
			if (number_input_handler("\nInput H (or quit [q]) :\n", d_h) != Good) {
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
			printf("\nAn internal error has occurred.\nTry again with another values.\n\n");
			Sleep(1500);
			continue;
		}

		int i_n{};
		while (2) {
			if (my_fabs(d_a) >= 1 || my_fabs(d_b) >= 4) {
				printf("\nFor better results 10 < N <= 40");
			}

			if (number_input_handler("\nInput N from 1 to 20 (or quit [q]) :\n", i_n) != Good) {
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
			if (!b_first_input) {
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
		if (number_input_handler("\nInput size of array (from 1 to 10000) (or quit [q]) :\n", i_array_size) != Good) {
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

			printf("\nAn internal error has occurred. Try again.\n\n");

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
			int iter{ 0 };
			Operation_code operation_code{ First_iter };                                      // For array_input_handler errors
			while (iter < i_array_size) {
				system("cls");

				if (operation_code == Quit) {                                               // Quit
					system("cls");
					return;
				}

				printf("\nPrefer [Enter] after every member."
					"\nWill clear all input after mistaken number, if input with [Space]."
					"\nRange is +-200000."
					"\n\n\nInput array. (or quit [q])\n\n");

				if (operation_code != First_iter) {                                         // Doesn't show anything on first iteration
					for (int j = 0; j < iter; ++j) {
						printf("%d ", p_i_array[j]);
					}
				}

				operation_code = array_input_handler(iter, p_i_array, 200000);

				while (operation_code == Not_val_size || operation_code == Not_val_num) {
					if (operation_code != Good) (void)buffer_clean();                       // If number isn't valid again "eats" buffer to not to just skip invalid input


					if (operation_code == Not_val_size) {
						printf("\nNot valid element range. Input in valid range.");
					}

					printf("\nInput from %d element again:\n", iter + 1);

					operation_code = array_input_handler(iter, p_i_array, 200000);

				}
				++iter;
			}
			(void)buffer_clean();
		}
		system("cls");

		puts("What to calculate? (or quit [q])\n\n"
			"Sum of elements in array after first positive member [1]\n"
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
				puts("\nSum of elements in the array after first positive member.\n");

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
				if (number_input_handler("\nInput square matrix size (from 2 to 10) (or quit [q]) :\n", i_matrix_rows) != Good) {
					system("cls");
					return;
				}
			}
			else {
				if (number_input_handler("\nInput number of matrix rows (from 2 to 10) (or quit [q]) :\n", i_matrix_rows) != Good) {
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
				if (number_input_handler("\nInput number of matrix columns (from 2 to 10) (or quit [q]) :\n", i_matrix_cols) != Good) {
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

			printf("\nAn internal error has occurred. Try again.\n");

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
			Operation_code operation_code{ First_iter }; // Shows first iteration
			for (int row = 0; row < i_matrix_rows; ++row) {
				for (int col = 0; col < i_matrix_cols; ++col) {
					system("cls");

					if (operation_code == Quit) {
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

					if (operation_code != First_iter) {
						for (int i = 0; i <= row; ++i) {
							int col_limit = (i == row) ? col : i_matrix_cols; // For all i, that are not current row, printing all elements.
							for (int j = 0; j < col_limit; ++j) {             // Else printing elements till current column 
								printf("%3d ", p_i_matrix[i][j]);
								if (j == i_matrix_cols - 1) printf("\n\n");
							}
						}
					}

					operation_code = array_input_handler(col, p_i_matrix[row], 20);

					while (operation_code == Not_val_size || operation_code == Not_val_num) {
						if (operation_code != Good) (void)buffer_clean();                       // If number isn't valid again "eats" buffer to not to just skip invalid input


						if (operation_code == Not_val_size) {
							printf("\nNot valid element range. Input in valid range.");
						}

						printf("\nInput from %d row and %d column again:\n", row + 1, col + 1);

						operation_code = array_input_handler(col, p_i_matrix[row], 20);

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

		system("cls");
		Sleep(300);
		printf(".");
		Sleep(200);
		printf(".");
		Sleep(350);
		printf(".");
		system("cls");

		if (i_variant == '1') {                        // Variant 12
			long long int lli_product_above_dioganal{ 1 };

			int column_for_diagonal = i_matrix_cols - 1;
			for (int i = 0; i < i_matrix_rows; ++i, --column_for_diagonal) {
				for (int j = 0; j < column_for_diagonal; ++j) {
					lli_product_above_dioganal *= p_i_matrix[i][j];
				}
			}

			printf("\nMultiplied elements above side diagonal.\n\n\n%s\n\n\nHere is your answer: %lld", ch_matrix_container, lli_product_above_dioganal);
		}
		else {                                         // Variant 4
			int i_number_of_special_elements{};
			int i_sum_in_col{};
			int* p_i_elements = (int*)calloc(1, sizeof(int));
			int i_full_size_elements{};

			do {
				if (p_i_elements == NULL) {
					b_memory_inicialize_fail = true;
					break;
				}

				for (int j = 0; j < i_matrix_cols; ++j) {

					// Calculating sum in the column
					for (int i = 0; i < i_matrix_rows; ++i) {
						i_sum_in_col += p_i_matrix[i][j];
					}

					for (int i = 0; i < i_matrix_rows; ++i) {
						if (p_i_matrix[i][j] > i_sum_in_col - p_i_matrix[i][j]) {
							++i_number_of_special_elements;

							i_full_size_elements = i_number_of_special_elements * 3;

							int* copy_array = (int*)realloc(p_i_elements, sizeof(int) * i_full_size_elements);

							if (copy_array == NULL) {
								b_memory_inicialize_fail = true;
								break;
							}

							p_i_elements = copy_array;

							p_i_elements[i_full_size_elements - 1] = j + 1;
							p_i_elements[i_full_size_elements - 2] = i + 1;
							p_i_elements[i_full_size_elements - 3] = p_i_matrix[i][j];
						}
					}
					if (b_memory_inicialize_fail) break;


					i_sum_in_col = 0;
				}

				printf("\nNumber of elements, that are bigger then sum of the rest elements in column.\n\n\n%s\n\n\nHere is your answer: %d", ch_matrix_container, i_number_of_special_elements);

				if (i_number_of_special_elements != 0) {
					printf("\n\nThe elements:\n");

					for (int i = 0; i < i_full_size_elements; i += 3) {
						if (i % 15 == 0 && i != 0) {
							printf("\n\n");
						}

						printf("%3d {%2d, %2d};  ", p_i_elements[i], p_i_elements[i + 1], p_i_elements[i + 2]);
					}
				}
			} while (0);

			free(p_i_elements);
			if (b_memory_inicialize_fail) {
				b_memory_inicialize_fail = true;

				system("cls");

				printf("\nAn internal error has occurred. Try again.\n");

				Sleep(1000);
			}

		}


		for (int i = 0; i < i_matrix_rows; ++i) {
			free(p_i_matrix[i]);
		}
		free(p_i_matrix);
		free(ch_matrix_container);

		if (b_memory_inicialize_fail) continue;

		USER_CONTINUE_USAGE()
	}

}
// END



// Laboratory work 7, variant 2 and 12
#define IS_CHAR_BINARY(ch_c) (ch_c == '0' || ch_c == '1')
#define IS_CHAR_SPLITTER(ch_c) (ch_c == '\n' || ch_c == ' ' || ch_c == '\t')

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

				printf("\nAn internal error has occurred. Try again.\n");

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

				int i_user_text_length = (int)strlen(p_ch_user_text);
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
					if (number_input_handler("\nInput position in poem (from 1 to %d) (or quit [q]) :\n", i_position_to_dispaly, 0, (int)sz_user_text_size - 2) != Good) {
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
					if (!IS_CHAR_SPLITTER(p_ch_user_text[i]) && !is_char_punctuation(p_ch_user_text[i])) {
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
	enum Name_type { FirstN, LastN };
	enum Command {
		Regen_database_manual,
		Regen_database_random,
		Sh_all,
		Sh_group,
		Sh_one,
		Sh_best,
		Sh_best_marks,
		Sh_best_median,
		Change_student,
		No_command
	};

	struct Student_form {
		int i_number;
		char ch_name[16];
		char ch_surname[16];
		struct {
			int i_day;
			int i_month;
			int i_year;
		} birth_date;
		int i_mark_physics[16];
		int i_mark_math[16];
		int i_mark_bel[16];
		int i_mark_chem[16];
		int i_mark_inf[16];
		double d_median;
	};

	struct Database_info {
		int i_groups_amount;
		//int i_students_amount;
		int i_group_numbers[6];            // Parallel
		int i_students_in_group_amount[6]; // Arrays
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
		"Samuel",  "Katherine","Frank",  "Christine", "Gregory", "Debra",
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
				printf("   ");
				continue;
			}
			printf("%2d ", p_i_marks_array[j]);
		}

	}

	static void print_student_form(Student_form& student_form) {
		printf("\n-----------------------------------------------------------------\nStudent number: %06d\nName:           %s\nSurname:        %s\nBirth day:      %02d.%02d.%d\nMarks:",
			student_form.i_number, student_form.ch_name, student_form.ch_surname, student_form.birth_date.i_day, student_form.birth_date.i_month, student_form.birth_date.i_year
		);

		print_student_marks(student_form.i_mark_math, "Math:");
		print_student_marks(student_form.i_mark_physics, "Physics:");
		print_student_marks(student_form.i_mark_bel, "Belarussian:");
		print_student_marks(student_form.i_mark_chem, "Chemistry:");
		print_student_marks(student_form.i_mark_inf, "Informatics:");
		printf("\n\nMedian mark:     %.1f", student_form.d_median);

	}

	static void generate_marks(int* p_i_marks_array, int i_strength) {
		int i_marks_count = 4 + my_random(8, 0);

		for (int j = 0; j < 16; ++j) {                   // Replacing marks with debug values
			p_i_marks_array[j] = -1;
		}

		int i_placed_count = 0;

		while (i_placed_count < i_marks_count) {         // Would place i_marks_count amount of marks
			int i_random_index = my_random(16, 0);

			if (p_i_marks_array[i_random_index] == -1) { // Continue if index already has mark
				if (i_strength > 824) {
					p_i_marks_array[i_random_index] = 7 + my_random(3, 0);
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

	static double get_median(Student_form& student_form) {
		size_t sz_header = sizeof(student_form.i_number) + sizeof(student_form.ch_name) + sizeof(student_form.ch_surname) + sizeof(student_form.birth_date);

		size_t sz_marks_fields_size = sizeof(Student_form) - sz_header - sizeof(student_form.d_median);

		int i_mark_slots_amount = sz_marks_fields_size / sizeof(int);

		// Moving the byte pointer to the marks fields start and then converting it to the int pointer. NumNameSurnameBirthDateMathPhysics...  NumNameSurnameBirthDateMathPhysics...
		//                                                                                              ^                                                             ^
		const int* p_i_marks = (const int*)((const char*)&student_form + sz_header); // Pointer on start of marks

		int i_marks_sum{};
		int i_marks_amount{};
		for (int i = 0; i < i_mark_slots_amount; ++i) {
			int i_mark = p_i_marks[i];

			if (i_mark == -1) continue;
			i_marks_sum += i_mark;
			++i_marks_amount;
		}

		return (double)i_marks_sum / (double)i_marks_amount;

	}

	static void show_students_filtered(FILE* Students_database, long l_target = -1, Command filter = Sh_all, Command filter_mode = No_command, double d_median_input = -1) {
		Database_info database_info{ 0, 0, 0 };
		Student_form student_form = { 0, "", "", 0, 0 };

		fseek(Students_database, 0, SEEK_SET);                            // Collecting info for moving cursor in file
		fread((char*)&database_info, sizeof(Database_info), 1, Students_database);

		int i_students_to_read{};
		if (l_target == -1) { // All
			fseek(Students_database, sizeof(Database_info), SEEK_SET);

			for (int k = 0; k < database_info.i_groups_amount; k++) {
				i_students_to_read += database_info.i_students_in_group_amount[k];
			}
		}
		else {                   // Group or one
			int i_offset = sizeof(Database_info);

			if (filter == Sh_one) {
				i_offset = l_target;
				i_students_to_read = 1;
			}
			else {     // Sh_group
				for (int i = 0; i < database_info.i_groups_amount; ++i) {     // Calculating an offset to the target group from the start of the file by using parallel arrays
					if (l_target == database_info.i_group_numbers[i]) {       // If group numbers matched, we need to read amount of the students as in matched group
						i_students_to_read = database_info.i_students_in_group_amount[i];
						break;
					}

					i_offset += database_info.i_students_in_group_amount[i] * sizeof(Student_form);
				}
			}
		
			fseek(Students_database, i_offset, SEEK_SET);
		}


		//if (i_target_group == -1) i_students_to_read = database_info.i_groups_amount * database_info.i_students_amount;
		//else i_students_to_read = database_info.i_students_amount;


		// Here is better to copy fread() everywhere then write it once and in every iteration check bunch of "if's"
		int i_students_amount_to_display = 0;
		if (filter == Sh_all) {
			while (fread((char*)&student_form, sizeof(Student_form), 1, Students_database) && i_students_to_read != 0) {
				print_student_form(student_form);
				--i_students_to_read;
				++i_students_amount_to_display;
			}
			if (l_target == -1) printf("\n\n\n\nAmount of students in all groups is %d\n\n\n", i_students_amount_to_display);
			else                      printf("\n\n\n\nAmount of students in group %d is %d\n\n\n", l_target, i_students_amount_to_display);
		}
		else if (filter == Sh_best) {
			while (fread((char*)&student_form, sizeof(Student_form), 1, Students_database) && i_students_to_read != 0) {
				bool b_good_student = false;

				if (filter_mode == Sh_best_marks) {
					for (int i = 0; i < 16; ++i) {
						if (student_form.i_mark_math[i] > 9 || student_form.i_mark_physics[i] == 7 || student_form.i_mark_physics[i] == 8) {
							b_good_student = true;
							++i_students_amount_to_display;
							break;
						}
					}
				}
				else {          // Sh_best_median
					if (student_form.d_median >= d_median_input) {
						b_good_student = true;
						++i_students_amount_to_display;
					}
				}

				if (b_good_student) print_student_form(student_form);
				--i_students_to_read;
			}

			if (i_students_amount_to_display == 0) {
				printf("\n\n\nNo good students :(\n\n\n");
			}
			else {
				if (l_target == -1) {
					if (filter_mode == Sh_best_marks) {
						printf("\n\n\n\nAmount of good students in all groups is %d\n\n\n", i_students_amount_to_display);
					}
					else if (filter_mode == Sh_best_median) {
						printf("\n\n\n\nAmount of good students in all groups with median mark minimal of %.1f is %d\n\n\n", d_median_input, i_students_amount_to_display);
					}
				}
				else {
					if (filter_mode == Sh_best_marks) {
						printf("\n\n\n\nAmount of good students in group %d is %d\n\n\n", l_target, i_students_amount_to_display);
					}
					else if (filter_mode == Sh_best_median) {
						printf("\n\n\n\nAmount of good students in group %d with median mark minimal of %.1f is %d\n\n\n", l_target, d_median_input, i_students_amount_to_display);
					}
				}
			}
		}
		else if (filter == Sh_one) {
			while (fread((char*)&student_form, sizeof(Student_form), 1, Students_database) && i_students_to_read != 0) {
				print_student_form(student_form);
				--i_students_to_read;
			}
		}

	}

	static void del_student(FILE* Students_database, long l_student_position) {
		Database_info database_info;

		fread(&database_info, sizeof(Database_info), 1, Students_database);

		long l_write_position = l_student_position;                                       // Position of the student to rewrite

		fseek(Students_database, l_student_position + sizeof(Student_form), SEEK_SET);    // Moving cursor to the next student

		Student_form student_form_buffer;
		while (fread(&student_form_buffer, sizeof(Student_form), 1, Students_database)) { // Reading this "next" student to buffer
			long l_resume_read_position = ftell(Students_database);                       // Saving position of the "next" student

			fseek(Students_database, l_write_position, SEEK_SET);                         // Moving cursor to the "rewrite" student

			fwrite(&student_form_buffer, sizeof(Student_form), 1, Students_database);     // Rewriting

			l_write_position += sizeof(Student_form);                                     // Setting following student to "rewrite" student

			fseek(Students_database, l_resume_read_position, SEEK_SET);                   // Moving cursor to the next student
		}

		int i_fd = _fileno(Students_database); // File descriptor (unique file number)
		long l_current_size = _filelength(i_fd);
		_chsize_s(i_fd, l_current_size - sizeof(Student_form)); // Shrinking file size to the position before extra student
	}

	static Operation_code input_subject_marks(int* p_i_marks_array, const char* ch_subject_name) {
		for (int i = 0; i < 16; ++i) p_i_marks_array[i] = -1; // Filling the array

		int iter{ 0 };
		Operation_code operation_code{ First_iter };

		while (iter < 16) {
			system("cls");

			if (operation_code == Quit) {
				system("cls");
				return Quit;
			}
			else if (operation_code == Back) {
				(void)buffer_clean();
				return Back;
			}

			printf("\nInput marks for %s.\n"
				"Range: 1 to 10 (or -1 for no mark).\n"
				"Prefer [Enter] after every member.\n"
				"\n[q] - quit\n"
				"[b] - back\n\n", ch_subject_name);

			if (operation_code != First_iter) {
				//printf("Current: ");
				for (int j = 0; j < iter; ++j) {
					printf("%d ", p_i_marks_array[j]);
				}
				//printf("\n");
			}

			operation_code = array_input_handler(iter, p_i_marks_array, 10, 1);

			while (operation_code == Not_val_size || operation_code == Not_val_num) {
				if (operation_code != Good) (void)buffer_clean();

				if (operation_code == Not_val_size) {
					printf("\nNot valid mark range. Range is 1-10 (or -1).");
				}

				printf("\nInput mark number %d again:\n", iter + 1);

				operation_code = array_input_handler(iter, p_i_marks_array, 10, 1);
			}

			if (p_i_marks_array[iter] == 0) {
				printf("\nMark cannot be 0. Use -1 for empty or 1-10.");
				Sleep(1000);
				continue;
			}

			if (p_i_marks_array[iter] != -1) {
				p_i_marks_array[iter] = my_abs(p_i_marks_array[iter]); // If mark accidentally lower then zero
			}

			++iter;
		}
		(void)buffer_clean();
		return Good;
	}

// Handles both only changing student form (Change_student in lab8) and editing file (create_database_manual)
static Operation_code change_student(Student_form& student_form, bool b_creation_mode, FILE* Students_database = NULL, long l_student_position = 0) {
	enum Change_info {
		Ch_id = '1',
		Ch_name,
		Ch_surname,
		Ch_date,
		Ch_marks,
		Ch_del
	};

	while (1) {
		system("cls");

		print_student_form(student_form);

		printf(
			"\n\n\nChoose what to change in student information.\n"
			"[1] - student's id\n"
			"[2] - student's name\n"
			"[3] - student's surname\n"
			"[4] - student's birth date\n"
			"[5] - student's marks\n"
		);

		if (!b_creation_mode) {
			printf("[6] - delete student\n");
			printf("\n[q] - quit\n[b] - back\n");
		}
		else {
			printf("\n[e] - NEXT STUDENT (Save & Continue)\n");
			printf("\n[q] - quit (Stop input)\n");
		}

		bool b_back_the_screen = false;
		Change_info ch_inf_filter{};
		Operation_code cod_screen_backwards{};

		long l_offset_to_field = l_student_position; // To calculate offsets for file writing

		while (2) {
			// Maybe it's better to rewrite the whole struct, because of byte alignment, but I think that it doesn't matter today, so it rewrites only one field at the time.
			// Temporary variables used because database could be left unchanged and because of that not to 'fread' every time this happened
			switch (ch_inf_filter = (Change_info)_getch()) {
			case Ch_id: {
				system("cls");
				print_student_form(student_form);

				int i_new_id{};
				cod_screen_backwards = number_input_handler("\n\n\nInput student's new id (or quit [q], back [b]) :\n", i_new_id, 1);

				if (cod_screen_backwards == Quit) return Quit;
				else if (cod_screen_backwards == Back) {
					b_back_the_screen = true;
					break;
				}

				student_form.i_number = i_new_id;

				if (!b_creation_mode) {
					fseek(Students_database, l_offset_to_field, SEEK_SET);
					fwrite((char*)&student_form.i_number, sizeof(student_form.i_number), 1, Students_database);
				}
				break;
			}

			case Ch_name:
			case Ch_surname: {
				l_offset_to_field += sizeof(student_form.i_number);

				while (3) {
					system("cls");
					print_student_form(student_form);

					if (ch_inf_filter == Ch_name) printf("\n\n\nInput student's new name (or quit [q], back [b]) :\n");
					else                          printf("\n\n\nInput student's new surname (or quit [q], back [b]) :\n");

					char ch_new_name[16];
					scanf_s("%15s", ch_new_name, 16);

					cod_screen_backwards = change_menu(ch_new_name, 1);
					if (cod_screen_backwards == Quit) return Quit;
					else if (cod_screen_backwards == Back) {
						b_back_the_screen = true;
						break;
					}

					if (buffer_clean()) {
						system("cls");
						printf("\nToo long. Input not more then 15 symbols, do not use spaces.");
						Sleep(1800);
						continue;
					}

					if (ch_inf_filter == Ch_name) {
						strcpy_s(student_form.ch_name, ch_new_name);

						if (!b_creation_mode) {
							fseek(Students_database, l_offset_to_field, SEEK_SET);
							fwrite(student_form.ch_name, sizeof(student_form.ch_name), 1, Students_database);
						}
					}
					else {
						l_offset_to_field += sizeof(student_form.ch_name);

						strcpy_s(student_form.ch_surname, ch_new_name);

						if (!b_creation_mode) {
							fseek(Students_database, l_offset_to_field, SEEK_SET);
							fwrite((char*)&student_form.ch_surname, sizeof(student_form.ch_surname), 1, Students_database);
						}
					}

					break;
				}
				break;
			}

			case Ch_date: {
				l_offset_to_field += sizeof(student_form.i_number) + sizeof(student_form.ch_name) + sizeof(student_form.ch_surname);

				while (3) {
					int i_new_day{},     i_new_month{},     i_new_year{};
					int i_current_day{}, i_current_month{}, i_current_year{};

					//system("cls");
					//print_student_form(student_form);

					//if ((cod_screen_backwards = number_input_handler("\n\n\nInput student's new day (1-31) (q/b) :\n", i_new_day, 1))) break;
					//if (i_new_day < 1 || i_new_day > 31) { printf("\nInvalid range."); Sleep(1000); continue; }

					//if ((cod_screen_backwards = number_input_handler("\n\n\nInput student's new month (1-12) (q/b) :\n", i_new_month, 1))) break;
					//if (i_new_month < 1 || i_new_month > 12) { printf("\nInvalid range."); Sleep(1000); continue; }

					//if ((cod_screen_backwards = number_input_handler("\n\n\nInput student's new year (q/b) :\n", i_new_year, 1))) break;

					system("cls");
					print_student_form(student_form);
					while (4) {
						cod_screen_backwards = number_input_handler("\n\n\nInput student's new day of birth (1-31)  (or quit [q], back [b]) :\n", i_new_day, 1);

						if (!cod_screen_backwards && (i_new_day < 1 || i_new_day > 31)) {
							printf("\n\nNot valid range. Input day from 1 to 31.");
							continue;
						}

						break;
					}

					system("cls");
					print_student_form(student_form);
					while (!cod_screen_backwards) {
						cod_screen_backwards = number_input_handler("\n\n\nInput student's new month of birth (1-12)  (or quit [q], back [b]) :\n", i_new_month, 1);

						if (!cod_screen_backwards && (i_new_month < 1 || i_new_month > 12)) {
							printf("\n\nNot valid range. Input month from 1 to 12.");
							continue;
						}

						break;
					}

					time_t t = time(NULL);                                                            // Getting seconds since 1900 year
					struct tm tm_info;                                                                // Creating formatted structure
					localtime_s(&tm_info, &t);                                                        // Writing pack of raw seconds to the formatted structure

					char ch_current_year_buffer[5];
					strftime(ch_current_year_buffer, sizeof(ch_current_year_buffer), "%Y", &tm_info); // Pulling what we need from structure and writing it as char string
					i_current_year = atoi(ch_current_year_buffer);

					system("cls");
					print_student_form(student_form);
					while (!cod_screen_backwards) {
						cod_screen_backwards = number_input_handler("\n\n\nInput student's new year of birth (or quit [q], back [b]) :\n", i_new_year, 1);

						if (!cod_screen_backwards && (i_new_year < 1 || i_new_year > i_current_year)) {
							printf("\n\nNot valid range. Input year from 1 to %d.", i_current_year);
							continue;
						}

						break;
					}
					if (cod_screen_backwards) break;

					char ch_current_day_buffer[3];
					strftime(ch_current_day_buffer, sizeof(ch_current_day_buffer), "%d", &tm_info);
					i_current_day = atoi(ch_current_day_buffer);

					char ch_current_month_buffer[3];
					strftime(ch_current_month_buffer, sizeof(ch_current_month_buffer), "%m", &tm_info);
					i_current_month = atoi(ch_current_month_buffer);

					bool b_is_future = false;                                                         // Checking that input date not in the future
					if (i_new_year > i_current_year) b_is_future = true;

					else if (i_new_year == i_current_year) {
						if (i_new_month > i_current_month) b_is_future = true;

						else if (i_new_month == i_current_month) {
							if (i_new_day > i_current_day) b_is_future = true;
						}
					}

					if (b_is_future) {
						system("cls");
						printf("\nNot valid date. Your date: %02d.%02d.%d .  Current date is %02d.%02d.%d .",
							i_new_day, i_new_month, i_new_year, i_current_day, i_current_month, i_current_year);
						Sleep(5500);
						continue;
					}

					student_form.birth_date.i_day = i_new_day;
					student_form.birth_date.i_month = i_new_month;
					student_form.birth_date.i_year = i_new_year;

					if (!b_creation_mode) {
						fseek(Students_database, l_offset_to_field, SEEK_SET);
						fwrite((char*)& student_form.birth_date, sizeof(student_form.birth_date), 1, Students_database);
					}
					break;
				}
				if (cod_screen_backwards == Quit) return Quit;
				else if (cod_screen_backwards == Back) b_back_the_screen = true;

				break;
			}

			case Ch_marks: {
				l_offset_to_field += sizeof(student_form.i_number) + sizeof(student_form.ch_name) + sizeof(student_form.ch_surname) + sizeof(student_form.birth_date);
				size_t sz_mark_field_size = sizeof(int) * 16;
				long l_offset_to_marks_array{};

				while (3) {
					cod_screen_backwards = No_code;
					system("cls");
					print_student_form(student_form);

					puts(
						"\n\n\nChoose what marks to change.\n"
						"[1] - Physics\n"
						"[2] - Mathematics\n"
						"[3] - Belarussian language\n"
						"[4] - Chemistry\n"
						"[5] - Informatics\n"
						"\n[q] - quit\n"
						"[b] - back\n"
					);

					int* p_i_marks_buffer{};
					const char* ch_subject_name{};

					while (4) {
						char ch_mark_filter = _getch();

						switch (ch_mark_filter) {
						case '1':
							l_offset_to_marks_array = l_offset_to_field;
							p_i_marks_buffer = student_form.i_mark_physics;
							ch_subject_name = "Physics";
							break;
						case '2':
							l_offset_to_marks_array = l_offset_to_field + sz_mark_field_size;
							p_i_marks_buffer = student_form.i_mark_math;
							ch_subject_name = "Mathematics";
							break;
						case '3':
							l_offset_to_marks_array = l_offset_to_field + sz_mark_field_size * 2;
							p_i_marks_buffer = student_form.i_mark_bel;
							ch_subject_name = "Belarussian language";
							break;
						case '4':
							l_offset_to_marks_array = l_offset_to_field + sz_mark_field_size * 3;
							p_i_marks_buffer = student_form.i_mark_chem;
							ch_subject_name = "Chemistry";
							break;
						case '5':
							l_offset_to_marks_array = l_offset_to_field + sz_mark_field_size * 4;
							p_i_marks_buffer = student_form.i_mark_inf;
							ch_subject_name = "Informatics";
							break;

						case 'b':
						case 'B':
							b_back_the_screen = true;
							break;

						case 'q':
						case 'Q':
							return Quit;

						default: continue;
						}
						if (b_back_the_screen) break;

						cod_screen_backwards = input_subject_marks(p_i_marks_buffer, ch_subject_name); // More clear. And easier to read, maybe

						break;
					}
					if (b_back_the_screen) break;

					if (cod_screen_backwards == Good) {
						student_form.d_median = get_median(student_form);

						if (!b_creation_mode) {
							fseek(Students_database, l_offset_to_marks_array, SEEK_SET);
							fwrite((char*)p_i_marks_buffer, sz_mark_field_size, 1, Students_database); // Already a pointer. No no need in &. Or (char*)&p_i_marks_buffer[0]

							fseek(Students_database, l_student_position + sizeof(student_form) - sizeof(student_form.d_median), SEEK_SET);
							fwrite(&student_form.d_median, sizeof((char*)&student_form.d_median), 1, Students_database);

							system("cls");
							printf("\nChanging...");
							Sleep(800);
							system("cls");
							printf("\nDone.");
							Sleep(800);
							system("cls");
						}
						else {
							system("cls");
							printf("\nChanging...");
							Sleep(450);
						}

						
						continue;
					}
					else if (cod_screen_backwards == Quit) return Quit;
					else if (cod_screen_backwards == Back) continue;

					break;
				}
				break;
			}

			case Ch_del:
				if (b_creation_mode) continue;
				return Not_val_num; // Return code for deleting student

			case 'e':
			case 'E':
				if (!b_creation_mode) continue;
				return Good;        // Return code for proceeding to the next student

			case 'b':
			case 'B':
				if (b_creation_mode) continue;
				return Back;

			case 'q':
			case 'Q':
				return Quit;

			default: continue;
			}
			break;
		}
		if (b_back_the_screen) continue;

		if (ch_inf_filter != Ch_del && ch_inf_filter != 'e' && ch_inf_filter != 'E') {
			if (!b_creation_mode) { 
				system("cls");
				printf("\nChanging...");
				Sleep(800);
				system("cls");
				printf("\nDone.");
				Sleep(800);
				system("cls");
			}
			else {
				system("cls");
				printf("\nChanging...");
				Sleep(450);
			}
		}
	}
}

#define ENTER_DATABASE_INFO(i_amount_of_parameter, i_min_range, i_max_range, ch_message, i_group_by_count)\
while (1) {\
	Operation_code cod_screen_backwards = number_input_handler(ch_message, i_amount_of_parameter, 1, i_group_by_count);\
	if (cod_screen_backwards == Quit) {\
		fclose(Students_database);\
		system("cls");\
		return;\
	}\
	else if (cod_screen_backwards == Back) {\
		system("cls");\
		fclose(Students_database);\
		return;\
	}\
	if (i_amount_of_parameter < i_min_range || i_amount_of_parameter > i_max_range) {\
		system("cls");\
		printf("\nNot valid range.\n\n");\
		Sleep(1500);\
		continue;\
	}\
	break;\
}\


static void create_database_manual(FILE* Students_database, Database_info& db_info) {
	int i_amount_of_groups{};
	ENTER_DATABASE_INFO(i_amount_of_groups, 1, 6, "\nInput amount of groups from 1 to 6 (quit [q], back [b]) :\n", 0);
	db_info.i_groups_amount = i_amount_of_groups;

	system("cls");

	for (int i = 0; i < i_amount_of_groups; ++i) { // Input Students Amount per Group
		ENTER_DATABASE_INFO(db_info.i_students_in_group_amount[i], 1, 10, "\nInput amount of students in %d group from 1 to 10 (quit [q], back [b]) :\n", i + 1);
		system("cls");

		db_info.i_group_numbers[i] = i + 1;
	}

	// Write header
	fseek(Students_database, 0, SEEK_SET);
	fwrite(&db_info, sizeof(Database_info), 1, Students_database);

	Student_form temp_student;

	for (int g = 0; g < i_amount_of_groups; ++g) {
		for (int s = 0; s < db_info.i_students_in_group_amount[g]; ++s) {

			// Initialization
			temp_student.i_number = (db_info.i_group_numbers[g]) * 1000 + (s + 1); // When formatted will be 001001, 001002...
			strcpy_s(temp_student.ch_name, "-");
			strcpy_s(temp_student.ch_surname, "-");
			temp_student.birth_date = { 1, 1, 2000 };

			for (int k = 0; k < 16; ++k) {
				temp_student.i_mark_physics[k] = -1;
				temp_student.i_mark_math[k] = -1;
				temp_student.i_mark_bel[k] = -1;
				temp_student.i_mark_chem[k] = -1;
				temp_student.i_mark_inf[k] = -1;
			}
			temp_student.d_median = 0.0;

			printf("\nInitializing Student %06d...\n", temp_student.i_number);
			Sleep(800);

			Operation_code op = change_student(temp_student, true);

			if (op == Quit) return;

			fwrite(&temp_student, sizeof(Student_form), 1, Students_database);

			system("cls");
			printf("\nStudent saved.\n");
			Sleep(300);
		}
	}

	printf("\nDatabase generation complete.\n");
	Sleep(1000);
}

static void lab_8() {
		while (1) {
			puts(
				"\nStudents sample database generator.\n\n"
				"[1] - recreate database randomly\n"
				"[2] - recreate database manually (amount of groups and students)\n"
				"[3] - show all students\n"
				"[4] - show students in group\n"
				"[5] - change student information\n"
				"\n[q] - quit\n"
			);

			Command cmd_general{};
			while (2) {
				switch (_getch()) {
				case '1':
					cmd_general = Regen_database_random;
					break;

				case '2':
					cmd_general = Regen_database_manual;
					break;

				case '3':
					cmd_general = Sh_all;
					break;

				case '4':
					cmd_general = Sh_group;
					break;

				case '5':
					cmd_general = Change_student;
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

			Database_info database_info = { 0, 0, 0 };

			FILE* Students_database = NULL;

			bool b_no_database = false;
			bool b_back_the_screen = false;
			do {
				int i_amount_of_groups{};
				if (cmd_general == Regen_database_random || cmd_general == Regen_database_manual) {
					if (fopen_s(&Students_database, "students_data.dat", "w+b")) {
						b_no_database = true;
						break;
					}

					generate_seed();

					if (cmd_general == Regen_database_random) {
						database_info.i_groups_amount = i_amount_of_groups = 2 + my_random(4, 0);
						//database_info.i_students_amount = i_amount_of_students = 2 + my_random(8, 0);

						for (int i = 0; i < i_amount_of_groups; ++i) {
							database_info.i_students_in_group_amount[i] = 2 + my_random(10, 0);
						}
					}
					else {          // Regen_database_manual
						create_database_manual(Students_database, database_info);
						fclose(Students_database);
						system("cls");
						break;
					}

					for (int g = 0; g < i_amount_of_groups; ++g) {       // The iterator for filling group numbers
						database_info.i_group_numbers[g] = my_random(482, 0);
					}

					fwrite((int*)&database_info, sizeof(Database_info), 1, Students_database);

					for (int g = 0; g < i_amount_of_groups; ++g) {       // Generate groups
						int i_group_number = database_info.i_group_numbers[g] * 1000 + my_random(432, 0);

						for (int i = 0; i < database_info.i_students_in_group_amount[g]/*i_amount_of_students*/; ++i) { // Generate students
							int i_strength = my_random(1000, 0);

							student_form.i_number = i_group_number + i;

							const char* ch_random_name{};

							ch_random_name = get_name(FirstN, my_random(119, 0));
							strcpy_s(student_form.ch_name, sizeof(student_form.ch_name), ch_random_name);

							ch_random_name = get_name(LastN, my_random(119, 0));
							strcpy_s(student_form.ch_surname, sizeof(student_form.ch_surname), ch_random_name);

							student_form.birth_date.i_day = 1 + my_random(30, 0);
							student_form.birth_date.i_month = 1 + my_random(11, 0);
							student_form.birth_date.i_year = 2006 + my_random(2, 0);

							generate_marks(student_form.i_mark_math, i_strength);
							generate_marks(student_form.i_mark_physics, i_strength);
							generate_marks(student_form.i_mark_bel, i_strength);
							generate_marks(student_form.i_mark_chem, i_strength);
							generate_marks(student_form.i_mark_inf, i_strength);

							student_form.d_median = get_median(student_form);

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

				if (fopen_s(&Students_database, "students_data.dat", "r+b")) {
					b_no_database = true;
					break;
				}

				Command cmd_filter{};
				Command cmd_filter_mode{};
				if (cmd_general == Change_student) {
					fread((char*)&database_info, sizeof(Database_info), 1, Students_database);

					int i_student_id_to_change{};
					while (3) {
						system("cls");
						show_students_filtered(Students_database);
						fseek(Students_database, sizeof(database_info), SEEK_SET);

						Operation_code cod_screen_backwards = number_input_handler("\nChoose student by id to change from listed (or quit [q], back [b]) :\n", i_student_id_to_change, 1);
						if (cod_screen_backwards == Quit) {
							fclose(Students_database);
							system("cls");
							return;
						}
						else if (cod_screen_backwards == Back) {
							fclose(Students_database);
							system("cls");
							b_back_the_screen = true;
							break;
						}

						bool b_student_exists = false;
						long l_student_position{};
						int i_group_index{};
						for (int g = 0; g < database_info.i_groups_amount; ++g) {                        // Iterator to catch student and to change students amount in database info
							int i_students_count = database_info.i_students_in_group_amount[g];

							for (int s = 0; s < i_students_count; ++s) {
								long l_current_position = ftell(Students_database);                      // Saving student we reading position

								fread((char*)&student_form, sizeof(Student_form), 1, Students_database); // Reading

								if (student_form.i_number == i_student_id_to_change) {
									b_student_exists = true;
									l_student_position = l_current_position;                             // If student exists, we have it in student_form and we have it's position
									i_group_index = g;                                                   // Also group index in parallel arrays
									break;
								}	
							}
							if (b_student_exists) break;
						}

						if (!b_student_exists) {
							system("cls");
							printf("\nNo such student. Input existing student number.\n\n");
							Sleep(1500);
							system("cls");
							continue;
						}

						Operation_code change_return = change_student(student_form, false, Students_database, l_student_position);

						if (change_return == Quit) {
							fclose(Students_database);
							system("cls");
							return;
						}
						else if (change_return == Not_val_num) { // Delete
							del_student(Students_database, l_student_position);

							--database_info.i_students_in_group_amount[i_group_index];
							fseek(Students_database, 0, SEEK_SET);
							fwrite(&database_info, sizeof(Database_info), 1, Students_database);

							system("cls");
							printf("\nDeleting...");
							Sleep(1000);
							system("cls");
							printf("\nDone.");
							Sleep(800);
							system("cls");

							continue;
						}
					}
					if (b_back_the_screen) break;
				}

				int i_group_number = -1;
				if (cmd_general == Sh_group) {
					system("cls");
					fread((char*)&database_info, sizeof(Database_info), 1, Students_database);

					while (3) {
						printf("\nAvailable groups:\n");
						for (int i = 0; i < database_info.i_groups_amount; ++i) {
							printf("%d ", database_info.i_group_numbers[i]);
						}

						Operation_code cod_screen_backwards = number_input_handler("\n\nInput wanted group number (or quit [q], back [b]) :\n", i_group_number, 1);
						if (cod_screen_backwards == Quit) {
							fclose(Students_database);
							system("cls");
							return;
						}
						else if (cod_screen_backwards == Back) {
							fclose(Students_database);
							system("cls");
							b_back_the_screen = true;
							break;
						}

						int i_not_matched_groups_amount = 0;
						for (int i = 0; i < database_info.i_groups_amount; ++i) {
							if (i_group_number != database_info.i_group_numbers[i]) {
								++i_not_matched_groups_amount;
							}						
						}
						if (i_not_matched_groups_amount == database_info.i_groups_amount) {
							system("cls");
							printf("\nNo such group. Input existing group number.\n\n");
							Sleep(1000);
							continue;
						}

						system("cls");
						break;
					}
					if (b_back_the_screen) break;
				}

				while (3) {
					if (cmd_general == Sh_all) puts("\nShow all students menu\n");
					else if (cmd_general == Sh_group) printf("\nShow students in group %d menu\n\n", i_group_number);
					puts(
						"[1] - show all students\n"
						"[2] - show best students by marks (physics 7 and 8, math > 9)\n"
						"[3] - show best students by median\n"
						"\n[q] - quit\n"
						"[b] - back to start\n"
					);

					while (4) {
						switch (_getch()) {
						case '1':
							cmd_filter = Sh_all;
							break;

						case '2':
							cmd_filter = Sh_best;
							cmd_filter_mode = Sh_best_marks;
							break;

						case '3':
							cmd_filter = Sh_best;
							cmd_filter_mode = Sh_best_median;
							break;

						case 'b':
						case 'B':
							b_back_the_screen = true;
							fclose(Students_database);
							break;

						case 'q':
						case 'Q':
							fclose(Students_database);
							system("cls");
							return;

						default: continue;
						}
						system("cls");
						break;
					}
					if (b_back_the_screen) break;

					if (cmd_filter == Sh_all) show_students_filtered(Students_database, i_group_number);

					else if (cmd_filter == Sh_best) {
						if (cmd_filter_mode == Sh_best_marks) show_students_filtered(Students_database, i_group_number, cmd_filter, cmd_filter_mode);

						else if (cmd_filter_mode == Sh_best_median) {
							double d_median{};

							bool b_back_to_menu = false;
							while (4) {
								Operation_code cod_screen_backwards = number_input_handler("\nInput median mark in range from 1 to 10 to filter students:\n", d_median, 1);
								if (cod_screen_backwards == Quit) {
									fclose(Students_database);
									system("cls");
									return;
								}
								else if (cod_screen_backwards == Back) {
									system("cls");
									fclose(Students_database);
									b_back_to_menu = true;
									break;
								}

								if (d_median < 1 || d_median > 10) {
									system("cls");
									printf("\nNot valid range.\n\n");
									Sleep(1500);
									continue;
								}
								break;
							}
							if (b_back_to_menu) continue;

							system("cls");
							show_students_filtered(Students_database, i_group_number, cmd_filter, cmd_filter_mode, d_median);
						}
					}
				}
			} while (0);
			if (b_no_database) {
				printf("\nNo database. Try again or restart application.\n");
				Sleep(1500);
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
			"Cycled algorithms and user functions [3]  Matrixes [6]  Plotting functions          [ ]\n"
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

			case 27: exit(0);
				/*printf("     Press [Esc] again to exit.");

				if (_getch() == 27) exit(0);

				else {
					system("cls");
					break;
				}*/

			default: continue;
			}
			break;
		}
	}
}
// END