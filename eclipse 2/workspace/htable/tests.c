/*
 * tests.c
 *
 *  Created on: Mar 31, 2016
 *      Author: rodrigopimenta
 */

#include <stdio.h>
#include <stdlib.h>
#include "htable.h"
#include "my_memory_checker_216.h"

/*****************************************************/
/* In this file you will provide tests to your       */
/* hash table.  Each test should be named test1()    */
/* test2(), etc. Each test must have a description   */
/* of what it is testing (this description is really */
/* important).                                       */
/*                                                   */
/* You can tell whether any test failed if you       */
/* execute on the command line "echo $?" and you get */
/* a value other than 0. "echo $?" prints the status */
/* of the last command.                              */
/*                                                   */
/* main just calls all test1(), test2(), etc.        */
/*****************************************************/

/* Description here: This test checks if the create_table and destroy_table
 functions work.  */
static int test1() {
	int table_size = 2;
	Table *table_ptr;

	create_table(&table_ptr, table_size, free);
	destroy_table(table_ptr);

	return SUCCESS;
}

/* This test checks the put function. */
static int test2() {
	int table_size = 6;
	Table *table_ptr;
	int a = 5;
	int b = 6;
	int c = 7;
	int d = 8;
	int e = 9;

	create_table(&table_ptr, table_size, free);
	clear_table(table_ptr);
	put(table_ptr, "Carlos", &a);
	put(table_ptr, "Carmen", &b);
	put(table_ptr, "Gabriel", &c);
	put(table_ptr, "Cida", &d);
	put(table_ptr, "Ligia", &e);

	if (is_empty(table_ptr) == FAILURE) {
		destroy_table(table_ptr);
		return SUCCESS;
	} else {
		destroy_table(table_ptr);
		return FAILURE;
	}

}

/* This test checks for the case when the NULL character is passed for
 table in the create_table function. */
static int test3() {
	int table_size = 2;

	if (create_table(NULL, table_size, free) == FAILURE) {
		return SUCCESS;
	} else {
		return FAILURE;
	}

	return FAILURE;

}

/* This test checks the get_value function. */
static int test4() {
	int table_size = 6;
	int a = 5;
	int b = 7;
	Table *table_ptr;
	void *value;
	void *value_two;

	create_table(&table_ptr, table_size, free);
	clear_table(table_ptr);
	put(table_ptr, "Carlos", &a);
	get_value(table_ptr, "Carlos", &value);
	put(table_ptr, "Gabriel", &b);
	get_value(table_ptr, "Gabriel", &value_two);
	if ((*(int *) value == 5) && (*(int *) value_two == 7)) {
		destroy_table(table_ptr);
		return SUCCESS;
	} else {
		destroy_table(table_ptr);
		return FAILURE;
	}

}

/* This test checks the remove_entry function.*/
static int test5() {
	int table_size = 7;
	Table *table_ptr;
	int a = 5;

	create_table(&table_ptr, table_size, free);
	clear_table(table_ptr);
	put(table_ptr, "Carlos", &a);
	remove_entry(table_ptr, "Carlos");
	if (is_empty(table_ptr) != FAILURE) {
		destroy_table(table_ptr);
		return SUCCESS;
	} else {
		destroy_table(table_ptr);
		return FAILURE;
	}
}

/* Test checks get_table_size function. */
static int test6() {
	int table_size = 5;
	Table *table_ptr;
	int a = 5;

	create_table(&table_ptr, table_size, free);
	clear_table(table_ptr);
	put(table_ptr, "Carlos", &a);
	if (get_table_size(table_ptr) == 5) {
		destroy_table(table_ptr);
		return SUCCESS;
	} else {
		destroy_table(table_ptr);
		return FAILURE;
	}

}

/* Test checks the case when table_size is 0 for the create_table function. */
static int test7() {
	int table_size = 0;
	Table *table_ptr;

	if (create_table(&table_ptr, table_size, free) != SUCCESS) {
		destroy_table(table_ptr);
		return SUCCESS;
	} else {
		destroy_table(table_ptr);
		return FAILURE;
	}
}

/* Test checks when NULL is passed into for table in destroy_table. */
static int test8() {
	int table_size = 5;
	Table *table_ptr = NULL;

	if (destroy_table(table_ptr) != SUCCESS) {
		return SUCCESS;
	} else {
		return FAILURE;
	}
}

/* Test checks when NULL is passed in for table for put. */
static int test9() {
	int table_size = 5;
	Table *table_ptr;
	int a = 5;

	if (put(table_ptr, "Carlos", &a) != SUCCESS) {
		return SUCCESS;
	} else {
		return FAILURE;
	}
}

/* Test checks when key is NULL for put.*/
static int test10() {
	int table_size = 5;
	Table *table_ptr;
	int a = 5;

	create_table(&table_ptr, table_size, free);
	clear_table(table_ptr);
	if (put(table_ptr, NULL, &a) != SUCCESS) {
		destroy_table(table_ptr);
		return SUCCESS;
	} else {
		destroy_table(table_ptr);
		return FAILURE;
	}

}

int main() {
	int result = SUCCESS;

	/***** Starting memory checking *****/
	start_memory_check();
	/***** Starting memory checking *****/

	if (test1() == FAILURE)
		result = FAILURE;
	if (test2() == FAILURE)
		result = FAILURE;
	if (test3() == FAILURE)
		result = FAILURE;
	if (test4() == FAILURE)
		result = FAILURE;
	if (test5() == FAILURE)
		result = FAILURE;
	if (test6() == FAILURE)
		result = FAILURE;
	if (test7() == FAILURE)
		result = FAILURE;
	if (test8() == FAILURE)
		result = FAILURE;
	if (test9() == FAILURE)
		result = FAILURE;
	if (test10() == FAILURE)
		result = FAILURE;

	/****** Gathering memory checking info *****/
	stop_memory_check();
	/****** Gathering memory checking info *****/

	if (result == FAILURE) {
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
