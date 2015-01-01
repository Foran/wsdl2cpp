#include "path.h"

Path::Path()
{

}

Path::Path(const string &source)
{
	*this = source;
}

Path::Path(const Path &source)
{
	*this = source;
}

Path::Path(const Path &&source) : mPath(std::move(source.mPath))
{
}

Path::~Path()
{

}

Path &Path::operator=(const string &source)
{
	mPath = source;

	return *this;
}

Path &Path::operator=(const Path &source)
{
	*this = source.mPath;

	return *this;
}

Path &Path::operator=(const Path &&source)
{
	mPath = std::move(source.mPath);

	return *this;
}

bool Path::operator==(const string &source)
{
	return mPath == source;
}

bool Path::operator==(const Path &source)
{
	return mPath == source.mPath;
}

string Path::get_Raw() const
{
	return mPath;
}

string Path::CurrentDirectory()
{
	string retval = "";
	char path[FILENAME_MAX];

	if (GetCurrentDir(path, sizeof(path)) > 0) {
		retval = path;
#ifdef _WIN32
		retval += '\\';
#else
		retval += '/';
#endif
	}

	return retval;
}

string Path::get_Absolute(const string &path)
{
	string retval = path;

	if (!Path::is_Absolute(retval)) {
		retval = Path::CurrentDirectory() + retval;
	}

	return retval;
}

string Path::get_Absolute() const
{
	return Path::get_Absolute(mPath);
}

string Path::get_BaseFilename(const string &path)
{
	string retval = Path::get_Absolute(path);

	size_t pos = retval.find_last_of("/\\");
	retval = retval.substr(pos + 1, retval.length() - pos - 1);

	return retval;
}

string Path::get_BaseFilename() const
{
	return Path::get_BaseFilename(mPath);
}

string Path::get_UNC(const string &path)
{
	string retval = path;

	if (!Path::is_UNC(retval)) {
		retval = "file://" + Path::get_Absolute(retval);
	}

	return retval;
}

string Path::get_UNC() const
{
	return Path::get_UNC(mPath);
}

Path Path::ResolveRelative(const string &source, const string &relative)
{
	return source;
}

Path Path::ResolveRelative(const string &relative) const
{
	return Path::ResolveRelative(mPath, relative);
}

bool Path::is_UNC(const string &path)
{
	bool retval = false;

	if (path.c_str()[0] !=
#ifdef _WIN32
		'\\'
#else
		'/'
#endif
		&&
		path.find_first_of("://") != string::npos) {
		retval = true;
}

	return retval;
}

bool Path::is_UNC() const
{
	return Path::is_UNC(mPath);
}

bool Path::is_Absolute(const string &path)
{
	bool retval = Path::is_UNC(path);
	if (!retval) {
#ifdef _WIN32
		if (isalpha(path.c_str()[0]) && path.c_str()[1] == ':' && path.c_str()[2] == '\\') {
			retval = true;
		}
		else if(path.c_str()[0] == '\\' && path.c_str()[1] == '\\') {
			retval = true;
		}
#else
		if (path.c_str()[0] == '/') {
			retval = true;
		}
#endif
	}
	return retval;
}

bool Path::is_Absolute() const
{
	return Path::is_Absolute(mPath);
}
