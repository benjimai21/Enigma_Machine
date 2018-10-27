#include <iostream>
#include <fstream>
#include <cstdlib>
#include "plugboard.h"
#include "errors.h"
using namespace std;

//construction for plugboard that returns errors
plugboard::plugboard(const char* plug_config)
{
 
  ifstream infile(plug_config);

  if (infile.fail())
    {
      cerr << "Fail to open configuration file" << plug_config << endl;
      exit(ERROR_OPENING_CONFIGURATION_FILE);
    }
  
  i = 0;
 infile >> number[i];

 while(!infile.eof()) {

   if(infile.fail()) {
     cerr << "Non-numeric character in plugboard file plugboard.pb\n";
     exit(NON_NUMERIC_CHARACTER);
   }
  
    if(number[i] < 0 || number[i] > 25) {
      cerr << "Invalid Index in plugboard file plugboard.pb\n";
      exit(INVALID_INDEX);
    }

     i++;

     infile >> number[i];    
 }

 infile.close();

if((i%2) == 1 && i < 26) {
     cerr << "Incorrect number of parameters in plugboard file plugboard.pb\n";
     exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
 }

   if(i > 26) {
     cerr << "Incorrect number of parameters in plugboard file plugboard.pb\n";
     exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
   }

   for(int count = 0 ; count < i - 1 ; count++){
     for(int j = count + 1 ; j < i ; j++) {
       if(number[count] == number[j]) {
	 cerr << "Error: Impossible plugboard configuration (a number cannot appear twice).\n";
	 exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
       }
     }
   }
   
}

//function that encrypts a letter in the plugboard
char plugboard::encrypt(char in)
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


