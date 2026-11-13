
#ifndef KEYWORD_H
#define KEYWORD_H
 
typedef enum { KW_NONE, KW_TYPE, KW_CONTROL } KeywordType;
 
KeywordType keyword_type(const char *word);
 
#endif