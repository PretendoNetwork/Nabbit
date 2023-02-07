
#include "medals/super-meat-boy.h"
#include "notifications.h"
#include "utils/rplinfo.h"
#include "utils/string_format.h"
#include "utils/logger.h"

bool super_meat_boy_test_medal_1_got = false;

int CURRENT_LEVEL_OFFSET = 0x2B718; // * uint32
int TOTAL_DEATHS_OFFSET = 0x5B68B; // * uint8

void checkSuperMeatBoyMedals(OSDynLoad_NotifyData rpx_data) {
	uint32_t* level_ptr = (uint32_t*)(rpx_data.dataAddr + CURRENT_LEVEL_OFFSET);
	auto level = *level_ptr;

	if (!super_meat_boy_test_medal_1_got && level == 3) {
		super_meat_boy_test_medal_1_got = true;
		sendNotification(string_format("\ue010 Medal Get - Test Medal, reach level 3!"));
	}

	DEBUG_FUNCTION_LINE("Level - %d", level);
}