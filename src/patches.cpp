
#include <string>
#include <wups.h>
#include <coreinit/cache.h>
#include "titles.h"
#include "notifications.h"
#include "thread.h"
#include "utils/string_format.h"
#include "utils/logger.h"

uint64_t current_title_id;

DECL_FUNCTION(uint32_t, MCP_RightCheckLaunchable, uint32_t *u1, uint32_t *u2, uint64_t title_id, uint32_t u4) {
	uint32_t result = real_MCP_RightCheckLaunchable(u1, u2, title_id, u4);

	if (result == 0 && current_title_id != title_id) {
		current_title_id = title_id;

		for (const auto& title : titles) {
			if (title.title_id == current_title_id) {
				DEBUG_FUNCTION_LINE("Launching title: %016llx, %s", current_title_id, title.name);

				SwapTitleMessage* param;
				param = (SwapTitleMessage*) malloc(sizeof(SwapTitleMessage));
				if (!param) {
					DEBUG_FUNCTION_LINE("Creating param failed"); // TODO - Make this better
					OSMemoryBarrier();
				}

				param->title_id = current_title_id;
				param->checkFunction = title.checkFunction;

				bool res = sendMessageToThread(param);
				if (!res) {
					free(param);
					DEBUG_FUNCTION_LINE("Sending message to thread failed"); // TODO - Make this better
				}

				OSMemoryBarrier();
			}
		}
	}

	return result;
}

WUPS_MUST_REPLACE(MCP_RightCheckLaunchable, WUPS_LOADER_LIBRARY_COREINIT, MCP_RightCheckLaunchable);