#include <iostream>
#include <fstream>
#include <cstdlib>
#include "rotor.h"
#include "errors.h"
using namespace std;

// Default constructor for the rotor class
rotor::rotor()
{}

//function that returns errors for rotors
void rotor::config(const char* rotor_config)
{
 
  ifstream infile(rotor_config);

  if (infile.fail())
    {
      cerr << "Fail to open configuration file" << rotor_config << endl;
      exit(ERROR_OPENING_CONFIGURATION_FILE);
    }

  // Set normal count
  for(int j = 0 ; j < 26 ; j++)
    normal[j] = j;
  
  
  //Errors for the rotor values part
  int i = 0;
  
  infile >> rotor_value[i];

  while(i < 26) {

    if(infile.eof()) {
      cerr << "Not all inputs mapped in rotor file: rotor.rot\n";
      exit(INVALID_ROTOR_MAPPING);
    }
   
    if(infile.fail()) {
       cerr << "Non-numeric character for mapping in rotor file rotor.rot\n";
       exit(NON_NUMERIC_CHARACTER);
    }

    if(rotor_value[i] < 0 || rotor_value[i] > 25) {
      cerr << "Invalid Index in rotor file: rotor.rot\n";
      exit(INVALID_INDEX);
    }
   
     i++;

     if(i == 26)
       break;

     infile >> rotor_value[i];
  }

  
for(int count = 0 ; count < 26 ; count++){
     for(int j = count + 1 ; j < 26 ; j++) {
       if(rotor_value[count] == rotor_value[j]) {
	 cerr << "Invalid mapping of input " << j << " to output " << rotor_value[j] << " (output " << rotor_value[j] << " is already mapped to from input " << count << ")\n";
	 exit(INVALID_ROTOR_MAPPING);
       }
     }   
 }

 
// Errors for the notch part
 nb_notch = 0;

  infile >> notch[nb_notch];

  while(!infile.eof()) {
    
    if(infile.fail()) {
      cerr << "Non-numeric character for mapping in rotor file rotor.rot\n";
      exit(NON_NUMERIC_CHARACTER);
    }

    if(notch[nb_notch] < 0 || notch[nb_notch] > 25) {
      cerr << "Invalid Index in file rotor: rot\n";
      exit(INVALID_INDEX);
    }
  
    nb_notch++;

    infile >> notch[nb_notch];
  }

  infile.close();
    
}

//function that encrypts letter in rotor from right to left
char rotor::map_in(const char letter)
{
  int number_letter = letter - 65;

  for(int i = 0 ; i < 26 ; i++) {
    if(rotor_value[normal[number_letter]] == normal[i])
      return i + 65;
  }
  cerr << "This error should not happen";
  exit(5);

}

char rotor::map_out(const char letter)
{
  int number_letter = letter - 65;
  int temp;
  for(int i = 0 ; i < 26 ; i++) {
    if(rotor_value[i] == normal[number_letter]) {
       temp = i;
       break;    
    }
   
  }
  
  for(int i = 0 ; i < 26 ; i++) {
    if(normal[i] == temp)
      return i + 65;
  }
  cerr << "This error should not happen";
  exit(5);
  
}
 

//function that that rotates the rotors one time
void rotor::rotate()
{  

  int stock = normal[0];
  for(int i = 0 ; i < 25 ; i++) {
      normal[i] = normal[i + 1];
  }
  normal[25] = stock;
 
}

//function that rotates the rotors in the initial setting
void rotor::rotate(int position)
{

  for(int j = 0 ; j < position ; j++) {
    this->rotate();
  }
}

//function that specifies when a rotor hits a notch
bool rotor::hit_notch()
{
  for(int j = 0 ; j < nb_notch ; j++) {
    if(normal[0] == notch[j]) 
      return true;
  }
  return false;
}
