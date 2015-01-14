#include "../inc/BatteryPredict.h"
#include "../inc/WeightedMeanPredict.h"
#include "../inc/Consts.h"

#include <cmath>

// DEBUG
#include <iostream>

using namespace bp;
using namespace std;

bp::WeightedMeanPredict::WeightedMeanPredict(const MonotonicPoints& mon_points)
   : BatteryPredict()
{
   Calculate(mon_points);
}

void bp::WeightedMeanPredict::Calculate(const MonotonicPoints& mon_points)
{
   double weighted_mean = _CalculateWeightedMean(mon_points.points);

   if (mon_points.monotonic == MON_DEC)
      _SetCharging(false);
   else
      _SetCharging(true);

   unsigned actual_charge = mon_points.points[mon_points.points.size() - 1].y;
   cout << "actual_charge: " << actual_charge << "\n"; 
   cout << "weighted_mean: " << weighted_mean << "\n";

   if (IsCharging())
   {
      _SetFullChargeTime(_WhenReachCharge(actual_charge, weighted_mean, 100));
   }
   else
   {
      _SetTheoriticalTimeFromFullCharge(abs(_WhenReachCharge(
         actual_charge, weighted_mean, 100)));
      _SetFullDischargeTime(_WhenReachCharge(actual_charge, weighted_mean, 0));
      _SetCriticalDischargeTime(_WhenReachCharge(actual_charge, weighted_mean,
         CONSTS::BATTERY_CRITICAL_LEVEL));
   }
}

double bp::WeightedMeanPredict::_CalculateWeightedMean(const vector<Point>& points) const
{
   // zmienne pomocnicze
   unsigned weight = points.size() - 1;
   int sum = 0;
   unsigned weight_sum = 0u;

   // pamiętamy, że punkty są teraz już w dobrej kolejności
   for (unsigned i = points.size() - 1; i >= 1; --i)
   {
      int diff = points[i].y - points[i-1].y; 
      sum += weight * diff;
      weight_sum += weight;

      --weight;
   }

   return (static_cast<double>(sum) / static_cast<double>(weight_sum));
}

int bp::WeightedMeanPredict::_WhenReachCharge(
   unsigned actual_charge, double weighted_mean, unsigned destination_charge) const
{
   int diff_charge = destination_charge - actual_charge;

   return diff_charge * (CONSTS::MINUTE_INTERVAL / weighted_mean);
}
