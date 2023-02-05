#include "medals/super-mario-3d-world.h"
#include "utils/rplinfo.h"

// * These are Cemu addresses, they are wrong when on real hardware
int SAVE_SLOT_ADDRESS = 0x36D3D7B4;
int COINS_ADDRESS_SLOT_1 = 0x36D3EA3C;
int COINS_ADDRESS_SLOT_2 = 0x36D3FE08;
int COINS_ADDRESS_SLOT_3 = 0x36D411D4;
int SCORE_ADDRESS_SLOT_1 = 0x36D3EB34;
int SCORE_ADDRESS_SLOT_2 = 0x36D3FF00;
int SCORE_ADDRESS_SLOT_3 = 0x36D412CC;
int WORLD_ADDRESS = 0x464E4DE0;
int LEVEL_ADDRESS = 0x464E4DDC;

void checkSuperMario3DWorldMedals(OSDynLoad_NotifyData rpx_data) {
	// TODO - Do this
}