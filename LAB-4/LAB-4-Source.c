#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

struct employee {
	int cipher;
	char* surname;
	int flag;
	union {
		char startDate[13];
		int salary;
	};
	employee* adress; // поле адреса
};

void push(employee**);
void view(employee*);
void find(employee* stTop);
void del(employee** s, int n);
void saveToFile(employee* stTop);
void copy(employee** reverse, employee* s);
void importFromFile(employee**);

int main() {
	employee* stTop = nullptr; // указатель на вершину стека
	char input;
	int num = 0;
	while (1) {
		system("CLS");
		printf("Operation\n");
		printf("1 - create/add\n");
		printf("2 - view\n");
		printf("3 - delete\n");
		printf("4 - find\n");
		printf("5 - save to .txt-.bin\n");
		printf("6 - load from .txt-.bin\n");
		printf("0 - end program\n");
		printf("-------------------\n");
		fflush(stdin);
		input = _getch();
		switch (input) {
		case '1': push(&stTop); break;
		case '2': view(stTop); break;
		case '3':
			if (stTop) {
				view(stTop);
				printf("\nInput number you want delete: ");
				scanf_s("%d", &num);
				del(&stTop, num-1);
				printf("Succesfully delete!");
			}
			else printf("Stack is empty!");
			break;
		case '4': find(stTop); break;
		case '5': saveToFile(stTop); break;
		case '6': importFromFile(&stTop); break;
		case '0': return 0;
		default: 
			printf("\nIncorrect input, Try again!\n");
			Sleep(500);
		}
	}
	return 0;
}

void push(employee** stTop) { // функция cоздания/добавления в стек
	employee* newEl = *stTop;
	char unionSwitch;
	do {
		if (!(*stTop = (employee*)calloc(1, sizeof(employee)))) {
			printf("\nNo Memory allocated!\n");
			Sleep(500);
			return;
		}
		printf("Input cipher: ");
		do {
			rewind(stdin);
		} while (!scanf_s("%d", &(*stTop)->cipher));
		printf("Input surname: ");
		rewind(stdin);
		(*stTop)->surname = (char*)calloc(30, sizeof(char));
		gets_s((*stTop)->surname,30);
		printf("Press '1' for input Start date - ");
		printf("Press '2' for input Salary");
		unionSwitch = _getch();
		switch (unionSwitch) {
		case '1': 			
			(*stTop)->flag = 0;
			printf("\nInput date like '20.08.2002': ");
			rewind(stdin);
			gets_s((*stTop)->startDate);
			break;
		case '2': 
			(*stTop)->flag = 1;
			printf("\nInput salary: ");
			do {
				rewind(stdin);
			} while (!scanf_s("%d", &(*stTop)->salary));
			break;
		default: printf("\nIncorrect input, Try again!\n");
		}
		(*stTop)->adress = newEl;              // новый эл-т стека "ссылается" на элемент вершину стека
		newEl = *stTop;                       // новый элемент становится вершиной стека
		printf("\nProceed?('y' = yes/'n' = no)\n\n");
		fflush(stdin);
	} while (_getch() == 'y');
}

void view(employee* stTop) {  // функция просмотра элементов стека
	if (!stTop) {
		puts("\nStack is empty! Add elements!");
		Sleep(500);
		return;
	}
	int id = 1;
	printf("\nid\b\tCipher\t|\tSurname \t|\tUnion\n");
	printf("------------------------------------------------------------------\n");
	do {
		printf("%d\t%d\t|\t%s  \t|", id, stTop->cipher, stTop->surname);
			if (stTop->flag == 0) 
				printf("\t%s - job enter date\n", stTop->startDate);
			else printf("\t%d - salary\n", stTop->salary);
		stTop = stTop->adress;
		id++;
	} while (stTop);
	_getch();
}

void find(employee* stTop) { // функция поиска элемента по параметру в стэке
	char switcher;
	char symbols[30] = "";
	int searchNum;
	int searchFlag = 0;
	if (!stTop) {
		puts("\nStack is empty! Add elements!");
		Sleep(500);
		return;
	}
	printf("\n1 - find by Cipher\n");
	printf("2 - find by Surname\n");
	printf("3 - find by Start date\n");
	printf("4 - find by Salary\n");
	switcher = _getch();
	switch (switcher) {
	case '1':
		printf("Input cipher id: ");
		do {
			rewind(stdin);
		} while (!scanf_s("%d", &searchNum));
		do {
			if (searchNum == stTop->cipher) {
				printf("%d\t|\t%s  \t|", stTop->cipher, stTop->surname);
				if (stTop->flag == 0)
					printf("\t%s - job enter date\n", stTop->startDate);
				else
					printf("\t%d - salary\n", stTop->salary);
				searchFlag++;
			}
			stTop = stTop->adress;
		} while (stTop);
		break;
	case '2':		
		printf("Input surname: ");
		rewind(stdin);
		gets_s(symbols);
		do {
			if (_strcmpi(symbols, stTop->surname) == 0) {
				printf("%d\t|\t%s  \t|", stTop->cipher, stTop->surname);
				if (stTop->flag == 0)
					printf("\t%s - job enter date\n", stTop->startDate);
				else
					printf("\t%d - salary\n", stTop->salary);
				searchFlag++;
			}
			stTop = stTop->adress;
		} while (stTop);
		break;
	case '3':
		printf("Input start date: ");
		rewind(stdin);
		gets_s(symbols);
		do {
			if (_strcmpi(symbols, stTop->startDate) == 0) {
				printf("%d\t|\t%s  \t|", stTop->cipher, stTop->surname);
				if (stTop->flag == 0)
					printf("\t%s - job enter date\n", stTop->startDate);
				else
					printf("\t%d - salary\n", stTop->salary);
				searchFlag++;
			}
			stTop = stTop->adress;
		} while (stTop);
		break;
	case '4':
		printf("Input salary id: ");
		do {
			rewind(stdin);
		} while (!scanf_s("%d", &searchNum));
		do {
			if (searchNum == stTop->salary) {
				printf("%d\t|\t%s  \t|", stTop->cipher, stTop->surname);
				if (stTop->flag == 0)
					printf("\t%s - job enter date\n", stTop->startDate);
				else 
					printf("\t%d - salary\n", stTop->salary);
				searchFlag++;
			}
			stTop = stTop->adress;
		} while (stTop);
		break;
	default: printf("\nIncorrect input, Try again!\n");
	}
	if (searchFlag == 0) printf("No matches found!\n");
	_getch();
}

void del(employee** s, int n) {
	employee* ptr, * buff;
	ptr = *s;
	buff = (*s)->adress;
	int i = 1;
	while (1) {
		if (n == 0) {
			(*s) = (*s)->adress;
			free(ptr->surname);
			free(ptr);
			return;
		}
		else if (n == i) {
			if (!((buff)->adress)) {
				(ptr)->adress = buff->adress;
				free(buff->surname);
				free(buff);
				return;
			}
			(ptr)->adress = buff->adress;
			free(buff->surname);
			free(buff);
			return;
		}
		if (!buff->adress) {
			printf("Find eroror\n");
			return;
		}
		ptr = ptr->adress;
		buff = (buff)->adress;
		i++;
	}
}

void saveToFile(employee* stTop) { // функция просмотра элементов стека
	if (!stTop) {
		puts("\nStack is empty! Add elements!");
		Sleep(500);
		return;
	}
	FILE* f;
	employee* reverse = nullptr;
	copy(&reverse, stTop);
	char input;
	printf("'1' - save to txt\n");
	printf("'2' - save to bin\n");
	fflush(stdin);
	input = _getch();
	switch (input) {
		case '1':
			if ((f = fopen("Save.txt", "w")) == NULL) {
				printf("Can't open file. Try Again!");
				Sleep(500);
				return;
			}
			do {
				fprintf(f, "%d\t\t%s  \t", reverse->cipher, reverse->surname);
				if (reverse->flag == 0)
					fprintf(f, "\t%s\n", reverse->startDate);
				else
					fprintf(f, "\t%d\n", reverse->salary);
				reverse = reverse->adress;
			} while (reverse);
			fclose(f);
			break;
		case '2': 
			if ((f = fopen("Save.bin", "wb")) == NULL) {
				printf("Can't open file. Try Again!");
				Sleep(500);
				return;
			}
			do {
				fprintf(f, "%d\t\t%s  \t", reverse->cipher, reverse->surname);
				if (reverse->flag == 0)
					fprintf(f, "\t%s\n", reverse->startDate);
				else
					fprintf(f, "\t%d\n", reverse->salary);
				reverse = reverse->adress;
			} while (reverse);
			fclose(f);
			break;
	}
	printf("Succesfully save!");
	_getch();
}

void copy(employee** reverse, employee* s) {
	employee* stTop = *reverse;
	while (1) {
		if (!(*reverse = (employee*)calloc(1, sizeof(employee)))) {
			printf("Memory read error!\n");
			break;
		}
		(*reverse)->cipher = s->cipher;
		(*reverse)->surname = (char*)calloc(30, sizeof(char));
		strcpy((*reverse)->surname, s->surname);
		(*reverse)->flag = s->flag;
		if ((*reverse)->flag == 0) {
			strcpy((*reverse)->startDate, s->startDate);
		}
		else {
			(*reverse)->salary = s->salary;
		}
		(*reverse)->adress = stTop;
		stTop = *reverse;
		if (!s->adress) {
			break;
		}
		s = s->adress;
	}
}

void importFromFile(employee** stTop) {
	FILE* f;
	employee* newEl = *stTop;
	int i,len, num = 0, numBuf = 0, dozens = 1;
	char buffer[12];
	char surnameBuf[20];
	int scanBuf = 0;
	char input;
	char fileName[20];
	printf("'1' - Import from txt\n");
	printf("'2' - Import from bin\n");
	fflush(stdin);
	input = _getch();
	switch (input) {
		case '1': 
			printf("Input filename.txt: ");
			rewind(stdin);
			gets_s(fileName);
			if ((f = fopen(fileName, "r")) == NULL) {
				printf("Can't open file. Try Again!");
				Sleep(500);
				return;
			}
			if (!(*stTop = (employee*)calloc(1, sizeof(employee)))) {  // указатель на новый элемент стека
				printf("\nNo Memory allocated!\n");
				Sleep(500);
				return;
			}
			while (fscanf(f, "%d %s %s", &scanBuf, surnameBuf, buffer) != EOF) {
				if (!(*stTop = (employee*)calloc(1, sizeof(employee)))) {  // указатель на новый элемент стека
					printf("\nNo Memory allocated!\n");
					Sleep(500);
					return;
				}
				(*stTop)->cipher = scanBuf;
				(*stTop)->surname = (char*)calloc(30, sizeof(char));
				for (i = 0; surnameBuf[i] != '\0'; i++) {
					(*stTop)->surname[i] = surnameBuf[i];
				}
				(*stTop)->startDate[i] = '\0';
				len = strlen(buffer);
				if (len < 9) {
					(*stTop)->flag = 1;
					for (i = len; i > 0; i--) {
						numBuf = buffer[i - 1] - '0';
						numBuf *= dozens;
						dozens *= 10;
						num += numBuf;
					}
					(*stTop)->salary = num;
					dozens = 1; num = 0;
				}
				else {
					(*stTop)->flag = 0;
					for (i = 0; buffer[i] != '\0'; i++) {
						(*stTop)->startDate[i] = buffer[i];
					}
					(*stTop)->startDate[i] = '\0';
				}
				(*stTop)->adress = newEl;              
				newEl = *stTop;    
			}
			break;
		case '2': 
			printf("Input filename.bin: ");
			rewind(stdin);
			gets_s(fileName);
			if ((f = fopen(fileName, "rb")) == NULL) {
				printf("Can't open file. Try Again!");
				Sleep(500);
				return;
			}
			if (!(*stTop = (employee*)calloc(1, sizeof(employee)))) {  // указатель на новый элемент стека
				printf("\nNo Memory allocated!\n");
				Sleep(500);
				return;
			}
			while (fscanf(f, "%d %s %s", &scanBuf, surnameBuf, buffer) != EOF) {
				if (!(*stTop = (employee*)calloc(1, sizeof(employee)))) {  // указатель на новый элемент стека
					printf("\nNo Memory allocated!\n");
					Sleep(500);
					return;
				}
				(*stTop)->cipher = scanBuf;
				(*stTop)->surname = (char*)calloc(30, sizeof(char));
				for (i = 0; surnameBuf[i] != '\0'; i++) {
					(*stTop)->surname[i] = surnameBuf[i];
				}
				(*stTop)->startDate[i] = '\0';
				len = strlen(buffer);
				if (len < 9) {
					(*stTop)->flag = 1;
					for (i = len; i > 0; i--) {
						numBuf = buffer[i - 1] - '0';
						numBuf *= dozens;
						dozens *= 10;
						num += numBuf;
					}
					(*stTop)->salary = num;
					dozens = 1; num = 0;
				}
				else {
					(*stTop)->flag = 0;
					for (i = 0; buffer[i] != '\0'; i++) {
						(*stTop)->startDate[i] = buffer[i];
					}
					(*stTop)->startDate[i] = '\0';
				}
				(*stTop)->adress = newEl;
				newEl = *stTop;
			}
			break;
	}
	printf("Succesfully write to stack!");
	_getch();
}