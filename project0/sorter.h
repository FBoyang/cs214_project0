#ifndef _SORTER_H
#define _SORTER_H
struct csv {
	int number_of_headers;
	int number_of_records;
	char **header_strings;
	struct field **values;
};
struct field {
	double number;
	char *string;
};

struct csv *read_table();
int print_table(const struct csv *table);
int sort_by_field(struct csv *table, const char *field_name);
#endif /* ifndef _SORTER_H */
