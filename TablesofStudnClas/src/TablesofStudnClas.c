/*
 ============================================================================
 Name        : TablesofStudnClas.c
 Author      : Engin Aybey
 Version     :
 Copyright   : All rights reserved.
 Description : Tables of Students and Classes
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	false, true
} bool;

typedef struct classes {
	char name[30];
	char semester[20];
	char grade[2];
	struct classes *next;
} tClasses;

typedef struct student {
	int id;
	char name[30];
	char surname[30];
	struct classes *classes_list;
	struct student *next;
} tStudent;

void pushStudent(tStudent **head, int id, char *name, char *surname) {
	tStudent *new = (tStudent *) malloc(sizeof(tStudent));
	new->id = id;
	strcpy(new->name, name);
	strcpy(new->surname, surname);
	new->classes_list = NULL;
	new->next = *head;
	*head = new;
	return;
}

void insertStudent(tStudent *prev_node, int id, char *name, char *surname) {
	if (prev_node == NULL) {
		printf("The previous node can\'t be NULL!");
	}
	tStudent *new = (tStudent *) malloc(sizeof(tStudent));
	new->id = id;
	strcpy(new->name, name);
	strcpy(new->surname, surname);
	new->classes_list = NULL;
	new->next = prev_node->next;
	prev_node->next = new;
	return;
}

void appendStudent(tStudent **head, int id, char *name, char *surname) {
	tStudent *new = (tStudent *) malloc(sizeof(tStudent));
	tStudent *last = *head;
	new->id = id;
	strcpy(new->name, name);
	strcpy(new->surname, surname);
	new->classes_list = NULL;
	new->next = NULL;
	if (*head == NULL) {
		*head = new;
		return;
	}
	while (last->next != NULL) {
		last = last->next;
	}
	last->next = new;
	return;
}
void appendClasses(tStudent **head, int id, char *name, char *semester,
		char *grade) {
	tClasses *new = (tClasses *) malloc(sizeof(tClasses));
	tStudent *last = *head;
	strcpy(new->name, name);
	strcpy(new->semester, semester);
	strcpy(new->grade, grade);
	new->next = NULL;
	while (last->id != id) {
		last = last->next;
	}
	if (last->classes_list != NULL) {
		while (last->classes_list->next != NULL)
			last->classes_list = last->classes_list->next;
		last->classes_list->next = new;
	} else {
		last->classes_list = new;
	}
	return;
}
void ListStudent(tStudent **head) {
	tStudent *temp = *head;
	if (temp != NULL) printf(" Student id	Name	Surname\n");
	if (temp != NULL) printf(" ----------	----	-------\n");
	while (temp != NULL) {
		printf(" 	%d	%s	%s\n", temp->id, temp->name,
				temp->surname);
		temp = temp->next;
	}
	return;
}

void ListStudentClasses(tStudent **head) {
	tStudent *temp = *head;
	while (temp != NULL) {
		printf(" Student id:%d Name:%s Surname:%s\n", temp->id, temp->name,
				temp->surname);
		tClasses *tempc = temp->classes_list;
		if (tempc != NULL) printf("		Class	Semester	Grade\n");
		if (tempc != NULL) printf("		-----	--------	-----\n");
		while (tempc != NULL) {
			printf(" 		%s	%s	%s\n", tempc->name,
					tempc->semester, tempc->grade);

			tempc = tempc->next;
		}
		temp = temp->next;
	}
	return;
}

void deleteStudent(tStudent **head, int id) {
	tStudent *temp = *head;
	tStudent *prev = (tStudent *) malloc(sizeof(tStudent));
	if (temp != NULL && temp->id == id) {
		*head = temp->next;
		free(temp);
		return;
	}
	while (temp != NULL && temp->id != id) {
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return;
	prev->next = temp->next;
	free(temp);
	return;
}

int main(void) {

	tStudent *studentH = NULL;
	appendStudent(&studentH, 1, "Mark", "Twain");
	appendStudent(&studentH, 2, "Alice", "Terese");
	appendStudent(&studentH, 3, "Mike", "Jones");
	pushStudent(&studentH, 4, "Jane", "Sea");
	insertStudent(studentH->next->next, 5, "Jane", "Sea");
	ListStudent(&studentH);
	puts("=================");
	deleteStudent(&studentH, 4);
	appendClasses(&studentH, 1, "Biology", "Winter 2019", "AA");
	appendClasses(&studentH, 1, "Math", "Spring 2018", "BA");
	ListStudent(&studentH);
	puts("=================");
	ListStudentClasses(&studentH);
	return EXIT_SUCCESS;
}
