#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include "tree.c"

void cleanTree(Node* s) {
	if (s) {
		if (s->left) {
			cleanTree(s->left);
		}
		if (s->right) {
			cleanTree(s->right);
		}
		free(s);
	}
	else {
		printf("Cleaned succesfully!\n");
	}
}

void getsEngWord(char* name, int n) {
	int i = 0;
	char c;
	do {
		rewind(stdin);
		i = 0;
		c = ' ';
		int error = 0;
		while (c != '\n') {
			scanf_s("%c", &c);
			if (((c < 'a' || c > 'z')&&(c<'A'|| c>'Z'))&&c!='\n') {
				printf("Error!\n");
				error = 1;
				break;
			}
			if (c != '\n') {
				name[i] = c;
				i++;
			}
			if (i > n) {
				printf("Error!\n");
				error = 1;
				break;
			}
		}
		if (error == 0) {
			break;
		}
	} while (1);
	name[i] = '\0';
}

void getsRusWord(char* name, int n) {
	int i = 0;
	char c;
	do {
		rewind(stdin);
		i = 0;
		c = ' ';
		int error = 0;
		while (c != '\n') {
			scanf_s("%c", &c);
			if (((c < 'à' || c > 'ÿ') && (c < 'À' || c>'ß')) && c != '\n') {
				printf("Error!\n");
				error = 1;
				break;
			}
			if (c != '\n') {
				name[i] = c;
				i++;
			}
			if (i > n) {
				printf("Error!\n");
				error = 1;
				break;
			}
		}
		if (error == 0) {
			break;
		}
	} while (1);
	name[i] = '\0';
}

void add(Node** head) {
	Node* p1, * p2; // новый элемент(узел, лист) добавляется в конец ветви дерева
	do {
		if (!(p1 = (Node*)calloc(1, sizeof(Node)))) { // создание нового элемента(узла) добавляемого в дерево
			printf("Memory alloc error!");
			return;
		}
		printf("Input word in English.\n");
		getsEngWord(p1->tree.word, 50);
		printf("Input translation in Russian.\n");
		getsRusWord(p1->tree.translation, 50);
		if (!(*head)) { // если дерево пустое (если в дерево еще не было ввода инф.)
			(*head) = p1;
			(*head)->tree.counter = 0;
			(*head)->left = (*head)->right = nullptr;
		}
		else {                                                  // иначе поиск места в дереве куда добавляется новый элемент
			p2 = *head;
			while (p2) {                                      // указатель "пробегает" по дереву до искомого узла или до конца ветви
				if (!strcmp(p1->tree.word, p2->tree.word)) { // в дереве найдена искомая информация т.е. узел с такой информацией уже в дереве есть
					p2->tree.counter++;
					free(p1);
					break;
				}
				else {                                               // в узле дерева информациея не совпадает с искомой
					if (strcmp(p1->tree.word, p2->tree.word) < 0) { // p1->word меньше p2->word  
						if (p2->left == nullptr) {                 // из вершины p2 нет движения влево 
							p2->left = p1;		  // вставка узла p2 в дерево
							p2 = nullptr;		 // для выхода из цикла while
						}
						else { // переход к следующей вершине дерева слева от p1
							p2 = p2->left;
						}
					}
					else {
						if (p2->right == nullptr) { // из вершины p2 нет движения вправо 
							p2->right = p1;        // вставка узла p1 в дерево
							p2 = nullptr;         // для выхода из цикла while
						}
						else {
							p2 = p2->right; // переход к следующей вершине дерева справа от p1
						}
					}
				}
			}
		}
		printf("\nProceed?('y' = yes/'n' = no)\n\n");
		fflush(stdin);
	} while (_getch() == 'y');
}

void outputRecursivly(Node* s) {
	if (s) {
		printf("%s\n%s\n", s->tree.word, s->tree.translation);
		if (s->left) {
			outputRecursivly(s->left); // вывод левой ветви дерева
		}
		if (s->right) {
			outputRecursivly(s->right); // вывод правой ветви дерева
		}
	}
	else {
		puts("Circle is empty! Add elements!");
	}
}

void output(Node* head) {
	struct stack {
		Node* Tree;
		stack* next;
	};
	stack* p1, * p2 = nullptr;
	if (!head) {
		puts("Circle is empty! Add elements!");
		return;
	}
	p1 = (stack*)calloc(1, sizeof(stack));
	p1->Tree = head;
	p1->next = p2;
	printf("%s\n%s\n", head->tree.word, head->tree.translation);
	int rightTrigger = 1;
	while (p1 || head->right) {
		do {
			if (rightTrigger && head->left) head = head->left;
			else if (head->right) head = head->right;
			rightTrigger = 1;
			if (head->left && head->right) {
				p2 = p1;
				p1 = (stack*)calloc(1, sizeof(stack));
				p1->Tree = head;
				p1->next = p2;
			}
			printf("%s\n%s\n", head->tree.word, head->tree.translation);
		} while (head->left || head->right);
		if (p1) {
			head = p1->Tree;
			p2 = p1->next;		
			free(p1);
		}
		p1 = p2;
		if (head->left && head->right) rightTrigger = 0;
		else break;
	}
}

void deleteWord(Node** head) {
	Node* ptr = *head, * buffer = nullptr;
	char word[50];
	int siteTrigger = 0, i = 0;
	printf("Input word wich you want delete\n");
	getsEngWord(word, 50);
	while (ptr) {
		if ((_strcmpi(word, ptr->tree.word)) < 0) {
			siteTrigger = 1;
			buffer = ptr;
			ptr = ptr->left;
		}
		else if ((_strcmpi(word, ptr->tree.word)) > 0) {
			siteTrigger = 2;
			buffer = ptr;
			ptr = ptr->right;
		}
		else {
			if (!buffer) {
				if ((*head)->right) {
					buffer = (*head);      // запоминаем удаляемую вершину дерева
					ptr = (*head)->right; // переход на вершину вправо от удаляемой и далее
					(*head) = (*head)->right;
					while (ptr->left) {
						ptr = ptr->left;
					}
					ptr->left = buffer->left;
				}
				else if ((*head)->left) { // у вершины есть ветвь влево
					buffer = (*head);
					(*head) = (*head)->left;
				}
				else {
					buffer = (*head);
					(*head) = nullptr;
				}
				free(buffer);
			}
			else if (ptr->right && ptr->left) {
				if (siteTrigger == 1) { 
					buffer->left = ptr->right;
					while (buffer->left) {
						buffer = buffer->left;
					}
					buffer->left = ptr->left;
				}
				else {
					buffer->right = ptr->right;
					buffer = buffer->right;
					while (buffer->left) {
						buffer = buffer->left;
					}
					buffer->left = ptr->left;
				}
				free(ptr);
			}
			else {
				if (siteTrigger == 1) {
					if (ptr->left) {
						buffer->left = ptr->left;
					}
					else if (ptr->right) {
						buffer->left = ptr->right;
					}
					else if (buffer->left == ptr) {
						buffer->left = nullptr;
					}
					else if (buffer->right == ptr) {
						buffer->right = nullptr;
					}
				}
				else {
					if (ptr->left) {
						buffer->left = ptr->left;
					}
					else if (ptr->right) {
						buffer->right = ptr->right;
					}
					else if (buffer->left == ptr) {
						buffer->left = nullptr;
					}
					else if (buffer->right == ptr) {
						buffer->right = nullptr;
					}
				}
				free(ptr);
			}
			break;

		}
	}
}