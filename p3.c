#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Arvin.h"
#define ll long long


void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *tea, int *pan, int l, int r){
    int x = rand()% (r-l+1)+l;
    swap(&tea[x], &tea[r]);
    int now = tea[r], pivot;
    int record_tea[r+2];
    int record_pan[r+2];
    for(int i = l; i <= r; i++){
        record_pan[i] = query(pan[i], now);
        //printf("%d\n", record_pan[i]);
        if(record_pan[i]==0){
            swap(&pan[i], &pan[r]);
            pivot = r;
            record_pan[i] = query(pan[i], now);
        }
        //printf("%d ", record_pan[i]);
    }
    //printf("%d\n", pivot);

    for(int i = l; i <= r; i++){
        record_tea[i] = -1*query(pan[pivot], tea[i]);
        //printf("%d ", record_tea[i]);
    }
    //for(int i = 0; i < 5; i++) printf("%d ", tea[i]);
    int i = l-1;
    for(int j = l; j < r; j++){
        if(record_pan[j]==-1){
            i++;
            swap(&pan[i], &pan[j]);
        }
    }
    i++;
    swap(&pan[i], &pan[r]);

    int ii = l-1;
    for(int j = l; j < r; j++){
        if(record_tea[j]==-1){
            ii++;
            swap(&tea[ii], &tea[j]);
        }
    }
    ii++;
    swap(&tea[ii], &tea[r]);

    return i;
}

void quicksort(int *tea, int *pan, int l, int r){
    if(l<r){
        int pivot = partition(tea, pan, l, r);
        quicksort(tea, pan, l, pivot-1);
        quicksort(tea, pan, pivot+1, r);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int tea[n+5], pan[n+5];
    for(int i = 0; i < n; i++) scanf("%d", &pan[i]);
    for(int i = 0; i < n; i++) scanf("%d", &tea[i]);
    srand(5);
    quicksort(tea, pan, 0, n-1);

    for(int i = 0; i < n; i++){
        printf("%d %d\n", pan[i], tea[i]);
    }
    return 0;
}



