#include <stdio.h>
#include <stdlib.h>

struct Player{
    int index;
    int drink_limit,drink;
    struct Player *prev,*next;
};

typedef struct Player Player;

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    Player *players[n];
    for(int i=0;i<n;i++){
        players[i] = (Player*)malloc(sizeof(Player));
        players[i]->index = i+1;
        players[i]->drink = 0;
        scanf("%d", &players[i]->drink_limit);
    }
    for(int i=0;i<n;i++){
        players[i]->prev = players[(i-1+n)%n];
        players[i]->next = players[(i+1)%n];
    }
    Player *current = players[0];
    int total_player = n;
    int current_count = 0;
    while(total_player > 1){
        current_count++;
        if(current_count % k == 0){
            current->drink++;
            if(current->drink > current->drink_limit){
                Player *temp = current;
                current->prev->next = current->next;
                current->next->prev = current->prev;
                free(temp);
                total_player--;
            }
        }
        current = current->next;
    }
    printf("%d\n", current->index);
}