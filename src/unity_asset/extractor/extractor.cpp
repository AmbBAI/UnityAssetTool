#include "extractor.h"

std::string Extractor::GetObjectName(DataReader& reader)
{
	std::string name;
	try
	{
		size_t originOffset = reader.Tell();
		reader.SetByteOrder(ByteOrder_LittleEndian);

		uint32_t len = reader.ReadNumber<uint32_t>();
		if (len > 100)
		{
			throw std::exception("error name");
		}

		if (len > 0)
		{
			name.assign(len, '\0');
			reader.ReadBytes((uint8_t*)name.c_str(), len);
		}

		reader.Seek(originOffset);
	}
	catch (std::exception e)
	{
		return "";
	}
	return name;
}

void Extractor::Extract(FileWriter& writer, DataReader& reader, size_t length)
{
}

void Extractor::DumpText(FileWriter& writer, DataReader& reader, size_t length, const TypeTree& typeTree, int32_t classID)
{
	//
}

void Extractor::DumpBinary(FileWriter& writer, DataReader& reader, size_t length)
{
	reader.WriteFile(writer, reader.Tell(), length);
}

std::map<uint16_t, std::shared_ptr<Extractor> > Extractor::extractorMap;

void Extractor::RegisterExtractor(uint16_t classID, const std::shared_ptr<Extractor>& extractor)
{
	extractorMap[classID] = extractor;
}

std::shared_ptr<Extractor> Extractor::GetExtractor(uint16_t classID)
{
	static std::shared_ptr<Extractor> defaultExtractor = std::make_shared<Extractor>();
	auto& itor = extractorMap.find(classID);
	if (itor != extractorMap.end()) return itor->second;
	return defaultExtractor;
}
