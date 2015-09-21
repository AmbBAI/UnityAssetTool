#include "struct/assetbundle_reader.h"

int main()
{
	BaseClass::LoadDefaultStringTable("strings.dat");

	FileReader fileReader("test5.1_lzma.assetbundle");

	AssetbundleReader assertbundleReader;
	assertbundleReader.ReadHeader(fileReader);
	
	auto headerSize = assertbundleReader.header.headerSize;
	DataReader content = std::move(fileReader.ReadData(headerSize));
	fileReader.Close();

	DataReader dataReader;
	if (assertbundleReader.header.IsCompressed())
		dataReader = content.Decompress();
	else
		dataReader = std::move(content);
	content.Close();

	auto assetFileList = assertbundleReader.ReadAssetFiles(dataReader);
	for (auto& keyValPair : assetFileList)
	{
		auto& entryInfo = keyValPair.first;
		auto& assetFile = keyValPair.second;
		dataReader.Seek(entryInfo.offset);
		assetFile.LoadAllObjects(dataReader, [&entryInfo](const ObjectInfo& objectInfo, DataReader& objectReader)
		{
			std::string path = "output/" + entryInfo.name + " - " + std::to_string(objectInfo.pathID);
			objectReader.WriteFile(path, objectReader.Tell(), objectInfo.length);
		});
	}
}