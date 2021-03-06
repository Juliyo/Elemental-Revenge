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
    std::cout << "Version: Hito 3" <<std::endl;
    std::cout << "Rama: Final" <<std::endl;
    std::cout << "Instrucciones: Click izquierdo para lanzar un hechizo basico.\nClick derecho para lanzar un hechizo avanzado." <<std::endl;
    std::cout << "Pulsa continuar para iniciar el juego.\nResponde una de las preguntas.\nM -> para pasar al siguiente nivel." <<std::endl;
    std::cout << "P -> Para pausar el juego.\n" <<std::endl;
}

int main(int, char const**)
{
    info();
    Game *game = new Game();
    game -> run();

    return 0;
   
}
