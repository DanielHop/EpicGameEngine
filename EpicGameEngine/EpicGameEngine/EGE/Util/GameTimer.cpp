#include "GameTimer.h"

#include <windows.h>


GameTimer::GameTimer()
	: m_secondsPerCount{ 0 }, m_deltaTime{ -1.0 }, m_baseTime{ 0 },
	m_pausedTime{ 0 }, m_stopTime{ 0 }, m_prevTime{ 0 }, m_currTime{ 0 }, m_stopped{ false }
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_secondsPerCount = 1.0 / (double)countsPerSec;
}


GameTimer::~GameTimer()
{
}

float GameTimer::TotalTime()const
{
	// If we are stopped, do not count the time that has passed since we stopped.
	// Moreover, if we previously already had a pause, the distance 
	// mStopTime - mBaseTime includes paused time, which we do not want to count.
	// To correct this, we can subtract the paused time from mStopTime:  
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime

	if (m_stopped)
	{
		return (float)(((m_stopTime - m_pausedTime) - m_baseTime)*m_secondsPerCount);
	}

	// The distance mCurrTime - mBaseTime includes paused time,
	// which we do not want to count.  To correct this, we can subtract 
	// the paused time from mCurrTime:  
	//
	//  (mCurrTime - mPausedTime) - mBaseTime 
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mCurrTime

	else
	{
		return (float)(((m_currTime - m_pausedTime) - m_baseTime)*m_secondsPerCount);
	}
}

void GameTimer::Tick()
{
	if (m_stopped)
	{
		m_deltaTime = 0.0;
		return;
	}


	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_currTime = currTime;
	
	m_deltaTime = (m_currTime - m_prevTime)*m_secondsPerCount;

	m_prevTime = m_currTime;

	if (m_deltaTime < 0.0 || m_deltaTime > 10000.f)
	{
		m_deltaTime = 0.0;
	}

}

float GameTimer::DeltaTime() const
{
	return (float)m_deltaTime;
}


void GameTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceFrequency((LARGE_INTEGER*)&currTime);

	m_baseTime = currTime;
	m_prevTime = currTime;
	m_stopTime = 0;
	m_stopped = true;
}

void GameTimer::Stop()
{
	if (!m_stopped)
	{
		__int64 currTime;
		QueryPerformanceFrequency((LARGE_INTEGER*)&currTime);
		
		m_stopTime = currTime;
		m_stopped = true;
	}
}

void GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceFrequency((LARGE_INTEGER*)&startTime);

	if (m_stopped)
	{
		m_pausedTime += (startTime - m_stopTime);

		m_prevTime = startTime;

		m_stopTime = 0;
		m_stopped = false;
	}
}