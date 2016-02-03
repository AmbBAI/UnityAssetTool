#ifndef _EXTRACTOR_H_
#define _EXTRACTOR_H_

#include "utils/header.h"
#include "utils/data_reader.h"
#include "struct/type_tree.h"

enum ClassID
{
	Texture2D = 28,
	Shader = 48,
	TextAsset = 49,
};

class Extractor
{
public:
	Extractor() = default;

	virtual void Extract(FileWriter& writer, DataReader& reader, size_t length);
	virtual void DumpText(FileWriter& writer, DataReader& reader, size_t length, const TypeTree& typeTree, int32_t classID);
	static void DumpBinary(FileWriter& writer, DataReader& reader, size_t length);
	static std::string GetObjectName(DataReader& reader);

private:
	static std::map<uint16_t, std::shared_ptr<Extractor> > extractorMap;

public:
	static void RegisterExtractor(uint16_t classID, const std::shared_ptr<Extractor>& extractor);
	static std::shared_ptr<Extractor> GetExtractor(uint16_t classID);
};

#endif //!_EXTRACTOR_H_