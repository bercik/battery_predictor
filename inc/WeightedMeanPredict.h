#ifndef WEIGHTEDMEANPREDICT_H
#define WEIGHTEDMEANPREDICT_H 

#include "BatteryPredict.h"
#include "MonotonicPoints.h"
#include "Point.h"

#include <vector>

namespace bp
{
   class WeightedMeanPredict : public BatteryPredict
   {
      public:
         // konstruktor dokonujący od razu obliczeń
         WeightedMeanPredict(const MonotonicPoints& mon_points);
         // funkcja wirtualna obliczająca parametry
         virtual void Calculate(const MonotonicPoints& mon_points); 
      protected:
         // oblicza średnią ważoną składowej y punktów
         double _CalculateWeightedMean(const std::vector<Point>& points) const;
         // oblicza po jakim czasie wart. naładowania osiagnie zadana
         // na podstawie podanych parametrów (funkcja liniowa)
         int _WhenReachCharge(unsigned actual_charge, double weighted_mean,
            unsigned destination_charge) const;
         // maksymalna liczba punktow branych pod uwage (wiekszej ilosci i tak
         // nie ma sensu ze wzgl. na geometryczny charakter tego przewidywania)
         static const unsigned _MAX_POINTS;
   };
}

#endif /* WEIGHTEDMEANPREDICT_H */
