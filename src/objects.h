#ifndef SRC_OBJECTS_H_
#define SRC_OBJECTS_H_

#include <iostream>
#include <string>

struct Figure {
  std::string symbol;
  int color;
  bool dominant;
};

struct Position2D {
  int x;
  int y;
  std::string to_string() {
    return std::to_string(x) + "|" + std::to_string(y);
  }
};

struct Position3D {
  int x;
  int y;
  int z; 
  std::string to_string() const {
    return std::to_string(x) + "|" + std::to_string(y) + "|" + std::to_string(z);
  }

};

#endif
