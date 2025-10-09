#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define N 10
typedef struct {
	char ime[N];
	char prezime[N];
	int bodovi;

}student;
int main() {
	FILE *read = fopen("C:\\Users\\student\\Desktop\\Strukture_JozoPavic\\Prvi.txt", "r");
	if (read == NULL) {
		return 0;
	}
	int rowCounter = 1, maxBrojBodova=100;
	char finder;
	while (feof(read) == 0) {
		finder = fgetc(read);
		if (finder == "\n") {
			rowCounter++;
		}
	}
	fclose(read);

	FILE *read2 = fopen("C:\\Users\\student\\Desktop\\Strukture_JozoPavic\\Prvi.txt", "r");
	student *stu = malloc(rowCounter * sizeof(student));
	int newCounter = 0;
	while (feof(read2) == 0) {
		fscanf(read2, "%s", (stu + newCounter)->ime);
		fscanf(read2, "%s", (stu + newCounter)->prezime);
		fscanf(read2, "%d", &(stu + newCounter)->bodovi);
		newCounter++;
	}
	fclose(read2);

	for (int i = 0; i < newCounter; i++) {
		printf("Ime: %s Prezime: %s Apsolutni Bodovi: %d Relativni Bodovi: %d \n", (stu + i)->ime, (stu + i)->prezime,(stu+i)->bodovi, ((stu + i)->bodovi)/maxBrojBodova*100);
	}
	return 0;
}