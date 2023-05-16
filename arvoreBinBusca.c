#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node* left; 
    struct node* right;
}Node;


Node* novoNode(int item){
    Node *n = (Node*)malloc(sizeof(Node));
    n->item = item;
    n->left = NULL;
    n->right = NULL;
    return n;
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
    
    return raiz;
}

/*  funcao alternativa para inserir na arvore, nao recursiva
void insert2(Node **raiz, int item){ //utiliza o ponteiro para ponteiro da raiz
    Node *aux = *raiz; 
    while(aux){ // aux!=0
        if(item < aux->item){ // o ponteiro raiz vai receber o endereco da esquerda ou da direita
            raiz = &aux->left; //recebe o conteudo desse endereco
        }
        else{
            raiz = &aux->right;
        }
        aux = *raiz; // aux recebe o conteudo do ponteiro raiz
    } 
    aux = (Node*)malloc(sizeof(Node));
    aux->item = item;
    aux->left = NULL;
    aux->right = NULL;
    *raiz = aux;
}*/

Node* buscar(Node *raiz, int item){
    if(raiz){ // se a raiz nao for nula
        if(item == raiz->item){
            return raiz;
        }
        else if(item < raiz->item){
            return buscar(raiz->left, item); 
        }
        else{
            return buscar(raiz->right, item);
        }
    }
    return NULL; // elemento nao esta na arvore
}

/* funcao busca alternativa, sem recursao
Node* busca2(Node *raiz, int item){
    while(raiz){  // raiz diferente de NULL
        if(item < raiz->item){
            raiz = raiz->left; // nao muda a raiz pois, essa variavel tem o escopo so dentro dessa funcao
        }
        else if(item > raiz->item){
            raiz = raiz->right;
        }
        else{
            return raiz;
        }
    }
    return NULL;
}
*/

int altura(Node *raiz){ // funcao para calcular a altura de uma arvore, o maior caminho entre uma folha e a raiz
    if(raiz == NULL){
        return -1; // retorna -1 pois se tiver so a raiz de elemento, a altura eh 0
    }
    else{ // verifica o caminho da esquerda e da direita para verificar qual eh maior e portanto eh a altura
        int esq = altura(raiz->left); 
        int dir = altura(raiz->right);
        if(esq > dir){
            return esq+1;
        } 
        else{
            return dir+1; // soma 1 devido a chamada recursiva 
        }
    }
}

int quantidadeNos(Node *raiz){
    if(raiz == NULL){
        return 0; // caso base
    }
    else{
        return 1 + quantidadeNos(raiz->left) + quantidadeNos(raiz->right);
    }     // 1 da raiz, e vai contando recursivamente os nos da esquerda e a direita
}

int quantidadeFolhas(Node *raiz){ // folhas == nohs sem filhos
    if(raiz == NULL){
        return 0; // caso base
    }
    else if(raiz->left == NULL && raiz->right==NULL){
        return 1; // sem filhos a esq e a direita, entao e folha
    }
    else{ // o noh tem filhos ou a esq ou a direita ou nos dois
        return quantidadeFolhas(raiz->left) + quantidadeFolhas(raiz->right); // percorre recursivamente ate chegar no noh sem filhos 
    }
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
            return raiz;
        }
    }

}

void liberaArvore(Node* raiz){
    if(raiz != NULL){
        liberaArvore(raiz->left);
        liberaArvore(raiz->right);
        free(raiz);
    }
}


void printPrefixo(Node *raiz){
    if(raiz != NULL){
        printf(" %d", raiz->item);
        printPrefixo(raiz->left);
        printPrefixo(raiz->right);
    }
}

void printInfixo(Node *raiz){
    if(raiz != NULL){
        printInfixo(raiz->left);
        printf(" %d", raiz->item);
        printInfixo(raiz->right);
    }
}

void printPosfixo(Node *raiz){
    if(raiz != NULL){
        printPosfixo(raiz->left);
        printPosfixo(raiz->right);
        printf(" %d", raiz->item);
    }
}


int main(){
    int opcao, valor;
    Node *raiz = NULL;
    Node *busca;
    
    do{
        printf("\n0-Sair\n1-Inserir\n2-Imprimir\n3-Buscar\n4-Calcular altura\n5-Tamanho\n6-Quantidade de folhas\n7-Remover\n");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("\nDigite um valor: ");
            scanf("%d", &valor);
            raiz = insert(raiz, valor);
            // insert2(raiz, valor);
            break;
        case 2:
            printf("\nImpressao prefixa: \n");
            printPrefixo(raiz);
            printf("\n");
            printf("\nImpressao infixa: \n");
            printInfixo(raiz);
            printf("\n");
            printf("\nImpressao posfixa: \n");
            printPosfixo(raiz);
            printf("\n");
            break;
        case 3:
            printf("Digite o item a ser buscado: ");
            scanf("%d", &valor);
            // busca = buscar2(raiz, valor);
            busca = buscar(raiz, valor);
            if(busca){
                printf("Valor encontrado: %d\n", busca->item);
            }
            else{
                printf("Valor nao encontrado!\n");
            }
            break;
        case 4:
            printf("A altura da arvore: %d\n", altura(raiz));
            break;
        case 5:
            printf("Quantidade de nos: %d", quantidadeNos(raiz));
            break;
        case 6:
            printf("Quantidade de folhas: %d", quantidadeFolhas(raiz));
            break;
        case 7:
            printInfixo(raiz);
            printf("\n");
            printf("Digite valor a ser removido:\n");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        default:
            if(opcao != 0)
                printf("\nOpcao invalida!\n");
            break;
        }


    }while(opcao != 0);
}
