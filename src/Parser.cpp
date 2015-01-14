#include "../inc/Parser.h"
#include "../inc/Consts.h"
#include "../inc/Point.h"
#include "../inc/MonotonicPoints.h"
#include "../inc/Errors.h"

#include <vector>
#include <string>
#include <sstream>

using namespace std;
using namespace bp;

const unsigned bp::Parser::MAX_MON_CONSTS_TIME = 10u;
const unsigned bp::Parser::MAX_MON_CONSTS = 
   Parser::MAX_MON_CONSTS_TIME / CONSTS::MINUTE_INTERVAL; 

vector<Point> bp::Parser::GetPoints(const vector<string>& lines)
{
   vector<Point> points;

   for (vector<string>::const_iterator it = lines.begin(); it != lines.end(); ++it)
   {
      points.push_back(_ParseLine(*it));
   }

   return points;
}

Point bp::Parser::_ParseLine(const std::string& line)
{
   Point p;

   // data jest w formacie 
   // 12.01.2015 21:32 45%
   // wyłuskujemy wartosc procentowa
   string percent = _SplitString(line, ' ')[2];
   // usuwamy ostatni znak (%)
   percent = percent.substr(0, percent.size() - 1);
   // konwertujemy string to int i przypisujemy do punktu
   p.y = stoi(percent); 
   // przypisujemy błąd jako 1 procent
   p.er = 1.0;

   return p;
}

vector<string> bp::Parser::_SplitString(const string &s, char delim) 
{
   vector<string> elems;
   _SplitString(s, delim, elems);

   return elems;
}

vector<string>& bp::Parser::_SplitString(const string &s, char delim, vector<string> &elems) 
{
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) 
    {
        elems.push_back(item);
    }

    return elems;
}

MonotonicPoints bp::Parser::GetMonotonicPoints(const std::vector<Point>& points)
{
   // potrzeba co najmniej 2 punktów, żeby móc cokolwiek powiedzieć
   // o monotoniczności punktów
   if (points.size() < 2)
      throw too_less_points("Need at least 2 points to analyze"
         " monotonic of points");

   // Pamiętamy, że dostajemy punkty w odwróconej kolejności!
   MONOTONIC monotonic = _Specify2PointsMonotonic(points[1], points[0]);
   // liczba wystąpień stałej monotoniczności 2 punktów
   unsigned mon_consts = (monotonic == MON_CONST) ? 2 : 1; 
   // licznik, który też wskazuje na to ile punktow zgadza sie 
   // z monotonicznoscia
   unsigned i = 1;
   for (; i < points.size() - 1; ++i)
   {
      MONOTONIC new_monotonic = _Specify2PointsMonotonic(points[i+1], points[i]);

      // jeżeli monotonicznosc punktow nie zmienila sie 
      if (new_monotonic == MON_CONST)
      {
         ++mon_consts;

         // i przekroczyla liczbe MAX_MON_CONSTS pod rzad to przerywamy petle
         if (mon_consts >= MAX_MON_CONSTS)
         {
            ++i;
            break;
         }
      }
      else
      {
         mon_consts = 1;
      }

      // jeżeli monotonicznosci sie roznia
      if (monotonic != new_monotonic)
      {
         // jeżeli żadna z monotonicznosci nie jest stala
         if (monotonic != MON_CONST && new_monotonic != MON_CONST)
         {
            break;
         }
         // jezeli poprzednia jest stala to zamieniamy z nowa
         if (monotonic == MON_CONST)
         {
            monotonic = new_monotonic;
         }
         // jeżeli nowa jest stala to nic nie robimy
      }
   }

   MonotonicPoints mon_points;
   mon_points.monotonic = monotonic;

   // przywracamy z powrotem odpowiednia kolejnosc
   for (int j = i; j >= 0; --j)
   {
      Point p = points[j];
      p.x = (i - j) * CONSTS::MINUTE_INTERVAL;
      mon_points.points.push_back(p);
   }

   return mon_points;
}
