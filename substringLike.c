#include <stdio.h>
#include <stdlib.h>

int main()
{   
    int m, p, n, i, j, count = 0, point = 0;
    char *text, *word, *ans;

    scanf("%d %d %d", &m, &p, &n);

    int same = p-n;

    text = (char *)malloc(sizeof(char) * m+1);
    word = (char *)malloc(sizeof(char) * p+1);
    ans = (char *)malloc(sizeof(char) * 100);

    scanf("%s", text);
    scanf("%s", word);

    for (i = 0; i < m; i++){
        for (j = 0; j < p; j++){
            if (i > m - p){
                continue;
            }
            else if (text[i+j] == word[j]){
                count += 1;
            }
        }
        if (count >= same){
            ans[point] = '[';
            point += 1;
            for (j = 0; j < p; j++){
                if (text[i+j] == word[j]){
                    ans[point] = text[i+j];
                    point += 1;
                }
                else{
                    ans[point] = '?';
                    point += 1;
                }
            }
            ans[point] = ']';
            point += 1;
            i += p-1;
        }
        else{
            ans[point] = text[i];
            point += 1;
        }
        count = 0;
    }
    printf("%s\n", ans);
    free(text);
    free(ans);
    free(word);
    return 0;
}