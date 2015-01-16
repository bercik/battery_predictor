#ifndef BATTERYPREDICT_H
#define BATTERYPREDICT_H 

#include "UNumber.h"
#include "MonotonicPoints.h"

#include <iostream>

namespace bp
{
   class BatteryPredict
   {
      public:
         // zwraca czas do całkowitego rozładowania baterii
         // lub wyjątek jeśli nie mógł obliczyć
         unsigned GetFullDischargeTime() const;
         // zwraca czas do całkowitego naładowania baterii
         // lub wyjątek jeśli nie mógł obliczyć
         unsigned GetFullChargeTime() const;
         // zwraca czas do krytycznego rozładowania baterii
         // lub wyjątek jeśli nie mógł obliczyć
         unsigned GetCriticalDischargeTime() const;
         // zwraca teoretyczny czas od naładowania baterii
         // lub wyjątek jeśli nie mógł obliczyć
         unsigned GetTheoriticalTimeFromFullCharge() const;
         // Zwraca poziom aktualnego naładowania baterii
         unsigned GetActualCharge() const;
         // zwraca czy bateria ładuje się
         bool IsCharging() const;
         // oblicza wszystkie parametry na podstawie podanych
         // punktów monotoniczności
         virtual void Calculate(const MonotonicPoints& mon_points) = 0;
      protected:
         // z klasy należy dziedziczyć
         BatteryPredict();
         // settery
         void _SetCharging(bool charging);
         void _SetFullDischargeTime(unsigned full_discharge_time, bool nan = false);
         void _SetFullChargeTime(unsigned full_charge_time, bool nan = false);
         void _SetTheoriticalTimeFromFullCharge(unsigned theoretical_time_from_full_charge,
            bool nan = false);
         void _SetCriticalDischargeTime(unsigned critical_discharge_time,bool nan = false);
         void _SetActualCharge(unsigned actual_charge);
      private:
         // czas do całkowitego rozładowania baterii
         UNumber _full_discharge_time;
         // czas do całkowitego naładowania baterii
         UNumber _full_charge_time;
         // czas do krytycznego rozładowania baterii
         UNumber _critical_discharge_time;
         // teoretyczny czas działania od całkowitego naładowania
         UNumber _theoretical_time_from_full_charge;
         // aktualny stan naładowania (w %)
         unsigned _actual_charge;
         // czy bateria się ładuje 
         bool _charging;
   };

   std::ostream& operator<<(std::ostream& os, const BatteryPredict& bp);
}

#endif /* BATTERYPREDICT_H */
