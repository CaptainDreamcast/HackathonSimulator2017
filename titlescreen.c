#include "titlescreen.h"

#include <tari/mugenanimationhandler.h>
#include <tari/input.h>
#include <tari/screeneffect.h>

#include "selectscreen.h"

static struct {
	MugenSpriteFile mSprites;

} gData;

static void loadTitleScreen() {
	instantiateActor(getMugenAnimationHandlerActorBlueprint());
	gData.mSprites = loadMugenSpriteFileWithoutPalette("assets/sprites/TITLE.sff");
	addMugenAnimation(createOneFrameMugenAnimationForSprite(0, 0), &gData.mSprites, makePosition(0, 0, 1));

	addFadeIn(30, NULL, NULL);
}

static void gotoSelectScreen(void* tCaller) {
	
	setNewScreen(&SelectScreen);
}

static void updateTitleScreen() {
	if (hasPressedAbortFlank()) {
		abortScreenHandling();
	}

	if (hasPressedStartFlank()) {
		addFadeOut(30, gotoSelectScreen, NULL);
	}
}

Screen TitleScreen = {
	.mLoad = loadTitleScreen,
	.mUpdate = updateTitleScreen,
};