#include "Player.hpp"
#include "Util.hpp"
#include "../States/InGame.hpp"
#include "../Otros/tmxHelper.hpp"
#include "../Motor/SoundManager.hpp"

void Player::CreateBody() {
    physicWorld = InGame::Instance()->physicWorld;

    //Creamos un objeto dinamico
    //bodyDef = new b2BodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(tmx::SfToBoxFloat(entity->GetPosition().x), tmx::SfToBoxFloat(entity->GetPosition().y));
    bodyDef.fixedRotation = true;
    //Añadimos el objeto al mundo
    body = physicWorld->CreateBody(&bodyDef);
    body->SetUserData(this);
    //Se crea una shape, le damos las dimensiones pasandole la mitad del ancho y la mitad del alto
    //del BoundingBox
    //shape = new b2PolygonShape();
    shape.SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    //Objeto que le da las propiedades fisicas al bodyDef
    //fixtureDef = new b2FixtureDef();
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    //fixtureDef->filter.groupIndex = Filtro::_entityCategory::PLAYER;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::PLAYER;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::ENEMIGO | Filtro::_entityCategory::BOUNDARY;
    body->CreateFixture(&fixtureDef);
}

Player::Player() : Collisionable((Entity*)this) {
    shapesFuego = new std::vector<sf::CircleShape*>();
}

Player::~Player() {
    delete hud;
}

std::string Player::getClassName() {
    return "Player";
}

void Player::Inicializar(float posX, float posY, float speedX, float speedY, float maxSpeedX, float maxSpeedY) {
    /*Reservamos memoria para los punteros de Animation*/

    walkingAnimationDown = new Animation();
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    walkingAnimationUp = new Animation();

    //casteo rayo
    castingAnimationUpRayo = new Animation();
    castingAnimationDownRayo = new Animation();
    castingAnimationRightRayo = new Animation();
    castingAnimationLeftRayo = new Animation();
    //casteo Fuego
    castingAnimationUpFuego = new Animation();
    castingAnimationDownFuego = new Animation();
    castingAnimationRightFuego = new Animation();
    castingAnimationLeftFuego = new Animation();
    //casteo Agua
    castingAnimationUpAgua = new Animation();
    castingAnimationDownAgua = new Animation();
    castingAnimationRightAgua = new Animation();
    castingAnimationLeftAgua = new Animation();

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

    animationMuerte = new Animation();
    Muerto = new Animation();
    

    hRayoBasico = new hRayBasic();
    hRayoAvanzado = new hRayAdvanced();


    hFuegoBasico = new hFireBasic[15];
    hFuegoAvanzado = new hFireAdvanced();


    hAguaBasico = new hWaterBasic();
    hAguaAvanzado = new hWaterAdvanced();

    hHeal = new Heal();

    flash = new Flash(1); //Animacion que aparece en la posicion que deja el jugador
    flash2 = new Flash(2); //Animacion que aparece a la posicion en que se ha movido el jugador


    Reloj *relojes = new Reloj[6];
    relojes[0] = hRayoBasico->tiempoCd;
    relojes[1] = hRayoAvanzado->clockCd;

    float *cds = new float[8];

    cds[0] = hRayoBasico->getCD();
    cds[1] = hRayoAvanzado->getCD();
    cds[2] = hAguaBasico->getCD();
    cds[3] = hAguaAvanzado->getCD();
    cds[4] = CDFire;
    cds[5] = hFuegoAvanzado->getCD();
    cds[6] = flash->getCD();
    cds[7] = hHeal->getCD();


    hud = new Hud(relojes, cds);

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

    animationMuerte->setSpriteSheet("resources/Textures/player.png");
    animationMuerte->addFrame(sf::IntRect(0, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(64, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(128, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(192, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(256, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));
    animationMuerte->addFrame(sf::IntRect(320, 1280, 64, 64));

    Muerto->setSpriteSheet("resources/Textures/player.png");
    Muerto->addFrame(sf::IntRect(320, 1280, 64, 64));
    Muerto->addFrame(sf::IntRect(320, 1280, 64, 64));


    
    currentAnimation = &walkingAnimationDown;

    InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    SetPosition(posX, posY);
    SetSpeed(speedX, speedY);
    SetMaxSpeed(maxSpeedX, maxSpeedY);
    SetOriginAnimatedSprite(32, 40);
    SetOriginColision(32, 40);
    
    //Cargamos shader del player para el colo
    LoadShader("resources/Shader/fs.frag");
    ActiveShader(false);

}

void Player::Update(const sf::Time elapsedTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (!cantMove) {
        if (isMovingUp)
            movement.y -= GetVelocity();
        if (isMovingDown)
            movement.y += GetVelocity();
        if (isMovingLeft)
            movement.x -= GetVelocity();
        if (isMovingRight)
            movement.x += GetVelocity();
    }
    if(GetEstado() == Estado::Damaged && damaged.getTiempo() > 0.06f){
        ActiveShader(false);
        SetEstado(Estado::ID::Vivo);
    }
    //Hay que setear al BodyDef el vector velocidad que hayamos calculado
    body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(movement) * Player::GetVelocity()));
    //Actualizamos la posicion del player con la posicion del bodyDef
    SetPosition(tmx::BoxToSfVec(body->GetPosition()));

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

void Player::UpdatePlayerAnimation() {
    //sf::Vector2f distancia(mouseSprite.getPosition().y - player -> GetRenderPosition().y, mouseSprite.getPosition().x - player -> GetRenderPosition().x);
    float playerPosX = InGame::Instance()->player->getPosition().x;
    float playerPosY = InGame::Instance()->player->getPosition().y;
    int x = Motor2D::Instance()->getMousePosition().x - playerPosX;
    int y = Motor2D::Instance()->getMousePosition().y - playerPosY;
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
    if (invulnerable.getTiempo() > 0.25f && (vida - a) >= 0) {

        vida -= a;

        hud->updateHud(vida);
        invulnerable.restart();
        SetEstado(Estado::ID::Damaged);
        ActiveShader(true);
        //Render::GetSpriteAnimated().setColor(sf::Color(255,255,0,255));
        SoundManager *sonido = SoundManager::Instance();
        sonido->play("resources/Sounds/Damage.wav");
        damaged.restart();
    }

    if(vida==0){
        SetEstado(Estado::ID::Muriendo);
        relojMuriendo.restart();
        currentAnimation = &animationMuerte;
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
    //    Dummy* dummy = InGame::Instance()->dummy;
    //dummy->body->SetTransform(tmx::SfToBoxVec(NuevaPosicion),body->GetAngle());
    //bool colision = dummy->getCollision(NuevaPosicion);
    sf::Vector2f resultado = NuevaPosicion - GetPosition();
    resultado.x = resultado.x * 10;
    resultado.y = resultado.y * 10;
    body->ApplyLinearImpulse(tmx::SfToBoxVec(resultado), body->GetWorldCenter(), true);
    //if(!colision){
    SetPosition(NuevaPosicion);
    //body->SetTransform(tmx::SfToBoxVec(NuevaPosicion),body->GetAngle()); 
    //}

}

bool Player::updateRayo(bool isShooting, bool RayoAvanzadoCast, float cdRayoBasicoPausa, float cdRayoAvanzadoPausa) {

    bool k=false;

    if (hRayoBasico->tiempoCast.getTiempo() > hRayoBasico->getCast() && aux == true) {
        isShooting = false;
        hRayoBasico->primerCast = false;
    }

    if ((isShooting && (hRayoBasico->clockCd.getTiempo()+cdRayoBasicoPausa) > hRayoBasico->getCD()) || (isShooting && hRayoBasico->primerCast == true)) {//Entra si dispara y el tiempo de enfriamiento ha pasado
        hRayoBasico->primerCast = false;
        if (aux == false) {//si es la primera vez que pulsa el boton
            hRayoBasico->tiempoCast.restart();
            aux = true; //no entra mas aqui para no hacer restart del cast
        }

        hRayoBasico->cast(sf::Vector2f(getPosition())); //siempre que entra aqui pintas

    } else {//entras si no disparas o si no ha pasado el tiempo de enfriamiento
        if (aux == true) {//entras si acabas de soltar el raton
           // hRayoBasico->tiempoCd.restart();
            //if(hRayoBasico->primerCast)
            //hud->resetRayo1();
                        k=true;

            //}
            // std::cout<<"Inicio den CD"<<std::endl;
            aux = false; //no entra mas aqui para no hacer restart dl cd
        }
        hRayoBasico->draw = false;
    }
    //avanzado
    if(RayoAvanzadoCast){
        hRayoAvanzado->cast(sf::Vector2f(getPosition()), hud, cdRayoAvanzadoPausa);
        printf("CD FUEGO DESDE PAUSA: %f\n", cdRayoAvanzadoPausa);
        printf("CD FUEGO CD NUEVO: %f\n", hRayoAvanzado->clockCd.getTiempo());
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && hRayoAvanzado->clockCd.getTiempo() > hRayoBasico->getCast()) {
        hRayoAvanzado->draw = false;
        hRayoAvanzado->StopAnimation();
    }
    
    
    return k;
}

void Player::updateFuego(bool fuegoBasicCast, bool fuegoAdvancedCast, sf::Time elapsedTime, float cdFuegoAvanzadoPausa, float cdFuegoBasicoPausa) {

    sf::Vector2f movement2(0.f, 0.f);

    if (fuegoBasicCast) {

        if (contFuego == 14) {
            contFuego = 0;
        }
        if ((clockCDFire.getTiempo()+cdFuegoBasicoPausa) > CDFire || primercastFuego == true) {
            primercastFuego = false;
            hFuegoBasico[contFuego].SetEstado(Estado::ID::Vivo);
            hFuegoBasico[contFuego].body->SetActive(true);
            hFuegoBasico[contFuego].cast(sf::Vector2f(getPosition()));
            castFire.restart();
        }
        contFuego++;
    }
    for (int aux = 0; aux <= 14; aux++) {
        //Si la bala esta viva updateamos su movimiento
        if (hFuegoBasico[aux].GetEstado() == Estado::ID::Vivo) {
            movement2.x = (4 * cos(hFuegoBasico[aux].angleshot2) * 10.0f);
            movement2.y = (4 * sin(hFuegoBasico[aux].angleshot2) * 10.0f);
            hFuegoBasico[aux].Update2(movement2, elapsedTime);
            shapesFuego->at(aux)->setPosition(tmx::BoxToSfVec(hFuegoBasico[aux].body->GetPosition()));
        } else if (hFuegoBasico[aux].GetEstado() == Estado::ID::Muriendo) {
            //Ademadas hacemos que su cuerpo no interactue
            hFuegoBasico[aux].body->SetActive(false);
            //Si la bala esta desapareciendo comprobamos hasta que desaparezca
            hFuegoBasico[aux].ComprobarSiMuerto();
        }

    }


    if (fuegoAdvancedCast) {
       /* 
        printf("CD FUEGO DESDE PAUSA: %f\n", cdFuegoAvanzadoPausa);
        printf("CD FUEGO CD NUEVO: %f\n", hFuegoAvanzado->clockCd.getTiempo());
        */

        if ((hFuegoAvanzado->clockCd.getTiempo()+cdFuegoAvanzadoPausa) > hFuegoAvanzado->getCD() || hFuegoAvanzado->primerCast == true) {

            hFuegoAvanzado->primerCast = false;
            hFuegoAvanzado->tiempoCast.restart();
            hFuegoAvanzado->lanzado = true;
            castFire2.restart();

            /*hFuegoAvanzado->actualSize.x = 0.3;
            hFuegoAvanzado->actualSize.y = 0.3;
            hFuegoAvanzado->SetScale(0.3, 0.3);*/
            hFuegoAvanzado->cast(sf::Vector2f(getPosition()));

        }
    }

}

void Player::updateAgua(bool aguaBasicCast, bool aguaAdvancedCast, sf::Time elapsedTime, float cdAguaBasicoPausa,float cdAguaAvanzadoPausa) {
    sf::Vector2f movement = tmx::BoxToSfVec(body->GetLinearVelocity());
    if (aguaBasicCast) {
        printf("CD AGUA DESDE PAUSA: %f\n", cdAguaBasicoPausa);
        printf("CD AGUA CD NUEVO: %f\n", hAguaBasico->clockCd.getTiempo());
        hAguaBasico->cast(sf::Vector2f(getPosition()), hud, cdAguaBasicoPausa);
    }
    if (hAguaBasico->tiempoCast.getTiempo() < 0.5f && hAguaBasico->dibujar == true) {
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
        hAguaAvanzado->cast(sf::Vector2f(getPosition()), hud, cdAguaAvanzadoPausa);
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

void Player::updateFlash(float cdFlashPausa) {
    if (isFlashing) {
        //Como el player se ha movido 'casteamos' la animacion del otro flash
        flash2->cast2(&flash->clockCd, cdFlashPausa);
        sf::Vector2f prueba = flash->cast(sf::Vector2f(getPosition()), hud,cdFlashPausa);
        if (prueba.x != getPosition().x && prueba.y != getPosition().y) {
            Colocar(prueba);
        }
    }

}

void Player::renderRayo(sf::Time elapsedTime, float interpolation) {
    hRayoAvanzado->PlayAnimation(*hRayoAvanzado-> currentAnimation); //Current animation es un puntero a puntero
    if (hRayoAvanzado->draw == true) {
        if (hRayoAvanzado->tiempoCast.getTiempo() < hRayoAvanzado->getCast()) {
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
    for (int aux = 0; aux <= 14; aux++) {

        if (hFuegoBasico[aux].GetEstado() == Estado::ID::Vivo) {
            hFuegoBasico[aux].PlayAnimation(*hFuegoBasico[aux].currentAnimation);
            hFuegoBasico[aux].UpdateAnimation(elapsedTime);
            hFuegoBasico[aux].DrawAnimation(hFuegoBasico[aux].GetPreviousPosition(), hFuegoBasico[aux].GetPosition(), interpolation);
        } else if (hFuegoBasico[aux].GetEstado() == Estado::ID::Muriendo) {
            hFuegoBasico[aux].PlayAnimation(*hFuegoBasico[aux].currentAnimation);
            hFuegoBasico[aux].UpdateAnimation(elapsedTime);
            hFuegoBasico[aux].DrawAnimationWithOut(hFuegoBasico[aux].GetRenderPosition());
        } else {
            hFuegoBasico[aux].StopAnimation();
            //hFuegoBasico[aux].DrawAnimationWithOut(hFuegoBasico[aux].GetRenderPosition());
        }

    }
    /*for(int i=0;i < shapesFuego->size();i++){
        Motor2D::Instance()->draw(*shapesFuego->at(i));
    }*/
    
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