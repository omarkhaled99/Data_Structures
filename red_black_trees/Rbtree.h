#pragma once

#pragma warning(disable:4996)

#ifdef _MSC_VER 
//not #if defined(_WIN32) || defined(_WIN64) because we have strncasecmp in mingw
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif
#include <algorithm>
#define BLACK false
#define RED true
typedef struct node {
	struct node* parent = NULL;
	struct node* left = NULL;
	struct node* right = NULL;
	char word[50]="";
	bool colour = RED;
}Rbtree_node;
class Rbtree
{
public:
	Rbtree();
	~Rbtree();
	int height();
	int findElement(char* str);
    void insert(char d[50]);
	void printtree();
	int size();
	bool is_repeated_insertion();
	void set_repeated_insertion();
private:
	Rbtree_node *root = NULL;
	bool repeated_insertion = false;
	void printtree(Rbtree_node* root);
	int size(Rbtree_node*root);
	Rbtree_node* insert(Rbtree_node* root, Rbtree_node* pt);
	int height(Rbtree_node* root);
	void left_rotate(Rbtree_node*& root, Rbtree_node* p);
	void right_rotate(Rbtree_node*& root, Rbtree_node* p);
	void fixup(Rbtree_node*& root, Rbtree_node*& p);
};


