#include "header.h"
#include "S_html.h"
#include "HTML.h"
#include "Keyword.h"
int main(int argc,char* argv[]){

    Files file;

    if(validate_args(argc,argv)==Failure){
        return 1;
    }

    if(open_files(&file,argv)==Failure){
        return 1;
    }
    
    Status result = source_to_html(&file);
 
    fclose(file.input_file);
    fclose(file.output_file);
 
    if (result == Failure)
    {
        fprintf(stderr, "Conversion failed\n");
        return 1;
    }
 
    printf("HTML Generated Successfully\n");
    return 0;

}
