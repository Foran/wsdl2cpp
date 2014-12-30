#pragma once

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