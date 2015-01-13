#ifndef MONOTONICPOINTS_H
#define MONOTONICPOINTS_H 

#include "Point.h"

#include <vector>

namespace bp
{
   enum MONOTONIC { MON_INC, MON_DEC, MON_CONST };

   struct MonotonicPoints
   {
      // wektor punktów
      std::vector<Point> points;
      // monotoniczność punktów (a dokładniej składowej y)
      MONOTONIC monotonic;
   };
}

#endif /* MONOTONICPOINTS_H */
