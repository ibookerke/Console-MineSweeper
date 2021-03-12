#include "players.h"
plr::plr(std::string str){//coonstruct
  this->points = 0;
  this->nickname = str;
}
void plr::set_points(int init, int after){
  int result = after - init;
  this->points += result; 
}
int plr::get_points(){
  return this->points;
}
std::string plr::get_nickname(){
  return this->nickname;
}