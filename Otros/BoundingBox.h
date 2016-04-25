/* 
 * File:   BoundingBox.h
 * Author: Tonire
 *
 */

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <SFML/Graphics.hpp>

class BoundingBox {
public:
    BoundingBox(float x, float y, float width, float height, bool fromCenter = false);
    BoundingBox(const sf::FloatRect& rect);
    BoundingBox(const BoundingBox& orig);
    virtual ~BoundingBox();

    sf::Vector2f GetTopLeft() const {
        return sf::Vector2f(bounding->left, bounding->top);
    }

    sf::Vector2f GetTopRight() const {
        return sf::Vector2f(bounding->left + bounding->width, bounding->top);
    }

    sf::Vector2f GetBottomLeft() const {
        return sf::Vector2f(bounding->left, bounding->top + bounding->height);
    }

    sf::Vector2f GetBottomRight() const {
        return sf::Vector2f(bounding->left + bounding->width, bounding->top + bounding->height);
    }

    float GetWidth() const {
        return bounding->width;
    }

    float GetHeight() const {
        return bounding->height;
    }

    void SetX(float x) {
        bounding->left = x;
    }

    void SetY(float y) {
        bounding->top = y;
    }

    void SetWidth(float w) {
        bounding->width = w;
    }

    void SetHeight(float h) {
        bounding->height = h;
    }

    void Set(float x, float y, float w, float h) {
        bounding->left = x;
        bounding->top = y;
        bounding->width = w;
        bounding->height = h;
    }

    bool Intersects(const BoundingBox& rec) {
        return bounding->intersects(*(rec.GetRectangle()));
    }

    bool IsInside(const sf::Vector2f& vec) {
        return bounding->contains(vec.x, vec.y);
    }

    sf::FloatRect* GetRectangle() const {
        return bounding;
    }

protected:
    sf::FloatRect* bounding;
};

#endif /* BOUNDINGBOX_H */

