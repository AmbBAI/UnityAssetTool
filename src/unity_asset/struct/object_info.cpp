#include <cassert>
#include "object_info.h"

void ObjectInfo::Read(DataReader& reader)
{
	offset = reader.ReadNumber<uint32_t>();
	length = reader.ReadNumber<uint32_t>();
	typeID = reader.ReadNumber<int32_t>();
	classID = reader.ReadNumber<int16_t>();
	reader.ReadNumber<int16_t>(); //
	reader.ReadNumber<int32_t>();
}
