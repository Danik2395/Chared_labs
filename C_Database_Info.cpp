//
// C_Database_Info.cpp
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Class instead of struct for easy workflow in lab 8.
//


#include "C_Database_Info.h"


C_Database_Info::C_Database_Info() {
	i_groups_amount = 0;
	i_marks_per_subject = 16; // 16, because of random database generation (default way)
	p_i_group_numbers = p_i_students_in_group_amount = NULL;
}



C_Database_Info::~C_Database_Info() {
	free(p_i_group_numbers);
	free(p_i_students_in_group_amount);
}



void C_Database_Info::init_arrays(int i_gr_amount) {
	i_groups_amount = i_gr_amount; // Field equals input value.

	free(p_i_group_numbers);       // To not to use realloc
	free(p_i_students_in_group_amount);

	p_i_group_numbers = (int*)calloc(i_groups_amount, sizeof(int));
	p_i_students_in_group_amount = (int*)calloc(i_groups_amount, sizeof(int));
}



void C_Database_Info::save_to_file(FILE* f) {
	fwrite(&i_groups_amount, sizeof(int), 1, f);
	fwrite(&i_marks_per_subject, sizeof(int), 1, f);

	if (i_groups_amount > 0) {
		// Writing as many ints as in value of i_groups_amount from allocated memory, that starts at p_i_..., to the file 
		fwrite(p_i_group_numbers, sizeof(int), i_groups_amount, f);
		fwrite(p_i_students_in_group_amount, sizeof(int), i_groups_amount, f);
	}
}



bool C_Database_Info::load_from_file(FILE* f) {
	if (fread(&i_groups_amount, sizeof(int), 1, f) != 1) return false;

	size_t sz_read_count = 0;
	sz_read_count += fread(&i_marks_per_subject, sizeof(int), 1, f);

	init_arrays(i_groups_amount);

	if (i_groups_amount > 0) {
		sz_read_count += fread(p_i_group_numbers, sizeof(int), i_groups_amount, f);
		sz_read_count += fread(p_i_students_in_group_amount, sizeof(int), i_groups_amount, f);
	}

	size_t sz_expected = 1 + (i_groups_amount > 0 ? ((size_t)i_groups_amount * 2) : 0);

	if (sz_read_count != sz_expected) return false;

	return true;
}



long C_Database_Info::get_size() {
	return sizeof(int) * 2 + (sizeof(int) * i_groups_amount * 2);
	// i_groups_amount + i_marks_per_subject + p_i_group_numbers + p_i_students_in_group_amount arrays
}