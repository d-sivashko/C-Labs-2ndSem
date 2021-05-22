#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>


int menu();
void reverse(char* fileName, fpos_t start, fpos_t end);

int main() {
	FILE* f;
	int numBuffer;
	char outBuffer[127];
	int max = 0, tmp, counter = 0;
	int i;
	char name[] = "File.txt";
	int start, end;
	int countNum = 0;
	while (1)
	{
		switch (menu())
		{
		case 1: // Input
			system("CLS");
			if ((f = fopen(name, "w")) == NULL) {
				printf("Can't open file!");
				return 0;
			}
			else {
				countNum = 0;
				f = fopen(name, "w");
				printf("Input numbers to file enter '999' for menu\n");
				while (1) {
					do {
						rewind(stdin);
					} while (!scanf_s("%d", &numBuffer));
					if (numBuffer == 999) break;
					fprintf(f, "%d ", numBuffer);
				}
				fclose(f);
				break;
			}
		case 2: // Output
			system("CLS");
			f = fopen(name, "r");
			printf("All data from file - enter '999' for menu\n");
			while (fgets(outBuffer, 127, f) != NULL)
				printf("%s", outBuffer);
			printf("\n");
			scanf_s("%d", &numBuffer);
			if (numBuffer == 999) break;
			fclose(f);
			break;
		case 3: // Find MAX number at file
			counter = 0;
			max = 0;
			system("CLS");
			f = fopen("File.txt", "r");
			printf("Max Num from file - enter '999' for menu\n");
			while (!(feof(f))) {
				if (fscanf(f, "%d", &tmp) == 1) {
					if (tmp == max) {
						counter++;
					}
					if (max < tmp) {
						counter == 0;
						max = tmp;
					}
				}
			}
			for (i = 0; i <= counter; i++)
				printf("%d ", max);
			scanf_s("%d", &numBuffer);
			if (numBuffer == 999) break;
			fclose(f);
			break;
		case 4: // Reverse
			system("CLS");
			printf("Input start position number you want reverse: ");
			do {
				rewind(stdin);
			} while (!scanf_s("%d", &start));;
			printf("Input end position number you want reverse: ");
			do {
				rewind(stdin);
			} while (!scanf_s("%d", &end));
			reverse(name,start,end);
			printf("\nFile with reverse number - enter '999' for menu\n");
			scanf_s("%d", &numBuffer);
			if (numBuffer == 999) break;
			break;
		case 5: // Exit
			return 0; break;
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
	printf("1 - Input number to file\n");
	printf("2 - Output data from file\n");
	printf("3 - Find MAX number at file\n");
	printf("4 - Reverse chosen number at file\n");
	printf("5 - Exit\n");
	printf("Input: ");
	scanf_s("%d", &menuInput);
	return menuInput;
}

void reverse(char *name, fpos_t n, fpos_t k) {
	FILE *f;
	char s1,s2;
	if (!(f = fopen(name, "r+"))) {
		puts("Can't open file");
		return;
	}                              
	while (n < k) {
		fsetpos(f, &n);                      
		fscanf(f,"%c",&s1);
		fsetpos(f, &k);                          
		fscanf(f,"%c",&s2);
		fsetpos(f, &n);                        
		fprintf(f,"%c",s2);
		fsetpos(f, &k);
		fprintf(f,"%c",s1);
		n++; k--;
	}
	fclose(f);
	return;
}