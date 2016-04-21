/* 
 * File:   :).cpp
 * Author: Tonire
 * 
 * FE
 */

#include "BoundingBox.h"

BoundingBox::BoundingBox(float x, float y, float width, float height, bool fromCenter) {
	if(fromCenter){
		x -= width/2.f;
		y -= height/2.f;
	}
	bounding = new sf::FloatRect(x, y, width, height);
}

BoundingBox::BoundingBox(const sf::FloatRect& rect) {
	bounding = new sf::FloatRect(rect.left, rect.top, rect.width, rect.height);
}

BoundingBox::BoundingBox(const BoundingBox& orig) {
}

BoundingBox::~BoundingBox() {
	delete bounding;
	bounding = NULL;
}

BoundingBox& BoundingBox::operator=(const BoundingBox& v)
{	
    bounding->left = v.GetTopLeft().x;
    bounding->top = v.GetTopLeft().y;
    bounding->width = v.GetWidth();
    bounding->height = v.GetHeight();
    return *this;
}
