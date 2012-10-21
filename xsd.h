#ifndef __XSD_H__
#define __XSD_H__

#include <string>
#include <vector>
#include <map>

using namespace std;

class XSD
{
 public:
   XSD(string filename);
   ~XSD();
   
 protected:
 private:
   XSD();
   XSD(const XSD &source);
};

#endif