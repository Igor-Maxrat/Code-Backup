#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void FormulaVerify(char formula[]);
void LetterInit(int number_list[], char formula[],  char letter_list[], int *letter_number, int *row_size, int *row_number);
void TruthAllocate(char **truth_table, int *row_space, int *row_size, int *letter_number);
int TruthInit(int number_list[], char truth_table[], char letter_list[], int letter_number, int row_size);
void FormulaWrite(char truth_table[], char argv[], int index, int row_size);
void TableSolver(int number_list[], char truth_table[], int letter_number, int row_size);
void Logic(char dest[], char src1[], char src2[], char ops[], int truth_length);
int main(int argc, char *argv[]){
char *truth_table = NULL;
int number_list[27] = {[0 ... 26] = 0}; char letter_list[27] = {[0 ... 26] = 0};
int letter_number = 0, row_size = 0, row_space = 0, index;
if(argc != 2) return 0;
FormulaVerify(argv[argc - 1]);
LetterInit(number_list, argv[1], letter_list, &letter_number, &row_size, &row_space);
TruthAllocate(&truth_table, &row_space, &row_size, &letter_number);
index = TruthInit(number_list, truth_table, letter_list, letter_number, row_size);
FormulaWrite(truth_table, argv[1], index, row_size);
TableSolver(number_list, truth_table, letter_number, row_size);
printf("%s", truth_table);
free(truth_table);
truth_table = NULL;
return 0;}
void LetterInit(int number_list[], char formula[], char letter_list[], int *letter_number, int *row_size, int *row_number){
int i, index = 0; char hold; *row_number += 1;
for(i = 0; formula[i] != 0; i++){
*row_number += (formula[i] == '(');
hold = formula[i]*(formula[i] >= 'A' && formula[i] <= 'Z');
index = (hold - 'A')*(hold >= 'A');
*letter_number += (hold >= 'A' && letter_list[index] == 0);
letter_list[index] += hold*(letter_list[index] == 0);
}
*row_size = (1 << *letter_number) + 7 + i; //2 for letter and \n, 5 for refs at end of line
for(int j = 0, index = 0; j < 26; j++){
letter_list[index] = letter_list[j]*(letter_list[j] != 0);
number_list[j + 1] = (i + (*row_size * index))*(letter_list[j] != 0); // sets each to the truth offset
index += (letter_list[j] != 0);
}
number_list[0] = i + (*row_size * *letter_number); //truth space of 1st formula
return;}
int TruthInit(int number_list[], char truth_table[], char letter_list[], int letter_number, int row_size){
int truth_half = 1 << letter_number; char truth = 1;
for(int i = 0; i < letter_number; i++){
	truth_half /= 2;
	truth_table[i*row_size] = letter_list[i];
	for(int j = 0, truth = 1; j < (1 << letter_number); j++){
		truth_table[number_list[letter_list[i] - 64] + j] = '0' + truth;
		truth = truth*(((j + 1) % truth_half) != 0) + (1 - truth)*(((j + 1) % truth_half) == 0);
	}
}
return letter_number*row_size;}
void FormulaWrite(char truth_table[], char formula[], int index, int row_size){
int i = 0, current_depth = 0, target_depth = 0, max_depth = 0, row_diff = row_size, connect_counter = 4;
for(i = 0; formula[i] != 0; i++){
current_depth += (formula[i] == '(');
current_depth -= (formula[i] == ')');
max_depth += (current_depth > max_depth);
}
for(target_depth = max_depth, max_depth = 6; target_depth > 0; target_depth--){
	for(current_depth = 0, i = 0; formula[i] != 0; i++){
		if(formula[i] == '(')current_depth++;
		if(current_depth >= target_depth){
			truth_table[index] = formula[i]; index++; row_diff--;
		}
		if(current_depth == target_depth && formula[i] == ')'){
			index += row_diff; row_diff = row_size; max_depth = 6; connect_counter = 4;
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
void TableSolver(int number_list[], char truth_table[], int letter_number, int row_size){
int ref_offset = ((letter_number + 1) * row_size) - 6; //'A', 'B', refs, operator offset will be ref_off + 2;
int solve_offset = number_list[0], truth_dex1 = 0, truth_dex2 = 0, i = 0;
for(i = ref_offset + 6; truth_table[i] != 0; i += row_size){
	truth_dex1 = number_list[(truth_table[ref_offset] % 64) & 31]; //'A' yeilds position 1, whitespace 0
	truth_dex2 = number_list[(truth_table[ref_offset + 1] % 64) & 31];
	truth_dex2 += row_size*(truth_table[ref_offset] == ' ' && truth_dex2 == truth_dex1);
	Logic(&truth_table[solve_offset], &truth_table[truth_dex1], &truth_table[truth_dex2], &truth_table[ref_offset + 2], 1 << letter_number);
	number_list[0] += row_size*((truth_table[ref_offset] == ' ') + (truth_table[ref_offset + 1] == ' '));
	solve_offset += row_size;
	ref_offset += row_size;
}
for(i = 0, truth_dex1 = solve_offset, truth_dex2 = solve_offset - row_size; i < (1 << letter_number); i++){
	truth_table[truth_dex1 + i] = (~truth_table[truth_dex2 + i] & 1) | 48;
}
return;}
void Logic(char dest[], char src1[], char src2[], char ops[], int truth_length){
char place[4] = {0, 0, 0, 0}; int i;
for(i = 0; i < truth_length && ops[2] == '|'; i++){
place[0] = src1[i]; place[1] = (~src1[i] & 1) | 48;
place[2] = src2[i]; place[3] = (~src2[i] & 1) | 48;
dest[i] = place[0 + ops[0] - 32] | place[2 + ops[1] - 32];
}
for(i = 0; i < truth_length && ops[2] == '&'; i++){
place[0] = src1[i]; place[1] = (~src1[i] & 1) | 48;
place[2] = src2[i]; place[3] = (~src2[i] & 1) | 48;
dest[i] = place[0 + ops[0] - 32] & place[2 + ops[1] - 32];
}
for(i = 0; i < truth_length && ops[2] == '>'; i++){
place[0] = src1[i]; place[1] = (~src1[i] & 1) | 48;
place[2] = src2[i]; place[3] = (~src2[i] & 1) | 48;
dest[i] = (~place[0 + ops[0] - 32] & 1) | 48 | place[2 + ops[1] - 32];
}
return;}
void FormulaVerify(char formula[]){
int i, depth, error = 0; int part_depth[100] = {[0 ... 99] = 0};
for(i = 1, depth = 0; formula[i] != 0 && error == 0; i++){
	formula[i] += ('A' - 'a')*(formula[i] >= 'a' && formula[i] <= 'z');
	error += 1*(formula[i] != ' ' && formula[i] != '!' && formula[i] != '>' && formula[i] != '&' && formula[i] != '|' && formula[i] != '(' && formula[i] != ')' && (formula[i] < 'A' || formula[i] > 'Z'));
	part_depth[(2*depth) + 0] += (formula[i] == '>' || formula[i] == '&' || formula[i] == '|');
	part_depth[(2*depth) + 1] += (formula[i] == '(' || (formula[i] >= 'A' && formula[i] <= 'Z'));
	error += 32*((formula[i] == '>' || formula[i] == '&' || formula[i] == '|') && part_depth[(2*depth) + 1] != 1);
	error += 64*(formula[i] == '!' && formula[i + 1] != '>' && formula[i + 1] != '&' && formula[i + 1] != '|' && formula[i - 1] != '>' && formula[i - 1] != '&' && formula[i - 1] != '|');
	if(formula[i] == ')'){
	error += 128 * (part_depth[(2*depth) + 0] != 1);  // connective count
	error += 256 * (part_depth[(2*depth) + 1] != 2);  //formula count, ( or A,B,C
	part_depth[(2*depth) + 0] = 0;
	part_depth[(2*depth) + 1] = 0;
	}
	depth += (formula[i] == '(') - (formula[i] == ')');
	error += 2*(depth == -1 && formula[i + 1] != 0);
}
error += 4*(formula[0] != '(') + 8*(formula[i] == 0 && formula[i - 1] != ')') + 16*(formula[i] == 0 && depth != -1);
if(error != 0){printf("error code is: %d\n", error); exit(0);}
return;}
void TruthAllocate(char **truth_table, int *row_space, int *row_size, int *letter_number){
 *row_space = (*row_size * *letter_number) + (*row_size * *row_space) + 1;
 *truth_table = malloc(*row_space * sizeof(char));
 if(*truth_table == NULL){printf("allocation failed, exiting...\n"); exit(0);}
 *(*truth_table + *row_space - 1) = 0;
 for(int i = 0; i < *row_space - 1; i++){
	*(*truth_table + i) = ' ' + ('\n' - ' ')*((i + 1) % *row_size == 0);
 }
return;}
