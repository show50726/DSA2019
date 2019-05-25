#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct TrieNode {
  struct TrieNode* c[26];
  bool isEndOfWord;
} Node;

Node * getNode(){
    Node *now = NULL;
    now = (Node *)malloc(sizeof(Node));

    now->isEndOfWord = false;

    if(now){
        for(int i = 0; i < 26; i++){
            now->c[i] = NULL;
        }
    }
    return now;
}

void insert(Node *root, char *key){
    int length = strlen(key);
    int index;
    Node *now = root;
    for(int i = 0; i < length; i++){
        index = key[i]-'a';
        if(!now->c[index]){
            now->c[index] = getNode();
        }

        now = now->c[index];
    }
    now->isEndOfWord = true;
}

bool search(Node *root, char *key){
    int length = strlen(key);
    int index;
    Node *now = root;

    for(int i = 0; i < length; i++){
        index = key[i]-'a';
        if(!now->c[index]) return false;
        now = now->c[index];
    }

    return (now!=NULL&&now->isEndOfWord);
}

int main() {
    int n, k;
    char ss[100];
    Node *root = getNode();
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%s", ss);
        insert(root, ss);
    }
    scanf("%d", &k);
    for(int i = 0; i < k; i++){
        scanf("%s", ss);
        printf("%s", search(root, ss)?"CHEESE!\n":"Ewwww.\n");
    }
    return 0;
}



