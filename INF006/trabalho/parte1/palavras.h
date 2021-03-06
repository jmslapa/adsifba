#define CONT 3

#define SUCESSO -1
#define EXISTING_WORD -2
#define CONSOANTE -3
#define VOGAL -4
#define PALAVRA_INVALIDA -5

void inicializa();
void finaliza();
void pause();
void composicaoSilaba(int size, char silaba[]);
void formaSilabaDuasLetras(char silaba[], int combinacaoTipos[]);
void formaSilabaTresLetras(char silaba[], int combinacaoTipos[]);
void formaSilabaQuatroLetras(char silaba[], int combinacaoTipos[]);

char getConsoante();
char getVogal();

int sorteiaTipo();
int defineConstrucao(int opcoes[], int size);
int buscaString(char *vetorStr[], char str[], int size);
int duasLetras(int posicao, int wordLength, char word[]);
int tresLetras(int posicao, int wordLength, char word[]);
int quatroLetras(int posicao, int wordLength, char word[]);
int comparaWord(char *word, int size);
