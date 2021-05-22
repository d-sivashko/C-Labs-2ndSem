#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

int menu();

int main() {
	FILE* f;
	int counter = 0;
	int value;
	int i;
	int min = 0, max = 0;
	int sum;
	while (1) {
		switch (menu()) {
		case 1: // Input
			system("CLS");
			if ((f = fopen("file.bin", "wb+")) == NULL) {
				printf("Can't open file");
				return 0;
			}
			printf("Input numbers to file enter '999' for menu\n");
			while (1) {
				do {
					rewind(stdin);
				} while (!scanf_s("%d", &value));
				if (value == 999) break;
				fwrite(&value, sizeof(int), 1, f);
				counter++;
			}
			fclose(f);
			break;
		case 2: // Output
			system("CLS");
			f = fopen("file.bin", "rb");
			printf("All data from file - enter '999' for menu\n");
			for (i = 0; i < counter; i++) {
				fread(&value, sizeof(int), 1, f);
				printf("%d ", value);
			}
			printf("\n");
			scanf_s("%d", &value);
			if (value == 999) break;
			fclose(f);
			break;
		case 3: // Task 2
			system("CLS");
			sum = 0;
			f = fopen("file.bin", "r+b");
			rewind(stdin);
			fread(&value, sizeof(int), 1, f);
			sum += value;
			min = value;
			for (i = 0; i < counter; i++) {
				fread(&value, sizeof(int), 1, f);
				sum += value;
				if (value < min) min = value;
				if (value > max) max = value;
			}
			sum -= value;
			fclose(f);
			sum -= min;
			sum -= max;
			sum = sum / (counter - 2);
			printf("Judges assesment = %d", sum);
			Sleep(2000);
			break;
		case 4: // Task 3 - поменять максимальные значения на минимальные и наоборот
			system("CLS");
			f = fopen("file.bin", "rb+");
			rewind(stdin);
			min = 0;
			max = 0;
			fread(&value, sizeof(int), 1, f);
			min = value;
			for (i = 0; i < counter; i++) {
				fread(&value, sizeof(int), 1, f);
				if (value < min) min = value;
				if (value > max) max = value;
			}
			fclose(f);
			value = 0;
			f = fopen("file.bin", "rb+");
			for (i = 0; i < counter; i++) {
				fread(&value, sizeof(int), 1, f);
				if (min == value) {
					fseek(f, -4, 1);
					fwrite(&max, sizeof(int), 1, f);
					fseek(f, +4, 1);
				}
				if (max == value) {
					fseek(f, -4, 1);
					fwrite(&min, sizeof(int), 1, f);
					fseek(f, +4, 1);
				}
			}
			fclose(f);
			rewind(stdin);
			printf("Replace was succesfully!");
			Sleep(500);
			break;
		case 5: return 0;
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
	printf("1. Input\n");
	printf("2. Output\n");
	printf("3. Judge asessment\n");
	printf("4. Min->Max - Max->Min\n");
	printf("5. Exit\n");
	printf("Input: ");
	scanf_s("%d", &menuInput);
	return menuInput;
}