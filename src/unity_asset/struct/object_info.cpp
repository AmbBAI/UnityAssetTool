#include "object_info.h"

void ObjectInfo::Read(DataReader& reader, int format)
{
	offset = reader.ReadNumber<uint32_t>();
	length = reader.ReadNumber<uint32_t>();
	typeID = reader.ReadNumber<int32_t>();
	classID = reader.ReadNumber<int16_t>();
	unknown0 = reader.ReadNumber<int16_t>(); // -1
	if (format > 13) unknown1 = reader.ReadNumber<int32_t>(); //0
}
