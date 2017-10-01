For raw data processing part:

The structure I use to store the data is a matrix, each element of such matrix is a struct node which contains a string variable.

For the tokenizing part, there are three conditions:
1. if the input string is a normal one, then I separate each word by comma
2. if the program detects that there is commas inside of a csv cell, then the program begain to detect the quotation mark and combine the new token and the previous one together,
but in such case I would loss the first comma inside of the string and has an extra quotation mark in front of the string. Therefore I add a comma manually between the previous 
token and the new token, then I copy the string from the second index
3. if there is empty cell inside of the csv, I use the formula: comma_num = add(current token pointer) - add(previos token pointer) - (previous token length) to calculate the 
total number of the comma number. If the empty cell happens to be in the first place, then previous token length is set to be -1 to deal with this case

For storing part, since getline malloc enough space for me, so I don't need to care about hte column size, and the only thing I need to take care is the row size. So I first creaet a matrix with 5000 row, and use the variable "row_counter" to keep track of the line numbers, if row_counter is about to reach the initial size, realloc 1000 line, such procedure repeat again and again until I have stored all the information. 
For each string space, I also malloc a length which is just enough to store such string. 

Therefore, the structure we designed is flexible to fit the general data.
