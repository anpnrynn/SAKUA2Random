//copyright Anoop Kumar Narayanan 2023 anoop.kumar.narayanan@gmail.com
#include <stdio.h>

#include "sakua-dominopasswordgen2.h"
#include "sakua-dominopasswordgen1.h"
#include "sakua-dominopasswordgen1_1.h"
#include "sakua-dominopasswordgen2_1.h"

int main() {
	char *initdata = 0;
	char shuffled_data[128] = "";

	bzero(shuffled_data, 128);
	gen2_algo->function_algo_init( gen2_algo );
	gen2_algo->function_set_pin( gen2_algo, 2023 );
	gen2_algo->function_set_get_seed( gen2_algo, &initdata );
	gen2_algo->function_shuffle( gen2_algo, shuffled_data );
	printf( " Output = %s \n", shuffled_data );

	char *initdata1 = 0;
	bzero(shuffled_data, 128);
	gen1_algo->function_algo_init( gen1_algo );
	gen1_algo->function_set_pin( gen1_algo, 2023 );
	gen1_algo->function_set_get_seed( gen1_algo, &initdata1 );
	gen1_algo->function_shuffle( gen1_algo, shuffled_data );
	printf( " Output = %s \n", shuffled_data );

	char *initdata1_1 = 0;
	bzero(shuffled_data, 128);
	gen1_1_algo->function_algo_init( gen1_1_algo );
	gen1_1_algo->function_set_pin( gen1_1_algo, 2023 );
	gen1_1_algo->function_set_get_seed( gen1_1_algo, &initdata1_1 );
	gen1_1_algo->function_shuffle( gen1_1_algo, shuffled_data );
	printf( " Output = %s \n", shuffled_data );

	char *initdata2_1 = 0;
	bzero(shuffled_data, 128);
	gen2_1_algo->function_algo_init( gen2_1_algo );
	gen2_1_algo->function_set_pin( gen2_1_algo, 2023 );
	gen2_1_algo->function_set_get_seed( gen2_1_algo, &initdata2_1 );
	gen2_1_algo->function_shuffle( gen2_1_algo, shuffled_data );
	printf( " Output = %s \n", shuffled_data );
	return 0;
}
