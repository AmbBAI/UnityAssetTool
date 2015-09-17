#ifndef _FILE_WRITER_H_
#define _FILE_WRITER_H_

#include <cstdint>
#include <string>
#include <cassert>
#include <memory>
#include "utils/data_reader.h"

class FileWriter
{
	FILE* filePtr = nullptr;

public:
	FileWriter() = default;
	explicit FileWriter(const std::string& file)
	{
		filePtr = fopen(file.c_str(), "wb");
		assert(filePtr != nullptr);
	}
	FileWriter(FileWriter&& other) { *this = std::move(other); }
	virtual ~FileWriter() { Close(); }
	void Close()
	{
		if (filePtr != nullptr)
		{
			fclose(filePtr);
			filePtr = nullptr;
		}
	}

	bool isValid() { return filePtr != nullptr; }

	void WriteString(std::string& data)
	{
		fwrite(data.c_str(), 1, data.length(), filePtr);
		fputc(0, filePtr);
	}

	void WriteBytes(uint8_t* bytes, size_t size)
	{
		fwrite(bytes, 1, size, filePtr);
	}

	void WriteByte(uint8_t byte)
	{
		fputc((int)byte, filePtr);
	}

	FileWriter& operator =(FileWriter&& other)
	{
		if (this == &other) return *this;
		if (filePtr != nullptr)
		{
			fclose(filePtr);
			filePtr = nullptr;
		}

		filePtr = other.filePtr;
		other.filePtr = nullptr;
		return *this;
	}
};

#endif //!_FILE_WRITER_H_