/*
  agenda_noptrs_fixed.c
  Versão corrigida: nenhuma variável não-ponteiro é declarada.
  Todas as informações ficam em pBuffer.
  Não usar struct.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* CONFIGURAÇÃO */
#define MAX_PEOPLE 100
#define NAME_SIZE 50
#define EMAIL_SIZE 50

/* Offsets dentro de pBuffer */
#define OFFSET_NPEOPLE 0                /* int */
#define OFFSET_TEMPINT 4                /* int - uso geral */
#define OFFSET_MENU 8                   /* int - escolha do menu / flag */
#define OFFSET_TEMPNAME 12              /* char[NAME_SIZE] */
#define OFFSET_TEMPEMAIL (OFFSET_TEMPNAME + NAME_SIZE) /* char[EMAIL_SIZE] */
#define OFFSET_RECORDS (OFFSET_TEMPEMAIL + EMAIL_SIZE) /* início dos registros */
#define RECORD_SIZE (NAME_SIZE + sizeof(int) + EMAIL_SIZE)

/* Limpeza do stdin: usa temp_int dentro de pBuffer para armazenar o int retornado por getchar */
void clear_stdin(void *pBuffer) {
    int *ch_ptr = (int*)((char*)pBuffer + OFFSET_TEMPINT);
    /* consumir até newline */
    while (1) {
        *ch_ptr = getchar();
        if (*ch_ptr == '\n' || *ch_ptr == EOF) break;
    }
}

/* Imprime um registro: rec_ptr aponta para início do registro */
void print_record(void *pBuffer, char *rec_ptr) {
    char *name_ptr = rec_ptr;
    int *age_ptr = (int*)(rec_ptr + NAME_SIZE);
    char *email_ptr = rec_ptr + NAME_SIZE + sizeof(int);

    if (name_ptr[0] == '\0') return; /* registro vazio */
    printf("Nome : %s\n", name_ptr);
    printf("Idade: %d\n", *age_ptr);
    printf("Email: %s\n", email_ptr);
}

/* Adicionar pessoa */
void adicionar_pessoa(void *pBuffer) {
    int *n_ptr = (int*)((char*)pBuffer + OFFSET_NPEOPLE);
    char *temp_name = (char*)pBuffer + OFFSET_TEMPNAME;
    char *temp_email = (char*)pBuffer + OFFSET_TEMPEMAIL;
    int *temp_int = (int*)((char*)pBuffer + OFFSET_TEMPINT);
    char *records = (char*)pBuffer + OFFSET_RECORDS;

    if (*n_ptr >= MAX_PEOPLE) {
        printf("Agenda cheia (max %d).\n", MAX_PEOPLE);
        return;
    }

    printf("Nome: ");
    if (!fgets(temp_name, NAME_SIZE, stdin)) return;
    /* remover newline se existir */
    char *pnl = strchr(temp_name, '\n');
    if (pnl) *pnl = '\0';

    printf("Idade: ");
    if (scanf("%d", temp_int) != 1) {
        printf("Entrada inválida.\n");
        clear_stdin(pBuffer);
        return;
    }
    clear_stdin(pBuffer);

    printf("Email: ");
    if (!fgets(temp_email, EMAIL_SIZE, stdin)) return;
    pnl = strchr(temp_email, '\n');
    if (pnl) *pnl = '\0';

    /* copiar para o registro novo */
    char *dest = records + (*n_ptr) * RECORD_SIZE;
    char *dest_name = dest;
    int *dest_age = (int*)(dest + NAME_SIZE);
    char *dest_email = dest + NAME_SIZE + sizeof(int);

    /* inicializar e copiar */
    memset(dest_name, 0, NAME_SIZE);
    memset(dest_email, 0, EMAIL_SIZE);

    strncpy(dest_name, temp_name, NAME_SIZE - 1);
    *dest_age = *temp_int;
    strncpy(dest_email, temp_email, EMAIL_SIZE - 1);

    (*n_ptr)++;
    printf("Pessoa adicionada.\n");
}

/* Listar todos */
void listar_todos(void *pBuffer) {
    int *n_ptr = (int*)((char*)pBuffer + OFFSET_NPEOPLE);
    char *records = (char*)pBuffer + OFFSET_RECORDS;
    char *cur = records;
    char *end = records + (*n_ptr) * RECORD_SIZE;

    if (*n_ptr == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }

    while (cur < end) {
        print_record(pBuffer, cur);
        printf("---------------------\n");
        cur += RECORD_SIZE;
    }
}

/* Buscar pessoa por nome (exata) */
void buscar_pessoa(void *pBuffer) {
    int *n_ptr = (int*)((char*)pBuffer + OFFSET_NPEOPLE);
    char *temp_name = (char*)pBuffer + OFFSET_TEMPNAME;
    char *records = (char*)pBuffer + OFFSET_RECORDS;
    char *cur = records;
    char *end = records + (*n_ptr) * RECORD_SIZE;
    int *temp_int = (int*)((char*)pBuffer + OFFSET_TEMPINT); /* usado como contador */

    *temp_int = 0; /* contador de achados */

    printf("Nome para buscar: ");
    if (!fgets(temp_name, NAME_SIZE, stdin)) return;
    char *pnl = strchr(temp_name, '\n');
    if (pnl) *pnl = '\0';

    while (cur < end) {
        char *rname = cur;
        if (rname[0] != '\0' && strcmp(rname, temp_name) == 0) {
            print_record(pBuffer, cur);
            (*temp_int)++;
        }
        cur += RECORD_SIZE;
    }

    if (*temp_int == 0) {
        printf("Nenhum resultado encontrado para '%s'.\n", temp_name);
    } else {
        printf("%d registro(s) encontrado(s).\n", *temp_int);
    }
}

/* Remover pessoa por nome (exata) -> desloca registros seguintes para "fechar o buraco" */
void remover_pessoa(void *pBuffer) {
    int *n_ptr = (int*)((char*)pBuffer + OFFSET_NPEOPLE);
    char *temp_name = (char*)pBuffer + OFFSET_TEMPNAME;
    char *records = (char*)pBuffer + OFFSET_RECORDS;
    int *index_ptr = (int*)((char*)pBuffer + OFFSET_TEMPINT); /* usaremos como índice */
    int *flag_ptr = (int*)((char*)pBuffer + OFFSET_MENU); /* usaremos como flag temporário */

    if (*n_ptr == 0) {
        printf("Agenda vazia.\n");
        return;
    }

    printf("Nome para remover: ");
    if (!fgets(temp_name, NAME_SIZE, stdin)) return;
    char *pnl = strchr(temp_name, '\n');
    if (pnl) *pnl = '\0';

    *index_ptr = 0;
    *flag_ptr = 0;

    char *cur = records;
    char *end = records + (*n_ptr) * RECORD_SIZE;

    while (cur < end) {
        char *rname = cur;
        if (rname[0] != '\0' && strcmp(rname, temp_name) == 0) {
            *flag_ptr = 1; /* encontrado */
            break;
        }
        cur += RECORD_SIZE;
        (*index_ptr)++;
    }

    if (*flag_ptr == 0) {
        printf("Nome não encontrado.\n");
        return;
    }

    /* shift left: copiar registros após o removido para a posição atual */
    char *from = records + ((*index_ptr) + 1) * RECORD_SIZE;
    char *to   = records + (*index_ptr) * RECORD_SIZE;
    char *limit = records + (*n_ptr) * RECORD_SIZE;

    while (from < limit) {
        memcpy(to, from, RECORD_SIZE);
        to += RECORD_SIZE;
        from += RECORD_SIZE;
    }

    /* zerar último registro */
    char *last = records + ((*n_ptr) - 1) * RECORD_SIZE;
    memset(last, 0, RECORD_SIZE);
    (*n_ptr)--;
    printf("Removido com sucesso.\n");
}

int main(void) {
    void *pBuffer = NULL;

    /* alocar sem declarar variável para tamanho: calculamos direto na chamada */
    pBuffer = malloc(OFFSET_RECORDS + MAX_PEOPLE * RECORD_SIZE);
    if (!pBuffer) {
        fprintf(stderr, "Falha ao alocar memoria.\n");
        return 1;
    }

    /* inicializar memória: tudo zero */
    memset(pBuffer, 0, OFFSET_RECORDS + MAX_PEOPLE * RECORD_SIZE);

    /* ponteiros que apontam para dentro de pBuffer */
    int *n_ptr = (int*)((char*)pBuffer + OFFSET_NPEOPLE);
    int *menu_ptr = (int*)((char*)pBuffer + OFFSET_MENU);

    *n_ptr = 0;
    *menu_ptr = 0;

    while (1) {
        printf("\n=== AGENDA (sem variaveis, apenas pBuffer) ===\n");
        printf("1 - Adicionar Pessoa\n");
        printf("2 - Remover Pessoa\n");
        printf("3 - Buscar Pessoa\n");
        printf("4 - Listar todos\n");
        printf("5 - Sair\n");
        printf("Escolha: ");

        /* ler escolha direto no menu_ptr (que aponta em pBuffer) */
        if (scanf("%d", menu_ptr) != 1) {
            printf("Entrada inválida.\n");
            clear_stdin(pBuffer);
            continue;
        }
        clear_stdin(pBuffer);

        if (*menu_ptr == 1) {
            adicionar_pessoa(pBuffer);
        } else if (*menu_ptr == 2) {
            remover_pessoa(pBuffer);
        } else if (*menu_ptr == 3) {
            buscar_pessoa(pBuffer);
        } else if (*menu_ptr == 4) {
            listar_todos(pBuffer);
        } else if (*menu_ptr == 5) {
            printf("Saindo...\n");
            break;
        } else {
            printf("Opção inválida.\n");
        }
    }

    free(pBuffer);
    return 0;
}
