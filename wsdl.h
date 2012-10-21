#ifndef __WSDL_H__
#define __WSDL_H__

#include <string>
#include <vector>
#include <map>

using namespace std;

class WSDL 
{
 public:
   WSDL(string filename);
   ~WSDL();
   
 protected:
 private:
   vector<string> mInterfaces;
   map<string, vector<string> > mOperations;
   map<string, vector<string> > mOperationReturnTypes;
   WSDL();
   WSDL(const WSDL &source);
};

#endif