#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>


struct data{
	int p;
	int linie[20];
	int coloana[20];
};

void *func(void *args){

	struct data *st = (struct data *) args;
	int c = 0;

	for(int k = 0; k < st->p; k++){
		c += st->linie[k] * st->coloana[k];
	}

	char *rez = (char*) malloc(5);
	sprintf(rez, "%d", c);

	return rez;
}

int main(int argc, char *argv[]){

	int n = 2;
	int m = 2;

    int A[2][2] = {{1, 2},	
	               {4, 5}};
		      
    int B[2][2] = {{7, 3},	
      	          {7, 5}};

	int C[n][m];

	char* rez[n * m];
	pthread_t threads[n * m];
	struct data st[n * m];

	int count = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
	
			st[count].p = 2;
			for(int x = 0; x < st[count].p; x++){
				st[count].linie[x] = A[i][x];
				st[count].coloana[x] = B[x][j]; 
			}

			pthread_create(&threads[count], NULL, func, &st[count]);	

			count++;
			
		}	
	}

	for(int i = 0; i < n * m; i++){
		pthread_join(threads[i], (void**) &rez[i]);
	}

	
	count = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){		
			C[i][j] = atoi(rez[count]);
			count++;
		}
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}

	return 0;
}