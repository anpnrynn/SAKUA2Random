#define _LARGEFILE64_SOURCE 
#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


int main(int argc , char *argv[]) {

if( argc < 6 ) {
	printf(" Usage : %s <filename> <searchlineindex> <stringoffset> <stringlength> <substringsearch>\n", argv[0] );
	return 0;
}

FILE *f;
printf(" Reading from file : %s \n", argv[1] );
f  = fopen(argv[1], "r");
int lineNumber = 0;

char fline[127];
fline[0] =0;
//fscanf( stdin, "%108s", fline );
fline[108]= 0;

int first = 0;
int readline = atoi ( argv[2] );
int offset = atoi( argv[3] );
int length = atoi( argv[4] );
int substring = atoi( argv[5] );
int submatches = 0;
int matches = 0;

printf(" Searching for string on line %d, at offset %d and of length %d \n", readline, offset, length );
printf(" Substring search %s \n", substring?"ON":"OFF" );

#define BUFSIZE 109 * 2048

char filebuf[BUFSIZE];
int nlines = 0;
while( ( nlines = fread( filebuf, 109, 2048, f ) ) > 0 ) {
int i = 0;
char *line = filebuf;
	if(  filebuf[nlines *109 -1 ] != '\n' )  {
		printf(" Structured read error \n");
		return 0;
	}
for(i=0;i<nlines;i++) {
	if( line[108] != '\n' )
	{
		printf(" EOL not found \n");
		return 0;
	}	

    line[108] = 0;
    lineNumber++;

    if (!feof(f)) {
    } else {
		printf("EOF\n");
		goto loopexit;
    }
    if( lineNumber % 1000000 == 0 ){
	    printf(" Searched %d lines  <<  %s  >> submatches=%d matches=%d\n", lineNumber, fline, submatches, matches );
		printf( " String = '%s' \n", line );
    }

    if( lineNumber == readline  ){
	    first = 1;
	    strcpy( fline, line );
	    fline[108] = 0;
		printf(" Line to scan for = '%s', %d , %d \n", fline, lineNumber, readline );

    } else if ( first ==  1 ) {
		int j = 0;
		while( j < 108-length ) {
    			if( strncmp ( &line[j] , &fline[offset], length ) == 0 ){
	    			printf(" Matching string found at line : %d , %d\n", lineNumber, offset+j);
				printf(" Matching string : %s \n", line );
				//fclose(f);
				//return 0;
				submatches++;
    			} 
			j++;
		}
	    	if( j == 0 ){
    			if( strncmp ( line , fline, length ) == 0 ){
	    			printf(" Matching string found at line : %d , %d\n", lineNumber, offset+j);
				printf(" Matching string = %s \n", line );
				//fclose(f);
				//return 0;
				matches++;
    			} 
			j++;
		}

	}
	line = filebuf + (i+1) * 109;
	}
}

loopexit:


printf(" Looping from begining \n");
fseek( f, SEEK_SET, 0 );
int ln = lineNumber;
lineNumber=0;
int n = 0;
while( ( nlines = fread( filebuf, 109, 2048, f ) ) > 0 ) {
	if(  filebuf[nlines *109 -1 ] != '\n' )  {
		printf(" Structured read error \n");
		return 0;
	}
int i = 0;
char *line = filebuf;
for(i=0;i<nlines && n<readline; i++) {
	if( line[108] != '\n' )
	{
		printf(" EOL not found \n");
		return 0;
	}	
    line[108] = 0;
	ln++;
    lineNumber++;

    if (!feof(f)) {
    } else {
		goto loopexit1;
    }

    if( ln % 1000000 == 0 ){
	    printf(" Searched %d lines  <<  %s  >> submatches=%d matches=%d\n", ln, fline, submatches, matches );
		printf( " String = '%s' \n", line );
    }

    if( lineNumber == readline  ){
	    first = 1;
	    strcpy( fline, line );
	    fline[108] = 0;
		goto loopexit1;
    } else {
		int j = 0;
		while( j < 108-length ) {
    			if( strncmp ( &line[j] , &fline[offset], length ) == 0 ){
	    			printf(" Matching string found at line : %d , %d\n", lineNumber, offset+j);
				printf(" Matching string : %s \n", line );
				//fclose(f);
				//return 0;
				submatches++;
    			} 
			j++;
		}
	    	if( j == 0 ){
    			if( strncmp ( line , fline, length ) == 0 ){
	    			printf(" Matching string found at line : %d , %d\n", lineNumber, offset+j);
				printf(" Matching string = %s \n", line );
				//fclose(f);
				//return 0;
				matches++;
    			} 
			j++;
		}
	    	
	}
	n++;
	line = filebuf + (i+1)*109;
}
}

loopexit1:

printf(" No matching string found \n");

fclose(f);

return(0);
}
