#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include"errors.h" 
#include"plugboard.h"
#include"rotor.h"  
#include"reflector.h"

const int MAX = 20;

void set_position(char argv[], int position[MAX], int nb_rotors);

using namespace std;


int main(int argc, char** argv)
{

  if(argc < 3) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?\n";
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }
  
  plugboard plug(argv[1]); 
  reflector reflect(argv[2]);
  
  int position[MAX]; 
  int no_of_rotors;
  no_of_rotors = argc - 4;
  char letter;
 
   //Case where number of rotors is greater than 0
   if(no_of_rotors > 0) {
   
   rotor* rot = new rotor[no_of_rotors];

   for(int i = 0 ; i < no_of_rotors ; i++) 
      rot[i].config(argv[3+i]);
   
   
  set_position(argv[3 + no_of_rotors], position, no_of_rotors);
  
   for(int i = 0 ; i < no_of_rotors ; i++)
     rot[i].rotate(position[i]);
   
   //encryption starts
  
   while(cin >> ws >> letter) {

     if(letter < 65 || letter > 90) {
       cerr << letter << " is not a valid input character (input characters must be upper case letters A-Z)!\n";
       return INVALID_INPUT_CHARACTER;
     }
     
     letter = plug.encrypt(letter);                        // letter enters plugboard
    
     rot[no_of_rotors - 1].rotate();                      //first rotor rotates before letter enters it 

     for(int i = 0 ; i < no_of_rotors - 1; i++) {         //if first rotor hits a notch, rotor to its left rotates 
         if(rot[no_of_rotors - i - 1].hit_notch())
            rot[no_of_rotors - i - 2].rotate();
  }
     
      
     for(int i = no_of_rotors ; i > 0 ; i--)            //letter is mapped through all rotors from right to left
	letter = rot[i - 1].map_in(letter);	  
      
     letter = reflect.encrypt(letter);                  //letter enters reflector
      
     for(int i = 0 ; i < no_of_rotors ; i++)           //letter is mapped through all rotors from left to right   
	letter = rot[i].map_out(letter);
      
     letter = plug.encrypt(letter);                    //letter enters plugboard again
		
     cout << letter;                                   //final letter output
   }
   }
   
   //Case with no rotors
   
   else if(no_of_rotors < 0) {
     
   // encryption starts
     
     while(cin >> ws >> letter) {

         if(letter < 65 || letter > 90) {
	   cerr << letter << " is not a valid input character (input characters must be upper case letters A-Z)!\n";
       return INVALID_INPUT_CHARACTER;
     }
	 
       letter = plug.encrypt(letter);
      
       letter = reflect.encrypt(letter);

       letter = plug.encrypt(letter);
       
     cout << letter; 
  } 
    
   }
   
	
  return NO_ERROR;
      
}

//function to return errors on the position files and get the initital positions for the rotors
void set_position(char argv[], int position[MAX], int nb_rotors)
{
  ifstream infile;

  infile.open(argv);
  int i = 0;
  
  infile >> position[i];
    
  while(!infile.eof()) {
    if(infile.fail()) {
   
      cerr << "Non-numeric character in rotor positions file rotor.pos\n";
      exit(4);
    }
  
    if(position[i] < 0 || position[i] > 25) {
      cerr << "Error: Invalid Index\n";
      exit(3);
    }

    i++;
    
    infile >> position[i];
  }

  if(i < nb_rotors) {
    cerr << "No starting position for rotor " << i << " in rotor position file: rotor.pos\n";
    exit(8);
    } 
}

