//Copyright Anoop Kumar Narayanan, anoop.kumar.narayanan@gmail.com
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "sakua-dominopasswordgen1.h"
#include "sakua-dominopasswordgen1_1.h"
#include "sakua-dominopasswordgen2.h"
#include "sakua-dominopasswordgen2_1.h"
#include "sakua-dominopassword.h"

#define _FILE_OFFSET_BITS=64
#define __USE_FILE_OFFSET64    1


int main(int argc, char *argv) {

    int years = 4;
    int pin = 2031;

	struct domino_password *dp = 0;
	char *s = 0, *k =0;

	fprintf( stderr, "Generating for %d years, with pin = %d \n", years, pin );
	fflush(stderr);

	dp = 0; s = 0; k = 0;
	dp = domino_password_new();
	dp->function_algo_setup( dp, 1 );
	dp->algo->function_set_pin( dp->algo, pin );
	dp->algo->incremental = 0;
	fprintf( stderr, "Generating for %d years, with pin = %d \n", years, pin );
	fflush(stderr);
	dp->function_set_gen_seed( dp, 0 );
	dp->algo->function_fastforward( dp->algo, dp->shuffled );
	dp->algo->incremental = 1;

	fprintf( stderr, "Generating for %d years, with pin = %d \n", years, pin );
	fflush(stderr);

	FILE *fp = fopen("readable_random-11-1-05.txt", "w+");
	#define MULTIPLES 31622400 //3600x24X366
	int i = 0;
	for( i = 0; i < MULTIPLES * years ; i++ ){
           fflush(stderr);
           dp->algo->function_set_pin( dp->algo, ++pin );
           dp->function_gen_shuffled( dp );
           fprintf( fp, "%s\n", dp->shuffled );
           fprintf( stderr, "INFO: Pin = %d \n", pin );
           fflush(fp);
	}

	fclose( fp );
    return 0;
}
