#ifndef __TYPEGENERATOR_H__
#define __TYPEGENERATOR_H__

#include <string>

#include "xsdelement.h"

using namespace std;

class TypeGenerator
{
public:
	TypeGenerator(string outputPath);
	TypeGenerator(string outputPath, string ns);
	TypeGenerator(const TypeGenerator &source);
	~TypeGenerator();

	TypeGenerator &operator=(const TypeGenerator &source);

	void Generate(const XSDElement &element);
protected:
private:
	string mOutputPath;
	string mNamespace;
	TypeGenerator() = delete;

};

#endif