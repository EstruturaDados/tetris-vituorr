#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Fixando quantidade de peças
#define MaxPecas_Fila 5
#define MaxPecas_Pilha 3

// Structs necessárias
typedef struct
{
    char nome[6]; // Tipo da peça ("I", "O", "T", "L")
    int id;       // Identificador único
} Peca;

typedef struct
{
    Peca pecas[MaxPecas_Fila]; // Vetor de peças
    int inicio;                // Índice do primeiro elemento
    int fim;                   // Índice do último elemento
    int total;                 // Quantidade atual de peças na fila
} Fila;

typedef struct
{
    Peca pecas[MaxPecas_Pilha];
    int topo;

} Pilha;

// Prototipos

void gerarPecasIniciais_Fila(Fila *f);
void mostrarFila(Fila *f);
Peca removerPeca(Fila *f);
void inserirPeca(Fila *f, Peca p);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
void inicializarFila(Fila *f);

void mostrarPilha(Pilha *p);
Peca pop(Pilha *p);
void push(Pilha *p, Peca nova);
int pilhaCheia(Pilha *p);
int pilhaVazia(Pilha *p);
void inicializarPilha(Pilha *p);

Peca gerarPecaAleatoria();
void Swap(Fila *f, Pilha *p);
void Swap3(Fila *f, Pilha *p);

// Função principal

int main()
{
    Fila fila;
    Pilha pilha;
    int op;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    srand(time(NULL)); // Semente para gerar aleatórios

    gerarPecasIniciais_Fila(&fila); // Gera peças iniciais automaticamente

    do
    {
        printf("\n========================\n");
        printf("      TETRIS STACK      \n");
        printf("========================\n");
        mostrarFila(&fila);
        mostrarPilha(&pilha);

        printf("[1] Jogar uma peca \n");
        printf("[2] Reservar uma peca\n");
        printf("[3] Usar peca reserva\n");
        printf("[4] Trocar peca atual\n");
        printf("[5] Troca multipla\n");
        printf("[0] Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
        {

            removerPeca(&fila);
            Peca nova = gerarPecaAleatoria();
            inserirPeca(&fila, nova);
            break;
        }
        case 2:
        {
            if (!pilhaCheia(&pilha)){    
            Peca reservada = removerPeca(&fila);
            push(&pilha, reservada);
            Peca nova = gerarPecaAleatoria();
            inserirPeca(&fila, nova);
            } else {printf("\nPilha cheia! Nao e possivel reservar mais pecas\n");} break;
        }
        case 3:
        {
            if (!pilhaVazia(&pilha))
            {
                Peca usada = pop(&pilha);
                printf("\nUsando peca da reserva: [%s | %d]\n", usada.nome, usada.id);
            }
            break;
        }
        case 4:
        {   if (!pilhaVazia(&pilha))
            {
            Swap(&fila, &pilha);
            } else {printf("\nPilha vazia! Nao e possivel trocar pecas\n");} break;
        }
        case 5:
        {
            if (pilhaCheia(&pilha))
            {
            Swap3(&fila, &pilha);  
            } else {printf("\nA pilha nao possui pecas suficientes\n");} break;
        }
        case 0:
            printf("\nAte mais!\n");
            break;
        default:
            printf("\nOpcao invalida!\n");
        }
    } while (op != 0);

    return 0;
}

// FUNÇÕES (FILA)

void inicializarFila(Fila *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f)
{
    return f->total == MaxPecas_Fila;
}

int filaVazia(Fila *f)
{
    return f->total == 0;
}

void inserirPeca(Fila *f, Peca p)
{
    if (filaCheia(f))
    {
        printf("\nFila cheia! Nao e possivel inserir nova peça.\n");
        return;
    }

    f->pecas[f->fim] = p;
    f->fim = (f->fim + 1) % MaxPecas_Fila;
    f->total++;
}

Peca removerPeca(Fila *f)
{
    Peca removida = {"", -1};
    if (filaVazia(f))
    {
        printf("\nFila vazia! Nao ha pecas para jogar.\n");
        return removida;
    }

    removida = f->pecas[f->inicio];
    printf("\nJogando peca: [%s | %d]\n", removida.nome, removida.id);

    f->inicio = (f->inicio + 1) % MaxPecas_Fila;
    f->total--;
    return removida;
}

void mostrarFila(Fila *f)
{
    if (filaVazia(f))
    {
        printf("\nFila vazia!\n");
        return;
    }

    printf("\nFila de pecas:\n");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MaxPecas_Fila)
    {
        printf("[%s %d] ", f->pecas[idx].nome, f->pecas[idx].id);
    }
    printf("\n");
}

// FUNÇÕES (PILHA)

void inicializarPilha(Pilha *p)
{
    p->topo = -1;
}

int pilhaVazia(Pilha *p)
{
    return p->topo == -1;
}

int pilhaCheia(Pilha *p)
{
    return p->topo == MaxPecas_Pilha - 1;
}

void push(Pilha *p, Peca nova)
{
    if (pilhaCheia(p))
    {
        printf("Pilha cheia! Nao e possivel reservar mais pecas\n");
        return;
    }
    p->topo++;
    p->pecas[p->topo] = nova;
}

Peca pop(Pilha *p)
{
    Peca removida = {"", -1};
    if (pilhaVazia(p))
    {
        printf("Pilha vazia!\n");
        return removida;
    }
    removida = p->pecas[p->topo];
    p->topo--;
    return removida;
}

void mostrarPilha(Pilha *p)
{
    printf("\nPilha (topo -> base): \n");

    if (pilhaVazia(p))
    {
        printf("Pilha vazia!\n\n");
        return;
    }

    for (int i = p->topo; i >= 0; i--)
    {
        printf("[%s %d]\n", p->pecas[i].nome, p->pecas[i].id);
    }
    printf("\n");
}

// Funções de geração de peças

Peca gerarPecaAleatoria()
{
    char *tipos[] = {"I", "O", "T", "L"};
    static int contador = 0; // Garante IDs únicos

    Peca nova;
    strcpy(nova.nome, tipos[rand() % 4]);
    nova.id = contador++;
    return nova;
}

void gerarPecasIniciais_Fila(Fila *f)
{
    for (int i = 0; i < MaxPecas_Fila; i++)
    {
        Peca nova = gerarPecaAleatoria();
        inserirPeca(f, nova);
    }
}

void Swap(Fila *f, Pilha *p) // Coloca a peça do inicio da fila no topo da pilha 
{
    Peca trocaFila = removerPeca(f); 
    Peca trocaPilha = pop(p);
    push(p, trocaFila);
    
    // void inserirpeca alterado para trocar a peça pela primeira da fila
    f->pecas[f->inicio] = trocaPilha;
    f->fim = (f->fim + 1) % MaxPecas_Fila;
    f->total++;
}

void Swap3(Fila *f, Pilha *p) // Função para trocar peças 
    
    // Usa iFila e iPilha para armazenar valores da fila e pilha e substituir posteriormente
{   
    int iFila = f->inicio;
    int iPilha = p->topo;

    for (int i = 0; i < 3; i++) 
    {
     Peca troca = f->pecas[iFila];
     f->pecas[iFila] = p->pecas[iPilha];
     p->pecas[iPilha] = troca;
    
    // Para avançar os indices    
    iFila = (iFila + 1) % MaxPecas_Fila;
    iPilha--;
    }
}
