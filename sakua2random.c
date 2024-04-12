//Copyright Anoop Kumar Narayanan, anoop.kumar.narayanan@gmail.com
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "sakua-dominopasswordgen1.h"
#include "sakua-dominopasswordgen1_1.h"
#include "sakua-dominopasswordgen2.h"
#include "sakua-dominopasswordgen2_1.h"
#include "sakua-dominopassword.h"

#define _FILE_OFFSET_BITS   64
#define __USE_FILE_OFFSET64 1


int main(int argc, char *argv[]) {

	struct domino_password *dp = 0;
	char *s = 0, *k =0;

	int n    = 0;
	int pin  = 0;
	int algo = 0;

	if( argc < 5 ){
		printf( "Usage: %s <algo> <Start of pin> <Number of strings> <filename>\n", argv[0]);
		printf( "	Algo, 0 - 1_0, 1 - 1_1, 2 - 2_0, 3 - 2_1 \n");
		return 0;
	} else {
		algo = atoi( argv[1] );
		pin = atoi( argv[2] );
		n  = atoi( argv[3] );
		printf( "Algo = %d, Start of pin = %d, Number of strings = %d \n", algo, pin, n);
	}


	dp = 0; s = 0; k = 0;
	dp = domino_password_new();
	dp->function_algo_setup( dp, algo );
	dp->algo->function_set_pin( dp->algo, pin );
	dp->algo->incremental = 0;
	fflush(stderr);
	dp->function_set_gen_seed( dp, 0 );
	dp->algo->function_fastforward( dp->algo, dp->shuffled );
	dp->algo->incremental = 1;
	fflush(stderr);

	FILE *fp = fopen(argv[4], "w+");
	int i = 0;
	for( i = 0; i < n; i++ ){
           fflush(stderr);
           dp->algo->function_set_pin( dp->algo, ++pin );
           dp->function_gen_shuffled( dp );
           fprintf( fp, "%s\n", dp->shuffled );
		if( pin % 10000 == 0 )
           fprintf( stderr, "INFO: Pin = %d \n", pin );
           fflush(fp);
	}

	fclose( fp );
    return 0;
}
