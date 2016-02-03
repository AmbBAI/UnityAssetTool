#include "utils/file_reader.h"
#include "struct/assetbundle_reader.h"
#include "struct/asset_file.h"
#include "struct/type_tree_database.h"
#include "extractor/extractor.h"

#include "boost/filesystem.hpp"
using namespace boost;

void ExtractAsset(DataReader& dataReader, const filesystem::path& outputDir);
void ExtractAssetBundle(FileReader& fileReader, const filesystem::path& outputDir);
filesystem::path workDir;

int main(int argc, char *argv)
{
	StringTable::LoadDefaultStringTable("strings.dat");

	if (argc == 1) workDir = filesystem::current_path();
	else workDir = filesystem::path((filesystem::path::value_type*)argv[1]);

	if (!filesystem::exists(workDir))
	{
		printf("%s not exist!", workDir.string().c_str());
		return 0;
	}

	filesystem::path outputRoot = workDir;
	outputRoot.append("output");

	std::vector<filesystem::path> assetbundles;
	std::map<filesystem::path, int> splitAssets;
	filesystem::recursive_directory_iterator itor(workDir);
	while (itor != filesystem::end(itor))
	{
		filesystem::path path = itor->path();
		++itor;

		if (filesystem::is_directory(path)) continue;

		std::string ext = path.extension().string();
		if (ext != ".assetbundle")
		{
			printf("ignore file %s\n", path.string().c_str());
			continue;
		}

		assetbundles.push_back(path);
	}

	for (auto& path : assetbundles)
	{
		try
		{
			puts(filesystem::relative(path, workDir).string().c_str());
			std::string pathStr = path.string();
			FileReader fileReader(pathStr);
			if (!fileReader.isValid())
			{
				throw std::exception((pathStr + " open fault!").c_str());
			}

			filesystem::path outputDir = outputRoot;
			outputDir.append(filesystem::relative(path, workDir).string());

			ExtractAssetBundle(fileReader, outputDir);
		}
		catch (std::exception e)
		{
			printf("%s\n", e.what());
		}
	}
}

void ExtractAssetBundle(FileReader& fileReader, const filesystem::path& outputDir)
{
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
	int autoID = 1;
	filesystem::create_directories(outputDir);
	for (auto& keyValPair : assetFileList)
	{
		auto& entryInfo = keyValPair.first;
		auto& assetFile = keyValPair.second;
		dataReader.Seek(entryInfo.offset);
		assetFile.LoadAllObjects(dataReader, [&autoID, &outputDir](const ObjectInfo& objectInfo, DataReader& objectReader)
		{
			std::string name = Extractor::GetObjectName(objectReader);
			if (!filesystem::portable_file_name(name)) name = std::to_string(objectInfo.pathID);

			filesystem::path objectFile = outputDir;
			objectFile.append(std::to_string(autoID) + "-" + name + "." + std::to_string(objectInfo.classID) + ".uafb");
			puts(filesystem::relative(objectFile, workDir).string().c_str());
			FileWriter writer(objectFile.string());
			Extractor::DumpBinary(writer, objectReader, objectInfo.length);
			writer.Close();
		});
		autoID += 1;
	}
}

