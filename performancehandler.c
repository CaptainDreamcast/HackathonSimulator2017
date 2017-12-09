#include "performancehandler.h"

static struct {
	int mValues[4];
	int mAnimationIDs[4][50];

	
} gData;

static double gOldPositionDelta[] = {
	0, 0, 0,
	25, 30, 0,
	60, 60, 0,
};

static double gPositionDelta[] = {
	70, 0, 0,
	70, 30, 0,
	70, 60, 0,
};

void addPerformance(Position tBasePosition, Vector3DI tValues, MugenSpriteFile * tSprites, MugenAnimations * tAnimations)
{
	gData.mValues[0] = tValues.x;
	gData.mValues[1] = tValues.y;
	gData.mValues[2] = tValues.z;

	int j, i;
	Position pos;
	for (j = 0; j < 3; j++) {
		pos = vecAdd(tBasePosition, makePosition(gPositionDelta[j * 3], gPositionDelta[j * 3 + 1], gPositionDelta[j * 3 + 2]));
		for (i = 0; i < gData.mValues[j]; i++) {
			gData.mAnimationIDs[j][i] = addMugenAnimation(getMugenAnimation(tAnimations, 20), tSprites, pos);

			pos = vecAdd(pos, makePosition(20, 0, 0));
		}
	}
}

void removePerformance()
{
	int j, i;
	for (j = 0; j < 3; j++) {
		for (i = 0; i < gData.mValues[j]; i++) {
			removeMugenAnimation(gData.mAnimationIDs[j][i]);
		}
	}
}
