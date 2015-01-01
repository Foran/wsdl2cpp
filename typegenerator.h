#ifndef __TYPEGENERATOR_H__
#define __TYPEGENERATOR_H__

#include <string>

#include "xsdelement.h"

using namespace std;

class TypeGenerator
{
public:
	TypeGenerator();
	void Generate(const string outputPath, const XSDElement &element);
protected:
private:
};

#endif