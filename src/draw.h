#ifndef SRC_DRAW_H_
#define SRC_DRAW_H_

#include "field_2d.h"
#include "objects.h"
#include <utility>
#include <vector>

namespace draw {
  void DrawField(int x_border, int y_border, const Field2D::t_2dfield& field);
}

#endif
