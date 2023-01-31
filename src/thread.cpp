#include <coreinit/cache.h>
#include <coreinit/debug.h>
#include <malloc.h>
#include "thread.h"
#include "notifications.h"
#include "utils/string_format.h"
#include "utils/logger.h"

ThreadData gThreadData;

static int32_t threadCallback([[maybe_unused]] int argc, const char **argv) {
	auto *magic = ((ThreadData*) argv);

	constexpr int32_t messageSize = sizeof(magic->messages) / sizeof(magic->messages[0]);
	OSInitMessageQueue(&magic->queue, magic->messages, messageSize);
	OSMessage recv;
	while (OSReceiveMessage(&magic->queue, &recv, OS_MESSAGE_FLAGS_BLOCKING)) {
		if (recv.args[0] == COMMAND_SWAP_TITLE) {
			auto *param = (SwapTitleMessage*) recv.message;

			// TODO - CHECK FOR MEDALS BASED ON TITLE ID?

			sendNotification(string_format("\ue010 Medal Get - Test"));
			DEBUG_FUNCTION_LINE("HELLO FROM THREAD");

			// TODO - Run the new check function in a loop
			//while(true) {
			//
			//}

			OSMemoryBarrier();
			free(param);
		}
	}

	return 0;
}

void startThread() {
	auto stackSize = 16 * 1024;

	auto *threadData = &gThreadData;
	memset(threadData, 0, sizeof(*threadData));
	threadData->ready  = false;
	threadData->thread = (OSThread *) memalign(8, sizeof(OSThread));
	if (!threadData->thread) {
		DEBUG_FUNCTION_LINE("Failed to allocate threadData");
		OSFatal("Nabbit: Failed to allocate IO Thread");
		return;
	}
	threadData->stack = (uint8_t *) memalign(0x20, stackSize);
	if (!threadData->thread) {
		free(threadData->thread);
		DEBUG_FUNCTION_LINE("Failed to allocate threadData stack");
		OSFatal("Nabbit: Failed to allocate IO Thread stack");
		return;
	}

	OSMemoryBarrier();

	if (!OSCreateThread(threadData->thread, &threadCallback, 1, (char *) threadData, reinterpret_cast<void *>((uint32_t) threadData->stack + stackSize), stackSize, 31, OS_THREAD_ATTRIB_AFFINITY_ANY)) {
		free(threadData->thread);
		free(threadData->stack);
		threadData->ready = false;
		DEBUG_FUNCTION_LINE("failed to create threadData");
		OSFatal("Nabbit: Failed to create threadData");
	}

	strncpy(threadData->threadName, "Medals Thread", sizeof(threadData->threadName) - 1);
	OSSetThreadName(threadData->thread, threadData->threadName);
	OSResumeThread(threadData->thread);
	threadData->ready = true;

	//gThreadsRunning = true;
	OSMemoryBarrier();
}

bool sendMessageToThread(SwapTitleMessage* param) {
	auto *curThread = &gThreadData;
	if (curThread->ready) {
		OSMessage send;
		send.message = param;
		send.args[0] = COMMAND_SWAP_TITLE;
		OSMemoryBarrier();
		return OSSendMessage(&curThread->queue, &send, OS_MESSAGE_FLAGS_NONE);
	} else {
		DEBUG_FUNCTION_LINE("Thread not ready");
	}
	return false;
}