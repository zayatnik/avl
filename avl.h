#include <iostream>
using namespace std;
#pragma once

struct node {
	int key;
	node* left;
	node* right;
	unsigned char height;
	node(int key1) {
		key = key1;
		left = 0;
		right = 0;
		height = 1;
	}
};

unsigned char height(node* x) {
	if (x)
		return x->height;
	else
		return 0;
}

int balfac(node* x) {
	return height(x->right) - height(x->left);
}

void fixh(node* x) {
	unsigned char l = height(x->left);
	unsigned char r = height(x->right);
	if (l > r)
		x->height = l + 1;
	else
		x->height = r + 1;
}

node* turnright(node* x) {
	node* y = x->left;
	x->left = y->right;
	y->right = x;
	fixh(x);
	fixh(y);
	return y;
}

node* turnleft(node* y) {
	node* x = y->right;
	y->right = x->left;
	x->left = y;
	fixh(y);
	fixh(x);
	return x;
}

node* balance(node* x) {
	fixh(x);
	if (balfac(x) == 2) {
		if (balfac(x->right) < 0)
			x->right = turnright(x->right);
		return turnleft(x);
	}
	if (balfac(x) == -2) {
		if (balfac(x->left) > 0)
			x->left = turnleft(x->left);
		return turnright(x);
	}
	return x;
}

node* insert(node* x, int k) {
	if (!x)
		return new node(k);
	if (k < x->key)
		x->left = insert(x->left, k);
	else
		x->right = insert(x->right, k);
	return balance(x);
}

node* findmin(node* x) {
	if (x->left)
		return findmin(x->left);
	else
		return x;
}

node* delmin(node* x) {
	if (x->left == 0)
		return x->right;
	x->left = delmin(x->left);
	return balance(x);
}

node* remove(node* x, int k) {
	if (!x) return 0;
	if (k < x->key)
		x->left = remove(x->left, k);
	else if (k > x->key)
		x->right = remove(x->right, k);
	else
	{
		node* y = x->left;
		node* z = x->right;
		delete x;
		if (!z) return y;
		node* min = findmin(z);
		min->right = delmin(z);
		min->left = y;
		return balance(min);
	}
	return balance(x);
}
