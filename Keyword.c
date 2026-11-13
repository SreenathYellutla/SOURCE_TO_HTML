
#include <string.h>
#include "Keyword.h"
#include "header.h"
#include "HTML.h"
#include "S_html.h"
 
static const char *type_keywords[] = {"char", "short", "int", "long", "float", "double",
                                    "signed", "unsigned", "void", NULL};
 
static const char *control_keywords[] = {"auto", "break", "case", "const", "continue", "default", "do", "else",
                                    "enum", "extern", "for", "goto", "if", "register", "return", "sizeof",
                                    "static", "struct", "switch", "typedef", "union", "volatile", "while", NULL};
 
// Check if a word is in a list of keywords. Returns 1 if found, 0 otherwise.
static int in_list(const char *word, const char *list[])
{
    for (int i = 0; list[i] != NULL; i++)
        if (strcmp(word, list[i]) == 0)
            return 1;
    return 0;
}


KeywordType keyword_type(const char *word)
{
    if (in_list(word, type_keywords))
        return KW_TYPE;
    if (in_list(word, control_keywords))
        return KW_CONTROL;
    return KW_NONE;
}