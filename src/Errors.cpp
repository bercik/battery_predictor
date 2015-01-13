#include "../inc/Errors.h"

#include <string>

using namespace std;

const string& bp::error::GetMsg() const
{
   return _msg;
}

bp::error::error(std::string msg)
   : _msg(msg) {}

bp::too_less_points::too_less_points(std::string msg)
   : error(msg) {}

bp::cant_calculate::cant_calculate(std::string msg)
   : error(msg) {}
