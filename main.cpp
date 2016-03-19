#include "../Headers/Game.hpp"
void info(){
    std::cout << "" << std::endl;
    std::cout << "  @@@@; +`    ;@@@@; :.       @  ;@@@@; ,`      @ @@@@@@@`  @     @  " << std::endl;
    std::cout << "  @     @;    .@  `, ;@      @@  .@  `, ;@      @ :  @      @.    @  " << std::endl;
    std::cout << "  @     @:     @     :#@     @@   @      @@     @    @     `+@    @  " << std::endl;
    std::cout << "  @     @:     @     :`@    @`@   @      ++@    @    @     @ @    @  " << std::endl;
    std::cout << "  @@@@  #.     @@@@  ; ;@   @ @   @@@@   + @@   @    @     @ ;#   #  " << std::endl;
    std::cout << "  @     #.     @     #  @  @  @   @      #  @#  @    @    @   @   #  " << std::endl;
    std::cout << "  @     @`     @     @  ;@ @  @   @      #   @'`@    @    @@@@@:  @  " << std::endl;
    std::cout << "  @     @`    `@     @   @@   @,  @      @    @:@    @   @.   .@  @  " << std::endl;
    std::cout << "  @     @`    .@     @   +@   @@  @      @     @@    @   @     @. @   #" << std::endl;
    std::cout << "  @@@@  @@@@@ `@@@@  @        ;+  @@@@   ;      @    @   @     `: @@@@@" << std::endl;
    std::cout << std::endl;
    std::cout << "  :@@#    ;@@@@;.:     @` @@@@@  ;     .@     `@@`   @@@@@" << std::endl;
    std::cout << "  @; ;@`  .@  `, @     @; @:  :  @+     @   .@+      @    " << std::endl;
    std::cout << "  @.  '@   @     @:    @. @.     @@,    @  ,@        @    " << std::endl;
    std::cout << "  #`  :@   @     .@    @  #.     @`@`   @  @         @    " << std::endl;
    std::cout << "  #`  @:   @@@@   @   `@  #@@@@  @ .@   @ .@         @@@@:" << std::endl;
    std::cout << "  #`.@+    @      #;  @   #`     @  ;@  @ :@     +@  @    " << std::endl;
    std::cout << "  @`:@.    @       @ `#   @`     @   #@ @ `@      @  @    " << std::endl;
    std::cout << "  @.  @.  `@       @ @    @`     @    @@@  @+     @  @    " << std::endl;
    std::cout << "  @:   @' .@  :    :@:    @   ;  @     @@   @@:  +@  @    " << std::endl;
    std::cout << "  +:    @ `@@@@     #     @@@@@ .@      #     ;@@:   @@@@'" << std::endl;
    std::cout << "------------------------------------------------------------------------"<<std::endl;
    std::cout << ""<<std::endl;
    std::cout << "Version: Hito 1" <<std::endl;
    std::cout << "Rama: Flash Entregable" <<std::endl;
    std::cout << "Instrucciones: Pulsa la tecla E para teletransportarte hacia \nla posicion del mouse." <<std::endl;
}

int main(int, char const**) {

    
    info();
    Game *game = new Game();
    game->run();
    delete game;
}

