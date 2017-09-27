#include <stdio.h>
#include <math.h>
#include <string.h>
#include "sorter.h"
int escaped(char *str);
void print_table()
{
	int i, j;
	/* print the sorted csv file */
	for (i = 0; i < feature_num; i++) {
		if (escaped(feature_name[i]))
			fprintf(stdout, "\"%s\"", feature_name[i]);
		else
			fputs(feature_name[i], stdout);
		if (i == feature_num - 1)
			break;
		fputc(',', stdout);
	}
	fputs("\r\n", stdout);
	for (i = 0; i < row_counter; i++) {
		for (j = 0; j < feature_num; j++) {
			if (record_table[i][j].string == NULL) {
				if (fabs(record_table[i][j].digit + 1) >= 0.0001)
					fprintf(stdout, "%.f", record_table[i][j].digit);
			} else {
				if (escaped(record_table[i][j].string))
					fprintf(stdout, "\"%s\"", record_table[i][j].string);
				else
					fputs(record_table[i][j].string, stdout);
			}
			if (j == feature_num - 1)
				break;
			fputc(',', stdout);
		}
		fputs("\r\n", stdout);
	}
}

int escaped(char *str)
{
	return index(str, ',') || index(str, '"') || index(str, '\r') || index(str, '\n');
}
