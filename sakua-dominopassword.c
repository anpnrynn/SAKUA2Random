//copyright Anoop Kumar Narayanan 2023 anoop.kumar.narayanan@gmail.com
#include "sakua-dominopasswordgen1.h"
#include "sakua-dominopasswordgen1_1.h"
#include "sakua-dominopasswordgen2.h"
#include "sakua-dominopasswordgen2_1.h"



void  dp_algo_setup      ( struct domino_password *dp, int gen ){
	switch( gen ){
		case 0:
			dp->algo = gen1_algo;
			break;
		case 1:
			dp->algo = gen1_1_algo;
			break;
		case 2:
			dp->algo = gen2_algo;
			break;
		case 3:
			dp->algo = gen2_1_algo;
			break;
		default:
			dp->algo = gen2_1_algo;
			break;
	}	
	dp->algo->function_algo_init(dp->algo);
	dp->algo->shuffled = dp->shuffled;
	char *tmpseed = 0;
	dp_set_gen_seed( dp, tmpseed );
#ifdef DEBUG
	printf("DBUG: algo_info: %s \n", dp->algo->seed );
	printf("DBUG: algo_info: %d \n", dp->algo->pin );
	printf("DBUG: algo_info: %d \n", dp->algo->random[0] );
	printf("DBUG: algo_info: %d \n", dp->algo->random[1] );
	printf("DBUG: algo_info: %d \n", dp->algo->random[2] );
#endif
}

void  dp_set_gen_seed    ( struct domino_password *dp,  char *seed ){
	if( seed ){
		strncpy(dp->gen_seed, seed, DP_SEED_LEN );
	} else {
		seed == 0;
	}
	dp->algo->function_set_get_seed( dp->algo, &seed );
}

char* dp_get_gen_seed    ( struct domino_password *dp){
	return dp->gen_seed;
}

const struct domino_password_algo* dp_get_algo ( struct domino_password *dp ) {
	return dp->algo;
}

void  dp_gen_shuffled    ( struct domino_password *dp){
	dp->algo->function_shuffle( dp->algo, dp->shuffled );
}

char* dp_get_shuffled    ( struct domino_password *dp){
	return dp->shuffled;
}

void  dp_set_n_activated ( struct domino_password *dp, int n ){
	if( n < 8 || n > DP_SEED_LEN ){
		n = 0;
		return;
	}
	dp->n_activated = n;
}

int   dp_get_n_activated ( struct domino_password *dp){
	return dp->n_activated;
}

void  dp_set_activated   ( struct domino_password *dp, int *array ){
	if ( dp->n_activated >= 8 && dp->n_activated <= DP_SEED_LEN ){
		memcpy ( dp->activated, array, sizeof(int) * dp->n_activated );	
	}
	return;
}

int  *dp_get_activated   ( struct domino_password *dp, int *n ){
	*n = dp->n_activated;
	return dp->activated;
}

char *dp_get_domino_key  ( struct domino_password *dp){
	int i = 0;
	for( i = 0; i < dp->n_activated; i++ ) {
		dp->key[i] = dp->shuffled[ dp->activated[ i ] ] ;	
	}
	dp->key[dp->n_activated] = 0;
	return dp->key;
}


void  dp_domino_init     ( struct domino_password *dp ){
	bzero( dp->gen_seed, 128 );
	bzero( dp->shuffled, 128 );
       	dp->n_activated = 0;
	bzero( dp->activated, DP_SEED_LEN*sizeof(int) ); 
	bzero( dp->key, 1024);	
	
	dp->function_algo_setup      = dp_algo_setup;
	dp->function_set_gen_seed    = dp_set_gen_seed;
	dp->function_get_gen_seed    = dp_get_gen_seed;
	dp->function_get_algo        = dp_get_algo;
	dp->function_gen_shuffled    = dp_gen_shuffled;
	dp->function_get_shuffled    = dp_get_shuffled;
	dp->function_set_n_activated = dp_set_n_activated;
	dp->function_get_n_activated = dp_get_n_activated;
	dp->function_set_activated   = dp_set_activated;
	dp->function_get_activated   = dp_get_activated;
	dp->function_get_domino_key  = dp_get_domino_key;
}

struct domino_password* domino_password_new () {
	struct domino_password *dp = (struct domino_password *) malloc ( sizeof( struct domino_password ) );
	dp->function_init = dp_domino_init;
	dp->function_init ( dp );
	return dp;
}
