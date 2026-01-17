//
// C_Database_Info.h
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// C_Database_Info.cpp header.
//
#pragma once
#include <cstdlib>
#include <cstdio>

class C_Database_Info {
public:
	int i_groups_amount;
	int i_marks_per_subject;           // To track dynamic size of marks arrays in file.
	int* p_i_group_numbers;            // Parallel
	int* p_i_students_in_group_amount; // Arrays

	C_Database_Info();                 // Initialize  every field

	~C_Database_Info();                // Custom destructor to free dynamic arrays

	// p_i_group_numbers, p_i_students_in_group_amount  INIT  sizeof(i_gr_amount)
	void init_arrays(int i_gr_amount); 

	// Write all fields values in file one by one
	void save_to_file(FILE* f);

	// Read data from file to all fields one by one
	bool load_from_file(FILE* f);

	// Returns size of header in bytes that in current object
	long get_size();
};

