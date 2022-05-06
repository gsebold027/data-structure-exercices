#include <stdlib.h>
#include <stddef.h>
#include "t_time.h"

t_time * t_time_init(short int h, short int m, short int s){
	t_time * nt;

	if(h < 0 || h > 23) return(NULL);
	if(m < 0 || m > 59) return(NULL);
	if(s < 0 || s > 59) return(NULL);

	nt = (t_time *) malloc(sizeof(t_time));

	nt->h = h;
	nt->m = m;
	nt->s = s;

	return(nt);
}

int t_time_cmp(t_time * ta, t_time * tb){
	int total_sa, total_sb;

	total_sa = ta->h*3600 + ta->m*60 + ta->s;
	total_sb = tb->h*3600 + tb->m*60 + tb->s;

	if(total_sa > total_sb)
		return(1);
	else if(total_sa < total_sb)
		return(-1);
	else
		return(0);
}

void t_time_free(t_time * t){
	free(t);
}

int t_time_get_h(t_time * t){ return t->h;}
int t_time_get_m(t_time * t){ return t->m;}
int t_time_get_s(t_time * t){ return t->s;}
