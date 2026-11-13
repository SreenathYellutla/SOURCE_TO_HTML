#ifndef HEADER_H
#define HEADER_H
 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
#define TOKEN_SIZE 256

typedef enum {
    STATE_IDLE,
    STATE_WORD,
    STATE_NUMBER,
    STATE_STRING,
    STATE_CHARACTER,
    STATE_SINGLE_COMMENT,
    STATE_MULTI_COMMENT,
    STATE_PREPROCESSOR,
    STATE_HEADER
} ParserState;


typedef enum
{
    Failure,
    Success
}Status;


typedef struct
{
    FILE* input_file;
    
    FILE* output_file;
   
    int line;                      
    int first_on_line;   
    char tok[TOKEN_SIZE];

}Files;


Status validate_args(int argc,char* argv[]);
Status open_files(Files *file,char *argv[]);

Status word_scan(int ch, Files *token);

Status number_scan(int ch, Files *token);

Status string_scan(int ch, Files *token);

Status char_scan(int ch, Files *token);

Status comment_scan(int ch, Files *token);

Status preprocessor_scan(int ch, Files *token);

Status header_scan(int ch, Files *token);

Status macro_scan(int ch, Files *token);

#endif