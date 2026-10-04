#include "astronauta.h"

Astronauta::Astronauta(string cpf, string nome, int idade) {
    this->cpf = cpf;
    this->nome = nome;
    this->idade = idade;
    this->vivo = true;
    this->disponivel = true;
}

string Astronauta::getCpf() {
    return cpf;
}

string Astronauta::getNome() {
    return nome;
}

int Astronauta::getIdade() {
    return idade;
}

bool Astronauta::getVivo() {
    return vivo;
}

bool Astronauta::getDisponivel() {
    return disponivel;
}
void Astronauta::setDisponivel(bool disponivel) {
    this->disponivel = disponivel;
}
void Astronauta::setVivo(bool vivo) {
    this->vivo = vivo;
}
void Astronauta::morrer() {
    vivo = false;
    disponivel = false;
}