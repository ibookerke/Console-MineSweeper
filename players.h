#ifndef PLAYERS_H
#define PLAYERS_H
#include<iostream>
#include<string>
class plr{
  public:
    plr(std::string name);
    int get_points();
    void set_points(int init, int after);
    std::string get_nickname();
  private:
    int points;
    std::string nickname;
};
#endif