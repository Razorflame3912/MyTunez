#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct node {
    char name[256]; 
    char artist[256]; 
    struct node *next;
};

void to_lowercase(char str[]) {
    int i = 0;
    while (str[i]) {
        str[i] = (char)tolower(str[i]);
        i++;
    }
}


void print_list(struct node *head){
    struct node *tmp = head;
    while(tmp){
        printf("%s by %s, ",tmp->name,tmp->artist);
        tmp = tmp->next;
    }
    printf("\n");
}

struct node* insert_front(struct node head[], char newname[], char newart[]){
    char name[256];
    strcpy(name, newname);
    char art[256];
    strcpy(art, newart);
    to_lowercase(name);
    to_lowercase(art);
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    strcpy(new_node->name, name);
    strcpy(new_node->artist, art);
    new_node->next = head;
    return new_node;
}

/*
   struct node* insert_order(struct node head[], char newname[], char newart[]) {
//printf("adding %s\n", newname);
char name[256];
strcpy(name, newname);
char art[256];
strcpy(art, newart);
to_lowercase(name);
to_lowercase(art);
if (!head || strcmp(art, head->artist) <= 0) {
return insert_front(head, name, art);
} else if (head->next && strcmp(art, head->next->artist) <= 0) {
//printf("adding next...\n");
struct node *new_node = (struct node*) malloc(sizeof(struct node));
new_node->next = head->next;
strcpy(new_node->name, name);
strcpy(new_node->artist, art);
head->next = new_node;
return head;
} else if (!head->next) {
//printf("adding to end\n");
struct node *new_node = (struct node*) malloc(sizeof(struct node));
strcpy(new_node->name, name);
strcpy(new_node->artist, art);
head->next = new_node;
} else {
//printf("adding later..\n");
insert_order(head->next, name, art);
return head;
}
}
*/

int list_len(struct node *head){
    int i = 0;
    while(head){
        head = head->next;
        i++;
    }
    return i;
}

struct node* free_list(struct node *head){
    while(head){
        struct node *tmp = head;
        head = head -> next;
        free(tmp);
    }
    return NULL;
}

struct node* find_name(struct node *head, char* s){
    struct node* tmp = head;
    while(tmp){
        if(strcmp(tmp->name,s) == 0){
            return tmp;
        }
        tmp = tmp->next;
    }
    return tmp;
}

struct node* find_artist(struct node *head, char* s){
    struct node* tmp = head;
    while(tmp){
        if(strcmp(tmp->artist,s) == 0){
            return tmp;
        }
        tmp = tmp->next;
    }
    return tmp;
}

struct node* random_pick(struct node *head){
    int r = rand();
    //printf("%d\n",r);
    //printf("%d\n",RAND_MAX);
    int len = list_len(head);
    //printf("%d\n",len);
    int i = 1;
    for(i;i<len;i++){
        //printf("%d\n",i);
        if(r< (RAND_MAX/len) * i){
            r=(i-1);
            //printf("%d\n",r);
            break;
        }
    }
    if (r > len-1){
        r=len-1;
    }
    for(r;r>0;r--){
        head = head->next;
    }
    return head;
}

struct node* insert_order(struct node head[], char newname[], char newart[]){
    char name[256];
    strcpy(name, newname);
    char art[256];
    strcpy(art, newart);
    to_lowercase(name);
    to_lowercase(art);
    struct node *tmp = head;

    if(!tmp){
        return insert_front(head,name,art);
    }
    struct node *follow = NULL;
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    strcpy(new_node->name, name);
    strcpy(new_node->artist, art);  
    while(tmp){
        if(strcmp(new_node->artist,tmp->artist) > 0){
        } else if(strcmp(new_node->artist,tmp->artist) < 0){
            new_node->next = tmp;
            if(follow){
                follow->next = new_node;
            }
            else{
                head = new_node;
            }
            return head;
        } else{
            if(strcmp(new_node->name,tmp->name) > 0){
            }
            else if(strcmp(new_node->name,tmp->name) <= 0){
                new_node->next = tmp;
                if(follow){
                    follow->next = new_node;
                }
                else{
                    head = new_node;
                }
                return head;
            }
        }

        follow = tmp;
        tmp = tmp->next;
        //printf("%s\n",follow->artist);
        if(tmp){
            //printf("%s\n---\n",tmp->artist);
        }
    }
    follow->next = new_node;
    new_node->next = NULL;
    return head;
}

struct node* remove_node(struct node *head, struct node *to_remove) {
    if (head == to_remove) {
        free(to_remove);
        return NULL;
    } else if (head->next == to_remove) {
        struct node* tmp = head->next;
        head->next = tmp->next;
        free(tmp);
        return head;
    } else {
        remove_node(head->next, to_remove);
        return head;
    }
}

struct node* lib_add(struct node *arr[27],char *newname, char *newart){
    int i = 0;
    struct node* *tmp = arr;
    for(i;i<27;i++){
        if (newart[0] - (97 + i) == 0){
            tmp[i] = insert_order(tmp[i], newname, newart);
            return tmp[i];
        }
    }
    return NULL;
}

struct node* lib_artist_pick(struct node *arr[27],char *artistname){
    int i = 0;
    for(i;i<27;i++){
        if(artistname[0] - (97+ i) == 0){
            return find_artist(arr[i],artistname);
        }
    }
    return NULL;
}

void print_artist_songs(struct node *arr[27], char *artistname){
    struct node *start = lib_artist_pick(arr,artistname);
    while(start && strcmp(artistname,start->artist) == 0){
        printf("%s by %s, ",start->name,start->artist);
        start = start->next;
    }
    printf("\n");
}

void print_lib(struct node *arr[27]){
    int i = 0;
    for(i;i<26;i++){
        if (arr[i]) {
            printf("%c songs:\n\t",97 + i);
            print_list(arr[i]);
        }
    }
}

struct node *random_lib(struct node *arr[27]){
    int r = rand();
    int i = 1;
    int choose = 0;
    int j = 0;
    for(j;j<27;j++){
        if(arr[j]){
            choose++;
        }
    }

    j=0;
    while(i < 27){
        if(r < (RAND_MAX/choose)*j){
            if(arr[i]){
                return random_pick(arr[i]);
            }
        }
        else{
            j++;
        }
        i++;
    }
    return NULL;
}

void print_shuffle(struct node * arr[27], int i){
    for(i;i>0;i--){
        struct node * pick = random_lib(arr);
        printf("%s by %s\n",pick->name,pick->artist);
    }
}

void print_letter(struct node * arr[27], char c){
    printf("%c songs:\n\t",c);
    print_list(arr[c-97]);
}

struct node *search_song(struct node * arr[27], char  *n, char *a){
    return find_name(lib_artist_pick(arr,a),n);
}

void delete_song(struct node *arr[27], char *n, char *a) {
    arr[a[0] - 97] = remove_node(arr[a[0] - 97], search_song(arr, n, a));
}

void delete_all_songs(struct node *arr[27]) {
    int i;
    for (i = 0; i < 27; i++) {
        free_list(arr[i]);
        arr[i] = NULL;
    }
}
