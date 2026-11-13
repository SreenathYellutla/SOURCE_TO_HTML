#include "header.h"
#include "S_html.h"
#include "HTML.h"
#include "Keyword.h"
static ParserState next_state(int ch, Files *token)
{
    int next;
 
    if (isalpha(ch) || ch == '_')
        return STATE_WORD;

    if (isdigit(ch))
        return STATE_NUMBER;

    if (ch == '"')
        return STATE_STRING;

    if (ch == '\'')
        return STATE_CHARACTER;
    /* '#' in a macro body is not a directive */ 
    if (ch == '#' && token->first_on_line)      
        return STATE_PREPROCESSOR;
 
    if (ch == '.' || ch == '/')
    {
        next = fgetc(token->input_file);
        if (next != EOF)
            ungetc(next, token->input_file);
 
        if (ch == '.' && isdigit(next))         /* .5 */
            return STATE_NUMBER;

        if (ch == '/' && next == '/')
            return STATE_SINGLE_COMMENT;

        if (ch == '/' && next == '*')
            return STATE_MULTI_COMMENT;
    }

    return STATE_IDLE;
}
Status source_to_html(Files *files)
{
    int ch;
 
    html_begin(files->output_file);
    // number for line 1 
    html_line_number(files);                
 
    while ((ch = fgetc(files->input_file)) != EOF)
    {
        switch (next_state(ch,files))
        {
            case STATE_WORD:
                        word_scan(ch, files);     
                        break;

            case STATE_NUMBER:
                        number_scan(ch,files);
                        break;

            case STATE_STRING:         
                        string_scan(ch,files);       
                        break;

            case STATE_CHARACTER:
                        char_scan(ch,files);
                        break;

            case STATE_SINGLE_COMMENT:
            case STATE_MULTI_COMMENT:
                        comment_scan(ch,files);
                        break;

            case STATE_PREPROCESSOR:
                        preprocessor_scan(ch,files); 
                        break;
 
            // STATE_HEADER is entered from inside preprocessor_scan, after #include 
            case STATE_HEADER:
            case STATE_IDLE:
            default:                   
                        char_to_html(ch,files); 
                        break;
        }
    }
 
    html_end(files->output_file);
    return Success;
}