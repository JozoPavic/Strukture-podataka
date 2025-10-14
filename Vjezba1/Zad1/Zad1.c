#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define N 10
typedef struct {
	char name[N];
	char lastname[N];
	int point;

}student; 
int rowNum() {
	FILE* read = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Prvi.txt", "r");
	if (read == NULL) {
		return 0;
	}

	int rowCounter = 1;
	char finder;

	while (feof(read) == 0) {
		finder = fgetc(read);
		if (finder == '\n') {
			rowCounter++;
		}
	}
	fclose(read);
	return rowCounter;
}
int loadStudents(student *stu) {
	int newCounter = 0;

	FILE* read2 = fopen("C:\\Users\\YpgCo\\source\\repos\\JozoPavic\\Strukture-podataka\\Prvi.txt", "r");
	if (read2 == NULL) {
		return 0;
	}

	while (feof(read2) == 0) {
		fscanf(read2, "%s", (stu + newCounter)->name);
		fscanf(read2, "%s", (stu + newCounter)->lastname);
		fscanf(read2, "%d", &(stu + newCounter)->point);
		newCounter++;
	}
	fclose(read2);
	return 0;
}

int output(student* stu,int rowCounter) {
	int maxPoints = 100;
	for (int i = 0; i < rowCounter; i++) {
		double relativePoints = (double)(stu + i)->point * maxPoints / 100;

		printf("Ime: %s	Prezime: %s Apsolutni Bodovi: %d Relativni Bodovi: %.2f \n", (stu + i)->name, (stu + i)->lastname, (stu + i)->point, relativePoints);
	}
	return 0;
}
int main() {
	
	int rowCounter = rowNum();
	student *stu = malloc(rowCounter * sizeof(student));
	
	loadStudents(stu);
	output(stu, rowCounter);
	
	return 0;
}