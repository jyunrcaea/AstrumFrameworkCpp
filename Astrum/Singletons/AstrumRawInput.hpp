#pragma once
#include <vector>
#include <windows.h>
#include "AstrumSingleton.hpp"

struct AstrumRawInputInformation
{
public:
	unsigned short ScanCode;
	bool IsPressed;
	double Timestamp;
};

class AstrumRawInputSingleton : public AstrumSingleton<AstrumRawInputSingleton>
{
	friend class AstrumSingleton<AstrumRawInputSingleton>;
	friend class AstrumRawInput;

private:
	void Initialize();
	void Update(const RAWKEYBOARD& kb);
	void Clear() { inputQueue.clear(); }
	void Dispose();

public:
	const std::vector<AstrumRawInputInformation>& GetQueue() const { return inputQueue; }

private:
	std::vector<AstrumRawInputInformation> inputQueue;
};

class AstrumRawInput {
private:
	friend class AstrumWindowSingleton;

	static void Initialize() { AstrumRawInputSingleton::Instance().Initialize(); }
	static void Update(const RAWKEYBOARD& kb) { AstrumRawInputSingleton::Instance().Update(kb); }
	static void Dispose() { AstrumRawInputSingleton::Instance().Dispose(); }

private:
	friend class AstrumFrameworkSingleton;

	static void Clear() { AstrumRawInputSingleton::Instance().Clear(); }

public:
	static const std::vector<AstrumRawInputInformation>& GetQueue() { return AstrumRawInputSingleton::Instance().GetQueue(); }
};