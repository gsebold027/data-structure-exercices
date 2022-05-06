#ifndef __T_TIME__
#define __T_TIME__

typedef struct {
	short int h, m, s;
} t_time;

t_time * t_time_init(short int h, short int m, short int s);
int t_time_cmp(t_time * ta, t_time * tb);
void t_time_free(t_time * t);

int t_time_get_h(t_time * t);
int t_time_get_m(t_time * t);
int t_time_get_s(t_time * t);

#endif
