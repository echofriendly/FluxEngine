#include "stdafx.h"
#include "Profiler.h"

Profiler::Profiler() :
	m_Name("")
{

}

Profiler::Profiler(const string& name, const string& description) :
	m_Name(name),
	m_Description(description)
{

}

Profiler::~Profiler()
{
}

void Profiler::Start()
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_SecondsPerCount = 1000.0f / (double)(countsPerSec);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_StartTime);
}

float Profiler::Stop()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_StopTime);
	return (float)((m_StopTime - m_StartTime) * m_SecondsPerCount);
}

AutoProfiler::AutoProfiler(const string& name, const string& description) :
	Profiler(name, description)
{
	Start();
}

AutoProfiler::~AutoProfiler()
{
	const float time = Stop();
	stringstream str;
	str << "[" << m_Name << "] " << m_Description << " > " << time << " ms";
	Console::Log(str.str());
}
