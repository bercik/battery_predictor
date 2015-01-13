#ifndef ERRORS_H
#define ERRORS_H 

#include <string>

namespace bp
{
   class error 
   {
      public:
         // zwraca wiadomość błędu
         const std::string& GetMsg() const;
      protected:
         // z klasy należy dziedziczyć
         error(std::string msg);
      private:
         // wiadomość błędu
         std::string _msg;
   };

   class too_less_points : public error
   {
      public:
         too_less_points(std::string msg = "");
   };
}

#endif /* ERRORS_H */
