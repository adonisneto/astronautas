#include "voo.h"

Voo::Voo(int codigo) {
    this->codigo = codigo;
    this->emPlanejamento = true;
    this->emCurso = false;
    this->finalizado = false;
    this->explodido = false;
}

int Voo::getCodigo() {
    return codigo;
}

bool Voo::getEmPlanejamento() {
    return emPlanejamento;
}

bool Voo::getEmCurso() {
    return emCurso;
}

bool Voo::getFinalizado() {
    return finalizado;
}

bool Voo::getExplodido() {
    return explodido;
}

vector<string> Voo::getPassageiros() {
    return passageiros;
}

void Voo::adicionarAstronauta(string cpf) {
    passageiros.push_back(cpf);
}

void Voo::removerAstronauta(string cpf) {
    for (int i = 0; i < passageiros.size(); i++) {
        if (passageiros[i] == cpf) {
            passageiros.erase(passageiros.begin() + i);
            return;
        }
    }
}

void Voo::lancar() {
    emPlanejamento = false;
    emCurso = true;
}
void Voo::finalizar() {
    emCurso = false;
    finalizado = true;
    
}
void Voo::explodir() {
    emCurso = false;
    finalizado = true;
    explodido = true;
}