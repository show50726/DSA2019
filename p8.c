#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>

int a[2000010];

void merge(int aa[], int head, int mid, int tail){
    int l1 = mid-head+1;
    int l2 = tail-mid;
    int x1[l1+1], x2[l2+1];

    for(int i = 0; i < l1; i++){
        x1[i] = aa[head+i];
    }
    x1[l1] = 1000000010;

    for(int j = 0; j < l2; j++){
        x2[j] = aa[mid+1+j];
    }
    x1[l2] = 1000000010;

    int i = 0, j = 0, k = head;
    while(i<l1||j<l2){
        if(x1[i]<x2[j]){
            aa[k] = x1[i];
            i++;
        }
        else{
            aa[k] = x2[j];
            j++;
        }
        k++;
    }

}

void mergesort(int aa[], int head, int tail){
    if(head<tail){
        int mid = (head+tail)/2;
        mergesort(aa, head, mid);
        mergesort(aa, mid+1, tail);
        merge(aa, head, mid, tail);
    }
}




int main(){
    int n, k, popnum = 0, cnt = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &k);
        if(k==0) scanf("%d", &a[cnt++]);
        else popnum++;
    }
    //puts("1");
    mergesort(a, 0, cnt-1);
    //puts("2");
    long long ans = 0;
    //for(int i = 0; i < cnt; i++) printf("%d\n", a[i]);
    for(int i = popnum; i < cnt; i++){
        ans+=a[i];
    }
    printf("%lld\n", ans);
    return 0;
}
