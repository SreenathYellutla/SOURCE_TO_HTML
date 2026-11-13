#ifndef HTML_H
#define HTML_H

#include "header.h"

void html_begin(FILE *fp);
void html_end(FILE *fp);

// Functions to convert characters and strings to HTML-safe representations
void char_to_html(int ch, Files *files);
void string_to_html(const char *str, Files *files);
void html_line_number(Files *files);

/* One begin/end pair per token type */
void html_line_number_begin(FILE *fp);
void html_line_number_end(FILE *fp);

void html_preprocessor_begin(FILE *fp);
void html_preprocessor_end(FILE *fp);

void html_header_begin(FILE *fp);
void html_header_end(FILE *fp);

void html_macro_begin(FILE *fp);
void html_macro_end(FILE *fp);

void html_comment_begin(FILE *fp);
void html_comment_end(FILE *fp);

void html_data_keyword_begin(FILE *fp);
void html_data_keyword_end(FILE *fp);

void html_control_keyword_begin(FILE *fp);
void html_control_keyword_end(FILE *fp);

void html_number_begin(FILE *fp);
void html_number_end(FILE *fp);

void html_string_begin(FILE *fp);
void html_string_end(FILE *fp);

void html_character_begin(FILE *fp);
void html_character_end(FILE *fp);

#endif