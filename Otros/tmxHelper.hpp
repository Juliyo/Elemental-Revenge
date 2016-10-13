/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tmxHelper.hpp
 * Author: tonir
 *
 * Created on 25 de abril de 2016, 12:39
 */

#ifndef TMXHELPER_HPP
#define TMXHELPER_HPP

#include <tmx/MapObject.h>

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Fixture.h>

#include <vector>
#include <queue>

#include "../Entities/Entity.hpp"

namespace tmx {
    b2Vec2 SfToBoxVec(const sf::Vector2f& vec);
    sf::Vector2f BoxToSfVec(const b2Vec2& vec);
    float SfToBoxFloat(float val);
    float BoxToSfFloat(float val);
    float SfToBoxAngle(float degrees);
    float BoxToSfAngle(float rads);

    class BodyCreator {
    public:
        typedef std::vector<sf::Vector2f> Shape;
        typedef std::vector<Shape> Shapes;
        typedef std::queue<Shape> ShapeQueue;

        //adds the object to the b2World. Returns a pointer to the body
        //created so that its properties my be modified. Bodies are static by default
        static b2Body* Add(const MapObject& object, b2World& world, b2BodyType bodyType = b2_staticBody);

    private:
        static void m_Split(const MapObject& object, b2Body* body);
        static Shapes m_ProcessConcave(const Shape& points);
        static Shapes m_ProcessConvex(const Shape& points);
        static sf::Vector2f m_HitPoint(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, const sf::Vector2f& p4);
        static bool m_OnLine(const sf::Vector2f& p, const sf::Vector2f& start, const sf::Vector2f& end);
        static bool m_OnSeg(const sf::Vector2f& p, const sf::Vector2f& start, const sf::Vector2f& end);
        static bool m_PointsMatch(const sf::Vector2f& p1, const sf::Vector2f& p2);
        static float m_GetWinding(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3);
        static void m_CreateFixture(const Shape& points, b2Body* body);
        static bool m_CheckShape(MapObject& object);
    };
}

#endif /* TMXHELPER_HPP */

