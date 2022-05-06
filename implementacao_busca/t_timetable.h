#ifndef __T_TIMETABLE__
#define __T_TIMETABLE__

#include "t_time.h"
#include <stdbool.h>

typedef struct item{
    t_time * key;
    char * value;
    struct item * next;
    struct item * prev;
} t_timetable_item;

typedef struct {
    t_timetable_item * start;
    t_timetable_item * finish;
    int count;
} t_timetable_header;

t_timetable_header * t_timetable_init();
t_timetable_item * t_timetable_item_init(t_time * key, char * value);
void t_timetable_put(t_timetable_header * tt, t_timetable_item * tti);
void t_timetable_delete(t_timetable_header * tt, t_time * key);
char * t_timetable_get(t_timetable_header * tt, t_time * key);
bool t_timetable_contains(t_timetable_header * tt, t_time * key);
bool t_timetable_is_empty(t_timetable_header * tt);
int t_timetable_size(t_timetable_header * tt);
t_time * t_timetable_floor (t_timetable_header * tt, t_time * key);
void t_timetable_print(t_timetable_header * tt);
void t_timetable_item_free (t_timetable_item * tti);
void t_timetable_header_free (t_timetable_header * tt);

#endif