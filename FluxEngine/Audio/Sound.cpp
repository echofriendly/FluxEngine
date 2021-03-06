#include "FluxEngine.h"
#include "Sound.h"
#include "AudioEngine.h"

Sound::Sound(Context* pContext) :
	Resource(pContext)
{

}

bool Sound::Load(InputStream& inputStream)
{
	AUTOPROFILE_DESC(Sound_Load, inputStream.GetSource().c_str());
	AudioEngine* pAudio = GetSubsystem<AudioEngine>();
	FMOD_RESULT result = pAudio->GetSystem()->createSound(inputStream.GetSource().c_str(), m_Mode, nullptr, &m_pSound);
	SetMemoryUsage((uint32)inputStream.GetSize());
	FLUX_LOG_FMOD(result);
	return m_pSound != nullptr;
}

void Sound::SetMode(const uint32 mode)
{
	m_Mode = mode;
	FMOD_RESULT result = m_pSound->setMode(mode);
	FLUX_LOG_FMOD(result);
}