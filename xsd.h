#ifndef __XSD_H__
#define __XSD_H__

#include <string>
#include <vector>

#include <libxml/parser.h>
#include <libxml/tree.h>

#ifdef _WIN32
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

using namespace std;

class XSD
{
	public:
		XSD(string filename);
		XSD(xmlDocPtr document);
		XSD(xmlNodePtr node);
		XSD(xmlDocPtr document, string path);
		XSD(xmlNodePtr node, string path);
		~XSD();

		string get_Namespace() const;
	protected:
		void Load(string filename);
		void Load(xmlDocPtr document);
		void Load(xmlNodePtr node);
		void LoadElements(xmlNodePtr node);
	private:
		string mPath;
		string mNamespace;
		XSD();
		XSD(const XSD &source);
		XSD operator=(const XSD &source) const;
};

#endif
