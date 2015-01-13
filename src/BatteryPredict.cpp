#include "../inc/BatteryPredict.h"
#include "../inc/UNumber.h"
#include "../inc/Errors.h"

#include <iostream>

using namespace std;
using namespace bp;

bp::BatteryPredict::BatteryPredict()
   : _full_discharge_time(), _full_charge_time(), _critical_discharge_time() {}

unsigned bp::BatteryPredict::GetFullDischargeTime() const
{
   if (_full_discharge_time.nan)
      throw cant_calculate("Nie udało obliczyć się czasu całkowitego rozładowania");

   return _full_discharge_time.number;
}

unsigned bp::BatteryPredict::GetFullChargeTime() const
{
   if (_full_charge_time.nan)
      throw cant_calculate("Nie udało obliczyć się czasu całkowitego naładowania");

   return _full_charge_time.number;
}

unsigned bp::BatteryPredict::GetCriticalDischargeTime() const
{
   if (_critical_discharge_time.nan)
      throw cant_calculate("Nie udało obliczyć się czasu do krytycznego rozładowania");

   return _critical_discharge_time.number;
}

bool bp::BatteryPredict::IsCharging() const
{
   return _charging;
}

ostream& operator<<(ostream& os, const BatteryPredict& bp)
{
   if (bp.IsCharging())
   {
      os << "Bateria ładuje się\n";
      os << "Do całkowitego naładowania pozostało " << 
         bp.GetFullChargeTime() << " minut\n";
   }
   else
   {
      os << "Bateria rozładowuje się\n";
      os << "Do krytycznego rozładowania pozostało " << 
         bp.GetCriticalDischargeTime() << " minut\n";
      os << "Do całkowitego rozładowania pozostało " << 
         bp.GetFullDischargeTime() << " minut\n";
   }

   return os;
}
