#include <stdio.h> 
#include <stdlib.h>


#include "EstruturaVetores.h"

//definindo estrutura principal
typedef struct{
    int tamanho;
    int preenchido;
    int *vetorAuxiliar;
}lista;

lista vetorPrincipal[TAM];


void inicializar(){

    int i;

    for(i=0; i<TAM; i++){

            vetorPrincipal[i].vetorAuxiliar = NULL;
            vetorPrincipal[i].tamanho = 0;
            vetorPrincipal[i].preenchido = 0;
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho tem inteiro maior ou igual a 1
*/
int criarEstruturaAuxiliar(int tamanho, int posicao){
    
    int retorno = 0;

    //testar se posição é um valor válido {entre 1 e 10}
    if (ehPosicaoValida(posicao)==POSICAO_INVALIDA)
        retorno = POSICAO_INVALIDA;
   
    else{
        //testar se existe a estrutura auxiliar    
        if(vetorPrincipal[posicao-1].vetorAuxiliar != NULL)
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    
        else{
            //testar se o tamanho não é menor que 1
            if(tamanho<1)
                retorno = TAMANHO_INVALIDO;
            else{
                // deu tudo certo, crie
                vetorPrincipal[posicao-1].vetorAuxiliar = (int*) malloc(tamanho * sizeof(int));

                //testa se a alocação ocorreu corretamente
                if(vetorPrincipal[posicao-1].vetorAuxiliar != NULL){
                    vetorPrincipal[posicao-1].tamanho = tamanho;
                    retorno = SUCESSO;
                }else
                    retorno = SEM_ESPACO_DE_MEMORIA;
            }
        }
    }

    return retorno;

}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao){
    int indiceEstruturaAuxiliar;
    
    //testa se a posição é valida    
    if (ehPosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;
    
    else{
        //se a estrutura existe
        if(vetorPrincipal[posicao-1].vetorAuxiliar == NULL)
            return SEM_ESTRUTURA_AUXILIAR;
        
        else{
                
            //testa se a estrutura está vazia
            if(vetorPrincipal[posicao-1].preenchido < 1)
                return ESTRUTURA_AUXILIAR_VAZIA;
            
            else{                    
                
                vetorPrincipal[posicao-1].preenchido--;

                return SUCESSO;  
            }
        }
    }
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliarD

*/
int excluirNumeroEspecificoDeEstrutura(int valor, int posicao){

    int indiceEstruturaAuxiliar;
    
    //testa se a posição é valida    
    if (ehPosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;
    
    else{
        //se a estrutura existe
        if(vetorPrincipal[posicao-1].vetorAuxiliar == NULL)
            return SEM_ESTRUTURA_AUXILIAR;
        
        else{
                
            //testa se a estrutura está vazia
            if(vetorPrincipal[posicao-1].preenchido < 1)
                return ESTRUTURA_AUXILIAR_VAZIA;
            
            else{                    
                
                indiceEstruturaAuxiliar = buscaElemento(valor, posicao);
                
                //testa se o valor informado existe na estrutura auxiliar
                if(indiceEstruturaAuxiliar == NUMERO_INEXISTENTE)
                    return NUMERO_INEXISTENTE;

                else{

                    shiftEsquerda(posicao, indiceEstruturaAuxiliar);
                    
                    vetorPrincipal[posicao-1].preenchido--;

                    return SUCESSO;                
                }
            }
        }
    }
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int valor, int posicao){

    int retorno = 0;

        //testar se a posicao eh valida
        if (ehPosicaoValida(posicao)==POSICAO_INVALIDA)
            retorno = POSICAO_INVALIDA;
        else{
            // testar se existe a estrutura auxiliar
            if (vetorPrincipal[posicao-1].vetorAuxiliar!=NULL){
                //testar se tem espaço
                if (vetorPrincipal[posicao-1].preenchido < vetorPrincipal[posicao-1].tamanho){
                  //insere
                  vetorPrincipal[posicao-1].vetorAuxiliar[vetorPrincipal[posicao-1].preenchido] = valor;
                  //incrementa a quantidade de posições preenchidas
                  vetorPrincipal[posicao-1].preenchido++;
                  //define o retorno como sucesso
                  retorno = SUCESSO;
                }else{
                  retorno = SEM_ESPACO;
                }
            }else{
                retorno = SEM_ESTRUTURA_AUXILIAR;
            }
        }


    return retorno;

}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho'

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser menor que 1
    *SEM_ESPACO_DE_MEMORIA - Realocação de memória falhou
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho){

    //define o novo tamanho da estrutura
    novoTamanho = vetorPrincipal[posicao-1].tamanho + novoTamanho;
    
    //testa se a posicao eh valida
    if(ehPosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;
    
    else{
        //testa se a estrutura auxiliar existe
        if(vetorPrincipal[posicao-1].vetorAuxiliar == NULL)
            return SEM_ESTRUTURA_AUXILIAR;
        else{
            //testa se o novo tamanho é um numero maior ou igual a 1
            if(vetorPrincipal[posicao-1].tamanho + novoTamanho < 1)
                return NOVO_TAMANHO_INVALIDO;
            else{
                //realiza realocação de memória
                vetorPrincipal[posicao-1].vetorAuxiliar = (int*) realloc(vetorPrincipal[posicao-1].vetorAuxiliar, sizeof(int) * novoTamanho);

                //testa se a realocação foi realizada com sucesso
                if(vetorPrincipal[posicao-1].vetorAuxiliar == NULL)
                    return SEM_ESPACO_DE_MEMORIA;                
                else{                    

                    vetorPrincipal[posicao-1].tamanho = novoTamanho; 
                    if(vetorPrincipal[posicao-1].tamanho < vetorPrincipal[posicao-1].preenchido)
                        vetorPrincipal[posicao-1].preenchido = vetorPrincipal[posicao-1].tamanho;
                    
                    return SUCESSO;           
                }        
            }
        }
    }

}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao){
   
    if (posicao > 0 && posicao <=10){
        return SUCESSO;
    }else{

        return POSICAO_INVALIDA;
    }
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    *ESTRUTURA_AUXILIAR_VAZIA - A estrutura não possui dados a serem listados
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){
    
    int retorno = 0;
    
    //testa se a posicao é valida
    if(ehPosicaoValida(posicao) != SUCESSO){
       
        retorno = POSICAO_INVALIDA;
   
    }else{
        //testa se existe estrutura auxiliar
        if (vetorPrincipal[posicao-1].vetorAuxiliar == NULL){      
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }else{
            //testa se a estrutura auxiliar está vazia
            if(vetorPrincipal[posicao-1].preenchido == 0)
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
            else{
                for(int i = 0; i < vetorPrincipal[posicao-1].preenchido; i++){
                    vetorAux[i] = vetorPrincipal[posicao-1].vetorAuxiliar[i];
                }
                retorno = SUCESSO;
        
            }
        }
    }

    return retorno;

}

void finalizar(){
    for(int i=0; i < TAM; i++){
        
        if(vetorPrincipal[i].vetorAuxiliar!=NULL)
            free(vetorPrincipal[i].vetorAuxiliar);
    }
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){

    int i,j,aux;

    //testa se a posicao eh valida
    if(ehPosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;
    
    else{        
        //testa se a estrutura auxiliar existe
        if(vetorPrincipal[posicao-1].vetorAuxiliar != NULL){            
            //testa se a estrutura auxiliar está vazia
            if(vetorPrincipal[posicao-1].preenchido > 0){               
                //Preenche vetorAux
                for(int i = 0; i < vetorPrincipal[posicao-1].preenchido; i++)
                    vetorAux[i] = vetorPrincipal[posicao-1].vetorAuxiliar[i];
                //tudo certo, ordena
                insertionSort(vetorAux, vetorPrincipal[posicao-1].preenchido);
                //FIM
                return SUCESSO;
            }else
                return ESTRUTURA_AUXILIAR_VAZIA;
        }else
            return SEM_ESTRUTURA_AUXILIAR;
        
    }
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux
Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - nao tem nenhum valor
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]){

    int i, j, k, count = 0;

    
    k = 0;

    for(i = 0 ; i < TAM ; i++){
        //testa se a estrutura auxiliar está vazia
        if(vetorPrincipal[i].preenchido > 0){
            //se nao está vazia, atribui os valores ao vetor auxiliar
            for(j = 0 ; j < vetorPrincipal[i].preenchido ; j++){
                vetorAux[k] = vetorPrincipal[i].vetorAuxiliar[j];
                k++;
            }
        //se está vazia, incrementa o contador
        }else
            count++;
    }

    //testa se todas as estruturas auxiliares estão vazias      
    if(count == 10)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    else
        return SUCESSO;

}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux
Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - nao tem nenhum valor
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]){

     int i, j, k, count = 0;

    
    k = 0;

    for(i = 0 ; i < TAM ; i++){
        //testa se a estrutura auxiliar está vazia
        if(vetorPrincipal[i].preenchido > 0){
            //se nao está vazia, atribui os valores ao vetor auxiliar
            for(j = 0 ; j < vetorPrincipal[i].preenchido ; j++){
                vetorAux[k] = vetorPrincipal[i].vetorAuxiliar[j];
                k++;
            }
        //se está vazia, incrementa o contador
        }else
            count++;
    }

    //testa se todas as estruturas auxiliares estão vazias      
    if(count == 10)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    else{

        insertionSort(vetorAux, getQuantidadeTotalElementos());
        return SUCESSO;
    }

}

int buscaElemento(int elemento, int posicao){

    int i, indice;

    for(i=0; i < vetorPrincipal[posicao-1].preenchido; i++){

        if(vetorPrincipal[posicao-1].vetorAuxiliar[i] == elemento){
            return i;
        }
    }

    return NUMERO_INEXISTENTE;
}

void shiftEsquerda(int posicao, int posicaoElemento){

    int i;

    for(i = posicaoElemento; i < (vetorPrincipal[posicao-1].tamanho)-1; i++ )
        vetorPrincipal[posicao-1].vetorAuxiliar[i] = vetorPrincipal[posicao-1].vetorAuxiliar[i+1];
}

/*
Objetivo: retorna a quantidade de elementos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao){

    int retorno = 0;
    
    //testa se a posicao eh valida
    if(ehPosicaoValida(posicao)==POSICAO_INVALIDA){
        retorno = POSICAO_INVALIDA;
    }else{
        //testa se a estrutura auxiliar existe
        if(vetorPrincipal[posicao-1].vetorAuxiliar == NULL)
            retorno = SEM_ESTRUTURA_AUXILIAR;
        else{
            //testa se a posição está vazia
            if(vetorPrincipal[posicao-1].preenchido < 1)
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
            //tudo certo, retorne a qtd de preenchidos
            else
                retorno = vetorPrincipal[posicao-1].preenchido;
        }
    }

    return retorno;

}

/*
Objetivo: retorna a quantidade total de elementos na estrutura vetorPrincipal

Retorno (int)
    Sempre retorna algum valor válido, mesmo que 0, pois os testes são realizados na função reutilizada
*/
int getQuantidadeTotalElementos(void){
    
    int qtdTotal = 0;
    
    for(int i = 1; i <= TAM; i++){
        if(getQuantidadeElementosEstruturaAuxiliar(i) > 0)
            qtdTotal = qtdTotal + getQuantidadeElementosEstruturaAuxiliar(i);
    }
    return qtdTotal;
}

void insertionSort(int *v, int tam){

	int i, j, aux;

	for(i=1; i<tam; i++){

		aux=v[i];

		for(j=i-1; j>=0 && v[j]>aux; j--){

			v[j+1]=v[j];
		}

		v[j+1]=aux;
	}
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.
Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No* montarListaEncadeadaComCabecote(){

    No *inicio = (No*) malloc(sizeof(No));

    inicio->prox == NULL;

    int qtdTotalElementos = getQuantidadeTotalElementos();
    int vetorAux[qtdTotalElementos];
    int ret = 0;

    ret = getDadosDeTodasEstruturasAuxiliares(vetorAux);

    if(ret == SUCESSO)
        for(int i = 0 ; i < qtdTotalElementos ; i++)
            inserirFimListaEncadeada(inicio, vetorAux[i]);
    else
        return NULL;

    return inicio;

}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No* inicio, int vetorAux[]){

    No *atual;
    int i;

    if(inicio != NULL)
        for(i = 0 , atual = inicio->prox ; atual != NULL ; atual = atual->prox , i++)
            vetorAux[i] = atual->conteudo; 

}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No* inicio){
   
   No *atual = inicio;
   No *tmp;

   while(atual != NULL){

        tmp = atual->prox;
        free(atual);
        atual = tmp;
   }

}

No* criarElementoEncadeado(int valor){

    No *novo = (No*) malloc(sizeof(No));

    if(novo == NULL)
        return NULL;

    novo->conteudo = valor;

    novo->prox = NULL;

    return novo;
}

void inserirFimListaEncadeada(No *inicio, int valor){

    No *tmp;
    No *novo = criarElementoEncadeado(valor);

    if(inicio->prox  == NULL)
        inicio->prox = novo;
    else{

        tmp = inicio->prox;

        while(tmp->prox != NULL)
            tmp = tmp->prox;

        tmp->prox = novo;

    }
}