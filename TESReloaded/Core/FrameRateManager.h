#pragma once

enum FrameRateRequestType
{
	FrameRateRequestType_None,
	FrameRateRequestType_TurnUp,
	FrameRateRequestType_TurnDown,
};

class FrameRateManager // Never disposed
{

public:
	FrameRateManager();

	void						Set();
	void						SetFrameTime(double CurrentFrameTime);
	bool						IsOutGrid(NiAVObject* Object);
	
	int							FrameRate;
	double						ElapsedTime;

private:
	float						GetDistance(NiAVObject* Object);
	
	double						LastFrameTime;
	int							FrameCounter;
	int							GridDistant;
	FrameRateRequestType		RequestType;

};