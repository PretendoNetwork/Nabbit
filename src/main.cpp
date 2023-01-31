#include <string>
#include <wups.h>
#include <notifications/notifications.h>
#include "notifications.h"
#include "thread.h"
#include "utils/logger.h"

// Mandatory plugin information.
WUPS_PLUGIN_NAME("Nabbit");
WUPS_PLUGIN_DESCRIPTION("Pretendo Network Patcher");
WUPS_PLUGIN_VERSION("v0.1");
WUPS_PLUGIN_AUTHOR("Pretendo contributors");
WUPS_PLUGIN_LICENSE("ISC");

// Gets called once the loader exists.
INITIALIZE_PLUGIN() {
	WHBLogUdpInit();
	DEBUG_FUNCTION_LINE("Init");
	initNotificationModule();
}

DEINITIALIZE_PLUGIN() {
	NotificationModule_DeInitLibrary();
}

ON_APPLICATION_START() {
	DEBUG_FUNCTION_LINE("Start");
	startThread();
}