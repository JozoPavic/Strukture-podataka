#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1
typedef struct poly* Position;
typedef struct poly {
	int coefficient;
	int power;//potencija
	Position Next;
}Poly;
int fileReader(Position, int);
int add(Position, Position,Position);
int multi(Position, Position, Position);
int out(Position);
int main() {
	int check;
	//Deklaracija Head - za zbrajanje, Head2- za množenje
	Poly Head = { 0,0,NULL };
	Poly Head2 = { 0,0,NULL };
	Poly firstP = Head;
	Poly secondP = Head;

	
	//Pročitaj FILE-ove i stavi ih u liste
	check=fileReader(&firstP, 1);
	//U slucaju da je FILE krivo ima loše znakove zaustavi program
	if (check == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	check=fileReader(&secondP, 2);
	//U slucaju da je FILE krivo ima loše znakove zaustavi program
	if (check == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	//Zbroji i pomnoži
	add(&firstP, &secondP, &Head);
	multi(&firstP, &secondP, &Head2);

	//Ispiši pa ih izbriši
	out(&firstP);
	out(&secondP);
	out(&Head);
	out(&Head2);

	
	return EXIT_SUCCESS;
}
int multi(Position First, Position Second, Position Start) {
	Position Q1 = First->Next;
	Position Q2 = Second->Next;
	Position temp = Start;

	int max, tempCoefficient1, tempCoefficient2;
	//Pošto je sortiran unos najveca moguca potencija je zbroj prvih elemenata listi
	max = Q2->power + Q1->power;
	//Kopiraj vrijednost u copyMax
	int copyMax = max;
	//U listu za rezultat prvo stavi sve eksponente od največeg do najmanjeg
	for (copyMax; copyMax > -1; copyMax--) {
		Position Q = (Position)malloc(sizeof(Poly));
		if (Q == NULL) {
			printf("G");
			return EXIT_FAILURE;
		}
		//Dođi do kraja
		while (temp->Next != NULL) {
			temp = temp->Next;
		}
		/*Dodaj novi el u listu i Postavi mu eksponent na vrijednost copyMax - a i koeficijent mu stavi na 0*/
		Q->coefficient = 0;
		Q->power = copyMax;
		Q->Next = temp->Next;
		temp->Next = Q;
	}
	//Nakon što su postavljeni eksponenti
		for (Q2 = Second->Next; Q2 != NULL; Q2 = Q2->Next) {
			//Uzmi koeficijent prvog elementa i pomnoži ga sa svim el. druge liste
			tempCoefficient2 = Q2->coefficient;
			for (Q1 = First->Next; Q1 != NULL; Q1 = Q1->Next) {
				tempCoefficient1 = Q1->coefficient;
				//Izračunaj umnožak 2 koeficijenta
				int mul = tempCoefficient1 * tempCoefficient2;
				//Zbroji njihove eksponente u tempPower
				int tempPower = Q2->power + Q1->power;
				//Prolazi listom za rezultate
				for (temp = Start->Next; temp != NULL; temp = temp->Next) {
					//Ako je tempPower jednak eksponentu u listi na to mjesto liste postavi taj umnožak
					if (temp->power == tempPower) {
						temp->coefficient = temp->coefficient + mul;
					}
				}
				//resetiraj
				mul = 0;
				tempPower = 0;
			}
		}

	return EXIT_SUCCESS;
}
int add(Position First, Position Second, Position Start) {
	Position Q1 = First->Next;
	Position Q2 = Second->Next;
	Position temp = Start;
	int max;

	
	if (Q1->power >= Q2->power) {
		//Ako Q1 ima najvecu potenciju ili jednaku sa Q2 postavi max na nju
		max = Q1->power;
	}
	else if (Q1->power < Q2->power) {
		//Ako Q2 ima najvecu potenciju postavi max na nju
		max = Q2->power;
	}

	for (max; max > -1; max--) {
		int firstNum = 0, secondNum = 0;
		//Prođi cijelu listu i nađi el liste koji ima jednak eksponent kao i varijabla max
		for (Q1 = First->Next; Q1->Next != NULL; Q1 = Q1->Next) {
			//Imaju istu vrijednost zabilježi vrijednost tog koeficijenta(koji ima isti eksponent) u var firstNum
			if (max == Q1->power) {
				firstNum = Q1->coefficient;
				break;
			}
		}
		//Prođi cijelu listu i nađi el liste koji ima jednak eksponent kao i varijabla max
		for (Q2 = Second->Next; Q2->Next != NULL; Q2 = Q2->Next) {
			//Imaju istu vrijednost zabilježi vrijednost tog koeficijenta(koji ima isti eksponent) u var secondNum
			if (max == Q2->power) {
				secondNum = Q2->coefficient;
			
				break;
			}
		}
		//Ako se koeficijenti poništavaju nemoj ništa dodavati u listu
		int added = firstNum + secondNum;
		if (added == 0) {
		}
		else {
			Position Q = (Position)malloc(sizeof(Poly));
			if (Q == NULL) {
				printf("G");
				return EXIT_FAILURE;
			}
			//Dođi do kraja liste
			while (temp->Next != NULL) {
				temp = temp->Next;
			}
			//Postavi koeficijent liste na zbroj 
			Q->coefficient = added;
			//Postavi pu potenciju na trenutni max tj. na trenutnu potenciju koja je zapisana u var max
			Q->power = max;

			Q->Next = temp->Next;
			temp->Next = Q;
		}
		
		
	}
	return EXIT_SUCCESS;
}
int fileReader(Position Start, int num) {
	Position temp = Start;
	Position P;
	FILE* f;
	//Ako je num=1 otvori FILE- sa prvom jednadžbom
	if (num == 1) {
		f = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Vjezba4\\br.txt", "r");
	}
	else {//Ako je num=2 otvori FILE- sa drugom jednadžbom
		f = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Vjezba4\\br2.txt", "r");
	}
	//U slučaju greške
	if (f == NULL) {
		return EXIT_FAILURE;
	}
	//Max broj sa 9 znamenki
	char* c = (char*)malloc(sizeof(char) * 10);
	int tempCoefficient, tempPower;
	//Čitaj FILE
	while (feof(f) == 0) {
		Position Q = (Position)malloc(sizeof(Poly));
		if (Q == NULL) {
			printf("G");
			return EXIT_FAILURE;
		}


		//Uzmi do razmaka i spremi u privremeni koeficijent
		fscanf(f, "%s", c);
		//Ako pronađe neko slovo javi grešku
		if (sscanf(c, "%d", &tempCoefficient) == 0) {
			return EXIT_FAILURE;
		}
		sscanf(c, "%d", &tempCoefficient);

		//Uzmi do razmaka i spremi u privremeni eksponent
		fscanf(f, "%s", c);
		//Ako pronađe neko slovo javi grešku
		if (sscanf(c, "%d", &tempPower) == 0) {
			return EXIT_FAILURE;
		}
		sscanf(c, "%d", &tempPower);


		//Ulazi u listu
		for (P = temp; P->Next != NULL; P = P->Next) {
			//Ako je privremeni eksponent veći od eksponenta sljedećeg el ubaci ga prije njega
			if (tempPower > P->Next->power) {
				break;
			}
		}
		//Ubacivanje u listu prije manjeg eksponenta
		Q->coefficient = tempCoefficient;
		Q->power = tempPower;
		Q->Next = P->Next;
		P->Next = Q;

	}
	//Oslobodi c i zatvori FILE
	free(c);
	fclose(f);
	return EXIT_SUCCESS;
}
int out(Position Start) {
	//Preskoči HEAD
	Position Q = Start->Next;
	//Prolaz cijelom listom
	while (Q != NULL) {
		//Ispiši pa prebaci na sljedeći el
		printf("%dx%d ", Q->coefficient, Q->power);
		Q = Q->Next;
	}
	//Postavi Q na Start tj. Head - tako da izbriše i prvi el. - Head se neće obrisati
	Q = Start;
	Position temp;
	//Prolaz listom Brijsanje od naprid
	while (Q->Next != NULL) {
		//Postavi temp na sljedeći el
		temp = Q->Next;
		//Iz liste je izbačen temp
		Q->Next = temp->Next;
		//temp pokazuje na NULL
		temp->Next = NULL;
		//Izbriši
		free(temp);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
