/* 
 * File:   Player.cpp
 * Author: linuxero
 * 
 * Created on March 5, 2014, 7:43 AM
 */

#include "Player.hpp"
#include "Util.hpp"
#include "../States/InGame.hpp"
#include "../Otros/tmxHelper.hpp"

Player::Player(BoundingBox *rectPlayer) : Collisionable((Entity*)this, rectPlayer) {

}

/*Player::Player(const Player& orig) {
}*/

Player::~Player() {
}

void Player::Inicializar(float posX, float posY, float speedX, float speedY, float maxSpeedX, float maxSpeedY) {
    /*Reservamos memoria para los punteros de Animation*/

    walkingAnimationDown = new Animation();
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    walkingAnimationUp = new Animation();
    castingAnimationUp = new Animation();
    castingAnimationDown = new Animation();
    castingAnimationRight = new Animation();
    castingAnimationLeft = new Animation();
    hud = new Hud();
    hRayoBasico = new hRayBasic();
    hRayoAvanzado = new hRayAdvanced();

    if (!texturaPlayer.loadFromFile("resources/Textures/player.png")) {
        std::cout << "Error cargando la textura: " << "resources/Textures/player.png" << std::endl;
        exit(0);
    }
    texturaPlayer.setSmooth(true);

    walkingAnimationDown->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationDown->addFrame(sf::IntRect(512, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(0, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(64, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(128, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(192, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(256, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(320, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(384, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(448, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(512, 640, 64, 64));


    walkingAnimationLeft->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationLeft->addFrame(sf::IntRect(512, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(0, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(64, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(128, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(192, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(256, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(320, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(384, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(448, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(512, 576, 64, 64));

    walkingAnimationRight->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationRight->addFrame(sf::IntRect(512, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(0, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(64, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(128, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(192, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(256, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(320, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(384, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(448, 704, 64, 64));


    walkingAnimationUp->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationUp->addFrame(sf::IntRect(512, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(0, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(64, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(128, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(192, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(256, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(320, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(384, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(448, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(512, 512, 64, 64));

    //casteo
    castingAnimationUp->setSpriteSheet("resources/Textures/player.png");
    castingAnimationUp->addFrame(sf::IntRect(320, 768, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(0, 768, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(64, 768, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(128, 768, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(192, 768, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(256, 768, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(320, 768, 64, 64));




    castingAnimationDown->setSpriteSheet("resources/Textures/player.png");
    castingAnimationDown->addFrame(sf::IntRect(320, 896, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(0, 896, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(64, 896, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(128, 896, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(192, 896, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(256, 896, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(320, 896, 64, 64));



    castingAnimationRight->setSpriteSheet("resources/Textures/player.png");
    castingAnimationRight->addFrame(sf::IntRect(320, 960, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(0, 960, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(64, 960, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(128, 960, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(192, 960, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(256, 960, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(320, 960, 64, 64));



    castingAnimationLeft->setSpriteSheet("resources/Textures/player.png");
    castingAnimationLeft->addFrame(sf::IntRect(320, 832, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(0, 832, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(64, 832, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(128, 832, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(192, 832, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(256, 832, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(320, 832, 64, 64));



    currentAnimation = &walkingAnimationDown;
    InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    SetPosition(posX, posY);
    SetSpeed(speedX, speedY);
    SetMaxSpeed(maxSpeedX, maxSpeedY);
    SetOriginAnimatedSprite(32, 40);
    SetOriginColision(32,32);
    SetScale(1.0, 1.0);
    //playerShape = sf::RectangleShape(sf::Vector2f(36, 52));
    //playerShape.setPosition(GetRectangleColisionAbsolute().GetTopLeft().x + 36, GetRectangleColisionAbsolute().GetTopLeft().y + 52);
    //playerShape.setOrigin(0,0);
    playerShape = sf::RectangleShape(sf::Vector2f(24,24));
}

void Player::Update(const sf::Time elapsedTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (isMovingUp)
        movement.y -= getVelocidad();
    if (isMovingDown)
        movement.y += getVelocidad();
    if (isMovingLeft)
        movement.x -= getVelocidad();
    if (isMovingRight)
        movement.x += getVelocidad();

   // playerShape.setPosition(GetRectangleColisionAbsolute().GetTopLeft().x, GetRectangleColisionAbsolute().GetTopLeft().y);
    /**Hay que normalizar la velocidad**/
   // sf::Vector2f nVelocity = Util::Normalize(movement);
     //SetSpeed(nVelocity * Player::getVelocidad());
    body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(movement)*Player::getVelocidad()));
    //SetSpeed(tmx::BoxToSfVec(body->GetLinearVelocity()));
    //SetPosition(body->GetPosition());
    
    //body->SetLinearVelocity(tmx::SfToBoxVec(movement));
    //HandleMapCollisions(elapsedTime);
    
    //PhysicsState::Update(elapsedTime);
   // body->SetTransform(tmx::SfToBoxVec(GetPosition()),body->GetAngle());
    SetPosition(tmx::BoxToSfVec(body->GetPosition()));
    //
}

//void Player::HandleMapCollisions(const sf::Time& elapsedTime) {
//    //InGame* world = InGame::Instance();
//    //world->level->updateQuadTree();
//    //objetosCercanos = world->level->queryQuadTree(*CalculateNextRect(elapsedTime).GetRectangle());
//    //std::vector<Colision::Type> type;
//   /* for (int i = 0; i < objetosCercanos.size(); i++) {
//        BoundingBox bb(objetosCercanos.at(i)->GetAABB());
//        if (CheckColision(bb, elapsedTime)) {
//            type = TypeOfColision(bb, elapsedTime);
//            OnColision(type);
//        }
//    }*/
//    int tileWidth = 24;
//    int tileHeight = 24;
//    int **colisiones = world->level->map->colisiones;
//    int height = world->level->map->_height;
//    int width = world->level->map->_width;
//    /*for(int i=0 ; i < width ; i++){
//        for(int j= 0;j<height; j++){
//            std::cout<<colisiones[i][j];
//        }
//        std::cout<<std::endl;
//    }*/
//
//    BoundingBox boundingPlayer = CalculateNextRect(elapsedTime);
//    sf::Vector2i indiceTopLeft = sf::Vector2i(boundingPlayer.GetTopLeft().x/24,boundingPlayer.GetTopLeft().y/24);
//    sf::Vector2i indiceTopRight = sf::Vector2i(boundingPlayer.GetTopRight().x/24,boundingPlayer.GetTopRight().y/24);
//    sf::Vector2i indiceBotLeft = sf::Vector2i(boundingPlayer.GetBottomLeft().x/24,boundingPlayer.GetBottomLeft().y/24);
//    sf::Vector2i indiceBotRight = sf::Vector2i(boundingPlayer.GetBottomRight().x/24,boundingPlayer.GetBottomRight().y/24);
//    /*std::cout<<"xTopright"<<indiceTopRight.x<<" , "<<"yTopright"<<indiceTopRight.y<<std::endl;
//    std::cout<<"Valor mapa"<<colisiones[indiceTopRight.x][indiceTopRight.y]<<std::endl;*/
//    if(colisiones[indiceTopLeft.y][indiceTopLeft.x] == 1){
//        //std::cout<<"Colisiona esquina superior izquierda"<<std::endl;
//        BoundingBox boundingArbol(indiceTopLeft.x*24,indiceTopLeft.y*24,24,24);
//        
//        playerShape.setPosition(sf::Vector2f(indiceTopLeft.x*24,indiceTopLeft.y*24));
//        playerShape.setFillColor(sf::Color::Red);
//        //Hacer algo
//        SetSpeed(0,0);
//    }
//    else if(colisiones[indiceTopRight.y][indiceTopRight.x] == 1){
//        //std::cout<<"Colisiona esquina superior derecha"<<std::endl;
//        BoundingBox boundingArbol((indiceTopRight.x*24),(indiceTopRight.y*24),24,24);
//        playerShape.setPosition(sf::Vector2f(indiceTopRight.x*24,indiceTopRight.y*24));
//        playerShape.setFillColor(sf::Color::Red);
//        //Hacer algo
//        SetSpeed(0,0);
//    }
//    else if(colisiones[indiceBotLeft.y][indiceBotLeft.x] == 1){
//        //std::cout<<"Colisiona esquina inferior izquierda"<<std::endl;
//        BoundingBox boundingArbol((indiceBotLeft.x*24),(indiceBotLeft.y*24),24,24);
//        playerShape.setPosition(sf::Vector2f(indiceBotLeft.x*24,indiceBotLeft.y*24));
//        playerShape.setFillColor(sf::Color::Red);
//        
//        SetSpeed(0,0);
//    }
//    else if(colisiones[indiceBotRight.y][indiceBotRight.x] == 1){
//        //std::cout<<"Colisiona esquina inferior derecha"<<std::endl;
//        BoundingBox boundingArbol((indiceBotRight.x*24),(indiceBotRight.y*24),24,24);
//        playerShape.setPosition(sf::Vector2f(indiceBotRight.x*24,indiceBotRight.y*24));
//        playerShape.setFillColor(sf::Color::Red);
//        
//        SetSpeed(0,0);
//    }
//    /*sf::Vector2f nextPos = GetNextPosition(elapsedTime);
//    int top=(int)nextPos.y-16;
//    int bot=(int)nextPos.y+16;
//    int left=(int)nextPos.x-16;
//    int right=(int)nextPos.x+16;
//    int left_right = (left+right)/2;
//    int top_bot = (top+bot)/2;
//    top=top/16;
//    bot=bot/16;
//    left=left/16;
//    right=right/16;
//    left_right=left_right/16;
//    top_bot=top_bot/16;
//    
//     sf::Vector2f speed2 = speed;
//    if (mapa->_tilemap[3][top][left_right] != 0 && mapa->_tilemap[3][top_bot][left] != 0) {
//        posPrev = posNew;
//    }else if (mapa->_tilemap[3][top][left_right] != 0 && mapa->_tilemap[3][top_bot][right] != 0) {
//        posPrev = posNew;
//    }else if (mapa->_tilemap[3][bot][left_right] != 0 && mapa->_tilemap[3][top_bot][left] != 0) {
//        posPrev = posNew;
//    }else if (mapa->_tilemap[3][bot][left_right] != 0 && mapa->_tilemap[3][top_bot][right] != 0) {
//        posPrev = posNew;
//    }else if (mapa->_tilemap[3][top][left_right] != 0) {
//        if(speed2.y<0){
//               speed2.y=0;  
//             }
//             posPrev = posNew;
//             posNew += speed2 * elapsedTime.asSeconds();
//    }else if (mapa->_tilemap[3][bot][left_right] != 0) {
//         if(speed2.y>0){
//               speed2.y=0;  
//             }
//             posPrev = posNew;
//             posNew += speed2 * elapsedTime.asSeconds();
//    }else if (mapa->_tilemap[3][top_bot][left] != 0) {
//        if(speed2.x<0){
//               speed2.x=0;  
//             }
//             posPrev = posNew;
//             posNew += speed2 * elapsedTime.asSeconds();
//    }else if (mapa->_tilemap[3][top_bot][right] != 0) {
//                if(speed2.x>0){
//               speed2.x=0;  
//             }
//             posPrev = posNew;
//             posNew += speed2 * elapsedTime.asSeconds();
//    }else if (mapa->_tilemap[3][top][left] != 0 && mapa->_tilemap[3][top_bot][left] == 0 && mapa->_tilemap[3][top][left_right] == 0) {
//             if(speed2.y<0){
//               speed2.y=0;  
//             }
//             if(speed2.x<0){
//               speed2.x=0;  
//             }
//             posPrev = posNew;
//             posNew += speed2 * elapsedTime.asSeconds();
//
//    }else if (mapa->_tilemap[3][top][right] != 0 && mapa->_tilemap[3][top_bot][right] == 0 && mapa->_tilemap[3][top][left_right] == 0) {
//             if(speed2.y<0){
//               speed2.y=0;  
//             }
//             if(speed2.x>0){
//               speed2.x=0;  
//             }
//             posPrev = posNew;
//             posNew += speed2 * elapsedTime.asSeconds();
//
//             posPrev = posNew;
//    } else if (mapa->_tilemap[3][bot][left] != 0 && mapa->_tilemap[3][top_bot][left] == 0 && mapa->_tilemap[3][bot][left_right] == 0) {
//             if(speed2.y>0){
//               speed2.y=0;  
//             }
//             if(speed2.x<0){
//               speed2.x=0;  
//             }
//             posPrev = posNew;
//             posNew += speed2 * elapsedTime.asSeconds();
//             
//
//    }else if (mapa->_tilemap[3][bot][right] != 0 && mapa->_tilemap[3][top_bot][right] == 0 && mapa->_tilemap[3][bot][left_right] == 0) {
//             if(speed2.y>0){
//               speed2.y=0;  
//             }
//             if(speed2.x>0){
//               speed2.x=0;  
//             }
//             posPrev = posNew;
//             posNew += speed2 * elapsedTime.asSeconds();
//
//             posPrev = posNew;
//    } else{
//        posPrev = posNew;
//        posNew += speed * elapsedTime.asSeconds();
//    }*/
//
//
//
//
//}

void Player::Draw() {
    GetSprite().setPosition(GetPosition().x, GetPosition().y);
    Motor2D::Instance()->draw(GetSprite());
}

void Player::DrawWithInterpolation(float interpolation) {
    Render::DrawAnimation(GetPreviousPosition(), GetPosition(), interpolation);
}

float Player::getVelocidad() {
    return velocity;
}

sf::Vector2f Player::getPosition() {
    return GetSpriteAnimated().getPosition();
}

void Player::UpdatePlayerAnimation(int x, int y) {
    //sf::Vector2f distancia(mouseSprite.getPosition().y - player -> GetRenderPosition().y, mouseSprite.getPosition().x - player -> GetRenderPosition().x);

    // 1 -> Arriba
    // 2 -> Abajo
    // 3 -> Derecha
    // 4 -> Izquierda


    if (abs(y) > abs(x) && y <= 0) {
        cuadrante = 1;
        currentAnimation = &walkingAnimationUp;
    } else if (abs(y) > abs(x) && y > 0) {
        currentAnimation = &walkingAnimationDown;
        cuadrante = 2;
    } else if (abs(x) > abs(y) && x > 0) {
        currentAnimation = &walkingAnimationRight;
        cuadrante = 3;
    } else {
        currentAnimation = &walkingAnimationLeft;
        cuadrante = 4;
    }
}

void Player::OnColision(std::vector<Colision::Type> type) {
    //std::cout<<GetPosition().x<<" , "<<GetPosition().y<<std::endl;
    //Colision solo por un lado
    if (type.size() == 1) {
        if (type.at(0) == Colision::Type::LEFT)
            SetSpeed(0.f, GetSpeed().y);
        else if (type.at(0) == Colision::Type::RIGHT)
            SetSpeed(0, GetSpeed().y);
        else if (type.at(0) == Colision::Type::TOP)
            SetSpeed(GetSpeed().x, 0);
        else if (type.at(0) == Colision::Type::BOTTOM)
            SetSpeed(GetSpeed().x, 0);
    //Colision en los 3 ejes
    } else if (type.size() == 3) {

        if (type.at(0) == Colision::Type::LEFT && type.at(1) == Colision::Type::BOTTOM && type.at(2) == Colision::Type::TOP) {
            if (GetSpeed().x < 0) {
                SetSpeed(0, 0);
            }else{
                SetSpeed(GetSpeed().x, 0);
            }
        } else if (type.at(0) == Colision::Type::RIGHT && type.at(1) == Colision::Type::BOTTOM && type.at(2) == Colision::Type::TOP) {
            if (GetSpeed().x > 0) {
                SetSpeed(0, 0);
            }else{
                SetSpeed(GetSpeed().x, 0);
            }
        } else if (type.at(0) == Colision::Type::LEFT && type.at(1) == Colision::Type::RIGHT && type.at(2) == Colision::Type::TOP) {
            if(GetSpeed().y < 0){
                SetSpeed(0, 0);
            }else{
                SetSpeed(0, GetSpeed().y);
            }
        } else if (type.at(0) == Colision::Type::LEFT && type.at(1) == Colision::Type::RIGHT && type.at(2) == Colision::Type::BOTTOM) {
            if(GetSpeed().y > 0){
                SetSpeed(0, 0);
            }else{
                SetSpeed(0, GetSpeed().y);
            }
        }
    //Colision 2 ejes
    } else {
        if (type.at(0) == Colision::Type::LEFT && type.at(1) == Colision::Type::BOTTOM) {
            if(GetSpeed().y > 0 && GetSpeed().x > 0){
                SetSpeed(GetSpeed().x,0);
            }else if(GetSpeed().y < 0 && GetSpeed().x < 0){
                SetSpeed(0,GetSpeed().y);
            }else if(GetSpeed().y > 0 && GetSpeed().x < 0 ){
                SetSpeed(0,GetSpeed().y);
            }else if(GetSpeed().y < 0 && GetSpeed().x > 0){//??
                SetSpeed(GetSpeed().x,0);
            }else{
                SetSpeed(0,0);
            }
            //SetSpeed(GetSpeed().x,0);
        } else if (type.at(0) == Colision::Type::RIGHT && type.at(1) == Colision::Type::BOTTOM){
            if(GetSpeed().y > 0 && GetSpeed().x > 0){
                SetSpeed(GetSpeed().y,0);
            }else if(GetSpeed().y < 0 && GetSpeed().x < 0){//???
                SetSpeed(0,GetSpeed().y);
            }else if(GetSpeed().y > 0 && GetSpeed().x < 0 ){
                SetSpeed(0,GetSpeed().y);
            }else if(GetSpeed().y < 0 && GetSpeed().x > 0){
                SetSpeed(0,GetSpeed().y);
            }else{
                SetSpeed(0,0);
            }
            
        } else if(type.at(0) == Colision::Type::LEFT && type.at(1) == Colision::Type::TOP){
            if(GetSpeed().y > 0 && GetSpeed().x > 0){//??
                SetSpeed(0,GetSpeed().y);
            }else if(GetSpeed().y < 0 && GetSpeed().x < 0){
                SetSpeed(GetSpeed().x,0);
            }else if(GetSpeed().y > 0 && GetSpeed().x < 0 ){
                SetSpeed(0,GetSpeed().y);
            }else if(GetSpeed().y < 0 && GetSpeed().x > 0){
                SetSpeed(GetSpeed().x,0);
            }else{
                SetSpeed(0,0);
            }
        } else if(type.at(0) == Colision::Type::RIGHT && type.at(1) == Colision::Type::TOP){
           if(GetSpeed().y > 0 && GetSpeed().x > 0){
                SetSpeed(0,GetSpeed().y);
            }else if(GetSpeed().y < 0 && GetSpeed().x < 0){
                SetSpeed(GetSpeed().x,0);
            }else if(GetSpeed().y > 0 && GetSpeed().x < 0 ){//??
                SetSpeed(0,GetSpeed().y);
            }else if(GetSpeed().y < 0 && GetSpeed().x > 0){
                SetSpeed(0,GetSpeed().y);
            }else{
                SetSpeed(0,0);
            }
        }
    }

}
