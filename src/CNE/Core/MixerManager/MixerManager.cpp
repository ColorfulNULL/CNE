#include "MixerManager.hpp"

cne::MixerManager* cne::MixerManager::instance_ = nullptr;

void cne::MixerManager::Init()
{
	mixer_ = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
}

MIX_Mixer* cne::MixerManager::Get()
{
	return mixer_;
}

void cne::MixerManager::Play(MIX_Track* track, int loops)
{
	SDL_PropertiesID id = SDL_CreateProperties();
	SDL_SetNumberProperty(id, MIX_PROP_PLAY_LOOPS_NUMBER, loops);
	MIX_PlayTrack(track, id);
	SDL_DestroyProperties(id);
}

void cne::MixerManager::Play(MIX_Track* track, int loops, Sint64 ms)
{
	SDL_PropertiesID id = SDL_CreateProperties();
	SDL_SetNumberProperty(id, MIX_PROP_PLAY_LOOPS_NUMBER, loops);
	SDL_SetNumberProperty(id, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, ms);
	MIX_PlayTrack(track, id);
	SDL_DestroyProperties(id);
}

void cne::MixerManager::Stop(MIX_Track* track, Sint64 ms)
{
	Sint64 fade_frames = MIX_TrackMSToFrames(track, ms);
	MIX_StopTrack(track, fade_frames);
}

bool cne::MixerManager::IsPlay(MIX_Track* track)
{
	return MIX_TrackPlaying(track);
}

Sint64 cne::MixerManager::GetFade(MIX_Track* track)
{
	return MIX_GetTrackFadeFrames(track);
}

void cne::MixerManager::Pause(MIX_Track* track)
{
	MIX_PauseTrack(track);
}

void cne::MixerManager::Resume(MIX_Track* track)
{
	MIX_ResumeTrack(track);
}

bool cne::MixerManager::IsPause(MIX_Track* track)
{
	return MIX_TrackPaused(track);
}

void cne::MixerManager::SetPosition(MIX_Track* track, Sint64 ms)
{
	Sint64 frames = MIX_TrackMSToFrames(track, ms);
	MIX_SetTrackPlaybackPosition(track, frames);
}

Sint64 cne::MixerManager::GetPosition(MIX_Track* track)
{
	Sint64 frames = MIX_GetTrackPlaybackPosition(track);
	return MIX_TrackFramesToMS(track, frames);
}

void cne::MixerManager::SetAllVolume(float volume)
{
	MIX_SetMixerGain(mixer_, volume);
}

void cne::MixerManager::SetVolume(float volume, MIX_Track* track)
{
	MIX_SetTrackGain(track, volume);
}

void cne::MixerManager::Quit()
{
	MIX_DestroyMixer(mixer_);
}