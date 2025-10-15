#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define N 10
//Struktura student
typedef struct {
	char name[N];
	char lastname[N];
	int point;

}student; 

int rowNum() {
	//Otvaranje File-a i provjera u slucaju greske
	FILE* read = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Prvi.txt", "r");
	if (read == NULL) {
		return 0;
	}
	//rowConter=1 umjesto 0, jer u zadnjem redu ce naici na EOF
	int rowCounter = 1;
	char finder;

	//Prolaz cijelim file-om 
	while (feof(read) == 0) {
		//Sprema trenutni znak
		finder = fgetc(read);
		/*Provjera je li znak '\n' i ako je povecati ce se
		varijabla koja biljezi koliko je redova u File-u*/
		if (finder == '\n') {
			rowCounter++;
		}
	}
	fclose(read);//Zatvaranje file-a
	//Vracam broj redova
	return rowCounter;
}

int loadStudents(student *stu) {
	int newCounter = 0;//index za studente
	//Otvaranje File-a i provjera u slucaju greske
	FILE* read2 = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Prvi.txt", "r");
	if (read2 == NULL) {
		return 0;
	}
	//Prolaz cijelim file-om 
	while (feof(read2) == 0) {
		//Spremanje imena, prezimena i ocjena iz file-a i spremanje u polje
		fscanf(read2, "%s", (stu + newCounter)->name);
		fscanf(read2, "%s", (stu + newCounter)->lastname);
		fscanf(read2, "%d", &(stu + newCounter)->point);
		newCounter++;
	}
	//Zatvaranje file-a
	fclose(read2);
	return 0;
}

int output(student* stu,int rowCounter) {
	int maxPoints = 100;//Koliko je bodova
	//Izvrti cijelo polje i ispise podatke studenata
	for (int i = 0; i < rowCounter; i++) {
		double relativePoints = (double)(stu + i)->point * maxPoints / 100;//Izracun relativnih bodova
		printf("Ime: %s	Prezime: %s Apsolutni Bodovi: %d Relativni Bodovi: %.2f \n", (stu + i)->name, (stu + i)->lastname, (stu + i)->point, relativePoints);
	}
	return 0;
}

int main() {
	//Poziv funkcije da dobijemo broj redova u file-u
	int rowCounter = rowNum();

	//Alociranje memorije pomoću broja redova
	student *stu = malloc(rowCounter * sizeof(student));

	//Učitavanje svih studenata iz file-a u polje
	loadStudents(stu);

	//Ispis 
	output(stu, rowCounter);
	
	return 0;
}