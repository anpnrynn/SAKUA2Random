//copyright Anoop Kumar Narayanan 2023 anoop.kumar.narayanan@gmail.com
#include <stdio.h>

#include "sakua-dominopasswordgen1.h"
#include "sakua-dominopasswordgen1_1.h"
#include "sakua-dominopasswordgen2.h"
#include "sakua-dominopasswordgen2_1.h"
#include "sakua-dominopassword.h"
#include "sakua-keycreate.h"

int main() {

	struct key_create *kc = sakua_key_create_new ( 3 );
	//sakua_key_create_setup( kc );
	sakua_key_create_setup_debug( kc );
	sakua_set_preseed (kc, 0);
        sakua_set_seedpin ( kc, 2023 );
	printf( " --------------------\n");
	printf( " --------------------\n");
	printf( " --------------------\n");
        printf( " Seed = %s \n", sakua_get_seed(kc) );
        sakua_set_seed    ( kc, 0 );
        sakua_set_pin     ( kc, 2023 );
        printf( " Secu = %s \n", sakua_get_secure(kc) );
	kc->n_sequence  = 9;
	kc->sequence[0] = 0;
	kc->sequence[1] = 1;
	kc->sequence[2] = 2;
	kc->sequence[3] = 3;
	kc->sequence[4] = 4;
	kc->sequence[5] = 5;
	kc->sequence[6] = 6;
	kc->sequence[7] = 7;
	kc->sequence[8] = 8;
        printf( " Key  = %s \n", sakua_get_key     ( kc ));
	printf( " --------------------\n");
	printf( " --------------------\n");
	printf( " --------------------\n");
	sakua_key_create_delete( kc );


	kc = sakua_key_create_new ( 3 );
	set_key_create_tv_pair (kc, KC_INFO_SOCIAL1, "1ello1" );
	set_key_create_tv_pair (kc, KC_INFO_SOCIAL2, "2ello1" );
	set_key_create_tv_pair (kc, KC_INFO_SOCIAL3, "3ello1" );
	set_key_create_tv_pair (kc, KC_INFO_SOCIAL4, "4ello1" );
	set_key_create_tv_pair (kc, KC_INFO_SOCIAL5, "5ello1" );
	set_key_create_tv_pair (kc, KC_INFO_SOCIAL6, "6ello1" );
	set_key_create_tv_pair (kc, KC_INFO_SOCIAL7, "7ello1" );

	sakua_key_create_setup( kc );
	sakua_key_create_setup_debug( kc );
	sakua_set_preseed (kc, 0);
	printf( " --------------------\n");
	printf( " --------------------\n");
	printf( " --------------------\n");
        printf( " Seed = %s \n", sakua_get_seed(kc) );
        sakua_set_seed    ( kc, kc->seed );
        printf( " Secu = %s \n", sakua_get_secure(kc) );
	kc->n_sequence  = 9;
	kc->sequence[0] = 0;
	kc->sequence[1] = 1;
	kc->sequence[2] = 2;
	kc->sequence[3] = 3;
	kc->sequence[4] = 4;
	kc->sequence[5] = 5;
	kc->sequence[6] = 6;
	kc->sequence[7] = 7;
	kc->sequence[8] = 8;
        printf( " Key  = %s \n", sakua_get_key     ( kc ));
	printf( " --------------------\n");
	printf( " --------------------\n");
	printf( " --------------------\n");
	sakua_key_create_delete( kc );

	return 0;
}
