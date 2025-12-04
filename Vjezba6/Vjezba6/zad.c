#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#define MAX 20


typedef struct _date* datePosition;
typedef struct _date {
	int year, month, day;
}Date;
typedef struct item* itemPosition;
typedef struct item {
	char name[MAX];
	int amount;
	float price;
	itemPosition Next;
}Item;
typedef struct _bill* billPosition;
typedef struct _bill {
	char billName[MAX];
	int id;
	itemPosition NextItem;
	datePosition date;
	billPosition NextBill;
}Bill;

typedef struct itemValue* itemValuePosition;
typedef struct itemValue {
	char name[MAX];
	float price;
	itemValuePosition Next;
}ItemValue;
//Prototipi
int backOrClose();
int maxValueBetween2(billPosition, itemValuePosition );
int printFilteredBill(billPosition, int);
int smallestBill(billPosition );
int biggestBill(billPosition );
int profitBill(itemPosition );
int profit(itemValuePosition );
int deleteItem(itemValuePosition);
int itemValuePeriod(itemValuePosition, char*);
int itemMinValued(itemValuePosition);
int itemMaxValued(itemValuePosition);
int outTest(itemValuePosition);
int out(billPosition);
int maxValue(billPosition , itemValuePosition , int );
int dateBetween(Date*, int, int, int, int, int, int);
int loadBills(billPosition);
int loadItems(billPosition, itemPosition, char*);


int main() {
	//Head za račune
	Bill Head={"",NULL,NULL,NULL};
	//Učitavanje računa
	loadBills(&Head);
	//Varijabla za aktivan meni
	int active = 1;
	//lista za sve proizvode 
	ItemValue ItemHead = { "",0.0,NULL };
	//Znak
	char input;
	
	while (active == 1) {
		printf("Welcome! Press:\n");
		printf("| [A] to see all bills | [B] to see how much money all the items made | [C] to see profit of all bills |\n");
		printf("| [D] to see item that made the most money | [E] to see item that made the most money in certain period |\n");
		printf("| [F] to see item that made the least money | [G] to see item that made the least money in certain period |\n");
		printf("| [H] to check how much money item made in certain period |\n");
		printf("| [I] to see bill that made the most money | [J] to see bill that made the least money |\n");
		printf("| [K] to see item that made the most money between 2 bills | [L] to see item that made the least money between 2 bills |\n");
		printf("| [M] to see every bill in which selected item sold |\n");
		printf("| [X] to exit |\n");
		//Uzima slovo i pretvori ga u veliko slovo
		input = getchar();
		input = toupper(input);
		switch (input) {
		case'A':
			//Ispis svih računa
			out(Head.NextBill);
			//Poziv na to hoće li se program završiti i vratiti u meni
			active = backOrClose();
			break;
		case'B':
			//Sprema sve artikle iz računa
			maxValue(&Head, &ItemHead, 0);
			//Ispiše sve račune
			outTest(&ItemHead);
			//Poziv na to hoće li se program završiti i vratiti u meni
			active = backOrClose();
			break;
		case'C':
			//Sprema sve artikle iz računa i ispiše profit
			maxValue(&Head, &ItemHead, 0);
			profit(&ItemHead);
			active = backOrClose();
			break;
		case'D':
			//Sprema sve artikle iz računa
			maxValue(&Head, &ItemHead, 0);
			//Ispiše artikl koji je najviše zaradio
			itemMaxValued(&ItemHead);
			//Poziv na to hoće li se program završiti i vratiti u meni
			active = backOrClose();
			break;
		case'E':
			//Sprema sve artikle iz računa, ali limit je 1 pa će pitati za određeni period
			maxValue(&Head, &ItemHead, 1);
			//Ispiše artikl koji je najviše zaradio
			itemMaxValued(&ItemHead);
			active = backOrClose();
			break;
		case'F':
			//Sprema sve artikle iz računa
			maxValue(&Head, &ItemHead, 0);
			//Ispiše artikl koji je najmanje zaradio
			itemMinValued(&ItemHead);
			active = backOrClose();
			break;
		case'G':
			//Sprema sve artikle iz računa, ali limit je 1 pa će pitati za određeni period
			maxValue(&Head, &ItemHead, 1);
			//Ispiše artikl koji je najmanje zaradio
			itemMinValued(&ItemHead);
			active = backOrClose();
			break;
		case'H':
			maxValue(&Head, &ItemHead, 1);
			char* name = malloc(sizeof(char) * 20);
			printf("What item: ");
			scanf("%s", name);
			int i = 0;
			while (*(name + i) != NULL) {
				*(name + i) = tolower(*(name + i));
				i++;
			}
			itemValuePeriod(&ItemHead, name);
			active = backOrClose();
			break;
		case'I':
			//Račun koji je najviše zaradio
			biggestBill(Head.NextBill);
			active = backOrClose();
			break;
		case'J':
			//Račun koji je najmanje zaradio
			smallestBill(Head.NextBill);
			active = backOrClose();
			break;
		case'K':
			//Ispiše sve račune
			out(Head.NextBill);
			//Pita korisnika da unese id od 2 računa
			maxValueBetween2(&Head, &ItemHead);
			//Izbaci proizvod koji je najviše zaradio između 2 računa
			itemMaxValued(&ItemHead);
			active = backOrClose();
			break;
		case'L':
			out(Head.NextBill);//Ispiše sve račune
			//Pita korisnika da unese id od 2 računa
			maxValueBetween2(&Head, &ItemHead);
			//Izbaci proizvod koji je najmanje zaradio između 2 računa
			itemMinValued(&ItemHead);
			active = backOrClose();
			break;
		case'M':
			//Formira listu svih proizvoda
			maxValue(&Head, &ItemHead, 0);
			//Funkcija ispiše sve račune u kojima se prodao proizvod koji je korisink unio
			itemFound(Head.NextBill);
			active = backOrClose();
			break;
		case'X':
			//Izlazi iz petlje
			active = 0;
			break;
		case '\n':
			//izbriše ekran,ali opet će se ispistati
			system("cls");
			break;
		default:
			while ((getchar()) != '\n');
			//izbriše ekran,ali opet će se ispistati
			system("cls");
			break;
		}
	}
	//Obriše sve račune prije završetka programa
	deleteBills(&Head);
	//Ispiše potvrdu da ih je obrisao
	out(Head.NextBill);
	return 0;
}
int backOrClose() {
	//Govori korisniku da pritisne ENTER da se vrati u meni
	//Bilo što drugo završava program
	printf("\nStisnite Enter da bi se vratili u meni\n");
	printf("Stisnite bilo što da bi ste zatvorili program\n");
	//Clear-a buffer
	while ((getchar()) != '\n');
	//Traži unos znaka
	char input = getchar();
	input = toupper(input);
	switch (input) {
	case'\n':
		//Obriši ekran i vrati se u meni
		system("cls");
		return 1;
		break;
	default:
		//Izgasi program, jer active=0
		return 0;
	}

}
int itemFound(billPosition Start) {
	if (Start == NULL) {
		printf("Sve obrisano");
		return 0;
	}
	//Traži unos proizvoda
	printf("Enter a name of an item: ");
	char* name = malloc(sizeof(char) * 20);
	scanf("%s", name);
	printf("\n");
	int i = 0;
	//Pretvori svako slovo unosa u malo slovo
	while (*(name + i) != NULL) {
		*(name+i) = tolower(*(name + i));
		i++;
	}
	//Varijabla je li pronašao proizvod i koliko ga je puta pronašao
	int found = 0, counter = 0;;
	billPosition B = Start;
	while (B != NULL) {
		itemPosition Q = B->NextItem->Next;
		//Postavi Begining na pocetni proizvod
		itemPosition Begining = B->NextItem->Next;
		while (Q != NULL) {
			if (strcmp(name, Q->name)==0) {
				found = 1;
				counter++;
				break;
			}
			Q = Q->Next;
		}//Ako je pronašao proizvod u računu
		if (found == 1) {//Ispiše sve o računu
			printf("%s Id=%d %d/%d/%d\n", B->billName, B->id, B->date->year, B->date->month, B->date->day);
			//Vrati pokazivac na prvi proizvod
			Q = Begining;
			while (Q != NULL) {//Ispiše sve proizvode od računa
				printf("%s %.2f %d\n", Q->name, Q->price, Q->amount);
				Q = Q->Next;
			}//Vrati found na 0
			found = 0;
		}
		
		if (counter>0&&B->NextBill != NULL)
			printf("\n");
		B = B->NextBill;

	}//Ako nije pronasao taj proizvod napisi ovu poruku
	if (counter == 0) {
		printf("%s wasn't found in any bill.\n", name);
	}
	return 0;
}
int maxValueBetween2(billPosition Start, itemValuePosition StartingItem) {
	billPosition P = Start;
	itemValuePosition P1 = StartingItem;
	int id1, id2;
	int find = 0;//Trazi od korisnika da upise 2 id-a od računa 
	printf("Type id of a 1st bill: ");
	scanf("%d", &id1);
	printf("\nType id of a 2nd bill: ");
	scanf("%d", &id2);
	id1;
	id2;//Prolaz svim računima
	for (P = Start->NextBill; P != NULL; P = P->NextBill) {
		//Ako je id računa jednak jednome od 2 upisana
		if (P->id == id1 || P->id == id2) {
			itemPosition I = P->NextItem;
			//Prolaz listom proizvoda jednog računa
			for (I = P->NextItem->Next; I != NULL; I = I->Next) {
				while (P1->Next != NULL) {
					P1 = P1->Next;
					//Ako su ime proizvoda prvog računa ista sa proizvodom drugog računa 
					//to je zapravo isti proizvod pa povečaj cijenu proizvoda u listi proizvoda
					if (strcmp(P1->name, I->name) == 0) {
						P1->price = P1->price + (I->amount * I->price);
						find = 1;
					}
				}//Ako nije našao
				if (find == 0) {//Postavi novi element u listu svih proizvoda
					itemValuePosition item = (itemValuePosition)malloc(sizeof(ItemValue));
					if (item == NULL) {
						return -1;
					}
					strcpy(item->name, I->name);
					item->price = (I->amount * I->price);
					item->Next = P1->Next;
					P1->Next = item;
				}
				find = 0;
				//Vrati se na početak liste svih proizvoda
				P1 = StartingItem;
			}
		}
	}
	return 0;
}
int printFilteredBill(billPosition P,int id) {
	while (P != NULL) {//Prolaz svim računima
		if (id == P->id) {//Ako je id računa jednak id traženog računa
			printf("%s %d %d/%d/%d\n", P->billName, P->id, P->date->year, P->date->month, P->date->day);
			itemPosition Q = P->NextItem->Next;
			while (Q != NULL) {//Ispiše sve proizvode računa
				printf("%s %.2f %d\n", Q->name, Q->price, Q->amount);
				Q = Q->Next;

			}
		}
		P = P->NextBill;
	}
	return 0;
}
int smallestBill(billPosition Start) {
	billPosition P = Start;
	//min postaje profit prvog računa
	float min = profitBill(P->NextItem);
	int id = P->id;
	while (P != NULL) {
		//Ako je min veći od profita računa min postaje profit tog računa i zabilježi se id
		if (min > profitBill(P->NextItem)) {
			min = profitBill(P->NextItem);
			id = P->id;
		}
		P = P->NextBill;
	}
	P = Start;
	//Poziva f koja ce ispisati taj racun
	printFilteredBill(P,id);//Ispiši profit
	printf("\nBill made %.2f$\n", min);
	return 0;
}
int biggestBill(billPosition Start) {
	billPosition P = Start;
	//max postaje profit prvog računa
	float max= profitBill(P->NextItem);
	int id = P->id;
	while (P != NULL) {
		//Ako je max manji od profita računa min postaje profit tog računa i zabilježi se id
		if (max < profitBill(P->NextItem)) {
			max = profitBill(P->NextItem);
			id = P->id;
		}
		P = P->NextBill;
	}
	P = Start;
	//Poziva f koja ce ispisati taj racun
	printFilteredBill(P, id);//Ispiši profit
	printf("\nBill made %.2f$\n", max);
	return 0;
}
int profitBill(itemPosition Start) {
	//Postavlja pokazivac na prvi proizvod
	itemPosition P = Start->Next;
	float profit = 0.0;

	while (P != NULL) {//Racuna sumu svih profita proizvoda
		profit = profit + P->price*P->amount;
		P = P->Next;
	}
	//Vraca vrijednost profita određenog računa
	return profit;
}
int profit(itemValuePosition Start) {
	//Postavlja pokazivac na prvi proizvod
	itemValuePosition P = Start->Next;
	float profit = 0.0;
	
	while (P != NULL) {//Racuna profit svih proizvoda u listi proizvoda
		profit = profit + P->price;
		P = P->Next;
	}
	//Ispiši profit
	printf("Our profit is: %.2f$\n", profit);

	P = Start;
	//Briše listu svih proizvoda
	deleteItem(P);
	return 0;
}
int deleteBills(billPosition Start) {
	billPosition B = Start;
	billPosition temp;
	//Prolaz svim računima
	while (B->NextBill != NULL) {
		itemPosition Q = B;
		itemPosition tempItem;
		while (Q->Next != NULL) {//Izbriši sve proizvode
			tempItem = Q->Next;
			Q->Next = tempItem->Next;
			tempItem->Next = NULL;
			free(tempItem);

		}
		//Izbriši datum računa
		B->date = NULL;
		//Izbriši račun
		temp = B->NextBill;
		B->NextBill = temp->NextBill;
		temp->NextBill = NULL;
		free(temp);
	}
	return 0;
}
int deleteItem(itemValuePosition Start) {//Za listu proizvoda
	itemValuePosition B = Start;
	itemValuePosition temp;
	//Prolaz listom Brijsanje od naprid
	while (B->Next != NULL) {
		//Postavi temp na sljedeći el
		temp = B->Next;
		//Iz liste je izbačen temp
		B->Next = temp->Next;
		//temp pokazuje na NULL
		temp->Next = NULL;
		//Izbriši
		free(temp);
	}
	return 0;
}

int itemValuePeriod(itemValuePosition Start,char *g) {
	itemValuePosition P = Start->Next;
	float max = P->price;
	int found = 0;
	//Prođi listu svih proizvoda
	while (P != NULL) {//Ako je nasao proizvod koji je korisnik upisao
		if (strcmp(g, P->name) == 0) {
			max = P->price;
			found = 1;
			break;
		}
		P = P->Next;
	}
	//Ako je pronasao proizvod ispisi koliko je proizvod zaradio
	if (found == 1) {
		printf("In that Period %s made: %.2f$\n", g, max);
	}
	else {//Ako nije
		printf("That item didn't make any money, if it even exists\n");
	}
	//Izbrisi listu proizvoda
	P = Start;
	deleteItem(P);
	return 0;
}
int itemMinValued(itemValuePosition Start) {
	//Preskoci head
	itemValuePosition P = Start->Next;
	//Postavi min na 1. el liste proizvoda
	float min = P->price;
	char* name = malloc(sizeof(char) * 20);
	strcpy(name, P->name);
	while (P != NULL) {
		//Ako je min veci od P->price
		if (min > P->price) {
			//novi min i zapamti ime
			min = P->price;
			strcpy(name, P->name);
		}
		P = P->Next;
	}//Ispisi proizvod
	printf("Item that made the least amount of money is: %s,%.2f$\n", name, min);
	//Izbrisi listu proizvoda
	P = Start;
	deleteItem(P);
	return 0;
}
int itemMaxValued(itemValuePosition Start) {
	itemValuePosition P = Start->Next;	//Preskoci head
	//Postavi max na 1. el liste proizvoda
	float max = P->price;
	char* name = malloc(sizeof(char) * 20);
	strcpy(name, P->name);
	//Prolaz listom proizvoda
	while (P != NULL) {//Ako je max manji od P->price
		if (max < P->price) {//novi max i zapamti ime
			max = P->price;
			strcpy(name, P->name);
		}
		P = P->Next;
	}//Ispisi proizvod
	printf("Item that made the most money is: %s,%.2f$\n", name, max);
	//Izbrisi listu proizvoda
	P = Start;
	deleteItem(P);
	return 0;
}
int outTest(itemValuePosition Start) {
	//Preskoci head
	itemValuePosition B = Start->Next;
	//Prođi listom svih proizvoda
	while (B != NULL) {//ispiši ime i zaradu
		printf("%s %.2f\n", B->name, B->price);
		B = B->Next;
		printf("\n");
	}
	//Pozovi funkciju za brisanje liste svih proizvoda
	B = Start;
	deleteItem(B);
	return 0;
}
int out(billPosition Start) {
	if (Start == NULL) {
		printf("Sve obrisano");
		return 0;
	}
	billPosition B = Start;
	//Prolaz listom racuna
	while (B != NULL) {//Ispisi ime,id i datum racuna
		printf("%s Id=%d %d/%d/%d\n", B->billName,B->id,B->date->year,B->date->month,B->date->day);
		itemPosition Q = B->NextItem->Next;//Preskoci head pokazivaca na proizvode racuna
		while (Q != NULL) {//Ispisi sve proizvode cijenu i kolicinu
			printf("%s %.2f %d\n", Q->name,Q->price,Q->amount);
			Q = Q->Next;
		}//Preskoci red osim ako je zadnji racun u listi
		if (B->NextBill != NULL)
			printf("\n");
		B = B->NextBill;
	}
	return 0;
}
int maxValue(billPosition Start, itemValuePosition StartingItem,int limit) {
	billPosition P = Start;
	//Pokazivac na listu svih proizvoda
	itemValuePosition P1 = StartingItem;
	int year, month, day;
	int year2, month2, day2;
	int find = 0;
	if (limit == 1) {//Ako je limit 1 onda ce uzeti u obzir samo racune koji su između datuma
		printf("Unesi datum od(pr. godina mjesec dan): ");
		scanf("%d %d %d", &year, &month, &day);
		//Provjera je li upisan datum odgovara
		if (year > 2026 || year < 0) {return -1;}
		if (month > 12 || month < 0) {return -1;}
		if (day > 31 || day < 0) {return -1;}

		printf("Unesi datum do(pr. godina mjesec dan): ");
		scanf("%d %d %d", &year2, &month2, &day2);

		if (year2 > 2026 || year2 < 0) {return -1;}
		if (month2 > 12 || month2 < 0) {return -1;}
		if (day2 > 31 || day2 < 0) {return -1;}
	}
	//Prolaz svih računima
	for (P = Start->NextBill; P != NULL; P = P->NextBill) {
		//Provjera je li treba uzeti u obzir datume ili ne
		if (limit == 0 || dateBetween(P->date, year, month, day, year2, month2, day2)) {
			//Preskoci head od pokazivaca proizvoda 1 racuna
			itemPosition I = P->NextItem;
			//Prođi sve proizvode 1 racuna
			for (I = P->NextItem->Next; I != NULL; I = I->Next) {
				while (P1->Next != NULL) {
					P1 = P1->Next;
					//Ako je proizvod upisan u listu svih proizvoda
					if (strcmp(P1->name, I->name) == 0) {
						//Izracunaj zaradu proizvoda
						P1->price = P1->price + (I->amount * I->price);
						find = 1;
					}
				}//Ako nije proizvod upisan u listu svih proizvoda
				if (find == 0) {//Dodaj novi element u listu svih proizvoda
					itemValuePosition item = (itemValuePosition)malloc(sizeof(ItemValue));
					if (item == NULL) {
						return -1;
					}
					//Postavi mu vrijednosti tj. zaradu i ime
					strcpy(item->name, I->name);
					item->price = (I->amount * I->price);
					item->Next = P1->Next;
					P1->Next = item;
				}
				//resetiraj find
				find = 0;
				//Vrati pokazivac liste svih proizvoda na pocetak
				P1 = StartingItem;
			}
		}
		
	}
	return 0;
}
int dateBetween(Date* d, int y1, int m1, int day1, int y2, int m2, int day2) {
	//Provjera je li datum od računa na pokazivacu *d manji od unesenog
	//Ako je taj racun se nece racunati tj. vratiti ce 0
	if (d->year < y1) 
		return 0;
	if (d->year == y1) {
		if (d->month < m1) 
			return 0;
		if (d->month == m1 && d->day < day1) 
			return 0;
	}
	//Provjera je li datum od računa na pokazivacu *d veci od unesenog
	//Ako je taj racun se nece racunati tj. vratiti ce 0
	if (d->year > y2) 
		return 0;
	if (d->year == y2) {
		if (d->month > m2) 
			return 0;
		if (d->month == m2 && d->day > day2) 
			return 0;
	}
	//Inace vraca 1 jer je datum između druga 2 datuma
	return 1;
}
int loadBills(billPosition Start) {
	//Otvara FILE
	FILE* read = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Vjezba6\\racuni.txt","r");
	if (read == NULL) {
		return -1;
	}
	billPosition P = Start;
	//Brojac racuna
	int i = 0;
	//Varijabla c koja ce imati zapisan link do datoteke racuna
	char* c = (char*)malloc(100 * sizeof(char));
	//Prolazi file-om
	while (feof(read) == 0) {

		billPosition Q = (billPosition)malloc(sizeof(Bill));
		if (Q == NULL) {
			return -1;
		}
		//Alocira memo za pokazivace datum i proizvoda 
		Q->date = malloc(sizeof(Date));
		Q->NextItem = malloc(sizeof(Item));
		Q->NextItem->Next = NULL;
		//Postavlja id na vrijednost koji je po redu upisan
		Q->id = i+1;
		strcpy(Q->billName, "Racun");
		//
		fscanf(read, "%s", c);
		//Pošalji glavu racuna i ucitaj sve proizvode u taj racun
		loadItems(Q,Q->NextItem,c);
		//Sortirani unos po datumu 
		//i>0 jer sortirani unos neradi ako nema nicega u listi tj. nema provjere datuma
		if (i > 0) {
			//Sortirani unos racuna po datumu
			for (P = Start; P->NextBill != NULL; P = P->NextBill) {
				if (Q->date->year > P->NextBill->date->year) {
					break;
				}
				else if (Q->date->year == P->NextBill->date->year) {
					if (Q->date->month > P->NextBill->date->month) {
						break;
					}
					else if (Q->date->month < P->NextBill->date->month) {
						P= P->NextBill;
						break;
					}
					else {
						if (Q->date->day > P->NextBill->date->day) {
							break;
						}
						else if (Q->date->day <= P->NextBill->date->day) {
							P = P->NextBill;
							break;
						}
					}
				}

			}

		}
		//Postavi racun u listu nakon sto mu je pronađeno mjesto u listi
		Q->NextBill = P->NextBill;
		P->NextBill = Q;
		//Povecaj brojac
		i++;
		
	}
	fclose(read);
	free(c);
	return 0;
}
int loadItems(billPosition Q,itemPosition Start,char *c) {
	itemPosition P = Start;
	//Otvori file sa racunom
	FILE* read2 = fopen(c, "r");

	char* y = malloc(sizeof(char) * 5);
	//Uzimi godinu i stavi ju u string
	fscanf(read2, "%4s", y);
	//atoi(y) pretvara string u int
	Q->date->year = atoi(y);

	//Preskoci znak /
	char* dum = malloc(sizeof(char) * 2);
	fscanf(read2, "%1s", dum);

	char* m = malloc(sizeof(char) * 3);
	//Uzimi mjesec i stavi ju u string
	fscanf(read2, "%2s", m);
	//atoi(m) pretvara string u int
	Q->date->month = atoi(m);

	//Preskoci znak /
	fscanf(read2, "%1s", dum);

	char* d = malloc(sizeof(char) * 3);
	//Uzimi mjesec i stavi ju u string
	fscanf(read2, "%2s", d);
	//atoi(d) pretvara string u int
	Q->date->day = atoi(d);

	//Nakon sto je proslo 1. red 

	while (feof(read2) == 0) {
		itemPosition QItem = (itemPosition)malloc(sizeof(Item));
		if (QItem == NULL) {
			return -1;
		}
		char* temp = malloc(sizeof(char) * 10);
		fscanf(read2, "%s", temp);
		//Sortirani unos proizvoda
		for (P=Start; P->Next != NULL; P = P->Next) {
			//Ako je ime proizvoda manje od imena proizvoda u listi izađi, jer je našlo mjesto u listi
			if (strcmp(temp, P->Next->name)<0) {
				break;
			}
		}
		//Postavlja ga u listu proizvoda 1 racuna
		QItem->Next =P->Next;
		P->Next = QItem;
		//Daje mu ime i cijenu i kolicinu
		strcpy(QItem->name, temp);


		fscanf(read2, "%s", temp);
		//atoi string -> int
		QItem->amount = atoi(temp);


		fscanf(read2, "%s", temp);
		//Atof pretvara string u float
		QItem->price = atof(temp);


	}
	fclose(read2);
	free(y);
	free(dum);
	free(m);
	free(d);
	return 0;
}