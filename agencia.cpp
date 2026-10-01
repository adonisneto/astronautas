#include "agencia.h"
#include <iostream>

void Agencia::cadastrarAstronauta(string cpf, string nome, int idade) {
    if (buscarAstronauta(cpf) != nullptr) {
        cout << "ERRO: astronauta com CPF " << cpf << " ja cadastrado" << endl;
        return;
    }

    Astronauta astronauta(cpf, nome, idade);
    astronautas.push_back(astronauta);

    cout << "OK: astronauta " << cpf << " cadastrado" << endl;
}

Astronauta* Agencia::buscarAstronauta(string cpf) {
    for (Astronauta& astronauta : astronautas) {
        if (astronauta.getCpf() == cpf) {
            return &astronauta;
        }
    }

    return nullptr;
}

void Agencia::cadastrarVoo(int codigo) {
    if (buscarVoo(codigo) != nullptr) {
        cout << "ERRO: voo " << codigo << " ja cadastrado" << endl;
        return;
    }

    Voo voo(codigo);
    voos.push_back(voo);

    cout << "OK: voo " << codigo << " cadastrado" << endl;
}

Voo* Agencia::buscarVoo(int codigo) {
    for (Voo& voo : voos) {
        if (voo.getCodigo() == codigo) {
            return &voo;
        }
    }

    return nullptr;
}

void Agencia::adicionarAstronauta(string cpf, int codigo) {
    Astronauta* astronauta = buscarAstronauta(cpf);

    if (astronauta == nullptr) {
        cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
        return;
    }

    Voo* voo = buscarVoo(codigo);

    if (voo == nullptr) {
        cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
        return;
    }

    if (!voo->getEmPlanejamento()) {
        cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
        return;
    }

    if (!astronauta->getVivo()) {
        cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
        return;
    }

    vector<string> passageiros = voo->getPassageiros();

    for (int i = 0; i < passageiros.size(); i++) {
        if (passageiros[i] == cpf) {
            cout << "ERRO: astronauta " << cpf
                 << " ja esta no voo " << codigo << endl;
            return;
        }
    }

    voo->adicionarAstronauta(cpf);

    cout << "OK: astronauta " << cpf
         << " adicionado ao voo " << codigo << endl;
}

void Agencia::removerAstronauta(string cpf, int codigo) {
    Astronauta* astronauta = buscarAstronauta(cpf);

    if (astronauta == nullptr) {
        cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
        return;
    }

    Voo* voo = buscarVoo(codigo);

    if (voo == nullptr) {
        cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
        return;
    }

    if (!voo->getEmPlanejamento()) {
        cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
        return;
    }

    vector<string> passageiros = voo->getPassageiros();
    bool encontrou = false;

    for (int i = 0; i < passageiros.size(); i++) {
        if (passageiros[i] == cpf) {
            encontrou = true;
            break;
        }
    }

    if (!encontrou) {
        cout << "ERRO: astronauta " << cpf
             << " nao esta no voo " << codigo << endl;
        return;
    }

    voo->removerAstronauta(cpf);

    cout << "OK: astronauta " << cpf
         << " removido do voo " << codigo << endl;
}

void Agencia::lancarVoo(int codigo) {
    Voo* voo = buscarVoo(codigo);

    if (voo == nullptr) {
        cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
        return;
    }

    if (!voo->getEmPlanejamento()) {
        cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
        return;
    }

    vector<string> passageiros = voo->getPassageiros();

    if (passageiros.empty()) {
        cout << "ERRO: voo " << codigo << " nao possui astronautas" << endl;
        return;
    }

    for (int i = 0; i < passageiros.size(); i++) {
        Astronauta* astronauta = buscarAstronauta(passageiros[i]);

        if (!astronauta->getVivo()) {
            cout << "ERRO: astronauta " << passageiros[i]
                 << " esta morto" << endl;
            return;
        }

        if (!astronauta->getDisponivel()) {
            cout << "ERRO: astronauta " << passageiros[i]
                 << " esta indisponivel" << endl;
            return;
        }
    }

    for (int i = 0; i < passageiros.size(); i++) {
        Astronauta* astronauta = buscarAstronauta(passageiros[i]);
        astronauta->setDisponivel(false);
    }

    voo->lancar();

    cout << "OK: voo " << codigo << " lancado" << endl;
}

void Agencia::finalizarVoo(int codigo) {
    Voo* voo = buscarVoo(codigo);

    if (voo == nullptr) {
        cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
        return;
    }

    if (!voo->getEmCurso()) {
        cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
        return;
    }

    vector<string> passageiros = voo->getPassageiros();

    for (int i = 0; i < passageiros.size(); i++) {
        Astronauta* astronauta = buscarAstronauta(passageiros[i]);
        astronauta->setDisponivel(true);
    }

    voo->finalizar();

    cout << "OK: voo " << codigo
         << " finalizado com sucesso" << endl;
}

void Agencia::explodirVoo(int codigo) {
    Voo* voo = buscarVoo(codigo);

    if (voo == nullptr) {
        cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
        return;
    }

    if (!voo->getEmCurso()) {
        cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
        return;
    }

    vector<string> passageiros = voo->getPassageiros();

    for (int i = 0; i < passageiros.size(); i++) {
        Astronauta* astronauta = buscarAstronauta(passageiros[i]);
        astronauta->morrer();
    }

    voo->explodir();

    cout << "OK: voo " << codigo << " explodiu" << endl;
}

void Agencia::listarVoos() {
    cout << "LISTA DE VOOS" << endl;

    cout << "== planejado ==" << endl;
    bool encontrou = false;

    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].getEmPlanejamento()) {
            encontrou = true;

            cout << "Voo " << voos[i].getCodigo() << ": ";

            vector<string> passageiros = voos[i].getPassageiros();

            if (passageiros.empty()) {
                cout << "sem astronautas";
            } else {
                for (int j = 0; j < passageiros.size(); j++) {
                    Astronauta* astronauta =
                        buscarAstronauta(passageiros[j]);

                    if (j > 0) {
                        cout << ", ";
                    }

                    cout << astronauta->getCpf() << " "
                         << astronauta->getNome();
                }
            }

            cout << endl;
        }
    }

    if (!encontrou) {
        cout << "(nenhum)" << endl;
    }

    cout << "== em curso ==" << endl;
    encontrou = false;

    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].getEmCurso()) {
            encontrou = true;

            cout << "Voo " << voos[i].getCodigo() << ": ";

            vector<string> passageiros = voos[i].getPassageiros();

            if (passageiros.empty()) {
                cout << "sem astronautas";
            } else {
                for (int j = 0; j < passageiros.size(); j++) {
                    Astronauta* astronauta =
                        buscarAstronauta(passageiros[j]);

                    if (j > 0) {
                        cout << ", ";
                    }

                    cout << astronauta->getCpf() << " "
                         << astronauta->getNome();
                }
            }

            cout << endl;
        }
    }

    if (!encontrou) {
        cout << "(nenhum)" << endl;
    }

    cout << "== finalizado com sucesso ==" << endl;
    encontrou = false;

    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].getFinalizado() && !voos[i].getExplodido()) {
            encontrou = true;

            cout << "Voo " << voos[i].getCodigo() << ": ";

            vector<string> passageiros = voos[i].getPassageiros();

            if (passageiros.empty()) {
                cout << "sem astronautas";
            } else {
                for (int j = 0; j < passageiros.size(); j++) {
                    Astronauta* astronauta =
                        buscarAstronauta(passageiros[j]);

                    if (j > 0) {
                        cout << ", ";
                    }

                    cout << astronauta->getCpf() << " "
                         << astronauta->getNome();
                }
            }

            cout << endl;
        }
    }

    if (!encontrou) {
        cout << "(nenhum)" << endl;
    }

    cout << "== finalizado com explosao ==" << endl;
    encontrou = false;

    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].getFinalizado() && voos[i].getExplodido()) {
            encontrou = true;

            cout << "Voo " << voos[i].getCodigo() << ": ";

            vector<string> passageiros = voos[i].getPassageiros();

            if (passageiros.empty()) {
                cout << "sem astronautas";
            } else {
                for (int j = 0; j < passageiros.size(); j++) {
                    Astronauta* astronauta =
                        buscarAstronauta(passageiros[j]);

                    if (j > 0) {
                        cout << ", ";
                    }

                    cout << astronauta->getCpf() << " "
                         << astronauta->getNome();
                }
            }

            cout << endl;
        }
    }

    if (!encontrou) {
        cout << "(nenhum)" << endl;
    }
}

void Agencia::listarMortos() {
    cout << "ASTRONAUTAS MORTOS" << endl;

    bool encontrou = false;

    for (int i = 0; i < astronautas.size(); i++) {
        if (!astronautas[i].getVivo()) {
            encontrou = true;

            cout << astronautas[i].getCpf() << " "
                 << astronautas[i].getNome()
                 << " - voos:";

            bool participou = false;

            for (int j = 0; j < voos.size(); j++) {
                if (voos[j].getEmPlanejamento()) {
                    continue;
                }

                vector<string> passageiros =
                    voos[j].getPassageiros();

                for (int k = 0; k < passageiros.size(); k++) {
                    if (passageiros[k] ==
                        astronautas[i].getCpf()) {

                        cout << " " << voos[j].getCodigo();
                        participou = true;
                        break;
                    }
                }
            }

            if (!participou) {
                cout << " nenhum";
            }

            cout << endl;
        }
    }

    if (!encontrou) {
        cout << "(nenhum)" << endl;
    }
}