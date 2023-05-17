#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct produto {
    int codigo;
    char nome[100];
    float preco;
    int quantidadeEstoque;
} Produto;

#endif