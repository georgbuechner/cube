#ifndef SRC_FIELD_3D_H_
#define SRC_FIELD_3D_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "curses.h"
#include "utils.h"
#include "objects.h"

#define COLOR_AVAILIBLE 1
#define COLOR_ERROR 2 
#define COLOR_DEFAULT 3
#define COLOR_MSG 4
#define COLOR_SUCCESS 5
#define COLOR_MARKED 6
#define COLOR_PROGRESS 7


class Field3D {
  public:
    Field3D(unsigned int size) {
       for (unsigned int x=0; x<size; x++) {
        field_.push_back(std::vector<std::vector<Figure>>());
        for (unsigned int y=0; y<size; y++) {
          field_[x].push_back(std::vector<Figure>());
            for (unsigned int z=0; z<size; z++)
              field_[x][y].push_back({" ", COLOR_ERROR, false});
        }
      }
      size_ = size;
    }

    typedef std::vector<std::vector<std::vector<Figure>>> t_3dfield;
    
    // getter 
    const t_3dfield& field() {
      return field_;
    }
    int size() {
      return size_;
    }


    void AddForms(std::vector<std::pair<Position3D, Position3D>> positions) {
      for (const auto &it : positions) {
        auto line = utils::GetLine3D(it.first, it.second);
        for (const auto pos : line) {
          if (pos.x > 0 && pos.x < size_ && pos.y > 0 && pos.y < size_ && pos.z > 0 && pos.z < size_)
            field_[pos.x][pos.y][pos.z].color = COLOR_AVAILIBLE;
        }
      }
    }

  private:
    t_3dfield field_;
    int size_;

};

#endif
