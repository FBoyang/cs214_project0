#ifndef _SORTER_H
#define _SORTER_H

struct record{
	double digit;
	char *string;
};


char **feature_name;
int number_of_features;
struct record **record_table;
int number_of_rows;
void print_table();
void sort_by_field(const char *field_name);
#endif /* ifndef _SORTER_H */
