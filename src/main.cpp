#include <wups.h>
#include <mocha/mocha.h>
#include <notifications/notifications.h>
#include "notifications.h"
#include "utils/logger.h"

// Mandatory plugin information.
WUPS_PLUGIN_NAME("Nabbit");
WUPS_PLUGIN_DESCRIPTION("Pretendo Network Medals");
WUPS_PLUGIN_VERSION("v0.1");
WUPS_PLUGIN_AUTHOR("Pretendo contributors");
WUPS_PLUGIN_LICENSE("AGPL3");

// Gets called once the loader exists.
INITIALIZE_PLUGIN() {
	initLogging();

	DEBUG_FUNCTION_LINE("Init");

	initNotificationModule();
}

DEINITIALIZE_PLUGIN() {
	deinitLogging();
	NotificationModule_DeInitLibrary();
}