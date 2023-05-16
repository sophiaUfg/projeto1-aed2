#include <stdio.h>
#include <stdlib.h>

/*O que pode desbalancear uma ArvoreBinaria: Insercao, Remocao*/

typedef struct node{
    int item;
    struct node* left; 
    struct node* right;
    int altura; // campo que registra a altura desse noh
}Node;

Node* novoNode(int item){
    Node *n = (Node*)malloc(sizeof(Node));
    n->item = item;
    n->left = NULL;
    n->right = NULL;
    n->altura = 0;
    return n;
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

Node* insert(Node *raiz, int item){
    if(raiz == NULL){
        return novoNode(item);
    }
    else if(item <= raiz->item){
        raiz->left = insert(raiz->left, item);
    }
    else{
        raiz->right = insert(raiz->right, item);
    }

    //recalcula a altura de todos os nos entre raiz e o novo noh inserido
    raiz->altura = maior(altura(raiz->left),altura(raiz->right)) + 1;
    
    //verifica se precisa balancear
    raiz = balancear(raiz);
    return raiz;
}

Node* remover(Node *raiz, int item){
    if(raiz == NULL){
        printf("Valor nao encontrado!\n"); 
        return NULL;
    }
    else{
        if(raiz->item == item){ // achou o item na arvore
            //remove noh folhas, sem filhos
            if(raiz->right == NULL && raiz->left == NULL){
                free(raiz);
                printf("Elemento removido: %d\n", item);
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
                    raiz->item = aux->item;
                    aux->item = item; // elemento trocado
                    raiz->left = remover(raiz->left, item);
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
                    printf("Elemento removido: %d!\n", item);
                    return aux; // retorna o aux para a chamada recursiva e altera os filhos do noh pai, apos a remocao
                }
            }
        }
        else{ // procura recursivamente onde o item a ser removido esta
            if(item < raiz->item){
                raiz->left = remover(raiz->left, item);
            }
            else{
                raiz->right = remover(raiz->right, item);
            }
        }

        //Recalcula altura de todos os nos
        raiz->altura = maior(altura(raiz->left),altura(raiz->right)) + 1;
    
        //verifica se precisa balancear
        raiz = balancear(raiz); 
        
        return raiz;
    }
}

void imprimir(Node *raiz, int nivel){ //printar a arvore balanceada, imprime a arvore deitada
    int i;
    if(raiz){
        imprimir(raiz->right, nivel + 1);
        printf("\n\n");

        for ( i = 0; i < nivel; i++) {
            printf("\t");
        }

        printf("%d", raiz->item);
        imprimir(raiz->left, nivel + 1);
    }
}

int main(){
    int opcao, valor;
    Node *raiz = NULL;

    do{
        printf("\n0-Sair\n1-Inserir\n2-Remover\n3-Imprimir\n");
        scanf("%d", &opcao);

        switch (opcao) {
        case 0:
            printf("Saindo!\n");
            break;
        case 1:
            printf("Digite o valor a ser inserido: \n");
            scanf("%d", &valor);
            raiz = insert(raiz, valor);
            break;
        case 2:
            printf("Digite o valor a ser removido:\n");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        case 3:
            imprimir(raiz, 1);
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }
    }while(opcao!=0);

    return 0;
}
