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
    std::cout << "Rama: Heal Entregable" <<std::endl;
    std::cout << "Instrucciones: Pulsa la tecla T para quitarte 1 punto de vida.\nPulsa R para curarte 2 puntos de vida" <<std::endl;
}

int main(int, char const**)
{
    info();
    Game *game = new Game();
    game->run();
    delete game;
}
