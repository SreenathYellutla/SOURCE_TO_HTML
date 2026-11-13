#include "header.h"
Status validate_args(int argc,char *argv[]){
    if(argc!=3){
        fprintf(stderr,"not sufficient output");
    }
    if (argv[1] == NULL || argv[1][0] == '\0') 
        return Failure;

    // Reject filenames that start with a dot
    if (argv[1][0] == '.') 
        return Failure;

    // Check if the filename ends with ".c"
    char *ch = strstr(argv[1], ".c");
    if (ch == NULL || strcmp(ch, ".c") != 0) {
        printf("ERROR: File must be a valid .c file\n");
        return Failure;
    }

    if (argv[2] == NULL || argv[1][0] == '\0') 
        return Failure;

    // Reject filenames that start with a dot
    if (argv[2][0] == '.') 
        return Failure;

    // Check if the filename ends with ".c"
    char *ch1 = strstr(argv[2], ".html");
    if (ch1 == NULL || strcmp(ch1, ".html") != 0) {
        printf("ERROR: File must be a valid .html file\n");
        return Failure;
    }
    return Success;

}

Status open_files(Files *files,char *argv[])
{
    files->input_file = fopen(argv[1], "r");
    if (files->input_file == NULL)
    {
        perror(argv[1]);
        return Failure;
    }

    files->output_file = fopen(argv[2], "w");
    if (files->output_file == NULL)
    {
        perror(argv[2]);
        fclose(files->input_file);
        return Failure;
    }

    files->line = 1;
    files->first_on_line = 1;
    return Success;
}
