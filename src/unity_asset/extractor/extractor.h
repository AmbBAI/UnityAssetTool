#ifndef _EXTRACTOR_H_
#define _EXTRACTOR_H_

#include "utils/header.h"
#include "utils/data_reader.h"

enum ClassID
{
	Texture2D = 28,
	Shader = 48,
	TextAsset = 49,
};

class Extractor
{
	std::string ext = ".bin";

public:
	Extractor() = default;
	explicit Extractor(const std::string& _ext) : ext(_ext) {}

	std::string GetObjectName(DataReader& reader);
	virtual void Extract(FileWriter& writer, DataReader& reader, size_t length);

	std::string GetFileExt() { return ext; }

	static std::map<uint16_t, std::shared_ptr<Extractor> > extractorMap;
	static void RegisterExtractor(uint16_t classID, const std::shared_ptr<Extractor>& extractor);
	static std::shared_ptr<Extractor> GetExtractor(uint16_t classID);
};

#endif //!_EXTRACTOR_H_