#include <stdio.h>
#include <string.h>

int main(void) {
    char text[100001] = "";
    char tmp[100001] = "";
    char c, ctmp;
    int i, j;

    while ((c = getchar()) != '\n') {
        if (c == '>'|| c == '<'){
            if (ctmp == '<'){
                i = 0;
                strcat(tmp,text);
                strcpy(text,tmp);
                tmp[0] = '\0';
            }
            else if (ctmp == '>'){
                i = 0;
                strcat(text,tmp);
                tmp[0] = '\0';
            }
            ctmp = c;
        }

        if (ctmp == '<' || ctmp == '>'){
            if (c != '<' && c != '>'){
                tmp[i++] = c;
                tmp[i] = '\0';
            }
        }
       else{
        text[j++] = c;
        text[j] = '\0';
       }
    }
    
    if (ctmp == '<'){
        strcat(tmp,text);
        strcpy(text,tmp);        
    }
    else {
        strcat(text,tmp);
    }
    
    printf("%s", text);
    return 0;
}