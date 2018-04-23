/*

Professor Gabriel Canhadas Genvigir

Alunos:

    Bruno Ricardo Secco RA: 1750879
    Guilherme Eiti Akita Miua RA: 1913158
    Lucas Carvalho Silva RA: 1997068
*/

/* Bibliotecas utilizadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

/* Constantes */
/* TA = tamanho do vetor de alunos */
#define TA 600
/* TD = tamanho do vetor de disciplinas */
#define TD 15

/* Structs */
struct Aluno {
    int codigo;
    char nome[50];
    char codigo_disciplina[6];
    int faltas;
    float notas[3];
    float media;
    float exame;
    float nota_final;
    char resultado[10];
} typedef tp_aluno;

struct Disciplina{
    char codigo_disciplina[6];
    char disciplina[30];
} typedef tp_disciplina;

tp_aluno alunos[TA];
tp_disciplina disciplinas[TD];

/* Declaração das variáveis e atribuição de valores */
int cod_aluno,
    /* Posições */
    pos_str_aluno = 0,
    pos_str_disciplina = 0;

char cod_disc[6];

/* Protótipos das funções */
void leraluno(tp_aluno [], int);
int verificaaluno(tp_aluno [], int);
float calcula_media (tp_aluno [], int) ;
float nota_exame(void);
float nota_final(float, float) ;
void resultadofinal(tp_aluno [], int, int);
void print_aluno(tp_aluno [], tp_disciplina[], int, int) ;
void ordena_nome(tp_aluno [], int);
void ordena_nota(tp_aluno [], int) ;
void lerdisciplina(tp_disciplina [], int);
int verificadisciplina(tp_disciplina [], int);
void print_disciplina(tp_disciplina [], int);
int qtd_alunos(tp_aluno [], int);

int main() {

    int x;

    /* MENU */

    do {
        printf("\n \t MENU");
        printf("\n 1) Cadastrar Alunos");
        printf("\n 2) Cadastrar Disciplinas");
        printf("\n 3) Listar Disciplinas");
        printf("\n 4) Listar Alunos em Ordem Alfabetica Crescente");
        printf("\n 5) Listar Alunos em Ordem Nota Final decrescente");
        printf("\n 0) Encerrrar o programa\n");

        scanf("%d", &x);

        switch(x){
            case 1:
                leraluno(alunos, TA);
                getch();
                system("cls");
                break;
            case 2:
                lerdisciplina(disciplinas, TD);
                getch();
                system("cls");
                break;
            case 3:
                system("cls");
                print_disciplina(disciplinas, pos_str_disciplina);
                getch();
                system("cls");
                break;
            case 4:
                system("cls");
                ordena_nome(alunos, pos_str_aluno);
                print_aluno(alunos, disciplinas, pos_str_aluno, pos_str_disciplina);
                getch();
                system("cls");
                break;
            case 5:
                system("cls");
                ordena_nota(alunos, pos_str_aluno);
                print_aluno(alunos, disciplinas, pos_str_aluno, pos_str_disciplina);
                getch();
                system("cls");
                break;
            case 0:
                x = 0;
                break;

        }

    } while(x != 0);

}

/* Cadastro de alunos */
void leraluno(tp_aluno *a,int t){
    int i, j, x, y, qnt;

    x = 0;

    system("cls");

    /* Verifica se existe disciplinas cadastradas, caso não exista não poderá cadastrar um aluno */
    if(pos_str_disciplina == 0){
        printf("\n\nNao e possivel cadastrar qualquer aluno, antes que exista uma disciplina cadastrada\n\n");
    }

    /* Cadastro de alunos quando é permitido */
    while(pos_str_disciplina > 0){
        while(x != 1){
            printf("\nInforme o codigo do aluno: ");
            scanf("%d", &cod_aluno);
            /* Verifica se existe aluno com o mesmo codigo */
            if(verificaaluno(a, t) == 1){
                a[pos_str_aluno].codigo = cod_aluno;
                x = 1;
            }
            else {
                printf("\nCODIGO EXISTENTE! UTILIZE OUTRO CODIGO");
                getch();
                system("cls");
            }
        }
        printf("\nInforme o nome do aluno: ");
        fflush(stdin);
        gets(a[pos_str_aluno].nome);

        do {
            /* Imprime as disciplinas cadastradas */
            printf("\nLista de disciplinas: ");
            print_disciplina(disciplinas, pos_str_disciplina);
            printf("\n\nInforme o codigo da disciplina: ");
            scanf("%s", &cod_disc);
            /* Verifica se a disciplina existe */
            if(verificadisciplina(disciplinas,TD)==0) {
                /* Verifica a quantidade de alunos na disciplina, a quantidade de alunos deve ser menor que 40 por disciplina */
                if(qtd_alunos(a, t) == 1) {
                    /* Armazena a disciplina */
                    strcpy(a[pos_str_aluno].codigo_disciplina,cod_disc);
                    i = 0;
                }
                else {
                    /* 40 Alunos na disciplina */
                    printf("\nDISCIPLINA COM MAXIMO DE ALUNOS PERMITIDOS");
                    i = 1;
                    getch();
                    system("cls");
                }
            }
            else {
                i = 1;
                /* Disciplina inexistente */
                printf("\nDISCIPLINA NAO EXISTENTE");
                getch();
                system("cls");
            }
        } while(i != 0);

        printf("\nInforme o numero de faltas: ");
        scanf("%d", &a[pos_str_aluno].faltas);

        /* Lê as notas dos alunos */
        for(i = 0; i < 3; i = i + 1){
            printf("\nInforme a nota numero %d: ", i + 1);
            scanf("%f", &a[pos_str_aluno].notas[i]);
        }

        /* Calcula e armazena a média do aluno */
        a[pos_str_aluno].media = calcula_media(a, pos_str_aluno);

        /* Verifica se o aluno pode fazer exame */
        if  ((a[pos_str_aluno].media >= 4.0) && (a[pos_str_aluno].media < 7.0)) {
            a[pos_str_aluno].exame = nota_exame();
        }

        /* Atribuição da nota final */
        a[pos_str_aluno].nota_final = nota_final(a[pos_str_aluno].media, a[pos_str_aluno].exame);

        /* Atribuição do resultado */
        resultadofinal(a, TA, pos_str_aluno);

        pos_str_aluno = pos_str_aluno + 1;
        /* Break para sair do cadastro de 1 aluno*/
        break;
    }
}

/* Cadastro de disciplinas */
void lerdisciplina(tp_disciplina *d, int t){
    int i, x = 0;

    system("cls");
    while(x != 1){

        printf("\nInforme o codigo da disciplina: ");
        fflush(stdin);
        scanf("%6s", &cod_disc);
        /* Verifica se disciplina existe */
        if(verificadisciplina(d, t) == 1){
            fflush(stdin);
            strcpy(d[pos_str_disciplina].codigo_disciplina, cod_disc);
            x = 1;
        }
        else {
            printf("\nCODIGO DE DISCIPLINA REPITIDO!");
            getch();
            system("cls");
        }
    }

    printf("\nInforme o nome da disciplina: ");
    fflush(stdin);
    gets(d[pos_str_disciplina].disciplina);

    pos_str_disciplina = pos_str_disciplina + 1;
}

/* Verifica se existe um aluno com o mesmo codigo */
int verificaaluno(tp_aluno *a, int t){
    int i ;

    if (pos_str_aluno == 0){
        return 1;
    }

    for (i = 0 ; i < pos_str_aluno ; i = i + 1){

        if (cod_aluno == a[i].codigo){
            return 0;
        }
    }

    return 1;
}

/* Verifica se a disciplina existe e se não é repetida */
int verificadisciplina(tp_disciplina *d, int t) {
    int i = 0, j , cont = 0;

    fflush(stdin);
    if(pos_str_disciplina == 0){
        return 1;
    }

    for (i = 0 ; i < pos_str_disciplina ; i = i + 1){
        if(strcmp(cod_disc,d[i].codigo_disciplina)==0){
            return 0;
        }
    }
    return 1;
}

/* Calcula a média do aluno */
float calcula_media(tp_aluno *a, int p) {

    int x;
    float soma, contador, resultado;
    contador = 0, soma = 0;

    for(x = 0; x < 3; x = x + 1) {
        soma = soma + a[p].notas[x];
        contador = contador + 1;
    }

    resultado = soma / contador;

    return resultado;
}

/* Lê a nota do exame do aluno */
float nota_exame(void) {
    float notaexame;

    printf("\nNota do exame: ");
    scanf("%f", &notaexame);

    return notaexame;
}

/* Atribui a nota final ao aluno */
float nota_final(float media , float exame) {
    float nota_final;

    if ( media >= 7 || media < 4 ) {
        nota_final = media ;
    }
    else {
        nota_final = (media + exame) / 2;

    }

    return nota_final ;
}

/* Resultado final do aluno: APROVADO ou REPROVADO */
void resultadofinal(tp_aluno *a, int t, int p) {

    char aprovado[10] = "APROVADO", reprovado[10] = "REPROVADO";

    if (a[p].nota_final >= 5) {
        strcpy(a[p].resultado, aprovado);
    }
    else if (a[p].nota_final < 5) {
        strcpy(a[p].resultado, reprovado);
    }
}

/* Imprime os alunos */
void print_aluno(tp_aluno *a, tp_disciplina *d, int p, int t) {

    int i, j;

    for(i = 0; i < p; i = i + 1) {
        printf("\nNOME........: %s", a[i].nome) ;
        for(j = 0; j < t; j = j + 1) {
            if (strcmp(a[i].codigo_disciplina,d[j].codigo_disciplina) == 0) {
                printf ("\nDISCIPLINA..: %s %s", a[i].codigo_disciplina,d[j].disciplina) ;
            }
        }
        printf("\nFALTAS......: %d", a[i].faltas) ;
        printf("\nNOTAS.......: %.2f - %.2f - %.2f", a[i].notas[0] , a[i].notas[1] , a[i].notas[2]) ;
        printf("\nMEDIA.......: %.2f", a[i].media) ;
        printf("\nEXAME.......: %.2f", a[i].exame) ;
        printf("\nNOTA FINAL..: %.2f", a[i].nota_final) ;
        printf("\nRESULTADO...: %s\n\n", a[i].resultado) ;
     }
}

/* Ordena por nome em letra alfabética dos alunos */
void ordena_nome(tp_aluno *a, int p) {
    int i, j, r;
    tp_aluno aux;

    for(i = p - 1; i > 0; i = i - 1) {
        for(j = 0; j < i; j = j + 1) {

            r = strcmp(a[j].nome, a[j+1].nome);

            if (r > 0) {
                aux = a[j];
                a[j] = a[j+1];
                a[j+1] = aux;
            }
        }
    }
}

/* Ordena os alunos por nota */
void ordena_nota(tp_aluno *a , int p) {
    int i, j;
    tp_aluno aux ;

    for(i = p - 1; i > 0; i = i - 1) {
        for(j = 0; j < i; j = j + 1) {
            if (a[j].nota_final < a[j+1].nota_final ) {
                aux = a[j] ;
                a[j] = a[j+1] ;
                a[j+1] = aux ;
            }
        }
    }
}

/* Imprime as disciplinas */
void print_disciplina(tp_disciplina *d, int p) {

    int x;

    for(x = 0; x < p; x = x + 1) {
        printf("\nCodigo da disciplina...%s", d[x].codigo_disciplina);
        printf("\nDisciplina.............%s\n\n", d[x].disciplina);
    }
}

/* Verifica a quantidade de alunos em uma disciplina e retorna se pode cadastrar o aluno na disciplina */
int qtd_alunos(tp_aluno *a, int t) {

    int x, contador, resultado;

    contador = 0;

    for(x = 0; x < t; x = x + 1) {
        if (strcmp(a[x].codigo_disciplina, cod_disc) == 0) {
            contador = contador + 1;
        }
    }

    if (contador < 2) {
        return 1;
    }

    return 0;
}
