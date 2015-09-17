#ifndef _DATA_READER_H_
#define _DATA_READER_H_

#include <cstdint>
#include <string>
#include <cassert>
#include <memory>
#include "file_writer.h"
extern "C" {
#include "LzmaDec.h"
}

enum ByteOrder
{
	ByteOrder_LittleEndian,
	ByteOrder_BigEndian,
};

class DataReader
{
protected:
	uint8_t* data = nullptr;
	size_t offset = 0;
	size_t size = 0;
	ByteOrder byteOrder = ByteOrder_LittleEndian;

public:
	DataReader() = default;
	explicit DataReader(uint8_t* dataBuffer, size_t size)
	{
		this->data = dataBuffer;
		this->size = size;
	}
	DataReader(DataReader&& other) { *this = std::move(other); }
	virtual ~DataReader() { Close(); }
	virtual void Close()
	{
		if (data != nullptr)
		{
			delete data;
			data = nullptr;
		}
		offset = 0;
		size = 0;
	}

	bool isValid() { return data != nullptr; }

	void SetByteOrder(ByteOrder byteOrder) { this->byteOrder = byteOrder; }
	ByteOrder GetByteOrder() const { return byteOrder; }

	virtual size_t GetSize() const { return size; }
	virtual size_t Tell() const { return offset; }
	virtual void Seek(size_t offset) { this->offset = offset; }

	virtual std::string ReadString()
	{
		std::string ret = (const char*)(data + offset);
		offset += ret.length() + 1;
		return ret;
	}

	virtual void ReadBytes(uint8_t* bytes, size_t size)
	{
		std::memcpy(bytes, data + offset, size);
		offset += size;
	}

	virtual uint8_t ReadByte()
	{
		uint8_t ret = *(data + offset);
		offset += 1;
		return ret;
	}

	template<typename Type>
	Type ReadNumber()
	{
		Type ret = 0;
		uint8_t* ptr = (uint8_t*)&ret;
		ReadBytes(ptr, sizeof(Type));
		if (byteOrder == ByteOrder_BigEndian) std::reverse(ptr, ptr + sizeof(Type));
		return ret;
	}

	DataReader& operator =(DataReader&& other)
	{
		if (this == &other) return *this;
		if (data != nullptr)
		{
			delete data;
			data = nullptr;
		}

		data = other.data;
		offset = other.offset;
		size = other.size;
		byteOrder = other.byteOrder;

		other.data = nullptr;
		other.offset = 0;
		other.size = 0;
		other.byteOrder = ByteOrder_LittleEndian;

		return *this;
	}

	DataReader Decompress()
	{
		SetByteOrder(ByteOrder_LittleEndian);
		uint8_t propData[LZMA_PROPS_SIZE];
		ReadBytes(propData, LZMA_PROPS_SIZE);
		SizeT uncompressSize = (SizeT)ReadNumber<uint32_t>();
		uint8_t* uncompressData = new uint8_t[uncompressSize];
		ReadNumber<uint32_t>(); // finish mode?
		SizeT compressedSize = (SizeT)(size - offset);
		ELzmaStatus lzmaStatus = LZMA_STATUS_NOT_SPECIFIED;

		static ISzAlloc lzmaAlloc = {
			[](void* p, size_t size) { p = p; return malloc(size); },
			[](void* p, void *address) { p = p; free(address); } };

		LzmaDecode(
			uncompressData, (SizeT*)&uncompressSize,
			data + offset, (SizeT*)&compressedSize,
			propData, LZMA_PROPS_SIZE,
			LZMA_FINISH_ANY, &lzmaStatus, &lzmaAlloc);

		return DataReader(uncompressData, uncompressSize);
	}

	bool WriteFile(std::string file, size_t offset, size_t size)
	{
		FileWriter fileWriter(file);
		if (!fileWriter.isValid()) return false;

		fileWriter.WriteBytes(data + offset, size);
		fileWriter.Close();
		return true;
	}
};

#endif //!_DATA_READER_H_