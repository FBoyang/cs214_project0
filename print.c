#include <stdio.h>
#include <math.h>
#include <string.h>
#include "sorter.h"
int escaped(char *str);
void print_table()
{
	int i, j;
	char *str;
	double num;
	/* print the sorted csv file */
	for (i = 0; i < feature_num; i++) {
		str = feature_name[i];
		if (escaped(str))
			fprintf(stdout, "\"%s\"", str);
		else
			fputs(str, stdout);
		if (i == feature_num - 1)
			break;
		fputc(',', stdout);
	}
	fputs("\r\n", stdout);
	for (i = 0; i < row_counter; i++) {
		for (j = 0; j < feature_num; j++) {
			str = record_table[j][i].string;
			num = record_table[j][i].digit;
			if (str == NULL) {
				if (fabs(num + 1) >= 0.0001) {
					if (num - floor(num) < 0.0001)
						fprintf(stdout, "%.f", num);
					else if (10 * num - floor(10 * num) < 0.0001)
						fprintf(stdout, "%.1f", num);
					else if (100 * num - floor(100 * num) < 0.0001)
						fprintf(stdout, "%.2f", num);
					else
						fprintf(stdout, "%.3f", num);
				}
			} else {
				if (escaped(str))
					fprintf(stdout, "\"%s\"", str);
				else
					fputs(str, stdout);
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
