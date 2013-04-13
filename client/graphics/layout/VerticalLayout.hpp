/*
 * VerticalLayout.hpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#ifndef VERTICALLAYOUT_HPP_
#define VERTICALLAYOUT_HPP_

#include "Layout.hpp"

namespace graphics {

	class VerticalLayout : public Layout {

	public:
		void validate();
		std::string getLayoutName();

	};

}


#endif /* VERTICALLAYOUT_HPP_ */
