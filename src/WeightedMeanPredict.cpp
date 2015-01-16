#include "../inc/BatteryPredict.h"
#include "../inc/WeightedMeanPredict.h"
#include "../inc/Consts.h"

#include <cmath>

using namespace bp;
using namespace std;

const unsigned bp::WeightedMeanPredict::_MAX_POINTS = 16;

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
   _SetActualCharge(actual_charge);

   if (IsCharging())
   {
      if (weighted_mean == 0.0)
         _SetFullChargeTime(0u);
      else
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
   // ograniczamy maksymalna ilosc punktow branych pod uwage
   unsigned n_points = points.size() - 2;
   if (n_points > _MAX_POINTS)
      n_points = _MAX_POINTS;

   unsigned weight = 1 << n_points; 
   int sum = 0;
   unsigned weight_sum = 0u;

   // pamiętamy, że punkty są teraz już w dobrej kolejności
   for (unsigned i = n_points + 1; i >= 1; --i)
   {
      int diff = points[i].y - points[i-1].y; 
      sum += weight * diff;
      weight_sum += weight;

      weight >>= 1;
   }

   return (static_cast<double>(sum) / static_cast<double>(weight_sum));
}

int bp::WeightedMeanPredict::_WhenReachCharge(
   unsigned actual_charge, double weighted_mean, unsigned destination_charge) const
{
   int diff_charge = destination_charge - actual_charge;

   return diff_charge * (CONSTS::MINUTE_INTERVAL / weighted_mean);
}
