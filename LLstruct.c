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
        printf("%s by %s, ",tmp->name, tmp->artist);
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

int main(){
    srand(time(NULL));
    struct node *head = NULL;
    head = insert_order(head, "demons", "imagine dragons");
    print_list(head);
    head = insert_order(head, "hello", "adele");
    print_list(head);
    head = insert_order(head, "baby", "justin bieber");
    print_list(head);
    head = insert_order(head, "radioactive", "imagine dragons");
    print_list(head);
    head = insert_order(head, "never say never", "justin bieber");
    print_list(head);
    printf("looking for hello...\n");
    print_list(find_name(head,"hello"));
    printf("looking for chandelier...\n");
    print_list(find_name(head,"chandelier"));
    printf("looking for imagine dragons...\n");
    print_list(find_artist(head,"imagine dragons"));
    printf("looking for maroon 5...\n");
    print_list(find_artist(head,"maroon 5"));
    printf("length of list is %d\n", list_len(head));

    int n = 0;
    for(n; n < 10; n++){
        printf("%s\n",random_pick(head)->name);
    }
    head = free_list(head);
    //Test call of print_list to show free_list worked.
    printf("printing freed list...\n");
    print_list(head);

    head = insert_order(head, "unstoppable", "the score");
    head = insert_order(head, "legend", "the score");
    head = insert_order(head, "bohemian rhapsody", "queen");
    printf("new list: ");
    print_list(head);
    printf("removing legend...\n");
    head = remove_node(head, find_name(head, "legend"));
    print_list(head);
    printf("removing unstoppable...\n");
    head = remove_node(head, find_name(head, "unstoppable"));
    print_list(head);
    printf("removing bohemian rhapsody...\n");
    head = remove_node(head, find_name(head, "bohemian rhapsody"));
    print_list(head);
    return 0;
}
