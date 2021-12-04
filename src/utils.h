#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include "objects.h"
#include <utility>
#include <map>
#include <vector>

namespace utils {
  Position2D TransformPosition(Position3D pos);


  std::vector<Position2D> GetLine(Position2D pos_a, Position2D pos_b);
  std::vector<Position3D> GetLine3D(Position3D pos_a, Position3D pos_b);

  unsigned int dist(Position2D pos_a, Position2D pos_b);

  Position2D reduce(Position2D pos);
  Position3D reduce3D(Position3D pos);

  void message(std::string msg);

  bool InCube(int z, int y, int size);

  std::vector<std::pair<Position3D, Position3D>> GetStar(Position3D center, int height);
}

#endif
