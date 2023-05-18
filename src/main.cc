#include <iostream>
#include <curses.h>
#include <string>
#include <set>
#include <utility>
#include <valarray>
#include <vector>
#include <stdlib.h>     
#include <time.h>      
#include "draw.h"
#include "field_2d.h"
#include "field_3d.h"
#include "objects.h"
#include "utils.h"

void Print(int field_size, int cs, int x_border, int y_border, std::map<char, int> form, Field3D& field_3d) {
  Field2D field(field_size-2);
  std::vector<std::pair<Position3D, Position3D>> cube_positions_a = {
    {{cs, cs,0}, {0,cs,0}}, {{cs,cs,0}, {cs,0,0}},  // first square 2
    {{cs, cs,0}, {cs,cs,cs}}, 
  };
  field.BuildCube(cube_positions_a, false);
  std::vector<std::pair<Position3D, Position3D>> cube_positions_b = {
    {{0,0,0}, {0,cs,0}}, {{0,0,0}, {cs,0,0}}, // first square 1
    {{0,0,cs}, {0,cs,cs}}, {{0,0,cs}, {cs,0,cs}}, // second square 1
    {{0,0,0}, {0,0,cs}}, {{0,cs,0}, {0,cs,cs}}, 
    {{cs, cs,cs}, {0,cs,cs}}, {{cs, 0, 0}, {cs, 0, cs}},
    {{cs,cs,cs}, {cs,0,cs}} // second square 1
  };
  field.BuildCube(cube_positions_b, true);
  
  field.Add3D(field_3d.size(), form, field_3d.field());

  draw::DrawField(x_border, y_border, field.field());

}

int main() {
  /* initialize random seed: */
  srand (time(NULL));

  // Initialize curses
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, true);
  clear();


  // Initialize colors.
  use_default_colors();
  start_color();
  init_pair(COLOR_AVAILIBLE, COLOR_BLUE, -1);
  init_pair(COLOR_ERROR, COLOR_RED, -1);
  init_pair(COLOR_DEFAULT, -1, -1);
  init_pair(COLOR_MSG, COLOR_CYAN, -1);
  init_pair(COLOR_SUCCESS, COLOR_GREEN, -1);
  init_pair(COLOR_MARKED, COLOR_MAGENTA, -1);

  mvaddstr(2, COLS/2-2, "CUBE");
  mvaddstr(4, COLS/2-8, "press 'q' to exit");
  mvaddstr(6, COLS/2-29, "x: toggle left/right, y: toggle up/down, z: toggle front/back");
  mvaddstr(7, COLS/2-7, "use j/k to move");

  char choice = ' ';

  int x_border = 8;
  int y_border = 10;
  if (COLS > LINES)
    x_border = (COLS-LINES)/4;
  else if (LINES > COLS)
    y_border += (LINES-COLS)/2;
  int field_size = std::min(LINES, COLS)-std::min(x_border, y_border)*2 + 4;
  int cs = field_size - field_size*0.25 -2;

  Field3D field_3d(cs+1);
  for (int i=0; i < 15; i++) {
    int ran_x = rand() % cs-5 + 5;
    int ran_y = rand() % cs-5 + 5;
    int ran_z = rand() % cs-5 + 5;
    int size = rand() % 8 + 3;
    field_3d.AddForms(utils::GetStar({ran_x, ran_y, ran_z}, size));
  }

  std::map<char, int> form_a = {{'x',-1},{'y',0},{'z',0}, {'d', -18}};
  std::map<char, int> form_b = {{'x',0},{'y',0},{'z',-1}, {'d', -15}};
  std::map<char, int> form_c = {{'x',0},{'y',1},{'z',0}, {'d', 22}};
  std::map<char, int> form = form_a;
  int faktor = 1;

  while (choice != 'q') {
    Print(field_size, cs, x_border, y_border, form, field_3d);
    choice = getch();

    if (choice == 'j')
      form['d'] += 1*faktor;
    if (choice == 'k')
      form['d'] += -1*faktor;

    if (choice == 'x') {
      form = form_a;
      faktor = 1;
    }
    if (choice == 'y') {
      form = form_c;
      faktor = 1;
    }
    if (choice == 'z') {
      form = form_b;
      faktor = 3;
    }

    std::string msg = "form=";
    for (const auto& it : form) {
      msg += it.first + std::to_string(it.second) + "  ";
    }

    mvaddstr(5, 5, msg.c_str());
  }
  
  // Wrap up.
  refresh();
  clear();
  endwin();
  exit(0);
}
