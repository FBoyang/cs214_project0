#ifndef _SORTER_H
#define _SORTER_H
struct csv {
	int number_of_headers;
	char **header_strings;
	struct record_node *records;
};
struct record {
	/*
	 * the CSV file format specifies that each record
	 * has the same number of entries, but I feel that
	 * we should be cautious
	 */
	int length;
	enum type_t *types;
	union field *values;
};
struct record_node {
	struct record *data;
	struct record_node *next;
};
enum type_t {
	EMPTY;
	NUMBER;
	STRING;
};
union field {
	double *number;
	char *string;
};

struct csv *read_table();
void print_table(const struct csv *table);
void sort_by_field(struct csv *table, const char *field_name);
#endif /* ifndef _SORTER_H */
