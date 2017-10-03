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

We perform mergesort by first recording the boundaries of the already sorted
regions, then merging them until they are combined into a single region.
Since the matrix is allocated, by a design decision, in column major order,
we must record the permutation of the input and replicate the rearrangement
in all other columns.

We compare strings by first grouping all characters into two categories:
non-whitespace ASCII characters, and all other characters.
We will treat these characters as unreadable and
we will therefore consider them "whitespace",
even though not all of those characters are actually whitespace.
We then strip all leading and trailing whitespace.
If we can convert the entire remaining string to a number,
then we will treat that field as a number.
Otherwise, we will treat it as a string.

When we compare two fields, if both are empty, then they are equal.
If one is empty, it comes before the other in our ordering.
If both are numbers, we compare their numerical values.
If one is numeric, it comes before the non-numeric value.
Otherwise, both fields are strings.

We compare strings in the following way:
first we remove all whitespace characters,
then we compare lexicographically character by character.
If the characters are the same in case insensitive comparison,
then we use the ASCII code as a tiebreaker.
