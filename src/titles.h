#include <functional>
#include "medals/mario-kart-8.h"
#include "medals/splatoon.h"
#include "medals/super-mario-3d-world.h"

#ifndef _PATCHER_H
#define _PATCHER_H

enum REGION {
	JPN,
	USA,
	EUR
};

typedef void v();
struct Title {
	uint64_t title_id;
	char name[80];
	REGION region;
	std::function<v> check_medals;
};

static const Title titles[] = {
	{0x000500001010EB00, "MARIO KART 8", JPN, &checkMarioKart8Medals},
	{0x000500001010EC00, "MARIO KART 8", USA, &checkMarioKart8Medals},
	{0x000500001010ED00, "MARIO KART 8", EUR, &checkMarioKart8Medals},

	{0x0005000010162B00, "スプラトゥーン", JPN, &checkSplatoonMedals},
	{0x0005000010176900, "Splatoon", USA, &checkSplatoonMedals},
	{0x0005000010176A00, "Splatoon", EUR, &checkSplatoonMedals},

	{0x0005000010106100, "スーパーマリオ ３Ｄワールド", JPN, &checkSuperMario3DWorldMedals},
	{0x0005000010145C00, "Super Mario 3D World", USA, &checkSuperMario3DWorldMedals},
	{0x0005000010145D00, "Super Mario 3D World", EUR, &checkSuperMario3DWorldMedals}
};

#endif
