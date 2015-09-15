#ifndef _UNITY_VERSION_H_
#define _UNITY_VERSION_H_

#include <cstdint>
#include <string>

struct UnityVersion
{
	//int8_t major = 0;
	//int8_t minor = 0;
	//int8_t patch = 0;
	//std::string build;
	std::string raw;

	UnityVersion() = default;
	UnityVersion(const std::string& version)
	{
		puts(version.c_str());
		raw = version;
		//size_t offset = 0;
		//major = parseVersion(version, &offset); offset += 1;
		//minor = parseVersion(version, &offset); offset += 1;
		//patch = parseVersion(version, &offset); offset += 1;
		//build = version.substr(offset);
	}

	int8_t parseVersion(const std::string& version, size_t* offset)
	{
		int8_t ret = -1;
		if (version[*offset] != 'x')
		{
			try
			{
				ret = (int8_t)std::stoi(version, offset);
				return ret;
			}
			catch (...)
			{
				puts ("invalid version string");
				return ret;
			}
		}
		else *offset += 1;
		return ret;
	}
};

#endif //!_UNITY_VERSION_H_