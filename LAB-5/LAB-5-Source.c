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
		char startDate[15];
		int salary;
	};
	employee* adress;
};

void add(employee** head, employee **tail);
void view(employee*);
void del(employee**, employee**, int);
void find(employee*);
void saveToFile(employee*);
void importFromFile(employee**, employee**);

int main() {
	employee *head, *tail;
	head = tail = nullptr;
	char input;
	int num;
	while (1) {
		system("CLS");
		printf("Queue LAB\n");
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
		case '1': add(&head, &tail); break;
		case '2': view(head); break;
		case '3':
			if (head) {
				view(head);
				printf("\nInput number you want delete: ");
				scanf_s("%d", &num);
				del(&head,&tail, num-1);
			}
			else {
				printf("Queue is empty! Add elements!"); 
				Sleep(500);
			}
			break;
		case '4': find(head); break;
		case '5': saveToFile(head); break;
		case '6': importFromFile(&head,&tail); break;
		case '0': return 0;
		default:
			printf("\nIncorrect input, Try again!\n");
			Sleep(500);
		}
	}
	return 0;
}

void add(employee** head, employee **tail) { // функция cоздания/добавления элементов в очередь
	employee* newEl = nullptr;
	char unionSwitch;
	do {
		if (!(newEl = (employee*)calloc(1, sizeof(employee)))) { 
			printf("\nNo Memory allocated!\n");
			Sleep(500);
			return;
		}
		printf("Input cipher: ");
		do {
			rewind(stdin);
		} while (!scanf_s("%d", &newEl->cipher));
		printf("Input surname: ");
		rewind(stdin);
		newEl ->surname = (char*)calloc(30, sizeof(char));
		gets_s((newEl)->surname, 30);
		printf("Press '1' for input Start date - ");
		printf("Press '2' for input Salary");
		unionSwitch = _getch();
		switch (unionSwitch) {
		case '1':
			newEl->flag = 0;
			printf("\nInput date like '20.08.2002': ");
			rewind(stdin);
			gets_s((newEl)->startDate);
			break;
		case '2':
			newEl->flag = 1;
			printf("\nInput salary: ");
			do {
				rewind(stdin);
			} while (!scanf_s("%d", &newEl->salary));
			break;
		default: printf("\nIncorrect input, Try again!\n");
		}
		if (!*head)                       
			*tail = *head = newEl;
		else {							
			(*tail)->adress = newEl; 
			*tail = newEl
		}
		printf("\nProceed?('y' = yes/'n' = no)\n\n");
		fflush(stdin);
	} while (_getch() == 'y');
}

void view(employee* head) { // функция просмотра элементов очереди
	if (!head) {
		puts("Queue is empty! Add elements!");
		Sleep(500);
		return;
	}
	int id = 1;
	printf("\nid\b\tCipher\t|\tSurname \t|\tUnion\n");
	printf("------------------------------------------------------------------\n");
	do {
		printf("%d\t%d\t|\t%s \t|", id, head->cipher, head->surname);
		if (head->flag == 0)
			printf("\t%s - job enter date\n", head->startDate);
		else printf("\t%d - salary\n", head->salary);
		head = head->adress;
		id++;
	} while (head);
	_getch();
}

void del(employee** head, employee** tail, int num) {
	employee* ptr, * buff;
	ptr = *head;
	buff = (*head)->adress;
	int i = 1;
	while (1) {
		if (num == 0) {
			(*head) = (*head)->adress;
			free(ptr->surname);
			free(ptr);
			printf("Succesfully delete!");
			Sleep(500);
			return;
		}
		if (!buff) {
			printf("Error input!");
			Sleep(500);
			return;
		}
		if (num == i) {
			if (!((buff)->adress)) {
				(ptr)->adress = buff->adress;
				free(buff->surname);
				free(buff);
				return;
			}
			(ptr)->adress = buff->adress;
			free(buff->surname);
			free(buff);
			printf("Succesfully delete!");
			Sleep(500);
			return;
		}
		ptr = ptr->adress;
		buff = (buff)->adress;
		i++;
	}
}

void find(employee* head) { // функция поиска элемента по параметру в очереди
	char switcher;
	char symbols[30] = "";
	int searchNum;
	int searchFlag = 0;
	if (!head) {
		puts("Queue is empty! Add elements!");
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
			if (searchNum == head->cipher) {
				printf("%d\t|\t%s \t|", head->cipher, head->surname);
				if (head->flag == 0)
					printf("\t%s - job enter date\n", head->startDate);
				else
					printf("\t%d - salary\n", head->salary);
				searchFlag++;
			}
			head = head->adress;
		} while (head);
		break;
	case '2':
		printf("Input surname: ");
		rewind(stdin);
		gets_s(symbols);
		do {
			if (_strcmpi(symbols, head->surname) == 0) {
				printf("%d\t|\t%s \t|", head->cipher, head->surname);
				if (head->flag == 0)
					printf("\t%s - job enter date\n", head->startDate);
				else
					printf("\t%d - salary\n", head->salary);
				searchFlag++;
			}
			head = head->adress;
		} while (head);
		break;
	case '3':
		printf("Input start date: ");
		rewind(stdin);
		gets_s(symbols);
		do {
			if (_strcmpi(symbols, head->startDate) == 0) {
				printf("%d\t|\t%s \t|", head->cipher, head->surname);
				if (head->flag == 0)
					printf("\t%s - job enter date\n", head->startDate);
				else
					printf("\t%d - salary\n", head->salary);
				searchFlag++;
			}
			head = head->adress;
		} while (head);
		break;
	case '4':
		printf("Input salary id: ");
		do {
			rewind(stdin);
		} while (!scanf_s("%d", &searchNum));
		do {
			if (searchNum == head->salary) {
				printf("%d\t|\t%s \t|", head->cipher, head->surname);
				if (head->flag == 0)
					printf("\t%s - job enter date\n", head->startDate);
				else
					printf("\t%d - salary\n", head->salary);
				searchFlag++;
			}
			head = head->adress;
		} while (head);
		break;
	default: printf("\nIncorrect input, Try again!\n");
	}
	if (searchFlag == 0) printf("No matches found!\n");
	_getch();
}

void saveToFile(employee* head) {
	if (!head) {
		puts("\nQueue is empty! Add elements!");
		Sleep(500);
		return;
	}
	FILE* f;
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
			fprintf(f, "%d\t\t%s \t", head->cipher, head->surname);
			if (head->flag == 0)
				fprintf(f, "\t%s\n", head->startDate);
			else
				fprintf(f, "\t%d\n", head->salary);
			head = head->adress;
		} while (head);
		fclose(f);
		break;
	case '2':
		if ((f = fopen("Save.bin", "wb")) == NULL) {
			printf("Can't open file. Try Again!");
			Sleep(500);
			return;
		}
		do {
			fprintf(f, "%d\t\t%s \t", head->cipher, head->surname);
			if (head->flag == 0)
				fprintf(f, "\t%s\n", head->startDate);
			else
				fprintf(f, "\t%d\n", head->salary);
			head = head->adress;
		} while (head);
		fclose(f);
		break;
	}
	printf("Succesfully save!");
	_getch();
}

void importFromFile(employee** head, employee** tail) {
	FILE* f;
	employee* newEl = nullptr;
	int i, len, num = 0, numBuf = 0, dozens = 1;
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
		if (!(newEl = (employee*)calloc(1, sizeof(employee)))) { 
			printf("\nNo Memory allocated!\n");
			Sleep(500);
			return;
		}
		while (fscanf(f, "%d %s %s", &scanBuf, surnameBuf, buffer) != EOF) {
			if (!(newEl = (employee*)calloc(1, sizeof(employee)))) {
				printf("\nNo Memory allocated!\n");
				Sleep(500);
				return;
			}
			newEl->cipher = scanBuf;
			newEl->surname = (char*)calloc(30, sizeof(char));
			for (i = 0; surnameBuf[i] != '\0'; i++) {
				newEl->surname[i] = surnameBuf[i];
			}
			newEl->startDate[i] = '\0';
			len = strlen(buffer);
			if (len < 9) {
				newEl->flag = 1;
				for (i = len; i > 0; i--) {
					numBuf = buffer[i - 1] - '0';
					numBuf *= dozens;
					dozens *= 10;
					num += numBuf;
				}
				newEl->salary = num;
				dozens = 1; num = 0;
			}
			else {
				newEl->flag = 0;
				for (i = 0; buffer[i] != '\0'; i++) {
					newEl->startDate[i] = buffer[i];
				}
				newEl->startDate[i] = '\0';
			}
			if (!*head)      
				*tail = *head = newEl;        
			else {							  
				(*tail)->adress = newEl; 
				*tail = newEl;
			}
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
		if (!(newEl = (employee*)calloc(1, sizeof(employee)))) {
			printf("\nNo Memory allocated!\n");
			Sleep(500);
			return;
		}
		while (fscanf(f, "%d %s %s", &scanBuf, surnameBuf, buffer) != EOF) {
			if (!(newEl = (employee*)calloc(1, sizeof(employee)))) {
				printf("\nNo Memory allocated!\n");
				Sleep(500);
				return;
			}
			newEl->cipher = scanBuf;
			newEl->surname = (char*)calloc(30, sizeof(char));
			for (i = 0; surnameBuf[i] != '\0'; i++) {
				newEl->surname[i] = surnameBuf[i];
			}
			newEl->startDate[i] = '\0';
			len = strlen(buffer);
			if (len < 9) {
				newEl->flag = 1;
				for (i = len; i > 0; i--) {
					numBuf = buffer[i - 1] - '0';
					numBuf *= dozens;
					dozens *= 10;
					num += numBuf;
				}
				newEl->salary = num;
				dozens = 1; num = 0;
			}
			else {
				newEl->flag = 0;
				for (i = 0; buffer[i] != '\0'; i++) {
					newEl->startDate[i] = buffer[i];
				}
				newEl->startDate[i] = '\0';
			}
			if (!*head)                 
				*tail = *head = newEl;         
			else {							 
				(*tail)->adress = newEl;    
				*tail = newEl;            
			}
		}
		break;
	}
	printf("Succesfully write to queue!");
	_getch();
}
