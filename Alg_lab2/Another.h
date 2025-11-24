#pragma once
#include "Node.h"

int max(int a, int b);
int get_height(Node* root);


void pre_order(Node* root);
void in_order(Node* root);
void post_order(Node* root);
void print_tree(Node* root, string space, bool left);

void BFS(Node* root);
void print_l(Node* root, int l);