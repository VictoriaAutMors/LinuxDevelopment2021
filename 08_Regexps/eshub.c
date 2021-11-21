#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "regex.h"

int RegexReplaceOnce(char **textForReplacement, const char *pattern, const char *replacementWord) {
    regex_t regular;
    unsigned int countOfReplacements = 0;
    if(!regcomp(&regular, pattern, REG_EXTENDED)) {
        size_t numberOfMatches = regular.re_nsub;
        regmatch_t matchesArray[numberOfMatches + 1];
        const char *lengthOfReplacementWord, *pointer;
        int br = 0;
        pointer = replacementWord;
        while(1) {
            while(*++pointer > 31);
            if(*pointer) {
                br++;
            }
            else {
                break; 
            }
            printf("skjdfksjfdkjfskdfj");
        }
        if(br != numberOfMatches) {
            regfree(&regular);
            return -2;
        }
        char *newAllocation;
        char *searchStart = *textForReplacement;
        int k = 0;
        while(!regexec(&regular, searchStart, numberOfMatches + 1, matchesArray, REG_NOTBOL)) {
            k++;
            newAllocation = (char *)malloc(strlen(*textForReplacement) + strlen(replacementWord));
            if(!newAllocation) exit(EXIT_FAILURE);
            *newAllocation = '\0';
            strncat(newAllocation, *textForReplacement, searchStart - *textForReplacement);
            pointer = lengthOfReplacementWord = replacementWord;
            int index;
            strncat(newAllocation, searchStart, matchesArray[0].rm_so);
            for(int k = 0; k < numberOfMatches; k++) {
                while(*++pointer > 31);
                index = *pointer;
                strncat(newAllocation, lengthOfReplacementWord, pointer - lengthOfReplacementWord);
                strncat(newAllocation, searchStart + matchesArray[index].rm_so, matchesArray[index].rm_eo - matchesArray[index].rm_so);
                lengthOfReplacementWord = pointer++;
            }
            strcat(newAllocation, pointer );
            unsigned int newStartOffset = strlen(newAllocation);
            strcat(newAllocation, searchStart + matchesArray[0].rm_eo);
            free(*textForReplacement);
            *textForReplacement = (char *)malloc(strlen(newAllocation)+1);
            strcpy(*textForReplacement, newAllocation);
            searchStart = *textForReplacement + newStartOffset;
            free(newAllocation);
            countOfReplacements++;
            if (k == 1) {
                break;
            }
        }
        regfree(&regular);
        *textForReplacement = (char *)realloc(*textForReplacement, strlen(*textForReplacement) + 1);
        return countOfReplacements;
    } else {
        return -1;
    }
}

int main(int argc, char **argv) {
	if(argc < 2) {
		return 0;
	}
    char *regexp, *substitution, *string;
    regexp = argv[2];
    substitution = argv[3];
    string = argv[1];

    char *stringDup[1]; 
    stringDup[0] = strdup(string);
    RegexReplaceOnce(stringDup, regexp, substitution);
    
    printf("%s\n", stringDup[0]);

    return 0;
}
