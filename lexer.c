#include "lexer.h"
const char *get_token_name(TokenType type){
        switch(type){
            case KEYWORD:
            return "KEYWORD";
            case IDENTIFIER:
            return "IDENTIFIER";
            case CONSTANT:
            return "CONSTANT";
            case OPERATOR:
            return "OPERATOR";
            case SPECIAL_SYMBOL:
            return "SPECIAL_SYMBOL";
            case STRING:
            return "STRING";
            case CHARACTER:
            return "CHARACTER";
            case PREPROCESSOR:
            return "PREPROCESSOR";
            case HEADER:
            return "HEADER";
            default:
            return "UNKNOWN";
    }
}
int is_keyword(const char *word){
    const char *keywords[]={
         "auto", "break", "case", "char", "const",
        "continue", "default", "do", "double", "else",
        "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return",
        "short", "signed", "sizeof", "static", "struct",
        "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
    };
    int count=sizeof(keywords)/sizeof(keywords[0]);
    for(int i=0;i<count;i++){
        if(strcmp(word,keywords[i])==0){
            return 1;
        }
    }
    return 0;
}
void analyze_file(FILE *fp){
    int ch;
    char word[MAX_LEXEME];
    int index;
    while((ch=fgetc(fp))!=EOF){
        if(isspace(ch)){
            continue;
        }
         if(ch=='#')
        {
            char directive[MAX_LEXEME];
            int i=0;
            directive[i++]=ch;
            ch=fgetc(fp);
            while(isalpha(ch))
            {
                if(i<MAX_LEXEME-1)
                {
                    directive[i++]=ch;
                }
                ch=fgetc(fp);
            }
            directive[i]='\0';
            printf("%s:%s\n","PREPROCESSOR",directive);
            if(ch!=EOF)
            {
                ungetc(ch,fp);
            }
            continue;
        }
        if(ch=='<')
        {
            index=0;
            word[index++]=ch;
            ch=fgetc(fp);
            while(ch!=EOF && ch!='>')
            {
                if(index<MAX_LEXEME-2)
                {
                    word[index++]=ch;
                }
                ch=fgetc(fp);
            }
            if(ch=='>')
            {
                word[index++]=ch;
                word[index]='\0';
                printf("%s:%s\n","HEADER",word);
            }
            continue;
        }
        if(isalpha(ch)||ch=='_'){
            index=0;
            while(isalnum(ch)||ch=='_'){
                if(index<MAX_LEXEME-1){
                   word[index++]=ch;
                }
                ch=fgetc(fp);
            }
            word[index]='\0';
            if(is_keyword(word)){
                printf("%s:%s\n","KEYWORD",word);
            }
            else{
                printf("%s:%s\n","IDENTIFIER",word);
            }
            if(ch!=EOF){
                ungetc(ch,fp);
            }
        }
    else if(isdigit(ch)){
        index=0;
        while(isdigit(ch)){
            if(index<MAX_LEXEME-1){
                word[index++]=ch;
            }
            ch=fgetc(fp);
        }
        word[index]='\0';
        printf("%s:%s\n","CONSTANT",word);
        if(ch!=EOF){
            ungetc(ch,fp);
        }
    }
    else if(ch=='+' || ch=='-' || ch=='*' ||
    ch=='/' || ch=='%' || ch=='=' ||
    ch=='<' || ch=='>' || ch=='!')
{
    int next=fgetc(fp);

    if ((ch=='=' && next=='=') ||
        (ch=='+' && next=='+') ||
        (ch=='-' && next=='-') ||
        (ch=='<' && next=='=') ||
        (ch=='>' && next=='='))
    {
       printf("%s:%c%c\n","OPERATOR",ch,next);
    }
    else
    {
        printf("%s:%c\n","OPERATOR",ch);
        if(ch!=EOF)
        {
            ungetc(next,fp);
        }
    }
}

else if (ch==';' || ch==',' ||
    ch=='(' || ch==')' ||
    ch=='{' || ch=='}' ||
    ch=='[' || ch==']')
{
    printf("%s:%c\n","SPECIAL_SYMBOL",ch);
}

else{
    printf("%s:%c\n","UNKNOWN",ch);
}
    }
}