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
void atualizarInformacoes(Node* raiz, int codigo, char novoNome[100], float novoPreco, int novaQuantidade);
Node* buscar(Node* raiz, int codigo);
void listarProdutos(Node* raiz);
void gerenciarEstoque(Node* raiz, int codigo, int quantidade);
void liberaArvore(Node* raiz);

#endif
