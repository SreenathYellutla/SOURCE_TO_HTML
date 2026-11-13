#include "header.h"
#include "HTML.h"
#include "Keyword.h"
#include "S_html.h"

// The list of preprocessor directives to recognize. The list is sorted for binary search.
static const char *directives[] = {
    "#include", "#define", "#undef", "#if", "#ifdef", "#ifndef",
    "#else", "#elif", "#endif", "#error", "#pragma", "#line", NULL
};

// Print a warning message with the line number.
static void warn(Files *token, const char *msg)
{
    fprintf(stderr, "Warning: line %d: %s\n", token->line, msg);
}

// Skip blanks and tabs, returning the first non-blank character.
// The blanks are sent to HTML.
static int skip_blanks(Files *token)
{
    int c;

    while ((c = fgetc(token->input_file)) == ' ' || c == '\t')
        char_to_html(c, token);
    return c;
}

// word_scan: takes letters, digits and underscores. 
// If the token is too long, it is split into multiple tokens. 
// The first part is checked for keywords;
Status word_scan(int ch, Files *token)
{
    int i = 0;
    int c = ch;
    int x= 0;

    while (c != EOF && (isalnum(c) || c == '_'))
    {
        if (i == TOKEN_SIZE - 1)            
        {
            token->tok[i] = '\0';
            string_to_html(token->tok, token);
            i = 0;
            x = 1;
        }

        token->tok[i++] = (char)c;
        c = fgetc(token->input_file);
    }
    token->tok[i] = '\0';

    if (c != EOF)
        ungetc(c, token->input_file);

    switch (x ? KW_NONE : keyword_type(token->tok))
    {
        case KW_TYPE:
            html_data_keyword_begin(token->output_file);
            string_to_html(token->tok, token);
            html_data_keyword_end(token->output_file);
            break;

        case KW_CONTROL:
            html_control_keyword_begin(token->output_file);
            string_to_html(token->tok, token);
            html_control_keyword_end(token->output_file);
            break;
            
        default:
            string_to_html(token->tok, token);
            break;
    }
    return Success;
}


//   Numbers: 10, 0x1F, 1.5f, 10UL, 1e-3, .5
//   Takes digits, letters and '.', plus a sign right after an exponent letter.
 
Status number_scan(int ch, Files *token)
{
    int c = ch;
    int prev;

    html_number_begin(token->output_file);
    do
    {
        char_to_html(c, token);
        prev = c;
        c = fgetc(token->input_file);

    } while (c != EOF &&(isalnum(c) || c == '.' || c == '_' ||
              ((c == '+' || c == '-') && strchr("eEpP", prev) != NULL)));

    if (c != EOF)
        ungetc(c, token->input_file);

    html_number_end(token->output_file);
    return Success;
}

// Scan a quoted string or character literal. The quote character is passed in, 
// and the error message to use if the string is unterminated.
static Status quoted_scan(int quote, Files *token, const char *what)
{
    int c;
    int closed = 0;

    if (quote == '"')
        html_string_begin(token->output_file);
    else
        html_character_begin(token->output_file);

    char_to_html(quote, token);

    while ((c = fgetc(token->input_file)) != EOF)
    {
        if (c == '\n')                       
        {
            ungetc(c, token->input_file);
            break;
        }

        char_to_html(c, token);

        if (c == '\\')
        {
            int next = fgetc(token->input_file);
            if (next != EOF)
                char_to_html(next, token);
            continue;
        }
        if (c == quote)
        {
            closed = 1;
            break;
        }
    }

    if (quote == '"')
        html_string_end(token->output_file);
    else
        html_character_end(token->output_file);

    if (!closed)
    {
        warn(token, what);
        return Failure;
    }

    return Success;
}

Status string_scan(int ch, Files *token)
{
    return quoted_scan(ch, token, "Unterminated string literal");
}

Status char_scan(int ch, Files *token)
{
    return quoted_scan(ch, token, "Unterminated character literal");
}


// Scan a comment. The first character is the '/', which has already been read.
Status comment_scan(int ch, Files *token)
{
    int c = fgetc(token->input_file);

    if (c == '/')   /* Single-line comment */
    {
        html_comment_begin(token->output_file);

        char_to_html(ch, token);
        char_to_html(c, token);

        while ((c = fgetc(token->input_file)) != EOF)
        {
            if (c == '\n')
            {
                ungetc(c, token->input_file);
                break;
            }

            char_to_html(c, token);
        }

        html_comment_end(token->output_file);
        return Success;
    }

    if (c == '*')   /* Multi-line comment */
    {
        int prev = 0;
        int closed = 0;

        html_comment_begin(token->output_file);

        char_to_html(ch, token);
        char_to_html(c, token);

        while ((c = fgetc(token->input_file)) != EOF)
        {
            if (c == '\n')
            {
                html_comment_end(token->output_file);
                char_to_html(c, token);

                html_line_number_begin(token->output_file);
                html_comment_begin(token->output_file);

                prev = c;
                continue;
            }

            char_to_html(c, token);

            if (prev == '*' && c == '/')
            {
                closed = 1;
                break;
            }

            prev = c;
        }

        html_comment_end(token->output_file);

        if (!closed)
        {
            warn(token, "Unterminated comment");
            return Failure;
        }

        return Success;
    }

    // Not a comment: restore the lookahead character 
    if (c != EOF)
        ungetc(c, token->input_file);

    return Failure;
}

// Scan a header name after #include. 
//The first character is the opening delimiter, which has already been read.
Status header_scan(int ch, Files *token)
{
    int c;
    int close = (ch == '<') ? '>' : '"';
    int closed = 0;

    html_header_begin(token->output_file);
    char_to_html(ch, token);

    while ((c = fgetc(token->input_file)) != EOF)
    {
        if (c == '\n')
        {
            ungetc(c, token->input_file);
            break;
        }
        char_to_html(c, token);
        if (c == close)
        {
            closed = 1;
            break;
        }
    }
    html_header_end(token->output_file);

    if (!closed)
    {
        warn(token, "Missing closing delimiter in header name");
        return Failure;
    }
    return Success;
}

/*
 * The name after #define.
 */
Status macro_scan(int ch, Files *token)
{
    int c;

    html_macro_begin(token->output_file);
    char_to_html(ch, token);

    while ((c = fgetc(token->input_file)) != EOF && (isalnum(c) || c == '_'))
        char_to_html(c, token);

    if (c != EOF)
        ungetc(c, token->input_file);
    html_macro_end(token->output_file);
    return Success;
}


// Scan a preprocessor directive. The first character is the '#', which has already been read. 
//The directive name is taken as a sequence of letters, and the rest of the line is treated as plain text.
// Unknown directives are warned about.
 
Status preprocessor_scan(int ch, Files *token)
{
    int i = 0;
    int c;
    int j;
    int name_start;
    char name[TOKEN_SIZE + 1];

    token->tok[i++] = (char)ch;

    c = fgetc(token->input_file);

    while ((c == ' ' || c == '\t') && i < TOKEN_SIZE - 1)      /* "#  include" is legal */
    {
        token->tok[i++] = (char)c;
        c = fgetc(token->input_file);
    }

    name_start = i;

    while (c != EOF && isalpha(c) && i < TOKEN_SIZE - 1)
    {
        token->tok[i++] = (char)c;
        c = fgetc(token->input_file);
    }
    token->tok[i] = '\0';

    if (c != EOF)
        ungetc(c, token->input_file);

    if (name_start == i)                     /* a lone '#' (null directive) */
    {
        string_to_html(token->tok, token);
        return Success;
    }

    snprintf(name, sizeof name, "#%s", token->tok + name_start);

    for (j = 0; directives[j] != NULL; j++)
        if (strcmp(name, directives[j]) == 0)
            break;

    if (directives[j] == NULL)               /* unknown directive: plain text + warning */
    {
        string_to_html(token->tok, token);
        warn(token, "Unknown preprocessor directive");
        return Failure;
    }

    html_preprocessor_begin(token->output_file);
    string_to_html(token->tok, token);
    html_preprocessor_end(token->output_file);

    if (strcmp(name, "#include") == 0)
    {
        c = skip_blanks(token);

        if (c == '<' || c == '"')
            return header_scan(c, token);

        if (c != EOF)                        /* #include MACRO_NAME is legal C */
           
        ungetc(c, token->input_file);
    }
    else if (strcmp(name, "#define") == 0)
    {
        c = skip_blanks(token);

        if (isalpha(c) || c == '_')
            return macro_scan(c, token);

        if (c != EOF)
            ungetc(c, token->input_file);
    }

    return Success;
}