#include "inc/Point.h"
#include "inc/Parser.h"
#include "inc/File.h"
#include "inc/MonotonicPoints.h"
#include "inc/UNumber.h"
#include "inc/BatteryPredict.h"
#include "inc/WeightedMeanPredict.h"

#include <iostream>

using namespace std;
using namespace bp;

int main()
{
   // odczytujemy i odwracamy linie z pliku
   vector<string> reverse_lines = File::GetReverseLines("battery.log");
   // parsujemy linie do wektora odwróconych punktów
   vector<Point> reverse_points = Parser::GetPoints(reverse_lines);
   // uzyskujemy punkty monotonicznosci (juz w oryginalnej kolejności)
   // czyli znowu je odwracamy
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

   // konstruujemy obiekt przewidujacy korzystający ze średniej ważonej
   WeightedMeanPredict wmp(monotonic_points);
   cout << wmp << "\n";

   return 0;
}
