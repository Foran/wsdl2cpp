#ifndef __WSDL2CPP_CLIENT_H__
#define __WSDL2CPP_CLIENT_H__

#include <string>

namespace WSDL2CPP {
	template <class T> class Serializable
	{
	public:
		static T Serialize(const std::string &source) { return T::_Serialize(source); }
		static std::string Deserialize(const T &source) { return source.Deserialize(); }
	protected:
		virtual std::string Deserialize() const = 0;
	};
};

#endif