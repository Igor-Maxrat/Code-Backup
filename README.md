Description...

Hello friends! I developed a program designed to solve a logical formula like (A | B), or (A & (B | C)), by printing a truth table in
the terminal. Make sure to only use one character symbols, '(' , ')', '!', '>', '&', '|', or the table will not be produced. Further, lowercase 
letters are automatically converted to uppercase, so only A through Z can be used. Greek or scientific symbols are not accepted, but could be added
in the future.

Compile Instructions...
      Compile with GCC as...
      GCC calc.c

Ignore...
      Ignore the input.c unless you want to edit/improve/test the input filter directly. It is designed to prevent the parent program from crashing
      due to bad inputs.

Run Code...
      ./a.out '(A | B)'
      ./a.out '(A !| B)'
      ./a.out '(A |! B)'
      ./a.out '(A !|! B)'

Input Instructions...
      1. Use single quotes ' '
      2. Provide only one input argument
      3. Use only symbols '(, ), | & > !'
      4. Use only letters 'A' through 'Z', uppercase
      5. Program requires the file and 1 formula, so argc must equal 2.
      6. To negate 1st formula, place '!' behind the logical connective, '!' in front of to negate 2nd formula

Output example...
./a.out '(A &! (C | D))'
A             11110000      
C             11001100      
D             10101010      
(C | D)       11101110 CD  |
(A &! (C | D))00010000 A  !&
(A &! (C | D))11101111 A  !&            //Negation of the top level formula always included

Improve My Code, Or Make Something Better...
      Feel free to make your own versions better and faster. I have much to learn, so please share what you've found!

Compatibility...
      Still in development, there may be bugs! Designed for Linux terminal, unsure of other OS behaviors!

Contact Developer...
      Feel free to email me at igormaxrat@gmail.com with ideas or improvements. Modify and share modified code as you wish. 
      Criticism is fine, avoid the trash talk.

Error Codes:
If an error code is thrown from the input, note that the filter is designed to stop running if an error is caught and terminate
execution. Thus, not all errors will be displayed on the output, but only those the logic encounters. That being said...

Codes...

Code 1. Unrecognized symbol
Code 2. The closing parenthesis of the top level formula came too early
Code 4. The input string does not start with an opening parenthesis
Code 8. The input string does not end with a closing parenthesis
Code 16. The number of '(' does not equal the number of ')'
Code 32. A logical symbol was placed somewhere other than between two formulas 'A', 'B', 'C', '()'
Code 64. Negations were present '!' that did not come immediately before or after a logical symbol
Code 128. The number of logical connectives in a formula is not 1
Code 256. The number of sub-formulae in a formula is not 2.

License: Open Source
Liability: Use at your own risk and responsibility!
