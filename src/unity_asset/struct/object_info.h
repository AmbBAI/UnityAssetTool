#ifndef _OBJECT_INFO_H_
#define _OBJECT_INFO_H_

#include "utils/header.h"
#include "utils/data_reader.h"

class ObjectInfo
{
public:
	uint64_t pathID = 0;
	uint32_t offset = 0;
	uint32_t length = 0;
	int32_t typeID = 0;
	int16_t classID = 0;
	int16_t unknown0 = 0;
	int32_t unknown1 = 0;

public:
	ObjectInfo() = default;

	void Read(DataReader& reader, int format);
};

#endif //!_OBJECT_INFO_H_