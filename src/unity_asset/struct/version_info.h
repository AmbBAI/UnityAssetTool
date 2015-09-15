#ifndef _VERSION_INFO_H_
#define _VERSION_INFO_H_

#include <cstdint>
#include "struct/unity_version.h"

struct VersionInfo
{
public:
	UnityVersion playerVersion;
	UnityVersion engineVersion;
	// 5 = 1.2 - 2.0
	// 6 = 2.1 - 2.6
	// 7 = 3.0 (?)
	// 8 = 3.1 - 3.4
	// 9 = 3.5 - 4.5
	// 11 = pre-5.0
	// 12 = pre-5.0
	// 13 = pre-5.0
	// 14 = 5.0
	// 15 = 5.0 (p3 and newer)
	int32_t assetVersion = 0;
};

#endif //!_VERSION_INFO_H_