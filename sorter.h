#ifndef _SORTER_H
#define _SORTER_H

struct record{
	double digit;
	char *string;
};


char **feature_name;
struct record **record_table;
void print_table(const struct record**);
void sort_by_field(char **feature_name, const char *field_name);
#endif /* ifndef _SORTER_H */
