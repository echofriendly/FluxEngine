#include "stdafx.h"
#include "PerfTimer.h"


PerfTimer::PerfTimer(const wstring& source):
	m_Source(source)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_SecondsPerCount = 1000.0f / (double)(countsPerSec);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_StartTime);
}

PerfTimer::~PerfTimer()
{
}

float PerfTimer::Stop()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_StopTime);
	float time = (float)((m_StopTime - m_StartTime) * m_SecondsPerCount);

	if (m_Source.size() > 0)
	{
		wstringstream stream;
		stream << L"[" << m_Source << L"] " << time << L" ms";
		DebugLog::Log(stream.str());
	}

	return time;
}