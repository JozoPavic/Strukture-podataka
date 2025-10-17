#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10

typedef struct person* Postition;
typedef struct person {
    char name[N];
    char lastName[N];
    int birthYear;
    Postition Next;
}Person;
int addBefore(Postition Start) {

    Postition Q = (Postition )malloc(sizeof(Person));
    addName(Q);
   
    Q->Next = Start->Next;
    Start->Next = Q;
    return 0;
}

int addAfter(Postition Start) {

    while (Start->Next != NULL) {
        Start = Start->Next;
    }
    Postition Q = (Postition)malloc(sizeof(Person));
    addName(Q);
    Q->Next = Start->Next;
    Start->Next = Q;
    return 0;
}

int output(Postition Start) {

    Start = Start->Next;
    while (Start != NULL) {
        printf("%s %s %d %p \n", Start->name, Start->lastName, Start->birthYear, Start);
        Start = Start->Next;
    }
    return 0;
}
int Find(Postition Start) {
    char X[N];
    int i = 0;
    do {
        printf("\nLastname you are looking for: ");
        scanf("%s", X);
    } while (2 == 3);
    
    while (Start != NULL && strcmp(Start->lastName, X) != 0) {
        Start = Start->Next;
    }
    if (Start == NULL) {
        printf("Not Found\n");
    }
    else { printf("Found on address: %p\n", Start); }
    return 0;
}

Postition FindBefore(char X[N], Postition Start) {
    Postition helper= Start;
    
    while(Start != NULL && strcmp(Start->lastName, X) != 0) {
        
        helper = Start;
        Start = Start->Next;
    }
    if (Start == NULL) {
        return NULL;
    }
    return helper;
}

int Delete(Postition Start) {
    char X[N];
    printf("Enter first lastname you want to delete: ");
    scanf("%s", X);
    Start = FindBefore(X, Start);
    if (Start == NULL) {
        return -1;
    }
    Postition temp = Start->Next;
    Start->Next = temp->Next;
    free(temp);
    return 0;
}
int addName(Postition Q) {

    char temp[N];
    int t;
    printf("Enter first name: ");
    scanf("%s", temp);
    strcpy(Q->name, temp);
    
    printf("Enter first lastname: ");
    scanf("%s", temp);
    strcpy(Q->lastName, temp);
    
    printf("Enter first birth year: ");
    scanf_s("%d", &t);
    Q->birthYear = t;
    
    
    return 0;
}
int main() {

    Person Head = {"","",0,NULL};
    addBefore(&Head);
    addBefore(&Head);
    addAfter(&Head);
    
    Find(&Head);
    
    output(&Head);
    Delete(&Head);
    output(&Head);

    return 0;
}