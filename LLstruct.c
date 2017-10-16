#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {char name[256]; char artist[256]; struct node *next;};
struct node *HEAD = NULL;

void print_list(struct node *head){
  struct node *tmp = head;
  while(tmp){
    printf("%s by %s -> ",tmp->name, tmp->artist);
    tmp = tmp->next;
  }
  printf("\n");
}

struct node* insert_front(struct node *head, char *newname, char *newart){
  struct node *new_node = (struct node*)malloc(sizeof(struct node));
  strcpy(new_node->name,newname);
  strcpy(new_node->artist, newart);
  new_node->next = head;
  HEAD = new_node;
  return new_node;
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


int main(){
  int i = 8;
  insert_front(HEAD, "Demons", "Imagine Dragons");
  insert_front(HEAD, "Hello", "Adele");
  insert_front(HEAD, "Baby", "Justin Bieber");
  print_list(HEAD);
  print_list(find_name(HEAD,"Hello"));
  print_list(find_name(HEAD,"Chandelier"));
  print_list(find_artist(HEAD,"Imagine Dragons"));
  print_list(find_artist(HEAD,"Maroon 5"));
  free_list(HEAD);
  //Test call of print_list to show free_list worked.
  //print_list(HEAD);
  return 0;
}
