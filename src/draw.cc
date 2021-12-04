#include "draw.h"
#include "curses.h"

void draw::DrawField(int x_border, int y_border, const Field2D::t_2dfield& field) {
  for (unsigned int x=0; x<field.size(); x++) {
    for (unsigned int y=0; y<field.size(); y++) {
      auto color = field[x][y].color;
      auto symbol = field[x][y].symbol;
      auto dominant = field[x][y].dominant;
      attron(COLOR_PAIR(color));

      if (utils::InCube(x, y, field.size())) {
        mvaddstr(y_border+y, (x_border+x)*2, "-"); 
        if (symbol != " ") {
          if (dominant)
            attron(COLOR_PAIR(COLOR_DEFAULT));
          mvaddstr(y_border+y, (x_border+x)*2, field[x][y].symbol.c_str());
        }
      }
      else 
        mvaddstr(y_border+y, (x_border+x)*2, field[x][y].symbol.c_str());
      attron(COLOR_PAIR(COLOR_DEFAULT));
    }
  }
}

