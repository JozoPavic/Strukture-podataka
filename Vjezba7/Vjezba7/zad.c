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
	addDir(&headDirectory, &headStack);
	addDir(&headDirectory, &headStack);
	int active = 1;
	cdTT(&headStack);
	int input = 0;
	char* command = malloc(sizeof(char) * 7);
	char *name = malloc(sizeof(char) * N);
	while (active) {
		if (headStack.Next == NULL) {
			GoBack(headDirectory.Next,&headStack);
		}
		else {
			printf("Upisi: mkdir | cd | cd.. | dir | EXIT");
			printf("\n%s> ", headStack.Next->dirLevel->ime);
			scanf("%s", command);
			if (strcmp(command, "mkdir") == 0) {
				scanf("%s", name);
				mkdir(headStack.Next->dirLevel, name);
				system("cls");
			}
			else if (strcmp(command, "cd") == 0) {
				scanf("%s", name);
				cd(headStack.Next->dirLevel, &headStack, name);
				system("cls");
			}
			else if (strcmp(command, "cd..") == 0) {
				cdTT(&headStack);
				system("cls");
			}
			else if (strcmp(command, "dir") == 0) {
				system("cls");
				dir(headStack.Next->dirLevel);
			}
			else if (strcmp(command, "EXIT") == 0) {
				out(headDirectory.Next);
				delete(&headDirectory);
				deleteStack(&headStack);
				out(headDirectory.Next);
				active = 0;

			}
			else {
				system("cls");
			}
		}
	}

	return 0;
}
int GoBack(dirPosition Start,stackPosition StackStart) {
	dirPosition P = Start;
	while (P != NULL) {
		printf("%s\n", P->ime);
		P = P->Next;
	}
	int found = 0;
	P = Start;
	while (found == 0) {
		printf("U koji disk ces se vratiti: ");
		char* input = malloc(sizeof(char) * N);
		scanf("%s", input);
		while (P != NULL) {
			if (strcmp(input, P->ime)==0) {
				found = 1;
				push(StackStart,P);
				break;
			}
			P = P->Next;
		}

	}
	
	return 0;
}
int deleteStack(stackPosition Start) {
	stackPosition temp;
	while (Start->Next != NULL) {

		temp = Start->Next;
		Start->Next = temp->Next;
		temp->Next = NULL;
		free(temp);
	}
	return 0;
}
int delete(dirPosition Start) {
	dirPosition temp;
	while (Start->Next != NULL) {
		
		deleteChild(Start->subDirPosition);
		temp = Start->Next;
		Start->Next = temp->Next;
		temp->Next = NULL;
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
	if (current->subDirPosition != NULL) {

		currentSub = current->subDirPosition;
		while (currentSub != NULL) {
			deleteChild(currentSub);
			temp = currentSub->Next;
			currentSub->Next = temp->Next;
			temp->Next = NULL;
			free(temp);
		}
	}
	return 0;
}
int mkdir( dirPosition P,char *input) {

	dirPosition Parent = P;
	dirPosition newEl = (dirPosition)malloc(sizeof(Directory));
	if (newEl == NULL) {
		return -1;
	}
	strcpy(newEl->ime, input);
	newEl->Next = Parent->subDirPosition;
	newEl->subDirPosition = NULL;
	Parent->subDirPosition = newEl;

	return 0;
}
int out(dirPosition Start) {
	if (Start == NULL) {
		printf("Obrisano je");
		return 0;
	}
	while (Start != NULL) {
		printf("%s\n", Start->ime);
		dir(Start);
		Start = Start->Next;
	}
	return 0;
}
int dir(dirPosition current) {
	int index = 1;
	dirPosition currentSub = NULL;
	if (current->subDirPosition != NULL) {	
		currentSub = current->subDirPosition;
		while (currentSub != NULL) {
			printf("%d%s\n", index,currentSub->ime);
			index++;
			dir(currentSub);
			currentSub = currentSub->Next;
		}
	}

	return 0;
}

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
		if (strcmp(input, temp->ime) == 0) {
			push(stack, temp);
			printf("FOUND\n");
			found = 1;
			break;
		}
		temp = temp->Next;
	}
	if (!found) {
		printf("Not FOUND\n");
	}
	return 0;
}
int push(stackPosition StackStart, dirPosition Q) {
	stackPosition P = malloc(sizeof(Stack));
	P->Next = StackStart->Next;
	StackStart->Next = P;
	P->dirLevel = Q;
	return 0;
}

int addDir(dirPosition head, stackPosition stack) {
	dirPosition Start = head;
	stackPosition StackStart = stack;

	dirPosition Q = (dirPosition)malloc(sizeof(Directory));
	if (Q == NULL) {
		return -1;
	}
	printf("Upisi ime diska: ");
	char* p = malloc(sizeof(char) * 10);
	scanf("%s", p);
	strcpy(Q->ime,p);
	while (Start->Next != NULL) {
		Start = Start->Next;
	}
	Q->Next = Start->Next;
	Start->Next = Q;
	Q->subDirPosition = NULL;

	push(StackStart, Q);


	return 0;
}