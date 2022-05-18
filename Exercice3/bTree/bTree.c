#include "bTree.h"
/*
Adaptado do código de:
Henrique Gomes Zanin NUSP: 10441321
Gabriel Guimaraes Vilas Boas Marin NUSP: 11218521
*/

struct record_st {
    int key;
    long recordRRN;
};

struct page_st {
    RECORD *records;
    long *childs;
    short numberOfKeys;
    boolean isLeaf;
};

struct promotedKey_st {
    int key;
    long recordRRN;
    long childs[2];
};

/*Retrives page from file pointer*/
BTPAGE *
readPageFromFile(FILE *fp) {
    // Aloca espaço para carregar página
    // Lê dados da página do arquivo
}

/*Writes page into file in certain rrn position*/
Errors writePageIntoFile(long rrn, BTPAGE *page, FILE *fp) {
    // Verifica se está tudo ok com os dados
    // Encontra local para escrita baseado no RRN
    // Escreve dados
    // Atualiza valor de espaço livre na página
    // Dica: você pode criar uma função que só lida com a escrita dos dados e chamar aqui
}

/*Get page by rrn*/
BTPAGE *getPage(long RRN, FILE *fp) {
    // Recupera uma página baseado no RRN
    // Procura e carrega seus dados
}

/*Get root RRN from header*/
long getTreeHeader(FILE *fp) {
    // Carrega o cabeçalho da árvore, que está no início do arquivo
}

/*Writes root RRN in header*/
void writeTreeHeader(FILE *fp, long rootRRN) {
    // Calcula espaço livre e escreve no cabeçalho da árvore, junto com o RRN do nó raíz
}

BTPAGE *createTree(FILE *fp) {
    // Aloca espaço pra raiz
    // Inicializa os valores
    // Escreve a raiz no cabeçalho
}

BTPAGE *getOrCreateRoot(FILE *fp) {
    // Verifica se a árvore já existe ou precisa criar uma nova
    // Se a árvore não existir, cria ela
    // Se existir, só pega o RRN da raiz no cabeçalho e carrega sua página
    // Pode ser adaptada pra inserção e busca sem precisar de 2 funções
}

promotedKey *insertIntoNode(BTPAGE *page, promotedKey *newKey, FILE *fp) {
    // Procura local pra inserir nova chave na página
    // Se não couber, splitta ele
    // Escreve dados na página
}

/*Insert some key on page*/
BTPAGE *searchPositionOnPageAndInsert(BTPAGE *page, promotedKey *newKey) {
    // Encontra a posição para inserir a chave
    // Se não existir espaço, precisa criar uma nova página (usem uma função para criar)
    // Salvar dados da nova chave na página
}
/*
    If page size is odd the return is biggest slice
*/
BTPAGE *splitAndCreateNewNode(BTPAGE **page) {
    // Encontra a posição do meio das chaves
    // Cria espaço pra nova página
    // Copia metade das chaves pra página nova
    // Limpa elas do nó antigo
    // Atualiza os filhos de ambas as páginas
    // Atualiza o número de chaves de ambas
}

/*Extract a promoted key from page*/
promotedKey *extractpromotedKey(BTPAGE *page) {
    // Aloca espaço pra chave
    // Tira ela da página
    // Atualiza dados da página (filho, número de chaves, etc)
}

/*Split node and writes into file*/
promotedKey *_split(BTPAGE *page, FILE *fp, promotedKey *newKey) {
    // Divide a página, cria o novo nó (faça numa função auxiliar pois é complexo)
    // Extrai a chave promovida e atualiza os filhos da chave
    // Escreve a página nova e a que foi dividida (com suas atualizações) no arquivo
}

/*Used if promotions reaches root*/
BTPAGE *createNodeWithPromotedKey(promotedKey *promoKey) {
    // Se promoção cria estrutura para nova raiz,
    // Aloca espaço para ela
    // Salva dados da chave promovida na nova raiz
    // atualiza os filhos deste novo nó/página
    // Pode reusar função que cria página nova e adicionar somente especificidades
}

Errors setNodeAsRoot(BTPAGE *page, FILE *fp) {
    // Escreve página nova e atualiza o cabeçalho para conter ela como raiz
    // Deveria ser chamada junto com criação de novo nó quando promoção cria uma nova raiz
}

/*Recursive insertion*/
promotedKey *_bTreeInsert(BTPAGE *node, promotedKey *key, FILE *fp) {
    // Se nó a ser inserido a chave é folha, tenta inserir
    // Caso a inserção crie uma promoção, precisa retornar a chave promovida para a recursão
    // Se não for nó folha, procura qual sub-árvore seguir para inserir numa folha
    // Encontrar a posição correta e descer para filho à esquerda se a chave for menor
    // E descer à direita se for maior
    // Chamar a inserção recursiva pro filho escolhido
    // Se a inserção recursiva retornar uma chave promovida, precisa tentar inserir essa chave promovida no nó atual
    // Retornar chave promovida ou um valor NULL se não houve promoção
}

Errors bTreeInsert(PrimaryIndex *newRecord, BTPAGE *root, FILE *fp) {
    // Função mais abstrata de inserção
    // Prepara os dados da nova chave
    // Tenta inserir recursivamente
    // Se tiver chave promovida no final da recursão, é que existe nova raiz
    // Chama as funções pra criar nova raiz e atualizar o cabeçalho
}

/*Returns rrn if key exist else return -1*/
long bTreeSelect(BTPAGE *node, int key, FILE *fp) {
    // Procura no nó atual se a chave existe
    // Se não existir, tenta procurar no filho adequado, recursivamente
    // Se encontrar a chave, retorna RRN dela
    // Se não encontrar (chegar num nó folha e não estiver lá), retorna -1
}

RECORD *createRecord(int key, long recordRRN){
				RECORD* record = (RECORD *) calloc(1, sizeof(RECORD));
				record->key = key;
				record->recordRRN = recordRRN;
				return record;
}

BTPAGE *createPage(RECORD* records, long* childs, boolean isLeaf, int numberOfKeys){
				BTPAGE *page = (BTPAGE *) calloc(1, sizeof(BTPAGE));
				page->records = records;
				page->childs = childs;
				page->isLeaf = isLeaf;
				page->numberOfKeys = numberOfKeys;
				return page;
}

PROMOTEDKEY *createPromoKey(int key, long recordRRN, long* childs){
				PROMOTEDKEY *promo = (PROMOTEDKEY *) calloc(1, sizeof(PROMOTEDKEY));
				promo->key = key;
				promo->recordRRN = recordRRN;
				promo->childs[0] = childs[0];
				promo->childs[1] = childs[1];
				return promo;
}
