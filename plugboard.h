#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class plugboard
{
 private:
  int number[26]; // mapping of plugboard
  int i;
 public:
  plugboard(const char* plug_config);
 // function to encode a character
  char encrypt(char in);
};
#endif
