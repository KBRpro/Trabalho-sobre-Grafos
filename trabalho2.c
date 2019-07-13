#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define Type int

// Nó de lista
typedef struct _node {
    Type valor;
    struct _node* next;
    struct _node* down;
    int peso;
    char cor;
    int pai;
    int visitado;
    int finalizado;
} node;


typedef struct TAD_LIST {
    node* no;
    int vertices;
    int adotados;
    int size;
}list;

// Aloca memória para um 'node' e define o endereço do próximo como NULL
node* new_node(Type valor,int peso) {
    node* n = malloc(sizeof(node));
    n->valor = valor;
    n->next  = NULL;
    n->down = NULL;
    n->peso = peso;
    n->cor = 'b';
    n->pai = -1;
    n->visitado = -1;
    n->finalizado= -1;
    return n;
}

// Aloca memória inicial para a lista
list* new_list()
{
    list *lista=malloc(sizeof(list));
    lista->no=NULL;
    lista->vertices=0;
    lista->adotados=0;
    lista->size=0;
    return lista;
}

int buscarVertice(list *G,int valor1) //encontra a posicao do vertice na horizontal
{
	node *ptr=G->no;
	int pos=-1;
	int i=0;
	while(ptr!=NULL)
	{
		if(ptr->valor==valor1)
			pos=i;
		i++;
		ptr=ptr->down;
	}
	return pos;
}

Type list_pop_front(list* lista) { //retorna o vertice head da lista
    Type valor;
    valor=lista->no->valor;
    lista->no=lista->no->next;
    lista->size--;
    return valor;
}

void list_push_back(list* lista, Type value) { //insere como o ultimo vertice da lista
  node *aux=new_node(value,-1);
  if(lista->no==NULL)
    lista->no=aux;
  else
  {
    node *ptr=lista->no;
    while(ptr->next!=NULL)
      ptr=ptr->next;
    ptr->next=aux;
  }
  lista->size++;
}

void list_push_front(list* lista, Type value) { //insere como o primeiro vertice da lista
    node *aux=new_node(value,-1);
    aux->next=lista->no;
    lista->no=aux;
    lista->size++;
}

Type list_pop_back(list* lista) //retorna o ultimo vertice da lista
{
   Type retorno;
   node *ptr=lista->no;
   if(lista->size==1)
   {
       retorno=lista->no->valor;
       lista->no=NULL;
       lista->size=0;
   }
    else
    {
        while(ptr->next->next!=NULL)
            ptr=ptr->next;
        retorno=ptr->next->valor;
        ptr->next=NULL;
        lista->size--;
    }
    return retorno;
}

Type list_erase(list* lista, int i){ //retira um vertice de posição i da lista
    Type retorno;
    int pos=0;
    node *ptr=lista->no;
    node *ptr1=lista->no;
    if(i==0)
        retorno=list_pop_front(lista);
    else if(i==lista->size)
        retorno=list_pop_back(lista);
    else if(i==-1)
      return -1;
    else
    {
        while(pos<i-1)
        {
           ptr=ptr->next;
           ptr1=ptr1->next;
           pos++;
        }
        ptr1=ptr1->next;
        retorno=ptr1->valor;
        ptr1=ptr1->next;
        ptr->next=ptr1;
        lista->size--;
    }
    return retorno;
}

int menordaPilha(list *aux) //retorna a posição do menor vertice da lista
{
  node *ptr=aux->no;
  int minimo=99999999;
  while(ptr!=NULL)
  {
    if(ptr->peso < minimo)
      minimo=ptr->valor;
    ptr=ptr->next;
  }
  ptr=aux->no;
  int i=0;
  if(minimo!=99999999)
  {
    while(ptr->valor!=minimo)
    {
      ptr=ptr->next;
      i++;
    }
  }
  else
    i=-1;
  return i;
}

int pertencePILHA(list *aux,int valor) //diz se o valor esta contido na pilha
{
  node *ptr=aux->no;
  int esta=-1;
  while(ptr!=NULL)
  {
      if(ptr->valor==valor)
        esta=1;
      ptr=ptr->next;
  }
  return esta;
}

int checarPeso(list *G,int valor) //retorna o peso de um vertice
{
  node *ptr=G->no;
  while(ptr->valor!=valor)
    ptr=ptr->down;
  return ptr->peso;
}

node* acharMinimo(list* G,int pai) //acha a aresta de menor peso de um vertice
{
  node *aux=G->no;
  while(aux->valor!=pai)
    aux=aux->down;
  node *minimo=aux;
  node *ptr=aux;
  while(ptr!=NULL)
  {
    if(ptr->peso < minimo->peso)
      minimo=ptr;
    ptr=ptr->next;
  }
  return minimo;
}

void marcarVisitado(list *G,int vertice,int ordem,int pai)
{
  node *ptr=G->no;
  while(ptr->valor!=vertice) //chega ate o vertice desejado
    ptr=ptr->down;
  ptr->visitado=ordem; //marca a ordem do mesmo na busca
  if(pai!=999)
    ptr->pai=pai;
}

void printarOrdem(list *G)
{
  node *ptr=G->no;
  int ordem=1;//ordem comeca do numero 1 por representar o primeiro elemento da busca;
  int Nconexo=0;
  while(ptr!=NULL) //confere se o grafo eh conexo
  {
    if(ptr->visitado==-1)
      Nconexo=1;
    ptr=ptr->down;
  }
  if(Nconexo==0) //procede a impressao caso o grafo seja conexo
  {
    printf("Segue em ordem os elementos visitados pela busca:\n");
    while(ordem!=G->vertices+1)
    {
      ptr=G->no;
      while(ptr!=NULL)
      {
        if(ptr->valor==ordem) //printa os elementos da busca em ordem;
        {
          printf("[%d]pai:%d distancia:%d\n",ptr->valor,ptr->pai,ptr->visitado);
        }
        ptr=ptr->down;
      }
      ordem++;
    }
  }
  else
    printf("A busca nao foi completa pois o grafo nao é conexo\n");
}

int checarVisitado(list *G,int vertice) //percorre o grafo ate e retorna a ordem de visita
{
  node *ptr=G->no;
  while(ptr->valor!=vertice)
    ptr=ptr->down;
  return ptr->visitado;
}

char checarcor(list *G,int vertice) //funcao para dizer a cor associada ao vertice procurado;
{
  node *ptr=G->no;
  while(ptr->valor!=vertice) //desce verticalmente ate o vertice desejado;
    ptr=ptr->down;
  return ptr->cor; // retorna a cor do mesmo;
}

void printarProfundidade(list *G) //funcao utilizada para printar dados da busca em profundidade
{
  node *ptr=G->no;
  printf("Segue a ordem dos vertices com sua descoberta e finalizacao:\n");
  while(ptr!=NULL)
  {
    printf("[%d] pai:%d, descoberta:%d, finalizacao:%d\n",ptr->valor,ptr->pai,ptr->visitado,ptr->finalizado);
    ptr=ptr->down;
  }
}

void atualizarPilha(list* G,list* aux)
{
  node *ptr=aux->no;
  while(ptr!=NULL)
  {
    ptr->peso=checarPeso(G,ptr->valor);
    ptr=ptr->next;
  }
}

void relax(list* G,int vertice,int aresta,int peso) //algoritmo para classificar se o caminho atual é mesmo o minimo no DIJKSTRA;
{
  node *ptr=G->no;
  node *ptr1=G->no;
  while(ptr->valor!=aresta)
    ptr=ptr->down;
  while(ptr1->valor!=vertice)
    ptr1=ptr1->down;
  if(ptr->peso>(ptr1->peso+peso))
  {
    ptr->peso=ptr1->peso+peso;
    ptr->pai=vertice;
  }
}

node* acharVertice(list* G,int valor) //encontra o vertice necessário
{
  node *ptr=G->no;
  while(ptr->valor!=valor)
    ptr=ptr->down;
  return ptr;
}

void inserirVertice(list *G,int value)
{
  if(buscarVertice(G,value)==-1) //verifica se nao ha um vertice repitido
  {
  	node *ptr=malloc(sizeof(node));
  	ptr->valor=value;
    ptr->peso=999;
    ptr->cor='b';
  	ptr->next=NULL;
  	ptr->down=NULL;
    ptr->pai=-1;
    ptr->visitado=-1;
  	if(G->no==NULL) //verifica se existe pelo menos um vertice
  		G->no=ptr; //caso nao exista adiciona na primeira posicao
  	else //caso exista pelo menos um vertice entra no else
  	{
  		node *ptr1=G->no;
  		while(ptr1->down!=NULL) // percorre verticalmente o grafo ate a ultima posicao
  		{
  			ptr1=ptr1->down;
  		}
  		ptr1->down=ptr; //adiciona o novo vertice que toma agora a ultima posicao do grafo
  	}
    G->vertices++; //aumenta o numero de vertices na predefinicao da estrutura lista
  }
}

void inserirAresta(list *G,int valor1,int valor2,int peso)
{
	int i=0;
	int existe=0;
	node *ptr1=new_node(valor2,peso); //cria um novo no apartir da funcao de lista
	int pos=buscarVertice(G,valor1); //busca o vertice no qual seria aplicado a aresta
	node *ptr=G->no;
  if(pos!=-1) //procura a existencia do vertice
  {
  	while(i!=pos) //desce na horizontal ate o vertice
  	{
  		ptr=ptr->down;
  		i++;
  	}
  	while(ptr->next!=NULL) //verifica se ha uma aresta repitida ao valor
  	{
  		if(ptr->valor==valor2)
  			existe=1;
  		ptr=ptr->next;
  	}
    if(ptr->valor==valor2)
      existe=1;
  	if(existe==0) //se nao existir adiciona a aresta
  		ptr->next=ptr1;
  }
}


void removerAresta(list *G,int verticeX,int verticeY)
{
  node *ptr=G->no; //cria-se um no identico a primeira posicao do grafo para nao alterar o grafo diretamente
  node *teste;
  node *head;
  node *proximo;
  int pos=buscarVertice(G,verticeY); //busca a posicao do vertice
  int i=0;
  int existencia=0;
  if(pos!=-1)//verifica existencia do vertice
  {
    while(i!=pos) //percorre verticalmente o grafo ate a posicao do vertice no qual a aresta se encontra
    {
      ptr=ptr->down;
      i++;
    }
    if(ptr->next!=NULL)
      teste=ptr->next;//para n considerar o vertice.
    else
      teste=NULL;
    while(teste!=NULL)//verifica existencia da aresta
    {
      if(teste->valor==verticeX) //caso o vertice seja encontrado e aplicado o valor 1 a variavel existencia
      {
        existencia=1;
        break;
      }
      teste=teste->next;
    }
    if(existencia==1) // caso exista a aresta pode-se remover
    {
      head=ptr->next;
      if(verticeX==head->valor) //remocao caso seja o primeiro vertice e aresta
        ptr->next=head->next;
      else if(head->next==NULL) //remocao caso exista apenas o vertice e nenhuma aresta
        ptr->next=NULL;
      else //remocao em todos os outros casos
      {
        while(head->next->valor!=verticeX)
          head=head->next;
        node *delete=head->next;
        proximo=head->next->next;
        head->next=proximo;
      }
    }
  }
}


void removerVertice(list *G,int valor)
{
  node *ptr=G->no;
  node *ptr1;
  node *ptrC;
  node *ptrR;
  node *ptrUnder;
  int i=0;
  int pos=buscarVertice(G,valor); //busca a posicao do vertice
  if(pos!=-1)//confere existencia do vertice,caso for -1 o mesmo nao existe
  {
  	while(ptr!=NULL) //remove arestas com indice do vertice
    {
      if(ptr->valor!=valor)
        removerAresta(G,valor,ptr->valor);
      ptr=ptr->down;
    }
    ptr=G->no;
    if(pos==0) //caso o vertice seja o primeiro efetua a remocao
    {
      ptr1=G->no;
      ptr=ptr->down;
      G->no=ptr;
    }
    else //remocao caso o vertice seja qualquer outro
    {
      int i=0;
      while(i!=pos-1) //encontramos a posicao anterior ao vertice que desejamos remover
      {
        ptr=ptr->down;
        i++;
      }
      ptrR=ptr->down;
      ptrC=ptrC->next;
      node *delete=ptr->down;
      free(delete); //libera a memoria alocada pelo vertice utilizado <------------
      ptrUnder=ptr->down->down;
      ptr->down=ptrUnder;
    }
    G->vertices--; //reduz o numero de vertices na struct lista
  }
}


//visualizar grafo funciona da mesma forma que um printMATRIZ
void visualizarGrafo(list *G)
{
  node *ptr=G->no;
	node *ptr1;
  while(ptr!=NULL) //percorre verticalmente o grafo
  {
    ptr1=ptr;
		while(ptr1!=NULL) //percorre horizontalmente o grafo
		{
			printf("%d ->",ptr1->valor);
			ptr1=ptr1->next;
		}
		printf("\n");
		ptr=ptr->down;
  }
}

//funciona de forma que cada aresta sinaliza uma adjacencia e portanto um grau
int GrauVertice(list *G,int vertice)
{
  node *ptr=G->no;
  int grau=0;
  int i=0;
  int pos=buscarVertice(G,vertice); //busca a posicao do vertice desejado
  if(pos==-1)
    return 0; //caso ele nao exista o grau eh retornado como zero
  else
  {
    while(i!=pos)
    {
      ptr=ptr->down;
      i++;
    }
    while(ptr!=NULL) //caso o vertice exista o grau eh calculado ate o ponteiro ser nulo
    {
      ptr=ptr->next;
      grau++;
    }
    return grau-1;
  }
  free(ptr);
}

void MatrizAdjacencias(list *G)
{
  node *ptr=G->no;
  node *ptrL;
  int linhas=0;
  int colunas=0;
  int vertices=0;
  int i=0;
  if(G->no!=NULL) //confere se o grafo existe
  {
    while(ptr!=NULL)
    {
      ptr=ptr->down;
      vertices++; //confere o numero de vertices
    }
    int M[vertices][vertices]; //cria uma matriz quadrada sendo numero de vertices x numero de vertices
    while(linhas!=vertices) //define o valor de todas as linhas e coluna como 0
    {
      while(colunas!=vertices)
      {
        M[linhas][colunas]=0;
        colunas++; //percorre horizontalmente
      }
      colunas=0;
      linhas++; //percorre verticalmente
    }
    ptr=G->no;
    int vetor[vertices]; // cria um vetor com o numero de vertices
    while(ptr!=NULL)
    {
      vetor[i]=ptr->valor; //criacao de um vetor para comparacao com o valor de cada vertice;
      ptr=ptr->down; //percorre verticalmente o vertice
      i++;
    }
    ptr=G->no;
    colunas=0;
    linhas=0;
    int VV;
    while(ptr!=NULL) //aplicando em binario  a existencia das arestas em cada vertice na matriz
    {
      ptrL=ptr;
      int principal= ptrL->valor;
      while(colunas!=vertices)
      {
        while(ptrL!=NULL)
        {
          if(ptrL->valor==vetor[colunas] && ptrL->valor!=principal)
            M[linhas][colunas]=ptrL->peso; //caso o valor do vertice seja encontrado no vetor de vertices,o 1 e aplicado a sua devida posicao
          ptrL=ptrL->next; //percorre horizontalmente o grafo
        }
        ptrL=ptr;
        colunas++;
      }
      colunas=0;
      linhas++;
      ptr=ptr->down; //percorre verticalmente o grafo
    }
    linhas=0;
    colunas=0;
    printf("[V] | ");
    while(colunas!=vertices) //printar os vertices existentes da tabela
    {
      VV=vetor[colunas];
      printf("[%d] -> ",VV); //cria o head da tabela com os vertices existentes
      colunas++;
    }
    printf("\n");
    printf("----|--------------------------------------------------------------------------\n");
    colunas=0;
    linhas=0;
    while(linhas!=vertices)
    {
      printf("[%d] | ",vetor[linhas]); //printa os indices dos vertices na horizontal
      while(colunas!=vertices)
      {
        VV=M[linhas][colunas];
        printf("[%d] -> ",VV); //printar em binario as adjacencias;
        colunas++;
      }
      colunas=0;
      linhas++;
      printf("\n");
    }
  }
}

void BuscaLargura(list *G,int start)
{
  int visitado=0;
  int i=0;
  node *ptr=G->no;
  list *aux=new_list();
  int pos=buscarVertice(G,start); //procura o vertice para checar a existencia do mesmo;
  if(pos!=-1) //caso o vertice exista é realizada a busca;
  {
    while(i!=pos) //chega ate a posicao do vertice inicial
    {
      ptr=ptr->down;
      i++;
    }
    list_push_back(aux,ptr->valor);//insere o primeiro vertice a uma lista auxiliar que simula uma fila;
    ptr->pai=-1;
    visitado++;
    ptr->visitado++;
    while(aux->no!=NULL)
    {
      int atual=list_pop_front(aux);//pega o primeiro valor da fila para fazer a busca no mesmo;
      visitado--;
      node *ptr1=G->no;
      while(ptr1->valor!=atual) //procura o vertice que é o antigo primeiro vertice da fila;
        ptr1=ptr1->down;
      int visi=ptr1->visitado;
      while(ptr1!=NULL)//visita todos os vertices que possuem aresta com o vertice atual;
      {
        if(checarVisitado(G,ptr1->valor)==-1)
        {
          visitado++;
          marcarVisitado(G,ptr1->valor,visi+1,atual); //marca os vertices do laço como marcados;
          list_push_back(aux,ptr1->valor); //coloca os vertices adjacentes na fila para serem visitados na ordem;
        }
        ptr1=ptr1->next;
      }
    }
    free(aux);//libera a memoria da fila auxiliar;
  }
}

int DFSvisit(list* G,node *u,int tempo)
{
  node *v=u; //salva o endereço do head do vertice
  node *achar;
  u->cor='c'; //pinta o vertice de cinza
  tempo++;
  u->visitado=tempo; //salva o tempo de descoberta
  while(u!=NULL) //percorre todas as adjacencias do vertice inicial
  {
    if(u->cor=='b' && u->visitado==-1) //verifica se tem cor branca e se ja foi vizitado
    {
      achar=acharVertice(G,u->valor); //encontra o vertice referente à aresta encontrada
      if(achar->visitado==-1) //caso o vertice não tenha sido vizitado
      {
        achar->pai=v->valor;  //é setado o pai do mesmo para a ultima recorrencia da recursão
        tempo=DFSvisit(G,achar,tempo); // salvando e incrementando o tempo a cada inserção
      }
    }
    u=u->next;
  }
  v->cor='p'; //assim que todas as adjacencias são percorridas o mesmo fica preto
  tempo++;
  v->finalizado=tempo; //o tempo de finalização é salvo;
  return tempo;
}

void BuscaProfundidade(list *G)
{
  int tempo=0;
  node *ptr=G->no;
  ptr->pai=-1; //seta o pai do vertice inicial para -1
  ptr->visitado=1; //seta como o primeiro visitado tambem
  while(ptr!=NULL) //percorre todos os vertices do grafo
  {
    if(ptr->cor=='b') //para todo vertice de cor branca
      tempo=DFSvisit(G,ptr,tempo); //é feito o dfs e salvo o tempo de operação
    ptr=ptr->down;
  }
  printarProfundidade(G); //printa a busca
}

void PRIM(list *G,int start)
{
  node *ptr=G->no;
  node *auxiliar;
  list *aux=new_list(); //cria uma lista que ira simular uma fila
  int pos=buscarVertice(G,start); //busca a posição do vertice inicial
  if(pos!=-1) //checa se o vertice inicial existe
  {
    int i=0;
    while(i!=pos) //chega até a posição do vertice inicial
    {
      ptr=ptr->down;
      i++;
    }
    ptr->pai=-1; //seta o pai do vertice inicial
    ptr->peso=0; //seta o peso do vertice inicial
    node *fila=G->no;
    node *minimo;
    while(fila!=NULL) //enfila os vertices que não estão na lista em fila de menor peso
    {
      if(fila->valor!=start)
      {
        minimo=acharMinimo(G,fila->valor); //acha a aresta de valor minimo do vertice
        list_push_back(aux,fila->valor); //enfila o vertice
      }
      fila=fila->down;
    }
    list_push_front(aux,start);
    atualizarPilha(G,aux); //atualiza peso dos valores da pilha
    int vert=start;
    while(aux->no!=NULL)
    {
      pos=menordaPilha(aux); //encontra a posição do menor elemento da fila
      vert=list_erase(aux,pos); //remove o menor elemento da fila
      if(vert!=-1)
      {
        ptr=G->no;
        while(ptr->valor!=vert) //seta o valor do proximo ciclo de ptr para o menor caminho armazenado na fila
          ptr=ptr->down;
      }
      ptr=ptr->next;
      while(ptr!=NULL)
      {
        if((pertencePILHA(aux,ptr->valor)>0) && (ptr->peso < checarPeso(G,ptr->valor))) //checa se o valor da aresta esta na fila e se o peso dele é menor que o atual
        {
          node *checker=G->no;
          while(checker->valor!=ptr->valor)
            checker=checker->down;
          checker->pai=vert; //troca os pesos e pais caso o valor dessa aresta seja menor que o que estava armazenado anteriormente
          checker->peso=ptr->peso;
        }
        ptr=ptr->next;
      }
      atualizarPilha(G,aux); //atualiza pesos dos valores da pilha
    }
    node *printer=G->no;
    while(printer!=NULL)
    {
      printf("[%d] pai:%d, key:%d.\n",printer->valor,printer->pai,printer->peso);
      printer=printer->down;
    }
  }
  else
    printf("vertice inicial não existente\n");
}

void DIJKSTRA(list* G,int start)
{
  list *aux=new_list();
  node *ptr=G->no;
  int pos=buscarVertice(G,start); //encontra vertice inicial
  node *starter=G->no;
  if(pos!=-1) //verifica se o vertice inicial existe
  {
    int i=0;
    while(i!=pos)
    {
      starter=starter->down; //encontra o vertice inicial
      i++;
    }
    starter->pai=-1; //seta o pai do inicial para -1
    starter->peso=0; //seta o peso do inicial para 0
    while(ptr!=NULL)
    {
      if(ptr->valor!=start)
        list_push_back(aux,ptr->valor); //enfila todos os vertices
      ptr=ptr->down;
    }
    list_push_front(aux,start); //enfila o inicial
    atualizarPilha(G,aux); //atualiza o peso dos vertices na pilha
    node *ptr=G->no;
    int vert=starter->valor;
    while(aux->no!=NULL)
    {
      i=menordaPilha(aux);
      vert=list_erase(aux,i);
      if(vert!=-1)
      {
        ptr=G->no;
        while(ptr->valor!=vert)
          ptr=ptr->down;
        ptr=ptr->next;
        while(ptr!=NULL)
        {
          relax(G,vert,ptr->valor,ptr->peso);
          ptr=ptr->next;
        }
        atualizarPilha(G,aux);
      }
    }
    free(aux);
    node *printer=G->no;
    while(printer!=NULL)
    {
      printf("[%d]pai:%d,distancia:%d.\n",printer->valor,printer->pai,printer->peso);
      printer=printer->down;
    }
  }
  else
    printf("vertice inicial não existente\n");
}

int GrafoConexo(list *G)
{
  BuscaLargura(G,G->no->valor);//aplica uma busca em largura e se caso algum vertice nao foi visitado sabe-se que o grafo nao eh conexo;
  node *ptr=G->no;
  int conexo=1;
  while(ptr!=NULL)
  {
    if(ptr->visitado==-1)
      conexo=0; //caso algum vertice nao for visitado na busca em largura o grafo altera o status da conectividade para 0;
    ptr=ptr->down;
  }
  if(conexo==0)
    printf("grafo Nao Conexo\n");
  else
    printf("Grafo Conexo\n");
  free(ptr);
}

int main(void)
{
	int escolha=0;
	int verticeI,verticeJ;
    int peso;
	list *G=new_list(); //aloca o grafico na estrutura lista
	/*Grafo para teste(utilizado nos slides de busca em largura)
	inserirVertice(G,1);//r
	inserirVertice(G,2);//s
	inserirVertice(G,3);//t
	inserirVertice(G,4);//u
	inserirVertice(G,5);//v
	inserirVertice(G,6);//w
	inserirVertice(G,7);//x
	inserirVertice(G,8);//y
	inserirAresta(G,1,2,1);
	inserirAresta(G,2,1,1);
	inserirAresta(G,1,5,1);
	inserirAresta(G,5,1,1);
	inserirAresta(G,2,6,1);
	inserirAresta(G,6,2,1);
	inserirAresta(G,3,6,1);
	inserirAresta(G,6,3,1);
	inserirAresta(G,3,7,1);
	inserirAresta(G,7,3,1);
	inserirAresta(G,6,7,5);
	inserirAresta(G,7,6,5);
	inserirAresta(G,4,7,1);
	inserirAresta(G,7,4,1);
	inserirAresta(G,3,4,1);
	inserirAresta(G,4,3,1);
	inserirAresta(G,4,8,1);
	inserirAresta(G,8,4,1);
	inserirAresta(G,7,8,1);
	inserirAresta(G,8,7,1);*/
	//Grafo para teste(utilizado nos slides de busca em profundidade)
  /*
	inserirVertice(G,1);//y
	inserirVertice(G,2);//z
	inserirVertice(G,3);//s
	inserirVertice(G,4);//t
	inserirVertice(G,5);//x
	inserirVertice(G,6);//w
	inserirVertice(G,7);//v
	inserirVertice(G,8);//u
	inserirAresta(G,3,2,1);
	inserirAresta(G,2,1,1);
	inserirAresta(G,1,5,1);
	inserirAresta(G,5,2,1);
	inserirAresta(G,2,6,1);
	inserirAresta(G,3,6,1);
	inserirAresta(G,7,3,1);
	inserirAresta(G,4,7,1);
	inserirAresta(G,4,8,1);
	inserirAresta(G,8,4,1);
	inserirAresta(G,8,7,1);
	inserirAresta(G,7,6,1);
	inserirAresta(G,6,5,1);
  */
  //Teste enunciado trabalho2

  inserirVertice(G,1);//y
  inserirVertice(G,2);//z
  inserirVertice(G,3);//s
  inserirVertice(G,4);//t
  inserirVertice(G,5);//t
  inserirVertice(G,6);//t
  inserirVertice(G,7);//t
  inserirVertice(G,8);//t
  inserirVertice(G,9);//t
  inserirVertice(G,10);

  inserirAresta(G,1,2,7);
  inserirAresta(G,2,1,7);

  inserirAresta(G,1,4,9);
  inserirAresta(G,4,1,9);

  inserirAresta(G,1,5,10);
  inserirAresta(G,5,1,10);

  inserirAresta(G,1,6,8);
  inserirAresta(G,6,1,8);

  inserirAresta(G,1,8,9);
  inserirAresta(G,8,1,9);

  inserirAresta(G,1,10,8);
  inserirAresta(G,10,1,8);

  inserirAresta(G,2,3,4);
  inserirAresta(G,3,2,4);

  inserirAresta(G,2,4,5);
  inserirAresta(G,4,2,5);

  inserirAresta(G,2,9,9);
  inserirAresta(G,9,2,9);

  inserirAresta(G,2,10,9);
  inserirAresta(G,10,2,9);

  inserirAresta(G,3,4,1);
  inserirAresta(G,4,3,1);

  inserirAresta(G,3,5,4);
  inserirAresta(G,5,3,4);

  inserirAresta(G,3,9,2);
  inserirAresta(G,9,3,2);

  inserirAresta(G,4,5,3);
  inserirAresta(G,5,4,3);

  inserirAresta(G,5,6,18);
  inserirAresta(G,6,5,18);

  inserirAresta(G,6,7,9);
  inserirAresta(G,7,6,9);

  inserirAresta(G,6,8,9);
  inserirAresta(G,8,6,9);

  inserirAresta(G,8,7,3);
  inserirAresta(G,7,8,3);

  inserirAresta(G,9,7,6);
  inserirAresta(G,7,9,6);

  inserirAresta(G,8,9,4);
  inserirAresta(G,9,8,4);

  inserirAresta(G,8,10,2);
  inserirAresta(G,10,8,2);

  inserirAresta(G,10,9,2);
  inserirAresta(G,9,10,2);

  //slides caminhoMinimo
  /*
  inserirVertice(G,1);//y
  inserirVertice(G,2);//z
  inserirVertice(G,3);//s
  inserirVertice(G,4);//t
  inserirVertice(G,5);//t
  inserirVertice(G,6);//t
  inserirAresta(G,1,2,10);
  inserirAresta(G,1,4,5);
  inserirAresta(G,2,6,1);
  inserirAresta(G,2,4,2);
  inserirAresta(G,4,2,3);
  inserirAresta(G,4,6,9);
  inserirAresta(G,4,5,2);
  inserirAresta(G,5,3,5);
  inserirAresta(G,5,1,7);
  inserirAresta(G,5,6,6);
  inserirAresta(G,6,5,4);
  inserirAresta(G,6,3,3);
  */
	visualizarGrafo(G);

	printf("Digite 1 para inserir vertices.\n");
	printf("Digite 2 para inserir arestas.\n");
	printf("Digite 3 para visualizar grafo.\n");
	printf("Digite 4 para remover vertices.\n");
	printf("Digite 5 para remover arestas.\n");
	printf("Digite 6 para saber o grau do vertice(trabalho2).\n");
	printf("Digite 7 para buscar em largura um vertice(trabalho2).\n");
  printf("Digite 8 para buscar em profundidade um vertice(trabalho2).\n");
  printf("Digite 9 para encontrar a matriz de adjacencias(trabalho2).\n");
  printf("Digite 10 para encontrar o caminho minimo(trabalho2).\n");
  printf("Digite 11 para encontrar a arvore geradora minima(trabalho2).\n");
  printf("Digite 12 para saber se o grafo e conexo(trabalho2).\n");
	printf("Digite 13 para sair do programa(trabalho2).\n");
	printf("Digite a opcao escolhida\n\n");
	scanf("%d",&escolha);
	while(escolha!=13)
	{
		if(escolha==1)
		{
			printf("Digite o head do vertice a ser adicionado\n");
			scanf("%d",&verticeI);
			inserirVertice(G,verticeI);
		}
		if(escolha==2)
		{
			printf("Digite o head dos vertice I e o head do vertice J e o peso da aresta(separados por espaco)\n");
			scanf("%d %d %d",&verticeI,&verticeJ,&peso);
			inserirAresta(G,verticeI,verticeJ,peso);
            inserirAresta(G,verticeJ,verticeI,peso);
		}
		if(escolha==3)
		{
			visualizarGrafo(G);
		}
		if(escolha==4)
		{
			printf("Digite o head do vertice que deseja remover\n");
			scanf("%d",&verticeI);
			removerVertice(G,verticeI);
		}
		if(escolha==5)
		{
			printf("Digite o head dos vertices que possuem a aresta a ser removida(separados por espaco)\n");
			scanf("%d %d",&verticeI,&verticeJ);
			removerAresta(G,verticeI,verticeJ);
			removerAresta(G,verticeJ,verticeI);
		}
		if(escolha==6)
		{
			printf("Digite o head do vertice que deseja saber o grau\n");
			scanf("%d",&verticeI);
      printf("o vertice tem grau %d",GrauVertice(G,verticeI));
		}
		if(escolha==7)
		{
      node *ptr=G->no;
      G->adotados=0;
      while(ptr!=NULL) //definindo todos os vertices como nao visitados a cada instancia de execucao;
      {
        ptr->cor='b';
        ptr->finalizado=-1;
        ptr->visitado=-1;
        ptr->pai=-1;
        ptr=ptr->down;
      }
			printf("Digite o head do vertice que deseja utilizar como start\n");
			scanf("%d",&verticeI);
			BuscaLargura(G,verticeI);
      printarOrdem(G); //printa a ordem da mesma
		}
    if(escolha==8)
    {
      node *ptr=G->no;
      G->adotados=0;
      while(ptr!=NULL) //definindo todos os vertices como nao visitados para obter uma nova resposta a cada caso
      {
        ptr->cor='b';
        ptr->finalizado=-1;
        ptr->visitado=-1;
        ptr->pai=-1;
        ptr=ptr->down;
      }
      BuscaProfundidade(G);
    }
		if(escolha==9)
		{
			MatrizAdjacencias(G);
		}
    if(escolha==10)
    {
      G->adotados=0;
      node *ptr=G->no;
      while(ptr!=NULL) //definindo todos os vertices como nao visitados para obter uma nova resposta a cada caso
      {
        ptr->peso=999;
        ptr->pai=-1;
        ptr->visitado=-1;
        ptr->cor='b';
        ptr=ptr->down;
      }
      printf("Digite o head do vertice que deseja utilizar como start:\n");
      scanf("%d",&verticeI);
      DIJKSTRA(G,verticeI);
    }
    if(escolha==11)
    {
      G->adotados=0;
      node *ptr=G->no;
      while(ptr!=NULL) //definindo todos os vertices como nao visitados para obter uma nova resposta a cada caso
      {
        ptr->peso=999;
        ptr->pai=-1;
        ptr->visitado=-1;
        ptr->cor='b';
        ptr=ptr->down;
      }
      printf("Digite o head do vertice que deseja utilizar como start:\n");
      scanf("%d",&verticeI);
      PRIM(G,verticeI);
    }
    if(escolha==12)
    {
      node *ptr=G->no;
      while(ptr!=NULL) //definindo todos os vertices como nao visitados para obter uma nova resposta a cada caso
      {
        ptr->visitado=-1;
        ptr=ptr->down;
      }
      GrafoConexo(G);
    }
    printf("\n");
    printf("\n");
    printf("Digite 1 para inserir vertices.\n");
  	printf("Digite 2 para inserir arestas.\n");
  	printf("Digite 3 para visualizar grafo.\n");
  	printf("Digite 4 para remover vertices.\n");
  	printf("Digite 5 para remover arestas.\n");
  	printf("Digite 6 para saber o grau do vertice(trabalho2).\n");
  	printf("Digite 7 para buscar em largura um vertice(trabalho2).\n");
    printf("Digite 8 para buscar em profundidade um vertice(trabalho2).\n");
    printf("Digite 9 para encontrar a matriz de adjacencias(trabalho2).\n");
    printf("Digite 10 para encontrar o caminho minimo(trabalho2).\n");
    printf("Digite 11 para encontrar a arvore geradora minima(trabalho2).\n");
    printf("Digite 12 para saber se o grafo e conexo(trabalho2).\n");
  	printf("Digite 13 para sair do programa(trabalho2).\n");
    printf("\n");
    printf("Digite a opcao escolhida\n\n");
    scanf("%d",&escolha);
	}
    free(G); //libera a memoria alocada pelo grafo
	  return 0;
}
