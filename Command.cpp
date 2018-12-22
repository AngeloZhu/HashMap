#include "Command.hpp"
#include <iostream>
#include "HashMap.hpp"


Command::Command(std::string first, std::string second, std::string third)
    : command{first}, username{second}, password{third}
{}


void Command::create(HashMap& hm)
{
    if(hm.contains(username))
    {
        std::cout << "EXISTS" << std::endl;
    }
    else
    {
        hm.add(username, password);
        std::cout << "CREATED" << std::endl;
    }
}

void Command::login(HashMap& hm)
{
    if (hm.value(username) == password)
    {
        std::cout << "SUCCEEDED" << std::endl;
    }
    else
    {
        std::cout << "FAILED" << std::endl;
    }
}

void Command::remove(HashMap& hm)
{
    if (hm.contains(username))
    {
        hm.remove(username);
        std::cout << "REMOVED" << std::endl;
    }
    else
    {
        std::cout << "NONEXISTENT" << std::endl;
    }
}

void Command::clear(HashMap& hm)
{
    hm.clear_all();
    std::cout << "CLEARED" << std::endl;
}

void Command::quit()
{
    std::cout << "GOODBYE" << std::endl;
}

void Command::invalid_input()
{
    std::cout << "INVALID" << std::endl;
}

unsigned int Command::login_count(HashMap& hm)
{
    return hm.size();
}

unsigned int Command::bucket_count(HashMap& hm)
{
    return hm.bucketCount();
}

double Command::load_factor(HashMap& hm)
{
    return hm.loadFactor();
}

unsigned int Command::max_bucket_size(HashMap& hm)
{
    return hm.maxBucketSize();
}

void Command::debug_on(bool& debug)
{
    if (debug == false)
    {
        debug = true;
        std::cout << "ON NOW" << std::endl;
    }
    else
    {
        std::cout << "ON ALREADY" << std::endl;
    }
}

void Command::debug_off(bool& debug)
{
    if (debug == true)
    {
        debug = false;
        std::cout << "OFF NOW" << std::endl;
    }
    else
    {
        std::cout << "OFF ALREADY" << std::endl;
    }
}

void Command::handle_commands(HashMap& hm, bool& debug)
{
    if (command == "CREATE" && username != "" && password != "")
    {
        create(hm);
    }
    else if (command == "LOGIN" && username != "" && password != "")
    {
        login(hm);
    }
    else if (command == "REMOVE" && username != "" && password == "")
    {
        remove(hm);
    }
    else if (command == "CLEAR")
    {
        clear(hm);
    }
    else if (command == "QUIT")
    {
        quit();
    }
    else if (command == "DEBUG" && username == "ON")
    {
        debug_on(debug);
    }
    else if (command == "DEBUG" && username == "OFF")
    {
        debug_off(debug);
    }
    else if (debug)
    {
        if (command == "LOGIN" && username == "COUNT")
        {
            std::cout << login_count(hm) << std::endl;
        }
        else if (command == "BUCKET" && username == "COUNT")
        {
            std::cout << bucket_count(hm) << std::endl;
        }
        else if (command == "LOAD" && username == "FACTOR")
        {
            std::cout << load_factor(hm) << std::endl;
        }
        else if (command == "MAX" && username == "BUCKET" && password == "SIZE")
        {
            std::cout << max_bucket_size(hm) << std::endl;
        }
        else
        {
            invalid_input();
        }
    }
    else
    {
        invalid_input();
    }
}