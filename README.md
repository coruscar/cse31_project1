# CSE-031 Project 1 -- Restricted Grep

The UNIX utility, grep, is used to parse or search through strings for a particular pattern. The
strings can be either put in through the console or in text files. It is a very convenient way to look
for basic patterns or ones with wildcards. It is fairly complicated to support the full character set
that grep is capable of. 

This project implements a restricted grep, rgrep.

### Wildcard Characters

. (period): Matches any character

\+ (plus sign): The preceding character will appear one or more times.

? (question mark): The preceding character may or may not appear in the line.

\ (backslash): "Escapes" the following character, nullifying any special meaning it has. 
