#include "Player.hpp"
#include "Util.hpp"
#include "../States/InGame.hpp"
#include "../Otros/tmxHelper.hpp"

Player::Player() : Collisionable((Entity*)this) {

}

Player::~Player() {
	delete hud;
}

void Player::Inicializar(float posX, float posY, float speedX, float speedY, float maxSpeedX, float maxSpeedY) {
    /*Reservamos memoria para los punteros de Animation*/

    walkingAnimationDown = new Animation();
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    walkingAnimationUp = new Animation();

    //casteo rayo
    castingAnimationUpRayo= new Animation();
    castingAnimationDownRayo= new Animation();
    castingAnimationRightRayo= new Animation();
    castingAnimationLeftRayo= new Animation();
    //casteo Fuego
    castingAnimationUpFuego= new Animation();
    castingAnimationDownFuego= new Animation();
    castingAnimationRightFuego= new Animation();
    castingAnimationLeftFuego= new Animation();
    //casteo Agua
    castingAnimationUpAgua= new Animation();
    castingAnimationDownAgua= new Animation();
    castingAnimationRightAgua= new Animation();
    castingAnimationLeftAgua= new Animation();
    
    //fuego
    fuegoAnimationDown = new Animation();
    fuegoAnimationLeft = new Animation();
    fuegoAnimationRight = new Animation();
    fuegoAnimationUp = new Animation();
    fuego2AnimationDown = new Animation();
    fuego2AnimationLeft = new Animation();
    fuego2AnimationRight = new Animation();
    fuego2AnimationUp = new Animation();
    //heal
    healingAnimationDown = new Animation();
    healingAnimationLeft = new Animation();
    healingAnimationRight = new Animation();
    healingAnimationUp = new Animation();


    hRayoBasico = new hRayBasic();
    hRayoAvanzado = new hRayAdvanced();
    
    hFuegoBasico = new hFireBasic[50];
    hFuegoAvanzado = new hFireAdvanced();
    
    hAguaBasico=new hWaterBasic();
    hAguaAvanzado = new hWaterAdvanced();
    
    hHeal = new Heal();
    
    flash = new Flash(1);//Animacion que aparece en la posicion que deja el jugador
    flash2 = new Flash(2);//Animacion que aparece a la posicion en que se ha movido el jugador

    
    Reloj *relojes = new Reloj[6];
    relojes[0] = hRayoBasico->tiempoCd;
    relojes[1] = hRayoAvanzado->tiempoCd;
    
    float *cds = new float[8];
    
    cds[0] = hRayoBasico->getCD();
    cds[1] = hRayoAvanzado->getCD();
    cds[2] = hAguaBasico->getCD();
    cds[3] = hAguaAvanzado->getCD();
    cds[4] = CDFire;
    cds[5] = hFuegoAvanzado->getCD();
    cds[6] = flash->getCD();
    cds[7] = hHeal->getCD();
    
    
    hud = new Hud(relojes,cds);

    if(!texturaPlayer.loadFromFile("resources/Textures/player.png")){
       std::cout<<"Error cargando la textura: "<<"resources/Textures/player.png"<<std::endl;
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
    
    //casteo Rayo
    castingAnimationUpRayo->setSpriteSheet("resources/Textures/player.png");
    castingAnimationUpRayo->addFrame(sf::IntRect(320, 768, 64, 64));
    castingAnimationUpRayo->addFrame(sf::IntRect(0, 768, 64, 64));
    castingAnimationUpRayo->addFrame(sf::IntRect(64, 768, 64, 64));
    castingAnimationUpRayo->addFrame(sf::IntRect(128, 768, 64, 64));
    castingAnimationUpRayo->addFrame(sf::IntRect(192, 768, 64, 64));
    castingAnimationUpRayo->addFrame(sf::IntRect(256, 768, 64, 64));
    castingAnimationUpRayo->addFrame(sf::IntRect(320, 768, 64, 64));
  
 
    castingAnimationDownRayo->setSpriteSheet("resources/Textures/player.png");
    castingAnimationDownRayo->addFrame(sf::IntRect(320, 896, 64, 64));
    castingAnimationDownRayo->addFrame(sf::IntRect(0, 896, 64, 64));
    castingAnimationDownRayo->addFrame(sf::IntRect(64, 896, 64, 64));
    castingAnimationDownRayo->addFrame(sf::IntRect(128, 896, 64, 64));
    castingAnimationDownRayo->addFrame(sf::IntRect(192, 896, 64, 64));
    castingAnimationDownRayo->addFrame(sf::IntRect(256, 896, 64, 64));
    castingAnimationDownRayo->addFrame(sf::IntRect(320, 896, 64, 64));
 
    
    castingAnimationRightRayo->setSpriteSheet("resources/Textures/player.png");
    castingAnimationRightRayo->addFrame(sf::IntRect(320, 960, 64, 64));
    castingAnimationRightRayo->addFrame(sf::IntRect(0, 960, 64, 64));
    castingAnimationRightRayo->addFrame(sf::IntRect(64, 960, 64, 64));
    castingAnimationRightRayo->addFrame(sf::IntRect(128, 960, 64, 64));
    castingAnimationRightRayo->addFrame(sf::IntRect(192, 960, 64, 64));
    castingAnimationRightRayo->addFrame(sf::IntRect(256, 960, 64, 64));
    castingAnimationRightRayo->addFrame(sf::IntRect(320, 960, 64, 64));
  
   
    castingAnimationLeftRayo->setSpriteSheet("resources/Textures/player.png");
    castingAnimationLeftRayo->addFrame(sf::IntRect(320, 832, 64, 64));
    castingAnimationLeftRayo->addFrame(sf::IntRect(0, 832, 64, 64));
    castingAnimationLeftRayo->addFrame(sf::IntRect(64, 832, 64, 64));
    castingAnimationLeftRayo->addFrame(sf::IntRect(128, 832, 64, 64));
    castingAnimationLeftRayo->addFrame(sf::IntRect(192, 832, 64, 64));
    castingAnimationLeftRayo->addFrame(sf::IntRect(256, 832, 64, 64));
    castingAnimationLeftRayo->addFrame(sf::IntRect(320, 832, 64, 64));
 
    //Casteo Agua
    //casteo
    castingAnimationUpAgua->setSpriteSheet("resources/Textures/player.png");
    castingAnimationUpAgua->addFrame(sf::IntRect(448, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(0, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(64, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(128, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(192, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(256, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(320, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(384, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(448, 256, 64, 64));  
    
    castingAnimationDownAgua->setSpriteSheet("resources/Textures/player.png");
    castingAnimationDownAgua->addFrame(sf::IntRect(448, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(0, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(64, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(128, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(192, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(256, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(320, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(384, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(448, 384, 64, 64));
    
    
    castingAnimationRightAgua->setSpriteSheet("resources/Textures/player.png");
    castingAnimationRightAgua->addFrame(sf::IntRect(448, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(0, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(64, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(128, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(192, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(256, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(320, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(384, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(448, 448, 64, 64));
    
    castingAnimationLeftAgua->setSpriteSheet("resources/Textures/player.png");
    castingAnimationLeftAgua->addFrame(sf::IntRect(448, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(0, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(64, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(128, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(192, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(256, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(320, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(384, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(448, 320, 64, 64));
    
    /////////////////////////////////
    //Fuegooo
    //castingAnimationLeftFuego
    fuegoAnimationUp->setSpriteSheet("resources/Textures/player.png");
    //fuegoAnimationUp->addFrame(sf::IntRect(320, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(0, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(64, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(128, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(192, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(256, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(320, 768, 64, 64));
  
    fuegoAnimationDown->setSpriteSheet("resources/Textures/player.png");
    //fuegoAnimationDown->addFrame(sf::IntRect(320, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(0, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(64, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(128, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(192, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(256, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(320, 896, 64, 64));
 
    
    
    fuegoAnimationRight->setSpriteSheet("resources/Textures/player.png");
    //fuegoAnimationRight->addFrame(sf::IntRect(320, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(0, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(64, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(128, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(192, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(256, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(320, 960, 64, 64));
  
    
    
    fuegoAnimationLeft->setSpriteSheet("resources/Textures/player.png");
    //fuegoAnimationLeft->addFrame(sf::IntRect(320, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(0, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(64, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(128, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(192, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(256, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(320, 832, 64, 64));

    fuego2AnimationDown->setSpriteSheet("resources/Textures/player.png");
    fuego2AnimationDown->addFrame(sf::IntRect(384, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(0, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(64, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(128, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(192, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(256, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(320, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(384, 128, 64, 64));


    fuego2AnimationLeft->setSpriteSheet("resources/Textures/player.png");
    fuego2AnimationLeft->addFrame(sf::IntRect(384, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(0, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(64, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(128, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(192, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(256, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(320, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(384, 64, 64, 64));

    fuego2AnimationRight->setSpriteSheet("resources/Textures/player.png");
    fuego2AnimationRight->addFrame(sf::IntRect(384, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(0, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(64, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(128, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(192, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(256, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(320, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(384, 192, 64, 64));


    fuego2AnimationUp->setSpriteSheet("resources/Textures/player.png");
    fuego2AnimationUp->addFrame(sf::IntRect(384, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(0, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(64, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(128, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(192, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(256, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(320, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(384, 0, 64, 64));
    
    //casteo heal
    

    healingAnimationDown->setSpriteSheet("resources/Textures/player.png");
    healingAnimationDown->addFrame(sf::IntRect(384, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(0, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(64, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(128, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(192, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(256, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(320, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(384, 128, 64, 64));










    healingAnimationLeft->setSpriteSheet("resources/Textures/player.png");
    healingAnimationLeft->addFrame(sf::IntRect(384, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(0, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(64, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(128, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(192, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(256, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(320, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(384, 64, 64, 64));

    healingAnimationRight->setSpriteSheet("resources/Textures/player.png");
    healingAnimationRight->addFrame(sf::IntRect(384, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(0, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(64, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(128, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(192, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(256, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(320, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(384, 192, 64, 64));










    healingAnimationUp->setSpriteSheet("resources/Textures/player.png");
    healingAnimationUp->addFrame(sf::IntRect(384, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(0, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(64, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(128, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(192, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(256, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(320, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(384, 0, 64, 64));
    
    currentAnimation = &walkingAnimationDown;

    InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    SetPosition(posX, posY);
    SetSpeed(speedX, speedY);
    SetMaxSpeed(maxSpeedX, maxSpeedY);
	SetOriginAnimatedSprite(32,40);
    SetOriginColision(32, 40);

}

void Player::Update(const sf::Time elapsedTime) {
    sf::Vector2f movement(0.f, 0.f);
    if(!cantMove){
        if (isMovingUp)
            movement.y -= GetVelocity();
        if (isMovingDown)
            movement.y += GetVelocity();
        if (isMovingLeft)
            movement.x -= GetVelocity();
        if (isMovingRight)
            movement.x += GetVelocity();
    }
    //Hay que setear al BodyDef el vector velocidad que hallamos calculado
    body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(movement) * Player::GetVelocity()));
    //Actualizamos la posicion del player con la posicion del bodyDef
    SetPosition(tmx::BoxToSfVec(body->GetPosition()));

}

void Player::HandleMapCollisions(const sf::Time& elapsedTime) {
    InGame* world = InGame::Instance();
   /* for (int i = 0; i < objetosCercanos.size(); i++) {
        BoundingBox bb(objetosCercanos.at(i)->GetAABB());
        if (CheckColision(bb, elapsedTime)) {
            type = TypeOfColision(bb, elapsedTime);
            OnColision(type);
        }
    }*/
    int tileWidth = 24;
    int tileHeight = 24;
    int **colisiones = world->level->map->colisiones;
    int height = world->level->map->_height;
    int width = world->level->map->_width;
    /*for(int i=0 ; i < width ; i++){
        for(int j= 0;j<height; j++){
            std::cout<<colisiones[i][j];
        }
        std::cout<<std::endl;
    }*/

    BoundingBox boundingPlayer = Collisionable::CalculateNextRect(elapsedTime);
    sf::Vector2i indiceTopLeft = sf::Vector2i(boundingPlayer.GetTopLeft().x/24,boundingPlayer.GetTopLeft().y/24);
    sf::Vector2i indiceTopRight = sf::Vector2i(boundingPlayer.GetTopRight().x/24,boundingPlayer.GetTopRight().y/24);
    sf::Vector2i indiceBotLeft = sf::Vector2i(boundingPlayer.GetBottomLeft().x/24,boundingPlayer.GetBottomLeft().y/24);
    sf::Vector2i indiceBotRight = sf::Vector2i(boundingPlayer.GetBottomRight().x/24,boundingPlayer.GetBottomRight().y/24);
    /*std::cout<<"xTopright"<<indiceTopRight.x<<" , "<<"yTopright"<<indiceTopRight.y<<std::endl;
    std::cout<<"Valor mapa"<<colisiones[indiceTopRight.x][indiceTopRight.y]<<std::endl;*/
    if(colisiones[indiceTopLeft.y][indiceTopLeft.x] == 1){
        //std::cout<<"Colisiona esquina superior izquierda"<<std::endl;
        BoundingBox boundingArbol(indiceTopLeft.x*24,indiceTopLeft.y*24,24,24);
        
        //Hacer algo
        PhysicsState::SetSpeed(0,0);
    }
    else if(colisiones[indiceTopRight.y][indiceTopRight.x] == 1){
        //std::cout<<"Colisiona esquina superior derecha"<<std::endl;
        BoundingBox boundingArbol((indiceTopRight.x*24),(indiceTopRight.y*24),24,24);
        //Hacer algo
        PhysicsState::SetSpeed(0,0);
    }
    else if(colisiones[indiceBotLeft.y][indiceBotLeft.x] == 1){
        //std::cout<<"Colisiona esquina inferior izquierda"<<std::endl;
        BoundingBox boundingArbol((indiceBotLeft.x*24),(indiceBotLeft.y*24),24,24);

        
        PhysicsState::SetSpeed(0,0);
    }
    else if(colisiones[indiceBotRight.y][indiceBotRight.x] == 1){
        //std::cout<<"Colisiona esquina inferior derecha"<<std::endl;
        BoundingBox boundingArbol((indiceBotRight.x*24),(indiceBotRight.y*24),24,24);

        PhysicsState::SetSpeed(0,0);
    }
    /*sf::Vector2f nextPos = GetNextPosition(elapsedTime);
    int top=(int)nextPos.y-16;
    int bot=(int)nextPos.y+16;
    int left=(int)nextPos.x-16;
    int right=(int)nextPos.x+16;
    int left_right = (left+right)/2;
    int top_bot = (top+bot)/2;
    top=top/16;
    bot=bot/16;
    left=left/16;
    right=right/16;
    left_right=left_right/16;
    top_bot=top_bot/16;
    
     sf::Vector2f speed2 = speed;
    if (mapa->_tilemap[3][top][left_right] != 0 && mapa->_tilemap[3][top_bot][left] != 0) {
        posPrev = posNew;
    }else if (mapa->_tilemap[3][top][left_right] != 0 && mapa->_tilemap[3][top_bot][right] != 0) {
        posPrev = posNew;
    }else if (mapa->_tilemap[3][bot][left_right] != 0 && mapa->_tilemap[3][top_bot][left] != 0) {
        posPrev = posNew;
    }else if (mapa->_tilemap[3][bot][left_right] != 0 && mapa->_tilemap[3][top_bot][right] != 0) {
        posPrev = posNew;
    }else if (mapa->_tilemap[3][top][left_right] != 0) {
        if(speed2.y<0){
               speed2.y=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
    }else if (mapa->_tilemap[3][bot][left_right] != 0) {
         if(speed2.y>0){
               speed2.y=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
    }else if (mapa->_tilemap[3][top_bot][left] != 0) {
        if(speed2.x<0){
               speed2.x=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
    }else if (mapa->_tilemap[3][top_bot][right] != 0) {
                if(speed2.x>0){
               speed2.x=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
    }else if (mapa->_tilemap[3][top][left] != 0 && mapa->_tilemap[3][top_bot][left] == 0 && mapa->_tilemap[3][top][left_right] == 0) {
             if(speed2.y<0){
               speed2.y=0;  
             }
             if(speed2.x<0){
               speed2.x=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();

    }else if (mapa->_tilemap[3][top][right] != 0 && mapa->_tilemap[3][top_bot][right] == 0 && mapa->_tilemap[3][top][left_right] == 0) {
             if(speed2.y<0){
               speed2.y=0;  
             }
             if(speed2.x>0){
               speed2.x=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();

             posPrev = posNew;
    } else if (mapa->_tilemap[3][bot][left] != 0 && mapa->_tilemap[3][top_bot][left] == 0 && mapa->_tilemap[3][bot][left_right] == 0) {
             if(speed2.y>0){
               speed2.y=0;  
             }
             if(speed2.x<0){
               speed2.x=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
             

    }else if (mapa->_tilemap[3][bot][right] != 0 && mapa->_tilemap[3][top_bot][right] == 0 && mapa->_tilemap[3][bot][left_right] == 0) {
             if(speed2.y>0){
               speed2.y=0;  
             }
             if(speed2.x>0){
               speed2.x=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();

             posPrev = posNew;
    } else{
        posPrev = posNew;
        posNew += speed * elapsedTime.asSeconds();
    }*/




}

void Player::Draw() {
    GetSprite().setPosition(GetPosition().x, GetPosition().y);
    Motor2D::Instance()->draw(GetSprite());
}

void Player::DrawWithInterpolation(float interpolation) {
    Render::DrawAnimation(GetPreviousPosition(), GetPosition(), interpolation);
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
int Player::getVida() {
    return vida;
}

int Player::restaVida(int a) {

    if (invulnerable.getTiempo() > 0.5f && (vida-a) >= 0) {
        //std::cout <<"Resto vidas";
        vida -= a;
        hud->updateHud(vida);
        invulnerable.restart();
    }


    return vida;
}

void Player::heal() {
    if (hHeal->cast(hud)) {
        //std::cout <<"Sumo vidas";
        vida += 2;
        if (vida > 15) {
            vida = 15;

        }
        hud->updateHud(vida);
    }
}

void Player::Colocar(sf::Vector2f NuevaPosicion) {
    SetPosition(NuevaPosicion);
}

void Player::updateRayo(bool isShooting) {
          
            
            if (hRayoBasico->tiempoCast.getTiempo() > hRayoBasico->getCast() && aux == true) {
                isShooting = false;
                hRayoBasico->primerCast = false;
            }

            if ((isShooting && hRayoBasico->tiempoCd.getTiempo() > hRayoBasico->getCD()) || (isShooting && hRayoBasico->primerCast == true)) {//Entra si dispara y el tiempo de enfriamiento ha pasado
                hRayoBasico->primerCast = false;
                if (aux == false) {//si es la primera vez que pulsa el boton
                    hRayoBasico->tiempoCast.restart();
                    aux = true; //no entra mas aqui para no hacer restart del cast
                }
                
                hRayoBasico->cast(sf::Vector2f(getPosition())); //siempre que entra aqui pintas

            } else {//entras si no disparas o si no ha pasado el tiempo de enfriamiento
                if (aux == true) {//entras si acabas de soltar el raton
                    hRayoBasico->tiempoCd.restart();
                    //if(hRayoBasico->primerCast)
                       hud->resetRayo1(); 
                    //}
                    
                    // std::cout<<"Inicio den CD"<<std::endl;
                    aux = false; //no entra mas aqui para no hacer restart dl cd
                }
                hRayoBasico->draw = false;
            }
            //avanzado

            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && hRayoAvanzado->tiempoCast.getTiempo() > hRayoBasico->getCast()) {
                hRayoAvanzado->draw = false;
                hRayoAvanzado->StopAnimation();
            }
}

void Player::updateFuego(bool fuegoBasicCast, bool fuegoAdvancedCast, sf::Time elapsedTime) {

        sf::Vector2f movement2(0.f, 0.f);
        
        if (fuegoBasicCast) {
            if (contFuego == 49) {
                contFuego = 0;
            }
            if (clockCDFire.getTiempo() > CDFire || primercastFuego == true) {
                primercastFuego = false;
                clockCDFire.restart();
                hFuegoBasico[contFuego].cast(sf::Vector2f(getPosition()));
                castFire.restart();
                hud->resetFuego1();
            }
            contFuego++;
        }
        for (int aux = 0; aux <= 49; aux++) {
            movement2.x = (40 * cos(hFuegoBasico[aux].angleshot2) * 10.0f);
            movement2.y = (40 * sin(hFuegoBasico[aux].angleshot2) * 10.0f);
            hFuegoBasico[aux].Update2(movement2, elapsedTime);
        }
        if (fuegoAdvancedCast) {

            if (hFuegoAvanzado->clockCd.getTiempo() > hFuegoAvanzado->getCD() || hFuegoAvanzado->primerCast == true) {

                hFuegoAvanzado->primerCast = false;
                hFuegoAvanzado->tiempoCast.restart();
                hFuegoAvanzado->clockCd.restart();
                hFuegoAvanzado->lanzado = true;
                castFire2.restart();

                /*hFuegoAvanzado->actualSize.x = 0.3;
                hFuegoAvanzado->actualSize.y = 0.3;
                hFuegoAvanzado->SetScale(0.3, 0.3);*/
                hFuegoAvanzado->cast(sf::Vector2f(getPosition()));
                
                hud->resetFuego2();
            }
        }

        if (hFuegoAvanzado->lanzado == true) {

            hFuegoAvanzado->cast(sf::Vector2f(getPosition()));
        }
}

void Player::updateAgua(bool aguaBasicCast, bool aguaAdvancedCast, sf::Time elapsedTime) {
    sf::Vector2f movement = tmx::BoxToSfVec(body->GetLinearVelocity());
    if (aguaBasicCast) {
        hAguaBasico->cast(sf::Vector2f(getPosition()), hud);
    }
    if ( hAguaBasico->tiempoCast.getTiempo() < 0.5f &&  hAguaBasico->dibujar == true) {
        hAguaBasico->Update(movement, elapsedTime, GetVelocity());
        
        
        /* **************************PARA LA FUTURA CLASE ENTITY*************************
        if (hAguaBasico->GetGlobalBounds().intersects(enemigo[0].getSprite().getGlobalBounds())) {
            enemigo[0].empujado = true;
            enemigo[0].tiempoempujado.restart();
        }

        if (enemigo[0].empujado == true) {
            sf::Vector2f movement3(0.f, 0.f);
            movement3.x = 300 * (cos(hAguaBasico->angleshot2) * 1.0f);
            movement3.y = 300 * (sin(hAguaBasico->angleshot2) * 1.0f);
            enemigo[0].Update(movement3, elapsedTime);
        }

        if (enemigo[0].tiempoempujado.getTiempo() > 0.5) {
            enemigo[0].empujado = false;
        }

        if (hAguaBasico->GetGlobalBounds().intersects(enemigo[1].getSprite().getGlobalBounds())) {
            enemigo[1].empujado = true;
            enemigo[1].tiempoempujado.restart();
        }

        if (enemigo[1].empujado == true) {
            sf::Vector2f movement3(0.f, 0.f);
            movement3.x = 300 * (cos(hAguaBasico->angleshot2) * 1.0f);
            movement3.y = 300 * (sin(hAguaBasico->angleshot2) * 1.0f);
            enemigo[1].Update(movement3, elapsedTime);
        }

        if (enemigo[1].tiempoempujado.getTiempo() > 0.5) {
            enemigo[1].empujado = false;
        }
*/
    }

    sf::Vector2f movement4(0.f, 0.f);
    if (aguaAdvancedCast) { //onMouseButtonRealeased
        hAguaAvanzado->cast(sf::Vector2f(getPosition()),hud);
    }
    if (hAguaAvanzado->tiempoCast.getTiempo() < 2.5 && hAguaAvanzado->dibujar == true) {
        movement4.x = (40 * cos(hAguaAvanzado->angleshot2) * 11.0f);
        movement4.y = (40 * sin(hAguaAvanzado->angleshot2) * 11.0f);
        hAguaAvanzado->UpdateHechizo(movement4, elapsedTime);
        
        
/* **************************PARA LA FUTURA CLASE ENTITY*************************
        if (hAguaAvanzado->GetGlobalBounds().intersects(enemigo[0].getSprite().getGlobalBounds())) {
            enemigo[0].empujado2 = true;
            enemigo[0].tiempoempujado.restart();
        }

        if (enemigo[0].empujado2 == true) {
            sf::Vector2f movement4(0.f, 0.f);
            movement4.x = 300 * (cos(hAguaAvanzado->angleshot2) * 1.0f);
            movement4.y = 300 * (sin(hAguaAvanzado->angleshot2) * 1.0f);
            enemigo[0].Update(movement4, elapsedTime);
        }

        if (enemigo[0].tiempoempujado.getTiempo() > 0.5) {
            enemigo[0].empujado2 = false;
        }
        */
    }    
}

void Player::updateFlash() {
        if (isFlashing) {
            //Como el player se ha movido 'casteamos' la animacion del otro flash
            flash2->cast2(&flash->clockCd);
            sf::Vector2f prueba =flash->cast(sf::Vector2f(getPosition()),hud);
            if(prueba.x != getPosition().x && prueba.y != getPosition().y){
                Colocar(prueba);
            } 
        }
        
}

void Player::renderRayo(sf::Time elapsedTime,float interpolation) {
     hRayoAvanzado->PlayAnimation(*hRayoAvanzado-> currentAnimation); //Current animation es un puntero a puntero
    if (hRayoAvanzado->draw == true) {
        if ( hRayoAvanzado->tiempoCast.getTiempo() < hRayoAvanzado->getCast()) {
            //switch
            switch (cuadrante) {
                case 1:
                    currentAnimation = &castingAnimationUpRayo;
                    break;
                case 2:
                    currentAnimation = &castingAnimationDownRayo;
                    break;
                case 3:
                    currentAnimation = &castingAnimationRightRayo;
                    break;
                case 4:
                    currentAnimation = &castingAnimationLeftRayo;
                    break;
            }
        }
        hRayoAvanzado -> UpdateAnimation(elapsedTime);
        if (hRayoAvanzado->tiempoCast.getTiempo() < hRayoAvanzado->getCast()) {
            hRayoAvanzado->DrawWithOutInterpolation();

        }
    } else {
        hRayoAvanzado->StopAnimation();
    }
    hRayoBasico->PlayAnimation(*hRayoBasico->currentAnimation);
    if (hRayoBasico->draw == true) {
        SetFrame(sf::seconds(0.125f));
        //switch
        switch (cuadrante) {
            case 1:
                currentAnimation = &castingAnimationUpRayo;
                break;
            case 2:
                currentAnimation = &castingAnimationDownRayo;
                break;
            case 3:
                currentAnimation = &castingAnimationRightRayo;
                break;
            case 4:
                currentAnimation = &castingAnimationLeftRayo;
                break;
        }


         hRayoBasico -> UpdateAnimation(elapsedTime);
        if (hRayoBasico->tiempoCast.getTiempo() < hRayoBasico->getCast()) {

            hRayoBasico->SetFrame(sf::seconds(0.075f));
            hRayoBasico->currentAnimation = &hRayoBasico->animationDurante;

            if (hRayoBasico->tiempoCast.getTiempo() < 1.0f) {


                hRayoBasico->SetFrame(sf::seconds(0.125f));
                hRayoBasico->currentAnimation = &hRayoBasico->PrimeraAnimacion;

            }

            hRayoBasico->DrawWithInterpolation(interpolation, GetPreviousPosition(), GetPosition());
        } else {

            hRayoBasico->draw = false;
        }

    } else {
        SetFrame(sf::seconds(0.075f));
        hRayoBasico->StopAnimation();
    }

}

void Player::renderFuego(sf::Time elapsedTime, float interpolation) {
if (hFuegoAvanzado->tiempoCast.getTiempo() < hFuegoAvanzado->getCast() && hFuegoAvanzado->lanzado == true) {
        if (hFuegoAvanzado->tiempoCast.getTiempo() > 0.4) {
           // hFuegoAvanzado->SetScale(1.0, 1.0);

        }
        hFuegoAvanzado->DrawWithInterpolation(interpolation, GetPreviousPosition(), GetPosition());
    }
    for (int aux = 0; aux <= 49; aux++) {
        hFuegoBasico[aux].PlayAnimation(hFuegoBasico[aux].animationInicio);
        hFuegoBasico[aux].UpdateAnimation(elapsedTime);
        hFuegoBasico[aux].DrawAnimation(hFuegoBasico[aux].GetPreviousPosition(),hFuegoBasico[aux].GetPosition(), interpolation);

    }
    if (castFire.getTiempo() < 0.45f) {
        SetFrameTime(sf::seconds(0.075f));
        //switch
        switch (cuadrante) {
            case 1:
                currentAnimation = &fuegoAnimationUp;
                break;
            case 2:
                currentAnimation = &fuegoAnimationDown;
                break;
            case 3:
                currentAnimation = &fuegoAnimationRight;
                break;
            case 4:
                currentAnimation = &fuegoAnimationLeft;
                break;
        }
    } else {
        SetFrameTime(sf::seconds(0.075f));
    }


    if (castFire2.getTiempo() < 0.4f) {
        SetFrameTime(sf::seconds(0.05f));
        /*hFuegoAvanzado->SetScale(hFuegoAvanzado->actualSize.x * 1.1, hFuegoAvanzado->actualSize.y * 1.1);
        hFuegoAvanzado->actualSize.x *= 1.05;
        hFuegoAvanzado->actualSize.y *= 1.05;*/
        //switch
        switch (cuadrante) {
            case 1:
                currentAnimation = &fuego2AnimationUp;
                break;
            case 2:
                currentAnimation = &fuego2AnimationDown;
                break;
            case 3:
                currentAnimation = &fuego2AnimationRight;
                break;
            case 4:
                currentAnimation = &fuego2AnimationLeft;
                break;
        }
    } else {
        SetFrameTime(sf::seconds(0.075f));
    }
}

void Player::renderAgua(sf::Time elapsedTime, float interpolation) {
    hAguaAvanzado->PlayAnimation(*hAguaAvanzado-> currentAnimation); //Current animation es un puntero a puntero
    if (hAguaAvanzado->dibujar == true) {
        SetFrame(sf::seconds(0.125f));
        //switch
        switch (cuadrante) {
            case 1:
                currentAnimation = &castingAnimationUpAgua;
                break;
            case 2:
                currentAnimation = &castingAnimationDownAgua;
                break;
            case 3:
                currentAnimation = &castingAnimationRightAgua;
                break;
            case 4:
                currentAnimation = &castingAnimationLeftAgua;
                break;
        }
        hAguaAvanzado -> UpdateAnimation(elapsedTime);
        if (hAguaAvanzado->tiempoCast.getTiempo() < 2.5) {
            hAguaAvanzado->DrawWithInterpolation(interpolation);
        } else {
            hAguaAvanzado->setDibujar(false);
        }
    }
    hAguaBasico->PlayAnimation(hAguaBasico->animation);
    if (hAguaBasico->dibujar == true) {
        SetFrame(sf::seconds(0.125f));
        //switch
        switch (cuadrante) {
            case 1:
                currentAnimation = &castingAnimationUpAgua;
                break;
            case 2:
                currentAnimation = &castingAnimationDownAgua;
                break;
            case 3:
                currentAnimation = &castingAnimationRightAgua;
                break;
            case 4:
                currentAnimation = &castingAnimationLeftAgua;
                break;
        }
        hAguaBasico -> UpdateAnimation(elapsedTime);
        if (hAguaBasico->tiempoCast.getTiempo() < 0.5f) {
            hAguaBasico->DrawWithInterpolation(interpolation);
        } else {
            hAguaBasico->setDibujar(false);
        }

    } else {
        SetFrame(sf::seconds(0.075f));
        hAguaBasico->StopAnimation();
    }
}

void Player::renderFlash(sf::Time elapsedTime, float interpolation) {
    //no hago play animation todo el rato porque no interesa ya que no haremos un getGlobalBounds del flash
    if (flash->dibujar == true) {
        flash->PlayAnimation(flash->flashingAnimation);
        flash->UpdateAnimation(elapsedTime);
        if (flash->tiempoCast.getTiempo() < 0.5f) {
            flash->Draw();
        } else {
            flash->dibujar = false;
        }
    } else {
        flash->StopAnimation();
    }


    DrawWithInterpolation(interpolation);

    //no hago play animation todo el rato porque no interesa ya que no haremos un getGlobalBounds del flash
    if (flash2->dibujar == true) {
        flash2->PlayAnimation(flash2->flashingAnimation2);
        flash2->UpdateAnimation(elapsedTime);
        if (flash2->tiempoCast.getTiempo() < 0.5f) {
            flash2->DrawWithInterpolation(interpolation, GetPreviousPosition(), GetPosition());
        } else {
            flash2->dibujar = false;
        }
    } else {
        flash2->StopAnimation();
    }
}

void Player::renderHeal(sf::Time elapsedTime, float interpolation) {
    hHeal->PlayAnimation(hHeal->animacion);
    if (hHeal->dibujar == true) {
        //Bloqueamos la movilidad mientras se castea
        cantMove = true;
        //Cambiamos el frameTime de la animacion
        SetFrameTime(sf::seconds(0.125f));
        //Vemos en que cuadrante estamos
        switch (cuadrante) {
            case 1:
                 currentAnimation = &healingAnimationUp;
                break;
            case 2:
                currentAnimation = &healingAnimationDown;
                break;
            case 3:
                currentAnimation = &healingAnimationRight;
                break;
            case 4:
                currentAnimation = &healingAnimationLeft;
                break;
        }
        hHeal->UpdateAnimation(elapsedTime);
        //Muy importante el getCD
        if (hHeal->tiempoCast.getTiempo() < hHeal->getCD()) {
            sf::Vector2f zizu(33.f, 35.f);
            hHeal->DrawWithInterpolation(interpolation, (GetPreviousPosition() - zizu), (GetPosition() - zizu));
        } else {
            hHeal->dibujar = false;
        }
    } else {
        //UpdatePlayerAnimation();  //Puede ser necesario llamar a esto
        //Devolvemos el Frametime al original
        SetFrameTime(sf::seconds(0.075f));
        //Volvemos a permitir el movimiento
        cantMove = false;
        hHeal->StopAnimation();
    }
}