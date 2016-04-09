/* 
 * File:   Render.cpp
 * Author: linuxero
 * 
 * Created on March 5, 2014, 8:08 AM
 */

#include "Render.hpp"

Render::Render() : sprite(), renderPos() {
}

Render::Render(const Render& orig) {
}

Render::~Render() {
}

void Render::SetTexture(sf::Texture &tex) {
    sprite = sf::Sprite(tex);

}

void Render::SetTextureRect(sf::IntRect rect) {
    sprite.setTextureRect(rect);
}

void Render::PlayAnimation(Animation animation) {
    animatedSprite.play(animation);
}

void Render::UpdateAnimation(sf::Time elapsedTime) {
    animatedSprite.update(elapsedTime);
}

void Render::StopAnimation() {
    //if(&animatedSprite!=NULL){
    animatedSprite.stop();
    //}

}

void Render::Draw(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation) {
    renderPos = sf::Vector2f(
            posPrev.x + ((posNew.x - posPrev.x) * interpolation),
            posPrev.y + ((posNew.y - posPrev.y) * interpolation));

    sprite.setPosition(renderPos.x, renderPos.y);
    window.draw(sprite);
}
void Render::DrawAnimation(sf::RenderWindow& window, const sf::Vector2f& posPrev, const sf::Vector2f& posNew, float interpolation, int top, int bot, int right, int left, Map *mapa){
    renderPos = sf::Vector2f(
            posPrev.x + ((posNew.x - posPrev.x) * interpolation),
            posPrev.y + ((posNew.y - posPrev.y) * interpolation));
    
    top = top/16;
    bot = bot/16;
    left= left/16;
    right= right/16;
    
    printf("(%d,%d,%d,%d)\n",top,bot,left,right);
    
     if (mapa->_tilemap[2][top][left] == 160) {
        printf("entro\n");
      //  player->SetPosition(player->GetPreviousPosition());
    }else if (mapa->_tilemap[2][top][right] == 160) {
           printf("entro1\n");
      //  player->SetPosition(player->GetPreviousPosition());
    }else if (mapa->_tilemap[2][bot][left] == 160) {
            printf("entro2\n");
       // player->SetPosition(player->GetPreviousPosition());
    }else if (mapa->_tilemap[2][bot][right] == 160) {
            printf("entro3\n");
        //player->SetPosition(player->GetPreviousPosition());
    }else{
        animatedSprite.setPosition(renderPos.x, renderPos.y);
    }
    window.draw(animatedSprite);
}
void Render::DrawAnimation(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation) {
    renderPos = sf::Vector2f(
            posPrev.x + ((posNew.x - posPrev.x) * interpolation),
            posPrev.y + ((posNew.y - posPrev.y) * interpolation));

        animatedSprite.setPosition(renderPos.x, renderPos.y);
    
    window.draw(animatedSprite);
}