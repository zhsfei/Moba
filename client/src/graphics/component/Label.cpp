/*
 * Label.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#include "Label.hpp"

namespace graphics {

	Label::Label(std::string text, BasicStyle* style) : m_text(text), m_style(style), m_align(alignLeft), m_valign(valignCenter) {
		log_out "Ref "+util::Cast::ptrToString(this)+": Create "+getComponentName()+" [text="+text+", style="+util::Cast::ptrToString(style)+"]" end_log_out;
	}

	Label::~Label() {

	}


	void Label::addListener(LabelListener* listener) {
		m_listener.push_back(listener);
	}

	bool Label::event(sf::Event* event, bool used) {
		util::CoordInt coord = getRealCoord();
		if(event->type == sf::Event::MouseMoved) {
			if(!used && event->mouseMove.x > coord.x && event->mouseMove.x < coord.x+m_width
				&& event->mouseMove.y > coord.y && event->mouseMove.y < coord.y+m_height) {
				if(!m_focus) {
					for(boost::ptr_vector<LabelListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
						m_window->addCallFunction(boost::bind(&LabelListener::mouseEntered, &(*it), this));
					}
				}
				m_focus = true;
				used = true;
			}
			else {
				if(m_focus) {
					for(boost::ptr_vector<LabelListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
						m_window->addCallFunction(boost::bind(&LabelListener::mouseLeft, &(*it), this));
					}
				}
				m_focus = false;
			}
		}
		else if(event->type == sf::Event::MouseLeft) {
			if(m_focus) {
				for(boost::ptr_vector<LabelListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
					m_window->addCallFunction(boost::bind(&LabelListener::mouseLeft, &(*it), this));
				}
			}
			m_focus = false;
		}
		return used;
	}

	void Label::setStyle(BasicStyle* style) {
		m_style = style;
	}

	void Label::setMinimalSize() {
		if(m_style == NULL) {
			return;
		}
		sf::Text text;
		text.setString(m_text);
		text.setFont(*m_style->font());
		text.setCharacterSize(m_style->fontSize());
		sf::FloatRect textSize = text.getGlobalBounds();
		m_width = textSize.width;
		m_height = textSize.height+5;
	}

	void Label::setAlign(Align align) {
		m_align = align;
	}

	void Label::setVAlign(VAlign align) {
		m_valign = align;
	}

	void Label::setText(std::string text) {
		m_text = text;
	}

	std::string Label::getText() {
		return m_text;
	}

	std::string Label::getComponentName() {
		return "Label";
	}

	bool Label::isSelectable() {
		return false;
	}

	void Label::draw(sf::RenderWindow* render) {
		if(m_style == NULL) {
			log_err "No style has been applied to the component "+getComponentName() end_log_err;
			return;
		}
		if(!m_visible)
			return;
		util::CoordInt coord = getRealCoord();
		sf::Text text;
		text.setString(m_text);
		text.setFont(*m_style->font());
		text.setCharacterSize(m_style->fontSize());
		text.setColor(*m_style->fontColor());
		sf::FloatRect textSize = text.getGlobalBounds();
		int x = coord.x+(m_width-textSize.width)/2;
		int y = coord.y+(m_height-textSize.height)/2;
		if(m_align == alignLeft)
			x = coord.x;
		else if(m_align == alignRight)
			x = coord.x+m_width-textSize.width;

		if(m_valign == valignTop)
			y = coord.y;
		else if(m_valign == valignBot)
			y = coord.y+m_width-textSize.height;
		text.setPosition(x,y);
		render->draw(text);
	}
}


