#ifndef ITUENGINE_STRINGUTILS_H
#define ITUENGINE_STRINGUTILS_H

#include <string>
#include <vector>

typedef unsigned int HashedString;

class StringUtils
{
public:
	static HashedString hash(std::string s);

	static std::string toLower(std::string s);

	static std::vector<std::string> tokenize(const std::string &str, const std::string &delimiter);
};

#endif // ITUENGINE_STRINGUTILS_H