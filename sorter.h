#ifndef _SORTER_H
#define _SORTER_H

struct record{
	char *string;
};

void column_count(char *str, int *column);
void matrix_free(int row, int column, struct record **matrix);
void matrix_enlarge(int row, int column, struct record **matrix);
char **feature_name;
int feature_num;
struct record **record_table;
int row_counter;
void print_table();
void sort_by_field(const char *field_name);
#endif /* ifndef _SORTER_H */
