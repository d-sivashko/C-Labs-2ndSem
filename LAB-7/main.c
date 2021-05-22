#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include "functions.h"

int main() {
	system("chcp 1251>null");
	Node* head = nullptr; // адрес корня бинарного дерева
	char input;
	while (1) {
		system("CLS");
		printf("Circle LAB\n");
		printf("1 - Create/Add\n");
		printf("2 - Output\n");
		printf("3 - Output recursively\n");
		printf("4 - Delete all\n");
		printf("5 - Delete word\n");
		printf("0 - End\n");
		printf("------------------------\n");
		fflush(stdin);
		input = _getch();
		switch (input) {
		case '1':
			add(&head);
			break;
		case '2':
			output(head);
			_getch();
			break;
		case '3':
			outputRecursivly(head);
			_getch();
			break;
		case '4':
			cleanTree(head);
			head = nullptr;
			printf("Cleaned succesfully.");
			Sleep(1000);
			break;
		case '5':
			deleteWord(&head);
			break;
		case '0':
			return 0;
		default:
			printf("Incorrect input, Try again!\n");
			Sleep(500);
		}
	};
	cleanTree(head);
	return 0;
}