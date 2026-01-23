//
// Lab_8.h
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Lab_8.cpp header.
//
#pragma once
#include "C_Student.h"
#include "C_Database_Info.h"
#include "side_functions.h"
#include "operating_functions.h"
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <windows.h> // File and directory handling
#include <io.h>      // For _chsize
#include <time.h>
#include <direct.h>  // For _mkdir

#define MAX_FILES 64
#define MAX_FILE_NAME 64
//#define DIR_PATH "C:\\Users\\ASUS\\Documents\\Databases\\"
typedef unsigned long long file_sz; // Because size_t is depended on the used OS

static inline void printf_file_info(int i_f_num, char* ch_f_name, file_sz fsz_size) { printf("[%02d]  %-12s %10llu b\n", i_f_num, ch_f_name, fsz_size); }

static inline void print_logo() {
	printf(
		"  _____ ______  __ __  ___    ___     ____  ______ \n"
		" / ___/|      ||  |  ||   \\  |   \\   /    ||      |\n"
		"(   \\_ |      ||  |  ||    \\ |    \\ |  o  ||      |\n"
		" \\__  ||_|  |_||  |  ||  D  ||  D  ||     ||_|  |_|\n"
		" /  \\ |  |  |  |  :  ||     ||     ||  _  |  |  |  \n"
		" \\    |  |  |  |     ||     ||     ||  |  |  |  |  \n"
		"  \\___|  |__|   \\__,_||_____||_____||__|__|  |__|     \n"
	);
}

static inline void xor_file_hidden_attr(const char* ch_path_to_file) {
	DWORD attrb = GetFileAttributesA(ch_path_to_file);
	SetFileAttributesA(ch_path_to_file, attrb ^= FILE_ATTRIBUTE_HIDDEN);
}


enum Name_type { FirstN, LastN };
enum Command {
	No_command,
	Regen_database_manual,
	Regen_database_random,
	Sh_all,
	Sh_group,
	Sh_best,
	Sh_best_marks,
	Sh_best_median,
	Change_student
};

static char* dir_path();

// FirstN - first name
// LastN  - last name
static const char* get_name(Name_type name_type, size_t i_name_position);

static Operation_code show_students_filtered(FILE* Students_database, long l_target = -1, Command filter = Sh_all, Command filter_mode = No_command, double d_median_input = -1);

static Operation_code del_student(FILE* Students_database, long l_student_position, C_Database_Info& info);

static Operation_code input_subject_marks(int* p_i_marks_array, int i_marks_cnt, const char* ch_subject_name);

static Operation_code change_student(C_Student& student_form, bool b_creation_mode, FILE* Students_database = NULL, long l_student_position = 0);

static Operation_code create_database_manual(FILE* Students_database, C_Database_Info& db_info);

static Operation_code file_manager(FILE** p_p_Database, char** ch_f_name_dest, char* ch_dir_path);

static Operation_code temp_session(FILE** p_p_Database, const char* ch_original_path, char* ch_temp_path_dest);

static int commit_temp_session(FILE** p_p_Database, const char* ch_original_path, const char* ch_temp_path, int i_only_save = 0);

void lab_8();