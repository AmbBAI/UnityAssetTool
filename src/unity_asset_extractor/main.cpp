#include "utils/file_reader.h"
#include "struct/asset_file.h"
#include "extractor/extractor.h"
#include "extractor/textasset_extractor.h"

int main()
{
	BaseClass::LoadDefaultStringTable("strings.dat");

	std::string file = "test5.1.assets";
	FileReader fileReader(file);
	if (!fileReader.isValid())
	{
		printf("%s open fault!", file.c_str());
		return 0;
	}

	AssetFile assetFile;
	assetFile.Read(fileReader);
	assert(assetFile.header.format == 9 || assetFile.header.format == 15);
	if (!(assetFile.header.format == 9 || assetFile.header.format == 15))
	{
		printf("%s format not support!", file.c_str());
		return 0;
	}

	Extractor::RegisterExtractor(ClassID::TextAsset, std::make_shared<TextAssetExtractor>(".txt"));
	Extractor::RegisterExtractor(ClassID::Shader, std::make_shared<TextAssetExtractor>(".shader"));

	fileReader.Seek(0);
	assetFile.LoadAllObjects(fileReader, [&file](const ObjectInfo& objectInfo, DataReader& objectReader)
	{
		auto extractor = Extractor::GetExtractor(objectInfo.classID);
		std::string name = extractor->GetObjectName(objectReader);
		if (name.empty()) name = std::to_string(objectInfo.pathID);
		std::string path = "output/" + file + " - " + name + "." + std::to_string(objectInfo.classID);
		FileWriter writer(path);
		extractor->Extract(writer, objectReader, objectInfo.length);
		writer.Close();
	});
}