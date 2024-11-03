#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int **table;
int direc[8][2] = {{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};

int moving(int x, int y, int cnt, int N, int M, int cmd);
int bounding(int x, int y, int cnt, int N, int M, int cmd){
    int nx, ny;
    if(cmd == 1 || cmd == 3 || cmd == 5 || cmd == 7){
        if(cmd == 1) cmd = 7;
        else cmd -= 2;
        for(int i = cmd ; ; i+=2){
            i%=8;
            nx = x + direc[i][1];
            ny = y + direc[i][0];
            if(ny < 0 || ny>= M || nx < 0 || nx >= N) continue;
            if(nx != x || ny != y){
                return moving(nx, ny, cnt, N, M , i);
            }
        }
    }
}
int moving(int x, int y, int cnt, int N, int M, int cmd){
    
    table[x][y] += 1;
    if(table[x][y] > 3) return 0;
    for(int i = 0 ; i < 8 ; i++){
        if(cmd != i) continue;
        if(y+direc[i][0] < 0 || y+direc[i][0] >= M || x+direc[i][1] < 0 || x+direc[i][1] >= N) return bounding(x,y,cnt,N,M,cmd);
        return moving(x+direc[i][1], y+direc[i][0], cnt, N, M, cmd);
    }
    
    return 0;
}

int main(){
    
    int N,M,x,y,direc;
    
    scanf("%d %d %d %d %d", &N, &M, &x, &y, &direc);
    if(direc == 0 || direc == 4){
        printf("%d", N);
        return 0;
    }
    if(direc == 2 || direc == 6){
        printf("%d", M);
        return 0;
    }
    if(N == 1 || M == 1 ){
        if(direc%2 == 1){
            printf("1");
            return 0;
        }
    }

    table = (int **)malloc(sizeof(int *) * N);

    for(int i = 0 ; i < N; i++){
        table[i] = (int *)malloc(sizeof(int) * M);
    }
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < M ; j++) table[i][j] = 0;
    }

    int cnt = 0;
    cnt = moving(x,y,0,N,M,direc);
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < M ; j++){
            if(table[i][j] != 0) cnt += 1;
        }
    }
    

    printf("%d", cnt);

    for(int i = 0 ; i < M ; i++){
        free(table[i]);
    }
    free(table);

    return 0;
}