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
    std::cout << "Rama: Mapa1" <<std::endl;
    std::cout << "Info: Carga de un mapa basico de prueba con colisiones basicas" <<std::endl;
}

int main(int, char const**)
{
    info();
    Game *game = new Game();
    game->run();
    delete game;
}
