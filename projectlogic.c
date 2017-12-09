#include "projectlogic.h"

static struct {
	int mCodeValue;
	int mDesignValue;
	int mMarketingValue;
	int mTime;
} gData;

void resetProject()
{
	gData.mCodeValue = 1;
	gData.mDesignValue = 1;
	gData.mMarketingValue = 1;
	gData.mTime = 0;
}

int getCodeProjectValue()
{
	return gData.mCodeValue;
}

int getDesignProjectValue()
{
	return gData.mDesignValue;
}

int getMarketingProjectValue()
{
	return gData.mMarketingValue;
}

int getTime()
{
	return gData.mTime;
}

void changeProjectCode(int tDelta)
{
	gData.mCodeValue += tDelta;
}

void changeProjectDesign(int tDelta)
{
	gData.mDesignValue += tDelta;
}

void changeProjectMarketing(int tDelta)
{
	gData.mMarketingValue += tDelta;
}

void changeProjectTime(int tDelta)
{
	gData.mTime += tDelta;
}

int isTimeOver()
{
	return gData.mTime > 9;
}
