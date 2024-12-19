# SAKUA2 Random String Generator (Based on dominopassword)

Updated LowRes_DominoPassword.apk today (19/04/2024)


### Please Read how it works file. (Original working theory of SAKUA2, a secure public key alternative with MITM prevention)
### Please use the sakua2random.c file for testing random number generation and testing the library.


`make`   
`make -f Makefile.sakua2random`   
`export LD_LIBRARY_PATH=./`  


SAKUA
-----
Shared Access Key User Authentication
SAKUA is similar to SAKA but the User first registers online using SSL/TLS and then the encryption layer is provided by SAKUA.



Please Also See, Original repository:
=====================================
https://github.com/anpnrynn/SAKUA2   
SAKUA2 original algo will remain there without any modifications.   
https://github.com/anpnrynn/dominopassword repository was removed by me as it was conflicting with an IBM technology name.  



DominoPassword C implementation for:
------------------------------------
1. GEN1   - Last update in 2023
2. GEN1_1 - Last update in 07-Apr-2024 - Reduction of conflicts (Heavily modified from original SAKUA2 algo) 
3. GEN2   - Last update in Jan-2023 
4. GEN2_1 - Last update in 07-Apr-2024 - Reduction of conflicts (Heavily modified from original SAKUA2 algo) 


    
TO DO:
------
Actual SAKUA and SAKA implemetation. SAKUA and SAKA are a replacement for public key alogrithm.

   
   
Random Number Generation and Validation programs   
================================================    
sakua2random   
=============   
`Usage: ./sakua2random_make <algo> <Start of pin> <Number of strings> <filename>`     
	Algo, 0 - 1_0, 1 - 1_1, 2 - 2_0, 3 - 2_1    

 ./sakua2random_make 1 1 10000000  random1.txt   
 ./sakua2random_make 1 14 10000000 random14.txt   

These two commands will generate different set of random files. Use either odd or even number, every subsequent odd and even number will generate same similar set minus the first random number.   
Ex: Use pins 1, 3, 5, 7, 9 or 2. 4. 6. 8. 10 ... etc   

As of now tested upto 1 billion random strings with a single pin, seems to generate unique random strings.   
The file size reaches about 100GB. This was the command.    
./sakua2random_make.exe 3 5 1000000000 randomstrings.txt   

   
searchline    
==========    
`Usage : ./searchline <filename> <searchlineindex> <stringoffset> <stringlength> <substringsearch>`    
./searchline random1.txt 34 0 16 1   


   
Domino Password : Password generation APK
=========================================   
The APK / android application comes with no waranties, its for generating passwords for website / applications. The Initial purpose for which I wrote this application. It doesn't store the pattern / passwords only the website / applicaiton name and pin , you will have to remember the pattern.    
Uninstalling the app and reinstalling the app causes the saved pins to be deleted, use caution, use a backup.   

Use dominopassword.apk or LowRes_dominopassword.apk(low res, FHD phones).    
DominoPassword algorithm uses GEN2 (Password gen algo)   
SAKUA2 is supposed to use GEN2_1 or GEN1_1 (Crypto string gen algo) 

Example: 

Steps:
 • Set the Pin     
 • Press Generate     
 • Create three patterns (uses back and next as required)     
 • You are left with a secure password for a website.     
 • Keep either the pin or password same, and repeat process for other websites.     

![Domino Password Generation Image ](https://github.com/anpnrynn/SAKUA2Random/blob/main/DominoPassword.png) 
 
![Domino Password Generation Image ](https://github.com/anpnrynn/SAKUA2Random/blob/main/DominoPassword-2.png)  

 You can download the html or use the apk just for testing out Domino Password( not to be confused with IBM product).    

 It makes use of a simple algo to create crypto secure 108char long string, which is used in DominoPassword to generate passwords based on pin and pattern.    

 36*3 = 108    
Each of the pattern matrix is 6x6 matrix.    
 And the pattern looks like a domino hence the name.    
   
Third Party Secure Key Communication
====================================

There are three parties involved.    
• SAKUA2Random String generated site (The third party)   
• The End-User   
• The Website or Service Provider the End-User wishes to work with.   

The End-User installs an app from the random strings generator site, the app downloads 
150Million+ 108 character long random strings file per device.    

The SAKUA2Random Strings Site (keyserver) will create one 150Million+ 108 character 
long random strings file, which is then shuffled around keeping the strings intact, but 
the order changed to generate around 8 Billion+ combinations, which are used by 
devices belonging to other users. Each user registers the (n)sites and usernames with 
the random strings file.   

The End-User accesses the site, Let’s say Gmail.com (server). Gmail.com uses one of 
the daily strings (random search string) and sends the string along with a list of indices.
These indices represent the offset from the end location of the random search string. 
The values together in these indices represent the shared key. Which could optionally 
be mixed in with the password to create an even more secure shared key.    

The End-User’s app then uses these indices which it receives over TCP to calculate the 
shared key, from its version of the random strings file, the indices are at an offset from 
the end of the search string which is present in all 8 billion+ versions of the file, 
including the one with Gmail.   

The End-User then sends his username and uses the encrypted key to create a secure 
connection.      

At the server-end which is Gmail in this case, it contacts SAKUA2Random Strings Site
(keyserver) sends the username and retrieves the shared key. Which is then used to 
decrypt the data from the End-User and vice versa.
The random strings file can be regenerated every week or so to improve the security of 
the End-User / Server.   

Public Key Method
=================
Create a domino password using pin and pattern, then try to locate another pin and pattern such that the first level of SHA256 or SHA512 yield the same message digest. So, now, one of the key can be private and the other can be public. The algorithm can be different but i am pretty sure that this method can be used to find public private key pairs.

Each of the public/private key are 2 pins and 1 pattern. 

There are 2 follow up algorithms which is non reversible that is required to do the actual encryption and decryption, such that what is encrypted by public key can only be decrypted by private key. (Work in progress).

Please note locating such a key is extremely hard. Known pairs of Messages should be avoided.

Another approach could be number co-relation method. Co-relate two numbers such that the algorithms are different. 

HISTORY
=======
I researched, designed and wrote this from scratch. Initially I wrote the DominoPasswordGen2.html from scratch for generating password and storing minimal information on an electronic device, only pins, and not patterns or passwords. The idea was to remember pins and a few patterns to generate different passwords for several websites. This was done because my account was constantly being hacked using several means including but not limited to MITM.   


DISCLAIMER
==========
If anyone claims otherwise, and say they have done it, they are either lying or cheating. If the person claiming this is affiliated with an University, you might need to suspend the persom from the University.  
