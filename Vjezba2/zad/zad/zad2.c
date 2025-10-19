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
    //Provjera je li malloc uspio
    Postition Q = (Postition )malloc(sizeof(Person));
    if (Q == NULL) {
        return -1;
    }
    //Poziv funkcije za dodavanje podataka
    addName(Q);
   
    //Postavljanje na početak liste
    Q->Next = Start->Next;
    Start->Next = Q;
    return 0;
}

int addAfter(Postition Start) {
    //Prolaz liste do kraja
    while (Start->Next != NULL) {
        Start = Start->Next;
    }
    //Provjera je li malloc uspio
    Postition Q = (Postition)malloc(sizeof(Person));
    if (Q == NULL) {
        return -1;
    }
    //Poziv funkcije za dodavanje podataka
    addName(Q);

    //Postavljanje na kraj liste
    Q->Next = Start->Next;
    Start->Next = Q;
    return 0;
}

int output(Postition Start) {
    //Preskok HEAD-a
    Start = Start->Next;
    //Ispis svega dok nedođe do NULL-a tj. kraja
    while (Start != NULL) {
        printf("%s %s %d %p \n", Start->name, Start->lastName, Start->birthYear, Start);
        //Odlazak na sljedeći el
        Start = Start->Next;
    }
    return 0;
}
int Find(Postition Start) {
    //Alociranje do 100 znakova
    char* X = (char*)malloc(100 * sizeof(char));
    int i = 0;
    //Provjera da je prezime koje trazi krace od 10 znakova
    do {
        printf("Enter lastname you want to find: ");
        scanf("%s", X);

        //Oslobađanje buffer-a
        while ((getchar()) != '\n');
    } while (strlen(X) > 9);
    
    //Provjera je li NULL el i je li prezime isto kao ono koje se trazi
    while (Start != NULL && strcmp(Start->lastName, X) != 0) {
        //Odlazak na iduci el
        Start = Start->Next;
    }

    //Ako je dosa do kraja tj. NULL-a Ispisi da nije nasa
    if (Start == NULL) {
        printf("Not Found\n");
    }
    //ako je nasa ispise na kojoj je adresi
    else { printf("Found on address: %p\n", Start); }

    //Oslobodi memoriju koju je zaozeo pokazivac X
    free(X);
    return 0;
}

Postition FindBefore(char X[N], Postition Start) {
    //Inicijalizacija
    Postition helper= NULL;

    //Provjera je li NULL el i je li prezime isto kao ono koje se trazi
    while(Start != NULL && strcmp(Start->lastName, X) != 0) {
        //helper postaje trenutni el
        helper = Start;
        //Start prelazi na iduci el
        Start = Start->Next;
    }
    //Ako nije nasa
    if (Start == NULL) {
        return NULL;
    }
    return helper;
}

int Delete(Postition Start) {
    //Alociranje do 100 znakova
    char *X= (char*)malloc(100 * sizeof(char));
    do {
        printf("Enter lastname you want to delete: ");
        scanf("%s", X);
        //Oslobađanje buffer-a
        while ((getchar()) != '\n');
    } while (strlen(X) > 9);
    /*Pozovi funckiju da nađe el prije elementa kojeg treba izbrisati
    Kad ga pronađe spremiti će ga u Start*/
    Start = FindBefore(X, Start);
    //Ako nije nasa
    if (Start == NULL) {
        return -1;
    }
    //Postavi temp na el koji treba izbrisati
    Postition temp = Start->Next;
    //Postavi Start da mu je sljedeci el, el koji je orginalno bio iza el kojeg treba izbrisati
    Start->Next = temp->Next;

    //Oslobodi memoriju od X i temp(izbrise el iz liste)
    free(temp);
    free(X);
    return 0;
}
int addName(Postition Q) {
    //Alociranje do 100 znakova
    char *X=(char*)malloc(100*sizeof(char));
    int t=-1;//varijabla za godine 
    
    //Traziti ce da upises ime dok ne upises ime koje ima max 9 znakova
    do {
        printf("Enter first name: ");
        scanf("%s", X);
        //Oslobađanje buffer-a
        while ((getchar()) != '\n');
    } while (strlen(X)>9);
    //Uspisi ime u el
    strcpy(Q->name, X);

    //Traziti ce da upises prezime dok ne upises prezime koje ima max 9 znakova
    do {
        printf("Enter lastname: ");
        scanf("%s", X);
        //Oslobađanje buffer-a
        while ((getchar()) != '\n');
    } while (strlen(X) > 9);
    //Upisi prezime u el liste
    strcpy(Q->lastName, X);

    //Traziti ce da upises god. rođenja dok ne upises neku koja nije veca od trenutne 2025 i nije negativna
    do {
        printf("Enter birth year: ");
        scanf_s("%d", &t);
        //Oslobađanje buffer-a
        while ((getchar()) != '\n');
    } while (t>2025 || t<0);
    //Upisi u el liste
    Q->birthYear = t;
    
    //Oslobodi memoriju
    free(X);
    return 0;
}
int main() {

    Person Head = {"","",0,NULL};
    //Dodaj 3 el 2 na pocetak 1 na kraj liste
    addBefore(&Head);
    addBefore(&Head);
    addAfter(&Head);
    
    //Pronađi el po prezimenu
    Find(&Head);
    //Ispisi
    output(&Head);
    //Izbrisi pa ispisi
    Delete(&Head);
    output(&Head);

    return 0;
}