#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>

typedef struct Node{
    int size;
    int array[2010];
    struct Node *next;
    struct Node *pre;
}Node;
int K;

void _printall(Node *head){
    if(head==NULL) return;
    Node *tmp = head;
    while(tmp!=NULL){
        for(int i = 0; i < tmp->size; i++){
            printf("%c", tmp->array[i]);
        }
        puts("");
        tmp = tmp->next;
    }
}

Node *split(Node *tmp, int firstSize){
    if(tmp==NULL) return NULL;
    Node *now = (Node *)malloc(sizeof(Node));
    now->size = tmp->size-firstSize;
    for(int i = firstSize, j = 0; i < tmp->size && j < now->size; i++, j++){
        now->array[j] = tmp->array[i];
    }
    tmp->size = firstSize;
    if(tmp->next!=NULL){
        tmp->next->pre = now;
    }
    now->next = tmp->next;
    now->pre = tmp;
    tmp->next = now;
    return tmp;
}

Node *combine(Node *n1, Node *n2){
    for(int i = n1->size; i < n1->size+n2->size; i++){
        n1->array[i] = n2->array[i-n1->size];
    }
    n1->size = n1->size+n2->size;
    n1->next = n2->next;
    if(n2->next!=NULL){
        n2->next->pre = n1;
    }
    free(n2);
    return n1;
}

Node* insert(Node *head, int pos, char c){
    int nowIndex = 0;
    Node *tmp = head;
    if(tmp==NULL){
        head = (Node *)malloc(sizeof(Node));
        head->size = 1;
        head->array[0] = c;
        head->next = NULL;
        head->pre = NULL;
        //_printall(head);
        return head;
    }
    if(pos==0){
        Node *now = (Node *)malloc(sizeof(Node));
        now->size = 1;
        now->next = head;
        now->pre = NULL;
        head->pre = now;
        now->array[0] = c;
        if(now->next!=NULL){
            combine(now, now->next);
        }
        if(now->size>=2*K){
            now = split(now, now->size/2);
        }
        //_printall(now);
        return now;
    }
    while((nowIndex+tmp->size)<=pos){
        //puts("1");
        nowIndex+=tmp->size;
        //printf("Index: %d\n", nowIndex);
        if(nowIndex==pos||tmp->next==NULL) break;
        tmp = tmp->next;
    }
    if(nowIndex<pos){
        split(tmp, pos-nowIndex);
    }

    tmp->array[tmp->size] = c;
    (tmp->size)++;

    if((tmp->size)>=2*K){
        //printf("size: %d\n", tmp->size);
        tmp = split(tmp, tmp->size/2);
        tmp = tmp->next;
    }

    while(tmp!=NULL&&tmp->next!=NULL&&(tmp->size+tmp->next->size<=K)){
        combine(tmp, tmp->next);
        tmp = tmp->next;
    }

    //_printall(head);
    return head;
}

Node* del(Node *head, int pos){
    pos++;
    int nowIndex = 0;
    Node *tmp = head;

    while((nowIndex+tmp->size)<=pos){
        nowIndex+=tmp->size;
        if(nowIndex==pos||tmp->next==NULL) break;
        tmp = tmp->next;
    }
    //printf("ni: %d\n", nowIndex);
    if(nowIndex<pos){
        //printf("split\n");
        tmp = split(tmp, pos-nowIndex);
    }
    (tmp->size)--;
    //printf("del size: %d\n", tmp->size);
    if(tmp->size==0){
        if(pos==1){
            head = tmp->next;
            if(tmp->next!=NULL){
                tmp->next->pre = head;
            }
            free(tmp);
            //_printall(head);
            return head;
        }
        //printf("del: %c\n", tmp->array[0]);
        Node *delnode = tmp;
        if(tmp->pre!=NULL){
            tmp->pre->next = tmp->next;
        }
        free(delnode);
        //_printall(head);
        return head;
    }
    while(tmp!=NULL&&tmp->next!=NULL&&(tmp->size+tmp->next->size<=K)){
        combine(tmp, tmp->next);
        tmp = tmp->next;
    }
    //_printall(head);
    return head;
}

void print(Node *head, int l, int r){
    Node *tmp = head;
    int nowIndex = 0;
    while(tmp->next!=NULL&&((nowIndex+tmp->size)<=l)){
        nowIndex+=tmp->size;
        tmp = tmp->next;
    }

    int count = 0;
    if(nowIndex!=l) count = l-nowIndex;
    for(int i = 0; i < r-l; i++){
        //printf("%d\n", count);
        putchar(tmp->array[count]);
        count++;
        if(count==tmp->size&&tmp->next!=NULL){
            count = 0;
            tmp = tmp->next;
        }
    }
    puts("");
}



int main() {
    int n, k, x;
    char c;
    Node *head = NULL;
    scanf("%d", &n);
    K = sqrt(n);
    //printf("%d\n", K);
    for(int i = 1; i <= n; i++){
        scanf("%d%d ", &k, &x);
        //printf("%d\n", head==NULL?1:0);
        if(k==1){
            c = getchar();
            head = insert(head, x, c);
            //printf("%c\n", head->data);
        }
        else if(k==2){
            head = del(head, x);
        }
        else if(k==3){
            int l;
            scanf("%d", &l);
            print(head, x, l);
        }
    }
    return 0;
}
/*
20
1 0 D
3 0 1
1 0 G
1 1 G
1 1 K
1 2 T
1 3 H
*/

