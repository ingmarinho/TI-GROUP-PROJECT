#pragma once

static volatile bool sequenceStart = 0;

int PI_THREAD(closeRightBarrier)
void closeLeftBarrier();
int PI_THREAD(openRightBarrier);
void openLeftBarrier();
int PI_THREAD(activateTrafficLights);
void openBridge();
void closeBridge();
int closeBarriers();
int openBarriers();
void playBarrierSound();
void startBridgeSequence();
int PI_THREAD(checkBoatDetection);