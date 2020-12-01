#include <stdio.h>
#include <stdlib.h>
#include "task6.h"

#define ERROR_CODE -1

char *output_name;
char *input_name;

int main(int argc, char **argv) {


    if (argc < 6) {

        fprintf(stderr, "Not enough parameters on enter!");
        return ERROR_CODE;
    }
    if (argc > 6) {

        fprintf(stderr, "Too many parameters on enter!");
        return ERROR_CODE;
    }
    array_size_t line_count;
    sorting_func_t sort = NULL;
    comparator_func_t comparator = NULL;
    if (args_solve(argv, &line_count, &sort, &comparator)) return ERROR_CODE;
    strings_array_t line_array = malloc(line_count * sizeof(char *));
    if (line_array == NULL) {

        abort_program("Couldn't allocate memory in main!", line_array, line_count);
    }
    for (int i = 0; i < line_count; i++) {

        line_array[i] = malloc(MAX_INPUT_STRING_SIZE);
        if (line_array[i] == NULL) {

            abort_program("Couldn't allocate memory in main!", line_array, line_count);
        }
    }
    if (read_from_file(line_array, line_count)) return ERROR_CODE;
    sort(line_array, line_count, comparator);
    print_to_file(line_array, line_count);
    free_all(line_array, line_count);
    return 0;
}
