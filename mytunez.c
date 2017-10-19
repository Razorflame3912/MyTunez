#include <stdio.h>
#include <stdlib.h>
#include "LLstruct.h"
#include <time.h>
#include <string.h>

int main(){
    srand(time(NULL));
    struct node *head = NULL;

    printf("adding demons...\n");
    head = insert_order(head, "demons", "imagine dragons");
    print_list(head);
    printf("adding hello...\n");
    head = insert_order(head, "hello", "adele");
    print_list(head);
    printf("adding baby...\n");
    head = insert_order(head, "baby", "justin bieber");
    print_list(head);
    printf("adding radioactive...\n");
    head = insert_order(head, "radioactive", "imagine dragons");
    print_list(head);
    printf("adding never say never...\n");
    head = insert_order(head, "never say never", "justin bieber");
    print_list(head);
    printf("\n");

    printf("looking for hello...\n");
    print_list(find_name(head,"hello"));
    printf("looking for chandelier...\n");
    print_list(find_name(head,"chandelier"));
    printf("looking for imagine dragons...\n");
    print_list(find_artist(head,"imagine dragons"));
    printf("looking for maroon 5...\n");
    print_list(find_artist(head,"maroon 5"));
    printf("length of list is %d\n", list_len(head));
    printf("\n");

    printf("picking 10 random songs...\n");
    int n = 0;
    for(n; n < 10; n++){
        printf("%s\n",random_pick(head)->name);
    }
    printf("\n");

    head = free_list(head);
    printf("printing freed list...\n");
    print_list(head);
    printf("\n");

    printf("adding new songs...\n");
    head = insert_order(head, "unstoppable", "the score");
    head = insert_order(head, "legend", "the score");
    head = insert_order(head, "bohemian rhapsody", "queen");
    printf("new list: ");
    print_list(head);
    printf("removing legend and reprinting...\n");
    head = remove_node(head, find_name(head, "legend"));
    print_list(head);
    printf("removing unstoppable and reprinting...\n");
    head = remove_node(head, find_name(head, "unstoppable"));
    print_list(head);
    printf("removing bohemian rhapsody and reprinting...\n");
    head = remove_node(head, find_name(head, "bohemian rhapsody"));
    print_list(head);

    struct node * lib[27];
    lib[26] = 0;
    int i = 0;
    for(i;i<26;i++){
        lib[i] = NULL;
    }

    lib_add(lib,"demons","imagine dragons");
    //print_lib(lib);
    lib_add(lib,"radioactive","imagine dragons");
    lib_add(lib,"believer","imagine dragons");
    lib_add(lib,"demons","imagine dragons");
    lib_add(lib,"hello","adele");
    lib_add(lib,"best day of my life","american authors");
    lib_add(lib,"classic","mkto");
    lib_add(lib,"thank you","mkto");
    lib_add(lib,"baby","justin bieber");
    lib_add(lib,"never say never","justin bieber");
    lib_add(lib,"bailando","enrique iglesias");
    lib_add(lib,"centuries","fallout boy");
    lib_add(lib,"wavin' flag","k'naan");
    lib_add(lib,"a thousand miles","vanessa carlton");
    lib_add(lib,"thriller","michael jackson");
    lib_add(lib,"can't help falling in love with you","twenty one pilots");
    lib_add(lib,"the lazy song","bruno mars");
    lib_add(lib,"uptown funk","bruno mars");
    lib_add(lib,"just the way you are","bruno mars");
    lib_add(lib,"that's what i like","bruno mars");
    lib_add(lib,"marry you","bruno mars");
    lib_add(lib,"i want it that way","backstreet boys");
    lib_add(lib,"hotline bling","drake");
    lib_add(lib,"one call away","charlie puth");
    lib_add(lib,"never gonna give you up","rick astley");
    lib_add(lib,"mans not hot","big shaq");
    lib_add(lib,"don't wanna know","maroon 5");
    lib_add(lib,"timber","ke$ha");
    lib_add(lib,"despacito","luis fonsi");
    lib_add(lib,"home","phillip phillips");
    lib_add(lib,"for you","phillip phillips");
    lib_add(lib,"bohemian rhapsody","queen");
    lib_add(lib,"stitches","shawn mendes");
    lib_add(lib,"treat you better","shawn mendes");
    lib_add(lib,"something big","shawn mendes");
    lib_add(lib,"shake it off","taylor swift");
    
    print_lib(lib);
    print_list(lib_artist_pick(lib,"mkto"));
    print_artist_songs(lib,"justin bieber");

    print_shuffle(lib,10);
    print_letter(lib,'t');

    

    return 0;
}
