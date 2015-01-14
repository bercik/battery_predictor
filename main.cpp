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
   // konstruujemy obiekt przewidujacy korzystający ze średniej ważonej
   WeightedMeanPredict wmp(monotonic_points);
   // wyświetlamy aktualny status baterii w oparciu o model średniej ważonej
   cout << wmp << "\n";

   return 0;
}
