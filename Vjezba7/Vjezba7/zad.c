#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include <string.h>

#define N 20
typedef struct directory* dirPosition;
typedef struct directory {
	char ime[N];
	dirPosition Next;
	dirPosition subDirPosition;
}Directory;
typedef struct stack* stackPosition;
typedef struct stack {
	stackPosition Next;
	dirPosition dirLevel;
}Stack;
//Prototipi
int GoBack(dirPosition, stackPosition);
int deleteStack(stackPosition);
int delete(dirPosition);
int deleteChild(dirPosition);
int dir(dirPosition);
int cdTT(stackPosition);
int cd(dirPosition, stackPosition,char *);
int push(stackPosition, dirPosition);
int addDir(dirPosition, stackPosition);
int mkdir(dirPosition,char *);
int main() {
	
	Directory headDirectory = { "",NULL,NULL };
	Stack headStack = { NULL,NULL };
	//Poziv funkcije da se dodaju 2 diska
	addDir(&headDirectory, &headStack);
	addDir(&headDirectory, &headStack);
	//varijabla za meni
	int active = 1;
	cdTT(&headStack);
	//char-ovi za komandu i ime datoteke ako je potrebno
	char* command = malloc(sizeof(char) * 7);
	char *name = malloc(sizeof(char) * N);
	while (active) {//Ako je STACK prazan traži korisnika da se vrati u disk
		if (headStack.Next == NULL) {
			GoBack(headDirectory.Next,&headStack);
		}
		else {//Trazi od kosnika da upiše komandu
			printf("Upisi: mkdir | cd | cd.. | dir | EXIT");
			//Ispiši u kojoj si datoteci
			printf("\n%s> ", headStack.Next->dirLevel->ime);
			scanf("%s", command);

			if (strcmp(command, "mkdir") == 0) {
				scanf("%s", name);//traži ime datoteke
				//Šalje adresu datoteke koja je na početku Stacka
				mkdir(headStack.Next->dirLevel, name);
				system("cls");//Očisti ekran
			}
			else if (strcmp(command, "cd") == 0) {
				scanf("%s", name);//traži ime datoteke
				cd(headStack.Next->dirLevel, &headStack, name);
				system("cls");//Očisti ekran
			}
			else if (strcmp(command, "cd..") == 0) {
				cdTT(&headStack);
				system("cls");//Očisti ekran
			}
			else if (strcmp(command, "dir") == 0) {
				system("cls");//Očisti ekran
				dir(headStack.Next->dirLevel);
			}
			else if (strcmp(command, "EXIT") == 0) {
				out(headDirectory.Next);//Ispis svega
				delete(&headDirectory);//Brisanje
				deleteStack(&headStack);//Brisanje stack-a
				out(headDirectory.Next);
				active = 0;//active 0 pa izlazi iz meni-a

			}
			else {//Očisti ekran i ispiši opet meni
				system("cls");
			}
		}
	}

	return 0;
}
int GoBack(dirPosition Start,stackPosition StackStart) {
	dirPosition P = Start;
	while (P != NULL) {
		//Ispiši sve opcije za diskove u koje ćes se vratiti
		printf("%s\n", P->ime);
		P = P->Next;
	}
	int found = 0;
	P = Start;
	while (found == 0) {
		printf("U koji disk ces se vratiti: ");
		char* input = malloc(sizeof(char) * N);
		
		scanf("%s", input);
		//Prolaz svim diskovima
		while (P != NULL) {//Ako nađe disk
			if (strcmp(input, P->ime)==0) {
				found = 1;
				push(StackStart,P);//Stavi ga u stack
				break;
			}
			P = P->Next;
		}

	}
	
	return 0;
}
int deleteStack(stackPosition Start) {
	stackPosition temp;
	//Prođi cijeli stack
	while (Start->Next != NULL) {

		temp = Start->Next;
		Start->Next = temp->Next;
		//Postavlja next na NULL
		temp->Next = NULL;
		//Izbriši
		free(temp);
	}
	return 0;
}
int delete(dirPosition Start) {
	dirPosition temp;
	while (Start->Next != NULL) {
		//Pozove funkciju koja će izbrisati sve poddatoteke
		deleteChild(Start->subDirPosition);
		temp = Start->Next;
		Start->Next = temp->Next;
		//Postavlja next na NULL
		temp->Next = NULL;
		//Izbriši
		free(temp);
	}
	return 0;
}
int deleteChild(dirPosition current) {
	if (current == NULL) {
		return 0;
	}
	dirPosition currentSub = NULL;
	dirPosition temp;
	//Ako ima poddatoteke
	if (current->subDirPosition != NULL) {

		currentSub = current->subDirPosition;
		//Ako datoteka u sebi ima djete
		while (currentSub != NULL) {
			//Pozovi funkciju opet, ali ovaj put sa adresom djeteta pa će njega obrisat
			deleteChild(currentSub);
			//Obriši datoteku
			temp = currentSub->Next;
			currentSub->Next = temp->Next;
			temp->Next = NULL;
			free(temp);
		}
	}
	return 0;
}
int mkdir( dirPosition P,char *input) {
	//Zapamti ime oca
	dirPosition Parent = P;
	//Alociraj memo za djete
	dirPosition newEl = (dirPosition)malloc(sizeof(Directory));
	if (newEl == NULL) {
		return -1;
	}
	//Stavi mu ime
	strcpy(newEl->ime, input);
	//Ubaci djete
	newEl->Next = Parent->subDirPosition;
	//djete nema djece
	newEl->subDirPosition = NULL;
	//Otac pokazuje na djete
	Parent->subDirPosition = newEl;

	return 0;
}
int out(dirPosition Start) {
	//Ako je sve obrisano obavjesti korisnika
	if (Start == NULL) {
		printf("Obrisano je");
		return 0;
	}
	//Ispiši disk
	while (Start != NULL) {
		printf("%s\n", Start->ime);
		//Ispiši djecu
		dir(Start);
		//Otiđi na sljedeći disk
		Start = Start->Next;
	}
	return 0;
}
int dir(dirPosition current) {
	int index = 1;
	dirPosition currentSub = NULL;
	//Ako ima poddatoteke
	if (current->subDirPosition != NULL) {	

		currentSub = current->subDirPosition;
		while (currentSub != NULL) {
			//Ispiši ime datoteke
			printf("%d%s\n", index,currentSub->ime);
			index++;
			//Pozovi funkciju opet, ali ovaj put sa adresom djeteta pa će njega ispisati
			dir(currentSub);
			currentSub = currentSub->Next;
		}
	}

	return 0;
}
//POP
int cdTT(stackPosition stack) {
	stackPosition StartStack = stack;
	stackPosition temp = stack->Next;

	StartStack->Next = temp->Next;
	temp->Next = NULL;
	free(temp);
	return 0;
}
int cd(dirPosition P, stackPosition stack,char *input) {
	int found = 0;

	dirPosition temp = P->subDirPosition;
	while (temp != NULL) {
		//Našao je datoteku
		if (strcmp(input, temp->ime) == 0) {
			//Postavi njenu adresu na stack
			push(stack, temp);
			//Obavjest da je ušao u datoteku
			printf("FOUND\n");
			found = 1;
			break;
		}
		temp = temp->Next;
	}//Ako nije našao datoteku
	if (!found) {
		printf("Not FOUND\n");
	}
	return 0;
}
int push(stackPosition StackStart, dirPosition Q) {
	//alokacija memo
	stackPosition P = malloc(sizeof(Stack));
	//Upis prije
	P->Next = StackStart->Next;
	StackStart->Next = P;
	//Postavi dirlevel tako da pokazuje na upisani element
	P->dirLevel = Q;
	return 0;
}

int addDir(dirPosition head, stackPosition stack) {
	dirPosition Start = head;
	stackPosition StackStart = stack;
	//Alocira memo za disk
	dirPosition Q = (dirPosition)malloc(sizeof(Directory));
	if (Q == NULL) {
		return -1;
	}
	//Trazi upis imena diska
	printf("Upisi ime diska: ");
	char* p = malloc(sizeof(char) * 10);
	scanf("%s", p);
	strcpy(Q->ime,p);
	while (Start->Next != NULL) {
		Start = Start->Next;
	}
	//Postavlja ga na kraj
	Q->Next = Start->Next;
	Start->Next = Q;
	Q->subDirPosition = NULL;

	//Stavi ga na početak stack
	push(StackStart, Q);


	return 0;
}