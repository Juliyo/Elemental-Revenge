#include "../Headers/Game.hpp"

void info(){
    std::cout << "" << std::endl;
    std::cout << "    ________                          __        __" << std::endl;
    std::cout << "   / ____/ /__  ____ ___  ___  ____  / /_____ _/ /" << std::endl;
    std::cout << "  / __/ / / _ \\/ __ `__ \\/ _ \\/ __ \\/ __/ __ `/ / " << std::endl;
    std::cout << " / /___/ /  __/ / / / / /  __/ / / / /_/ /_/ / /  " << std::endl;
    std::cout << "/_____/_/\\___/_/ /_/ /_/\\___/_/ /_/\\__/\\__,_/_/  " << std::endl;
    std::cout << std::endl;
    std::cout << "    ____                                " << std::endl;
    std::cout << "   / __ \\___ _   _____  ____  ____ ____ " << std::endl;
    std::cout << "  / /_/ / _ \\ | / / _ \\/ __ \\/ __ `/ _ \\" << std::endl;
    std::cout << " / _, _/  __/ |/ /  __/ / / / /_/ /  __/" << std::endl;
    std::cout << "/_/ |_|\\___/|___/\\___/_/ /_/\\__, /\\___/ " << std::endl;
    std::cout << "                           /____/       " << std::endl;
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
