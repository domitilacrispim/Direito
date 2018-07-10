/******************************************************************************
                             heap.c
   Este programa implementa um heap MAXIMO em uma implementação estática de uma 
   árvore binária. Nao usa a posicao 0 (zero) do arranjo.
******************************************************************************/
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#define true 1
#define false 0

typedef int bool;
int linha, global=1;

typedef struct folha {
	int elementos[4];
	int linha_arq[4];
	int cheio;
} folha;

folha hash[100];	

typedef struct {
  int * A;
  int tamanhoAtual;
  int tamanhoMaximo;
} HEAP;


FILE * pFile;

bool insere ( int a ) {
	 pFile = fopen ("registros","a");
	//printf("Insira o nome\n");
	//char nome[64000];
	char nome = "meu deus";
	int idade = 13;
	//gets(nome);
	//printf("Insira a idade\n");
	//scanf("%d", &idade);
	getchar();
	fprintf(pFile, "%d %d ", a, strlen(nome));
	fputs(nome,pFile);
	fclose(pFile); 
	linha++;
	return true;
}

void inicializarHeap(HEAP * h, int tamanhoMax){
  h->A = (int*) malloc(sizeof(int)*(tamanhoMax+1));
  h->tamanhoAtual = 0;
  h->tamanhoMaximo = tamanhoMax;
}

void destruirHeap(HEAP * h){
  int tamanho = h->tamanhoMaximo;
  free(h->A);
  h->tamanhoMaximo=0;
  h->tamanhoAtual=0;
}

int pai(int i){
  return i/2;
}

int filhoEsquerda(int i){
  return 2*i;
}

int filhoDireita(int i){
  return 2*i + 1;
}

/* metodo auxiliar que pressupoe que o heap para qualquer j>i estah ordenado
   porem o elemento i nao eh necessariamente maior que seus filhos           */
void maxHeapify(HEAP * h, int i){
  int esq = filhoEsquerda(i);
  int dir = filhoDireita(i);
  int temp;
  int maior = i;
  if ((esq <= h->tamanhoAtual) && (h->A[esq]>h->A[i])) maior = esq;
  if ((dir <= h->tamanhoAtual) && (h->A[dir]>h->A[maior])) maior = dir;
  if (maior != i) {
     temp = h->A[i];
     h->A[i] = h->A[maior];
     h->A[maior] = temp;
     maxHeapify(h,maior);
  }
}

// Constroi heap a partir do arranjo usando o metodo maxHeapify
void construirHeapMaximo(HEAP * h){
  int i;
  int metadeTamanho = h->tamanhoAtual/2;
  for (i=metadeTamanho;i>0;i--) maxHeapify(h,i);
}

// Insere no final do arranjo do heap
bool inserirForaDeOrdem(HEAP * h, int valor){
  if (h->tamanhoAtual < h->tamanhoMaximo){
    (h->tamanhoAtual)++;
    h->A[h->tamanhoAtual] = valor;
    	insere(valor);
    return true;
  }
  return false;
}


// Imprime o arranjo (na ordem que estiver)
void imprimirArranjo(HEAP h){
  int tamanho = h.tamanhoAtual;
  int i;
  for (i=1;i<=tamanho;i++) printf("%d ",h.A[i]);
  printf("\n");
}


// Imprime elementos em ordem decrescente e esvazia o heap
void heapSort(HEAP * h){
  int tamanho = h->tamanhoAtual;
  int i, temp;
  construirHeapMaximo(h);  // se o arranjo jah for um heap, nao precisa desta linha
  for (i=tamanho;i>1;i--){
     temp = h->A[1];
     h->A[1] = h->A[i];
     h->A[i] = temp;
     //printf("%d ",temp);
     (h->tamanhoAtual)--;
     maxHeapify(h,1);
  }
  //printf("\n");
  h->tamanhoAtual = tamanho;;
}

bool inserirHeap(HEAP * h, int chave){
  int i, temp;
  if (h->tamanhoAtual == h->tamanhoMaximo) return false;
  (h->tamanhoAtual)++;
  i = h->tamanhoAtual;
  h->A[i] = chave;
	insere(chave);
  while ((i>1) && (h->A[pai(i)]<h->A[i])){
     temp = h->A[i];
     h->A[i] = h->A[pai(i)];
     h->A[pai(i)] = temp;       
     i = pai(i);
  }
  return true;
}

int percursoPreOrdem(HEAP* h, int atual){
  if (atual <= h->tamanhoAtual){
    printf("%i ", h->A[atual]);
    percursoPreOrdem(h, filhoEsquerda(atual));
    percursoPreOrdem(h, filhoDireita(atual));
  }
}

int alturaHeap(HEAP* h){
  int altura = -1;
  int i = 1;
  while (i <= h->tamanhoAtual){
    i = filhoEsquerda(i);
    altura++;
  }
  return altura;
}


int inserehash ( int id){
	int aux=id%(int)pow(2,global);
	folha aux2;
	if(hash[aux].cheio!=4){
		hash[aux].elementos[hash[aux].cheio]=id;
		hash[aux].linha_arq[hash[aux].cheio]=linha-1;
		hash[aux].cheio++;
		return 0;
	}
	int mud;
	// inserir caso  q duplica o diretorio
	aux2=hash[aux]; int lin = linha ;
	for ( int i=0; i<4; i++){
		if(hash[aux].elementos[i]%(int)pow(2,global)!=aux) mud++;
		
	}
	if( mud!=4 && mud>0){
		hash[aux].cheio=0;
		global++;
		for ( int i=0; i<4; i++){
				linha=aux2.linha_arq[i]+1;
				inserehash( aux2.elementos[i]);
		}
		inserehash(id);
	}
	linha=lin;
}

int main(){
  HEAP meuHeap;
  inicializarHeap(&meuHeap, 100);
  inserirForaDeOrdem(&meuHeap,10);
  inserirForaDeOrdem(&meuHeap,5);
  inserirForaDeOrdem(&meuHeap,3);
  inserirForaDeOrdem(&meuHeap,20);
  inserirForaDeOrdem(&meuHeap,8);
  inserirForaDeOrdem(&meuHeap,6);
  inserirForaDeOrdem(&meuHeap,15);
  inserirForaDeOrdem(&meuHeap,1);
  inserirForaDeOrdem(&meuHeap,18);
  inserirForaDeOrdem(&meuHeap,40);
  inserirForaDeOrdem(&meuHeap,17);
  inserirForaDeOrdem(&meuHeap,12);
  imprimirArranjo(meuHeap);
  construirHeapMaximo(&meuHeap);
  imprimirArranjo(meuHeap);
  percursoPreOrdem(&meuHeap,1);
  printf("\n");
  heapSort(&meuHeap);  
  imprimirArranjo(meuHeap);
  destruirHeap(&meuHeap);


  printf("\nTestes parte 2\n");
  inicializarHeap(&meuHeap, 50);
  inserirHeap(&meuHeap,10);
  printf("Altura heap: %i\n", alturaHeap(&meuHeap));
  inserirHeap(&meuHeap,5);
  printf("Altura heap: %i\n", alturaHeap(&meuHeap));
  inserirHeap(&meuHeap,3);
  printf("Altura heap: %i\n", alturaHeap(&meuHeap));
  inserirHeap(&meuHeap,20);
  printf("Altura heap: %i\n", alturaHeap(&meuHeap));
  inserirHeap(&meuHeap,8);
  printf("Altura heap: %i\n", alturaHeap(&meuHeap));
  inserirHeap(&meuHeap,6);
  printf("Altura heap: %i\n", alturaHeap(&meuHeap));
  inserirHeap(&meuHeap,15);
  printf("Altura heap: %i\n", alturaHeap(&meuHeap));
  inserirHeap(&meuHeap,1);
  printf("Altura heap: %i\n", alturaHeap(&meuHeap));
  inserirHeap(&meuHeap,18);
  printf("Altura heap: %i\n", alturaHeap(&meuHeap));
  inserirHeap(&meuHeap,40);
  printf("Altura heap: %i\n", alturaHeap(&meuHeap));
  inserirHeap(&meuHeap,17);
  printf("Altura heap: %i\n", alturaHeap(&meuHeap));
  inserirHeap(&meuHeap,12);
  imprimirArranjo(meuHeap);
  /*o Heap ja esta corretamente montado, o comando a seguir nao alterara nada*/
  construirHeapMaximo(&meuHeap);
  imprimirArranjo(meuHeap);
  percursoPreOrdem(&meuHeap,1);
  printf("\n");  
  heapSort(&meuHeap);  
  imprimirArranjo(meuHeap);
  destruirHeap(&meuHeap);
 
}
