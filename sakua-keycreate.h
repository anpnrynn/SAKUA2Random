//Copyright Anoop Kumar Narayanan 2023 anoop.kumar.narayanan@gmail.com
#ifndef SAKUA_KEYCREATE
#define SAKUA_KEYCREATE

#define KEY_CREATE_VERSION 1


#include "sakua-dominopasswordgen1.h"
#include "sakua-dominopasswordgen1_1.h"
#include "sakua-dominopasswordgen2.h"
#include "sakua-dominopasswordgen2_1.h"
#include "sakua-dominopassword.h"

/*
 * Key create permanently activated options
 * KC_USERNAME
 * KC_PASSWORD
 * KC_DATE
 * KC_TIME      // with granularity of 10 minutes
 * KC_ACCOUNTID // set to zero if not present
 * KC_DOJ       // Date of joining a service
 */

typedef enum _keycreate_options {
	KC_USENAME = 0x01,    // Full name
	KC_USEPINCODE  = 0x02, 
	KC_USECOUNTRY  = 0x04,
	KC_USESTATE    = 0x08,
	KC_USECITY     = 0x10,
	KC_USEMOBILE   = 0x20, 
	KC_USEEMAIL    = 0x40,
	KC_USESS       = 0x80,   // some string like transaction id, DOB, Recovery Answer, ...etc or combination/think of it as a query / response field could be ';' separated
	KC_USEGPS      = 0x100,  // Use GPS location
	KC_USESOCIAL1  = 0x200,
	KC_USESOCIAL2  = 0x400,
	KC_USESOCIAL3  = 0x800,
	KC_USESOCIAL4  = 0x1000,
	KC_USESOCIAL5  = 0x2000,
	KC_USESOCIAL6  = 0x4000,
	KC_USESOCIAL7  = 0x8000,
}keycreate_options;

typedef enum _kc_info_type {
	KC_INFO_USERNAME   = 1,    // Full name
	KC_INFO_PASSWORD   = 2,    // Full name
	KC_INFO_DATE   = 3,    // Full name
	KC_INFO_TIME   = 4,    // Full name
	KC_INFO_ACCID  = 5,    // Full name
	KC_INFO_DOJ    = 6,    // Full name
	KC_INFO_NAME     = 7,    // Full name
	KC_INFO_PINCODE  = 8, 
	KC_INFO_COUNTRY  = 9,
	KC_INFO_STATE    = 10,
	KC_INFO_CITY     = 11,
	KC_INFO_MOBILE   = 12, 
	KC_INFO_EMAIL    = 13,
	KC_INFO_SS       = 14,   // some string like transaction id
	KC_INFO_GPS      = 15,  // Use GPS location
	KC_INFO_SOCIAL1  = 16,
	KC_INFO_SOCIAL2  = 17,
	KC_INFO_SOCIAL3  = 18,
	KC_INFO_SOCIAL4  = 19,
	KC_INFO_SOCIAL5  = 20,
	KC_INFO_SOCIAL6  = 21,
	KC_INFO_SOCIAL7  = 22,
	KC_INFO_MAX    
}kc_info_type;




struct key_create {
	char username  [128];
	char password  [128];
	char date      [16];
	char time      [16];
	char accountid [24];
	char doj       [16]; //client side epoch timestamp without timezone
	char name      [128];
	char pincode   [8];
	char country   [32]; //Abbreviations where applicable
	char state     [32];
	char city      [32];
	char mobile    [16];
	char email     [64];
	char ss        [128];
	char gps       [16];
	char social1   [32];
	char social2   [32];
	char social3   [32];
	char social4   [32];
	char social5   [32];
	char social6   [32];
	char social7   [32];

	unsigned long int flags;

	struct domino_password *dp_seed;
	struct domino_password *dp_key;

	int  algorithm;
	int  primes [16];
	int  seedpin;
	char preseed[128];
	int  pin;
    char seed   [128];
    char secure [128];
	int  n_sequence;
	int  sequence [108];
	void *user_data;
};

void  set_key_create_tv_pair( struct key_create *kc, kc_info_type type, char *value);
char* get_key_create_tv_pair( struct key_create *kc, kc_info_type type, char *value);


struct key_create *sakua_key_create_new(int algorithm);
int    sakua_key_create_setup ( struct key_create * );
void   sakua_key_create_setup_debug(struct key_create * );
void   sakua_key_create_delete( struct key_create * );
void   sakua_set_preseed ( struct key_create *, char *preseed );
void   sakua_set_seedpin ( struct key_create *, int seedpin );
char*  sakua_get_seed    ( struct key_create * );
void   sakua_set_seed    ( struct key_create *, char *seed );
void   sakua_set_pin     ( struct key_create *, int pin);
char*  sakua_get_secure  ( struct key_create * );
char*  sakua_get_key     ( struct key_create * );

#endif
