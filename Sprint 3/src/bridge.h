#pragma once

static volatile bool sequenceStart = 0;

void closeLeftBarrier();
void openLeftBarrier();
void openBridge();
void closeBridge();
int closeBarriers();
int openBarriers();
void playBarrierSound();
void startBridgeSequence();
void checkBoatDetection();
// void startBoatDetectionThread();