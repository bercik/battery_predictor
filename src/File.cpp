#include "File.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> bp::File::GetReverseLines(
   const string& file_name)
{
   vector<string> lines_in_reverse;
   ifstream in(file_name.c_str());

   if (in.is_open())
   {
      string line;

      while (getline(in, line))
      {
         // Store the lines in reverse order.
         lines_in_reverse.insert(lines_in_reverse.begin(),
             line);
      }
   }

   return lines_in_reverse;
}
