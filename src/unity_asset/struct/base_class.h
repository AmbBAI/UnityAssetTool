#ifndef _BASE_CLASS_H_
#define _BASE_CLASS_H_

#include <cstdint>
#include "utils/data_reader.h"
#include "struct/type_node.h"

struct BaseClass
{
	int32_t classID = 0;
	uint8_t scriptID[16] = { 0 };
	uint8_t oldTypeHash[16] = { 0 };
	TypeNode typeTree;
};

#endif //!_BASE_CLASS_H_