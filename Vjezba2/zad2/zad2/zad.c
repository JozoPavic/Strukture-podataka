
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
/*E) KORISTI DODAVANJE NA KRAJ LISTE



*/
//Prototipi
int addName(Postition);
int addBefore(Postition);
int addAfter(Postition);
int output(Postition);
Postition Find(char*, Postition);
Postition FindBefore(char*, Postition);
int Delete(Postition);
int addAfterElement(Postition);
int addBeforeElement(Postition);
int Sort(Postition);
int txtOutput(Postition);
int automaticScan(Postition);
int main() {

    Person Head = { "","",0,NULL };
    Postition found = NULL;
    int num;
    printf("Type 1 for manual input\nType 2 for automatic txt input \n");
    scanf("%d", &num);
    if (num == 1) {
        addBefore(&Head);
        addBefore(&Head);
        addAfter(&Head);

        //Ispisi
        //Izbrisi pa ispisi
        Delete(&Head);
        output(&Head);
        addAfterElement(&Head);
        addBeforeElement(&Head);
    }
    else if (num == 2) {
        automaticScan(&Head);
    }
    else { 
        printf("Error\n");
        return -1;
    }

    output(&Head);
    printf("Sort\n");
	Sort(Head.Next);
    output(&Head);

    txtOutput(Head.Next);

    return 0;
}
int txtOutput(Postition Start) {
    FILE* read = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Vjezba2\\zad2\\Ispis.txt", "w");
    if (read == NULL) {
        return -1;
    }
    while (Start != NULL) {
        fprintf(read,"%s %s %d %p \n", Start->name, Start->lastName, Start->birthYear, Start);
        //Odlazak na sljedeći el
        Start = Start->Next;
    }
    fclose(read);
    return 0;
}
int automaticScan(Postition Start) {
    FILE* read = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Vjezba2\\zad2\\Upis.txt", "r");
    if (read == NULL) {
        return -1;
    }
    char* X = (char*)malloc(sizeof(char) * 10);
    int t = 0;
    while (feof(read) == 0) {
        
        Postition Q = (Postition)malloc(sizeof(Person));
        if (Q == NULL) {
            return -1;
        }
        Q->Next = NULL;
        
        fscanf(read, "%s",X);
        strcpy(Q->name, X);
        fscanf(read, "%s", X);
        strcpy(Q->lastName, X);
        fscanf(read, "%d",&t);
        Q->birthYear = t;
        while (Start->Next != NULL) {
            Start = Start->Next;
        }

        Q->Next = Start->Next;
        Start->Next = Q;
    }

    fclose(read);
    return 0;
}

int Sort(Postition Start) {
   
    char* X = (char*)malloc(sizeof(char) * 10);
    char* X2 = (char*)malloc(sizeof(char) * 10);
    int X3;
    Postition Q = Start;
    Postition Q2 = Start;
    for (Q2 = Start; Q2 != NULL; Q2 = Q2->Next) {
        for (Q= Start; Q->Next != NULL; Q = Q->Next) {
            if (strcmp(Q->lastName, Q->Next->lastName) > 0) {
                strcpy(X, Q->lastName);
                strcpy(X2, Q->name);
                X3 = Q->birthYear;

                strcpy(Q->lastName, Q->Next->lastName);
                strcpy(Q->name, Q->Next->name);
                Q->birthYear = Q->Next->birthYear;

                strcpy(Q->Next->lastName, X);
                strcpy(Q->Next->name, X2);
                Q->Next->birthYear = X3;
            }
        }
    }
    

    return 0;
}
int addAfterElement(Postition Start) {
    //Provjera je li malloc uspio
    Postition Q = (Postition)malloc(sizeof(Person));
    if (Q == NULL) {
        return -1;
    }
    char* X = (char*)malloc(100 * sizeof(char));
    do {
        printf("Enter lastname that you want to add a person after: ");
        scanf("%s", X);
        //Oslobađanje buffer-a
        while ((getchar()) != '\n');
    } while (strlen(X) > 9);
    Start = Find(X, Start);
    if (Start == NULL) {
        return -1;
    }
    addName(Q);
    //Postavljanje na početak liste
    Q->Next = Start->Next;
    Start->Next = Q;

    return 0;
}
int addBeforeElement(Postition Start) {
    //Provjera je li malloc uspio
    Postition Q = (Postition)malloc(sizeof(Person));
    if (Q == NULL) {
        return -1;
    }
    //Alociranje do 100 znakova
    char* X = (char*)malloc(100 * sizeof(char));
    do {
        printf("Enter lastname that you want to add a person before : ");
        scanf("%s", X);
        //Oslobađanje buffer-a
        while ((getchar()) != '\n');
    } while (strlen(X) > 9);

    Start = FindBefore(X, Start);
    if (Start == NULL) {
        return -1;
    }
    addName(Q);
    //Postavljanje na početak liste
    Q->Next = Start->Next;
    Start->Next = Q;
    //free(X);
    return 0;
}
int addBefore(Postition Start) {
    //Provjera je li malloc uspio
    Postition Q = (Postition)malloc(sizeof(Person));
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
Postition Find(char* X, Postition Start) {
    //Alociranje do 100 znakova

    int i = 0;
    //Provjera da je prezime koje trazi krace od 10 znakova


    //Provjera je li NULL el i je li prezime isto kao ono koje se trazi
    while (Start != NULL && strcmp(Start->lastName, X) != 0) {
        //Odlazak na iduci el
        Start = Start->Next;
    }

    //Ako je dosa do kraja tj. NULL-a Ispisi da nije nasa
    if (Start == NULL) {
        printf("Not Found\n");
        //return -1;
    }
    //ako je nasa ispise na kojoj je adresi
    else { printf("Found on address: %p\n", Start); }

    //Oslobodi memoriju koju je zaozeo pokazivac X
    free(X);
    return Start;
}

Postition FindBefore(char* X, Postition Start) {
    //Inicijalizacija
    Postition helper = NULL;
    //Alociranje do 100 znakova



    //Provjera je li NULL el i je li prezime isto kao ono koje se trazi
    while (Start != NULL && strcmp(Start->lastName, X) != 0) {
        //helper postaje trenutni el
        helper = Start;
        //Start prelazi na iduci el
        Start = Start->Next;
    }
    free(X);
    //Ako nije nasa
    if (Start == NULL) {
        return NULL;
    }
    return helper;
}

int Delete(Postition Start) {
    char* X = (char*)malloc(100 * sizeof(char));
    /*Pozovi funckiju da nađe el prije elementa kojeg treba izbrisati
    Kad ga pronađe spremiti će ga u Start*/
    do {
        printf("Enter lastname you want to delete: ");
        scanf("%s", X);
        //Oslobađanje buffer-a
        while ((getchar()) != '\n');
    } while (strlen(X) > 9);
    Start = FindBefore(X, Start);
    //Ako nije nasa
    if (Start == NULL) {
        return -1;
    }
    //Postavi temp na el koji treba izbrisati
    Postition temp = Start->Next;
    //Postavi Start da mu je sljedeci el, el koji je orginalno bio iza el kojeg treba izbrisati
    Start->Next = temp->Next;

    //BRISI NJEGOV POKAZIVAC TJ NA NULL
    temp->Next = NULL;
    //Oslobodi memoriju od X i temp(izbrise el iz liste)
    free(temp);
    return 0;
}
int addName(Postition Q) {
    //Alociranje do 100 znakova
    char* X = (char*)malloc(100 * sizeof(char));
    int t = -1;//varijabla za godine 

    
        //Traziti ce da upises ime dok ne upises ime koje ima max 9 znakova
        do {
            printf("Enter first name: ");
            scanf("%s", X);
            //Oslobađanje buffer-a
            while ((getchar()) != '\n');
        } while (strlen(X) > 9);
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
            scanf("%d", &t);
            //Oslobađanje buffer-a
            while ((getchar()) != '\n');
        } while (t > 2025 || t < 0);
        //Upisi u el liste
        Q->birthYear = t;

    
    
    //Oslobodi memoriju
    free(X);
    return 0;
}