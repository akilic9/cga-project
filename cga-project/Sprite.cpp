#include "Sprite.h"

Sprite::Sprite(SpriteLoader* texLoader)
	: m_spriteId("")
	, m_spriteSize(32, 32)
	, m_spriteScale(1.0f, 1.0f)
	, m_spriteDirection(Direction::Down)
	, m_textureLoader(texLoader)
{
}

Sprite::~Sprite()
{
	Release();
}

void Sprite::CropSprite(sf::IntRect& rectangle)
{
	m_sprite.setTextureRect(rectangle);
}

void Sprite::SetSpriteSize(sf::Vector2i& size) {
	if (m_spriteSize == size)
		return;

	m_spriteSize = size;
	m_sprite.setOrigin(m_spriteSize.x / 2.f, m_spriteSize.y / 2.f);
}

void Sprite::SetSpriteScale(sf::Vector2f& scale)
{
	if (m_spriteScale == scale)
		return;

	m_spriteScale = scale;
	m_sprite.setScale(scale);
}

void Sprite::SetSpritePosition(sf::Vector2f& position)
{
	if (m_sprite.getPosition() == position)
		return;

	m_sprite.setPosition(position);	
}

void Sprite::SetSpriteDirection(Direction& direction)
{
	if (m_spriteDirection == direction)
		return;

	m_spriteDirection = direction;
	m_sprite.setRotation(int(m_spriteDirection) * 90.f);
}

//Load the sprite data. Only one sprite and no animations for now. TODO: expand.
bool Sprite::Load(const std::string& path)
{
	std::ifstream dataFile;
	dataFile.open("Data/SpriteData/" + path);
	if (dataFile.is_open()) {
		Release(); // Release current sheet resources.
		std::string line;
		while (std::getline(dataFile, line)) {
			if (line[0] == '<') //Comment line.
				continue;

			std::stringstream keystream(line);
			std::string dataType;
			keystream >> dataType;

			if (dataType == "Texture") { //TODO: make it case insensitive.
				if (m_spriteId != "") {
					std::cerr << "Multiple textures in:" << path << std::endl;
					continue;
				}
				std::string spriteId;
				keystream >> spriteId;
				if (!m_textureLoader->AllocateResource(spriteId)) {
					std::cerr << "Texture loader can't load the texture: " << spriteId << std::endl;
					continue;
				}
				m_spriteId = spriteId;
				m_sprite.setTexture(*m_textureLoader->GetResource(m_spriteId));
			}
			else if (dataType == "Size" || dataType == "Scale" || dataType == "Location") {
				std::string data;
				keystream >> data;
				std::string dataSep = ":";
				int index = data.find(dataSep);
				if (index == std::string::npos) {
					std::cerr << "Error in size specification: " << path << std::endl;
					continue;
				}
				if (dataType == "Size") {
					m_spriteSize.x = stoi(data.substr(0, index));
					m_spriteSize.y = stoi(data.substr(index + dataSep.length(), data.length()));
					SetSpriteSize(m_spriteSize);
				}
				else if (dataType == "Scale") {
					m_spriteScale.x = stof(data.substr(0, index));
					m_spriteScale.y = stof(data.substr(index + dataSep.length(), data.length()));
					SetSpriteScale(m_spriteScale);
				}
				else if (dataType == "Location") {
					int column = stoi(data.substr(0, index));
					int row = stoi(data.substr(index + dataSep.length(), data.length()));
					sf::IntRect rect(column * m_spriteSize.x, row * m_spriteSize.y, m_spriteSize.x, m_spriteSize.y);
					CropSprite(rect);
				}
			}
		}
		dataFile.close();
		return true;
	}
	return false;
}

void Sprite::Release()
{
	m_textureLoader->ReleaseResource(m_spriteId);
}

void Sprite::Update(float deltaTime)
{
}

void Sprite::Render(sf::RenderWindow* window) const
{
	window->draw(m_sprite);
}
