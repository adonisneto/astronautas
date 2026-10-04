#ifndef ASTRONAUTA_H
#define ASTRONAUTA_H

#include <string>

using namespace std;

class Astronauta {
private:
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;

public:
    Astronauta(string cpf, string nome, int idade);

    string getCpf();
    string getNome();
    int getIdade();
    bool getVivo();
    bool getDisponivel();
    void setDisponivel(bool disponivel);
    void morrer();
};

#endif