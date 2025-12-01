#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
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

int loadBills(billPosition);
int loadItems(billPosition, itemPosition, char*);
int out(billPosition);

int main() {
	Bill Head={"",NULL,NULL,NULL};
	loadBills(&Head);
	int active = 1;
	ItemValue ItemHead = { "",0.0,NULL };
	
	char input;
	
	while (active == 1) {
		printf("Welcome! Press:\n");
		printf("[A] to see all bills [B] to see how much money all the items made\n");
		printf("[C] to check how much money item made in certain period [D] to see item that made the most money\n");
		printf("[X] to exit\n");
		input = getchar();
		input = toupper(input);
		switch (input) {
		case'A':
			out(Head.NextBill);
			break;
		case'B':
			maxValue(&Head, &ItemHead, 0);
			outTest(&ItemHead);
			break;
		case'C':
			maxValue(&Head, &ItemHead, 1);
			char* name = malloc(sizeof(char) * 20);
			printf("What item: ");
			scanf("%s", name);
			itemValuePeriod(&ItemHead, name);
			outTest(&ItemHead);
			break;
		case'X':
			active = 0;
			break;
		}
	}
	
	/*printf("\n");

	
	itemMaxValued(&ItemHead);
	printf("\n");
	

	maxValue(&Head, &ItemHead, 1);
	
	itemMaxValued(&ItemHead);
	
	printf("\n");
	outTest(&ItemHead);*/
	
	//main();
	return 0;
}
int itemValuePeriod(itemValuePosition Start,char *g) {
	itemValuePosition P = Start->Next;
	float max = P->price;

	while (P != NULL) {
		if (strcmp(g, P->name) == 0) {
			max = P->price;
			break;
		}
		P = P->Next;
	}
	printf("In that Period %s made: %.2f$\n", g, max);
	return 0;
}
int itemMaxValued(itemValuePosition Start) {
	itemValuePosition P = Start->Next;
	float max = P->price;
	char* name = malloc(sizeof(char) * 20);
	while (P!= NULL) {
		if (max < P->price) {
			max = P->price;
			strcpy(name, P->name);
		}
		P = P->Next;
	}
	printf("Item that made the most money is: %s,%.2f$\n", name, max);
	return 0;
}
int outTest(itemValuePosition Start) {
	itemValuePosition B = Start->Next;

	while (B != NULL) {
		printf("%s %f\n", B->name, B->price);
		
		B = B->Next;
		printf("\n");
	}
	B = Start;
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
int out(billPosition Start) {
	billPosition B = Start;
	
	while (B != NULL) {
		printf("%s %d/%d/%d\n", B->billName,B->date->year,B->date->month,B->date->day);
		itemPosition Q = B->NextItem->Next;
		while (Q != NULL) {
			printf("%s %f %d\n", Q->name,Q->price,Q->amount);
			Q = Q->Next;

		}
		B = B->NextBill;
		printf("\n");
	}
	return 0;
}

int maxValue(billPosition Start, itemValuePosition StartingItem,int limit) {
	billPosition P = Start;
	itemValuePosition P1 = StartingItem;
	int year, month, day;
	int year2, month2, day2;
	int find = 0;
	if (limit == 1) {
		printf("Unesi datum od(pr. godina mjesec dan): ");
		scanf("%d %d %d", &year, &month, &day);

		if (year > 2026 || year < 0) {return -1;}
		if (month > 12 || month < 0) {return -1;}
		if (day > 31 || day < 0) {return -1;}

		printf("Unesi datum do(pr. godina mjesec dan): ");
		scanf("%d %d %d", &year2, &month2, &day2);

		if (year2 > 2026 || year2 < 0) {return -1;}
		if (month2 > 12 || month2 < 0) {return -1;}
		if (day2 > 31 || day2 < 0) {return -1;}
	}
	
	for (P = Start->NextBill; P != NULL; P = P->NextBill) {
		if (limit == 0 || dateBetween(P->date, year, month, day, year2, month2, day2)) {
			itemPosition I = P->NextItem;
			//printf("%d\n", P->date->year);
			for (I = P->NextItem->Next; I != NULL; I = I->Next) {
				//printf("%s ", I->name);

				while (P1->Next != NULL) {
					P1 = P1->Next;
					if (strcmp(P1->name, I->name) == 0) {
						P1->price = P1->price + (I->amount * I->price);
						find = 1;
					}
				}
				if (find == 0) {
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
				P1 = StartingItem;
			}
		}
		
	}
	return 0;
}
int dateBetween(Date* d, int y1, int m1, int day1, int y2, int m2, int day2) {
	
	if (d->year < y1) 
		return 0;
	if (d->year == y1) {
		if (d->month < m1) 
			return 0;
		if (d->month == m1 && d->day < day1) 
			return 0;
	}

	if (d->year > y2) 
		return 0;
	if (d->year == y2) {
		if (d->month > m2) 
			return 0;
		if (d->month == m2 && d->day > day2) 
			return 0;
	}

	return 1;
}
int loadBills(billPosition Start) {
	FILE* read = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Vjezba6\\racuni.txt","r");
	if (read == NULL) {
		return -1;
	}
	billPosition P = Start;
	int i = 0;
	while (feof(read) == 0) {

		billPosition Q = (billPosition)malloc(sizeof(Bill));
		if (Q == NULL) {
			return -1;
		}
		Q->date = malloc(sizeof(Date));
		Q->NextItem = malloc(sizeof(Item));
		Q->NextItem->Next = NULL;
	
		strcpy(Q->billName, "Racun");

		char* c = (char*)malloc(100 * sizeof(char));
		fscanf(read, "%s", c);
		loadItems(Q,Q->NextItem,c);
		if (i > 0) {
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
		
		Q->NextBill = P->NextBill;
		P->NextBill = Q;
		i++;
		//printf("\n");

	}
	fclose(read);
	return 0;
}
int loadItems(billPosition Q,itemPosition Start,char *c) {
	itemPosition P = Start;

	FILE* read2 = fopen(c, "r");




	char* y = malloc(sizeof(char) * 5);
	fscanf(read2, "%4s", y);
	Q->date->year = atoi(y);
	//printf("%d", Q->date->year);

	char* dum = malloc(sizeof(char) * 2);
	fscanf(read2, "%1s", dum);

	char* m = malloc(sizeof(char) * 3);
	fscanf(read2, "%2s", m);
	Q->date->month = atoi(m);
	//printf(" %d", Q->date->month);

	fscanf(read2, "%1s", dum);

	char* d = malloc(sizeof(char) * 3);
	fscanf(read2, "%2s", d);
	Q->date->day = atoi(d);
	//printf(" %d", Q->date->day);



	while (feof(read2) == 0) {


		itemPosition QItem = (itemPosition)malloc(sizeof(Item));
		if (QItem == NULL) {
			return -1;
		}
		char* temp = malloc(sizeof(char) * 10);
		fscanf(read2, "%s", temp);

		for (P=Start; P->Next != NULL; P = P->Next) {
			if (strcmp(temp, P->Next->name)<0) {
				break;
			}
		}
		QItem->Next =P->Next;
		P->Next = QItem;
		strcpy(QItem->name, temp);
		//printf(" %s", QItem->name);


		fscanf(read2, "%s", temp);
		QItem->amount = atoi(temp);
		//printf(" %d", QItem->amount);

		fscanf(read2, "%s", temp);
		QItem->price = atof(temp);
		//printf(" %.2f", QItem->price);

	}
	fclose(read2);
	return 0;
}