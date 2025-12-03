#pragma once
#include "Node.h"

int max(int a, int b);
int get_height(Node* root, Node* psevdo);


void pre_order(Node* root);
void in_order(Node* root);
void post_order(Node* root);
void print_tree(Node* root, string space, bool left, tree tree);

void BFS(Node* root);
void print_l(Node* root, int l);

void experiment(tree type);
void monoton_experiment(tree type);