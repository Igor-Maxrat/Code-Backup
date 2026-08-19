#include<stdio.h>
#include<string.h>
void LetterInit(int number_list[], char letter_list[], char formula[], int *letter_number, int *row_size);
void TruthInit(char truth_table[], char letter_list[], int number_list[], int letter_number, int row_size);
void FormulaWrite(char truth_table[], char argv[], int index, int row_size);
void TableSolver(char truth_table[], int number_list, int letter_number, int row_size);
void Logic(char dest[], char src1[], char src2[], char ops[], int truth_length);
int main(int argc, char *argv[]){
int number_list[33] = {[0 ... 32] = 0}; char letter_list[27] = {0};
char truth_table[1000] = {[0 ... 998] = ' ', [999] = 0}; int letter_number = 0, row_size = 0;
if(argc != 2) return 0;
printf("%s", truth_table);
return 0;}
void LetterInit(int number_list[], char letter_list[], char formula[], int *letter_number, int *row_size){
int i, j, index = 0; char hold;
for(i = 0; formula[i] != 0; i++){
hold = formula[i]*((formula[i] >= 'A' && formula[i] <= 'Z') || (formula[i] >= 'a' && formula[i] <= 'z'));
hold -= 32*(hold > 90);
index = (hold - 'A')*(hold >= 'A');
*letter_number += (hold >= 'A' && letter_list[index] == 0);
letter_list[index] += hold*(letter_list[index] == 0);
}
*row_size = (1 << *letter_number) + 7 + i; //2 for letter and \n, 5 for refs at end of line, i is f_length
for(j = 0, index = 0; j < 26; j++){
letter_list[index] = letter_list[j]*(letter_list[j] != 0);
number_list[j + 1] = (arg_length + (*row_size * index))*(letter_list[j] != 0); // sets each to the truth offset
index += (letter_list[j] != 0);
}
number_list[0] = i + (*row_size * *letter_number); //1st refererence
number_list[32] = number_list[0] + *row_size;
return;}
void TruthInit(int number_list[], char truth_table[], char letter_list[], int letter_number, int row_size){
int i, j, truth = 1, truth_half = 1 << letter_number;
for(i = 0; i < letter_number; i++){
	truth_half >> 1;
	truth_table[i*row_size] = letterList[i];
	truth_table[((i + 1)*row_size) - 1] = '\n';
	for(j = 0; j < (1 << letter_number); j++){
		truth_table[number_list[i + 1] + j] = '0' + truth;
		truth = truth*((j + 1) % truth_half != 0) + (1 - truth)*((j + 1) % truth_half == 0);
	}
}
truth_table[letter_number*row_size] = 0;
return;}
void formulaWrite(char truth_table[], char formula[], int index, int row_size){
int i = 0, current_depth = 0, target_depth = 0, max_depth = 0, row_diff = row_size, connect_counter = 4;
for(i = 0; formula[i] != 0; i++){
current_depth += (formula[i] == '(');
current_depth -= (formula[i] == ')');
max_depth += (current_depth > max_depth);
}
for(target_depth = max_depth, max_depth = 6; target_depth > 0; target_depth--){
	for(current_depth = 0, i = 0; formula[i] != 0; i++){
		formula[i] += ('A' - 'a')*(formula[i] >= 'a' && formula[i] <= 'z');
		if(formula[i] == '(')current_depth++;
		if(current_depth >= target_depth){
			truth_table[index] = formula[i]; index++; row_diff--;
		}
		if(current_depth == target_depth && formula[i] == ')'){
			index += row_diff; truth_table[index - 1] = '\n'; row_diff = row_size; max_depth = 6;
			connect_counter = 4;
		}
		if(current_depth == target_depth  && formula[i] >= 'A' && formula[i] <= 'Z'){
			truth_table[index + row_diff - max_depth] = truth_table[index - 1];
		}
		if(current_depth == target_depth && formula[i] != ' ' && formula[i] != '(' && formula[i] != ')' && (formula[i] < 'A' || formula[i] > 'Z')){
			if(formula[i] != '!' && connect_counter > 3){
				truth_table[index + row_diff - 2] = truth_table[index - 1]; connect_counter--;
			}
			else {truth_table[index + row_diff - connect_counter] = truth_table[index - 1];}
			max_depth -=(max_depth > 5);
		}
		if(formula[i] == ')')current_depth--;
	}
}
memcpy(&truth_table[index], &truth_table[index - row_size], (size_t) row_size);
truth_table[index + row_size] = 0;
return;}
void tableSolver(char truth_table[], int number_list, int letter_number, int row_size){
int ref_offset = ((letter_number + 1) * row_size) - 6; //'A', 'B', refs, operator offset will be ref_off + 2;
int solve_offset = number_list[0], truth_dex1 = 0, truth_dex2 = 0, i = 0;
for(i = 0; truth_table[(i + 1)*row_size] != 0; i++){
	truth_dex1 = number_list[(truth_table[ref_offset] % 64) & 31]; //'A' yeilds position 1, whitespace 0
	truth_dex2 = number_list[truth_table[ref_offset + 1] % 64]; //'A' yeilds position 1, whitespace 32
	Logic(&truth_table[solve_offset], &truth_table[truth_dex1], &truth_table[truth_dex2], &truth_table[ref_offset], 1 << letter_number);
	number_list[0] += row_size*((truth_dex1 == number_list[0]) + (truth_dex2 == number_list[32]));
	number_list[32] = number_list[0] + row_size;
	solve_offset += row_size;
	ref_offset += row_size;
}
for(i = 0, truth_dex1 = solve_offset, truth_dex2 = solve_offset - row_size; i < (1 << letter_number); i++;){
	truth_table[truth_dex1 + i] = (~truth_table[truth_dex2 + i] & 1) | 48;
}
return;}
void Logic(char dest[], char src1[], char src2[], char ops[], int truth_length){
char place[4] = {0, 0, 0, 0};
int i;
for(i = 0; i < truth_length && ops[2] == "|"; i++){
place[0] = src1[i]; place[1] = (~src1[i] & 1) | 48;
place[2] = src2[i]; place[3] = (~src2[i] & 1) | 48;
dest[i] = place[0 + ops[0] - 32] | place[2 + ops[1] - 32];
}
for(i = 0; i < truth_length && ops[2] == "&"; i++){
place[0] = src1[i]; place[1] = (~src1[i] & 1) | 48;
place[2] = src2[i]; place[3] = (~src2[i] & 1) | 48;
dest[i] = place[0 + ops[0] - 32] & place[2 + ops[1] - 32];
}
for(i = 0; i < truth_length && ops[2] == ">"; i++){
place[0] = src1[i]; place[1] = (~src1[i] & 1) | 48;
place[2] = src2[i]; place[3] = (~src2[i] & 1) | 48;
dest[i] = (~place[0 + ops[0] - 32] & 1) | 48 | place[2 + ops[1] - 32]
}
return;}
