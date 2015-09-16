#ifndef _OBJECT_INFO_H_
#define _OBJECT_INFO_H_

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include "utils/data_reader.h"

class ObjectInfo
{
public:
	uint32_t offset = 0;
	uint32_t length = 0;
	int32_t typeID = 0;
	int16_t classID = 0;

public:
	ObjectInfo() = default;

	void Read(DataReader& reader);
};

#endif //!_OBJECT_INFO_H_