#include "HashMap.hpp"
#include "Command.hpp"
#include <iostream>
#include <sstream>

int main()
{
    std::string input;
    HashMap database;
    bool debug = false;

    while (input != "QUIT")
    {
        std::string command = "";
        std::string username = "";
        std::string password = "";

        std::getline(std::cin, input);
        std::istringstream line(input);
        line >> command >> username >> password;

        Command line_input = Command(command, username, password);

        line_input.handle_commands(database, debug);
    }

    return 0;
}
