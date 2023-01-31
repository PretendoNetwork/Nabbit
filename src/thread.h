#pragma once
#include <functional>
#include <coreinit/messagequeue.h>
#include <coreinit/thread.h>
#include <notifications/notifications.h>

typedef void v();

struct ThreadData {
	OSThread *thread;
	void *stack;
	OSMessageQueue queue;
	OSMessage messages[2];
	bool ready;
	char threadName[0x50];
	std::function<v> checkFunction;
};

struct SwapTitleMessage {
	uint64_t title_id;
	std::function<v> checkFunction;
};

extern ThreadData gThreadData;

#define COMMAND_STOP_THREAD 0xFFFFFFFF
#define COMMAND_SWAP_TITLE  0x00000001

void startThread();
bool sendMessageToThread(SwapTitleMessage*);