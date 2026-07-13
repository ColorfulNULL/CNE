#pragma once

namespace cne
{
	class Scene
	{
	public:
		virtual void Init() {};
		virtual void HandleEvent() {};
		virtual void Update() {};
		virtual void Render() {};
		virtual void Quit() {};
	};
}