#ifndef FILE_H
#define FILE_H 

#include <vector>
#include <string>

namespace bp
{
   class File
   {
      public:
         // zwraca wektor wczytanych od tylu lini z pliku
         static std::vector<std::string> GetReverseLines(
            const std::string& file_name);
      private:
         // Singleton
         File();
   };
}

#endif /* FILE_H */
