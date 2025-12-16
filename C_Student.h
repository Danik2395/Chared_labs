//
// C_Student.h
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// C_Student.cpp header.
//
#pragma once
#include <cstdlib>
#include <cstdio>
#include "my_lib.h"

class C_Student {
public:
	int i_number;
	char ch_name[16];
	char ch_surname[16];
	struct {
		int i_day;
		int i_month;
		int i_year;
	} St_birth_date;

	// Dynamic arrays
	int i_current_marks_count; // To know how much marks in current object's arrays
	int* p_i_mark_physics;
	int* p_i_mark_math;
	int* p_i_mark_bel;
	int* p_i_mark_chem;
	int* p_i_mark_inf;

	double d_median;


	C_Student();

	~C_Student();

	void free_mark_arrays();

	// Initialize every value in mark arrays with -1
	void init_mark_arrays(int i_count);

	// Set every value of mark arrays to -1
	void reset_marks();

	// Setting random marks depending on strength of the student
	void set_random_marks(int i_strength);

	double set_get_median();

	// Print preformatted student form
	void print();

	// Writes fields to file one by one
	void save_to_file(FILE* f);

	// Reads data from file to all fields one by one
	bool load_from_file(FILE* f);

	// To calculate size of student form in file
	long get_size();

private:
	void print_marks(int* p_i_marks_array, int i_marks_cnt, const char* ch_subject_name);
};

