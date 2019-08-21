#pragma once
#include <functional>
#include <map>
#include <vector>
#include <windows.h>

//#define GLOBALS 0x5B28C0
#define GLOBALS 0x62D0A0

// https://github.com/erayarslan/WriteProcessMemory-Example
// http://stackoverflow.com/q/32798185
// http://stackoverflow.com/q/36018838
// http://stackoverflow.com/q/1387064
class Memory
{
public:
	Memory(const std::string& processName);
	~Memory();

	Memory(const Memory& memory) = delete;
	Memory& operator=(const Memory& other) = delete;

	int GetCurrentFrame();

	template <class T>
	std::vector<T> ReadArray(int panel, int offset, int size) {
		if (size == 0) return std::vector<T>();
		return ReadData<T>({ GLOBALS, 0x18, panel * 8, offset, 0 }, size);
	}

	template <class T>
	void WriteArray(int panel, int offset, const std::vector<T>& data) {
		if (data.size() == 0) return;
		WriteData<T>({ GLOBALS, 0x18, panel * 8, offset, 0 }, data);
	}

	template <class T>
	std::vector<T> ReadPanelData(int panel, int offset, size_t size) {
		if (size == 0) return std::vector<T>();
		return ReadData<T>({ GLOBALS, 0x18, panel * 8, offset }, size);
	}

	template <class T>
	T ReadPanelData(int panel, int offset) {
		return ReadData<T>({ GLOBALS, 0x18, panel * 8, offset }, 1)[0];
	}

	template <class T>
	void WritePanelData(int panel, int offset, const std::vector<T>& data) {
		WriteData<T>({ GLOBALS, 0x18, panel * 8, offset }, data);
	}

	void AddSigScan(const std::vector<byte>& scanBytes, const std::function<void(int index)>& scanFunc);
	int ExecuteSigScans();

	void ClearOffsets() { _computedAddresses = std::map<uintptr_t, uintptr_t>(); }

	template <class T>
	void* AllocArray(int numItems) {
		return static_cast<void*>(VirtualAllocEx(_handle, 0, numItems * sizeof(T), MEM_COMMIT, PAGE_READWRITE));
	}

	template <class T>
	void* AllocArray(size_t numItems) {
		return AllocArray<T>(static_cast<int>(numItems));
	}

private:
	template<class T>
	std::vector<T> ReadData(const std::vector<int>& offsets, size_t numItems) {
		std::vector<T> data;
		data.resize(numItems);
		for (int i=0; i<5; i++) {
			if (ReadProcessMemory(_handle, ComputeOffset(offsets), &data[0], sizeof(T) * numItems, nullptr))
			{
				return data;
			}
		}
		ThrowError();
		return {};
	}

	template <class T>
	void WriteData(const std::vector<int>& offsets, const std::vector<T>& data) {
		for (int i=0; i<5; i++) {
			if (WriteProcessMemory(_handle, ComputeOffset(offsets), &data[0], sizeof(T) * data.size(), nullptr)) {
				return;
			}
		}
		ThrowError();
	}

	void ThrowError();

	void* ComputeOffset(std::vector<int> offsets);

	std::map<uintptr_t, uintptr_t> _computedAddresses;
	uintptr_t _baseAddress = 0;
	HANDLE _handle = nullptr;
	struct SigScan {
		std::function<void(int)> scanFunc;
		bool found;
	};
	std::map<std::vector<byte>, SigScan> _sigScans;

	friend class Temp;
	friend class ChallengeRandomizer;
	friend class Randomizer;
};