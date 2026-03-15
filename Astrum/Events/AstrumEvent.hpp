#pragma once
#include <vector>

class AstrumEvent
{
	struct ReceiverTicket {

	};

public:
	void AddReceiver(void func()) {
		receivers.emplace_back(func);
	}
	void RemoveReceiver() {

	}

private:
	std::vector<void()> receivers;
};