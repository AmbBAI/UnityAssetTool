#include <cstdint>
#include <cstdlib>
#include <string>
#include <memory>
#include "struct/assetbundle_reader.h"

int main()
{
	FileReader fileReader("test4.6.assetbundle");

	AssetbundleReader assertbundleReader;
	assertbundleReader.ReadHeader(fileReader);
	
	auto headerSize = assertbundleReader.header.headerSize;
	DataReader content = std::move(fileReader.ReadData(headerSize));
	fileReader.Close();

	DataReader dataReader;
	if (assertbundleReader.header.IsCompressed())
		dataReader = DataReader::Decompress(content);
	else
		dataReader = std::move(content);
	content.Close();

	auto assetFileList = assertbundleReader.ReadAssetFiles(dataReader);
	for (auto& assetFile : assetFileList)
	{
		puts(assetFile.name.c_str());
		//assetFile.metaData.objectInfoMap;
	}
}