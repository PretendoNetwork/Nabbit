#include <functional>
#include "medals/mario-kart-8.h"
#include "medals/splatoon.h"

#ifndef _PATCHER_H
#define _PATCHER_H

typedef void v();
typedef struct Titles
{
	uint64_t title_id;
	char name[80];
	std::function<v> checkFunction;
} Titles;

static const Titles titles[] = {
	{0x000500001010EC00, "MARIO KART 8", &checkMarioKart8Medals},
	{0x0005000010176900, "Splatoon", &checkSplatoonMedals}
};

#endif
