#include <iostream>
#include <fstream>
#include <cstdlib>
#include "reflector.h"
#include "errors.h"
using namespace std;

//constructor for reflector that returns errors
reflector::reflector(const char* reflector_config)
{
 
  ifstream infile(reflector_config);

  if (infile.fail())
    {
      cerr << "Fail to open configuration file\n" << reflector_config << endl;
      exit(ERROR_OPENING_CONFIGURATION_FILE);
    }
  
  i = 0;
 infile >> number[i];

 while(!infile.eof()) {

   if(infile.fail()) {
     cerr << "Non-numeric character in reflector file reflector.rf\n";
     exit(NON_NUMERIC_CHARACTER);
   }
  
    if(number[i] < 0 || number[i] > 25) {
      cerr << "Invalid Index in reflector file reflector.rf\n";
      exit(INVALID_INDEX);
    }

     i++;

     infile >> number[i];
     
 }

 infile.close();
 
 if((i%2) == 1 && (i < 26 || i > 26)) {
   cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf\n";
   exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
 }

 if((i%2) == 0 && i < 26) {
   cerr << "Insufficient number of mappings in reflector file: reflector.rf\n";
   exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
 }

 if((i%2) == 0 && i > 26) {
   cerr << "Incorrect (even) number of parameters in reflector file reflector.rf\n";
   exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
 }

   for(int count = 0 ; count < i - 1 ; count++){
     for(int j = count + 1 ; j < i ; j++) {
       if(number[count] == number[j]) {
	 cerr << "Error: Invalid reflector mapping (a number cannot appear twice).\n";
	 exit(INVALID_REFLECTOR_MAPPING);
       }
     }
   }
   
  }

//function that encrypts a letter in the reflector
char reflector::encrypt(char in)
     {
       
       for(int j = 0 ; j < i ; j++) {
   
	    if(number[j] == in - 65) {
	      
	   if((j%2) == 0) 
	     return number[j+1] + 65;
	   else 
	     return number[j-1] + 65;
	 }
       }
       return in;
     }


