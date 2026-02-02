### One

Single line comments are simple enough, detect "//" and consume characters till "\\n"

For multi line comments, initially I tried a logic of:
"/\*"[.\n]\*"\*/
but it ended up consuming the end sequence aswell

Upon further thinking I landed on this idea:
if the character being processed is not "\*" --> consume it, as it cannot be end tag after that
and, if a "\*" is encountered --> 
    we want to consume the asterisks upto the point before a "\*/" sequence (negation)
    for this I used \*+[^\*/].
so the final regex for multi line comments comes out to be "/\*"([^\*]|\\\*+[^\*/])\*"\*/"

### Two

Single and multi line comment logic applies from First code
Documentation code is actually already handled by the existing multi line comment logic,
as it simply degenerates into a case of "/\*" followed by an extra "\*" (no end sequence "\*/" following it)

But, for clarity sake, "/\*\*"([^\*]|\\\*+[^\*/])\*"\*/" can be added, with just an extra "\*" in the start sequence.

### Three

Regex logic was simple enough - 
    Tag starts with "\<" or "\</"
    then, just consume the first word after, which is the tag name
    and skip over other text line tag modifiers (src, href, etc.), tag closer (not needed), and body text

The text consumed with regex was captured from yytext to a string variable (char* since this is C)
and after some manipulation the initial "\<" or "\</" was removed and a "\\0" was added to the tag, as a string.

In the global space, a static array based hashmap implementation is used.
An array of strings (char\*\*) and an array of ints (int\*) are used as key and value stores.
A counter variable (int) is used to keep track of size of hashmap.

Each new tag, after preprocessing to string, is passed to the "process_tag" function -
This checks through the keys in the string array -
    if matched, value is incremented
    if not, a new key is created with value 1 and the counter is incremented.
Key matching happens upto counter (existing keys at that point of time)

Output is simply printing all key value pairs after yylex() is done.