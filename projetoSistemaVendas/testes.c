#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "avl.h"

Node* testeInserir() {
    int i;
    Node* raizTesteInsercao = NULL;
    Produto novoProduto;

    printf("Iniciando testes de inserção...\n");
    for (i = 1; i <= 7000; i++) {
        char temp[20];
        sprintf(temp, "uva-%d", i);
        strcpy(novoProduto.nome, temp);

        novoProduto.codigo = i;
        novoProduto.preco = i * 2;
        novoProduto.quantidadeEstoque = i * 3;

        raizTesteInsercao = insert(raizTesteInsercao, novoProduto);
    }
    printf("Testes finalizados.\n");

    return raizTesteInsercao;
}

Node* testeRemover() {
    int i;
    Node* raizTesteRemocao = testeInserir();

    printf("Iniciando testes de remoção...\n");
    for (i = 1; i <= 2000; i++) {
        int codigo;

        if (i <= 500)
            codigo = i * 3;
        else if (i > 500 && i <= 1000)
            codigo = i * 2;
        else if (i > 1000)
            codigo = i;

        raizTesteRemocao = remover(raizTesteRemocao, codigo);
    }
    printf("Testes finalizados.\n");

    return raizTesteRemocao;
}