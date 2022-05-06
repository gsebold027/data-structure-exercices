#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "t_time.h"
#include "t_timetable.h"

t_timetable_header * t_timetable_init() {
    t_timetable_header * tt;

    tt = (t_timetable_header *) malloc(sizeof(t_timetable_header));

    tt->start = NULL;
    tt->finish = NULL;
    tt->count = 0;
    return(tt);
}

t_timetable_item * t_timetable_item_init(t_time * key, char * value) {
    t_timetable_item * tti;

    tti = (t_timetable_item *) malloc(sizeof(t_timetable_item));

    tti->key = key;
    tti->value = value;
    tti->next = NULL;
    tti->prev = NULL;

    return(tti);
}

void t_timetable_put(t_timetable_header * tt, t_timetable_item * tti) {
    if (tt->count == 0) {
        tt->start = tti;
        tt->finish = tti;
        tt->count++;
        return;
    }

    tti->prev = tt->finish;
    tt->finish->next = tti;
    tt->finish = tti;
    tt->count++;

    return;
}

void t_timetable_delete(t_timetable_header * tt, t_time * key) {
    t_timetable_item * tti = tt->start;
    int count = 1;

    while(count<=tt->count) {
        if ((t_time_cmp(tti->key, key)) == 0) {
            tti->prev->next = tti->next;
            tti->next->prev = tti->prev;
            tt->count--;
            return;
        }
        tti = tti->next;
        count++;
    }
}

char * t_timetable_get(t_timetable_header * tt, t_time * key) {
    t_timetable_item * tti = tt->start;
    int count = 1;

    while(count<=tt->count) {
        if ((t_time_cmp(tti->key, key)) == 0) {
            return tti->value;
        }
        tti = tti->next;
        count++;
    }

    return NULL;
}

bool t_timetable_contains(t_timetable_header * tt, t_time * key) {
    t_timetable_item * tti = tt->start;
    int count = 1;

    while(count<=tt->count) {
        if ((t_time_cmp(tti->key, key)) == 0) {
            return true;
        }
        tti = tti->next;
        count++;
    }
    return false;
}

bool t_timetable_is_empty(t_timetable_header * tt) {
    if (tt->count == 0) {
        return true;
    }
    return false;
}

int t_timetable_size(t_timetable_header * tt) {
    return tt->count;
}

t_time * t_timetable_floor (t_timetable_header * tt, t_time * key) {
    t_timetable_item * tti = tt->start;
    t_timetable_item * tti_floor = NULL;
    int count = 1;
    int result;

    while(count<=tt->count) {
        result = t_time_cmp(tti->key, key);
        if (tti_floor == NULL) {
            if (result == 0 || result == -1) { // igual ou menor coloca
                tti_floor = tti;
            }
        } else {
            if ((result == 0 || result == -1) && (t_time_cmp(tti_floor->key, tti->key) == -1) ) { // (igual ou menor) e (maior que o que tá)
                tti_floor = tti;
            }
        }
        tti = tti->next;
        count++;
    }
    return tti_floor->key;
}

void t_timetable_print(t_timetable_header * tt) {
	int i, h, m, s;
	t_time * t;
    t_timetable_item * tti = tt->start; 

	for (i = 0; i < tt->count; ++i) {
		t = tti->key;
		h = t_time_get_h(t);
		m = t_time_get_m(t);
		s = t_time_get_s(t);

		printf("[%02d] - %02d:%02d:%02d => %s\n",i, h, m, s, tti->value);
        tti = tti->next;
	}
}

void t_timetable_item_free (t_timetable_item * tti) {
    t_time_free(tti->key);
    free(tti);
}

void t_timetable_header_free (t_timetable_header * tt) {
    while(tt->count != 0){
        t_timetable_item * tti = tt->start;
        tt->start = tti->next;
        tt->start->prev = NULL;

        t_timetable_item_free(tti);

        tt->count--;
    }

    free(tt);
}
