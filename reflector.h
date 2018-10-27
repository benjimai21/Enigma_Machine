#ifndef REFLECTOR_H
#define REFLECTOR_H

class reflector
{
 private:
  int number[50]; // mapping of reflector
  int i;
 public:
  reflector(const char* reflector_config);
  // function to encode a character
  char encrypt(char in);
};
#endif
