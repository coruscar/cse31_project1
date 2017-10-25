#include <stdio.h>
#include <ctype.h> //isalum
#include <string.h>


#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
    // Implement if desire

    return 0;
}

/**
 * You may assume that all strings are properly null terminated
 * and will not overrun the buffer set by MAXSIZE
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {

    if (*pattern == '\0') {
        return 1;
    }


    //string length of pattern and line
    int plen = (int) strlen(pattern);
    int llen = (int) strlen(line);

    //inits important variables
    int streak = 0;
    int lpos = 0;
    int pisalnum = 0;
    int offset = 0;
    int plus_exists = 0;
    int last_slash = 0;

    //quick check to make sure query is alphanumerical
    for (int i = 0; i < plen; i++) if (isalnum(pattern[i])) pisalnum = 1;

    //the main looping boy
    for (lpos = 0; lpos < llen; lpos++) {
        //I know this is low-tier coding. I'm sorry TODO FIX THIS SUBSTANDARD ATROCITY
        badconvention:
        //if the line is a null terminator, return 0
        if (line[lpos] == '\0') {
            return 0;
        }
        if (line[lpos] == '\n') {
            return 0;
        }
        //printf("pattern[%d] = %c\t\n",matching_consec_characters,pattern[matching_consec_characters]);
        //pattern[streak+1] == '\?'


        if (pattern[streak] == '\\'){
            if (pattern[streak+1] == line[lpos]){ //TODO add modifier cases
                streak++;
                last_slash = 1; //cheap hacky code
            } else {
                streak = 0;
                last_slash = 1;
                continue;

            }
        } else {
            last_slash = 0;
        }


        if (pattern[streak] == '+' && last_slash == 0 && plus_exists == 0){
            //printf("we got this far\t");
            if (pattern[streak - 1] == line[lpos] && pattern[streak - 1] != '\\'
                && pattern[streak + 1] <= plen) {//TODO add escape scenario
                plus_exists = 1;
                streak--;
                offset++;
                goto badconvention;
            } else {
                return 0;
            }
            //plus_exists = 1;

//            lpos--;
            //goto badconvention;
        }

        if (line[lpos] == pattern[streak] || pattern[streak] == '.') {//if they're equal to each other or '.'
            streak++;

        } else if (plus_exists){
            streak = streak + plus_exists + 1; //increments streak, adds offset which was temporarily taken away.
            plus_exists = 0;//this words because we know we matched the letter before at least one time

        }else {
            streak = 0;
            continue;
        }

        //it should be the only way to return 1, is to make the streak = pattern length
        if (streak == plen + offset) {
            return 1;
        }


    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}
