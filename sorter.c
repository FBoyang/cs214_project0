#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"sorter.h"

void column_count(char *str, int *column){
	//FILE *file = fopen(file_name, "r");
	*column = 0;
	//fgets(str, 1024, file);
	char* token = strtok(str, ",");
	while(token)
	{	
		if(token[0] != '"')
		{
			(*column)++;
			token = strtok(NULL, ",");
		}
		else
		{	

			token = strtok(NULL, "\"");
		}
			
	}
/*	while(fgets(str, 1024, file))
	{
		(*row)++;
	}
	(*row)++;
	//fclose(file);
*/
}


void matrix_free(int row, int column, struct record **matrix){
	int i;
	int j;
	for (i = 0; i < column; i++)
	{
		for (j = 0; j < row; j++)
		{
			free(matrix[i][j].string);
			//only need to free the string
			//because only string in the struct mallocate
		}
		free(matrix[i]);
	}
	free(matrix);
}
	
/* matrix_enlarge function dynamically allocate the matrix
 */
void matrix_enlarge(int row, int column, struct record **matrix){
	int i = 0;
	for (i = 0; i < column; i++)
	{
		matrix[i] = realloc((matrix)[i], row*sizeof(struct record));
	}
}

int main(int argc, char** argv){

//	char *name = "movie_metadata.csv";
//	FILE *file = fopen("movie_metadata.csv", "r");
	int feature_num;

	int row_num = 5000;

	//counter( &row_num, &feature_num);
	FILE *file = stdin;	
	char str[1024];
	fgets(str, 1024, file);
	char str_temp[1024];
	strcpy(str_temp, str);
	column_count(str_temp ,&feature_num);
	
	record_table = malloc(sizeof(struct record*)*feature_num);
	
	//int i;
	//for(i = 0; i< feature_num; i++)
	//{
	//	record_table[i] = malloc(sizeof(struct record)*row_num);
	//	}

	matrix_enlarge(row_num, feature_num, record_table);
	feature_name = malloc(sizeof(char*)*feature_num);
		
	int row_counter = 0;
	int column_counter = 0;

	char* tokens = strtok(str, "\r\n,");

	while(tokens)
	{	
		//record_table[column_counter] = malloc(sizeof(struct record)*(row_num+1));
		if(tokens[0] != '"')
		{	
			feature_name[column_counter] = malloc(sizeof(char)*(strlen(tokens) + 1));
			strcpy(feature_name[column_counter++], tokens);
			tokens = strtok(NULL, ",\r\n");
	 	}

		else
		{
			//embeded comma
			char special_tokens[200];
			strcpy(special_tokens, tokens);
			tokens = strtok(NULL, "\"");
			strcat(special_tokens, tokens);
			feature_name[column_counter] = malloc(sizeof(char)*(strlen(tokens) + 1));
			strcpy(feature_name[column_counter++], special_tokens+1);
			tokens = strtok(NULL, ",\r\n");
		}
		
			
	}
	/*
 * 	this part serves to read the record and store them into the record struct
 */
	while(fgets(str, 1024, file))
	{
		
		//printf("%s\n", tokens);
		column_counter = 0;		
		tokens = strtok(str, ",\r\n");
		double value;
		
			while(tokens)
			{		
				char *ptr = NULL;
				value = strtod(tokens, &ptr);
				if(strlen(tokens)>15 || strcmp(ptr, ""))
				{
					//treat the data as string

					if(tokens[0] != '"')
					{

						record_table[column_counter][row_counter].string = malloc(150);
						strcpy(record_table[column_counter++][row_counter].string, tokens);
					}
					else
					{
					//embeded comma
						char special_tokens[200];
						strcpy(special_tokens, tokens);
						tokens = strtok(NULL, "\"");
						strcat(special_tokens, tokens);
						//need to be optimized
						record_table[column_counter][row_counter].string = malloc(150);
						strcpy(record_table[column_counter++][row_counter].string, special_tokens+1);
					}
				}

				else
				{
					//treat the data as digit
					
					record_table[column_counter][row_counter].string = NULL;
					record_table[column_counter++][row_counter].digit = value;				
				}
			tokens = strtok(NULL, ",\r\n"); 
		
			
			}
		column_counter = 0;	
		row_counter++;
		if(row_counter >= row_num -2){
			row_num = row_num + 1000;
			matrix_enlarge(row_num, feature_num, record_table);
		}
					
	}



	return 0;
}
