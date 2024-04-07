#copyright Anoop Kumar Narayanan 2023 anoop.kumar.narayanan@gmail.com
all:build buildshared tests

build:sakua-dominopasswordgen1.o sakua-dominopasswordgen1_1.o sakua-dominopasswordgen2.o sakua-dominopasswordgen2_1.o sakua-dominopassword.o sakua-keycreate.o

buildshared:libsakua-dominopassword.so libsakua-keycreate.so

FLAGS=-I./ -g3 -fPIC
#LDFLAGS=-L./ -lsakua-dominopassword 

cleanbuild: clean build buildshared tests

clean:
	rm -f *.so *.o test testkeygen testkeycreate

sakua-dominopasswordgen1_1.o:sakua-dominopasswordgen1_1.c sakua-dominopasswordgen1_1.h
	gcc sakua-dominopasswordgen1_1.c -c -o sakua-dominopasswordgen1_1.o $(FLAGS)

sakua-dominopasswordgen1.o:sakua-dominopasswordgen1.c  sakua-dominopasswordgen1.h
	gcc sakua-dominopasswordgen1.c -c -o sakua-dominopasswordgen1.o $(FLAGS)

sakua-dominopasswordgen2.o:sakua-dominopasswordgen2.c sakua-dominopasswordgen2.h
	gcc sakua-dominopasswordgen2.c -c -o sakua-dominopasswordgen2.o $(FLAGS)

sakua-dominopasswordgen2_1.o:sakua-dominopasswordgen2_1.c sakua-dominopasswordgen2_1.h  
	gcc sakua-dominopasswordgen2_1.c -c -o sakua-dominopasswordgen2_1.o $(FLAGS)

sakua-dominopassword.o:sakua-dominopassword.c sakua-dominopassword.h  
	gcc sakua-dominopassword.c -c -o sakua-dominopassword.o $(FLAGS)
	
libsakua-dominopassword.so:sakua-dominopasswordgen1.o sakua-dominopasswordgen1_1.o sakua-dominopasswordgen2.o sakua-dominopasswordgen2_1.o sakua-dominopassword.o
	gcc -shared sakua-dominopasswordgen1.o sakua-dominopasswordgen1_1.o sakua-dominopasswordgen2.o sakua-dominopasswordgen2_1.o sakua-dominopassword.o -o libsakua-dominopassword.so  -g3 -fPIC 

sakua-keycreate.o:sakua-keycreate.c sakua-keycreate.h  
	gcc sakua-keycreate.c -c -o sakua-keycreate.o $(FLAGS)
	
libsakua-keycreate.so:libsakua-dominopassword.so
	gcc -shared sakua-keycreate.o -o libsakua-keycreate.so libsakua-dominopassword.so $(LDFLAGS) -g3 -fPIC

tests:test testkeygen testkeycreate

test:test.c
	gcc test.c -o test *.o $(FLAGS) $(LDFLAGS)
	./test

testkeygen:testkeygen.c
	gcc testkeygen.c -o testkeygen *.o $(FLAGS) $(LDFLAGS)
	./testkeygen

testkeycreate:testkeycreate.c
	gcc testkeycreate.c -o testkeycreate *.o $(FLAGS) $(LDFLAGS)
	./testkeycreate
