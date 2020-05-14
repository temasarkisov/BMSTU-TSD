#include "word_oper.h"

/* char *wordInput()
{
    char notValidSymbols[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '}; 
    char *wordNew = (char *) malloc(WORD_MAX_SIZE * sizeof(char));

    scanf("%s", wordNew);
    for (int i = 0; i < 11; i++)
        if (strchr(wordNew, notValidSymbols[i]) != NULL)
            return NULL; 
    
    return wordNew;
} */

char *wordInput()
{
    char notValidSymbols[] = {" 0123456789,.!?/(){}+-=*&^#@"}; 
    char *wordNew = (char *) malloc(WORD_MAX_SIZE * sizeof(char));
    char letter = ' ';
    int ind = 0;

    while (letter != '\n')
    {
        scanf("%c", &letter);
        if (letter == '\n' && ind == 0)
            return NULL;
        if (strchr(notValidSymbols, letter) != NULL)
            return NULL;
        if (letter != '\n')
        {
            wordNew[ind] = letter;
            ind++;
        }
    }

    return wordNew;
}