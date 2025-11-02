#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 10
#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1
typedef struct postfix* Position;
typedef struct postfix {
    int number;
    Position Next;
}postfix;

//Prototipi
int fileCheck();
int fileRead(Position);
int push(Position,int);
int pop(Position, Position,char);
int out(Position);
int main() {

    postfix Head = { 0,NULL };
    fileCheck();
    fileRead(&Head); 
    out(Head.Next); 


    return EXIT_SUCCESS;
}
int fileCheck() {

    FILE *f = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Vjezba5\\postifx.txt","r");
    if (f == NULL) { 
        return -1; }
    //Brojevi sa 9 znamenki max
    char *c=(char*)malloc(sizeof(char)*10);
    int numberOfNumbers = 0,dum;
    int numberOfOperations = 0;

    while (feof(f) == 0) {
        
        fscanf(f,"%s",c);
        printf("%s\n", c);
        if (c == EOF) {

        }
        else if (sscanf(c, "%d",&dum)==1) {
            numberOfNumbers++;
        }
        else {
            if (*c == '+' || *c == '*' || *c == '-' || *c == '/' || *c== '%') {
                numberOfOperations++;
            }
            else{
                return EXIT_FAILURE;
            }
        }
        
    }
    if (numberOfOperations + 1 != numberOfNumbers) {
        return EXIT_FAILURE;
    }
    printf("Numbers = %d Mat=%d", numberOfNumbers, numberOfOperations);
    free(c);
    fclose(f);
    return EXIT_SUCCESS;
}
int fileRead(Position Start) {
    FILE* f = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Vjezba5\\postifx.txt", "r");
    if (f == NULL) {
        return -1;
    }
    Position Q = Start;
    //Brojevi sa 9 znamenki max
    char* c = (char*)malloc(sizeof(char) * 10);
    int numberOfNumbers = 0,dum;
    
    while (feof(f) == 0) {

        fscanf(f,"%s", c);

        if (c == EOF) {
        
        }
        else if (sscanf(c, "%d", &dum) == 1) {
            numberOfNumbers++;
            push(Q, dum);
        }
        else {
            if (numberOfNumbers > 1) {
              pop(Q->Next, Q->Next->Next, *c);
            }
            else {
                printf("Nije postfix\n");
                return EXIT_FAILURE;
            }
        }
    }
    free(c);
    fclose(f);
    return EXIT_SUCCESS;
}
int push(Position Start,int num) {

    Position Q = (Position)malloc(sizeof(postfix));
    if (Q == NULL) {
        return -1;
    }
    Q->number = num;
    Q->Next = Start->Next;
    Start->Next = Q;

    return 0;
}
int pop(Position First, Position Second,char c) {
    switch (c) {
        case '+':
        First->number = First->number + Second->number;
        break;
        
        case '*':
        First->number = First->number * Second->number;
        break;

        case '-':
        First->number = First->number - Second->number;
        break;

        case '%':
        First->number = First->number % Second->number;
        break;

        case '/':
        First->number = First->number / Second->number;
        break;
    }
    First->Next = Second->Next;
    Second->Next = NULL;
    free(Second);
    return 0;
}
int out(Position Q) {
    if (Q == NULL) {
        return EXIT_FAILURE;
    }
    printf("\nRezultat: ");
    while (Q != NULL) {
       
        printf("%d", Q->number);
        Q = Q->Next;
    }

    free(Q);

    return EXIT_SUCCESS;
}