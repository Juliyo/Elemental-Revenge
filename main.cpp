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
    std::cout << "Rama: Fuego Entregable" <<std::endl;
    std::cout << "Instrucciones: Click izquierdo para lanzar un hechizo basico.\nClick derecho para lanzar un hechizo avanzado." <<std::endl;
}


int main(int, char const**)
{
    info();
    Game *game = new Game();
    game->run();
    delete game;
}
