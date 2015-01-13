#ifndef PARSER_H
#define PARSER_H 

#include "Point.h"
#include "MonotonicPoints.h"
#include "Consts.h"

#include <vector>
#include <string>

namespace bp
{
   class Parser
   {
      public:
         // funkcja zwracajaca wektor punktow na podstawie
         // lini
         static std::vector<Point> GetPoints(
            const std::vector<std::string>& lines);
         // Wyodrębnia monotoniczne punkty
         static MonotonicPoints GetMonotonicPoints(
            const std::vector<Point>& points);
         // rozdziela łańcuch
         static std::vector<std::string> _SplitString(
            const std::string &s, char delim);
         // rozdziela łańcuch
         static std::vector<std::string>& _SplitString(
            const std::string &s, char delim, 
            std::vector<std::string> &elems);
      private:
         // singleton
         Parser();

         // parsuje jedna linie
         static Point _ParseLine(const std::string& line);
         // określa monotoniczność dwóch punktów
         static MONOTONIC _Specify2PointsMonotonic(
            const Point& p1, const Point& p2);

         // maksymalny czas wystapienia stalej 
         // monotonicznosci punktow
         static const unsigned MAX_MON_CONSTS_TIME;
         // maksymalna liczba wystapien stalej
         // monotonicznosci punktow
         static const unsigned MAX_MON_CONSTS;
   };


   inline MONOTONIC Parser::_Specify2PointsMonotonic(
      const Point& p1, const Point& p2)
   {
      double diff = p1.y - p2.y;

      if (diff < 0)
         return MON_INC;
      else if (diff > 0)
         return MON_DEC;
      else
         return MON_CONST;
   }
}

#endif /* PARSER_H */
