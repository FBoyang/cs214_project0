#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorter.h"
int compare(struct record *a, struct record *b);
void sort_by_field(const char *field_name)
{
	int field_index;
	int *end;
	int low, middle, high;
	int i, j;
	struct record **a, **b, **tmp;
	int ind;
	/* performs a bottom-up mergesort on the table */
	/* find the column number for comparisons */
	field_index = -1;
	for (i = 0; i < number_of_features; i++) {
		if (strcmp(feature_name[i], field_name) == 0) {
			field_index = i;
			break;
		}
	}
	if (field_index == -1) {
		fprintf(stderr, "could not find column name %s\n", field_name);
		return;
	}
	/* find already sorted regions */
	end = malloc(number_of_rows * sizeof(int));
	j = 0;
	for (i = 0; i < number_of_rows; i++) {
		if (compare(record_table[i - 1] + field_index, record_table[i] + field_index) > 0) {
			end[j] = i;
			j = i;
		}
	}
	end[j] = number_of_rows;
	/* begin actual mergesort */
	a = record_table;
	b = malloc(number_of_rows * sizeof(struct record *));
	ind = 0;
	while (end[0] != number_of_rows) {
		low = ind;
		middle = end[ind];
		high = end[middle];
		i = low;
		j = middle;
		while (i < middle && j < high) {
			if (compare(a[i] + field_index, a[j] + field_index) <= 0)
				b[ind++] = a[i++];
			else
				b[ind++] = a[j++];
		}
		while (i < middle)
			b[ind++] = a[i++];
		while (j < high)
			b[ind++] = a[j++];
		end[low] = high;
		if (high == number_of_rows || end[high] == number_of_rows) {
			/* reset ind to 0, then swap a and b */
			for (; ind < number_of_rows; ind++)
				b[ind] = a[ind];
			ind = 0;
			tmp = a;
			a = b;
			b = tmp;
		}
	}
	if (record_table != a) {
		record_table = a;
	}
	free(end);
	free(b);
}

int compare(struct record *a, struct record *b) {
	if (a->string == NULL && b->string == NULL) {
		if (a->digit < b->digit)
			return -1;
		else if (a->digit > b->digit)
			return 1;
		else
			return 0;
	} else if (a->string == NULL) {
		if (b->string[0] == '\0')
			return 1;
		else
			return -1;
	} else if (b->string == NULL) {
		if (a->string[0] == '\0')
			return -1;
		else
			return 1;
	} else {
		return strcmp(a->string, b->string);
	}
}
