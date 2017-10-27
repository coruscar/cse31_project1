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
    int additional_iterations = 0;
    int firstpath = 0;
    int secondpath = 0;



    int streak = 0;
    int lpos = 0;
    //int pisalnum = 0;
    int offset = 0;
    //int plus_exists = 0;
    //int last_slash = 0;
    int degbugvar = 0;

    //int secondtimearound = 0;

    //quick check to make sure query is alphanumerical
    //for (int i = 0; i < plen; i++) if (isalnum(pattern[i])) pisalnum = 1;

    //the main looping boy
    start:
    for (lpos = 0; lpos < llen; lpos++) {
        //I know this is low-tier coding. I'm sorry TODO FIX THIS SUBSTANDARD ATROCITY
        //badconvention:
        //if the line is a null terminator, return 0
        if (line[lpos] == '\0') {
            return 0;
        }
//        if (line[lpos] == '\n') {
//            return 0;
//        }

        //printf("pattern[%d] = %c\t\n",matching_consec_characters,pattern[matching_consec_characters]);
        //pattern[streak+1] == '\?'


        if (pattern[streak] == '\\') {
            if(pattern[streak+2] == '?') {
                //lpos++;
                streak++;
                goto i_have_many_questions;
            }
            if (pattern[streak + 1] == line[lpos]) { //TODO add modifier cases

                streak++;
                //continue; //I just added this, remove if problems arise
                //last_slash = 1; //cheap hacky code
            } else {
                streak = 0;
                //last_slash = 1;
                continue;

            }
        } else {
            //last_slash = 0;
        }

        //printf("%s",line);
//        if (line[lpos] == 'l'){
//            degbugvar = 1;
//        }


        //this iteration doesn't matter, we '?' boys
        i_have_many_questions:
        if(pattern[streak+1]=='?'){

            if(pattern[streak] == '.'){
                if (additional_iterations == 0) {
                    additional_iterations++;
                } else {
                    additional_iterations = 0;
                }
                if(firstpath){
                    goto second;
                }
                if (secondpath){
                    goto first;
                }


                //printf("m %s\n",line);
                //printf("Why isn't this infinite\t");

            }
            if (line[lpos] == pattern[streak]){
                first:
                firstpath = 1;
                //printf("v %s\n",line);

                streak = streak + 2;
                if (lpos+2 >= llen){//for the single letter cases, I hope this doesn't mess anything else up
                    streak++;
                }
                if (streak >= plen) //hacky code
                    goto ending;
                continue;
            } else {
                second:
                secondpath = 1;

                //printf("m %s\n",line);
                streak = streak + 2;
                if (streak >= plen) //hacky code
                    goto ending;

                lpos = lpos-1;
                continue;
            }
        }


        //plus solution
        if (pattern[streak + 1] == '+') {

            //printf("gtf 1\t");
            int i = 0;

            //'.' implementation


            char recurring = 0;
            int plus_offset = 0;

            if (pattern[streak] == '.'){ //half works for '.+l' or '.+o' and I don't know  why TODO fix
                recurring = line[lpos];
            }
            if (pattern[streak + 2] == pattern[streak]){
                plus_offset++;//
            }
            while (1) {
                //printf("gtf %s\t",line);


                if (degbugvar){
                    printf("line[lpos+i] = %c\t pattern[streak] = %c\t i = %i\n",line[lpos+i], pattern[streak],i);
                }

                if (line[lpos+i] == pattern[streak] || line[lpos+i] == recurring) {//TODO add modifiers
                    i++;
                } else if (i != 0){
                    //printf("gtf 4\t");
                    if (i>1) { //if this isn't here, plus_offset would cause us to incorrectly return words like "aba" with "a+ab" queries
                        lpos = lpos + i - 1 - plus_offset;
                    } else{
                        lpos = lpos + i - 1;
                    }
                    streak = streak + 2;
                    break;
                } else{
                    break;
                }
            }
            //not sure why I need this here, TODO look into this
            goto ending;

        }


        if (line[lpos] == pattern[streak] || pattern[streak] == '.') {//if they're equal to each other or '.'
            streak++;

        } else {
            streak = 0;
            continue;
        }


        ending:

        //it should be the only way to return 1, is to make the streak = pattern length


        if (streak >= plen + offset) {
            return 1;
        }



    }
    //hey if it didn't work and we got some crazy ".?" going on, let's just do it again but a little differently
    if (additional_iterations > 0){
        goto start;
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
