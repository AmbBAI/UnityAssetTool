#ifndef _FILE_WRITER_H_
#define _FILE_WRITER_H_

#include "utils/header.h"
#include "utils/data_reader.h"

class FileWriter
{
	FILE* filePtr = nullptr;
	ByteOrder byteOrder = ByteOrder_LittleEndian;

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

	template<typename Type>
	void WriteNumber(Type number)
	{
		static uint16_t _byteOrderMagic = 0x0102;
		static ByteOrder systemByteOrder =
			(*(uint8_t*)&_byteOrderMagic != 0x01) ? ByteOrder_LittleEndian : ByteOrder_BigEndian;

		uint8_t* ptr = (uint8_t*)&number;
		if (byteOrder != systemByteOrder) std::reverse(ptr, ptr + sizeof(Type));
		WriteBytes(ptr, sizeof(Type));
	}

	void Print(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		vfprintf(filePtr, format, args);
		va_end(args);
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