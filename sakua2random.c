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
    int pin = 2024;
    //int pin = 200;

	struct domino_password *dp = 0;
	char *s = 0, *k =0;

	fprintf( stderr, "Generating for %d years, with pin = %d ", years, pin );
	fflush(stderr);

	dp = 0; s = 0; k = 0;
	dp = domino_password_new();
	dp->function_algo_setup( dp, 1 );



	FILE *fp = fopen("readable_random-11.txt", "w+");


	//fprintf( stderr, "Generating for %d years, with pin = %d ", years, pin );
	#define MULTIPLES 31622400 //3600x24X366
	int i = 0;
	char randomtmp [2048];
	int j = 1;
	dp->function_set_gen_seed( dp, 0 );
    dp->algo->function_set_pin( dp->algo, pin );
    //gen1_1_algo->pin = 200;
    //gen1_1_shuffle(gen1_1_algo, dp->shuffled );
    //dp->function_gen_shuffled( dp );
    //strcpy( dp->gen_seed, dp->shuffled);
    //strcpy( dp->algo->seed, dp->shuffled);
    pin = 2023;
    dp->algo->function_set_pin( dp->algo, pin );
	//fprintf( stderr, "Generating for %d years, with pin = %d ", years, pin );
	for( i = 0; i < MULTIPLES * years ; i++ ){

        //fprintf(stderr, "%d", i);
        fflush(stderr);
        dp->function_gen_shuffled( dp );
        //strncpy( seed, dp->function_get_shuffled(dp), 108 );
        dp->algo->function_set_pin( dp->algo, pin++ );
        //strcpy( dp->gen_seed, dp->shuffled);
        //strcpy( dp->algo->seed, dp->shuffled);
        //dp->algo->function_set_get_seed ( dp->algo, &seed );
        fprintf( fp, "%s\n", dp->shuffled );
        fprintf( stderr, "%s\n", dp->shuffled );
        fflush(fp);
	}

	fclose( fp );
    return 0;
}
