#include "inc/Point.h"
#include "inc/Parser.h"
#include "inc/File.h"
#include "inc/MonotonicPoints.h"
#include "inc/UNumber.h"

#include <iostream>

using namespace std;
using namespace bp;

int main()
{
   vector<string> reverse_lines = File::GetReverseLines("battery.log");
   vector<Point> reverse_points = Parser::GetPoints(reverse_lines);
   MonotonicPoints monotonic_points = Parser::GetMonotonicPoints(reverse_points);

   string mon_str;
   MONOTONIC monotonic = monotonic_points.monotonic;
   if (monotonic == MON_INC)
      mon_str = "increasing";
   else if (monotonic == MON_DEC)
      mon_str = "decreasing";
   else
      mon_str = "const";

   cout << "monotonic: " << mon_str << "\n";
   cout << "points size: " << monotonic_points.points.size() << "\n";
   for (vector<Point>::iterator it = monotonic_points.points.begin();
      it != monotonic_points.points.end(); ++it)
   {
      cout << "x:" << (*it).x << " y:" << (*it).y <<
         " er:" << (*it).er << "\n";
   }

   return 0;
}
