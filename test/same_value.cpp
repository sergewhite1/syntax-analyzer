#include "same_value.h"

#include <cmath>
#include <limits>

bool same_value(double a, double b) {
  return fabs(a - b) < std::numeric_limits<double>::epsilon();
}
