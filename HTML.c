#include "header.h"
#include "HTML.h"
#include "S_html.h"
#include "Keyword.h"

void html_begin(FILE *fp)
{
    fprintf(fp,
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
        "<meta charset=\"utf-8\">\n"
        "<title>Source2HTML</title>\n"
        "<style>\n"
        "body{\n"
        "background:black;\n"
        "color:white;\n"
        "font-family:monospace;\n"
        "font-size:16px;\n"
        "}\n"
        "pre{\n"
        "white-space:pre-wrap;\n"
        "tab-size:4;\n"
        "}\n"
        "</style>\n"
        "</head>\n"
        "<body>\n"
        "<pre>\n");
}

void html_end(FILE *fp)
{
    fprintf(fp, "</pre>\n"
                "</body>\n"
                "</html>\n");
}

// Convert a character to its HTML-safe representation and write it to the output file.
void char_to_html(int ch, Files *files)
{
    FILE *fp = files->output_file;
    
    if (ch == '<')
        fprintf(fp, "&lt;");

    else if (ch == '>')
        fprintf(fp, "&gt;");

    else if (ch == '&')
        fprintf(fp, "&amp;");

    else if (ch == '\n')
    {
        fputc('\n', fp);
        files->line++;
        files->first_on_line = 1;
        html_line_number(files);
        return;
    }
    else
        fputc(ch, fp);

    if (!isspace(ch))
        files->first_on_line = 0;
}

// Convert a string to its HTML-safe representation and write it to the output file.
void string_to_html(const char *str, Files *files)
{
    while (*str != '\0')
    {
        char_to_html((unsigned char)*str, files);
        str++;
    }
}

// Print the current line number in HTML format.
void html_line_number(Files *files)
{
    html_line_number_begin(files->output_file);
    fprintf(files->output_file, "%4d  ", files->line);
    html_line_number_end(files->output_file);
}


void html_line_number_begin(FILE *fp)
{
    fprintf(fp, "<span style=\"color:grey;\">");
}
void html_line_number_end(FILE *fp)
{
    fprintf(fp, "</span>");
}


void html_preprocessor_begin(FILE *fp)
{
    fprintf(fp, "<span style=\"color:violet;\">");
}
void html_preprocessor_end(FILE *fp)
{
    fprintf(fp, "</span>");
}


void html_header_begin(FILE *fp)
{
    fprintf(fp, "<span style=\"color:lightblue;\">");
}
void html_header_end(FILE *fp)
{
    fprintf(fp, "</span>");
}


void html_macro_begin(FILE *fp)
{
    fprintf(fp, "<span style=\"color:khaki;\">");
}
void html_macro_end(FILE *fp)
{
    fprintf(fp, "</span>");
}


void html_comment_begin(FILE *fp)
{
    fprintf(fp, "<span style=\"color:#6A9955;\">");
}
void html_comment_end(FILE *fp)
{
    fprintf(fp, "</span>");
}


void html_data_keyword_begin(FILE *fp)
{
    fprintf(fp, "<span style=\"color:#E06C75;\">");
}
void html_data_keyword_end(FILE *fp)
{
    fprintf(fp, "</span>");
}


void html_control_keyword_begin(FILE *fp)
{
    fprintf(fp, "<span style=\"color:violet;\">");
}
void html_control_keyword_end(FILE *fp)
{
    fprintf(fp, "</span>");
}



void html_number_begin(FILE *fp)
{
    fprintf(fp, "<span style=\"color:lightgreen;\">");
}
void html_number_end(FILE *fp)
{
    fprintf(fp, "</span>");
}


void html_string_begin(FILE *fp)
{
    fprintf(fp, "<span style=\"color:orange;\">");
}
void html_string_end(FILE *fp)
{
    fprintf(fp, "</span>");
}


void html_character_begin(FILE *fp)
{
    fprintf(fp, "<span style=\"color:orange;\">");
}
void html_character_end(FILE *fp)
{
    fprintf(fp, "</span>");
}