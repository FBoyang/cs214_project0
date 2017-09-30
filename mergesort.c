#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "sorter.h"
int compare(struct record a, struct record b);
int lexcmp(char *a, char *b);
charcmp(int a, int b);
void sort_by_field(const char *field_name)
{
	int field_index;
	int *end;
	int *pa, *pb, *ptmp;
	int low, middle, high;
	int i, j;
	struct record *a, *b, *tmp;
	int ind;
	/* performs a bottom-up mergesort on the table */
	/* find the column number for comparisons */
	field_index = -1;
	for (i = 0; i < feature_num; i++) {
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
	end = malloc(row_counter * sizeof(*end));
	pa = malloc(row_counter * sizeof(*pa));
	pb = malloc(row_counter * sizeof(*pb));
	for (i = 0; i < row_counter; i++) {
		pa[i] = i;
		pb[i] = i;
	}
	j = 0;
	for (i = 1; i < row_counter; i++) {
		if (compare(record_table[field_index][i - 1], record_table[field_index][i]) > 0) {
			end[j] = i;
			j = i;
		}
	}
	end[j] = row_counter;
	/* begin actual mergesort */
	a = record_table[field_index];
	b = malloc(row_counter * sizeof(*b));
	memcpy(b, a, row_counter * sizeof(*a));
	ind = 0;
	while (end[0] != row_counter) {
		low = ind;
		middle = end[ind];
		high = end[middle];
		i = low;
		j = middle;
		while (i < middle && j < high) {
			if (compare(a[i], a[j]) <= 0) {
				b[ind] = a[i];
				pb[ind] = pa[i];
				ind++;
				i++;
			} else {
				b[ind] = a[j];
				pb[ind] = pa[j];
				ind++;
				j++;
			}
		}
		while (i < middle) {
			b[ind] = a[i];
			pb[ind] = pa[i];
			ind++;
			i++;
		}
		while (j < high) {
			b[ind] = a[j];
			pb[ind] = pa[j];
			ind++;
			j++;
		}
		end[low] = high;
		if (high == row_counter || end[high] == row_counter) {
			/* reset ind to 0, then swap a and b */
			for (; ind < row_counter; ind++)
				b[ind] = a[ind];
			ind = 0;
			tmp = a;
			ptmp = pa;
			a = b;
			pa = pb;
			b = tmp;
			pb = ptmp;
		}
	}
	if (record_table[field_index] != a) {
		record_table[field_index] = a;
	}
	tmp = malloc(row_counter * sizeof(*tmp));
	for (i = 0; i < feature_num; i++) {
		if (i == field_index)
			continue;
		for (j = 0; j < row_counter; j++)
			tmp[pa[j]] = record_table[i][j];
		for (j = 0; j < row_counter; j++)
			record_table[i][j] = tmp[j];
	}
	free(end);
	free(b);
	free(tmp);
	free(pa);
	free(pb);
}

int compare(struct record a, struct record b)
{
	double ad, bd;
	bool ab, bb;
	char *endptr;
	if (a.string == NULL && b.string == NULL) {
		return 0;
	} else if (a.string == NULL) {
		return -1;
	} else if (b.string == NULL) {
		return 1;
	} else {
		ab = false;
		bb = false;
		ad = strtod(a.string, &endptr);
		if (*endptr == '\0')
			ab = true;
		bd = strtod(b.string, &endptr);
		if (*endptr == '\0')
			bb = true;
		if (ab && bb) {
			if (fabs(ad - bd) < 0.0001)
				return 0;
			else if (ad < bd)
				return -1;
			else
				return 1;
		} else if (ab) {
			return -1;
		} else if (bb) {
			return 1;
		} else {
			return lexcmp(a.string, b.string);
		}
	}
}

int lexcmp(char *a, char *b)
{
	int i, j;
	int ae, be;
	int ac, bc;
	int cmp;
	i = strbegin(a);
	ae = strend(a);
	j = strbegin(b);
	be = strend(b);
	for (; i < ae && j < be; i++, j++) {
		if ((cmp = charcmp(a[i], b[j])))
			return cmp;
	}
	if (i < ae)
		return -1;
	else if (j < be)
		return 1;
	else
		return 0;
}

int charcmp(int a, int b)
{
	if (isalpha(a) && isalpha(b)) {
		if (toupper(a) == toupper(b)) {
			if (isupper(a) && isupper(b))
				return 0;
			else if (isupper(a))
				return -1;
			else if (isupper(b))
				return 1;
			else
				return 0;
		} else if (toupper(a) < toupper(b)) {
			return -1;
		} else {
			return 1;
		}
	} else if (isalpha(a)) {
		if (toupper(a) < b)
			return -1;
		else
			return 1;
	} else if (isalpha(b)) {
		if (a < toupper(b))
			return -1;
		else
			return 1;
	} else if (a == b) {
		return 0;
	} else if (a < b) {
		return -1;
	} else {
		return 1;
	}
}
