#include <string>
#include <coreinit/debug.h>
#include <notifications/notifications.h>
#include "utils/logger.h"

bool notificationsAvailable = false;
float NOTIFICATION_FADE_OUT_TIME = 7.0f;

NMColor BACKGROUND_COLOR = {100, 100, 100, 255};

NMColor TEXT_COLOR_DEFAULT = {100, 100, 100, 255};
NMColor TEXT_COLOR_SUCCESS = {50, 205, 50, 255};

void initNotificationModule() {
	// * Ensure the notification module library is initialized
	auto res = NotificationModule_InitLibrary();
	if (res != NOTIFICATION_MODULE_RESULT_SUCCESS) {
		DEBUG_FUNCTION_LINE("Failed to initialize notification module library");
		OSFatal("Failed to initialize notification module library"); // TODO - Make this better
	} else {
		DEBUG_FUNCTION_LINE("Notification module library initialized");
	}

	notificationsAvailable = true;
}

void sendNotification(std::string notification) {
	if (!notificationsAvailable) {
		OSFatal("Nabbit: Tried to send notification before available"); // TODO - Make this better
	}

	auto res = NotificationModule_AddInfoNotificationEx(notification.c_str(), NOTIFICATION_FADE_OUT_TIME, TEXT_COLOR_SUCCESS, BACKGROUND_COLOR, nullptr, nullptr);

	if (res == NOTIFICATION_MODULE_RESULT_INVALID_ARGUMENT) {
		OSFatal("Nabbit: NOTIFICATION_MODULE_RESULT_INVALID_ARGUMENT: text was NULL"); // TODO - Make this better
	}

	if (res == NOTIFICATION_MODULE_RESULT_UNSUPPORTED_COMMAND) {
		OSFatal("Nabbit: NOTIFICATION_MODULE_RESULT_UNSUPPORTED_COMMAND: The loaded module version doesn't not support this function"); // TODO - Make this better
	}

	if (res == NOTIFICATION_MODULE_RESULT_OVERLAY_NOT_READY) {
		OSFatal("Nabbit: NOTIFICATION_MODULE_RESULT_OVERLAY_NOT_READY: The overlay is not ready. See NotificationModule_IsOverlayReady"); // TODO - Make this better
	}

	if (res == NOTIFICATION_MODULE_RESULT_ALLOCATION_FAILED) {
		OSFatal("Nabbit: NOTIFICATION_MODULE_RESULT_ALLOCATION_FAILED: Allocation of the Notification has failed"); // TODO - Make this better
	}

	if (res == NOTIFICATION_MODULE_RESULT_LIB_UNINITIALIZED) {
		OSFatal("Nabbit: NOTIFICATION_MODULE_RESULT_LIB_UNINITIALIZED: The library is not initialized"); // TODO - Make this better
	}
}