#include <string>
#include "HashMap.hpp"

#ifndef USER_IO
#define USER_IO

class Command
{
public:
    Command(std::string order, std::string username, std::string password);

    void create(HashMap& hm);
    void login(HashMap& hm);
    void remove(HashMap& hm);
    void clear(HashMap& hm);
    void quit();
    void invalid_input();

    unsigned int login_count(HashMap& hm);
    unsigned int bucket_count(HashMap& hm);
    double load_factor(HashMap& hm);
    unsigned int max_bucket_size(HashMap& hm);
    void debug_on(bool& debug);
    void debug_off(bool& debug);

    void handle_commands(HashMap& hm, bool& debug);

    std::string command;
    std::string username;
    std::string password;

};

#endif 