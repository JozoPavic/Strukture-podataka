#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10

typedef struct postfix* Position;
typedef struct postfix {
    double number;
    Position Next;
}postfix;

//Prototipi
/*
oslobodi listu temp->Next=NULL;

free(temp)

Nikad u fun(&head)
head=head->Next radije Q=head->Next korisit zamjenski pokazivac

5.zad
infix (4+3)*2
postfix zapis   43+2*

u listu ubacujes brojeve kada dođe mat.operacija onda nju obavis
Na kraju programa samo 1 broj i da nema viška mat.operacija
*/
int fileRead();
int main() {

    postfix Head = { 0,NULL };
    /*1funkcija
    Otvori datoteku
    pohranit u podatke
    zatvorit

    AKO JE USPJESNO return EXIT_SUCCESS ako ne EXIT FAILURE
    */

    /*2 P
    if
    je li znak br
    je li mat.operacija
    else ima višak

    push(ubacuje el na vrh ADDBEFORE(num,&head))
    pop(&first,&second)-mos napravit da skida 2 el odjednom pa onda odradi mat op
    ili
    pop(&first,)-mos napravit da skida 1 el
    */

    /*
    Alocirat prostor za novi el
    Position newEl=(Position)malloc(sizeof(postfix));//Umjesto head koristi zamjensku var Q
    newEl->Next=head->Next
    head->next=newEl;


    Kad dođe matop korisit temp za novu listu ili u jedan od 2 el pohraniš rezultat pa onda obrišeš jedan od elemenata

    first=head->Next
    second=first->Next

    napravis funkciju koja ce prepoznat znak pr +
    first->number=first->number+second->number;
    nesmis dobit neg?

    nakon sto izracunas
    pop(&first,&second)

    pop
    {first->Next=Second->Next;
    Second->Next=NULL;
    free(Second);

    PREGLEDAJ DODATNE EL I IZBRISI
    }
    */
    return 0;
}
int fileRead() {

    return 0;
}