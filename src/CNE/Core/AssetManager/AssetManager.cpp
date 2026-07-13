#include "AssetManager.hpp"

cne::AssetManager* cne::AssetManager::instance_ = nullptr;

void cne::AssetManager::LoadImage(std::string path, std::string name)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(RendererManager::Instance()->renderer_, surface);
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);//防止边缘光晕
	Image image{ texture, surface->w, surface->h };
	image_pool_.insert(std::make_pair(name, image));
	SDL_DestroySurface(surface);
}

std::vector<std::string> cne::AssetManager::GetImagePoolKey()
{
	std::vector<std::string> keys;
	keys.reserve(image_pool_.size());
	for (const auto& pair : image_pool_)
	{
		keys.push_back(pair.first);
	}
	return keys;
}

std::vector<cne::Image> cne::AssetManager::GetImagePoolValue()
{
	std::vector<Image> values;
	values.reserve(image_pool_.size());
	for (const auto& pair : image_pool_)
	{
		values.push_back(pair.second);
	}
	return values;
}

int cne::AssetManager::GetImagePoolSize()
{
	return image_pool_.size();
}

void cne::AssetManager::FreeImage(std::string name)
{
	SDL_DestroyTexture(image_pool_.at(name).texture);
	image_pool_.erase(name);
}

void cne::AssetManager::FreeImagePool()
{
	for (auto image : image_pool_)
	{
		SDL_DestroyTexture(image.second.texture);
	}
	image_pool_.clear();
}

cne::Image cne::AssetManager::GetImage(std::string name)
{
	return image_pool_.at(name);
}

bool cne::AssetManager::IsExistImageKey(std::string name)
{
	return image_pool_.contains(name);
}

void cne::AssetManager::LoadFont(std::string path, std::string name)
{
	Font font = TTF_OpenFont(path.c_str(), 32);
	font_pool_.insert(std::make_pair(name, font));
}

std::vector<std::string> cne::AssetManager::GetFontPoolKey()
{
	std::vector<std::string> keys;
	keys.reserve(font_pool_.size());
	for (const auto& pair : font_pool_)
	{
		keys.push_back(pair.first);
	}
	return keys;
}

std::vector<cne::Font> cne::AssetManager::GetFontPoolValue()
{
	std::vector<Font> values;
	values.reserve(font_pool_.size());
	for (const auto& pair : font_pool_)
	{
		values.push_back(pair.second);
	}
	return values;
}

int cne::AssetManager::GetFontPoolSize()
{
	return font_pool_.size();
}

void cne::AssetManager::FreeFont(std::string name)
{
	TTF_CloseFont(font_pool_.at(name));
	font_pool_.erase(name);
}

void cne::AssetManager::FreeFontPool()
{
	for (auto font : font_pool_)
	{
		TTF_CloseFont(font.second);
	}
	font_pool_.clear();
}

cne::Font cne::AssetManager::GetFont(std::string name)
{
	return font_pool_.at(name);
}

bool cne::AssetManager::IsExistFontKey(std::string name)
{
	return font_pool_.contains(name);
}

void cne::AssetManager::LoadAudio(std::string path, std::string name, bool isPreDecoding)
{
	MIX_Audio* audio_data = MIX_LoadAudio(MixerManager::Instance()->mixer_, path.c_str(), isPreDecoding);
	MIX_Track* track = MIX_CreateTrack(MixerManager::Instance()->mixer_);
	MIX_SetTrackAudio(track, audio_data);
	Audio audio{ audio_data, track };
	audio_pool_.insert(std::make_pair(name, audio));
}

std::vector<std::string> cne::AssetManager::GetAudioPoolKey()
{
	std::vector<std::string> keys;
	keys.reserve(audio_pool_.size());
	for (const auto& pair : audio_pool_)
	{
		keys.push_back(pair.first);
	}
	return keys;
}

std::vector<cne::Audio> cne::AssetManager::GetAudioPoolValue()
{
	std::vector<Audio> value;
	value.reserve(audio_pool_.size());
	for (const auto& pair : audio_pool_)
	{
		value.push_back(pair.second);
	}
	return value;
}

int cne::AssetManager::GetAudioPoolSize()
{
	return audio_pool_.size();
}

void cne::AssetManager::FreeAudio(std::string name)
{
	MIX_DestroyTrack(audio_pool_.at(name).track);
	MIX_DestroyAudio(audio_pool_.at(name).audio);
	audio_pool_.erase(name);
}

void cne::AssetManager::FreeAudioPool()
{
	for (auto audio : audio_pool_)
	{
		MIX_DestroyTrack(audio.second.track);
		MIX_DestroyAudio(audio.second.audio);
	}
	audio_pool_.clear();
}

cne::Audio cne::AssetManager::GetAudio(std::string name)
{
	return audio_pool_.at(name);
}

bool cne::AssetManager::IsExistAudioKey(std::string name)
{
	return audio_pool_.contains(name);
}

void cne::AssetManager::LoadTextMap(std::string path, std::string map_name)
{
	Json json;
	FileManager::Instance()->ReadJson(path, json);
	text_pool_.insert(std::make_pair(map_name, json.get<std::map<std::string, std::string>>()));
}

void cne::AssetManager::FreeTextMapPool()
{
	for (auto text : text_pool_)
	{
		text.second.clear();
	}
}

cne::Text cne::AssetManager::GetText(std::string map_name, std::string text_name)
{
	return text_pool_.at(map_name).at(text_name);
}

bool cne::AssetManager::IsExistTextMapKey(std::string name)
{
	return text_pool_.contains(name);
}

void cne::AssetManager::MakeTextImage(std::string name, std::string font_name, Text text, int size, SDL_Color color)
{
	TTF_SetFontSize(font_pool_[font_name], size);
	SDL_Surface* surface = TTF_RenderText_Solid(font_pool_[font_name], text.c_str(), text.size(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(RendererManager::Instance()->renderer_, surface);
	Image image{ texture, surface->w, surface->h };
	SDL_DestroySurface(surface);
	image_text_pool_.insert(std::make_pair(name, image));
}

std::vector<std::string> cne::AssetManager::GetTextImagePoolKey()
{
	std::vector<std::string> keys;
	keys.reserve(image_text_pool_.size());
	for (const auto& pair : image_text_pool_)
	{
		keys.push_back(pair.first);
	}
	return keys;
}

std::vector<cne::Image> cne::AssetManager::GetTextImagePoolValue()
{
	std::vector<Image> values;
	values.reserve(image_text_pool_.size());
	for (const auto& pair : image_text_pool_)
	{
		values.push_back(pair.second);
	}
	return values;
}

void cne::AssetManager::FreeTextImage(std::string name)
{
	SDL_DestroyTexture(image_text_pool_.at(name).texture);
	image_text_pool_.erase(name);
}

int cne::AssetManager::GetTextImagePoolSize()
{
	return image_text_pool_.size();
}

void cne::AssetManager::FreeTextImagePool()
{
	for (auto image : image_text_pool_)
	{
		SDL_DestroyTexture(image.second.texture);
	}
	image_text_pool_.clear();
}

cne::Image cne::AssetManager::GetTextImage(std::string name)
{
	return image_text_pool_.at(name);
}

bool cne::AssetManager::IsExistTextImageKey(std::string name)
{
	return image_text_pool_.contains(name);
}
