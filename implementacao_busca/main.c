// Gustavo Henrique Sebold da Silva - grr20204429
// Marielly Louise Souza Frozza - grr20204502

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "t_time.h"
#include "t_timetable.h"

int main() {
    t_timetable_header * timetable_header;
    t_timetable_item * t_timetable_item_aux;
    t_time * t_time_aux;
    char * value;
    int h, m, s;
    size_t len;

    int opt, aux;
    bool result;

    timetable_header = t_timetable_init();

    while(opt != 10) {
        printf("O que você deseja fazer?\n");
        printf("1) Imprimir a tabela de cidades\n");
        printf("2) Adicionar uma nova cidade\n");
        printf("3) Remover uma cidade\n");
        printf("4) Saber se um horário está na tabela\n");
        printf("5) Buscar uma cidade a partir do horario\n");
        printf("6) Saber se a tabela está vazia\n");
        printf("7) Saber quantas cidades estão na tabela\n");
        printf("8) Pegar o maior horario menor ou igual a entrada\n");
        printf("9) Sair\n");
        scanf("%d", &opt);


        switch(opt) {
            case 1:
                t_timetable_print(timetable_header);
            break;
            case 2:
                printf("Digite o horario:\n");
                scanf("%d:%d:%d",&h,&m,&s);
                t_time_aux = t_time_init(h, m, s);

                getchar();

                value = NULL;
                printf("Digite a cidade:\n");
                len = getline(&value, &len, stdin);
                value[len-1] = '\0';

                t_timetable_item_aux = t_timetable_item_init(t_time_aux, value);

                t_timetable_put(timetable_header, t_timetable_item_aux);
            break;
            case 3:
                printf("Digite o horario:\n");
                scanf("%d:%d:%d",&h,&m,&s);
                t_time_aux = t_time_init(h, m, s);

                t_timetable_delete(timetable_header, t_time_aux);
            break;
            case 4:
                printf("Digite o horario:\n");
                scanf("%d:%d:%d",&h,&m,&s);
                t_time_aux = t_time_init(h, m, s);

                result = t_timetable_contains(timetable_header, t_time_aux);

                if (result) {
                    printf("O horario está na tabela");
                }
                else {
                    printf("O horario não está na tabela");
                }
            break;
            case 5:
                printf("Digite o horario:\n");
                scanf("%d:%d:%d",&h,&m,&s);
                t_time_aux = t_time_init(h, m, s);

                value = t_timetable_get(timetable_header, t_time_aux);

                if(value == NULL) {
                    printf("Cidade não encontrada!\n");
                } else {
                    printf("A cidade é %s\n", value);
                }
            break;
            case 6:
                result = t_timetable_is_empty(timetable_header);

                if (result) {
                    printf("A tabela está vazia");
                }
                else {
                    printf("A table não está vazia");
                }
            break;
            case 7:
                aux = t_timetable_size(timetable_header);

                printf("A tabela possui %d itens", aux);
            break;
            case 8:
                printf("Digite o horario:\n");
                scanf("%d:%d:%d",&h,&m,&s);
                t_time_aux = t_time_init(h, m, s);

                t_time_aux = t_timetable_floor(timetable_header, t_time_aux);

                h = t_time_get_h(t_time_aux);
                m = t_time_get_m(t_time_aux);
                s = t_time_get_s(t_time_aux);

                printf("\n%02d:%02d:%02d\n", h, m, s);
            break;
        }

        t_timetable_header_free(timetable_header);
    }
}