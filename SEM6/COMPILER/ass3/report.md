### One
For the date validation, the main challenge was handling the ambiguity between formats like dd-mm versus mm-dd, and numeric months versus text months (e.g., "JAN").

Initially, I considered writing separate, strict regex patterns for every possible valid date, but that makes the LEX file huge and hard to read.

Upon further thinking, I landed on a hybrid approach:
- Use LEX only to identify the "shape" of the data (e.g., Num-Num-Num or Num-Text-Num).
- Offload the logic to C functions.

I used sscanf to parse the strings into integers. The validation logic (checking if a day is valid for a given month) was much easier to write in C using a lookup array for days-in-month. For the leap year check, I just added a conditional to update the February limit to 29 if the year was divisible by 4 (and satisfied the 100/400 rule).

### Two
The requirement here was straightforward—counting specific SQL command types—so I avoided writing a full SQL parser.

The logic relies on tokenizing simple words:
- I defined a regex {WORD} to catch any sequence of alphabetic characters.
- Every time a word is found, I pass it to a C function check_and_count.

In the global space, I maintained two string arrays (lookup tables) for DDL and DML keywords. The processing function simply iterates through these arrays and compares the current word using strcasecmp to handle case insensitivity (so "SELECT", "Select", and "select" all count). This keeps the LEX rules clean and the logic extensible just by adding words to the arrays.

### Three
Validating arithmetic expressions in LEX is tricky because LEX is usually stateless. To solve this, I had to manually track the "context" using C variables.

I used a flag called expect_operand:
- At the start, we expect a Number or Identifier (flag = 1).
- After seeing an Identifier, we expect an Operator next (flag = 0).
- If we see an Operator but expect_operand was 1 (meaning we were waiting for a number), it’s an error (e.g., + + or * a).

For parentheses, I used a simple integer counter paren_count:
- Increment on (
- Decrement on )
- If the count drops below zero at any point, or isn't zero at the end, the expression is invalid.