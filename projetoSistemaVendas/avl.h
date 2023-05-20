#ifndef AVL_H
#define AVL_H
#include "produto.h"

typedef struct node {
    Produto produto;
    struct node* left;
    struct node* right;
    int altura;
} Node;

Node* insert(Node* raiz, Produto produto);
Node* remover(Node* raiz, int codigo);
Node* buscar(Node* raiz, int codigo);
void listarProdutos(Node* raiz);
void liberaArvore(Node* raiz);
void altura(Node* no);

#endif
