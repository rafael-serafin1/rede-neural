#pragma once

#ifndef INDEX_H
#define INDEX_H

#include "./src/logic_brain.hpp"
#define MAX_DISTANCE 3

class corretor_comandos {
private:
    const std::vector<std::string>* lista_comandos = nullptr;

public:
    corretor_comandos(const std::vector<std::string>& cmds): lista_comandos(&cmds) { }

    corretor_comandos(int argc, const char** argv) {
        std::vector<std::string>* cmds = new std::vector<std::string>();

        for (std::size_t i = 0; i < argc; ++i)
            cmds->push_back(std::string(argv[i]));

        lista_comandos = cmds;
    }

    ~corretor_comandos() {
        delete lista_comandos;
    }

    bool is_command(const char* arg) {
        for (const auto& i: *lista_comandos)
            if (i == std::string(arg))
                return true;

        return false;
    }

    bool is_command(const std::string& arg) {
        for (const auto& i: *lista_comandos) 
            if (i == arg)
                return true;
        return false;
    }

    
};

#endif