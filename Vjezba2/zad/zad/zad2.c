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
    char* X = (char*)malloc(24 * sizeof(char));
    int i = 0;
    do {
        printf("Enter lastname you want to delete: ");
        scanf("%s", X);
    } while (2 == 3 && strlen(X) > 9);
    
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
    char *X= (char*)malloc(24 * sizeof(char));
    do {
        printf("Enter lastname you want to delete: ");
        scanf("%s", X);
    } while (strlen(X) > 9);
    Start = FindBefore(X, Start);
    if (Start == NULL) {
        return -1;
    }
    Postition temp = Start->Next;
    Start->Next = temp->Next;
    free(temp);
    free(X);
    return 0;
}
int addName(Postition Q) {

    char *temp=(char*)malloc(24*sizeof(char));
    int t=-1;
    
    do {
        printf("Enter first name: ");
        scanf("%s", temp);
    } while (strlen(temp)>9);
    strcpy(Q->name, temp);

    do {
        printf("Enter lastname: ");
        scanf("%s", temp);
    } while (strlen(temp) > 9);
    strcpy(Q->lastName, temp);

    do {
        printf("Enter birth year: ");
        scanf_s("%d", &t);
    } while (t>2025 || t<0);
    Q->birthYear = t;
  
    free(temp);
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