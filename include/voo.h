#ifndef VOO_H
#define VOO_H

#include <vector>
#include <string>

using namespace std;

class Voo {
private:
    int codigo;
    vector<string> passageiros;
    bool emPlanejamento;
    bool emCurso;
    bool finalizado;
    bool explodido;

public:
    Voo(int codigo);

    int getCodigo();
    bool getEmPlanejamento();
    bool getEmCurso();
    bool getFinalizado();
    bool getExplodido();

    vector<string> getPassageiros();
    string getEstado();
    void setEstado(string estado);

    void adicionarAstronauta(string cpf);
    void removerAstronauta(string cpf);
    void lancar();
    void finalizar();
    void explodir();
};

#endif