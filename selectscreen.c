#include "selectscreen.h"

#include <tari/mugenanimationhandler.h>
#include <tari/input.h>
#include <tari/screeneffect.h>

#include "titlescreen.h"
#include "performancehandler.h"
#include "hackscreen.h"
#include "projectlogic.h"

static struct {
	MugenSpriteFile mSprites;
	MugenAnimations mAnimations;
	int mCurrentCharacter;
	int mCharacterID;
	int mPerformanceID;

	Vector3DI mPerformances[4];
} gData;

static void addCharacter();

static void loadTitleScreen() {
	instantiateActor(getMugenAnimationHandlerActorBlueprint());
	gData.mSprites = loadMugenSpriteFileWithoutPalette("assets/sprites/SELECT.sff");
	gData.mAnimations = loadMugenAnimationFile("assets/sprites/SELECT.air");
	addMugenAnimation(createOneFrameMugenAnimationForSprite(0, 0), &gData.mSprites, makePosition(0, 0, 1));
	addMugenAnimation(createOneFrameMugenAnimationForSprite(0, 1), &gData.mSprites, makePosition(0, 0, 3));

	gData.mPerformances[0] = makeVector3DI(5, 3, 1);
	gData.mPerformances[1] = makeVector3DI(3, 5, 1);
	gData.mPerformances[2] = makeVector3DI(20, 20, 20);

	gData.mCurrentCharacter = 0;
	addCharacter();


	addFadeIn(30, NULL, NULL);
}

static void addCharacter() {
	gData.mCharacterID = addMugenAnimation(getMugenAnimation(&gData.mAnimations, gData.mCurrentCharacter+10), &gData.mSprites, makePosition(320, 480, 2));
	addPerformance(makePosition(175, 384, 4), gData.mPerformances[gData.mCurrentCharacter], &gData.mSprites, &gData.mAnimations);
}

static void removeCharacter() {
	removeMugenAnimation(gData.mCharacterID);
	removePerformance();
}

static void changeCharacter(int tDelta) {
	removeCharacter();
	gData.mCurrentCharacter += tDelta;
	if (gData.mCurrentCharacter < 0) gData.mCurrentCharacter += 3;
	if (gData.mCurrentCharacter >= 3) gData.mCurrentCharacter -= 3;
	addCharacter();
}

static void gotoHackScreen(void* tCaller) {
	resetProject();
	setNewScreen(&HackScreen);
}

static void updateTitleScreen() {
	if (hasPressedAbortFlank()) {
		setNewScreen(&TitleScreen);
	}

	if (hasPressedLeftFlank()) {
		changeCharacter(-1);
	}

	if (hasPressedRightFlank()) {
		changeCharacter(1);
	}

	if ((gData.mCurrentCharacter != 2) && (hasPressedAFlank() || hasPressedStartFlank())) {
		addFadeOut(30, gotoHackScreen, NULL);
	}
}

Screen SelectScreen = {
	.mLoad = loadTitleScreen,
	.mUpdate = updateTitleScreen,
};