//copyright Anoop Kumar Narayanan 2023 anoop.kumar.narayanan@gmail.com
#include "sakua-dominopasswordgen1_1.h"



void gen1_1_algo_init   ( struct domino_password_algo *algo_info ) {
	static int random[6] = { 23, 13, 17, 7, 11 };
	algo_info->pin = 2023;
	algo_info->random = random;
}


void gen1_1_set_get_seed    ( struct domino_password_algo *algo_info, char **seed  ) {
	static char initdata[128] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`~!@#$%^&*()_+-={}|[]\\:\";'<>?,./^&*()_+-={}|[]";
	if( *seed == 0 ) {
	    *seed = initdata;
	    algo_info->seed = initdata;
	} else {
	    memcpy( initdata, algo_info->seed, DP_SEED_LEN );
	    initdata[DP_SEED_LEN] = 0;
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


void gen1_1_shuffle     ( struct domino_password_algo *algo_info, char *data ) {
     int n = strlen(algo_info->seed);
     if( n == 0 )
	     return;
     memcpy( data, algo_info->seed, DP_SEED_LEN);
     data[DP_SEED_LEN] = 0;
     int k = 1;
#ifdef DEBUG
     printf("DBUG: shuffle start : %s %d \n", data, strlen(data) );
     printf("DBUG: shuffle start : %d \n", algo_info->pin );
     printf("DBUG: shuffle start : %d \n", algo_info->random[0] );
     printf("DBUG: shuffle start : %d \n", algo_info->random[1] );
     printf("DBUG: shuffle start : %d \n", algo_info->random[2] );
     printf("DBUG: shuffle start : %s \n", data );
#endif
     for ( int j = 0; j < algo_info->pin; j++ ) {
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
         if( algo_info->pin % 3500 == 0 ){
            strcpy( algo_info->seed, data );
            gen1_1_rotate( algo_info->seed, 3, n - 3 );
         }
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
	gen1_1_shuffle
};

struct domino_password_algo *gen1_1_algo = &_gen1_1_algo;
