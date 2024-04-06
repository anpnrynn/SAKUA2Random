//copyright Anoop Kumar Narayanan 2023 anoop.kumar.narayanan@gmail.com
#include <stdio.h>

#include "sakua-dominopasswordgen1.h"
#include "sakua-dominopasswordgen1_1.h"
#include "sakua-dominopasswordgen2.h"
#include "sakua-dominopasswordgen2_1.h"
#include "sakua-dominopassword.h"

int main() {
	struct domino_password *dp = 0;
	char *s = 0, *k =0;
	int array[10] = { 0,1,2,3,4,5,6,7,8,9 };
	int array2[10] = { 98,99,100,101,102,103,104,105,106,107  };

	dp = 0; s = 0; k = 0;
	dp = domino_password_new();
	dp->function_algo_setup( dp, 2 );
	dp->function_set_gen_seed( dp, 0 );
	dp->function_gen_shuffled( dp );
	dp->function_set_n_activated( dp, 10 );
	dp->function_set_activated( dp, array );
	s = dp->function_get_shuffled(dp);
	printf( " Shuffle = %s \n", s );
	k = dp->function_get_domino_key( dp );
	printf( " Key = %s \n", k );
	dp->function_set_activated( dp, array2 );
	k = dp->function_get_domino_key( dp );
	printf( " Key = %s \n", k );

	dp = 0; s = 0; k = 0;
	dp = domino_password_new();
	dp->function_algo_setup( dp, 0 );
	dp->function_set_gen_seed( dp, 0 );
	dp->function_gen_shuffled( dp );
	dp->function_set_n_activated( dp, 10 );
	dp->function_set_activated( dp, array );
	s = dp->function_get_shuffled(dp);
	printf( " Shuffle = %s \n", s );
	k = dp->function_get_domino_key( dp );
	printf( " Key = %s \n", k );
	dp->function_set_activated( dp, array2 );
	k = dp->function_get_domino_key( dp );
	printf( " Key = %s \n", k );

	dp = 0; s = 0; k = 0;
	dp = domino_password_new();
	dp->function_algo_setup( dp, 1 );
	dp->function_set_gen_seed( dp, 0 );
	dp->function_gen_shuffled( dp );
	dp->function_set_n_activated( dp, 10 );
	dp->function_set_activated( dp, array );
	s = dp->function_get_shuffled(dp);
	printf( " Shuffle = %s \n", s );
	k = dp->function_get_domino_key( dp );
	printf( " Key = %s \n", k );
	dp->function_set_activated( dp, array2 );
	k = dp->function_get_domino_key( dp );
	printf( " Key = %s \n", k );

	dp = 0; s = 0; k = 0;
	dp = domino_password_new();
	dp->function_algo_setup( dp, 3 );
	dp->function_set_gen_seed( dp, 0 );
	dp->function_gen_shuffled( dp );
	dp->function_set_n_activated( dp, 10 );
	dp->function_set_activated( dp, array );
	s = dp->function_get_shuffled(dp);
	printf( " Shuffle = %s \n", s );
	k = dp->function_get_domino_key( dp );
	printf( " Key = %s \n", k );
	dp->function_set_activated( dp, array2 );
	k = dp->function_get_domino_key( dp );
	printf( " Key = %s \n", k );
	return 0;
}
