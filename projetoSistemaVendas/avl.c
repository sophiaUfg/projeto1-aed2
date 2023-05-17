#include <stdio.h>
#include <stdlib.h>
#include "produto.h"

/*O que pode desbalancear uma ArvoreBinaria: Insercao, Remocao*/

typedef struct node{
    Produto produto;
    struct node* left; 
    struct node* right;
    int altura; // campo que registra a altura desse noh
}Node;

Node* novoNode(Produto produto){
    Node *n = (Node*)malloc(sizeof(Node));
    n->produto = produto;
    n->left = NULL;
    n->right = NULL;
    n->altura = 0;
    return n;
}

Node* buscar(Node *raiz, int codigo){
    if(raiz){ // se a raiz nao for nula
        if(codigo == raiz->produto.codigo){
            return raiz;
        }
        else if(codigo < raiz->produto.codigo){
            return buscar(raiz->left, codigo); 
        }
        else{
            return buscar(raiz->right, codigo);
        }
    }
    return NULL; // elemento nao esta na arvore
}

int maior(int a, int b){
    return (a>b)? a: b;
} // importante p comparar alturas das subarvores esq e dir e definir a altura no noh raiz

int altura(Node *no){ // funcao para calcular a altura de um noh
    if(no == NULL){
        return -1; // caso seja nulo
    }
    else{ 
        return no->altura;
    }
}

int fatorDeBalanceamento(Node *no){ // define qual tipo de rotacao necessaria
    if(no){
        return (altura(no->left) - altura(no->right));
    }
    else{
        return 0;
    }
} // fb > 1 -> arvore desbalanceada p esquerda
  // fb < -1 -> arvore desbalanceada p direita

Node* rotacaoEsquerda(Node *raiz){ //chamada quando o fb for menor que -1
    Node *r, *l; 
    r = raiz->right; //l vai ser nova raiz
    l = r->left;

    r->left = raiz;
    raiz->right = l; // antiga raiz aponta p o antigo filho a esq da nova raiz
    
    //calcula novas alturas
    raiz->altura = maior(altura(raiz->right), altura(raiz->right)+1);
    r->altura = maior(altura(r->left), altura(r->right)+1);

    return r; // retorna a nova raiz
}

Node* rotacaoDireita(Node *raiz){ //chamada quando o fb for maior que 1
    Node *r, *l; 
    l = raiz->left; //l vai ser nova raiz
    r = l->right;

    l->right = raiz;
    raiz->left = r; // antiga raiz aponta p o antigo filho a esq da nova raiz
    
    //calcula novas alturas
    raiz->altura = maior(altura(raiz->right), altura(raiz->right)+1);
    l->altura = maior(altura(l->left), altura(l->right)+1);

    return l; // retorna a nova raiz
}

//rotacaoes duplas
Node* rotacaoDireitaEsquerda(Node *raiz){
    raiz->right = rotacaoDireita(raiz->right);
    return rotacaoEsquerda(raiz);
}

Node* rotacaoEsquerdaDireita(Node *raiz){
    raiz->left = rotacaoEsquerda(raiz->left);
    return rotacaoDireita(raiz);
}

Node* balancear(Node *raiz){
    int fb = fatorDeBalanceamento(raiz);

    //Rotacao a esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->right)<=0){
        raiz = rotacaoEsquerda(raiz);
    } //Rotacao a direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->left)>=0){
        raiz = rotacaoDireita(raiz);
    } // Rotacao Direita Esquerda
    else if(fb < -1 && fatorDeBalanceamento(raiz->right)>0){
        raiz = rotacaoDireitaEsquerda(raiz);
    } //Rotacao Esquerda Direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->left)<0){
        raiz = rotacaoEsquerdaDireita(raiz);
    }

    return raiz;

}

Node* insert(Node *raiz, Produto produto){
    if(raiz == NULL){
        return novoNode(produto);
    }
    else if(produto.codigo <= raiz->produto.codigo){
        raiz->left = insert(raiz->left, produto);
    }
    else{
        raiz->right = insert(raiz->right, produto);
    }

    //recalcula a altura de todos os nos entre raiz e o novo noh inserido
    raiz->altura = maior(altura(raiz->left),altura(raiz->right)) + 1;
    
    //verifica se precisa balancear
    raiz = balancear(raiz);
    return raiz;
}

Node* remover(Node *raiz, int codigo){
    if(raiz == NULL){
        printf("Valor nao encontrado!\n"); 
        return NULL;
    }
    else{
        if(raiz->produto.codigo == codigo){ // achou o item na arvore
            //remove noh folhas, sem filhos
            if(raiz->right == NULL && raiz->left == NULL){
                free(raiz);
                printf("Produto de codigo %d removido\n", codigo);
                return NULL; // retorna nulo apos liberar a memoria pq se tiver noh pai ele vai passar a apontar pra NULL
            }
            else{
                //remove noh com 2 filhos
                if(raiz->left != NULL && raiz->right != NULL){
                    //procura em uma subarvore o elemento mais a esq ou a dir e troca o conteudo de posicao com o noh com 2 filhos
                    Node *aux = raiz->left; // subarvore a esquerda
                    while(aux->right != NULL){ // loop ate achar o elemento mais a dir no caso da subarvore esq
                        aux = aux->right;
                    }
                    raiz->produto.codigo = aux->produto.codigo;
                    aux->produto.codigo = codigo; // elemento trocado
                    raiz->left = remover(raiz->left, codigo);
                    return raiz;
                }
                else{
                    //remove noh com 1 filho
                    Node *aux; // aux que armazena o filho da esq ou da dir 
                    if(raiz->left != NULL){ // verifica se o filho esta a esq ou a dir
                        aux = raiz->left;
                    }
                    else{
                        aux = raiz->right;
                    }
                    free(raiz);
                    printf("Elemento de codigo %d removido!\n", codigo);
                    return aux; // retorna o aux para a chamada recursiva e altera os filhos do noh pai, apos a remocao
                }
            }
        }
        else{ // procura recursivamente onde o item a ser removido esta
            if(codigo < raiz->produto.codigo){
                raiz->left = remover(raiz->left, codigo);
            }
            else{
                raiz->right = remover(raiz->right, codigo);
            }
        }

        //Recalcula altura de todos os nos
        raiz->altura = maior(altura(raiz->left),altura(raiz->right)) + 1;
    
        //verifica se precisa balancear
        raiz = balancear(raiz); 
        
        return raiz;
    }
}

void listarProdutos(Node *raiz){
    if(raiz){
        listarProdutos(raiz->left);
        printf("Código: %d, Nome: %s, Preco: %.2f, Quantidade em Estoque: %d\n",raiz->produto.codigo, raiz->produto.nome, raiz->produto.preco, raiz->produto.quantidadeEstoque);
        listarProdutos(raiz->right);
    }
}

void liberaArvore(Node* raiz){
    if(raiz != NULL){
        liberaArvore(raiz->left);
        liberaArvore(raiz->right);
        free(raiz);
    }
}
