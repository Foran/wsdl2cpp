#ifndef __WSDL_H__
#define __WSDL_H__

#include <string>

using namespace std;

class WSDL 
{
 public:
   WSDL();
   WSDL(const WSDL &source);
   WSDL(string filename);
   ~WSDL();
   
 protected:
 private:
};

#endif