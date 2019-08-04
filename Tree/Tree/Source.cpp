#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string.h>
#include <cctype> 

using namespace std;

struct tree1 {};

struct tree
{
	unsigned char height;
	string word;
	int value;
	struct tree* left;
	struct tree* right;
};

unsigned char height(tree* p)
{
	return p ? p->height : 0;
}

//Вторая вычисляет balance factor заданного узла (и работает только с ненулевыми указателями):
int bfactor(tree* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(tree* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

tree * rotateright(tree * p) // правый поворот вокруг p
{
	tree* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

tree* rotateleft(tree * q) // левый поворот вокруг q
{
	tree* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

tree* balance(tree * p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

void freetr(tree * p)
{
	if (p != NULL)
	{
		freetr(p->left);
		freetr(p->right);
		delete p;
	}
}

const char* words[] = { "char", "double", "int", "short", "void", "unsigned", "string", "sizeof", "if", "while", "else", "return", "delete", "new" };

int length = sizeof(words) / sizeof(words[0]);

struct tree* addtree(tree * p, string w)
{
	if (p == NULL)
	{
		p = new tree;
		p->word = w;
		p->value = 1;
		p->height = 1;
		p->left = p->right = NULL;
	}
	else
	{
		if (w == p->word)
		{
			p->value = p->value + 1;
		}
		else if (w < p->word)
		{
			p->left = addtree(p->left, w);
		}
		else
		{
			p->right = addtree(p->right, w);
		}
	}
	return balance(p);
}

int Search_Binary(int left, int right, char* key)
{
	int midd = 0;
	while (1)
	{
		midd = (left + right) / 2;

		if (strcmp(words[midd], key) > 0)       // если искомое меньше значения в ячейке
			right = midd - 1;      // смещаем правую границу поиска
		else if (strcmp(words[midd], key) < 0)  // если искомое больше значения в ячейке
			left = midd + 1;    // смещаем левую границу поиска
		else                       // иначе (значения равны)
			return 1;           // функция возвращает индекс ячейки

		if (left > right)          // если границы сомкнулись 
			return 0;
	}
}

void search_in_tree(tree * p, string w)
{
	if (p == NULL)
	{
	}
	else
	{
		if (w == p->word)
		{
			p->value = p->value + 1;
		}
		else if (w < p->word)
		{
			search_in_tree(p->left, w);
		}
		else
		{
			search_in_tree(p->right, w);
		}
	}

}
void treeprint(tree * p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		cout << p->value << " " << p->word << endl;
		treeprint(p->right);
	}
}

tree* root = NULL;

void search()
{
	FILE* fin = fopen("input.txt", "r");
	int j = 0;
	char temp_name[150] = { '\0' };
	if (!fin)
	{
		cout << "Cant read file";
	}
	int c = fgetc(fin);
	while (c != EOF)
	{
		if (c == '#')
		{
			while (c != '\n')
			{
				c = fgetc(fin);
			}
		}
		else if (c == '"')
		{
			c = fgetc(fin);
			while (c != '"')
			{
				c = fgetc(fin);
			}
		}
		else if (c == '\'')
		{
			c = fgetc(fin);
			while (c != '\'')
			{
				if (c == '\\')
				{
					c = fgetc(fin);
				}
				c = fgetc(fin);
			}
		}
		else if (isalpha(c))
		{
			while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
			{
				temp_name[j] = c;
				j++;
				c = fgetc(fin);
			}
			if (temp_name[0] != '\0')
			{
				string s = temp_name;
				if (!Search_Binary(0, length - 1, temp_name))
				{
					root = addtree(root, s);
				}
			}
		}
		j = 0;
		memset(temp_name, '\0', 150);
		c = fgetc(fin);
	}

	fclose(fin);
}

void qsortRecursive(int left, int right)
{
	int i = left; int j = right;
	const char* mid = words[(i + j) / 2];
	do {
		while (strcmp(words[i], mid) < 0) {
			i++;
		}
		while (strcmp(words[j], mid) > 0) {
			j--;
		}

		if (i <= j) {
			const char* tmp = words[i];
			words[i] = words[j];
			words[j] = tmp;

			i++;
			j--;
		}
	} while (i <= j);

	if (j > left)
	{
		qsortRecursive(left, j);
	}
	if (i < right)
	{
		qsortRecursive(i, right);
	}
}

int main()
{
	qsortRecursive(0, length - 1);
	search();
	treeprint(root);
	freetr(root);
	return 0;
}
