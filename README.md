# my_bc
reimplementation of unix basic calculator (bc)  

# Synopsis
./my_bc "1 + 2 * (3 - 42) / 5"   
./my_bc "-(-((-4)+-6))"  

# Description
A valid expression:  
• must only contain the operators +, -, *, /, and modulo (percent)  
• must only have integer values  
• can contain parentheses, but each group must be properly closed  
• can contain spaces  

Since we are doing whole number arithmetic, divisions are euclidian keeping only the quotient, while the remainder can be obtained with a modulo operation.  

# Allowed functions
• malloc(3)  
• free(3)  
• printf(3)  
• write(2)  

# Installation
make  
to clean up after usage: make fclean  

Enjoy!
