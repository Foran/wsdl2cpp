/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/path/path.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include "lib/path/path.h"

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#include <libgen.h>
#endif

#include <string>
#include <vector>

#include "gflags/gflags.h"

DEFINE_bool(auto_expand_relative_root, true, "Automatically expand a relative "
                                             "path to file:/// UNC when no "
                                             "prefix is supplied");

namespace wsdl2cpp {
namespace lib {
namespace path {

Path::Path() {
}

Path::Path(const ::std::string &source) {
    *this = source;
}

Path::Path(const Path &source) {
    *this = source;
}

Path::~Path() {
}

Path &Path::operator=(const ::std::string &source) {
    mPath = source;

    return *this;
}

Path &Path::operator=(const Path &source) {
    *this = source.mPath;

    return *this;
}

bool Path::operator==(const ::std::string &source) {
    return mPath == source;
}

bool Path::operator==(const Path &source) {
    return mPath == source.mPath;
}

::std::string Path::get_Raw() const {
    return mPath;
}

::std::string Path::CurrentDirectory() {
    ::std::string retval = "";
    char path[FILENAME_MAX];

    if (GetCurrentDir(path, sizeof(path)) != nullptr) {
        retval = path;
#ifdef _WIN32
        retval += '\\';
#else
        retval += '/';
#endif
    }

    return retval;
}

::std::string Path::get_Absolute(const ::std::string &path) {
    ::std::string retval = path;

    if (!Path::is_Absolute(retval)) {
        retval = Path::CurrentDirectory() + retval;
    }

    return retval;
}

::std::string Path::get_Absolute() const {
    return Path::get_Absolute(mPath);
}

::std::string Path::get_BaseFilename(const ::std::string &path) {
    ::std::string retval = Path::get_Absolute(path);

    size_t pos = retval.find_last_of("/\\");
    retval = retval.substr(pos + 1);

    return retval;
}

::std::string Path::get_BaseFilename() const {
    return Path::get_BaseFilename(mPath);
}

::std::string Path::get_BasePath(const ::std::string &path) {
    ::std::string retval = Path::get_Absolute(path);

    size_t pos = retval.find_last_of("/\\");
    retval = retval.substr(0, pos + 1);

    return retval;
}

::std::string Path::get_BasePath() const {
    return Path::get_BasePath(mPath);
}

::std::string Path::get_UNC(const ::std::string &path) {
    ::std::string retval = path;

    if (!Path::is_UNC(retval)) {
        if (Path::is_Absolute(retval)) {
            retval = "file://" + Path::get_Absolute(retval);
        } else if (Path::is_Relative(retval)) {
            retval = Path::ResolveRelative(Path::CurrentDirectory(),
                                           retval).get_UNC();
        }
    }

    return retval;
}

::std::string Path::get_UNC() const {
    return Path::get_UNC(mPath);
}

::std::string Path::get_Protocol() const {
    ::std::string retval = get_UNC();

    return retval.substr(0, retval.find_first_of(":"));
}

Path Path::ResolveRelative(const ::std::string &source,
                           const ::std::string &relative) {
    Path path(source);
    ::std::string temp = path.get_UNC();
    temp = temp.substr(path.get_Protocol().length() + 3);
    ::std::vector<::std::string> parts;
    while (temp.length() > 0) {
        size_t t = temp.find_first_of('/');
        if (t == ::std::string::npos) {
            parts.push_back(temp);
            temp = "";
        } else {
            parts.push_back(temp.substr(0, t));
            temp = temp.substr(t + 1);
        }
    }
    ::std::string retval = relative;
    while (retval.find_first_of("../") == 0) {
        parts.pop_back();
        retval = retval.substr(3);
    }
    for (int i = parts.size() - 1; i >= 0; i--) {
        retval = parts[i] + "/" + retval;
    }

    return Path(retval);
}

Path Path::ResolveRelative(const ::std::string &relative) const {
    return Path::ResolveRelative(mPath, relative);
}

bool Path::is_Relative(const ::std::string &relative) {
    bool retval = false;

    if (!Path::is_Absolute(relative)) {
        retval = true;
    }

    return retval;
}

bool Path::is_UNC(const ::std::string &path) {
    bool retval = true;
#ifdef _WIN32
    char seperator = '\\';
#else
    char seperator = '/';
#endif
    bool isRoot = path.c_str()[0] == seperator;
    bool isExplicitRelative = path.c_str()[0] == '.' &&
                              (path.c_str()[1] == seperator ||
                               (path.c_str()[1] == '.' &&
                                path.c_str()[2] == seperator));

    if (isRoot ||
        isExplicitRelative ||
        path.find("://") == ::std::string::npos) {
        retval = false;
    }

    return retval;
}

bool Path::is_UNC() const {
    return Path::is_UNC(mPath);
}

bool Path::is_Absolute(const ::std::string &path) {
    bool retval = Path::is_UNC(path);

    if (!retval) {
#ifdef _WIN32
        if (isalpha(path.c_str()[0]) &&
            path.c_str()[1] == ':' &&
            path.c_str()[2] == '\\') {
            retval = true;
        } else if (path.c_str()[0] == '\\' &&
                   path.c_str()[1] == '\\') {
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

bool Path::is_Absolute() const {
    return Path::is_Absolute(mPath);
}

}  // namespace path
}  // namespace lib
}  // namespace wsdl2cpp
