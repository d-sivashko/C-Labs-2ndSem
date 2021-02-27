// Вариант 8
// Структура «Покупатель» : фамилия, имя; домашний адрес; номер телефона; номер кредитной карточки.

// В БД хранить только нужную информацию.
// Адекватный, читабельный, красивый пользовательский интерфейс.

// Меню
// 1) Ввод                                                        +
// 2) Вывод                                                                                                           + 
// 3) Выбрать запись для изменения, только одно поле																  + 
// 4) Поиск по имени(все приводить к одному регистру!)																  +
// 5) Сортировка по заданному параметру                                                                               +
// 6) Удалить, выбрать парметр и удалить(ДОБАВИТЬ ПОДТВЕРЖДЕНИЕ)                                                      + 
// 7) Поиск по частичному совпадению Vova - *v*v* вывести все слова где есть 2 v. * = любое количество символов

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

int menu();
int inputData(struct customer data[],int counter);
void outputData(struct customer data[], int counter);
int deleteData(struct customer data[], int counter);
void changeData(struct customer data[], int counter);
void sortData(struct customer data[], int counter);
void findData(struct customer data[], int counter);

struct customer {
	char name[20];
	char surname[20];
	char homeAdress[30];
	int phoneNum;
	int cardNum;
};

int main() {
	int counter = 0;
	struct customer data[30];
	while (1)
	{
		switch (menu())
		{
		case 1: counter = inputData(data,counter); break;
		case 2: outputData(data,counter); break;
		case 3: changeData(data,counter); break;
		case 4: counter = deleteData(data,counter); break;
		case 5: sortData(data,counter); break;
		case 6: findData(data,counter); break;
		case 7: return 0;
		default:	
			system("CLS");
			rewind(stdin);
			printf("Error! Try again!\n");
			Sleep(500);
			system("CLS");
		}
	}
}

int menu() {
	system("CLS");
	int menuInput = 0;
	printf("1 - Input new data\n");
	printf("2 - Show data\n");
	printf("3 - Change record\n");
	printf("4 - Delete\n");
	printf("5 - Sort\n");
	printf("6 - Find data\n");
	printf("7 - Exit\n");
	printf("Input: ");
	scanf_s("%d", &menuInput);
	return menuInput;
}

int inputData(struct customer data[], int counter) {
	system("CLS");
	if (counter < 30) {
		rewind(stdin);
		printf("Record number %d of 30\n", counter+1);
		printf("\nInput name: ");
		gets(data[counter].name);
		printf("Input surname: ");
		gets(data[counter].surname);
		printf("Input home adress: ");
		gets(data[counter].homeAdress);
		printf("Input 9 digits of phone number like 44*******: "); 
		do
		{
			rewind(stdin);
		} while (!scanf_s("%d", &(data + counter)->phoneNum));
		printf("Input 4 digits of card number like 1234: ");
		do
		{
			rewind(stdin);
		} while (!scanf_s("%d", &(data + counter)->cardNum));
		counter++;
	}
	else { 
		printf("Maximum amount of data entered. Clean database!");
		Sleep(500);
	}
}

void outputData(struct customer data[], int counter) {
	system("CLS");
	int outputSwitch;
	int structNumber;
	int exit;
	if (counter == 0) {
		printf("No records. Please, input data!");
		Sleep(500);
	}
	else {
		printf("Please, Enter\n");
		printf("1 - to see only one record.\n");
		printf("2 - to see all records.\n");
		printf("99 - to main menu.\n");
		printf("Input: ");
		do
		{
			rewind(stdin);
		} while (!scanf_s("%d", &outputSwitch));
		if (outputSwitch == 99) return;
		if (outputSwitch == 1) {
			system("CLS");
			printf("Enter 1-30 number you want see: ");
			do
			{
				rewind(stdin);
			} while (!scanf_s("%d", &structNumber));
			if (structNumber > counter) {
				system("CLS");
				printf("Uncorrect input. Try again!");
				Sleep(1000);
				return;
			}
			printf("\nName: %s\n", data[structNumber - 1].name);
			printf("Surname: %s\n", data[structNumber - 1].surname);
			printf("Home adress: %s\n", data[structNumber - 1].homeAdress);
			printf("Phone: +375%d\n", data[structNumber - 1].phoneNum);
			printf("Card number: %d\n", data[structNumber - 1].cardNum);
			printf("\nPlease, Enter\n");
			printf("1 - Output menu\n");
			printf("2 - Main menu\n");
			printf("Input: ");
			do
			{
				rewind(stdin);
			} while (!scanf_s("%d", &exit));;
			if (exit == 1) outputData(data, counter);
			if (exit == 2) return;
		}
		if (outputSwitch == 2) {
			system("CLS");
			printf("|id. Name-Surname-Home adress-Phone-Card|\n\n");
			for (int i = 0; i < counter; i++) {
				printf("|%d . %s-%s-%s", i+1, data[i].name, data[i].surname, data[i].homeAdress);
				printf("-80%d-%d|\n", data[i].phoneNum, data[i].cardNum);
			}
			printf("\nPlease, Enter\n");
			printf("1 - Output menu\n");
			printf("2 - Main menu\n");
			printf("Input: ");
			do
			{
				rewind(stdin);
			} while (!scanf_s("%d", &exit));
			if (exit == 1) outputData(data,counter);
			if (exit == 2) return;
		}
	}
}

int deleteData(struct customer data[], int counter) {
	system("CLS");
	if (counter == 0) {
		printf("No records. Please, input data!");
		Sleep(500);
	}
	else {
		int structNumber;
		int confirmation;
		printf("Please, Enter\n");
		printf("Enter 1-30 record you want delete\n");
		printf("Enter '99' - if you want delete all Data\n");
		printf("Enter '100' - to main menu\n");
		printf("Input: ");
		do
		{
			rewind(stdin);
		} while (!scanf_s("%d", &structNumber));
		if (structNumber == 100) return counter;
		if (structNumber > counter && structNumber != 99) {
			system("CLS");
			printf("Error! Please, input correct data.");
			Sleep(1000);
			return counter;
		}
		if (structNumber != 99) {
			system("CLS");
			printf("You really want delete this record?\n");
			printf("%s-%s-%s", data[structNumber - 1].name, data[structNumber - 1].surname, data[structNumber - 1].homeAdress);
			printf("-80%d-%d\n", data[structNumber - 1].phoneNum, data[structNumber - 1].cardNum);
			printf("\n1 - Yes\n");
			printf("2 - No\n");
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
		if (structNumber == 99) {
			system("CLS");
			printf("You really want delete all data?\n");
			printf("1 - Yes\n");
			printf("2 - No\n");
			printf("Input: ");
			scanf_s("%d", &confirmation);
			struct customer tmp = data[counter+1];
			if (confirmation == 1) {
				for (int i = 0; i < 30; i++) {
					data[i] = tmp;
				}
				return counter = 0;
			}if (confirmation == 2) {
				return counter;
			}
		}
	}
}

void changeData(struct customer data[], int counter) {
	system("CLS");
	if (counter == 0) {
		printf("No records. Please, input data!");
		Sleep(500);
	}
	else {
		int changeID;
		int switcher;
		printf("Please, Input ID of record you want change or press 99 for menu: ");
		do
		{
			rewind(stdin);
		} while (!scanf_s("%d", &changeID));
		if (changeID == 99) return;
		if (changeID > counter) {
			system("CLS");
			printf("You input non-existent record. Try again.");
			Sleep(2000);
			return;
		}
		do {
			system("CLS");
			printf("1 - for change name.\n");
			printf("2 - for change surname.\n");
			printf("3 - for change home adress.\n");
			printf("4 - for change phone number.\n");
			printf("5 - for change card number.\n");
			printf("6 - exit to menu.\n");
			printf("Input: ");
			scanf_s("%d", &switcher);
			switch (switcher) {
			case 1:
				printf("\nInput new name:");
				rewind(stdin);
				gets(data[changeID - 1].name);
				break;
			case 2:
				printf("\nInput new surname:");
				rewind(stdin);
				gets(data[changeID - 1].surname);
				break;
			case 3:
				printf("\nInput new home adress:");
				rewind(stdin);
				gets(data[changeID - 1].homeAdress);
				break;
			case 4:
				printf("\nInput new phone number:");
				do
				{
					rewind(stdin);
				} while (!scanf_s("%d", &(data + (changeID - 1))->phoneNum));
				break;
			case 5:
				printf("\nInput new card number:");
				do
				{
					rewind(stdin);
				} while (!scanf_s("%d", &(data + (changeID - 1))->cardNum));
				break;
			case 6:; return;
			}
		} while (1);
	}
}

void sortData(struct customer data[], int counter) {
	int switcher;
	struct customer temp;
	system("CLS");
	if (counter == 0 || counter == 1) {
		if (counter == 0) {
			printf("No records. Please, input data!");
			Sleep(500);
		}
		else {
			printf("Input more then 1 record for sorting!");
			Sleep(500);
		}
	}
	else {
		printf("Sort parametr\n");
		printf("1 - Name\n");
		printf("2 - Surname\n");
		printf("3 - Home adress\n");
		printf("4 - Phone number\n");
		printf("5 - Card number\n");
		printf("99 - to main menu.\n");
		printf("Input: ");
		scanf_s("%d", &switcher);
		if (switcher == 99) return;
		switch (switcher)
		{
		case 1:
			for (int i = 0; i < counter; i++)
				for (int j = 0; j < counter; j++)
					if (strcmp(data[i].name, data[j].name) < 0) {
						temp = data[i];
						data[i] = data[j];
						data[j] = temp;
					}
			printf("Sorted successfully!");
			Sleep(500);
			break;
		case 2:
			for (int i = 0; i < counter; i++)
				for (int j = 0; j < counter; j++)
					if (strcmp(data[i].surname, data[j].surname) < 0) {
						temp = data[i];
						data[i] = data[j];
						data[j] = temp;
					}
			printf("Sorted successfully!");
			Sleep(500);
			break;
		case 3:
			for (int i = 0; i < counter; i++)
				for (int j = 0; j < counter; j++)
					if (strcmp(data[i].homeAdress, data[j].homeAdress) < 0) {
						temp = data[i];
						data[i] = data[j];
						data[j] = temp;
					}
			printf("Sorted successfully!");
			Sleep(500);
			break;
		case 4:
			for (int i = 0; i < counter; i++)
				for (int j = 0; j < counter; j++)
					if (data[i].phoneNum < data[j].phoneNum) {
						temp = data[i];
						data[i] = data[j];
						data[j] = temp;
					}
			printf("Sorted successfully!");
			Sleep(500);
			break;
		case 5:
			for (int i = 0; i < counter; i++)
				for (int j = 0; j < counter; j++)
					if (data[i].cardNum < data[j].cardNum) {
						temp = data[i];
						data[i] = data[j];
						data[j] = temp;
					}
			printf("Sorted successfully!");
			Sleep(500);
			break;
		}
	}
}

void findData(struct customer data[], int counter) {
	system("CLS");
	int i ,switcher;
	int flag = 0;
	int searchNum = 0;
	int exit;
	char symbols[30] = "";
	if (counter == 0) {
			printf("No records.Please, input data!");
			Sleep(500);
	}
	else {
		printf("1 - find by name\n");
		printf("2 - find by surname\n");
		printf("3 - find by home adress\n");
		printf("4 - find by phone number\n");
		printf("5 - find by card number\n");
		printf("99 - to main menu.\n");
		printf("Input: ");
		scanf_s("%d", &switcher);
		if (switcher == 99) return;
		switch (switcher) {
		case 1: 
			system("CLS");
			printf("Input chars: ");
			rewind(stdin);
			gets(symbols);
			printf("\n|id. Name-Surname-Home adress-Phone-Card|\n\n");
			for (i = 0; i < counter; i++) {
				if (strcmpi(symbols, data[i].name) == 0) {
					printf("|%d . %s-%s-%s", i + 1, data[i].name, data[i].surname, data[i].homeAdress);
					printf("-80%d-%d|\n", data[i].phoneNum, data[i].cardNum);
					flag++;
				}
			}
			if (flag == 0) printf("No matches found!\n");
			printf("\nPlease, Enter\n");
			printf("1 - Find menu\n");
			printf("2 - Main menu\n");
			printf("Input: ");
			scanf_s("%d", &exit);
			if (exit == 1) findData(data,counter);
			if (exit == 2) return;
			break;
		case 2: 
			system("CLS");
			printf("Input chars: ");
			rewind(stdin);
			gets(symbols);
			printf("\n|id. Name-Surname-Home adress-Phone-Card|\n\n");
			for (i = 0; i < counter; i++) {
				if (strcmpi(symbols, data[i].surname) == 0) {
					printf("|%d . %s-%s-%s", i + 1, data[i].name, data[i].surname, data[i].homeAdress);
					printf("-80%d-%d|\n", data[i].phoneNum, data[i].cardNum);
					flag++;
				}
			}
			if (flag == 0) printf("No matches found!\n");
			printf("\nPlease, Enter\n");
			printf("1 - Find menu\n");
			printf("2 - Main menu\n");
			printf("Input: ");
			scanf_s("%d", &exit);
			if (exit == 1) findData(data,counter);
			if (exit == 2) return;
			break;
		case 3:
			system("CLS");
			printf("Input chars: ");
			rewind(stdin);
			gets(symbols);
			printf("\n|id. Name-Surname-Home adress-Phone-Card|\n\n");
			for (i = 0; i < counter; i++) {
				if (strcmpi(symbols, data[i].homeAdress) == 0) {
					printf("|%d . %s-%s-%s", i + 1, data[i].name, data[i].surname, data[i].homeAdress);
					printf("-80%d-%d|\n", data[i].phoneNum, data[i].cardNum);
					flag++;
				}
			}
			if (flag == 0) printf("No matches found!\n");
			printf("\nPlease, Enter\n");
			printf("1 - Find menu\n");
			printf("2 - Main menu\n");
			printf("Input: ");
			scanf_s("%d", &exit);
			if (exit == 1) findData(data,counter);
			if (exit == 2) return;
			break;
		case 4:
			system("CLS");
			printf("Input 9 digits of number you want found: ");
			do
			{
				rewind(stdin);
			} while (!scanf_s("%d", &searchNum));
			printf("\n|id. Name-Surname-Home adress-Phone-Card|\n\n");
			for (i = 0; i < counter; i++) {
				if (searchNum == data[i].phoneNum) {
					printf("|%d . %s-%s-%s", i + 1, data[i].name, data[i].surname, data[i].homeAdress);
					printf("-80%d-%d|\n", data[i].phoneNum, data[i].cardNum);
					flag++;
				}
			}
			if (flag == 0) printf("No matches found!\n");
			printf("\nPlease, Enter\n");
			printf("1 - Find menu\n");
			printf("2 - Main menu\n");
			printf("Input: ");
			scanf_s("%d", &exit);
			if (exit == 1) findData(data,counter);
			if (exit == 2) return;	
			case 5:
			system("CLS");
			printf("Input 4 digits of card number you want found: ");
			do
			{
				rewind(stdin);
			} while (!scanf_s("%d", &searchNum));
			printf("\n|id. Name-Surname-Home adress-Phone-Card|\n\n");
			for (i = 0; i < counter; i++) {
				if (searchNum == data[i].cardNum) {
					printf("|%d . %s-%s-%s", i + 1, data[i].name, data[i].surname, data[i].homeAdress);
					printf("-80%d-%d|\n", data[i].phoneNum, data[i].cardNum);
					flag++;
				}
			}
			if (flag == 0) printf("No matches found!\n");
			printf("\nPlease, Enter\n");
			printf("1 - Find menu\n");
			printf("2 - Main menu\n");
			printf("Input: ");
			scanf_s("%d", &exit);
			if (exit == 1) findData(data,counter);
			if (exit == 2) return;
		}
	}
}

// Добавить поиск по частичному совпаденю