#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "sorter.h"
int compare(struct record a, struct record b);
int lexcmp(char *a, char *b);
int strbegin(char *str);
int strend(char *str);
int min(int a, int b);
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
		ad = strtod(a.string + strbegin(a.string), &endptr);
		if (endptr == a.string + strend(a.string))
			ab = true;
		bd = strtod(b.string + strbegin(b.string), &endptr);
		if (endptr == b.string + strend(b.string))
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
	int ab, bb;
	int ae, be;
	int alen, blen;
	int cmp;
	ab = strbegin(a);
	ae = strend(a);
	bb = strbegin(b);
	be = strend(b);
	alen = ae - ab + 1;
	blen = be - bb + 1;
	if (alen <= 0 && blen <= 0)
		return 0;
	else if (alen <= 0)
		return -1;
	else if (blen <= 0)
		return 1;
	else if ((cmp = strncasecmp(a + ab, b + bb, min(alen, blen))))
		return cmp;
	else if (alen < blen)
		return -1;
	else if (alen > blen)
		return 1;
	else
		return 0;
}

int strbegin(char *str)
{
	int i, len, begin;
	len = strlen(str);
	begin = len;
	i = 0;
	for (i = 0; i < len; i++) {
		if (str[i] > '\0' && !isspace(str[i])) {
			begin = i;
			break;
		}
	}
	return begin;
}

int strend(char *str)
{
	int i, end;
	end = -1;
	for (i = strlen(str) - 1; i >= 0; i--) {
		if (str[i] > '\0' && !isspace(str[i])) {
			end = i;
			break;
		}
	}
	return end;
}

int min(int a, int b)
{
	return a <= b ? a : b;
}
