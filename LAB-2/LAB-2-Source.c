#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

int menu();
int inputData(struct employee* data, int counter);
void outputData(struct employee* data, int counter);
int deleteData(struct employee* data, int counter);
void findData(struct employee* data, int counter);
int additionalTask(struct employee* data, int counter);

struct employee {
	int cipher;
	char *surname;
	int flag;
	union
	{
		char startDate[12];
		int salary;
	};
};

int main() {
	int counter = 0;
	struct employee* data = malloc(sizeof(struct employee));
	while (1)
	{
		switch (menu())
		{
		case 1: counter = inputData(data, counter); break;
		case 2: outputData(data, counter); break;
		case 3: counter = deleteData(data, counter); break;
		case 4: findData(data, counter); break;
		case 5: counter = additionalTask(data, counter); break;
		case 6: return 0;
		default:
			system("CLS");
			rewind(stdin);
			printf("Error! Try again!\n");
			Sleep(500);
			system("CLS");
		}
	}
	free(data);
}

int menu() {
	system("CLS");
	int menuInput = 0;
	printf("1 - Input new data\n");
	printf("2 - Show all data\n");
	printf("3 - Delete\n");
	printf("4 - Find data\n");
	printf("5 - Additional task\n");
	printf("6 - Exit\n");
	printf("Input: ");
	scanf_s("%d", &menuInput);
	return menuInput;
}

int inputData(struct employee* data, int counter) {
	system("CLS");
	rewind(stdin);
	printf("Record number %d\n", counter + 1);
	printf("\nInput cipher: ");
	do
	{
		rewind(stdin);
	} while (!scanf_s("%d", &(data + counter)->cipher));
	printf("Input surname: ");
	rewind(stdin);
	data[counter].surname = malloc(15);
	gets(data[counter].surname);
	printf("\nEnter '0' if you want input date of receipt\n");
	printf("Enter '1' if you want input salary\n");
	printf("Input: ");
	do
	{
		rewind(stdin);
	} while (!scanf_s("%d", &(data + counter)->flag));
	if(data[counter].flag == 0) {
		printf("\nInput date like '20.08.2002': ");
		rewind(stdin);
		gets(data[counter].startDate);
	}
	else {
		printf("\nInput salary: ");
		do
		{
			rewind(stdin);
		} while (!scanf_s("%d", &(data + counter)->salary));
	}
	counter++;
}

void outputData(struct employee* data, int counter) {
	system("CLS");
	int exit;
	if (counter == 0) {
		printf("No records. Please, input data!");
		Sleep(500);
	}
	else {

		system("CLS");
		printf("id\b\tCipher\t|\tSurname \t|\tUnion\n");
		printf("------------------------------------------------------------------\n");
		for (int i = 0; i < counter; i++) {
			printf("%d\t%d\t|\t%s  \t|", i+1, data[i].cipher, data[i].surname);
			if(data[i].flag == 0)
				printf("\t%s - date of job enter\n", data[i].startDate);
			else
				printf("\t%d - salary\n", data[i].salary);
		}
		printf("\nPlease, Enter 2 for Main menu\n");
		printf("Input: ");
		do
		{
				rewind(stdin);
		} while (!scanf_s("%d", &exit));
		if (exit == 2) return;
	}
}

int deleteData(struct employee* data, int counter) {
	system("CLS");
	if (counter == 0) {
		printf("No records. Please, input data!");
		Sleep(500);
	}
	else {
		int structNumber;
		int confirmation;
		struct employee tmp = data[counter + 1];
		printf("Enter number of %d records you want delete\n", counter);
		printf("Enter '-1' - if you want delete all Data\n");
		printf("Enter '-2' - to main menu\n");
		printf("Input: ");
		do {
			rewind(stdin);
		} while (!scanf_s("%d", &structNumber));
		if (structNumber == -2) return counter;
		if (structNumber > counter && structNumber != -1 && structNumber < -2) {
			system("CLS");
			printf("Error! Please, input correct data.");
			Sleep(1000);
			return counter;
		}
		if (structNumber != -1) {
			system("CLS");
			printf("You really want delete this record?\n");
			printf("\n%d-%s-", data[structNumber - 1].cipher, data[structNumber - 1].surname);
			if (data[structNumber - 1].flag == 0)
				printf("%s-date of job enter\n", data[structNumber - 1].startDate);
			else
				printf("%d-salary\n", data[structNumber - 1].salary);
			printf("\n1 - Yes\n");
			printf("2 - Exit\n");
			printf("Input: ");
			scanf_s("%d", &confirmation);
			if (confirmation == 1) {
				for (int i = (structNumber - 1); i < counter; i++)
					data[i] = data[i + 1];
				counter -= 1;
			}if (confirmation == 2) {
				return counter;
			}
		}
		if (structNumber == -1) {
			system("CLS");
			printf("You really want delete all data?\n");
			printf("1 - Yes\n");
			printf("2 - No\n");
			printf("Input: ");
			scanf_s("%d", &confirmation);
			if (confirmation == 1) {
				for (int i = 0; i < counter; i++) {
					data[i] = tmp;
				}
				return counter = 0;
			}if (confirmation == 2) {
				return counter;
			}
		}
	}
}

void findData(struct employee* data, int counter) {
	system("CLS");
	int i, switcher;
	int flag = 0;
	int searchNum = 0;
	int exit;
	char symbols[30] = "";
	if (counter == 0) {
		printf("No records.Please, input data!");
		Sleep(500);
	}
	else {
		printf("1 - find by Cipher\n");
		printf("2 - find by Surname\n");
		printf("3 - find by Start date\n");
		printf("4 - find by Salary\n");
		printf("99 - back to main menu.\n");
		printf("Input: ");
		scanf_s("%d", &switcher);
		if (switcher == 99) return;
		switch (switcher) {
		case 1:
			system("CLS");
			printf("Input cipher id: ");
			do {
				rewind(stdin);
			} while (!scanf_s("%d", &searchNum));
			printf("\nid\b\tCipher\t|\tSurname \t|\tUnion\n");
			printf("------------------------------------------------------------------\n");
			for (i = 0; i < counter; i++) {
				if (searchNum == data[i].cipher) {
					printf("%d\t%d\t|\t%s  \t|", i + 1, data[i].cipher, data[i].surname);
					if (data[i].flag == 0)
						printf("\t%s - date of enter\n", data[i].startDate);
					else
						printf("\t%d - salary\n", data[i].salary);
					flag++;
				}
			}
			if (flag == 0) printf("No matches found!\n");
			printf("\nPlease, Enter\n");
			printf("1 - Find menu\n");
			printf("2 - Main menu\n");
			printf("Input: ");
			scanf_s("%d", &exit);
			if (exit == 1) findData(data, counter);
			if (exit == 2) return;
			break;
		case 2:
			system("CLS");
			printf("Input chars: ");
			rewind(stdin);
			gets(symbols);
			printf("\nid\b\tCipher\t|\tSurname \t|\tUnion\n");
			printf("------------------------------------------------------------------\n");
			for (i = 0; i < counter; i++) {
				if (strcmpi(symbols, data[i].surname) == 0) {
					printf("%d\t%d\t|\t%s  \t|", i + 1, data[i].cipher, data[i].surname);
					if (data[i].flag == 0)
						printf("\t%s - date of enter\n", data[i].startDate);
					else
						printf("\t%d - salary\n", data[i].salary);
					flag++;
				}
			}
			if (flag == 0) printf("No matches found!\n");
			printf("\nPlease, Enter\n");
			printf("1 - Find menu\n");
			printf("2 - Main menu\n");
			printf("Input: ");
			scanf_s("%d", &exit);
			if (exit == 1) findData(data, counter);
			if (exit == 2) return;
			break;
		case 3:
			system("CLS");
			printf("Input date **.**.****: ");
			rewind(stdin);
			gets(symbols);
			printf("\nid\b\tCipher\t|\tSurname \t|\tUnion\n");
			printf("------------------------------------------------------------------\n");
			for (i = 0; i < counter; i++) {
				if (strcmpi(symbols, data[i].startDate) == 0) {
					printf("%d\t%d\t|\t%s  \t|", i + 1, data[i].cipher, data[i].surname);
					if (data[i].flag == 0)
						printf("\t%s - date of enter\n", data[i].startDate);
					else
						printf("\t%d - salary\n", data[i].salary);
					flag++;
				}
			}
			if (flag == 0) printf("No matches found!\n");
			printf("\nPlease, Enter\n");
			printf("1 - Find menu\n");
			printf("2 - Main menu\n");
			printf("Input: ");
			scanf_s("%d", &exit);
			if (exit == 1) findData(data, counter);
			if (exit == 2) return;
			break;
		case 4:
			system("CLS");
			printf("Input the alleged salary: ");
			do
			{
				rewind(stdin);
			} while (!scanf_s("%d", &searchNum));
			printf("\nid\b\tCipher\t|\tSurname \t|\tUnion\n");
			printf("------------------------------------------------------------------\n");
			for (i = 0; i < counter; i++) {
				if (searchNum == data[i].salary) {
					printf("%d\t%d\t|\t%s  \t|", i + 1, data[i].cipher, data[i].surname);
					if (data[i].flag == 0)
						printf("\t%s - date of enter\n", data[i].startDate);
					else
						printf("\t%d - salary\n", data[i].salary);
					flag++;
				}
			}
			if (flag == 0) printf("No matches found!\n");
			printf("\nPlease, Enter\n");
			printf("1 - Find menu\n");
			printf("2 - Main menu\n");
			printf("Input: ");
			do {
				rewind(stdin);
			} while (!scanf_s("%d", &exit));
			if (exit == 1) findData(data, counter);
			if (exit == 2) return;
		}
	}
}

int additionalTask(struct employee* data, int counter) {
	system("CLS");
	int i, j;
	int switcher;
	int exit;
	char symbols[30] = "";
	struct employee temp;
	struct employee tmp = data[counter + 1];
	if (counter == 0) {
		printf("No records. Please, input data!");
		Sleep(500);
	}
	else {
		printf("1 - Find employees with minimal salary\n");
		printf("2 - Delete employees on a given day\n");
		printf("99 - Exit to main menu\n");
		printf("Input: ");
		do {
			rewind(stdin);
		} while (!scanf_s("%d", &switcher));
		if (switcher == 99) return counter;
		switch (switcher) {
			case 1: 
				for (i = 0; i < counter; i++)
					for (j = 0; j < counter; j++)
						if (data[i].salary < data[j].salary) {
							temp = data[i];
							data[i] = data[j];
							data[j] = temp;
						}
				printf("\nid\b\tCipher\t|\tSurname \t|\tUnion\n");
				printf("------------------------------------------------------------------\n");
				for (i = 0; i < counter; i++) {
					if (data[i].salary > 0 && data[i].salary < 10000) {
						printf("%d\t%d\t|\t%s  \t|\t %d - salary\n", i + 1, data[i].cipher, data[i].surname, data[i].salary);
					}
				}
				printf("\n\nInput 2 for Main menu\n");
				printf("Input: ");
				do {
					rewind(stdin);
				} while (!scanf_s("%d", &exit));
				if (exit == 2) return;
				break;
			case 2: 
				system("CLS");
				printf("Input date **.**.****: ");
				rewind(stdin);
				gets(symbols);
				for (int i = 0; i < counter; i++) {
					if (strcmpi(symbols, data[i].startDate) == 0) {
						for (int j = i; j < counter; j++)
							data[j] = data[j + 1];
						counter--; i--;
					}
				}
				return counter;
				break;
		}
	}
} 