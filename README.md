# Assembler

Assembling 

SIA is similar to assembling other assembly languages. With SIA, almost every instruction is aligned with a 4 bit nibble, 
so all assembly should be presented in hexadecimal. 

Step 1: Determine the opcode. Use the SIA documentation to find the opcode. Note that these are in decimal; convert to hexadecimal. 
That will be the first “digit” of the first byte.

Step 2: Find the format. The SIA documentation lists the format for an instruction. 
For example, add uses the “3R” format. Find the “3R” section of the document.

Step 3: Determine the remaining portions of the hexadecimal. This depends on the opcode. 
Make sure to note instructions that require 32 bits instead of 16 bits (jump and branches).


