#include <stdio.h>
int FormulaVerify(char formula[]);
int main(argc, *argv[]){
int error = FormulaVerify(argv[argc - 1]);
printf("error code is: %d\n", error);
return 0;}
int FormulaVerify(char formula[]){
int i, depth, error = 0; int error_depth[100] = {[0 ... 99] = 0};
for(i = 0; formula[i] != 0 && error == 0; i++){
	depth += (formula[i] == '(') - (formula[i] == ')');
	formula[i] += ('A' - 'a')*(formula[i] >= 'a' && formula[i] <= 'z');
	error += 1*(formula[i] != ' ' && formula[i] != '!' && formula[i] != '>' && formula[i] != '&' && formula[i] != '|' && formula[i] != '(' && formula[i] != ')' && (formula[i] < 'A' || formula[i] > 'Z'));
	error += 2*(depth == 0 && formula[i + 1] != 0);
}
error += 4*(formula[0] != '(') + 8*(formula[i] == 0 && formula[i - 1] != ')') + 16*(depth != 0);
for(i = 1, depth = 0; formula[i] != 0 && error == 0; i++){
	error_depth[(2*depth) + 0] +=  (formula[i] == '>' || formula[i] == '&' || formula[i] == '|');
	error_depth[(2*depth) + 1] +=  ((formula[i]== '(' || (formula[i] >= 'A' && formula[i] <= 'Z'));
	error += 32*(error_depth[(2*depth) + 0] > 0 && error_depth[(2*depth) + 1] != 1);
	error += 64*(formula[i] == '!' && formula[i + 1] != '>' && formula[i + 1] != '&' && formula[i + 1] != '|' && formula[i - 1] != '>' && formula[i - 1] != '&' && formula[i - 1] != '|');
	if(formula[i] == ')'){
	error += 128 * (error_depth[(2*depth) + 0] != 1);  // connective count
	error += 256 * (error_depth[(2*depth) + 1] != 2);  //formula count, ( or A,B,C
	error_depth[(2*depth) + 0] = 0;
	error_depth[(2*depth) + 1] = 0;
	}
	depth += (formula[i] == '(') - (formula[i] == ')');
}
return error;}
