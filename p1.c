#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int aa[2000010];
int a1[2000010];
int top1 = -1;
int a2[2000010];
int top2 = -1;
int maxn[2000010];

void push(int *a, int *top, int num){
    (*top)++;
    a[*top] = num;
    return;
}

void pop(int *a, int *top){
    a[*top] = 0;
    (*top)--;
}

bool isempty(int a[1000010], int top){
    return top>=0?0:1;
}

int top(int a[1000010], int top){
    if(top==-1) return -1;
    return a[top];
}

int main() {
    int n,x;
    scanf("%d%d",&n,&x);
    for(int i = 0; i < n; i++){
        scanf("%d", aa+i);
    }
    maxn[n-1] = 0;
    for(int i = n-2; i >= 0; i--){
        if(aa[i+1]>maxn[i+1]){
            maxn[i] = aa[i+1];
        }
        else{
            maxn[i] = maxn[i+1];
        }
    }
    //for(int i = 0; i < n; i++) printf("%d ", maxn[i]);
    //puts("");
    for(int i = 0; i < n; i++){
        if(aa[i]<maxn[i]||(maxn[i]<=top(a1, top1))){
            if(aa[i]<maxn[i]){
                //printf("push: %d\n", aa[i]);
                while(top(a1, top1)>=maxn[i]){
                    push(a2, &top2, top(a1, top1));
                    pop(a1, &top1);
                }
                push(a1, &top1, aa[i]);
            }
            else if(maxn[i]<=top(a1, top1)){
                //printf("%d %d...\n", aa[i], top(a1, top1));
                while(top(a1, top1)>=aa[i]){
                    push(a2, &top2, top(a1, top1));
                    pop(a1, &top1);
                }
                push(a1, &top1, aa[i]);
            }
        }
        else{
            push(a2, &top2, aa[i]);
        }
        //for(int i = 0; i <= top1; i++) printf("%d ", a1[i]);
        //puts("");
        //for(int i = 0; i <= top2; i++) printf("%d%s", a2[i], i==top2?"\n":" ");
    }
    while(!isempty(a1, top1)){
        push(a2, &top2, top(a1, top1));
        pop(a1, &top1);
    }
    for(int i = 0; i <= top2; i++) printf("%d%s", a2[i], i==top2?"\n":" ");

    return 0;
}


/*
7 0
9 5 6 8 4 2 3
*/
/*
8 0
5 2 3 6 5 2 3 1
*/
