#include <stdio.h>

struct Tree {
	char word[50];         // информационное поле слова
	char translation[50]; // информационное поле перевода
	int counter;                // число встреч инф. поля в бинарном дереве
};
struct Node {           // указатель на левое и правое поддерево 
	Tree tree;
	Node* left;
	Node* right;
};