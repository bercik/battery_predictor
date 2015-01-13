#ifndef CONSTS_H
#define CONSTS_H 

namespace bp
{
   class CONSTS
   {
      public:
         // minutowy interwał pomiędzy pomiarami
         static const unsigned MINUTE_INTERVAL;
         // krytyczny poziom baterii (w %)
         static const unsigned BATTERY_CRITICAL_LEVEL;
      private:
         CONSTS();
   };
}
#endif /* CONSTS_H */
