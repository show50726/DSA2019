//dicussed with B07902122
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#define ll long long
#define M2 10000000009
#define M1 10000020133
#define MAXN 20000003
#define M 20000003
//50000017
typedef struct node{
    char name[101];
    int parent;
    int myindex;
    char parent_name[101];
    int order;
    struct hotpot* thishp;
    struct node *next;
}node;

typedef struct hotpot{
	int name;
	char m_name[101];
	int hash1, hash2;
	struct hotpot *next;
	struct hotpot* prev;
}hotpot;


node *hash_table[MAXN];
hotpot *hp[MAXN];
long long alpha_mapping[256] = {0};
long long beta_mapping[256] = {0};
int existM[MAXN] = {0};
int existHP[MAXN] = {0};

void preprocess_a(){
    alpha_mapping[0] = 1;
    for(int i=1;i<256;i++){
        alpha_mapping[i] = (alpha_mapping[i-1] * 1213) % M2;
    }
}
unsigned int JSHash(char *str){
    unsigned int hash = 1315423911;
    while (*str)
        hash ^= ((hash << 5) + (alpha_mapping[*str++]) + (hash >> 2));
    return (hash & 0x7FFFFFFF);
}

void preprocess_b(){
    beta_mapping[0] = 1;
    for(int i=1;i<256;i++){
        beta_mapping[i] = (beta_mapping[i-1] * 131) % M1;
    }
}

int cal_hash1(char s[], int l){
    ll v = 0;
    for(int i = 0; i < l; i++){
        v*=10427;
        v%=M1;
        v+=alpha_mapping[s[i]];
        v%=M1;
    }
    v%=M;
    v+=JSHash(s);
    v%=M;
    if(v<0) v+=M;
    return (int)v;
}



int cal_hash2(char s[], int l){
    ll v = 0;
    for(int i = 0; i < l; i++){
        v*=2441;
        v%=M2;
        v+=beta_mapping[s[i]];
        v%=M2;
    }
    v%=M;
    //v+=JSHash(s);
    //v%=M;
    if(v<0) v+=M;
    return (int)v;
}

node *find_name(char s[]){
    int v = cal_hash1(s, strlen(s))%M;
    node *now = hash_table[v];
    while(strcmp(now->name, s)!=0&&now->next!=NULL){
        now = now->next;
    }
    return now;
}

void add(hotpot *now, int hash1, int hash2, node *member, int o, int a1){
    now->name = a1;
    now->hash1 = hash1;
    now->hash2 = hash2;
    now->next = NULL;
    //now->prev = NULL;
    strcpy(now->m_name, member->name);
    member->myindex = a1;
    member->parent = a1;
    member->thishp = now;
    member->order = o;
    member->next = NULL;
    return ;
}

node* find_set(char name[]){
    node *now = find_name(name);
    int p = now->parent;
    //printf("%d %d\n", p, a);
    if(p!=now->myindex){
        //    puts("?");
        node *f = find_set(now->parent_name);
        now->parent = f->parent;
        memset(now->parent_name, 0, sizeof(now->parent_name));
        strcpy(now->parent_name, f->parent_name);
        now = f;

    }
    return now;
}


void check(int x, hotpot *now){
    hotpot *tmp = hp[x%M];

    if(now->hash2==tmp->hash2&&tmp!=now){
        check_merge(tmp, now);
    }
    else{
        while(tmp->next!=NULL){
            tmp = tmp->next;
            if(now->hash2==tmp->hash2&&tmp!=now){
                check_merge(tmp, now);
                break;
            }
        }
    }
    return;
}

void union_set(node* set1, node* set2){
    int p, k;
    //printf("%d %d\n", member_order[set1], member_order[set2]);
    if(set1->order<set2->order){
        set2->parent = set1->myindex;
        memset(set2->parent_name, 0, sizeof(set2->parent_name));
        strcpy(set2->parent_name, set1->name);
        p = set1->myindex;
        k = 1;
    }
    else{
        set1->parent = set2->myindex;
        memset(set1->parent_name, 0, sizeof(set1->parent_name));
        strcpy(set1->parent_name, set2->name);
        p = set2->myindex;
        k = 2;
    }
    hotpot *now;
    hotpot *h1 = set1->thishp;
    hotpot *h2 = set2->thishp;
    int newhp1 = ((h1->hash1+h2->hash1)%M);
    int newhp2 = ((h1->hash2+h2->hash2)%M);
    if(existHP[newhp1]==0){
        //puts("new!");
        existHP[newhp1]++;
        hp[newhp1] = (hotpot *)malloc(sizeof(hotpot));
        now = hp[newhp1];

        now->name = p;
        now->hash1 = newhp1;
        now->hash2 = newhp2;
        now->next = NULL;
        now->prev = NULL;
        if(k==1)
            strcpy(now->m_name, set1->name);
        else strcpy(now->m_name, set2->name);

        set1->thishp = now;
        set2->thishp = now;
        //link the pre and next
        if(h1->prev!=NULL){
            h1->prev->next = h1->next;
            if(h1->next!=NULL){
                h1->next->prev = h1->prev;
            }
        }
        else if(h1->next!=NULL){
            h1->next->prev = NULL;
            hp[h1->hash1%M] = h1->next;
        }





        if(h2->prev!=NULL){
            h2->prev->next = h2->next;
            if(h2->next!=NULL){
                h2->next->prev = h2->prev;
            }
        }
        else if(h2->next!=NULL){
            h2->next->prev = NULL;
            hp[h2->hash1%M] = h2->next;
        }



        existHP[h1->hash1]--;
        existHP[h2->hash1]--;
        free(h1);
        free(h2);
    }
    else{
    	existHP[newhp1]++;
        now = hp[newhp1];
        while(now->next!=NULL){
            now = now->next;
        }
        now->next = (hotpot *)malloc(sizeof(hotpot));
        now->next->prev = now;
        now = now->next;

        now->name = p;
        now->hash1 = newhp1;
        now->hash2 = newhp2;
        now->next = NULL;
        if(k==1)
            strcpy(now->m_name, set1->name);
        else strcpy(now->m_name, set2->name);

        set1->thishp = now;
        set2->thishp = now;
        //connect
        if(h1->prev!=NULL){
            h1->prev->next = h1->next;
            if(h1->next!=NULL){
                h1->next->prev = h1->prev;
            }
        }
        else if(h1->next!=NULL){
            h1->next->prev = NULL;
            hp[h1->hash1%M] = h1->next;
        }




        if(h2->prev!=NULL){
            h2->prev->next = h2->next;
            if(h2->next!=NULL){
                h2->next->prev = h2->prev;
            }
        }
        else if(h2->next!=NULL){
            h2->next->prev = NULL;
            hp[h2->hash1%M] = h2->next;
        }



        existHP[h1->hash1]--;
        existHP[h2->hash1]--;
        free(h1);
        free(h2);
        check(newhp1, now);
    }
}



void merge(node *n1, node *n2){
    node *k1 = find_set(n1->name);
    node *k2 = find_set(n2->name);
    union_set(k1, k2);
    return;
}

void check_merge(hotpot *hp1, hotpot *hp2){
    node* set1 = find_set(hp1->m_name);
    node* set2 = find_set(hp2->m_name);
    if(set1->order<set2->order){
        printf("%s %s\n", set1->name, set2->name);
    }
    else{
        printf("%s %s\n", set2->name, set1->name);
    }
    merge(set1, set2);
}




int main(){
    memset(hash_table, 0, sizeof(hash_table));
    memset(hp, 0, sizeof(hp));
    int n, num, order_cnt = 1;
    char command[10];
    char name1[110], name2[110];

    preprocess_a();
    preprocess_b();

    scanf("%d", &n);
    for(int i = 0; i < n; i++){

        scanf("%s", &command);
        if(strcmp("New", command)==0){
            scanf("%s", &name1);

            //printf("%s\n", name1);

            int namehash = cal_hash1(name1, strlen(name1))%M;

            node *newnode;
            if(existM[namehash]!=0){
                existM[namehash]++;
                newnode = hash_table[namehash];
                while(newnode->next!=NULL){
                    newnode = newnode->next;
                }
                newnode->next = (node *)malloc(sizeof(node));
                newnode = newnode->next;
            }
            else{
                existM[namehash]++;
                newnode = (node *)malloc(sizeof(node));
                hash_table[namehash%M] = newnode;
            }
            //printf("%d\n", namehash);
            strcpy(newnode->name, name1);
            strcpy(newnode->parent_name, name1);
            //printf("%s %d\n", pos->name, pos->order);

            scanf("%d", &num);

            //printf("%d\n", num);
            ll v1 = 0, v2 = 0;
            for(int k = 0; k < num; k++){
                scanf("%s", &name2);

                //printf("%s\n", name2);

                v1 += cal_hash1(name2, strlen(name2));
                v1%=M;
                v2 += cal_hash2(name2, strlen(name2));
                v2%=M;
            }

            //printf("aa: %lld %lld\n", pos->hotpotVal1, pos->hotpotVal2);

            if(existHP[(int)v1]==0){
                existHP[(int)v1]++;
                //puts("123");
                hp[(int)v1%M] = (hotpot *)malloc(sizeof(hotpot));
                add(hp[(int)v1%M], (int)v1, (int)v2, newnode, i+1, namehash);
                hp[(int)v1%M]->prev = NULL;
            }
            else{
                existHP[(int)v1]++;
                hotpot *now = hp[(int)v1%M];
                while(now->next!=NULL){
                    now = now->next;
                }
                now->next = (hotpot *)malloc(sizeof(hotpot));
                now->next->prev = now;
                now = now->next;
                add(now, (int)v1, (int)v2, newnode, i+1, namehash);
                check((int)v1, now);
            }

        }
        else if(strcmp("Merge", command)==0){
            scanf("%s %s", &name1, &name2);
            node *n1 = find_name(name1);
            node *n2 = find_name(name2);
            merge(n1, n2);
        }
    }
    return 0;
}

/*
9
New Qmao 1 A
New Howard 1 B
New Mama 2 A B
New Arvin 4 A A B B
New Piepie 2 C C
New Yanger 1 D
Merge Qmao Howard
Merge Mama Yanger
New K 9 A A A A B B B B D
*/
