#include "hackscreen.h"

#include <tari/mugenanimationhandler.h>
#include <tari/input.h>
#include <tari/screeneffect.h>
#include <tari/optionhandler.h>
#include <tari/math.h>

#include "selectscreen.h"
#include "performancehandler.h"
#include "projectlogic.h"
#include "storyscreen.h"

static struct {
	MugenSpriteFile mSprites;
	MugenAnimations mAnimations;
} gData;

static void loadScreenOptions();

static void loadTitleScreen() {
	instantiateActor(getMugenAnimationHandlerActorBlueprint());
	gData.mSprites = loadMugenSpriteFileWithoutPalette("assets/sprites/HACK.sff");
	gData.mAnimations = loadMugenAnimationFile("assets/sprites/HACK.air");
	addMugenAnimation(createOneFrameMugenAnimationForSprite(0, 0), &gData.mSprites, makePosition(0, 0, 1));
	addMugenAnimation(getMugenAnimation(&gData.mAnimations, 30+getTime()), &gData.mSprites, makePosition(444, 54, 2));

	loadScreenOptions();

	addFadeIn(30, NULL, NULL);
}

static void gotoCode(void* tCaller) {
	(void)tCaller;
	char path[1000];
	sprintf(path, "assets/story/code/%d.def", randfromInteger(0, 2));

	setCurrentStoryDefinitionFile(path);
	setNewScreen(&StoryScreen);
}

static void selectCode(void* tCaller) {
	addFadeOut(30, gotoCode, NULL);
}

static void gotoDesign(void* tCaller) {
	(void)tCaller;
	char path[1000];
	sprintf(path, "assets/story/design/%d.def", randfromInteger(0, 2));

	setCurrentStoryDefinitionFile(path);
	setNewScreen(&StoryScreen);
}

static void selectDesign(void* tCaller) {
	addFadeOut(30, gotoDesign, NULL);
}

static void gotoMarketing(void* tCaller) {
	(void)tCaller;
	char path[1000];
	sprintf(path, "assets/story/marketing/%d.def", randfromInteger(0, 2));

	setCurrentStoryDefinitionFile(path);
	setNewScreen(&StoryScreen);
}

static void selectMarketing(void* tCaller) {
	addFadeOut(30, gotoMarketing, NULL);
}

static void gotoHarrassment(void* tCaller) {
	(void)tCaller;
	char path[1000];
	sprintf(path, "assets/story/GAMEOVER.def");

	setCurrentStoryDefinitionFile(path);
	setNewScreen(&StoryScreen);
}

static void selectHarrassment(void* tCaller) {
	addFadeOut(30, gotoHarrassment, NULL);
}


static void loadScreenOptions() {
	instantiateActor(getOptionHandlerBlueprint());
	setOptionButtonA();
	setOptionButtonStart();
	setOptionTextSize(15);
	double x = 190;
	double y = 283;
	double dy = 26;
	addOption(makePosition(x, y, 3), "", selectCode, NULL);
	addOption(makePosition(x, y + dy, 3), "", selectDesign, NULL);
	addOption(makePosition(x, y + dy * 2, 3), "", selectMarketing, NULL);
	addOption(makePosition(x, y + dy * 3, 3), "", selectHarrassment, NULL);

	addPerformance(makePosition(105, 93, 3), makeVector3DI(getCodeProjectValue(), getDesignProjectValue(), getMarketingProjectValue()), &gData.mSprites, &gData.mAnimations);
}

static void gotoSelectScreen(void* tCaller) {

	setNewScreen(&SelectScreen);
}

static void updateTitleScreen() {
	if (hasPressedAbortFlank()) {
		abortScreenHandling();
	}
}

Screen HackScreen = {
	.mLoad = loadTitleScreen,
	.mUpdate = updateTitleScreen,
};