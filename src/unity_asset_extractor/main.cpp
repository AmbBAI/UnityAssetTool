#include "utils/file_reader.h"
#include "struct/asset_file.h"

int main()
{
	BaseClass::LoadDefaultStringTable("strings.dat");

	std::string file = "test4.6.assets";
	FileReader fileReader(file);

	AssetFile assetFile;
	assetFile.Read(fileReader);

	fileReader.Seek(0);
	assetFile.LoadAllObjects(fileReader, [&file](const ObjectInfo& objectInfo, DataReader& objectReader)
	{
		std::string path = "output/" + file + " - " + std::to_string(objectInfo.pathID);
		objectReader.WriteFile(path, objectReader.Tell(), objectInfo.length);
	});
}