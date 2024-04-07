//copyright Anoop Kumar Narayanan 2023 anoop.kumar.narayanan@gmail.com
#include "sakua-dominopasswordgen1_1.h"

static unsigned int shiftkeys[40] = { 3500, 301390, 0 };

void gen1_1_algo_init   ( struct domino_password_algo *algo_info ) {
	static int random[6] = { 23, 13, 17, 7, 11 };
	algo_info->pin = 2023;
	algo_info->random = random;
	algo_info->incremental = 0;
}


void gen1_1_set_get_seed    ( struct domino_password_algo *algo_info, char **seed  ) {
	static char initdata[128] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`~!@#$%^&*()_+-={}|[]\\:\";'<>?,./^&*()_+-={}|[]";
	if( *seed == 0 ) {
	    *seed = initdata;
	    algo_info->seed = initdata;
		if( algo_info->incremental == 1 ){
			memcpy( algo_info->shuffled, algo_info->seed, DP_SEED_LEN );
			algo_info->shuffled[DP_SEED_LEN] = 0;
		}
	} else {
	    memcpy( initdata, *seed, DP_SEED_LEN );
	    initdata[DP_SEED_LEN] = 0;
		algo_info->seed = initdata;
		if( algo_info->incremental == 1 ){
			memcpy( algo_info->shuffled, algo_info->seed, DP_SEED_LEN );
			algo_info->shuffled[DP_SEED_LEN] = 0;
		}
	}
}



void gen1_1_set_pin     ( struct domino_password_algo *algo_info, int n ) {
	algo_info->pin = n;
}


int  gen1_1_get_pin     ( struct domino_password_algo *algo_info ) {
	return algo_info->pin;
}


void gen1_1_set_random  ( struct domino_password_algo *algo_info , int *random ) {
	static int srandom[6];
	srandom[0] = random[0];
	srandom[1] = random[1];
	srandom[2] = random[2];
	srandom[2] = random[4];
	srandom[2] = random[5];
	algo_info->random = srandom;
}


void gen1_1_rotate      ( char *data, int count, int n ) {
	char tmpdata[128];
	memcpy( tmpdata, data, count );
	memcpy( data, &data[count], n-count );
	memcpy( &data[ n-count ], tmpdata, count );
}


void gen1_1_swapchars   ( char *data, int i, int j, int n ) {
	char tmp = 0;
	tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
}


int gen1_1_rotatevalue( int pin, unsigned int *shiftkeys ){
	int i = 0;
	static int rotatevalues [] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 0 };
	while( shiftkeys[i] != 0 ){
		if( pin < shiftkeys[i] ) {
			return 0;
		} else {

			if( pin % shiftkeys[i] == 0 ){
				return rotatevalues[i];
			}
		}
		i++;
	}
	return 0;
}


void gen1_1_shuffle     ( struct domino_password_algo *algo_info, char *data ) {
	int n = 108;
     if( algo_info->incremental == 0 ){
         n = strlen(algo_info->seed);
         if( n == 0 )
	     return;
         memcpy( data, algo_info->seed, DP_SEED_LEN);
         data[DP_SEED_LEN] = 0;
     } else {
         //n = strlen(algo_info->shuffled);
         //if( n == 0 )
	     //return;
         //memcpy( data, algo_info->shuffled, DP_SEED_LEN);
         data[DP_SEED_LEN] = 0;
     }
     int k = 1;
#ifdef DEBUG
     printf("DBUG: shuffle start : %s %d \n", data, strlen(data) );
     printf("DBUG: shuffle start : %d \n", algo_info->pin );
     printf("DBUG: shuffle start : %d \n", algo_info->random[0] );
     printf("DBUG: shuffle start : %d \n", algo_info->random[1] );
     printf("DBUG: shuffle start : %d \n", algo_info->random[2] );
     printf("DBUG: shuffle start : %s \n", data );
#endif
     
     int j = 0;
     if( algo_info->incremental == 1 ){
	 j = algo_info->pin - 1;
     }
     for ( ;  j < algo_info->pin; j++ ) {
         char* s1 = &data[0];
         char* s2 = &data[n/2];

         for ( int i = 0; i < n/4; i++ ){
               if( k % 2  == 0 ){
                    gen1_1_swapchars( s1, i, n/2-i-1, n/2 );
                    gen1_1_swapchars( s1+algo_info->random[3], i, n/2-i-1-algo_info->random[2], n/2 );
                    gen1_1_swapchars( s2, i, n/2-i-1, n/2 );
                    gen1_1_swapchars( s1+algo_info->random[4], i, n/2-i-1-algo_info->random[4], n/2 );
               } else {
                    gen1_1_swapchars( s1, i, n/2-i-2, n/2 );
                    gen1_1_swapchars( s1+algo_info->random[3], i, n/2-i-2-algo_info->random[3], n/2 );
                    gen1_1_swapchars( s2, i, n/2-i-2, n/2 );
                    gen1_1_swapchars( s1+algo_info->random[4], i, n/2-i-2-algo_info->random[4], n/2 );
               }
               gen1_1_swapchars( s1, i, algo_info->random[1]+i, n/2 );
               gen1_1_swapchars( s2, i, algo_info->random[2]+i, n/2 );
               k++;
         }
         gen1_1_rotate( s1, algo_info->random[1], n/2 );
         gen1_1_rotate( s2, algo_info->random[2], n/2 );
         gen1_1_rotate( data, algo_info->random[0], n - algo_info->random[0] );
         gen1_1_rotate( s1, algo_info->random[3], n - algo_info->random[3] );
         gen1_1_rotate( &s1[algo_info->random[3]], algo_info->random[4], n/2 );
	 
	 int nrotate = 0;
         if( ( nrotate = gen1_1_rotatevalue(  algo_info->pin, shiftkeys) ) != 0  ){
         //if( algo_info->pin % 3500 == 0 ){
            strcpy( algo_info->shuffled, data );
            gen1_1_rotate( algo_info->shuffled, nrotate, n - nrotate );
         }
	 //printf("INFO: nrotate = %d \n", nrotate );
     }
#ifdef DEBUG
     printf("DBUG: shuffle end : %s %d \n", data, strlen(data) );
     printf("DBUG: shuffle end : %d \n", algo_info->pin );
     printf("DBUG: shuffle end : %d \n", algo_info->random[0] );
     printf("DBUG: shuffle end : %d \n", algo_info->random[1] );
     printf("DBUG: shuffle end : %d \n", algo_info->random[2] );
     printf("DBUG: shuffle end : %s \n", data );
#endif
     return;
}


void gen1_1_fastforward     ( struct domino_password_algo *algo_info, char *data ){
	algo_info->incremental = 0;
	gen1_1_shuffle(algo_info, data );
	algo_info->incremental = 1;
}


struct domino_password_algo _gen1_1_algo = {
	1,
	2023,
	0,
	0,
	gen1_1_algo_init,
	gen1_1_set_get_seed,
	gen1_1_set_pin,
	gen1_1_get_pin,
	gen1_1_set_random,
	gen1_1_rotate,
	gen1_1_swapchars,
	gen1_1_shuffle,
	gen1_1_fastforward,
	0,
	0
};

struct domino_password_algo *gen1_1_algo = &_gen1_1_algo;
