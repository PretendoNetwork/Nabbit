#include <functional>
#include <string>
#include "utils/rplinfo.h"
#include "medals/mario-kart-8.h"
#include "medals/splatoon.h"
#include "medals/super-mario-3d-world.h"
#include "medals/super-meat-boy.h"

#ifndef _PATCHER_H
#define _PATCHER_H

enum REGION {
	JPN,
	USA,
	EUR
};

typedef void v(OSDynLoad_NotifyData);
struct Title {
	uint64_t title_id;
	std::string name;
	std::string rpx_name;
	REGION region;
	std::function<v> check_medals;
	bool initialized;
	OSDynLoad_NotifyData rpx_data;
};

static const Title titles[] = {
	{0x000500001010EB00, "MARIO KART 8", "Turbo.rpx", JPN, &checkMarioKart8Medals, false, nullptr},
	{0x000500001010EC00, "MARIO KART 8", "Turbo.rpx", USA, &checkMarioKart8Medals, false, nullptr},
	{0x000500001010ED00, "MARIO KART 8", "Turbo.rpx", EUR, &checkMarioKart8Medals, false, nullptr},

	{0x0005000010162B00, "スプラトゥーン", "Gambit.rpx", JPN, &checkSplatoonMedals, false, nullptr},
	{0x0005000010176900, "Splatoon", "Gambit.rpx", USA, &checkSplatoonMedals, false, nullptr},
	{0x0005000010176A00, "Splatoon", "Gambit.rpx", EUR, &checkSplatoonMedals, false, nullptr},

	{0x0005000010106100, "スーパーマリオ ３Ｄワールド", "RedCarpet.rpx", JPN, &checkSuperMario3DWorldMedals, false, nullptr},
	{0x0005000010145C00, "Super Mario 3D World", "RedCarpet.rpx", USA, &checkSuperMario3DWorldMedals, false, nullptr},
	{0x0005000010145D00, "Super Mario 3D World", "RedCarpet.rpx", EUR, &checkSuperMario3DWorldMedals, false, nullptr},

	{0x00050000101F3F00, "Super Meat Boy", "SuperMeatBoy.rpx", USA, &checkSuperMeatBoyMedals, false, nullptr},
	{0x00050000101F4000, "Super Meat Boy", "SuperMeatBoy.rpx", EUR, &checkSuperMeatBoyMedals, false, nullptr},
};

#endif
