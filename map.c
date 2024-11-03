#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char **table;
int **track;
// ‘#’ หมายถึง กําแพงของเขาวงกต
// ‘ ’ หมายถึง ช่องทางที่สามารถเดินผ่านได้
// ‘.’ หมายถึง ช่องทางที่เลือกเดินผ่าน
// ‘S’ หมายถึง จุดเริ่มต้น
// ‘G’ หมายถึง จุดหมายเพื่อออกจากเขาวงกตนั้น
void printTable(int n);
int traverseMaze(int row, int col, int size){

    if(row < 0 || row > size-1 || col < 0 || col > size-1){
        // printf("%d %d out of range\n", row, col);
        return 0;
    }
    if(track[row][col] == 1){
        // printf("%d %d same part\n",row, col);
        return 0;
    }
    
    char sign = table[row][col];
    // printf("%c ", sign);
    if(sign == '#') return 0;
    if(sign == 'G' || sign == '.'){
        // printf("found\n");
        return 1;
    }

    // printf("%d %d\n",row, col);
    track[row][col] = 1;
    int status = 0;
    int direct[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    for(int i = 0 ; i < 4 ; i++){
        int Nrow = row + direct[i][0], Ncol = col + direct[i][1];
        // printf("%d %d ", Nrow, Ncol);
        status = traverseMaze(Nrow, Ncol, size);
        if(status == 1 && sign != 'S'){
            table[row][col] = '.';
            return 1;
        }
    }
    return 0;
}

int main(){
    int n, st_col, st_row;
    scanf("%d", &n);
    getchar();

    table = (char **)malloc(sizeof(char *) * n);
    track = (int **)malloc(sizeof(int *) * n);
    for(int i = 0 ; i < n ; i ++){
        table[i] = (char *)calloc(n+1, sizeof(char));
        track[i] = (int *)calloc(n+1,sizeof(int));
        fgets(table[i], n+2, stdin);
    }   

    //find start locate
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j++){
            if(table[i][j] == 'S'){
                st_row = i, st_col = j;
                break;
            }
        }
    }
    // printf("%d %d", st_row, st_col);
    traverseMaze(st_row, st_col, n);
    // printf("What");
    printTable(n);

    return 0;
}


void printTable(int n){
    for(int i = 0 ; i < n ; i++){
        printf("%s",table[i]);
    }
}

/*
12
############
#   #      #
# # # #### #
### #    # G
#    ### # #
#### # # # #
#  # # # # #
## # # # # #
#        # #
###### ### #
#      #   #
###S########