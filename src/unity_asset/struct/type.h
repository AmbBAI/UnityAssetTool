#ifndef _TYPE_H_
#define _TYPE_H_

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "utils/data_reader.h"

class Type
{
public:
	uint16_t version = 0;
	uint8_t treeLevel = 0;
	bool isArray = 0;
	int32_t typeOffset = 0;
	std::string type;
	int32_t nameOffset = 0;
	std::string name;
	uint32_t size = 0;
	uint32_t index = 0;
	uint32_t metaFlag = 0;

public:
	Type() = default;

	void Read(DataReader& reader, int format);
};

#endif //!_TYPE_H_