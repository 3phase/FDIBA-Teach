#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int *arr;
int *st_pos_fn;
int FLAG_ARRAY_FILLED = 0;
int CONST_COUNT_OF_STUDENTS;

void get_meta_info_file() {
	int student_position;
	FILE *fp;
	
	fp = fopen("./user-task.txt", "w");
	
	for (student_position = 0; student_position < CONST_COUNT_OF_STUDENTS; student_position++)
		fprintf(fp, "%d   -->   %d\n", *(st_pos_fn + student_position), *(arr + student_position));
	
	fclose(fp);
	
}

char* get_resp_student_assignment(int task_num) {
	char *num = (char *) (malloc(sizeof(char *) * 1));
	char *file_name_without_extension;
	char *file_name;
	
	itoa(task_num, num, 10);
	
	file_name_without_extension = (malloc(strlen("./assignments/") + strlen(num) + 1));
	file_name_without_extension[0] = '\0';
	strcat(file_name_without_extension, "./assignments/");
	strcat(file_name_without_extension, num);
	
	file_name = (malloc(strlen(".txt") + strlen(file_name_without_extension) + 1));
	file_name[0] = '\0';
	strcat(file_name, file_name_without_extension);
	strcat(file_name, ".txt");
	
	return file_name;	
}

char* get_respective_file_ct(int task_num) {
	char *file_name = get_resp_student_assignment(task_num);
	
	FILE *fp;
	// TO CHANGE AS SOON AS POSSIBLE !!!!!!!!
	char *buff = (char *) (malloc(sizeof(char) * 255));
	
	fp = fopen(file_name, "r");
	fgets(buff, 255, fp);
	fclose(fp);
	
	return buff;
}

char* generate_file_name(char *fn) {
	char *file_name_without_extension;
	char *file_name;
	
	file_name_without_extension = (malloc(strlen("./tasks/") + strlen(fn) + 1));
	file_name_without_extension[0] = '\0';
	strcat(file_name_without_extension, "./tasks/");
	strcat(file_name_without_extension, fn);
	
	file_name = (malloc(strlen(".txt") + strlen(file_name_without_extension) + 1));
	file_name[0] = '\0';
	strcat(file_name, file_name_without_extension);
	strcat(file_name, ".txt");
	
	return file_name;
	
}

void write_assignment_to_files() {
	int i;
	char *file_name_without_extension;
	char *file_name;
	char *r_file_ct;
	char *fn = (char *) (malloc(sizeof(char *) * 9));
	
	for (i = 0; i < CONST_COUNT_OF_STUDENTS; i++) {
		itoa(*(st_pos_fn + i), fn, 10);
		
		file_name = generate_file_name(fn);
		
		r_file_ct = get_respective_file_ct(*(arr + i));
		
		FILE *fp;
		
		fp = fopen(file_name, "w");
		fprintf(fp, "You have 20 minutes to solve the task below and you are allowed to use all the resources on your computer.\nAfter you are ready, submit it to X:/PCLU/3a/submissions/ and name the file as follows: \n%d.c.\n!!!! DO NOT FORGET TO INCLUDE THE TASK IN YOUR FILE AS A COMMENT !!!!\n\n\nTask: %s\n\nGood luck!", *(st_pos_fn + i), r_file_ct);
		fflush(fp);
		
		fclose(fp);
	}
	
}

void init_task_array() {
	int i = 0;
	
	for (i; i < CONST_COUNT_OF_STUDENTS; i++)
		*(arr + i) = 0;
}

void init_student_array() {
	*(st_pos_fn + 0) = 201217019;
	*(st_pos_fn + 1) = 201217016;
	*(st_pos_fn + 2) = 201217031;
	*(st_pos_fn + 3) = 201217035;
	*(st_pos_fn + 4) = 201217046;
	*(st_pos_fn + 5) = 201217028;
	*(st_pos_fn + 6) = 201217015;
	*(st_pos_fn + 7) = 201217013;
	*(st_pos_fn + 8) = 201217017;
	*(st_pos_fn + 9) = 201217037;
	*(st_pos_fn + 10) = 201216041;
	*(st_pos_fn + 11) = 201216042;
}

int try_insert_val(int val, int pos) {
	int i;
	
	if (pos >= CONST_COUNT_OF_STUDENTS)
		return 0;
	
	for (i = 0; i < CONST_COUNT_OF_STUDENTS; i++)
		if (*(arr + i) == val)
			return 0;
	
	if (*(arr + pos) == 0) {
		*(arr + pos) = val;
		
		if (pos == CONST_COUNT_OF_STUDENTS - 1)
			FLAG_ARRAY_FILLED = 1;
		
		return 1;
	}
	
	return 0;
}

int genrn() {
	srand (time(NULL));
	
	// Got 16 tasks, starting from number 1
	return rand() % 16 + 1;
}

int main(int argc, char* argv[]) {
	int student_position;
	
	// Casting argv[1] which is the first argument of the runned program to integer
	CONST_COUNT_OF_STUDENTS = atoi(argv[1]);
	
	printf("Generating tests for %d students...", CONST_COUNT_OF_STUDENTS);

	arr = (int *) (malloc(sizeof(int) * CONST_COUNT_OF_STUDENTS));
	st_pos_fn = (int *) (malloc(sizeof(int) * CONST_COUNT_OF_STUDENTS));
	
	init_task_array();
	init_student_array();
		
	student_position = 0;
	while (FLAG_ARRAY_FILLED == 0) {
		while (try_insert_val(genrn(), student_position) == 0) {}
		student_position += 1;
		printf("Student pos: %d\n", student_position);
	}
	
	printf("\n\nResult:\n");
	
	for (student_position = 0; student_position < CONST_COUNT_OF_STUDENTS; student_position++)
		printf("Student %d gets task %d\n", *(st_pos_fn + student_position), *(arr + student_position));
	
	write_assignment_to_files();
	get_meta_info_file();
	
	return 0;
}