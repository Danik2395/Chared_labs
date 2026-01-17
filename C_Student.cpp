//
// C_Student.cpp
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Class instead of struct for easy workflow in lab 8.
//


#include "C_Student.h"
#include <Windows.h>


C_Student::C_Student() {                   // Initializing everything with zeros and dynamic arrays with NULL
	i_number = i_current_marks_count = d_median = 0;
	for (int i = 0; i < 16; ++i) {
		ch_name[i] = ch_surname[i] = 0;
	}
	St_birth_date = { 0, 0, 0 };

	p_i_mark_physics = p_i_mark_math = p_i_mark_bel = p_i_mark_chem = p_i_mark_inf = NULL;
}



C_Student::~C_Student() { free_mark_arrays(); } // Free dynamic arrays
										        // To not to fuss with infinite "while's"
										        // Main reason to do this with class instead of struct



void C_Student::free_mark_arrays() {
	free(p_i_mark_physics);
	free(p_i_mark_math);
	free(p_i_mark_bel);
	free(p_i_mark_chem);
	free(p_i_mark_inf);
	p_i_mark_physics = p_i_mark_math = p_i_mark_bel = p_i_mark_chem = p_i_mark_inf = NULL;
}



void C_Student::init_mark_arrays(int i_count) {
	i_current_marks_count = i_count;
	free_mark_arrays();

	p_i_mark_physics = (int*)calloc(i_count, sizeof(int));
	p_i_mark_math    = (int*)calloc(i_count, sizeof(int));
	p_i_mark_bel     = (int*)calloc(i_count, sizeof(int));
	p_i_mark_chem    = (int*)calloc(i_count, sizeof(int));
	p_i_mark_inf     = (int*)calloc(i_count, sizeof(int));

	for (int i = 0; i < i_count; ++i) {    // Initialize with -1
		p_i_mark_physics[i] = p_i_mark_math[i] = p_i_mark_bel[i] = p_i_mark_chem[i] = p_i_mark_inf[i] = -1;
	}

	d_median = 0.0;
}



void C_Student::reset_marks() {
	for (int i = 0; i < i_current_marks_count; ++i) {
		p_i_mark_physics[i] = p_i_mark_bel[i] = p_i_mark_math[i] = p_i_mark_chem[i] = p_i_mark_inf[i] = -1;
	}

	d_median = 0.0;
}



void C_Student::set_random_marks(int i_strength) {
	reset_marks();

	int* p_p_mark_arrays[] = { p_i_mark_physics, p_i_mark_math, p_i_mark_bel, p_i_mark_chem, p_i_mark_inf };
	
	for (int subj = 0; subj < 5; ++subj) {
		int i_marks_count = 4 + my_random(8, 0);
		int i_placed_count = 0;

		while (i_placed_count < i_marks_count) {         // Would place i_marks_count amount of marks
			int i_random_index = my_random(16, 0);

			if (p_p_mark_arrays[subj][i_random_index] == -1) {
				if (i_strength > 824) {
					p_p_mark_arrays[subj][i_random_index] = 7 + my_random(3, 0);
				}
				else if (i_strength < 327) {
					p_p_mark_arrays[subj][i_random_index] = 2 + my_random(4, 0);
				}
				else {
					p_p_mark_arrays[subj][i_random_index] = 3 + my_random(5, 0);
				}


				++i_placed_count;
			} 
			// Else continue, if index already has mark
		}
	}

	set_get_median();
}



double C_Student::set_get_median() {
	int* p_p_mark_arrays[] = { p_i_mark_physics, p_i_mark_math, p_i_mark_bel, p_i_mark_chem, p_i_mark_inf };

	int i_marks_sum{};
	int i_marks_amount{};
	for (int subj = 0; subj < 5; ++subj) {
		for (int i = 0; i < i_current_marks_count; ++i) {
			int i_mark = p_p_mark_arrays[subj][i];
			if (i_mark != -1) {
				++i_marks_amount;
				i_marks_sum += i_mark;
			}
		}
	}
	return d_median = (i_marks_amount == 0) ? 0.0 : (double)i_marks_sum / (double)i_marks_amount;
}



void C_Student::print() {
	printf("\n-----------------------------------------------------------------\nStudent number: %06d\nName:           %s\nSurname:        %s\nBirth day:      %02d.%02d.%d\nMarks:",
		i_number, ch_name, ch_surname, St_birth_date.i_day, St_birth_date.i_month, St_birth_date.i_year
	);

	int i_count = i_current_marks_count;
	print_marks(p_i_mark_math, i_count, "Math:");
	print_marks(p_i_mark_physics, i_count, "Physics:");
	print_marks(p_i_mark_bel, i_count, "Belarussian:");
	print_marks(p_i_mark_chem, i_count, "Chemistry:");
	print_marks(p_i_mark_inf, i_count, "Informatics:");
	printf("\n\nMedian mark:     %.1f", d_median);

}



void C_Student::print_marks(int* p_i_marks_array, int i_marks_cnt, const char* ch_subject_name) {
	printf("\n  %-14s", ch_subject_name);

	for (int j = 0; j < i_marks_cnt; ++j) {
		if (p_i_marks_array[j] == -1) {
			printf("   ");
			continue;
		}
		printf("%2d ", p_i_marks_array[j]);
	}
}



void C_Student::save_to_file(FILE* f) {
	fwrite(&i_number, sizeof(int), 1, f);
	fwrite(ch_name, sizeof(char), 16, f);
	fwrite(ch_surname, sizeof(char), 16, f);
	fwrite(&St_birth_date, sizeof(St_birth_date), 1, f);

	// Write arrays
	fwrite(p_i_mark_physics, sizeof(int), i_current_marks_count, f);
	fwrite(p_i_mark_math, sizeof(int), i_current_marks_count, f);
	fwrite(p_i_mark_bel, sizeof(int), i_current_marks_count, f);
	fwrite(p_i_mark_chem, sizeof(int), i_current_marks_count, f);
	fwrite(p_i_mark_inf, sizeof(int), i_current_marks_count, f);

	fwrite(&d_median, sizeof(double), 1, f);
}



bool C_Student::load_from_file(FILE* f) {
	if (fread(&i_number, sizeof(int), 1, f) != 1) return false;

	size_t sz_read_count = 0;

	sz_read_count += fread(ch_name, sizeof(char), 16, f);
	sz_read_count += fread(ch_surname, sizeof(char), 16, f);
	sz_read_count += fread(&St_birth_date, sizeof(St_birth_date), 1, f);

	sz_read_count += fread(p_i_mark_physics, sizeof(int), i_current_marks_count, f);
	sz_read_count += fread(p_i_mark_math, sizeof(int), i_current_marks_count, f);
	sz_read_count += fread(p_i_mark_bel, sizeof(int), i_current_marks_count, f);
	sz_read_count += fread(p_i_mark_chem, sizeof(int), i_current_marks_count, f);
	sz_read_count += fread(p_i_mark_inf, sizeof(int), i_current_marks_count, f);

	sz_read_count += fread(&d_median, sizeof(double), 1, f);

	size_t sz_expected = 16 + 16 + 1 + ((size_t)i_current_marks_count * 5) + 1;

	if (sz_read_count != sz_expected) return false;
	return true;
}
// It's too complicated to make real error handling and bulletproof database. Chance of such structured file corruption is low enough to not to bother with it



long C_Student::get_size() {
	return sizeof(int) + 16 + 16 + sizeof(St_birth_date) + (5 * i_current_marks_count * sizeof(int)) + sizeof(double);
	    // i_number + ch_name + ch_surname + St_birth_date +  5 marks arrays + d_median
}