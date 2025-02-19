#pragma once
#include <SFML/Graphics.hpp>
#include "constExpressions.h"

class View
{
private:
	inline static sf::View m_view;
	inline static sf::Vector2u m_screenSize;
	inline static sf::Vector2i m_uniqueScreenSizeGridSize;
	inline static sf::Vector2u m_sceneSize;
	inline static sf::Vector2f m_originOffset;
	inline static int m_pixelSize;
	inline static int m_tilePixels;
	
	sf::Vector2f m_movementOffset;
	bool m_movementAllowed;

	void m_setPixelSize(float factor)
	{
		if (m_screenSize.x < CHUNK_WIDTH_PIXELS * (factor * 1)) { m_pixelSize = 1; }
		else if (m_screenSize.x < CHUNK_WIDTH_PIXELS * (factor * 2)) { m_pixelSize = 2; }
		else if (m_screenSize.x < CHUNK_WIDTH_PIXELS * (factor * 3)) { m_pixelSize = 3; }
		else if (m_screenSize.x < CHUNK_WIDTH_PIXELS * (factor * 4)) { m_pixelSize = 4; }
		else { m_pixelSize = 4; }
		// I doubt we need more.
		m_pixelSize = 2;

		//DEBUG(m_pixelSize);
		m_tilePixels = TILE_SIZE * m_pixelSize;
		m_uniqueScreenSizeGridSize = pairI(m_screenSize.x / (m_tilePixels), m_screenSize.y / (m_tilePixels));
	}
	void m_setScreenSize()
	{
		m_screenSize = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	}
	void m_setView()
	{
		m_view = sf::RenderWindow::RenderWindow().getDefaultView();

		//new stuff to fixs bugs...
		m_view.setSize(floatify(m_uniqueScreenSizeGridSize.x * m_tilePixels), floatify(m_uniqueScreenSizeGridSize.y * m_tilePixels));
		m_view.setCenter(pairF(m_view.getSize().x / 2, m_view.getSize().y / 2));
		m_originOffset = pairF(0.f, 0.f);
	}
	void m_setSceneSize()
	{
		m_sceneSize = sf::Vector2u(32 * TILES_PER_CHUNK_X * 3, 32 * TILES_PER_CHUNK_Y * 3);
	}

	void m_move(sf::Vector2f offset)
	{
		m_originOffset += offset;
		m_view.move(offset);
	}
	void m_move(float offsetX, float offsetY)
	{
		m_originOffset.x += offsetX;
		m_originOffset.y += offsetY;
		m_view.move(offsetX, offsetY);
	}

public:

	View()
	{
		m_setScreenSize();
		m_setPixelSize(1.2f);
		m_setSceneSize();
		m_setView();
	}

	static const sf::Vector2u getScreenSize() { return m_screenSize; }
	static const int getPixelSize() { return m_pixelSize; }
	static const sf::View getView() { return m_view; }
	static const int getTilePixels() { return m_tilePixels; }
	static const sf::Vector2u getSceneSize() { return m_sceneSize; }
	static const sf::Vector2f getOriginOffset() { return m_originOffset; }
	sf::Vector2f getViewCoordinates(int dir)
	{
		switch (dir)
		{
		case UL:
			return sf::Vector2f(floatify(m_view.getCenter().x - m_view.getSize().x / 2), floatify(m_view.getCenter().y - m_view.getSize().y / 2));
			break;
		case UR:
			return sf::Vector2f(floatify(m_view.getCenter().x + m_view.getSize().x / 2), floatify(m_view.getCenter().y - m_view.getSize().y / 2));
			break;
		case DL:
			return sf::Vector2f(floatify(m_view.getCenter().x - m_view.getSize().x / 2), floatify(m_view.getCenter().y + m_view.getSize().y / 2));
			break;
		case DR:
			return sf::Vector2f(floatify(m_view.getCenter().x + m_view.getSize().x / 2), floatify(m_view.getCenter().y + m_view.getSize().y / 2));
			break;
		default:
			// UL
			return sf::Vector2f(floatify(m_view.getCenter().x - m_view.getSize().x / 2), floatify(m_view.getCenter().y - m_view.getSize().y / 2));
			break;
		}
	}


	void startViewMovement(sf::Vector2f offset)
	{
		m_movementAllowed = true;
		m_movementOffset = offset;
	}
	void endViewMovement()
	{
		m_movementAllowed = false;
		m_movementOffset = sf::Vector2f(0.f, 0.f);
	}
	void zoom(float delta)
	{
		m_view.zoom(1 - delta);
	}
	void resetZoom()
	{
		m_view.setSize(floatify(m_uniqueScreenSizeGridSize.x * m_tilePixels), floatify(m_uniqueScreenSizeGridSize.y * m_tilePixels));
	}
	sf::View moveViewByCharacter(sf::Vector2i pos, int stepSize)
	{
		sf::Vector2i oneSixthOfVisibleGrid{ pairI(m_uniqueScreenSizeGridSize.x / 6, m_uniqueScreenSizeGridSize.y / 6) };

		// Move view when character is offset from the center by one sixth of the displayed grid size
		if (pos.x > m_view.getCenter().x + (m_tilePixels) * oneSixthOfVisibleGrid.x)
		{
			if (getViewCoordinates(UR).x < m_sceneSize.x * m_pixelSize)
			{
				m_move(floatify(stepSize * m_pixelSize), 0.f);
				return m_view;
			}
		}
		else if (pos.x + (m_tilePixels) * oneSixthOfVisibleGrid.x < m_view.getCenter().x)
		{
			if (getViewCoordinates(UL).x > m_pixelSize)
			{
				m_move(floatify(-stepSize * m_pixelSize), 0.f);
				return m_view;
			}
		}
		if (pos.y > m_view.getCenter().y + (m_tilePixels) * oneSixthOfVisibleGrid.y)
		{
			if (getViewCoordinates(DL).y < m_sceneSize.y * m_pixelSize)
			{
				m_move(0.f, floatify(stepSize * m_pixelSize));
				return m_view;
			}
		}
		else if (pos.y + (m_tilePixels) * oneSixthOfVisibleGrid.y < m_view.getCenter().y)
		{
			if (getViewCoordinates(UL).y > m_pixelSize)
			{
				m_move(0.f, floatify(-stepSize * m_pixelSize));
				return m_view;
			}
		}
		return m_view;
	}
};
