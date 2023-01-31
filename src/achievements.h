#ifndef _PATCHER_H
#define _PATCHER_H

typedef struct Achievement
{
	uint64_t title_id;
	char name[80];
} Achievement;

static const Achievement achievements[] = {
	{0x000500001010ec00, "MARIO KART 8"}
};

#endif
