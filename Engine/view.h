#pragma once
#include <SFML/Graphics.hpp>
#include "constExpressions.h"

class View
{
private:
	inline static sf::View m_view;
	inline static sf::Vector2u m_screenSize;
	inline static sf::Vector2u m_sceneSize;
	inline static sf::Vector2f m_originOffset;
	inline static int m_pixelSize;
	
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
	}
	void m_setScreenSize()
	{
		m_screenSize = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	}
	void m_setView()
	{
		//sets view and zoom level to default
		m_view = sf::RenderWindow::RenderWindow().getDefaultView();
		resetView();
		m_view.setCenter(pairF(m_view.getSize().x / 2, m_view.getSize().y / 2));
		m_originOffset = pairF(0.f, 0.f);
	}
	void m_setSceneSize()
	{
		//todo: add more scenes
		m_sceneSize = sf::Vector2u(32 * TILES_PER_CHUNK_X * 3, 32 * TILES_PER_CHUNK_Y * 3);
	}

	void m_move(sf::Vector2f offset)
	{
		m_originOffset += offset;
		m_view.move(offset);
	}
	template <typename T>
	void m_move(T const& x, T const& y)
	{
		m_originOffset.x += floatify(x);
		m_originOffset.y += floatify(y);
		m_view.move(floatify(x), floatify(y));
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
	static const sf::View getView() { return m_view; }
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
	void resetView()
	{
		m_view.setSize(sf::Vector2f(m_screenSize));
		m_view.zoom(1.f / m_pixelSize);
	}
	sf::View moveViewByCharacter(sf::Vector2i pos, int stepSize)
	{
		sf::Vector2i oneSixth{ pairI(m_screenSize.x / 6 / m_pixelSize, m_screenSize.y / 6 / m_pixelSize) };

		// Move view when character is offset from the center by one sixth of the displayed grid size
		if (pos.x > m_view.getCenter().x + oneSixth.x && getViewCoordinates(UR).x + stepSize < m_sceneSize.x)
		{
			m_move(stepSize, 0);
			return m_view;
		}
		else if (pos.x + oneSixth.x < m_view.getCenter().x && getViewCoordinates(UL).x > stepSize)
		{
			m_move(-stepSize, 0);
			return m_view;
		}
		if (pos.y > m_view.getCenter().y + oneSixth.y && getViewCoordinates(DL).y + stepSize < m_sceneSize.y)
		{
			m_move(0, stepSize);
			return m_view;
		}
		else if (pos.y + oneSixth.y < m_view.getCenter().y && getViewCoordinates(UL).y > stepSize)
		{
			m_move(0, -stepSize);
			return m_view;
		}
		return m_view;
	}
};
