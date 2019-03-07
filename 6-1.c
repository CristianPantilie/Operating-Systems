
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>


void *func(void *args){
	
	char *str = (char*) args;
	char *rez = (char*) malloc (strlen(str) + 1);

	int i;
	int j = 0;
	for(i = strlen(str) - 1; i >= 0; --i){
		rez[j++] = str[i];
	}

	return rez;
}


int main(int argc, char *argv[]){

	char *str = argv[1];
	char *rez;
	
	

	pthread_t thr;
	pthread_create(&thr, NULL, func, str);
	pthread_join(thr, &rez);
		
	printf("%s", rez);
	

	//tid = pthread_create(funct, args);

	//pthread_join(&tid, ptr);

	return 0;
}
