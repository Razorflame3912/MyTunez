#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct node {
    char name[256]; 
    char artist[256]; 
    struct node *next;
};

struct node *HEAD = NULL;

void print_list(struct node *head){
  struct node *tmp = head;
  while(tmp){
    printf("%s by %s, ",tmp->name, tmp->artist);
    tmp = tmp->next;
  }
  printf("\n\n");
}


struct node* insert_front(struct node *head, char *newname, char *newart){
  struct node *new_node = (struct node*)malloc(sizeof(struct node));
  strcpy(new_node->name,newname);
  strcpy(new_node->artist, newart);
  new_node->next = head;
  HEAD = new_node;
  return new_node;
}

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

struct node* insert_order(struct node *head, char *newname, char *newart ){
  if(!head){
    return insert_front(head,newname,newart);
  }
  struct node *follow = NULL;
  struct node *new_node = (struct node*)malloc(sizeof(struct node));
  strcpy(new_node->name,newname);
  strcpy(new_node->artist, newart);  
  while(head){
    if(strcmp(new_node->artist,head->artist) > 0){

    }
    else if(strcmp(new_node->artist,head->artist) < 0){
      new_node->next = head;
      if(follow){
	follow->next = new_node;
      }
      else{
	HEAD = new_node;
      }
      return new_node;
    }
    
    else{
      if(strcmp(new_node->name,head->name) > 0){

      }
      
      else if(strcmp(new_node->name,head->name) <= 0){

	new_node->next = head;
	if(follow){
	  follow->next = new_node;
	}
	else{
	  HEAD = new_node;
	}
	return new_node;
      }

    }

    follow = head;
    head = head->next;
    //printf("%s\n",follow->artist);
    if(head){
      //printf("%s\n---\n",head->artist);
    }
      

  }
  follow->next = new_node;
  new_node->next = NULL;
  return new_node;

}


int main(){
  srand(time(NULL));
  insert_order(HEAD, "Demons", "Imagine Dragons");
  print_list(HEAD);
  insert_order(HEAD, "Hello", "Adele");
  print_list(HEAD);
  insert_order(HEAD, "Baby", "Justin Bieber");
  print_list(HEAD);
  insert_order(HEAD, "Radioactive", "Imagine Dragons");
  print_list(HEAD);
  printf("Looking for Hello...\n");
  print_list(find_name(HEAD,"Hello"));
  printf("Looking for Chandelier...\n");
  print_list(find_name(HEAD,"Chandelier"));
  printf("Looking for Imagine Dragons...\n");
  print_list(find_artist(HEAD,"Imagine Dragons"));
  printf("Looking for Maroon 5...\n");
  print_list(find_artist(HEAD,"Maroon 5"));
  printf("Length of list is %d\n", list_len(HEAD));

  int n = 0;
  for(n;n<10;n++){
    printf("%s\n",random_pick(HEAD)->name);
  }
  HEAD = free_list(HEAD);
  //Test call of print_list to show free_list worked.
  printf("Printing freed list...\n");
  print_list(HEAD);
  return 0;
}
