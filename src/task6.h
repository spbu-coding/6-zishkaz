//
// Created by Z on 17.11.2020.
//
#include <stdlib.h>
#include <stdio.h>
#include "sortings.h"

#define SORTS_COUNT 5
#define COMPARATORS_COUNT 2

typedef void (*sorting_func_t)(strings_array_t, array_size_t, comparator_func_t);

int asc_comparator(const char *, const char *);

int des_comparator(const char *, const char *);

int args_solve(char **, array_size_t *, sorting_func_t *, comparator_func_t *);

void free_all(strings_array_t, array_size_t);

void abort_program(const char *, strings_array_t, array_size_t);

void swap(char **, char **);

void print_to_file(strings_array_t, array_size_t);

int read_from_file(strings_array_t, array_size_t);
