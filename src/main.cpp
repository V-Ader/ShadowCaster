#include <iostream>
#include "player.hpp"
#include "window.hpp"
#include "line.hpp"
#include "system.hpp"

void print_instruction();

int main(int argc, char* argv[])
{
    print_instruction();
    System system;
    Window window(&system);

    while (window.isOpen())
    {
        window.handleEvents(); 

        window.update();
        
        window.render();

    }

    return 0;
}

void print_instruction()
{
    std::cout << "Instruction" << std::endl;
    std::cout << "Keys:" << std::endl;
    std::cout << "Arrow UP - up" << std::endl;
    std::cout << "Arrow Down - Down" << std::endl;
    std::cout << "Arrow Right - Right" << std::endl;
    std::cout << "Arrow Left - Left" << std::endl;
    std::cout << "m - tunf on/off mouse mode" << std::endl;
    std::cout << "  when on - you can anly moce player using mouse. He well follow the cursor" << std::endl;
    std::cout << "Space - tunf on/off debug mode" << std::endl;
    std::cout << "  in debug mode you can see all rays castes to each main point on walls" << std::endl;
}