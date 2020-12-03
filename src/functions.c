#include <stdio.h>
#include <string.h>
#include "task6.h"

static char *sorts[SORTS_COUNT] = {"bubble", "insertion", "merge", "quick", "radix"};
static char *comparators[COMPARATORS_COUNT] = {"asc", "des"};
static comparator_func_t comparators_functions[COMPARATORS_COUNT] = {&asc_comparator, &des_comparator};
static sorting_func_t sorting_functions[SORTS_COUNT] = {&bubble, &insertion, &merge, &quick, &radix};

extern char *output_name;
extern char *input_name;

int asc_comparator(const char *temp1, const char *temp2) {

    return strcmp(temp1, temp2) > 0;
}

int des_comparator(const char *temp1, const char *temp2) {

    return strcmp(temp1, temp2) < 0;
}

void swap(char **temp1, char **temp2) {

    char *buf = *temp2;
    *temp2 = *temp1;
    *temp1 = buf;
}

int args_solve(char **argv, int *line_count, sorting_func_t *sorting_method, comparator_func_t *comparator) {

    char *temp = argv[1];
    *line_count = strtol(argv[1], &temp, 10);
    if (strlen(argv[1]) == strlen(temp)) {

        fprintf(stderr, "Line count expected to be a number, found %s", temp);
        return -1;
    }
    input_name = argv[2];
    if (strcmp(strchr(argv[3], '.'), ".txt") != 0) {

        fprintf(stderr, "Wrong output file type!");
        return -1;
    }
    output_name = argv[3];
    for (unsigned i = 0; i < SORTS_COUNT; i++) {

        if (strcmp(argv[4], sorts[i]) == 0) {

            *sorting_method = sorting_functions[i];
            break;
        }
    }
    if (*sorting_method == NULL) {

        fprintf(stderr, "%s %s", argv[4], "is not a valid sorting method!");
        return -1;
    }

    for (int i = 0; i < COMPARATORS_COUNT; i++) {

        if (strcmp(argv[5], comparators[i]) == 0) {

            *comparator = comparators_functions[i];
            break;
        }
    }
    if (*comparator == NULL) {

        fprintf(stderr, "Wrong comparator name!");
        return -1;
    }
    return 0;
}

void free_all(strings_array_t line_array, array_size_t lines_count) {

    for (unsigned i = 0; i < lines_count; i++) {

        free(line_array[i]);
    }
    free(line_array);
}

void abort_program(const char *error_line, strings_array_t line_array, array_size_t lines_count) {

    if (error_line != NULL) fprintf(stderr, "%s", error_line);
    free_all(line_array, lines_count);
}

void print_to_file(strings_array_t line_array, array_size_t lines_count) {

    FILE *output = fopen(output_name, "w");
    for (unsigned i = 0; i < lines_count; i++) {

        fputs(line_array[i], output);
    }
    fclose(output);
}

int read_from_file(strings_array_t line_array, array_size_t lines_count) {

    FILE *input = fopen(input_name, "r");
    if (input == NULL) {

        abort_program("Couldn't open the source file!", line_array, lines_count);
        return -1;
    }
    for (unsigned i = 0; i < lines_count; i++) {

        if(fgets(line_array[i], MAX_INPUT_STRING_SIZE, input) == NULL) {

            fprintf(stderr, "Error while reading line %d/%d\n", i,  lines_count);
            abort_program("Number of lines is more than actual one!", line_array, lines_count);
            return -1;
        }
        if(strchr(line_array[i], '\n') == NULL) strcat(line_array[i], "\n");
    }
    fclose(input);
    return 0;
}