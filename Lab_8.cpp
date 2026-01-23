//
// Lab_8.cpp
//
//      Author:  Kalenkovich Daniil Alekseevich, 568405
//
// Too big for main file.
//


#include "Lab_8.h"

#define ENTER_DATABASE_INFO(i_amount_of_parameter, i_min_range, i_max_range, ch_message, i_group_by_count)\
while (1) {\
	Operation_code cod_screen_backwards = number_input_handler(ch_message, i_amount_of_parameter, 1, i_group_by_count);\
	if (cod_screen_backwards == Quit) return Quit;\
	else if (cod_screen_backwards == Back) return Back;\
	if (i_amount_of_parameter < i_min_range || i_amount_of_parameter > i_max_range) {\
		system("cls");\
		printf("\nNot valid range.\n\n");\
		Sleep(1500);\
		continue;\
	}\
	break;\
}\


#define READ_ERROR()\
system("cls");\
printf("\nError reading from file. Check file or recreate database\n\n");\
Sleep(2000);\
return Read_error;\


static char* dir_path() {
	static char ch_dir_path[MAX_PATH] = "C:\\Databases\\";
	return ch_dir_path;
}



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



static Operation_code show_students_filtered(FILE* Students_database, long l_target, Command filter, Command filter_mode, double d_median_input) {
	C_Database_Info database_info;
	C_Student student_form;

	fseek(Students_database, 0, SEEK_SET);                            // Collecting info for moving cursor in file
	if (!database_info.load_from_file(Students_database)) {
		READ_ERROR()
	}

	// Need to init student arrays to match file structure
	student_form.init_mark_arrays(database_info.i_marks_per_subject);
	long l_form_current_size = student_form.get_size();

	int i_students_to_read{};
	if (l_target == -1) { // All
		// Skip header
		fseek(Students_database, database_info.get_size(), SEEK_SET);

		for (int k = 0; k < database_info.i_groups_amount; k++) {
			i_students_to_read += database_info.p_i_students_in_group_amount[k];
		}
	}
	else {                // Group
		long i_offset = database_info.get_size();

		for (int i = 0; i < database_info.i_groups_amount; ++i) {       // Calculating an offset to the target group from the start of the file by using parallel arrays
			if (l_target == database_info.p_i_group_numbers[i]) {       // If group numbers matched, we need to read amount of the students as in matched group
				i_students_to_read = database_info.p_i_students_in_group_amount[i];
				break;
			}

			i_offset += (long)database_info.p_i_students_in_group_amount[i] * l_form_current_size;
		}

		fseek(Students_database, i_offset, SEEK_SET);
	}


	// Here is better to copy fread() everywhere then write it once and in every iteration check bunch of "ifs"
	int i_students_amount_to_display = 0;
	if (filter == Sh_all) {
		while (i_students_to_read != 0) {
			if (!student_form.load_from_file(Students_database)) {
				READ_ERROR()
			}

			student_form.print();
			--i_students_to_read;
			++i_students_amount_to_display;
		}
		if (l_target == -1) printf("\n\n\n\nAmount of students in all groups is %d\n\n\n", i_students_amount_to_display);
		else                printf("\n\n\n\nAmount of students in group %d is %d\n\n\n", l_target, i_students_amount_to_display);
	}
	else if (filter == Sh_best) {
		while (i_students_to_read != 0) {
			if (!student_form.load_from_file(Students_database)) {
				READ_ERROR()
			}

			bool b_good_student = false;

			if (filter_mode == Sh_best_marks) {
				for (int i = 0; i < student_form.i_current_marks_count; ++i) {
					if (student_form.p_i_mark_math[i] > 9 || student_form.p_i_mark_physics[i] == 7 || student_form.p_i_mark_physics[i] == 8) {
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

			if (b_good_student) student_form.print();
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
}



static Operation_code del_student(FILE* Students_database, long l_student_position, C_Database_Info& db_info) {
	long l_write_position = l_student_position;                                   // Position of the student to rewrite

	C_Student student_form_buffer;
	student_form_buffer.init_mark_arrays(db_info.i_marks_per_subject);
	long l_form_current_size = student_form_buffer.get_size();

	fseek(Students_database, l_student_position + l_form_current_size, SEEK_SET); // Moving cursor to the next student

	bool b_read_error = false;
	while (b_read_error = student_form_buffer.load_from_file(Students_database)) {// Reading "next" student
		long l_resume_read_position = ftell(Students_database);                   // Saving position of the "next" student
		fseek(Students_database, l_write_position, SEEK_SET);                     // Moving cursor to the position of the "deleted" student
		student_form_buffer.save_to_file(Students_database);                      // Rewriting "deleted" student with "next" student
		l_write_position += l_form_current_size;                                  // Moving write position to the next student
		fseek(Students_database, l_resume_read_position, SEEK_SET);               // Moving cursor to the position of the "next" student
	}
	if (b_read_error == true) READ_ERROR()

	int i_fd = _fileno(Students_database);                                        // File descriptor (unique file number)
	long l_file_current_size = _filelength(i_fd);
	_chsize_s(i_fd, l_file_current_size - l_form_current_size);                   // Shrinking file size to the position before extra student
}



static Operation_code input_subject_marks(int* p_i_marks_array, int i_marks_cnt, const char* ch_subject_name) {
	for (int i = 0; i < i_marks_cnt; ++i) p_i_marks_array[i] = -1; // Filling the array

	int iter{ 0 };
	Operation_code operation_code{ First_iter };

	while (iter < i_marks_cnt) {
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
static Operation_code change_student(C_Student& student_form, bool b_creation_mode, FILE* Students_database, long l_student_position) {
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
		student_form.print();

		printf(
			"\n\n\nChoose what to change in student information.\n"
			"[1] - student's id\n"
			"[2] - student's name\n"
			"[3] - student's surname\n"
			"[4] - student's birth date\n"
			"[5] - student's marks\n"
		);

		if (!b_creation_mode) printf("[6] - delete student\n\n[q] - quit\n[b] - back\n");
		else printf("\n[e] - NEXT STUDENT (Save & Continue)\n\n[q] - quit (Stop input)\n");

		bool b_back_the_screen = false;
		bool b_quit_changing_mode = false;
		Change_info ch_inf_filter{};
		Operation_code cod_screen_backwards{};

		while (2) {
			// Now we don't calculate offsets. We change data in object and rewrite the WHOLE object to file.
			switch (ch_inf_filter = (Change_info)_getch()) {
			case Ch_id: {
				system("cls");
				student_form.print();

				int i_new_id{};
				cod_screen_backwards = number_input_handler("\n\n\nInput student's new id (or quit [q], back [b]) :\n", i_new_id, 1);

				if (cod_screen_backwards == Quit) return Quit;
				else if (cod_screen_backwards == Back) { b_back_the_screen = true; break; }

				student_form.i_number = i_new_id;
				break;
			}

			case Ch_name:
			case Ch_surname: {
				while (3) {
					system("cls");
					student_form.print();

					if (ch_inf_filter == Ch_name) printf("\n\n\nInput student's new name (or quit [q], back [b]) :\n");
					else                          printf("\n\n\nInput student's new surname (or quit [q], back [b]) :\n");

					char ch_new_name[16];
					scanf_s("%15s", ch_new_name, 16);

					cod_screen_backwards = change_menu(ch_new_name, 1);
					if (cod_screen_backwards == Quit) return Quit;
					else if (cod_screen_backwards == Back) { b_back_the_screen = true; break; }

					if (buffer_clean()) {
						system("cls"); printf("\nToo long. Input not more then 15 symbols."); Sleep(1800); continue;
					}

					if (ch_inf_filter == Ch_name) strcpy_s(student_form.ch_name, ch_new_name);
					else                          strcpy_s(student_form.ch_surname, ch_new_name);

					break;
				}
				break;
			}

			case Ch_date: {
				while (3) {
					int i_new_day{},     i_new_month{},     i_new_year{};
					int i_current_day{}, i_current_month{}, i_current_year{};

					system("cls");
					student_form.print();
					while (4) {
						cod_screen_backwards = number_input_handler("\n\n\nInput student's new day of birth (1-31)  (or quit [q], back [b]) :\n", i_new_day, 1);

						if (!cod_screen_backwards && (i_new_day < 1 || i_new_day > 31)) {
							printf("\n\nNot valid range. Input day from 1 to 31.");
							continue;
						}

						break;
					}

					system("cls");
					student_form.print();
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
					student_form.print();
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

					student_form.St_birth_date.i_day = i_new_day;
					student_form.St_birth_date.i_month = i_new_month;
					student_form.St_birth_date.i_year = i_new_year;

				}
				if (cod_screen_backwards == Quit) return Quit;
				else if (cod_screen_backwards == Back) b_back_the_screen = true;

				break;
			}

			case Ch_marks: {
				while (3) {
					cod_screen_backwards = No_code;
					system("cls");
					student_form.print();

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
					int* p_i_marks_buffer{}; // Not a buffer, but pointer to the marks array of chosen subject
					const char* ch_subject_name{};

					while (4) {
						char ch_mark_filter = _getch();
						switch (ch_mark_filter) {
						case '1':
							p_i_marks_buffer = student_form.p_i_mark_physics;
							ch_subject_name = "Physics";
							break;
						case '2':
							p_i_marks_buffer = student_form.p_i_mark_math;
							ch_subject_name = "Mathematics";
							break;
						case '3':
							p_i_marks_buffer = student_form.p_i_mark_bel;
							ch_subject_name = "Belarussian language";
							break;
						case '4':
							p_i_marks_buffer = student_form.p_i_mark_chem;
							ch_subject_name = "Chemistry";
							break;
						case '5':
							p_i_marks_buffer = student_form.p_i_mark_inf;
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

						cod_screen_backwards = input_subject_marks(p_i_marks_buffer, student_form.i_current_marks_count, ch_subject_name);
						break;
					}
					if (b_back_the_screen) break;

					if (cod_screen_backwards == Good) {
						student_form.set_get_median();
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
				return Not_val_num;

			case 'e': case 'E':
				if (!b_creation_mode) continue;
				return Good;

			case 'b': case 'B':
				if (b_creation_mode) continue;
				return Back;

			case 'q': case 'Q':
				b_quit_changing_mode = true;
				break;

			default: continue;
			}
			break;
		}
		if (b_back_the_screen) continue;

		if (ch_inf_filter != Ch_del/* && ch_inf_filter != 'e' && ch_inf_filter != 'E' && !b_creation_mode*/) {
			if (b_quit_changing_mode) {
				printf("\n\n\nSave when quitting? [Y/N] (or stay [S]) :\n");
				switch (_getch()) {
				case 'Y':
				case 'y': 
					if (b_creation_mode) return Quit_s;
					break;

				case 'N':
				case 'n': return Quit;

				default: continue;
				}
			}

			if (!b_creation_mode) {
				fseek(Students_database, l_student_position, SEEK_SET); // Go to student's to rewrite position
				student_form.save_to_file(Students_database);           // Rewrite whole student form

				system("cls");
				printf("\nChanging...");
				Sleep(800);
				system("cls");
				printf("\nDone.");
				Sleep(800);
				system("cls");
			}

			if (b_quit_changing_mode) return Quit;
		}
	}
}



static Operation_code create_database_manual(FILE* Students_database, C_Database_Info& db_info) {
	int i_amount_of_groups{};
	ENTER_DATABASE_INFO(i_amount_of_groups, 1, 6, "\nInput amount of groups from 1 to 6 (quit [q], back [b]) :\n", 0);

	// Init dynamic arrays
	db_info.init_arrays(i_amount_of_groups);

	system("cls");

	// Ask for marks amount per subject (since arrays are dynamic now)
	ENTER_DATABASE_INFO(db_info.i_marks_per_subject, 1, 32, "\nInput amount of marks per subject (1-32) (quit [q], back [b]) :\n", 0);
	system("cls");

	for (int i = 0; i < i_amount_of_groups; ++i) {                                   // Input Students Amount per Group
		ENTER_DATABASE_INFO(db_info.p_i_students_in_group_amount[i], 1, 10, "\nInput amount of students in group number %d from 1 to 10 (quit [q], back [b]) :\n", i + 1);
		system("cls");

		db_info.p_i_group_numbers[i] = i + 1;
	}

	// Write header
	fseek(Students_database, 0, SEEK_SET);
	db_info.save_to_file(Students_database);

	C_Student temp_student;
	temp_student.init_mark_arrays(db_info.i_marks_per_subject);                      // Allocate dynamic memory for student

	for (int g = 0; g < i_amount_of_groups; ++g) {
		for (int s = 0; s < db_info.p_i_students_in_group_amount[g]; ++s) {

			// Initialization
			temp_student.i_number = (db_info.p_i_group_numbers[g]) * 1000 + (s + 1); // When formatted will be 001001, 001002...
			strcpy_s(temp_student.ch_name, "-");
			strcpy_s(temp_student.ch_surname, "-");
			temp_student.St_birth_date = { 1, 1, 2000 };

			printf("\nInitializing Student %06d...\n", temp_student.i_number);
			Sleep(800);

			Operation_code op = change_student(temp_student, true);

			if (op == Quit) {
				db_info.p_i_students_in_group_amount[g] = s;                         // If quit, set students amount to current index (what we already have)

				for (int k = g + 1; k < i_amount_of_groups; ++k) {                   // All remaining groups are empty
					db_info.p_i_students_in_group_amount[k] = 0;
				}

				fseek(Students_database, 0, SEEK_SET);                               // Rewrite header with new amounts
				db_info.save_to_file(Students_database);

				return Quit;
			}

			temp_student.save_to_file(Students_database);

			system("cls");
			printf("\nStudent saved.\n");
			Sleep(300);

			if (op == Quit_s) {                                    // The same as above, but after saving current student
				db_info.p_i_students_in_group_amount[g] = s + 1;

				for (int k = g + 1; k < i_amount_of_groups; ++k) {
					db_info.p_i_students_in_group_amount[k] = 0;
				}

				fseek(Students_database, 0, SEEK_SET);
				db_info.save_to_file(Students_database);

				return Quit;
			}
		}
	}

	printf("\nDatabase generation complete.\n");
	Sleep(1000);
}



static Operation_code file_manager(FILE** p_p_Database, char** ch_f_name_dest, char* ch_dir_path) {
	//const char* ch_dir_path = DIR_PATH;
	//_mkdir("C:\\Databases");
	//_mkdir("C:\\Users\\ASUS\\Documents\\Databases");


	//char* ch_to_mkdir = (char*)calloc(MAX_PATH, sizeof(char));
	//strcpy_s(ch_to_mkdir, MAX_PATH, ch_dir_path);
	//ch_to_mkdir[my_strlen(ch_to_mkdir) - 1] = '\0';
	_mkdir(ch_dir_path);
	//free(ch_to_mkdir);

	bool b_back_the_screen = false;
	while (1) {
		system("cls");
		printf("\nCurrent directory: %s\n\n\n", ch_dir_path);

										                                                            // Simpler to do in ANCI version of WinAPI, because all is in char
		WIN32_FIND_DATAA St_find_data;                                                              // Structure to save properties of the file, that found by Find[First/Next]File[A/W/ or macro]
		char ch_path_to_file[MAX_PATH];                                                             // Buffer to store path of file to find. Max length of file name is MAX_PATH (260 here)
		sprintf_s(ch_path_to_file, MAX_PATH, "%s*.dat", ch_dir_path);                               // Printing to buffer full path to use in FindFirstFileA

		HANDLE H_found_file = FindFirstFileA(ch_path_to_file, &St_find_data);                       // Start searching for files with some internal "HANDLING". HANDLE is like pointer to some internal structure of WinAPI, to continue in the same finding process

		int i_file_count = 0;
		struct {
			char ch_names[MAX_FILES][MAX_FILE_NAME];
			file_sz fsz_sizes[MAX_FILES];
		} St_f_store{};                                                                             // Anonymous structure to store found file names and sizes

		if (H_found_file != INVALID_HANDLE_VALUE) {
			do {
				strcpy_s(St_f_store.ch_names[i_file_count], MAX_FILE_NAME, St_find_data.cFileName); // Coping found file name from structure to our buffer
				St_f_store.fsz_sizes[i_file_count] = (file_sz)(St_find_data.nFileSizeHigh * 4294967296 + St_find_data.nFileSizeLow);
				                                                                                    // Moving size from 32bit size parts to full 64bit size
				printf_file_info(i_file_count + 1, St_f_store.ch_names[i_file_count], St_f_store.fsz_sizes[i_file_count]);
				++i_file_count;                                                                     // While file is found or max files reached
			} while (FindNextFileA(H_found_file, &St_find_data) != 0 && i_file_count <= MAX_FILES - 1);
			FindClose(H_found_file);                                                                // Closing HANDLE finding process
			ch_path_to_file[0] = '\0';                                                              // Emptying buffer for future usage
		}
		else {
			printf("\nNo byte files found in the directory.\n\n");
		}

		printf(
			"\n\n----------------------------\n"
			"[n] - new file\n"
			"[d] - delete file\n"
			"[s] - select file by number\n\n"
			"[b] - back\n"
			"[q] - quit\n"
		);

		Operation_code op_code{};
		enum { F_sel, F_del } F_cmd{};
		bool b_no_database = false;
		while (2) {
			switch (_getch()) {
			case 'n':
			case 'N': {
				system("cls");
				printf("\nCurrent directory: %s\n\n\n", ch_dir_path);
				for (int i = 0; i < i_file_count; ++i) printf_file_info(i + 1, St_f_store.ch_names[i], St_f_store.fsz_sizes[i]);
				printf("\n\n----------------------------\n");

				if (i_file_count == MAX_FILES) {
					system("cls");
					printf("\nYou have reached maximum amount of %d files. Delete some files first.\n", MAX_FILES);
					Sleep(2000);
					break;
				}

				char ch_new_file_name[MAX_FILE_NAME];
				while (3) {
					printf("\nInput new .dat file name without extension (or quit [q], back [b]) :\n");

					fgets(ch_new_file_name, MAX_FILE_NAME, stdin);
					if (clean_fgets(ch_new_file_name)) {
						printf("\nOut of name range. Input name less or equals 64 chars.");
						continue;
					}

					op_code = change_menu(ch_new_file_name, 1);
					if (op_code == Quit) return Quit;
					else if (op_code == Back) { b_back_the_screen = true; break; }

					bool b_inval_file_name = false;
					for (int i = 0; i < ch_new_file_name[i] != '\0'; ++i) {
						if (my_strchr("\\/:*?\"<>|\'", ch_new_file_name[i])) {
							b_inval_file_name = true;
							printf("\nCannot name file with this chars \' \\ / : * ? \" < > | \'");
							break;
						}

						if (ch_new_file_name[i] == '.' &&
							ch_new_file_name[i + 1] == 'd' &&
							ch_new_file_name[i + 2] == 'a' &&
							ch_new_file_name[i + 3] == 't'
							) {
							ch_new_file_name[i] = '\0';                   // Cutting extension if user added it
							break;
						}
					}
					if (b_inval_file_name == true) continue;

					strcat_s(ch_new_file_name, MAX_FILE_NAME, ".dat");

					bool b_file_exists = false;
					for (int i = 0; i < i_file_count; ++i) {
						if (my_strcmp(St_f_store.ch_names[i], ch_new_file_name)) {
							printf("\nFile with this name already exists. Try another name.");
							b_file_exists = true;
							break;
						}
					}
					if (b_file_exists == true) continue;

					

					break;
				}
				if (b_back_the_screen == true) { b_back_the_screen = false; break; }

				sprintf_s(ch_path_to_file, MAX_PATH, "%s%s", ch_dir_path, ch_new_file_name);

				if (fopen_s(p_p_Database, ch_path_to_file, "w+b")) { // Pointer on pointer is an address of the pointer that had been pointed at (but here it's just a double pointer)
					b_no_database = true;
					break;
				}

				system("cls");
				printf("\nFile created successfully.");
				Sleep(1200);
				system("cls");
				printf("\nOpen created file? [Y/N]");

				if (!YN()) {
					fclose(*p_p_Database);
					break;
				}

				//sprintf_s(ch_new_file_name, MAX_FILE_NAME, ".dat");
				strcpy_s(*ch_f_name_dest, MAX_FILE_NAME, ch_new_file_name);                // On stack variable ch_new_file_name, so we need to copy
				return Good;
			}
			
			case 'd':
			case 'D': 
				F_cmd = F_del;
			case 's':
			case 'S': {
				F_cmd = F_cmd == F_del ? F_del : F_sel;

				if (i_file_count == 0) {
					system("cls");
					printf("\nNo files found. Create some files first.\n");
					Sleep(2000);
					break;
				}

				const char* ch_msg = F_cmd == F_del ? "delete" : "select";

				int i_select = 0;
				while (3) {
					system("cls");
					printf("\nCurrent directory: %s\n\n\n", ch_dir_path);
					for (int i = 0; i < i_file_count; ++i) printf_file_info(i + 1, St_f_store.ch_names[i], St_f_store.fsz_sizes[i]);
					printf("\n\n----------------------------\n");

					op_code = number_input_handler("\nInput number of file to %s (or quit [q], back [b]) :\n", i_select, 1, ch_msg);
					if      (op_code == Quit) return Quit;
					else if (op_code == Back) break;

					if (i_select < 1 || i_select > i_file_count) {
						system("cls");
						printf("\nNot valid file number. Try again.\n");
						Sleep(1500);
						system("cls");
						continue;
					}
					break;
				}
				if (op_code == Back) break;
				--i_select; // To match array index

				sprintf_s(ch_path_to_file, "%s%s", ch_dir_path, St_f_store.ch_names[i_select]);

				// Temp finding logic -----------------------------------------------
				char ch_temp_f[MAX_PATH];
				strcpy_s(ch_temp_f, MAX_PATH, ch_path_to_file);
				ch_temp_f[my_strlen(ch_temp_f) - 4] = '\0'; // Cutting .dat for message
				strcat_s(ch_temp_f, MAX_PATH, "_temp.tmp");

				WIN32_FIND_DATAA St_temp_find_data;
				HANDLE H_temp_found_file = FindFirstFileA(ch_temp_f, &St_temp_find_data);
				
				if (H_temp_found_file != INVALID_HANDLE_VALUE) {
					FindClose(H_temp_found_file);

					system("cls");
					printf("\nFound temporary for the file you want to access. What to do?\n\n");
					printf(
						"[1] - RECOVER (rewrite origin with temp)\n"
						"[2] - delete temporary\n"
						"[b] - cancel %s operation\n"
						"[q] - quit\n", ch_msg
					);

					while (4) {
						switch (_getch())
						{
						case '1': { // Open temp
							if (!DeleteFileA(ch_path_to_file)) {
								printf("\nError access original file.\n");
								Sleep(1500);
								b_back_the_screen = true;
								break;
							}

							if (!MoveFileA(ch_temp_f, ch_path_to_file)) {
								printf("\nError recovering file.\n");
								Sleep(1500);
								b_back_the_screen = true;
								break;
							}

							system("cls");
							printf("\nFile recovered successfully.\n");
							Sleep(1000);

							F_cmd = F_sel;
							break;
						}
						case '2':   // Delete temp
							DeleteFileA(ch_temp_f);
							break;

						case 'b':
						case 'B':   // Cancel operation
							b_back_the_screen = true;
							break;

						case 'q':
						case 'Q': return Quit;

						default: continue;
						}
						break;
					}
					if (b_back_the_screen) {
						b_back_the_screen = false;
						break;
					}
				}
				// -------------------------------------------------------------------

				system("cls");
				if (F_cmd == F_del) {
					if (!DeleteFileA(ch_path_to_file)) {
						printf("\nCannot delete file. It may be used by another application.\n");
						Sleep(2000);
						break;
					}
					system("cls");
					printf("\nFile deleted successfully.");
					Sleep(1500);
					break;
				}
				else {    // F_sel
					if (fopen_s(p_p_Database, ch_path_to_file, "r+b")) {
						b_no_database = true;
						break;
					}
					system("cls");
					printf("\nOpening the file...");
					Sleep(1000);
					strcpy_s(*ch_f_name_dest, MAX_FILE_NAME, St_f_store.ch_names[i_select]);
					return Good;
				}
			}

			case 'b':
			case 'B':
				b_back_the_screen = true;
				break;

			case 'q':
			case 'Q': return Quit;

			default: continue;
			}
			break;
		}
		if (b_back_the_screen) break;

		if (b_no_database) {
			system("cls");
			printf("\nNo database. Try again or restart application.\n");
			Sleep(1500);
			system("cls");
			continue;
		}
	}
	if (b_back_the_screen) {
		return Back;
	}
}



static Operation_code temp_session(FILE** p_p_Database, const char* ch_original_path, char* ch_temp_path) {
	fclose(*p_p_Database);
	*p_p_Database = NULL;

	strcpy_s(ch_temp_path, MAX_PATH, ch_original_path);
	size_t len = my_strlen(ch_temp_path);
	if (len > 4) ch_temp_path[len - 4] = '\0';
	strcat_s(ch_temp_path, MAX_PATH, "_temp.tmp");

	//sprintf_s(ch_temp_path_dest, MAX_PATH, "%s_temp.tmp", ch_original_path);

	if (!CopyFileA(ch_original_path, ch_temp_path, FALSE)) {
		system("cls");
		printf("\nError creating temporary file. Access denied or path invalid.\n");
		Sleep(2000);

		fopen_s(p_p_Database, ch_original_path, "r+b");
		return Quit;
	}

	xor_file_hidden_attr(ch_temp_path); // Setting hidden attribute to the file (to authentic look)

	if (fopen_s(p_p_Database, ch_temp_path, "r+b")) {
		system("cls");
		printf("\nError opening temporary file.\n");
		Sleep(2000);

		fopen_s(p_p_Database, ch_original_path, "r+b");
		return Quit;
	}

	return Good;
}



static int commit_temp_session(FILE** p_p_Database, const char* ch_original_path, const char* ch_temp_path, int i_only_save) {
	system("cls");

	printf("\nSave changes to the file? [Y/N]\n");
	if (!YN()) {
		if (!i_only_save) {
			DeleteFileA(ch_temp_path);
			fopen_s(p_p_Database, ch_original_path, "r+b");
		}
		return 1;
	}

	fclose(*p_p_Database);
	*p_p_Database = NULL;

	if (!DeleteFileA(ch_original_path)) {             // Delete original file
		system("cls");
		printf("\nError updating database. Original file is locked.\n"
			"Changes are saved in: %s\n", ch_temp_path);
		Sleep(2500);
		return 1;
	}

	if (!MoveFileA(ch_temp_path, ch_original_path)) { // Rename temp to original
		system("cls");
		printf("\nError renaming temporary file. Data saved in: %s\n", ch_temp_path);
		Sleep(2500);
		return 1;
	}

	xor_file_hidden_attr(ch_original_path);

	fopen_s(p_p_Database, ch_original_path, "r+b");   // Reopen original file
	return 0;
}



void lab_8() {
	while (1) {
		system("cls");
		print_logo();
			printf(
				"\n\nCurrent directory: %s\n\n"
				"[m] - DATABASE MANAGER\n"
				"[d] - change directory\n\n"
				"[q] - quit\n", dir_path()
			);

		FILE* Students_database = NULL;
		//char ch_selected_file_name[MAX_FILE_NAME]{};
		char* ch_selected_file_name = (char*)calloc(MAX_FILE_NAME, sizeof(char));

		if (ch_selected_file_name == NULL) {
			system("cls");
			printf("\nAn internal error has occurred. Try again or restart the application\n");
			Sleep(1500);
			continue;
		}

		char* ch_dir_path = dir_path();
		bool b_back_the_screen = false;
		Operation_code op_code{};
		while (2) {
			switch (_getch()) {
			case 'm':
			case 'M': {
				op_code = file_manager(&Students_database, &ch_selected_file_name, ch_dir_path);
				if (op_code == Quit) {
					system("cls");
					free(ch_selected_file_name);
					return;
				}
				else if (op_code == Back) {
					b_back_the_screen = true;
					free(ch_selected_file_name);
					break;
				}
				else break;
			}

			case 'd':
			case 'D': { // May not work properly (actually not detecting non-existing directories)
				system("cls");
				print_logo();
					printf("\n\nInput path to the databases new directory (or quit [q], back [b]) :\n");

				char ch_path_buff[MAX_PATH];
				while (3) {
					fgets(ch_path_buff, MAX_PATH, stdin);
					if (clean_fgets(ch_path_buff)) {
						printf("\nOut of name range. Input name less or equals 64 chars.");
						continue;
					}

					op_code = change_menu(ch_path_buff, 1);
					if (op_code == Quit) return;
					else if (op_code == Back) { b_back_the_screen = true; break; }

					if (my_strlen(ch_path_buff) == 0) {
						printf("\nInvalid path. Must include at least one symbol.");
						continue;
					}
					break;
				}
				if (b_back_the_screen == true) break;

				strcpy_s(ch_dir_path, MAX_PATH, ch_path_buff);

				system("cls");
				printf("\nDirectory changed.");
				b_back_the_screen = true;
				break;
			}

			case 'q':
			case 'Q':
				system("cls");
				return;
			default: continue;
			}
			break;
		}
		if (b_back_the_screen) continue;

		/*const char* ch_selected_file_name = ch_f_name_buffer;
		free(ch_f_name_buffer);*/
		char ch_path_to_temp_file[MAX_PATH]{};
		char ch_path_to_file[MAX_PATH]{};
		strcat_s(ch_path_to_file, MAX_PATH, ch_dir_path);
		strcat_s(ch_path_to_file, MAX_PATH, ch_selected_file_name); // It's just simpler then to add another parameter to file_manager

		fseek(Students_database, 0, SEEK_END);
		long l_size = ftell(Students_database);
		rewind(Students_database);
		bool b_file_is_empty = l_size == 0;

		bool b_in_temp = false;
		while (2) {
			system("cls");
			if (b_file_is_empty) {
				printf(
					"%s\n"
					"\nSelected database is empty. Choose generation method:\n"
					"[1] - recreate randomly\n"
					"[2] - recreate manually\n"
					"\n[b] - close file and back\n"
					"[q] - quit\n", ch_selected_file_name
				);

			}
			else {
				printf(
					"%s\n"
					"\nDatabase Operations:\n"
					"[1] - clear and recreate randomly\n"
					"[2] - clear and recreate manually\n"
					"[3] - show all students\n"
					"[4] - show students in group\n"
					"[5] - change student information\n"
					"\n[b] - close file and back\n", ch_selected_file_name
				);
				if (b_in_temp) printf("[s] - save\n");
				printf("[q] - quit\n");

			}

			Command cmd_general{};
			while (3) {
				cmd_general = No_command;
				switch (_getch()) {
				case '1':
					cmd_general = Regen_database_random;
					break;

				case '2':
					cmd_general = Regen_database_manual;
					break;

				case '3':
					cmd_general = cmd_general ? cmd_general : Sh_all;
				case '4':
					cmd_general = cmd_general ? cmd_general : Sh_group;
				case '5':
					cmd_general = cmd_general ? cmd_general : Change_student;
					if (b_file_is_empty) continue;
					break;

				case 'q':
				case 'Q':
					if (b_in_temp) commit_temp_session(&Students_database, ch_path_to_file, ch_path_to_temp_file);
					fclose(Students_database);
					system("cls");
					return;

				case 'b':
				case 'B':
					b_back_the_screen = true;
					break;

				case 's':
				case 'S':
				if (b_in_temp) {
					if (!commit_temp_session(&Students_database, ch_path_to_file, ch_path_to_temp_file, 1)) b_in_temp = false;
					break;
				}
				continue;

				default: continue;
				}
				system("cls");
				break;
			}
			if (b_back_the_screen) {
				if (b_in_temp) commit_temp_session(&Students_database, ch_path_to_file, ch_path_to_temp_file);
				fclose(Students_database);
				break;
			}
			if (cmd_general == No_command) continue;

			C_Student student_form;
			C_Database_Info database_info;

			bool b_no_database = false;
			do {
				/*
				if (!b_in_temp && (cmd_general == Regen_database_random || cmd_general == Regen_database_manual || cmd_general == Change_student)) {
					if (temp_session(&Students_database, ch_path_to_file, ch_path_to_temp_file) != Good) {
						b_no_database = true;
						break;
					}
					b_in_temp = true;
				}
				*/
				if (!b_in_temp) {
					if (freopen_s(&Students_database, ch_path_to_file, "r+b", Students_database)) {
						b_no_database = true;
						break;
					}
				}

				int i_amount_of_groups{};
				if (cmd_general == Regen_database_random || cmd_general == Regen_database_manual) {
					//if (freopen_s(&Students_database, ch_path_to_temp_file, "w+b", Students_database)) {
					//	b_no_database = true;
					//	break;
					//}
					if (!b_in_temp) {
						if (temp_session(&Students_database, ch_path_to_file, ch_path_to_temp_file) != Good) {
							b_no_database = true;
							break;
						}
						b_in_temp = true;
					}

					if (_chsize_s(_fileno(Students_database), 0)) { // Simpler way to "reopen" the file. C functions cannot open files with HIDDEN attribute
						b_no_database = true;
						break;
					}
					rewind(Students_database);

					generate_seed();

					Operation_code op = No_code;
					do {
						if (cmd_general == Regen_database_random) {
							database_info.i_groups_amount = i_amount_of_groups = 2 + my_random(4, 0);
							database_info.init_arrays(i_amount_of_groups);
							database_info.i_marks_per_subject = 16; // Default random size

							for (int i = 0; i < i_amount_of_groups; ++i) {
								database_info.p_i_students_in_group_amount[i] = 2 + my_random(10, 0);
							}
						}
						else {          // Regen_database_manual
							op = create_database_manual(Students_database, database_info);
							if (op == Quit) {
								//commit_temp_session(&Students_database, ch_path_to_file, ch_path_to_temp_file);
								fclose(Students_database);
								system("cls");
								return;
							}
							else if (op == Back) {
								//commit_temp_session(&Students_database, ch_path_to_file, ch_path_to_temp_file);
								system("cls");
								//fclose(Students_database);
								//return;
								break;
							}
							//fclose(Students_database);
							//system("cls");
							break;
						}

						for (int g = 0; g < i_amount_of_groups; ++g) {       // The iterator for filling group numbers
							database_info.p_i_group_numbers[g] = my_random(482, 0);
						}

						database_info.save_to_file(Students_database);

						student_form.init_mark_arrays(database_info.i_marks_per_subject);

						for (int g = 0; g < i_amount_of_groups; ++g) {       // Generate groups
							int i_group_number = database_info.p_i_group_numbers[g] * 1000 + my_random(432, 0);

							for (int i = 0; i < database_info.p_i_students_in_group_amount[g]; ++i) { // Generate students
								int i_strength = my_random(1000, 0);

								student_form.i_number = i_group_number + i;

								const char* ch_random_name{};

								ch_random_name = get_name(FirstN, my_random(119, 0));
								strcpy_s(student_form.ch_name, sizeof(student_form.ch_name), ch_random_name);

								ch_random_name = get_name(LastN, my_random(119, 0));
								strcpy_s(student_form.ch_surname, sizeof(student_form.ch_surname), ch_random_name);

								student_form.St_birth_date.i_day = 1 + my_random(30, 0);
								student_form.St_birth_date.i_month = 1 + my_random(11, 0);
								student_form.St_birth_date.i_year = 2006 + my_random(2, 0);

								student_form.set_random_marks(i_strength);

								student_form.save_to_file(Students_database);
							}
						}
					} while (0);

					b_file_is_empty = false;

					if (op != Back) {
						system("cls");
						printf("\nRecreating...");
						Sleep(1000);
						system("cls");
						printf("\nDone.");
						Sleep(800);
						system("cls");
					}

					break;
				}

				/*if (fopen_s(&Students_database, ch_path_to_file, "r+b")) {
					b_no_database = true;
					break;
				}*/

				Command cmd_filter{};
				Command cmd_filter_mode{};
				if (cmd_general == Change_student) {
					database_info.load_from_file(Students_database);
					student_form.init_mark_arrays(database_info.i_marks_per_subject);

					int i_student_id_to_change{};
					while (4) {
						system("cls");
						if (show_students_filtered(Students_database) == Read_error) {
							system("cls");
							b_back_the_screen = true;
							break;
						}
						fseek(Students_database, database_info.get_size(), SEEK_SET);

						Operation_code cod_screen_backwards = number_input_handler("\nChoose student by id to change from listed (or quit [q], back [b]) :\n", i_student_id_to_change, 1);
						if (cod_screen_backwards == Quit) {
							commit_temp_session(&Students_database, ch_path_to_file, ch_path_to_temp_file);
							fclose(Students_database);
							system("cls");
							return;
						}
						else if (cod_screen_backwards == Back) {
							//fclose(Students_database);
							system("cls");
							b_back_the_screen = true;
							break;
						}

						if (!b_in_temp) {
							if (temp_session(&Students_database, ch_path_to_file, ch_path_to_temp_file) != Good) {
								b_no_database = true;
								break;
							}
							b_in_temp = true;
						}
						fseek(Students_database, database_info.get_size(), SEEK_SET);

						bool b_student_exists = false;
						long l_student_position{};
						int i_group_index{};
						for (int g = 0; g < database_info.i_groups_amount; ++g) {                        // Iterator to catch student and to change students amount in database info
							int i_students_count = database_info.p_i_students_in_group_amount[g];

							for (int s = 0; s < i_students_count; ++s) {
								long l_current_position = ftell(Students_database);                      // Saving student we reading position

								student_form.load_from_file(Students_database);                          // Reading

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

						while (5) {
							Operation_code change_return = change_student(student_form, false, Students_database, l_student_position);

							if (change_return == Quit) {
								fclose(Students_database);
								system("cls");
								return;
							}
							else if (change_return == Not_val_num) { // Delete
								system("cls");

								student_form.print();

								printf("\n\n\nDelete student? [Y/N]");

								if (!YN()) continue;

								del_student(Students_database, l_student_position, database_info);

								--database_info.p_i_students_in_group_amount[i_group_index];

								fseek(Students_database, 0, SEEK_SET);
								database_info.save_to_file(Students_database);

								system("cls");
								printf("\nDeleting...");
								Sleep(1000);
								system("cls");
								printf("\nDone.");
								Sleep(800);
								system("cls");
							}
							break;
						}
					}
					if (b_back_the_screen) {
						b_back_the_screen = false;
						break;
					}
				}

				int i_group_number = -1;
				if (cmd_general == Sh_group) {
					system("cls");
					database_info.load_from_file(Students_database);

					while (3) {
						printf("\nAvailable groups:\n");
						for (int i = 0; i < database_info.i_groups_amount; ++i) {
							printf("%d ", database_info.p_i_group_numbers[i]);
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
							if (i_group_number != database_info.p_i_group_numbers[i]) {
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

				// "show" while
				while (4) {
					if (cmd_general == Sh_all) puts("\nAll students menu\n");
					else if (cmd_general == Sh_group) printf("\nStudents in group %d menu\n\n", i_group_number);

					puts(
						"[1] - show all students\n"
						"[2] - show best students by marks (physics 7 and 8, math > 9)\n"
						"[3] - show best students by median\n"
						"\n[q] - quit\n"
						"[b] - back to start\n"
					);

					while (5) {
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

					if (cmd_filter == Sh_all) { 
						if (show_students_filtered(Students_database, i_group_number) == Read_error) {
							system("cls");
							b_back_the_screen = true;
							break;
						}
					}

					else if (cmd_filter == Sh_best) {
						if (cmd_filter_mode == Sh_best_marks) {
							if (show_students_filtered(Students_database, i_group_number, cmd_filter, cmd_filter_mode) == Read_error) {
								system("cls");
								b_back_the_screen = true;
								break;
							}
						}

						else if (cmd_filter_mode == Sh_best_median) {
							double d_median{};

							bool b_back_to_menu = false;
							while (5) {
								Operation_code cod_screen_backwards = number_input_handler("\nInput median mark in range from 1 to 10 to filter students:\n", d_median, 1);
								if (cod_screen_backwards == Quit) {
									fclose(Students_database);
									system("cls");
									return;
								}
								else if (cod_screen_backwards == Back) {
									system("cls");
									//fclose(Students_database);
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
							if (show_students_filtered(Students_database, i_group_number, cmd_filter, cmd_filter_mode, d_median) == Read_error) {
								system("cls");
								b_back_the_screen = true;
								break;
							}
						}
					}
				}
				if (b_back_the_screen) {
					b_back_the_screen = false;
					break;
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
}



#undef ENTER_DARABASE_INFO
#undef READ_ERROR