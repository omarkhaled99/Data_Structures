#include "Rbtree.h"
#include<iostream>
#include <algorithm>
#include<string.h>
using namespace std;

Rbtree::Rbtree()
{ 
	
}

Rbtree::~Rbtree()
{
}

int Rbtree::height(Rbtree_node* root) {
	return (root == NULL) ? -1 :
		1 + max(height(root->left), height(root->right));
}


int Rbtree::findElement(char* str) {
	Rbtree_node* temp = NULL;
	int flag = 0, res = 0;
	if (root == NULL) {

		return 0;
	}
	temp = root;
	while (temp) {
		if ((res = strcasecmp(temp->word, str)) == 0) {

			flag = 1;
			return 1;
		}
		temp = (res > 0) ? temp->left : temp->right;
	}
	if (!flag)

		return 0;

}








void Rbtree::left_rotate(Rbtree_node*& root, Rbtree_node* p)
{
	Rbtree_node* p_right_child = p->right;

		p->right = p_right_child->left;
	if (p_right_child->left != NULL) {
		p_right_child->left->parent = p;
	}
	p_right_child->parent = p->parent;
	
		if (p->parent == NULL) {
		root = p_right_child;
	}
	else if (p == p->parent->left) {
			p->parent->left = p_right_child;
	}
	else {
		   
			p->parent->right = p_right_child;
	}
	
	p_right_child->left = p;
	p->parent = p_right_child;
}

void Rbtree::right_rotate(Rbtree_node*& root, Rbtree_node* p)
{
	Rbtree_node* p_left_child = p->left;

	p->left = p_left_child->right;
	if (p_left_child->right != NULL) {
		p_left_child->right->parent = p;
	}
	p_left_child->parent = p->parent;
	if (p->parent == NULL) {
		root = p_left_child;
	}
	else if (p == p->parent->right) {
		p->parent->right = p_left_child;
	}
	else {
		p->parent->left = p_left_child;
	}

	p_left_child->right = p;
	p->parent = p_left_child;
}
void Rbtree::fixup(Rbtree_node*& root, Rbtree_node*& p)
{
	Rbtree_node* uncle;
	Rbtree_node* grand_parent;
	while (p!=root&&p->parent->parent!=NULL&&p->parent->colour == RED) {
		if (p->parent == p->parent->parent->left) {
			uncle = p->parent->parent->right;
			grand_parent = p->parent->parent;
			if (uncle!=NULL&&uncle->colour == RED) {
				p->parent->colour = BLACK;
				uncle->colour = BLACK;
				grand_parent->colour = RED;
				p = grand_parent;
			}
			else
			{
				if (p == p->parent->right)
				{
					p = p->parent;
					left_rotate(root, p);
				}
					p->parent->colour = BLACK;
					p->parent->parent->colour = RED;
					right_rotate(root, p->parent->parent);
				
			}


		}
		else {
			uncle = p->parent->parent->left;
			grand_parent = p->parent->parent;
			if (uncle != NULL && uncle->colour == RED) {
				p->parent->colour = BLACK;
				uncle->colour = BLACK;
				grand_parent->colour = RED;
				p = grand_parent;
			}
			else
			{
				if (p == p->parent->left)
				{
					p = p->parent;
					right_rotate(root, p);
				}
					p->parent->colour = BLACK;
					p->parent->parent->colour = RED;
					left_rotate(root, p->parent->parent);
				
			}


		}

		root->colour = BLACK;
	}
}
int Rbtree::size(Rbtree_node* root)
{
	return (root==NULL)?0:1+size(root->right)+ size(root->left);
}

Rbtree_node* Rbtree::insert(Rbtree_node* root, Rbtree_node* pt)
{

	if (root == NULL) {
		return pt;
	}
	if (strcasecmp(pt->word, root->word) < 0)
	{
		root->left = insert(root->left, pt);
		root->left->parent = root;
	}
	else if (strcasecmp(pt->word, root->word) > 0)
	{
		root->right = insert(root->right, pt);
		root->right->parent = root;
	}
	//else {
		//repeated_insertion = true;
//	}

	return root;
}
void Rbtree::insert(char d[50]) {
	Rbtree_node* node = new Rbtree_node;
	strcpy(node->word, d);
	root = insert(root, node);
	fixup(root,node);

}
void Rbtree:: printtree() {
	printtree(root);
}
int Rbtree::size()
{
	
	return size(root);
}

bool Rbtree::is_repeated_insertion()
{
	return repeated_insertion;
}
void Rbtree::set_repeated_insertion() {
	repeated_insertion = false;
}


int Rbtree::height() {
	return height(root);
}

void Rbtree::printtree(Rbtree_node* root) {
	if (root != NULL) {
		
		printtree(root->left);
		cout << root->word << endl;
		printtree(root->right);
	}
	}