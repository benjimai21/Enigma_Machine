#ifndef ROTOR_H
#define ROTOR_H

class rotor
{
 private:
  int rotor_value[26];
  int normal[26];
  int notch[26];
  int nb_notch;
 public:
  void config(const char* rotor_config);
  rotor();
  char map_in(const char letter);
  char map_out(const char letter);
  void rotate();
  void rotate(int position);
  bool hit_notch();
};
#endif
