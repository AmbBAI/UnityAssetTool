#include "utils/file_reader.h"
#include "struct/asset_file.h"
#include "struct/type_tree_database.h"
#include "extractor/extractor.h"
#include "extractor/textasset_extractor.h"

#include "boost/filesystem.hpp"
using namespace boost;

void ExtractAsset(DataReader& dataReader, const filesystem::path& outputDir);

int main(int argc, char *argv)
{
	StringTable::LoadDefaultStringTable("strings.dat");
	TypeTreeDatabase::LoadTypeTreeDatabase(9, "types9.dat");
	TypeTreeDatabase::LoadTypeTreeDatabase(15, "types15.dat");
	//Extractor::RegisterExtractor(ClassID::TextAsset, std::make_shared<TextAssetExtractor>(".txt"));
	//Extractor::RegisterExtractor(ClassID::Shader, std::make_shared<TextAssetExtractor>(".shader"));

	filesystem::path workDir;
	if (argc == 1) workDir = filesystem::current_path();
	else workDir = filesystem::path((filesystem::path::value_type*)argv[1]);

	if (!filesystem::exists(workDir))
	{
		printf("%s not exist!", workDir.string().c_str());
		return 0;
	}

	filesystem::path outputRoot = workDir;
	outputRoot.append("Output/");

	std::vector<filesystem::path> assets;
	std::map<filesystem::path, int> splitAssets;
	filesystem::recursive_directory_iterator itor(workDir);
	while (itor != filesystem::end(itor))
	{
		filesystem::path path = itor->path();
		++itor;

		if (filesystem::is_directory(path)) continue;

		std::string ext = path.extension().string();
		if (ext == ".uafb"
			|| ext == ".exe"
			|| ext == ".dll"
			|| ext == ".png"
			|| ext == ".xml"
			|| ext == ".resource")
		{
			printf("ignore file %s\n", path.string().c_str());
			continue;
		}
		else if (ext.find(".split") != ext.npos)
		{
			path.replace_extension(".split");
			int partID = std::stoi(ext.substr(6));
			auto itor = splitAssets.find(path);
			if (itor == splitAssets.end() || itor->second < partID + 1)
			{
				splitAssets[path] = partID + 1;
			}
		}
		else
		{
			assets.push_back(path);
		}
	}

	// assets
	for (auto& path : assets)
	{
		try
		{
			printf("%s\n", path.string().c_str());
			FileReader fileReader(path.string());
			if (!fileReader.isValid())
			{
				throw std::exception((path.string() + " open fault!").c_str());
			}

			filesystem::path outputDir = outputRoot;
			outputDir.append(path.filename().string() + "/");

			ExtractAsset(fileReader, outputDir);
		}
		catch (std::exception e)
		{
			printf("%s\n", e.what());
		}
	}

	// split assets
	for (auto keyValuePair : splitAssets)
	{
		auto path = keyValuePair.first;
		auto partCount = keyValuePair.second;

		std::vector<std::shared_ptr<DataReader> > fileReaderList;
		for (int i = 0; i < partCount; ++i)
		{
			path.replace_extension(".split" + std::to_string(i));
			auto fileReaderPtr = std::make_shared<FileReader>(path.string());
			if (!fileReaderPtr->isValid())
			{
				fileReaderList.clear();
				puts((path.string() + " open fault!").c_str());
				break;
			}
			fileReaderList.emplace_back(fileReaderPtr);
		}

		if (!fileReaderList.empty())
		{
			DataReader dataReader = DataReader::Join(fileReaderList);

			path.replace_extension();
			printf("%s\n", path.string().c_str());
			filesystem::path outputDir = outputRoot;
			outputDir.append(path.filename().string() + "/");

			ExtractAsset(dataReader, outputDir);
		}
	}
}

void ExtractAsset(DataReader& dataReader, const filesystem::path& outputDir)
{
	AssetFile assetFile;
	assetFile.Read(dataReader);
	if (!assetFile.IsValid())
	{
		throw std::exception("format not support!");
	}

	dataReader.Seek(0);
	assetFile.LoadAllObjects(dataReader, [&outputDir](const ObjectInfo& objectInfo, DataReader& objectReader)
	{
		//std::string name = extractor->GetObjectName(objectReader);
		//if (name.empty()) name = std::to_string(objectInfo.pathID);
		std::string name = std::to_string(objectInfo.pathID);

		filesystem::path objectFile = outputDir;
		objectFile.append(name + "." + std::to_string(objectInfo.classID) + ".uafb");
		filesystem::create_directories(outputDir);
		FileWriter writer(objectFile.string());
		Extractor::DumpBinary(writer, objectReader, objectInfo.length);
		writer.Close();
	});
}

