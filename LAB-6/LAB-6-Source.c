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
	employee* l;
	employee* r;
};

void add(employee** enter);
void view(employee*);
employee* del_any(employee*);
void find(employee*);
void saveToFile(employee*);
void importFromFile(employee**);
employee* direction(char c, employee* s);

int main() {
	employee *enter;  // указатель на 'начальный' элемент кольца ("точка входа")
	enter = nullptr; // кольца нет
	char input;
	int delNum;
	while (1) {
		system("CLS");
		printf("Circle LAB\n");
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
		case '1': add(&enter); break;
		case '2': view(enter); break;
		case '3': enter = del_any(enter); break;
		case '4': find(enter); break;
		case '5': saveToFile(enter); break;
		case '6': importFromFile(&enter); break;
		case '0': return 0;
		default:
			printf("Incorrect input, Try again!\n");
			Sleep(500);
		}
	}
	return 0;
}

void add(employee** enter) { // функция cоздания/добавления элементов в кольцо
	employee *prevEl, *nextEl;
	char unionSwitch;
	if (!*enter) {                                               // кольцо еще создано (т.е. не содержит ни одного элемента)
		if (!(prevEl = (employee*)malloc(sizeof(employee)))) { // создаем первый элемент для создания кольца                  
			printf("\nNo Memory allocated!\n");
			Sleep(500);
			return;
		}
		printf("Input cipher: ");
		do {
			rewind(stdin);
		} while (!scanf_s("%d", &prevEl->cipher));
		printf("Input surname: ");
		rewind(stdin);
		prevEl->surname = (char*)calloc(30, sizeof(char));
		gets_s((prevEl)->surname, 30);
		printf("Press '1' for input Start date - ");
		printf("Press '2' for input Salary");
		unionSwitch = _getch();
		switch (unionSwitch) {
		case '1':
			prevEl->flag = 0;
			printf("\nInput date like '20.08.2002': ");
			rewind(stdin);
			gets_s((prevEl)->startDate);
			break;
		case '2':
			prevEl->flag = 1;
			printf("\nInput salary: ");
			do {
				rewind(stdin);
			} while (!scanf_s("%d", &prevEl->salary));
			break;
		default: printf("\nIncorrect input, Try again!\n");
		}
		prevEl->l = prevEl ->r = prevEl;  // "замыкаем" единственный элемент на себя 
		*enter = prevEl;          // указатель на кольцо пока с единственным эл-том
	}
	else prevEl = (*enter)->r;  // кольцо уже существует, prevEl - указатель на право от точки входа
	do {
		if (!(nextEl = (employee*)calloc(1, sizeof(employee)))) {
			printf("\nNo Memory allocated!\n");
			Sleep(500);
			return;
		}
		printf("Input cipher: ");
		do {
			rewind(stdin);
		} while (!scanf_s("%d", &nextEl->cipher));
		printf("Input surname: ");
		rewind(stdin);
		nextEl->surname = (char*)calloc(30, sizeof(char));
		gets_s((nextEl)->surname, 30);
		printf("Press '1' for input Start date - ");
		printf("Press '2' for input Salary");
		unionSwitch = _getch();
		switch (unionSwitch) {
		case '1':
			nextEl->flag = 0;
			printf("\nInput date like '20.08.2002': ");
			rewind(stdin);
			gets_s((nextEl)->startDate);
			break;
		case '2':
			nextEl->flag = 1;
			printf("\nInput salary: ");
			do {
				rewind(stdin);
			} while (!scanf_s("%d", &nextEl->salary));
			break;
		default: printf("\nIncorrect input, Try again!\n");
		}
		prevEl->l = nextEl;
		nextEl->r = prevEl;       // nextEl->l теперь указывает на  элемент  prevEl
		prevEl = nextEl;         // указатель prevEl передвигаем на nextEl (для добавления следующего эл-та)
		printf("\nProceed?('y' = yes/'n' = no)\n\n");
		fflush(stdin);
	} while (_getch() == 'y');
	nextEl->l = *enter; // если цикл ввода новых эл-тов в кольцо окончен, то сообщаем
	(*enter)->r = nextEl; // точке входа адрес элемента расположенного справа
}

void view(employee* enter) { // функция просмотра элементов кольца
	int id = 1;
	char switchCase;
	employee* pointer;
	pointer = enter;
	if (!enter) {
		puts("Circle is empty! Add elements!");
		Sleep(500);
		return;
	}
	puts("\n'r' - clockwise, 'l' - counter-clockwise\n");
	fflush(stdin);
	switch (switchCase = _getch()) {
		case 'r': case 'R':
			case 'l': case 'L':
			printf("\nid\b\tCipher\t|\tSurname \t|\tUnion\n");
			printf("------------------------------------------------------------------\n");
			do {
				printf("%d\t%d\t|\t%s \t|", id, pointer->cipher, pointer->surname);
				if (pointer->flag == 0)
					printf("\t%s - job enter date\n", pointer->startDate);
				else printf("\t%d - salary\n", pointer->salary);
				pointer = direction(switchCase, pointer);
				id++;
			} while (pointer != enter);
	}
	_getch();
}

employee* del_any(employee* enter) {
	employee* pointer; // указатель на удаляемый элемент кольца
	char buf[50];
	if (!enter) {
		puts("Circle is empty! Add elements!");
		Sleep(500);
		return enter;
	}
	pointer = enter;
	puts("Input 'Surname' of element you want delete");
	rewind(stdin);
	gets_s(buf);
	do {                                                            // цикл просмотра содержимого кольца
		if (_strcmpi(pointer->surname, buf)) pointer = pointer->r; // не элемент для удаления
		else {                                                    // найден элемент кольца для удаления
			if (pointer->r == pointer) {                         // в кольце всего один элемент 
				free(pointer->surname);
				free(pointer); 
				return nullptr;
			}
			if (enter == pointer) enter = enter->r; // новая точка входа в кольцо, т.е. если удаляемый элемент на точке входа, то смещаем ее вправо
			pointer->l->r = pointer->r;            // исключение узла s1 из кольца
			pointer->r->l = pointer->l;
			free(pointer->surname);
			free(pointer);                       // удаление элемента кольца s1
			printf("Succesfully delete!");
			Sleep(500);
			return enter;
		}
	} while (pointer != enter);               // пока не выполнен обход кольца
	printf("No information about = %s\n", buf);
	Sleep(500);
	return enter;
}

void find(employee* enter) { // функция поиска элемента по параметру в кольце
	employee* begin;
	char switcher;
	char symbols[30] = "";
	int searchNum;
	int searchFlag = 0;
	if (!enter) {
		puts("Circle is empty! Add elements!");
		Sleep(500);
		return;
	}
	begin = enter;
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
			if (searchNum == enter->cipher) {
				printf("%d\t|\t%s \t|", enter->cipher, enter->surname);
				if (enter->flag == 0)
					printf("\t%s - job enter date\n", enter->startDate);
				else
					printf("\t%d - salary\n", enter->salary);
				searchFlag++;
			}
			enter = enter->l;
		} while (enter != begin);
		break;
	case '2':
		printf("Input surname: ");
		rewind(stdin);
		gets_s(symbols);
		do {
			if (_strcmpi(symbols, enter->surname) == 0) {
				printf("%d\t|\t%s \t|", enter->cipher, enter->surname);
				if (enter->flag == 0)
					printf("\t%s - job enter date\n", enter->startDate);
				else
					printf("\t%d - salary\n", enter->salary);
				searchFlag++;
			}
			enter = enter->l;
		} while (enter != begin);
		break;
	case '3':
		printf("Input start date: ");
		rewind(stdin);
		gets_s(symbols);
		do {
			if (_strcmpi(symbols, enter->startDate) == 0) {
				printf("%d\t|\t%s \t|", enter->cipher, enter->surname);
				if (enter->flag == 0)
					printf("\t%s - job enter date\n", enter->startDate);
				else
					printf("\t%d - salary\n", enter->salary);
				searchFlag++;
			}
			enter = enter->l;
		} while (enter != begin);
		break;
	case '4':
		printf("Input salary id: ");
		do {
			rewind(stdin);
		} while (!scanf_s("%d", &searchNum));
		do {
			if (searchNum == enter->salary) {
				printf("%d\t|\t%s \t|", enter->cipher, enter->surname);
				if (enter->flag == 0)
					printf("\t%s - job enter date\n", enter->startDate);
				else
					printf("\t%d - salary\n", enter->salary);
				searchFlag++;
			}
			enter = enter->l;
		} while (enter != begin);
		break;
	default: printf("\nIncorrect input, Try again!\n");
	}
	if (searchFlag == 0) printf("No matches found!\n");
	_getch();
}

void saveToFile(employee* enter) {
	if (!enter) {
		puts("\nCircle is empty! Add elements!");
		Sleep(500);
		return;
	}
	FILE* f;
	char input;
	employee* pointer;
	pointer = enter;
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
			fprintf(f, "%d\t\t%s \t", enter->cipher, enter->surname);
			if (enter->flag == 0)
				fprintf(f, "\t%s\n", enter->startDate);
			else
				fprintf(f, "\t%d\n", enter->salary);
			enter = enter->l;
		} while (enter != pointer);
		fclose(f);
		break;
	case '2':
		if ((f = fopen("Save.bin", "wb")) == NULL) {
			printf("Can't open file. Try Again!");
			Sleep(500);
			return;
		}
		do {
			fprintf(f, "%d\t\t%s \t", enter->cipher, enter->surname);
			if (enter->flag == 0)
				fprintf(f, "\t%s\n", enter->startDate);
			else
				fprintf(f, "\t%d\n", enter->salary);
			enter = enter->l;
		} while (enter != pointer);
		fclose(f);
		break;
	}
	printf("Succesfully save!");
	Sleep(500);
}


void importFromFile(employee** enter) {
	int counter = 6;
	FILE* f;
	employee *prevEl, *nextEl;
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
		if (!(nextEl = (employee*)calloc(1, sizeof(employee)))) {
			printf("\nNo Memory allocated!\n");
			Sleep(500);
			return;
		}
		if (!*enter) {
			if (!(prevEl = (employee*)malloc(sizeof(employee)))) {
				printf("\nNo Memory allocated!\n");
				Sleep(500);
				return;
			}
			fscanf(f, "%d %s %s", &scanBuf, surnameBuf, buffer);
			prevEl->cipher = scanBuf;
			prevEl->surname = (char*)calloc(30, sizeof(char));
			for (i = 0; surnameBuf[i] != '\0'; i++) {
				prevEl->surname[i] = surnameBuf[i];
			}
			prevEl->startDate[i] = '\0';
			len = strlen(buffer);
			if (len < 9) {
				prevEl->flag = 1;
				for (i = len; i > 0; i--) {
					numBuf = buffer[i - 1] - '0';
					numBuf *= dozens;
					dozens *= 10;
					num += numBuf;
				}
				prevEl->salary = num;
				dozens = 1; num = 0;
			}
			else {
				prevEl->flag = 0;
				for (i = 0; buffer[i] != '\0'; i++) {
					prevEl->startDate[i] = buffer[i];
				}
				prevEl->startDate[i] = '\0';
			}
			prevEl->l = prevEl->r = prevEl;  // "замыкаем" единственный элемент на себя 
			*enter = prevEl;          // указатель на кольцо пока с единственным эл-том
		}
		else  prevEl = (*enter)->r;
		do {
			if (fscanf(f, "%d %s %s", &scanBuf, surnameBuf, buffer) == EOF)
				break;
			if (!(nextEl = (employee*)calloc(1, sizeof(employee)))) {
				printf("\nNo Memory allocated!\n");
				Sleep(500);
				return;
			}
			nextEl->cipher = scanBuf;
			nextEl->surname = (char*)calloc(30, sizeof(char));
			for (i = 0; surnameBuf[i] != '\0'; i++) {
				nextEl->surname[i] = surnameBuf[i];
			}
			nextEl->startDate[i] = '\0';
			len = strlen(buffer);
			if (len < 9) {
				nextEl->flag = 1;
				for (i = len; i > 0; i--) {
					numBuf = buffer[i - 1] - '0';
					numBuf *= dozens;
					dozens *= 10;
					num += numBuf;
				}
				nextEl->salary = num;
				dozens = 1; num = 0;
			}
			else {
				nextEl->flag = 0;
				for (i = 0; buffer[i] != '\0'; i++) {
					nextEl->startDate[i] = buffer[i];
				}
				nextEl->startDate[i] = '\0';
			}
			prevEl->l = nextEl;
			nextEl->r = prevEl;       // nextEl->l теперь указывает на  элемент  prevEl
			prevEl = nextEl;
		} while (1);
		nextEl->l = *enter;
		(*enter)->r = nextEl;
		fclose(f);
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
		if (!(nextEl = (employee*)calloc(1, sizeof(employee)))) {
			printf("\nNo Memory allocated!\n");
			Sleep(500);
			return;
		}
		if (!*enter) {
			if (!(prevEl = (employee*)malloc(sizeof(employee)))) {
				printf("\nNo Memory allocated!\n");
				Sleep(500);
				return;
			}
			fscanf(f, "%d %s %s", &scanBuf, surnameBuf, buffer);
			prevEl->cipher = scanBuf;
			prevEl->surname = (char*)calloc(30, sizeof(char));
			for (i = 0; surnameBuf[i] != '\0'; i++) {
				prevEl->surname[i] = surnameBuf[i];
			}
			prevEl->startDate[i] = '\0';
			len = strlen(buffer);
			if (len < 9) {
				prevEl->flag = 1;
				for (i = len; i > 0; i--) {
					numBuf = buffer[i - 1] - '0';
					numBuf *= dozens;
					dozens *= 10;
					num += numBuf;
				}
				prevEl->salary = num;
				dozens = 1; num = 0;
			}
			else {
				prevEl->flag = 0;
				for (i = 0; buffer[i] != '\0'; i++) {
					prevEl->startDate[i] = buffer[i];
				}
				prevEl->startDate[i] = '\0';
			}
			prevEl->l = prevEl->r = prevEl;  // "замыкаем" единственный элемент на себя 
			*enter = prevEl;          // указатель на кольцо пока с единственным эл-том
		}
		else  prevEl = (*enter)->r;
		do {
			if (fscanf(f, "%d %s %s", &scanBuf, surnameBuf, buffer) == EOF)
				break;
			if (!(nextEl = (employee*)calloc(1, sizeof(employee)))) {
				printf("\nNo Memory allocated!\n");
				Sleep(500);
				return;
			}
			nextEl->cipher = scanBuf;
			nextEl->surname = (char*)calloc(30, sizeof(char));
			for (i = 0; surnameBuf[i] != '\0'; i++) {
				nextEl->surname[i] = surnameBuf[i];
			}
			nextEl->startDate[i] = '\0';
			len = strlen(buffer);
			if (len < 9) {
				nextEl->flag = 1;
				for (i = len; i > 0; i--) {
					numBuf = buffer[i - 1] - '0';
					numBuf *= dozens;
					dozens *= 10;
					num += numBuf;
				}
				nextEl->salary = num;
				dozens = 1; num = 0;
			}
			else {
				nextEl->flag = 0;
				for (i = 0; buffer[i] != '\0'; i++) {
					nextEl->startDate[i] = buffer[i];
				}
				nextEl->startDate[i] = '\0';
			}
			prevEl->l = nextEl;
			nextEl->r = prevEl;       // nextEl->l теперь указывает на  элемент  prevEl
			prevEl = nextEl;
		} while (1);
		nextEl->l = *enter;
		(*enter)->r = nextEl;
		fclose(f);
		break;
	}
	printf("Succesfully write to Circle!");
	Sleep(500);
}

employee* direction(char c, employee* s) {
	switch (c) {
	case 'r': case 'R': return s->r;   // вправо
	case 'l': case 'L': return s->l;   // влево
	}
}
