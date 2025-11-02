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
    //Provjeri za krive znakove i je li uopće moguće izvršiti jednadžbu tj. ima li dovoljno brojeva i mat operacija
    fileCheck();
    //Stog
    fileRead(&Head); 
    //Ispiši Rezultat
    out(Head.Next); 


    return EXIT_SUCCESS;
}
int fileCheck() {
    //Učitaj datoteku i provjeri je li postoji
    FILE *f = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Vjezba5\\postifx.txt","r");
    if (f == NULL) { 
        return EXIT_FAILURE; }
    //Brojevi sa 9 znamenki max
    char *c=(char*)malloc(sizeof(char)*10);
    //Brojač brojeva i operacija
    int numberOfNumbers = 0;
    int numberOfOperations = 0;
    int dum;
    //Izvrti cijeli file
    while (feof(f) == 0) {
        //Dodaj u c do razmaka tako da mogu višeznamenkasti brojevi
        fscanf(f,"%s",c);
        //Ispiši taj char
        printf("%s ", c);
        //Ako je zadnji el 
        if (c == EOF) {

        }//Sa sscanf provjerimo je li c broj i pohranimo ga u dum, ako je broj onda je uvjet ispunjen
        else if (sscanf(c, "%d",&dum)==1) {
            //Poveća se brojac brojeva
            numberOfNumbers++;
        }
        else {//Ako je operacija
            if (*c == '+' || *c == '*' || *c == '-' || *c == '/' || *c== '%') {
                //Poveća se brojac operacija
                numberOfOperations++;
            }
            else{//Ako je našlo neki loš znak npr. slovo 
                return EXIT_FAILURE;
            }
        }
        
    }//Svaka mat. operacija mora ispuniti ovaj uvjet tj. uvjek je više brojeva za 1 od broja operacija
    if (numberOfOperations + 1 != numberOfNumbers) {
        return EXIT_FAILURE;
    }
    //Ispiši koliko je brojeva i operacija
    //printf("\nNumbers = %d Operations=%d", numberOfNumbers, numberOfOperations);
    //Zatovori datoteku i oslobodi c
    free(c);
    fclose(f);
    return EXIT_SUCCESS;
}
int fileRead(Position Start) {
    //Učitaj datoteku i provjeri je li postoji
    FILE* f = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Vjezba5\\postifx.txt", "r");
    if (f == NULL) {
        return -1;
    }
    Position Q = Start;
    //Brojevi sa 9 znamenki max
    char* c = (char*)malloc(sizeof(char) * 10);
    //Brojač brojeva i dum kao dummy int
    int numberOfNumbers = 0,dum;
    //Izvrti cijeli file
    while (feof(f) == 0) {
        //Dodaj u c do razmaka tako da mogu višeznamenkasti brojevi
        fscanf(f,"%s", c);

        //Ako je zadnji el
        if (c == EOF) {
        
        }//Sa sscanf provjerimo je li c broj i pohranimo ga u dum, ako je broj onda je uvjet ispunjen
        else if (sscanf(c, "%d", &dum) == 1) {
            //Poveća se brojac brojeva i šaljemo Q i dum u funkciju push tj. u stog
            numberOfNumbers++;
            push(Q, dum);
        }
        else {//Ako nema makar 2 broja 
            if (numberOfNumbers > 1) {
              pop(Q->Next, Q->Next->Next, *c);
              //Nakon što je izvršilo operaciju imamo 1 broj manje pa
              numberOfNumbers--;
            }
            else {
                //Ako nema dovoljno brojeva za operaciju onda nije ispravan postfix
                printf("Nije postfix\n");
                return EXIT_FAILURE;
            }
        }
    }
    //Zatovori datoteku i oslobodi c
    free(c);
    fclose(f);
    return EXIT_SUCCESS;
}
int push(Position Start,int num) {
    //Provjera je li Q NULL
    Position Q = (Position)malloc(sizeof(postfix));
    if (Q == NULL) {
        return -1;
    }
    //Dajemo mu broj
    Q->number = num;
    //Postavljamo ga na vrh stoga tj. početak liste
    Q->Next = Start->Next;
    Start->Next = Q;

    return 0;
}
int pop(Position First, Position Second,char c) {
    //Obavi jednu od 5 operacija i spremi ju u 1. el
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
    //Prvi el pokazuje na el na koji je pokazivao drugi
    First->Next = Second->Next;
    //Brisanje drugog el iz liste
    Second->Next = NULL;
    free(Second);
    return 0;
}
int out(Position Q) {
    //Ako je NULL
    if (Q == NULL) {
        return EXIT_FAILURE;
    }
    printf("\nResult: ");
    printf("%d", Q->number);
    
    //Oslobodi listu
    Q->Next = NULL;
    free(Q);

    return EXIT_SUCCESS;
}