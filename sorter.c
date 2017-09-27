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
			/*if(i == 2)
			{
				printf("row num is %d\n", j);
			}
			*/
			
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

	int row_num = 5000;

	//counter( &row_num, &feature_num);
	FILE *file = stdin;
	int ini_size = 1024;	
	char *str = malloc(ini_size);
	char *comp = malloc(ini_size);
	fgets(str, ini_size, file);
	while(str[strlen(str)-1] != '\n')
	{
		ini_size = ini_size + 1024;
		str = realloc(str, ini_size);
		fgets(comp, ini_size, file);
		strcat(str, comp);
	}

	




	
	char *str_temp = malloc(ini_size);
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
				
<<<<<<< HEAD
	int row_counter = 0;
=======
	row_counter = 0;
>>>>>>> 94dfcd8077ce8371db13df33dfcc552ef3126494
	int column_counter = 0;

	char* tokens = strtok(str, "\r\n,");
	
	char* prev_tokens;

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
	while(fgets(str, ini_size, file))
	{
		
		//printf("%s\n", tokens);
		int str_len = strlen(str) - 2;//exclude the \n
		int pstr_len = 0;
		column_counter = 0;		
		tokens = strtok(str, ",\r\n");
		prev_tokens = str;

		double value;
			
			while(tokens)
			{
				//pstr_len = strlen(prev_tokens);
				if(prev_tokens[0] == ',')
				{
					pstr_len = -1;
				}

	
				char *ptr = NULL;
				value = strtod(tokens, &ptr);
				int p_diff = tokens - (prev_tokens + pstr_len);
				if(p_diff <= 1)
				{
		
<<<<<<< HEAD
=======
					if(strlen(tokens) > 15 || strcmp(ptr, ""))
					{
>>>>>>> 94dfcd8077ce8371db13df33dfcc552ef3126494
						//treat the data as string
					
						if(tokens[0] != '"')
						{
							prev_tokens = tokens;
							pstr_len = strlen(prev_tokens);
							record_table[column_counter][row_counter].string = malloc(150);
							strcpy(record_table[column_counter++][row_counter].string, tokens);
						}
						else
						{
							//embeded comma
							prev_tokens = tokens;
							char special_tokens[200];
							strcpy(special_tokens, tokens);
							strcat(special_tokens, ",");
							// make up the lost comma
							tokens = strtok(NULL, "\"");
							strcat(special_tokens, tokens);
							pstr_len = strlen(special_tokens) + 2; // one comma and one quotation mark miss
							//need to be optimized
							record_table[column_counter][row_counter].string = malloc(150);
							strcpy(record_table[column_counter++][row_counter].string, special_tokens+1);
						}
<<<<<<< HEAD
							tokens = strtok(NULL, ",\r\n");
=======
					}

					else
					{
						//treat the data as digit
						prev_tokens = tokens;
						pstr_len = strlen(prev_tokens);
					//	printf("%d\n", column_counter);
					//	printf("%d\n", row_counter);
					//	printf("%s\n", tokens);	
						record_table[column_counter][row_counter].string = NULL;
						record_table[column_counter++][row_counter].digit = value;				
					}
					tokens = strtok(NULL, ",\r\n");
>>>>>>> 94dfcd8077ce8371db13df33dfcc552ef3126494
				 
				}
				else
				{
					int i;
					for(i =1; i < p_diff; i++)
					{
						record_table[column_counter][row_counter].string = NULL;
<<<<<<< HEAD
=======
						record_table[column_counter++][row_counter].digit = -1;
>>>>>>> 94dfcd8077ce8371db13df33dfcc552ef3126494
					}
					
						
					prev_tokens = tokens;
					pstr_len = 0; //since prev_tokens and tokens point to the same possition
				}
				
					
				 
		
			
			}
			/*
 * 			check whether the last few cell are empty
 */
			int p_diff = str + str_len  - (strlen(prev_tokens) + prev_tokens);
			if(p_diff > 0)
			{
				int i;
				for (i = 0; i < p_diff; i++)
				{
					record_table[column_counter][row_counter].string = NULL;
<<<<<<< HEAD
=======
					record_table[column_counter++][row_counter].digit = -1;
>>>>>>> 94dfcd8077ce8371db13df33dfcc552ef3126494
				}
			}
		column_counter = 0;	
		row_counter++;
		if(row_counter >= row_num -2){
			row_num = row_num + 1000;
			matrix_enlarge(row_num, feature_num, record_table);
		}
		/*if((row_counter -1) % 100 == 0 && record_table[0][row_counter-1].string !=NULL)
		{
			printf("%s\n", record_table[0][row_counter-1].string);
			printf("%d\n", row_counter-1);
		}
		*/
					
	}
	
<<<<<<< HEAD
	printf("row number is %d\n", row_counter);
	printf("column number is %d\n", feature_num);

/*	free function
 */
=======

/*	free function
 */
	if (argc >= 3)
		sort_by_field(argv[2]);
	else
		fputs("no parameter provided for sorting, printing original table\n", stderr);
	print_table();
>>>>>>> 94dfcd8077ce8371db13df33dfcc552ef3126494
	matrix_free(row_counter, feature_num, record_table);
	int i;
	for(i = 0; i < feature_num; i++)
	{
<<<<<<< HEAD
		free(feature_name[feature_num]);
=======
		free(feature_name[i]);
>>>>>>> 94dfcd8077ce8371db13df33dfcc552ef3126494
	}
	free(feature_name);	
	return 0;
}
