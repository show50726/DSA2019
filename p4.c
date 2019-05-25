#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define M 10000007
#define ll long long

char spells[500010];
ll _pow[500010];
ll hash_val[500010];
int record_pos[10010], a[6];

int cal(int p1, int p2){
    int v = 0;
    for(int i = p1+1; i <= p2; i++){
        v+=spells[i];
        v*=131;
        v%=M;
    }
    //printf("%d %d value: %d\n",p1, p2, v);
    //printf("cal: %d\n", (hash_val[p2]-_pow[p2-p1]*hash_val[p1]%M+M)%M);
    return v;
}


bool compare(int pf1, int pf2, int pb1, int pb2){
    /*
    printf("%s\n%s\n%d %d\n", s1, s2, m, n);
    for(int i = 0; i < m; i++){
        printf("%c", s1[i]);
    }
    puts("");
    for(int i = 0; i < n; i++){
        printf("%c", s2[i]);
    }
    puts("");
    */
    //printf("%d %d %d %d--\n", pf1, pf2, pb1, pb2);
    int m = pf2-pf1+1;
    int n = pb2-pb1+1;
    //printf("mn: %d %d\n", m, n);
    if(m==1&&n==1) return true;
    int f_mid = (int)floor((float)(pf1+pf2)/2);
    int b_mid = (int)floor((float)(pb1+pb2)/2);
    //printf("mid: %d %d\n", f_mid, b_mid);

    ll n1 = (pf1==0?hash_val[f_mid]:(hash_val[f_mid]%M-_pow[f_mid-pf1+1]*hash_val[pf1-1]%M+M)%M);    //  compute(s1, floor((float)m/2));
    ll n2 = (pb1==0?hash_val[b_mid]:(hash_val[b_mid]%M-_pow[b_mid-pb1+1]*hash_val[pb1-1]%M+M)%M);        //        compute(s2, floor((float)n/2));
    ll m1 = (hash_val[pf2]%M-_pow[pf2-f_mid]*hash_val[f_mid]%M+M)%M;                   //                compute(s1+(int)floor(m/2), ceil((float)m/2));
    ll m2 = (hash_val[pb2]%M-_pow[pb2-b_mid]*hash_val[b_mid]%M+M)%M;                  //              compute(s2+(int)floor(n/2), ceil((float)n/2));
    //if(n2%M!=cal(f_mid, pf2)%M) puts("ERROR");
    //printf("%d %d %d %d\n", n1, n2, m1, m2);

    if(n1!=n2&&m1!=m2){
        return false;
    }
    else{

        if(n1==n2&&m1==m2) return true;
        if(n1!=n2){
            return compare(pf1, f_mid, pb1, b_mid);
        }
        else if(m1!=m2){
            //printf("!!%d %d %d %d\n", f_mid+1, pf2, b_mid+1, pb2);
            return compare(f_mid+1, pf2, b_mid+1, pb2);

        }
    }
}

int main(){
    int n, q, now_pos = 0, cnt = 1;
    scanf("%d ", &n);
    _pow[0] = 1;
    for(int i = 1; i < 200010; i++){
        _pow[i] = _pow[i-1]*131%M;
    }
    
    
    for(int i = 0; i < n; i++){
        gets(spells+now_pos);
        record_pos[cnt++] = strlen(spells);
        //printf("%d\n", record_pos[cnt-1]);
        now_pos = record_pos[cnt-1];
    }
    int vvv = 0;
    for(int i = 0; i < now_pos; i++){
        vvv*=131;
        vvv+=spells[i];
        vvv%=M;
        hash_val[i] = vvv;
    }

    scanf("%d", &q);
    for(int i = 0; i < q; i++){
        for(int j = 0; j < 6; j++){
            scanf("%d", &a[j]);
        }
        if(compare(record_pos[a[0]]+a[1], record_pos[a[0]]+a[2], record_pos[a[3]]+a[4], record_pos[a[3]]+a[5])) puts("Y");
        else puts("N");
        //printf("%d %d %d %d\n", record_pos[a[0]]+a[1], record_pos[a[0]]+a[2], record_pos[a[3]]+a[4], record_pos[a[3]]+a[5]);

    }
    return 0;
}
/*
5
Sic vos non vobis...
Ari Ari Ari Ari Ari Arrivederci!
MUDAMUDAMUDAMUDAMUDAMUDA!
Ash nazg durbatuluk, ash nazg gimbatul
Ash nazg thrakatuluk, agh burzumishi krimpatul
5
3 0 10 4 0 10
*/
