#ifndef SRC_FIELD_2D_H_
#define SRC_FIELD_2D_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "curses.h"
#include "utils.h"
#include "objects.h"
#include "field_3d.h"

class Field2D {
  public:
    Field2D(unsigned int size) {
      for (unsigned int x=0; x<size; x++) {
        field_.push_back(std::vector<Figure>());
        for (unsigned int y=0; y<size; y++)
          field_[x].push_back({" ", COLOR_DEFAULT, false});
      }
    }

    typedef std::vector<std::vector<Figure>> t_2dfield;

    // getter 
    const t_2dfield& field() {
      return field_;
    }

    void BuildCube(std::vector<std::pair<Position3D, Position3D>> positions, bool dominant) {
      for (const auto& edge : positions) {
        auto line = utils::GetLine(utils::TransformPosition(edge.first), utils::TransformPosition(edge.second));
        for (const auto& pos : line) 
          field_[pos.x][pos.y] = {"+", COLOR_DEFAULT, dominant};
      }
    }

    void Add3D(int size, std::map<char, int> form, const Field3D::t_3dfield& field_3d) {
      for (int x=0; x<size; x++) {
        for (int y=0; y<size; y++) {
          for (int z=0; z<size; z++) {
            unsigned int ux = x+int(z/3);
            unsigned int uy = y+int(z/3);
            if (x*form['x']+y*form['y']+z*form['z'] == form['d'] && ux < field_.size() && uy < field_[ux].size()) {
              field_[ux][uy].color = field_3d[x][y][z].color;
              if (field_3d[x][y][z].color == COLOR_AVAILIBLE && !field_[ux][uy].dominant)
                field_[ux][uy].symbol= "-";
            }
          }
        }
      }
    }

  private:
    t_2dfield field_;
};

#endif
