#include "lexer.h"

int main()
{
    FILE *fp;
    fp=fopen("input.c","r");
    if(fp==NULL){
        printf("ERROR:Unable to open input.c\n");
        return 1;
    }
    analyze_file(fp);
    fclose(fp);
    return 0;
}