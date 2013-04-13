/*
 * ButtonImage.cpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#include "ButtonImage.hpp"

namespace graphics {

	ButtonImage::ButtonImage(std::string image, BasicStyle* style) : Button("", style) {
		m_image = ImageLoader::get(image);
		if(m_style != NULL) {
			m_width = m_style->topleft(BasicStyle::normal)->getGlobalBounds().width*2+m_image->getSize().x;
			m_height = m_style->topleft(BasicStyle::normal)->getGlobalBounds().height*2+m_image->getSize().y;
		}
	}

	void ButtonImage::draw(sf::RenderWindow* render) {
		Button::draw(render);
		util::Coordinates coord = getRealCoord();
		sf::Sprite sprite;
		sprite.setTexture(*m_image);
		sprite.setPosition(coord.x+m_style->topleft(BasicStyle::normal)->getGlobalBounds().width, coord.y+m_style->topleft(BasicStyle::normal)->getGlobalBounds().height);
		render->draw(sprite);
	}

}
