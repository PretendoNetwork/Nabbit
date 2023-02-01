#include <cstring>
#include <mocha/mocha.h>
#include <coreinit/memorymap.h>
#include "medals/super-mario-3d-world.h"
#include "notifications.h"
#include "utils/string_format.h"
#include "utils/logger.h"

int SAVE_SLOT_ADDRESS = 0x36D3D7B4;
int COINS_ADDRESS_SLOT_1 = 0x36D3EA3C;
int COINS_ADDRESS_SLOT_2 = 0x36D3FE08;
int COINS_ADDRESS_SLOT_3 = 0x36D411D4;
int SCORE_ADDRESS_SLOT_1 = 0x36D3EB34;
int SCORE_ADDRESS_SLOT_2 = 0x36D3FF00;
int SCORE_ADDRESS_SLOT_3 = 0x36D412CC;
int WORLD_ADDRESS = 0x464E4DE0;
int LEVEL_ADDRESS = 0x464E4DDC;

bool test_medal_1_got = false;

void checkSuperMario3DWorldMedals() {
	uint8_t save_slot_buff[4];
	uint8_t world_buff[4];
	uint8_t level_buff[4];
	uint8_t coins_buff[4];
	uint8_t score_buff[4];

	uint32_t save_slot;
	uint32_t world;
	uint32_t level;
	uint32_t coins;
	uint32_t score;

	Mocha_IOSUKernelRead32(OSEffectiveToPhysical(SAVE_SLOT_ADDRESS), (uint32_t*)&save_slot_buff);
	Mocha_IOSUKernelRead32(OSEffectiveToPhysical(WORLD_ADDRESS), (uint32_t*)&world_buff);
	Mocha_IOSUKernelRead32(OSEffectiveToPhysical(LEVEL_ADDRESS), (uint32_t*)&level_buff);

	std::memcpy(&save_slot, save_slot_buff, sizeof(uint32_t));
	std::memcpy(&world, world_buff, sizeof(uint32_t));
	std::memcpy(&level, level_buff, sizeof(uint32_t));

	if (save_slot == 0) {
		Mocha_IOSUKernelRead32(OSEffectiveToPhysical(COINS_ADDRESS_SLOT_1), (uint32_t*)&coins_buff);
		Mocha_IOSUKernelRead32(OSEffectiveToPhysical(SCORE_ADDRESS_SLOT_1), (uint32_t*)&score_buff);
	}

	if (save_slot == 1) {
		Mocha_IOSUKernelRead32(OSEffectiveToPhysical(COINS_ADDRESS_SLOT_2), (uint32_t*)&coins_buff);
		Mocha_IOSUKernelRead32(OSEffectiveToPhysical(SCORE_ADDRESS_SLOT_2), (uint32_t*)&score_buff);
	}

	if (save_slot == 2) {
		Mocha_IOSUKernelRead32(OSEffectiveToPhysical(COINS_ADDRESS_SLOT_3), (uint32_t*)&coins_buff);
		Mocha_IOSUKernelRead32(OSEffectiveToPhysical(SCORE_ADDRESS_SLOT_3), (uint32_t*)&score_buff);
	}

	std::memcpy(&coins, coins_buff, sizeof(uint32_t));
	std::memcpy(&score, score_buff, sizeof(uint32_t));

	DEBUG_FUNCTION_LINE("Save slot: %d, World %d-%d, Coins - %d, Score - %d", save_slot, world, level, coins, score);

	if (!test_medal_1_got && world == 1 && level == 1 && coins == 10) {
		sendNotification(string_format("\ue010 Medal Get - Test Medal, got 10 coins on 1-1"));
		test_medal_1_got = true;
	}
}