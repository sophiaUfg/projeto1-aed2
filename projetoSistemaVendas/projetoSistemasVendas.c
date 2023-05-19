#include <stdio.h>
#include <stdlib.h>
#include "produto.h"
#include "avl.h"

int main(){
    Node *raiz = NULL;

    int opcao;
    do {
        printf("\n=== Sistema de Vendas ===\n");
        printf("1. Inserir produto\n");
        printf("2. Remover produto\n");
        printf("3. Buscar produto\n");
        printf("4. Listar produtos\n");
        printf("5. Calcular altura da árvore\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Produto novoProduto;
                printf("Digite o codigo do produto: ");
                scanf("%d", &novoProduto.codigo);
                printf("Digite o nome do produto: ");
                scanf(" %[^\n]", novoProduto.nome);
                printf("Digite o preco do produto: ");
                scanf("%f", &novoProduto.preco);
                printf("Digite a quantidade em estoque do produto: ");
                scanf("%d", &novoProduto.quantidadeEstoque);

                raiz = insert(raiz, novoProduto);
                printf("Produto inserido com sucesso!\n");
                break;
            }
            case 2: {
                int codigo;
                printf("Digite o codigo do produto a ser removido: ");
                scanf("%d", &codigo);

                raiz = remover(raiz, codigo);
                break;
            }
            case 3: {
                int codigo;
                printf("Digite o codigo do produto a ser buscado: ");
                scanf("%d", &codigo);

                Node* resultado = buscar(raiz, codigo);
                if (resultado) {
                    printf("Produto encontrado:\n");
                    printf("Código: %d, Nome: %s, Preco: %.2f, Quantidade em Estoque: %d\n",
                           resultado->produto.codigo, resultado->produto.nome, resultado->produto.preco,
                           resultado->produto.quantidadeEstoque);
                } else {
                    printf("Produto nao encontrado!\n");
                }
                break;
            }
            case 4:
                printf("Lista de produtos:\n");
                listarProdutos(raiz);
                break;
            case 5:
                printf("A altura da árvore é: %d\n", altura(raiz));
                break;
            case 6:
                printf("Saindo do sistema de vendas...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 6);

    liberaArvore(raiz);

    return 0;
}