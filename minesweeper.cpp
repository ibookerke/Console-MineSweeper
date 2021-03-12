#include <iostream>

#include <string>

#include <cstdlib>//чтобы юзать rand()

#include <time.h>//чтобы юзать srand()

#include "players.h" 
//forward declaration in order to be able to call this function in empty_checker function below
void multi_opener(char true_grid[][11], char fake_grid[][9], int y, int x);
//gives a fake grid value from true grid
char opener(char true_grid[][11], int y, int x) {
  y++;
  x++;
  return true_grid[y][x];
}
//calculate number of empty squares
int get_empty_num(char fake_grid[][9]) {
  int empty_num = 0;
  int x = 0;
  int y = 0;
  do{
    do{
      if(fake_grid[y][x] == 'O'){
        empty_num++;
      }
      x++;
    }while(x < 9);
    x = 0;
    y++;
  }while(y < 9);
  return empty_num;
}
//fill the squares with mines and numbers
void true_filler(char true_grid[][11], int bomb_num){
  int x, y, num;
  for(int t = 0; t < bomb_num;){
    //take random values
    srand(time(0));
    x = rand() % 9;
    y = rand() % 9;
    if(true_grid[y + 1][x + 1] == '-'){
      true_grid[y + 1][x + 1] = '@';
      t++;
    }
  }
  //giving numbers to neibhours of mines_num
  for (y = 1; y < 10; y++) {
    for (int x = 1; x < 10; x++) {
      num = 0;
      if (true_grid[y][x] == '-') {
        //using ternary operations
        num = true_grid[y + 1][x + 1] == '@' ? num += 1 : num += 0;
        num = true_grid[y + 1][x] == '@' ? num += 1 : num += 0;
        num = true_grid[y + 1][x - 1] == '@' ? num += 1 : num += 0;
        num = true_grid[y][x + 1] == '@' ? num += 1 : num += 0;
        num = true_grid[y][x - 1] == '@' ? num += 1 : num += 0;
        num = true_grid[y - 1][x + 1] == '@' ? num += 1 : num += 0;
        num = true_grid[y - 1][x] == '@' ? num += 1 : num += 0;
        num = true_grid[y - 1][x - 1] == '@' ? num += 1 : num += 0;
        true_grid[y][x]= num + '0';
        if(true_grid[y][x] == '0'){
          true_grid[y][x] = '-';
        }
      }
    }
  }
}
//checks if the surrounding squares are empty or not
void empty_checker(char true_grid[][11], char fake_grid[][9], int y, int x){
  if(fake_grid[y][x] == 'O'){
    fake_grid[y][x] = opener(true_grid, y, x);
    if(fake_grid[y][x] == '-'){
      multi_opener(true_grid, fake_grid, y, x);
    }
  }
}
//to open additional empty squares in cases of opening one of them
void multi_opener(char true_grid[][11], char fake_grid[][9], int y, int x) {
  if(y > 0){
    empty_checker(true_grid, fake_grid, y - 1, x);
    if(x > 0){
      empty_checker(true_grid, fake_grid, y - 1, x - 1);
    }
    if(x < 8){
      empty_checker(true_grid, fake_grid, y - 1, x + 1);
    }
  }
  if(y < 8){
    empty_checker(true_grid, fake_grid, y + 1, x);
    if(x > 0){
      empty_checker(true_grid, fake_grid, y + 1, x - 1);
    }
    if(x < 8){
      empty_checker(true_grid, fake_grid, y + 1, x + 1);
    }
  }
  if(x > 0){
    empty_checker(true_grid, fake_grid, y, x - 1);
  }
  if(x < 8){
    empty_checker(true_grid, fake_grid, y, x + 1);
  }
}
//prints the fake grid
void show_grid(char fake_grid[][9]) {
  int a, b;
  //header
  std::cout << std::endl << "  ";
  for (a = 1; a < 10; a++) {
    std::cout << " " << a;
  }
  std:: cout << std::endl;
  std:: cout << "   ";
  for(b = 1; b < 18; b++){
    std::cout << "—";
  }
  //body
  std:: cout << std:: endl;
  a = 0;
  b = 0;
  do{
    std:: cout << a + 1 << "¦";
    do{
      std:: cout << " " << fake_grid[a][b];
      b++;
    }while(b < 9);
    b = 0;
    std::cout << " ¦" << a + 1 << std::endl;
    a++;
  }while(a < 9);
  //footer
  std:: cout << "   ";
  for(a = 1; a < 18; a++){
    std::cout << "—";
  }
  std::cout << std::endl << "  ";
  for (b = 1; b < 10; b++) {
    std::cout << " " << b;
  }
  std::cout << std::endl << std::endl;
}

int main() {
  bool is_playing = true;
  char want;
  while(is_playing){
    int mines_num, x, y, initial, after;
    bool is_mined, is_explode, is_first, is_multi;
    is_first = true;
    is_mined = false;
    is_explode = false;
    is_multi = false;
    char mode, true_grid[11][11], fake_grid[9][9];
    //select mode
    while (1) {
      std::cout << "Choose game mode" << std::endl;
      std::cout << "S - stands for singleplayer" << std::endl;
      std::cout << "M - stands for multiplayer" << std::endl;
      std::cin >> mode;
      if (mode == 'S' || mode == 'M') {
        break;
      }
    }
    if(mode == 'M'){
      is_multi = true;
    }
    //ussing objects to store names and calculate points
    std::string name;
    if (is_multi) {
      std::cout << "Player1, what's your name?" << std::endl;
      std::cin >> name;
    }
    //another one
    plr plr1(name);
    if(is_multi){
      std::cout << "Player2, what's your name?" << std::endl;
      std::cin >> name;
    }
    plr plr2(name);
    //recieve the number of mines
    std::cout << "How many mines do you want?" << std::endl;
    std::cin >> mines_num;
    //fill true grid
    x = 0;
    y = 0;
    do{
      do{
        if(y == 0 || y == 10){
          true_grid[y][x] = 'H';
        }
        else if(x == 0 || x == 10){
          true_grid[y][x] = 'H';
        }
        else{
          true_grid[y][x] = '-';
        }
        x++;
      }while(x < 11);
      x = 0;
      y++;
    }while(y < 11);
    //fill fake grid
    x = 0;
    y = 0;
    do{
      do{
        fake_grid[y][x] = 'O';
        x++;
      }while(x < 9);
      x = 0;
      y++;
    }while(y < 9);

    show_grid(fake_grid);
    //game started
    while (1) {
      //count initial number of empty squares
      initial = get_empty_num(fake_grid);
      if (is_multi) {
        //get the player number 
        if (is_first == true) {
          std::cout << "Your turn, " << plr1.get_nickname() << std::endl;
        } else {
          std::cout << "Your turn, " << plr2.get_nickname() << std::endl;
        }
      }
      std::cout << "Make your move (row[1-9] column[1-9])" << std::endl;
      std::cin >> y >> x;
      if (fake_grid[y - 1][x - 1] != 'O' || y < 1 || x < 1 || y > 9 || x > 9) {
        std::cout << "ERROR: wrong values - try again" << std::endl;
        continue;
      }
      //fill true grid with mines if it haven't been done
      if (is_mined == false) {
        is_mined = true;
        true_filler(true_grid, mines_num);
      }

      //open a square
      fake_grid[y - 1][x - 1] = opener(true_grid, y - 1, x - 1);
      //open multiple squares if opened square was empty
      if (fake_grid[y - 1][x - 1] == '-') {
        multi_opener(true_grid, fake_grid, y - 1, x - 1);
      }
      //grid visualisation
      std::cout << std::endl;
      show_grid(fake_grid);
      //count empty squares after move
      after = get_empty_num(fake_grid);
      //adding points to players
      if(is_multi){
        if (is_first == true) {
          is_first = false;
          plr1.set_points(after, initial);
        } else {
          is_first = true;
          plr2.set_points(after, initial);
        }
      }
      //when the game is over
      if (fake_grid[y - 1][x - 1] == '@') {
        is_explode = true;
        break;
      }
      if (after == mines_num) {
        break;
      }
    }
    //if we are out of empty squares
    if (is_explode == false) {
      if (is_multi) {
        std::cout << plr1.get_nickname() << " - " << plr1.get_points() << " points" <<  std::endl;
        std::cout << plr2.get_nickname() << " - " << plr2.get_points() << " points" << std::endl;
        if(plr1.get_points() == plr2.get_points()){
          std::cout << "Tie" << std:: endl;
        }
        else if (plr1.get_points() > plr2.get_points()) {
          std::cout << plr1.get_nickname() << " is winner!\n" << plr2.get_nickname() <<" is looser";
        } else {
          std::cout << plr2.get_nickname() << " is winner!\n" << plr1.get_nickname() <<" is looser";
        }
      } else {
        std::cout << "Congratulations!!! \nVictory" << std::endl;
      }
    }
    //if mine explodes
    else {
      if (is_multi == false) {
        std::cout << "you have died from mine explosion \nGame Over" << std::endl;
      }
      else {
        if (is_first) {
          std::cout << plr1.get_nickname() << " won! \n" << plr2.get_nickname() << " died from mine explosion";
        } 
        else {
          std::cout << plr2.get_nickname() << " won! \n" << plr1.get_nickname() << " died from mine explosion";
        }
      }
    }
    std::cout << "Want to play another game?" << std::endl;
    std::cout << "'Y' - for yes/'N' - for no" << std::endl;
    std:: cin >> want;
    if(want == 'N'){
      is_playing = false;
    }
  }
  
}
