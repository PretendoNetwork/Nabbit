
#include <string>
#include <wups.h>
#include <coreinit/cache.h>
#include <gx2/surface.h>
#include "titles.h"
#include "notifications.h"
#include "utils/string_format.h"
#include "utils/logger.h"

Title current_title;

DECL_FUNCTION(uint32_t, MCP_RightCheckLaunchable, uint32_t *u1, uint32_t *u2, uint64_t title_id, uint32_t u4) {
	uint32_t result = real_MCP_RightCheckLaunchable(u1, u2, title_id, u4);

	if (result == 0 && current_title.title_id != title_id) {
		for (const auto& title : titles) {
			if (title.title_id == title_id) {
				current_title = title;
				DEBUG_FUNCTION_LINE("Launching title: %016llx, %s", current_title.title_id, current_title.name);
				sendNotification(string_format("\ue010 Medal Get - Test"));
			}
		}
	}

	return result;
}

DECL_FUNCTION(void, GX2CopyColorBufferToScanBuffer, const GX2ColorBuffer* buffer, GX2ScanTarget scanTarget) {
	if (current_title.check_medals != nullptr) {
		current_title.check_medals();
	}

	real_GX2CopyColorBufferToScanBuffer(buffer, scanTarget);
}

WUPS_MUST_REPLACE(MCP_RightCheckLaunchable, WUPS_LOADER_LIBRARY_COREINIT, MCP_RightCheckLaunchable);
WUPS_MUST_REPLACE(GX2CopyColorBufferToScanBuffer, WUPS_LOADER_LIBRARY_GX2, GX2CopyColorBufferToScanBuffer);