#ifndef _TEXTASSET_EXTRACTOR_H_
#define _TEXTASSET_EXTRACTOR_H_

#include "utils/header.h"
#include "utils/data_reader.h"
#include "extractor/extractor.h"

class TextAssetExtractor : public Extractor
{
public:
	TextAssetExtractor() = default;
	explicit TextAssetExtractor(const std::string& _ext) : Extractor(_ext) {}

	void Extract(FileWriter& writer, DataReader& reader, size_t length) override;
};

#endif //!_TEXTASSET_EXTRACTOR_H_