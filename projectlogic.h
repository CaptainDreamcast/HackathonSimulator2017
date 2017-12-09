#pragma once

void resetProject();
int getCodeProjectValue();
int getDesignProjectValue();
int getMarketingProjectValue();
int getTime();

void changeProjectCode(int tDelta);
void changeProjectDesign(int tDelta);
void changeProjectMarketing(int tDelta);
void changeProjectTime(int tDelta);
int isTimeOver();