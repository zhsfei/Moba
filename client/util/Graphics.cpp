/*
 * Graphics.cpp
 *
 *  Created on: 10 avr. 2013
 *      Author: pierre
 */

#include "Graphics.hpp"

namespace util {

	void Graphics::repeat(sf::RenderWindow* render, sf::Texture* texture, sf::IntRect rect, graphics::Repeat repeat) {


		if(repeat == graphics::full) {
			for(unsigned int i=0; i<(unsigned int)rect.width; i += (unsigned int)texture->getSize().x) {
				for(unsigned int j=0; j<(unsigned int)rect.height; j += (unsigned int)texture->getSize().y) {
					sf::Sprite sprite;
					sprite.setTexture(*texture);
					if(i+(unsigned int)texture->getSize().x > (unsigned int)rect.width)
						sprite.setTextureRect(sf::IntRect(0, 0, i+texture->getSize().x-rect.width, texture->getSize().y));
					if(j+(unsigned int)texture->getSize().y > (unsigned int)rect.height)
						sprite.setTextureRect(sf::IntRect(0, 0, sprite.getGlobalBounds().width, j+texture->getSize().y-rect.height));
					sprite.setPosition(i, j);
					render->draw(sprite);
				}
			}
		}
		else {
			sf::Sprite sprite;
			sprite.setTexture(*texture);
			sprite.setPosition(rect.left, rect.top);
			sprite.setScale(rect.width/texture->getSize().x, rect.height/texture->getSize().y);
			render->draw(sprite);
		}
	}

}


