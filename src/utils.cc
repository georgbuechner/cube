#include <math.h>
#include <numeric>
#include <string>
#include <vector>

#include "curses.h"
#include "utils.h"
#include "objects.h"

Position2D utils::TransformPosition(Position3D pos) {
  if (pos.z == 0) 
    return {pos.x, pos.y};
  return {pos.x + pos.z/3, pos.y + pos.z/3};
}


std::vector<Position2D> utils::GetLine(Position2D pos_a, Position2D pos_b) {
  auto reduced_b = reduce({pos_b.x - pos_a.x, pos_b.y-pos_a.y});
  std::vector<Position2D> positions = {pos_a};
  do {
    auto cur = positions.back();
    positions.push_back({cur.x+reduced_b.x, cur.y+reduced_b.y});
    //message("new: " + positions.back().to_string());
  } while (positions.back().x != pos_b.x || positions.back().y != pos_b.y);
  return positions;
}

std::vector<Position3D> utils::GetLine3D(Position3D pos_a, Position3D pos_b) {
  auto reduced_b = reduce3D({pos_b.x - pos_a.x, pos_b.y-pos_a.y, pos_b.z-pos_a.z});
  std::vector<Position3D> positions = {pos_a};
  // message("a: " + pos_a.to_string());
  // message("b: " + pos_b.to_string());
  // message("reduced: " + reduced_b.to_string());
  do {
    auto cur = positions.back();
    positions.push_back({cur.x+reduced_b.x, cur.y+reduced_b.y, cur.z+reduced_b.z});
    // message("new: " + positions.back().to_string());
  } while (positions.back().x != pos_b.x || positions.back().y != pos_b.y || positions.back().z != pos_b.z);
  return positions;
}

Position2D utils::reduce(Position2D pos) {
  int gcd = std::gcd(pos.x, pos.y); 
  return {pos.x/gcd, pos.y/gcd};
}

Position3D utils::reduce3D(Position3D pos) {
  int gcd = std::gcd(pos.x, pos.y); 
  gcd = std::gcd(gcd, pos.z);
  if (gcd == 0)
    return {pos.x, pos.y, pos.z};
  return {pos.x/gcd, pos.y/gcd, pos.z/gcd};
}

unsigned int utils::dist(Position2D pos_a, Position2D pos_b) {
  return std::sqrt(pow(pos_b.x- pos_a.x, 2) + pow(pos_b.y- pos_a.y, 2));
}

void utils::message(std::string msg) {
  mvaddstr(1, 1, "                   ");
  mvaddstr(1, 1, msg.c_str());
  getch();

}

bool utils::InCube(int x, int y, int size) {
  size = size - size * 0.25;
  if (x > 0 && x < size-1 && y > 0 && y < size-1)
    return true;
  if (x-size <= y && y-size <= x)
    return true;
  return false;
}

std::vector<std::pair<Position3D, Position3D>> utils::GetStar(Position3D center, int height) {
  std::vector<std::pair<Position3D, Position3D>> positions;
  for (int z=0; z<height; z++) {
    for (int x=0; x<height-z; x++) {
      for (int y=0; y<height-(x+z); y++) {
        positions.push_back({{center.x+x, center.y+y, center.z+z}, {center.x+x, center.y-y, center.z+z}});
        positions.push_back({{center.x+x, center.y+y, center.z-z}, {center.x+x, center.y-y, center.z-z}});

        positions.push_back({{center.x-x, center.y+y, center.z-z}, {center.x-x, center.y-y, center.z-z}});
        positions.push_back({{center.x-x, center.y+y, center.z+z}, {center.x-x, center.y-y, center.z+z}});
      }
    }
  }
  return positions;
}
