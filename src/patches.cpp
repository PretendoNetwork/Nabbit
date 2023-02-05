
#include <wups.h>
#include <coreinit/title.h>
#include <gx2/surface.h>
#include "titles.h"
#include "utils/rplinfo.h"
#include "utils/logger.h"

Title current_title;

ON_APPLICATION_START() {
	current_title = Title(); // * Reset current title

	auto title_id = OSGetTitleID();

	for (const auto& title : titles) {
		if (title.title_id == title_id) {
			current_title = title;

			auto rpl_info = TryGetRPLInfo();
			if (!rpl_info) {
				DEBUG_FUNCTION_LINE("Failed to get RPL info");
				return;
			}

			rplinfo rpls = *rpl_info;
			auto rpx = FindRPL(rpls, current_title.rpx_name);
			if (!rpx) {
				DEBUG_FUNCTION_LINE("Failed to find %s", current_title.rpx_name);
				return;
			}

			current_title.rpx_data = *rpx;

			DEBUG_FUNCTION_LINE("Launching title: %016llx, %s", current_title.title_id, current_title.name);

			break;
		}
	}
}

DECL_FUNCTION(void, GX2CopyColorBufferToScanBuffer, const GX2ColorBuffer* buffer, GX2ScanTarget scanTarget) {
	if (current_title.check_medals != nullptr) {
		current_title.check_medals(current_title.rpx_data);
	}

	real_GX2CopyColorBufferToScanBuffer(buffer, scanTarget);
}

WUPS_MUST_REPLACE(GX2CopyColorBufferToScanBuffer, WUPS_LOADER_LIBRARY_GX2, GX2CopyColorBufferToScanBuffer);