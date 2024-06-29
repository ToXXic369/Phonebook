#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 12

typedef struct node {
  char name[MAX];
  char number[MAX];
  struct node *next;
} node;

void add_contact(node **head);
void free_all(node **head);
void remove_contact(node **head);
void display_all(node *head);
node* search_contact(node *head,char choice[]);

int main(void) {
  node *head = NULL;
  char choice[MAX];

  printf("1.To add a contact.\n");
  printf("2.To remove a contact.\n");
  printf("3.To display all contacts.\n");
  printf("4.To search a contact.\n");
  printf("5.To exit.\n");

  int num;

  do {
    printf("Number>> ");
    scanf("%d",&num);
    getchar();

    switch (num) {
      case 1:
        add_contact(&head);
        break;
      case 2:
        remove_contact(&head);
        break;
      case 3:
        display_all(head);
        break;
      case 4:
        printf("enter name, ");
        fgets(choice,MAX,stdin);
        choice[strcspn(choice,"\n")] = '\0';

        node *result;
        result=search_contact(head,choice);
        if(result != NULL) {
          printf("Number: %s\n",result->number);
        } else {
          printf("contact not found.\n");
        }
        
        break;
      case 5:
        free_all(&head);
        exit(0);
      default:
        printf("enter a valid number.\n");
    }
  } while (1);
}


void add_contact(node **head) {
  node *new = (node *)malloc(sizeof(node));
  if (new == NULL) {
    printf("error allocating memory.\n");
    return;
  }
  
  printf("name: ");
  fgets(new->name,MAX,stdin);
  new->name[strcspn(new->name,"\n")]='\0';
  
  printf("number: ");
  fgets(new->number,MAX,stdin);
  new->number[strcspn(new->number,"\n")]='\0';

  new->next = *head;
  *head = new;
  printf("added succesfully :)\n");
}
  
void free_all(node **head) {
  if (*head == NULL) {
    printf("nothing to display.\n");
    return;
  }

  node *chad = *head;
  while (chad != NULL) {
    chad = chad->next;
    free(*head);
    *head = chad;
  }

}

void remove_contact(node **head) {
  if (*head == NULL) {
    printf("nothing to delete.\n");
    return;
  }
  
  char choice[MAX];
  printf("enter name, ");
  fgets(choice,MAX,stdin);
  choice[strcspn(choice,"\n")] = '\0';

  node *result=search_contact(*head,choice);
  if(result != NULL) {
    node *next = *head;
    node *prev = NULL;
    if (strcasecmp(choice,next->name) == 0) {
      *head = (*head)->next;
      free(next);
      printf("deleted succesfully.\n");
      return;
    } else {
      while (strcasecmp(choice,next->name) != 0) {
        prev = next;
        next = next->next;
      }
      prev->next = next->next;
      free(next);    prev = next;
      next = next->next;
    }
    printf("deleted succesfully.\n");
    return;
  } else {
    printf("contact not found.\n");
    return;
  }  
}

void display_all(node *head) {
  if (head == NULL) {
    printf("nothing to display\n");
    return;
  }

  node *chad = head;
  while (chad != NULL) {
    printf("Name: %s\tNumber: %s\n\n",chad->name,chad->number);
    chad=chad->next;
  }

}
node* search_contact(node *head,char choice[]) {
  if (head == NULL) {
    printf("nothing to search.\n");
    return NULL;
  }

  node *chad = head;

  while (chad != NULL) {
    if (strcasecmp(choice,chad->name) == 0 ) {
      return chad;
      break;
    }
    chad = chad->next;
  }

  return NULL;
}

