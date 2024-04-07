//Copyright Anoop Kumar Narayanan 2023 anoop.kumar.narayanan@gmail.com
#include "sakua-keycreate.h"

#include <string.h>
#include <stdlib.h>


//Work in progress
//Beta version, need to test this file out
//Compiles but untested.

int charmap[128] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 
	/*till 31*/
	2,       3,      5,      7,     11,     13,     17,     19, 
	23,     29,     31,     37,     41,     43,     47,     53,
	59,     61,     67,     71,     73,     79,     83,     89, 
	97,    101,    103,    107,    109,    113,    127,    131, 
	137,   139,    149,    151,    157,    163,    167,    173, 
	179,   181,    191,    193,    197,    199,    211,    223, 
	227,   229,    233,    239,    241,    251,    257,    263, 
	269,   271,    277,    281,    283,    293,    307,    311, 
	313,   317,    331,    337,    347,    349,    353,    359, 
	367,   373,    379,    383,    389,    397,    401,    409, 
	419,   421,    431,    433,    439,    443,    449,    457,
       	461,   463,    467,    479,    487,    0 
	/*till 128*/
};

int multipliers[90] = {
	        613,    617,    619,    631,    641,    643,    647,    653,    659,
	661,    673,    677,    683,    691,    701,    709,    719,    727,    733,
	739,    743,    751,    757,    761,    769,    773,    787,    797,    809,
	811,    821,    823,    827,    829,    839,    853,    857,    859,    863,
	877,    881,    883,    887,    907,    911,    919,    929,    937,    941,
	947,    953,    967,    971,    977,    983,    991,    997,    1009,   1013,
	1019,   1021,   1031,   1033,   1039,   1049,   1051,   1061,   1063,   1069,
	1087,   1091,   1093,   1097,   1103,   1109,   1117,   1123,   1129,   1151,
	1153,   1163,   1171,   1181,   1187,   1193,   1201,   1213,   1217,   1223
};

unsigned long long int string_to_number( char *value ){
	int n = strlen ( value );
	unsigned long long int result = 0;
	for ( int i = 0; i < n; i++ ){
		result += charmap[ value[i] ];	
	}
	return result;
}

unsigned long long int final_stage( unsigned long long int value ) {
	return multipliers[value%89] * value;
}

unsigned long long int calculate_number_from_info ( struct key_create *kc, unsigned int flags, unsigned long long int *calc_result ){
	unsigned long long int un   = string_to_number( kc->username );
	unsigned long long int ps   = string_to_number( kc->password );
	unsigned long long int date = string_to_number( kc->date );
	unsigned long long int time = string_to_number( kc->time );
	unsigned long long int accountid = string_to_number( kc->accountid );
	unsigned long long int doj       = string_to_number( kc->doj );
	
	unsigned long long int name = 0;    
	if( flags & KC_USENAME ) 
		name = string_to_number( kc->name ); 

	unsigned long long int pincode = 0;
	if( flags & KC_USEPINCODE )
		pincode = string_to_number( kc->pincode );

	unsigned long long int country = 0;
	if( flags & KC_USECOUNTRY )
		country = string_to_number( kc->country );

	unsigned long long int state   = 0;
	if( flags & KC_USESTATE )
		state = string_to_number( kc->state );

	unsigned long long int city    = 0;
	if( flags & KC_USECITY ) 
		city  = string_to_number( kc->city );

	unsigned long long int mobile  = 0;
	if( flags & KC_USEMOBILE )
		mobile = string_to_number( kc->mobile );

	unsigned long long int email   = 0;
	if( flags & KC_USEEMAIL )
		email = string_to_number( kc->email );

	unsigned long long int ss   = 0;
	if( flags & KC_USESS )
		ss = string_to_number( kc->ss );

	unsigned long long int gps   = 0;
	if( flags & KC_USEGPS )
		ss = string_to_number( kc->gps );

	unsigned long long int social1   = 0;
	if( flags & KC_USESOCIAL1 )
		ss = string_to_number( kc->social1 );

	unsigned long long int social2   = 0;
	if( flags & KC_USESOCIAL2 )
		ss = string_to_number( kc->social2 );

	unsigned long long int social3   = 0;
	if( flags & KC_USESOCIAL3 )
		ss = string_to_number( kc->social3 );

	unsigned long long int social4   = 0;
	if( flags & KC_USESOCIAL4 )
		ss = string_to_number( kc->social4 );

	unsigned long long int social5   = 0;
	if( flags & KC_USESOCIAL5 )
		ss = string_to_number( kc->social5 );

	unsigned long long int social6   = 0;
	if( flags & KC_USESOCIAL6 )
		ss = string_to_number( kc->social6 );

	unsigned long long int social7   = 0;
	if( flags & KC_USESOCIAL7 )
		ss = string_to_number( kc->social7 );

	unsigned long long int result = un + ps + date + time + accountid + 
			doj + name + pincode + country + state + city + 
			mobile + email + ss + gps + social1 + social2 + social3 +
			social4 + social5 + social6 + social7;

	*calc_result = result; //Intermediate 
	return final_stage( result ) + result % 1009; //final result
						      //either intermediate or final result can be used
}

void calculate_seedpin_from_result( unsigned long long int result , unsigned int *pin ){
	*pin = result % 9999;
	if( *pin == 0 ){
		*pin = 2937; 
		//my car number ... couldn't think of anything better !!!
	} else if ( *pin == 1 ){
		*pin = 7086; 
		//spartan number
	}
	return;
}

void calculate_pin_from_result( unsigned long long int result , unsigned int *pin ){
	*pin = result % 999999;
	if( *pin == 0 ){
		*pin = 2937; 
		//my car number ... couldn't think of anything better !!!
	} else if ( *pin == 1 ){
		*pin = 7086; 
		//spartan number
	}
	return;
}

void calculate_randoms_from_result( unsigned long long int result, int n_randoms, int *randoms ){
	unsigned int seed = (unsigned int) result ;
	for( int i = 0; i < n_randoms; i++ ){
		int r = rand_r ( &seed );
		int offset = r % 94; // in charmap table;
		randoms[i] = charmap[32+offset] % 54;
	}
	return;
}

//seed string is calculated using seedpin, baseseedstring & random
//baseseedstring is present in dominopassword algo
//secure string is calculated using dominopassword algorithm with the help of pin, seedstring & randoms

void set_key_create_tv_pair( struct key_create *kc, kc_info_type type, char *value ){
	if( type >= KC_INFO_MAX || !value )
		return;
	switch( type ) {
		case KC_INFO_USERNAME:
			if( strlen(value) > 127 )
				break;
			strcpy( kc->username, value );
			break;
		case KC_INFO_PASSWORD:
			if( strlen(value) > 127 )
				break;
			strcpy( kc->password, value );
			break;
		case KC_INFO_DATE:
			if( strlen(value) > 15 )
				break;
			strcpy( kc->date, value );
			break;
		case KC_INFO_TIME:
			if( strlen(value) > 15 )
				break;
			strcpy( kc->time, value );
			break;
		case KC_INFO_ACCID:
			if( strlen(value) > 23 )
				break;
			strcpy( kc->accountid, value );
			break;
		case KC_INFO_DOJ:
			if( strlen(value) > 15 )
				break;
			strcpy( kc->doj, value );
			break;
		case KC_INFO_NAME:
			if( strlen(value) > 127 )
				break;
			kc->flags |= KC_USENAME;
			strcpy( kc->name, value );
			break;
		case KC_INFO_PINCODE:
			if( strlen(value) > 7 )
				break;
			kc->flags |= KC_USEPINCODE;
			strcpy( kc->pincode, value );
			break;
		case KC_INFO_COUNTRY:
			if( strlen(value) > 31 )
				break;
			kc->flags |= KC_USECOUNTRY;
			strcpy( kc->country, value );
			break;
		case KC_INFO_STATE:
			if( strlen(value) > 31 )
				break;
			kc->flags |= KC_USESTATE;
			strcpy( kc->state, value );
			break;
		case KC_INFO_CITY:
			if( strlen(value) > 31 )
				break;
			kc->flags |= KC_USECITY;
			strcpy( kc->city, value );
			break;
		case KC_INFO_MOBILE:
			if( strlen(value) > 15 )
				break;
			kc->flags |= KC_USEMOBILE;
			strcpy( kc->mobile, value );
			break;
		case KC_INFO_EMAIL:
			if( strlen(value) > 63 )
				break;
			kc->flags |= KC_USEEMAIL;
			strcpy( kc->email, value );
			break;
		case KC_INFO_SS:
			if( strlen(value) > 127 )
				break;
			kc->flags |= KC_USESS;
			strcpy( kc->ss, value );
			break;
		case KC_INFO_GPS:
			if( strlen(value) > 15 )
				break;
			kc->flags |= KC_USEGPS;
			strcpy( kc->gps, value );
			break;
		case KC_INFO_SOCIAL1:
			if( strlen(value) > 31 )
				break;
			kc->flags |= KC_USESOCIAL1;
			strcpy( kc->social1, value );
			break;
		case KC_INFO_SOCIAL2:
			if( strlen(value) > 31 )
				break;
			kc->flags |= KC_USESOCIAL2;
			strcpy( kc->social2, value );
			break;
		case KC_INFO_SOCIAL3:
			if( strlen(value) > 31 )
				break;
			kc->flags |= KC_USESOCIAL3;
			strcpy( kc->social3, value );
			break;
		case KC_INFO_SOCIAL4:
			if( strlen(value) > 31 )
				break;
			kc->flags |= KC_USESOCIAL4;
			strcpy( kc->social4, value );
			break;
		case KC_INFO_SOCIAL5:
			if( strlen(value) > 31 )
				break;
			kc->flags |= KC_USESOCIAL5;
			strcpy( kc->social5, value );
			break;
		case KC_INFO_SOCIAL6:
			if( strlen(value) > 31 )
				break;
			kc->flags |= KC_USESOCIAL6;
			strcpy( kc->social6, value );
			break;
		case KC_INFO_SOCIAL7:
			if( strlen(value) > 31 )
				break;
			kc->flags |= KC_USESOCIAL7;
			strcpy( kc->social7, value );
			break;
		default :
			break;
	}
}


char* get_key_create_tv_pair( struct key_create *kc, kc_info_type type, char *value ){
	if( type == 0 || type >= KC_INFO_MAX || !value )
		return 0;
	switch( type ) {
		case KC_INFO_USERNAME:
			strcpy( value, kc->username );
			break;
		case KC_INFO_PASSWORD:
			strcpy( value, kc->password);
			break;
		case KC_INFO_DATE:
			strcpy( value, kc->date);
			break;
		case KC_INFO_TIME:
			strcpy( value, kc->time);
			break;
		case KC_INFO_ACCID:
			strcpy( value, kc->accountid);
			break;
		case KC_INFO_DOJ:
			strcpy( value, kc->doj);
			break;
		case KC_INFO_NAME:
			strcpy( value, kc->name);
			break;
		case KC_INFO_PINCODE:
			strcpy( value, kc->pincode);
			break;
		case KC_INFO_COUNTRY:
			strcpy( value, kc->country);
			break;
		case KC_INFO_STATE:
			strcpy( value, kc->state);
			break;
		case KC_INFO_CITY:
			strcpy( value, kc->city);
			break;
		case KC_INFO_MOBILE:
			strcpy( value, kc->mobile);
			break;
		case KC_INFO_EMAIL:
			strcpy( value, kc->email);
			break;
		case KC_INFO_SS:
			strcpy( value, kc->ss);
			break;
		case KC_INFO_GPS:
			strcpy( value, kc->gps);
			break;
		case KC_INFO_SOCIAL1:
			strcpy( value, kc->social1);
			break;
		case KC_INFO_SOCIAL2:
			strcpy( value, kc->social2);
			break;
		case KC_INFO_SOCIAL3:
			strcpy( value, kc->social3);
			break;
		case KC_INFO_SOCIAL4:
			strcpy( value, kc->social4);
			break;
		case KC_INFO_SOCIAL5:
			strcpy( value, kc->social5);
			break;
		case KC_INFO_SOCIAL6:
			strcpy( value, kc->social6);
			break;
		case KC_INFO_SOCIAL7:
			strcpy( value, kc->social7);
			break;
		default :
			break;
	}
	return value;
}


struct key_create *sakua_key_create_new(int algorithm){
	struct key_create *kc = ( struct key_create *) malloc( sizeof( struct key_create ) );
	if( kc ) {
		bzero( kc, sizeof( struct key_create ) );
		kc->seedpin = 2023;
		kc->pin = 2023;
		kc->algorithm = algorithm;
        	kc->dp_seed = domino_password_new();
        	kc->dp_seed->function_algo_setup( kc->dp_seed, kc->algorithm );
        	kc->dp_key = domino_password_new();
        	kc->dp_key->function_algo_setup( kc->dp_key, kc->algorithm );
		if( kc->algorithm == 1 || kc->algorithm == 3 ){
			kc->dp_seed->algo->incremental = 1;
			kc->dp_key->algo->incremental = 1;
		}
	}
	return kc;
}

int    sakua_key_create_setup ( struct key_create * kc ){
	unsigned long long int intresult = 0;
	unsigned long long int result    = 0;
	if ( kc ) {
		result = calculate_number_from_info ( kc, (unsigned int ) kc->flags, &intresult );  
		calculate_seedpin_from_result ( result , &kc->seedpin );
		calculate_pin_from_result     ( result , &kc->pin );
		calculate_randoms_from_result ( result , 16, kc->primes );
		return 0;
	}
	return 1;
}

void   sakua_key_create_setup_debug(struct key_create *kc ){
	printf(" Debug key create : %d, %d \n", kc->seedpin, kc->pin);
	printf(" Randoms : \n");
	for( int i = 0; i <16; i++ ){
		printf(" %d,", kc->primes[i]);
	}
	printf("\n");
}

void   sakua_key_create_delete( struct key_create * kc ){
	if( kc ) { 
		if( kc->dp_seed ) {
			free( kc->dp_seed );
			kc->dp_seed = 0;
		}
		if( kc->dp_key  ) { 
			free( kc->dp_key );
			kc->dp_key  = 0;
		}
		free(kc); 
	}
}

void   sakua_set_preseed ( struct key_create * kc, char *preseed ){
	if( preseed ){
		strcpy( kc->preseed, preseed );
	}	
}

void   sakua_set_seedpin ( struct key_create * kc, int seedpin ){
	kc->seedpin = seedpin;
}

char*  sakua_get_seed    ( struct key_create * kc ){
	kc->dp_seed->algo->function_set_pin( kc->dp_seed->algo, kc->seedpin );
	kc->dp_seed->function_set_gen_seed( kc->dp_seed, kc->preseed );
	if( kc->dp_seed->algo->incremental == 1 ){
		kc->dp_seed->algo->function_fastforward( kc->dp_seed->algo, kc->dp_seed->shuffled );
		kc->dp_seed->algo->incremental = 1;
		kc->dp_seed->algo->function_set_pin( kc->dp_seed->algo, kc->seedpin );
	}
	kc->dp_seed->function_gen_shuffled( kc->dp_seed );
	strcpy( kc->seed , kc->dp_seed->function_get_shuffled(kc->dp_seed) );
	printf( " Preseed=%s, Seed = %s \n", kc->preseed, kc->seed );
	return kc->seed;
}

void   sakua_set_pin     ( struct key_create * kc, int pin ){
	kc->pin = pin;
}

void   sakua_set_seed    ( struct key_create * kc, char *seed ){
	if( seed ){
		strcpy( kc->seed, seed );
	}	
}

char*  sakua_get_secure  ( struct key_create * kc ){
	kc->dp_key->algo->function_set_pin( kc->dp_key->algo, kc->pin );
	kc->dp_key->function_set_gen_seed( kc->dp_key, kc->seed );
	if( kc->dp_key->algo->incremental == 1 ){
		kc->dp_key->algo->function_fastforward( kc->dp_key->algo, kc->dp_key->shuffled );
		kc->dp_key->algo->incremental = 1;
		kc->dp_key->algo->function_set_pin( kc->dp_key->algo, kc->pin );
	}
	kc->dp_key->function_gen_shuffled( kc->dp_key );
	strcpy( kc->secure , kc->dp_key->function_get_shuffled(kc->dp_key) );
	printf( " Preseed=%s, Seed = %s \n", kc->preseed, kc->seed );
	return kc->secure;
}

char*  sakua_get_key     ( struct key_create * kc ) {
	kc->dp_key->function_set_n_activated( kc->dp_key, kc->n_sequence );
	kc->dp_key->function_set_activated( kc->dp_key, kc->sequence );
	return kc->dp_key->function_get_domino_key( kc->dp_key );
}



