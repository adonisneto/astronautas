#ifndef AGENCIA_H
#define AGENCIA_H

#include <vector>
#include <string>
#include "astronauta.h"
#include "voo.h"

using namespace std;

class Agencia {
private:
    vector<Astronauta> astronautas;
    vector<Voo> voos;

public:
    void cadastrarAstronauta(string cpf, string nome, int idade);
    Astronauta* buscarAstronauta(string cpf);

    void cadastrarVoo(int codigo);
    Voo* buscarVoo(int codigo);

    void adicionarAstronauta(string cpf, int codigo);
    void removerAstronauta(string cpf, int codigo);

    void lancarVoo(int codigo);
    void finalizarVoo(int codigo);
    void explodirVoo(int codigo);

    void listarVoos();
    void listarMortos();

    void listarAstronautas();
    void historicoAstronauta(string cpf);

    void relatorio();

    void salvar(string nomeArquivo);
    void carregar(string nomeArquivo);
};

#endif