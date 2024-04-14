#pragma once
#include "SpriteLoader.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Direction.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Sprite
{
public:
	Sprite(SpriteLoader* texLoader);
	~Sprite();

	void CropSprite(sf::IntRect& rectangle);
	void SetSpriteSize(sf::Vector2i& size);
	void SetSpriteScale(sf::Vector2f& scale);
	void SetSpritePosition(sf::Vector2f& position);
	void SetSpriteDirection(Direction& dirention);

	bool Load(const std::string& path);
	void Release();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window) const;

private:
	std::string m_spriteId;
	sf::Sprite m_sprite;
	sf::Vector2i m_spriteSize;
	sf::Vector2f m_spriteScale;
	Direction m_spriteDirection;
	SpriteLoader* m_textureLoader;
};