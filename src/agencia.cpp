#include "agencia.h"
#include <iostream>
#include <fstream>

// Separa uma linha em partes, usando o separador informado.
// Ex.: separar("111;Ana Maria;30", ';') -> {"111", "Ana Maria", "30"}
vector<string> separar(string linha, char separador) {
    vector<string> partes;
    string atual = "";

    for (int i = 0; i < linha.size(); i++) {
        if (linha[i] == separador) {
            partes.push_back(atual);
            atual = "";
        } else {
            atual += linha[i];
        }
    }

    partes.push_back(atual);
    return partes;
}

// Verifica se o texto so tem digitos (sem espaco nem sinal).
bool ehNumero(string texto) {
    if (texto.empty()) {
        return false;
    }

    for (int i = 0; i < texto.size(); i++) {
        if (texto[i] < '0' || texto[i] > '9') {
            return false;
        }
    }

    return true;
}

void Agencia::salvar(string nomeArquivo) {
    ofstream arquivo(nomeArquivo.c_str());

    if (!arquivo.is_open()) {
        cout << "ERRO: nao foi possivel salvar em " << nomeArquivo << endl;
        return;
    }

    arquivo << "ASTRONAUTAS" << endl;

    for (int i = 0; i < astronautas.size(); i++) {
        arquivo << astronautas[i].getCpf() << ";"
                << astronautas[i].getNome() << ";"
                << astronautas[i].getIdade() << ";"
                << (astronautas[i].getVivo() ? "sim" : "nao") << ";"
                << (astronautas[i].getDisponivel() ? "sim" : "nao")
                << endl;
    }

    arquivo << "VOOS" << endl;

    for (int i = 0; i < voos.size(); i++) {
        arquivo << voos[i].getCodigo() << ";"
                << voos[i].getEstado() << ";";

        vector<string> passageiros = voos[i].getPassageiros();

        for (int j = 0; j < passageiros.size(); j++) {
            if (j > 0) {
                arquivo << " ";
            }

            arquivo << passageiros[j];
        }

        arquivo << endl;
    }

    arquivo.close();

    cout << "OK: dados salvos em " << nomeArquivo << endl;
}

void Agencia::carregar(string nomeArquivo) {
    ifstream arquivo(nomeArquivo.c_str());

    if (!arquivo.is_open()) {
        cout << "ERRO: nao foi possivel carregar de "
             << nomeArquivo << endl;
        return;
    }

    // Le tudo em vetores temporarios. So se a leitura inteira
    // funcionar e que os dados atuais sao substituidos.
    vector<Astronauta> novosAstronautas;
    vector<Voo> novosVoos;
    string linha;
    bool naSecaoVoos = false;
    bool achouAstronautas = false;
    bool achouVoos = false;
    bool invalido = false;

    while (getline(arquivo, linha)) {
        if (linha == "ASTRONAUTAS") {
            achouAstronautas = true;
            continue;
        }

        if (linha == "VOOS") {
            naSecaoVoos = true;
            achouVoos = true;
            continue;
        }

        if (linha.empty()) {
            continue;
        }

        if (!achouAstronautas) {
            invalido = true;
            break;
        }

        if (!naSecaoVoos) {
            vector<string> partes = separar(linha, ';');

            if (partes.size() != 5) {
                invalido = true;
                break;
            }

            string vivoTexto = partes[3];
            string disponivelTexto = partes[4];

            if ((vivoTexto != "sim" && vivoTexto != "nao") ||
                (disponivelTexto != "sim" && disponivelTexto != "nao") ||
                !ehNumero(partes[2])) {
                invalido = true;
                break;
            }

            Astronauta astronauta(partes[0], partes[1], stoi(partes[2]));
            astronauta.setVivo(vivoTexto == "sim");
            astronauta.setDisponivel(disponivelTexto == "sim");
            novosAstronautas.push_back(astronauta);
        } else {
            vector<string> partes = separar(linha, ';');

            if (partes.size() != 3) {
                invalido = true;
                break;
            }

            string estado = partes[1];

            if (!ehNumero(partes[0]) ||
                (estado != "planejado" && estado != "em curso" &&
                estado != "finalizado com sucesso" &&
                estado != "finalizado com explosao")) {
                invalido = true;
                break;
            }

            Voo voo(stoi(partes[0]));
            voo.setEstado(estado);

            vector<string> cpfs = separar(partes[2], ' ');

            for (int i = 0; i < cpfs.size(); i++) {
                if (!cpfs[i].empty()) {
                    voo.adicionarAstronauta(cpfs[i]);
                }
            }

            novosVoos.push_back(voo);
        }
    }

    arquivo.close();

    if (invalido || !achouAstronautas || !achouVoos) {
        cout << "ERRO: nao foi possivel carregar de "
             << nomeArquivo << endl;
        return;
    }

    astronautas = novosAstronautas;
    voos = novosVoos;

    cout << "OK: dados carregados de " << nomeArquivo << endl;
}

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

void Agencia::listarAstronautas() {
    cout << "LISTA DE ASTRONAUTAS" << endl;

    cout << "== disponiveis ==" << endl;
    bool encontrou = false;

    for (int i = 0; i < astronautas.size(); i++) {
        if (astronautas[i].getVivo() && astronautas[i].getDisponivel()) {
            encontrou = true;

            cout << astronautas[i].getCpf() << " "
                 << astronautas[i].getNome() << " ("
                 << astronautas[i].getIdade() << " anos)" << endl;
        }
    }

    if (!encontrou) {
        cout << "(nenhum)" << endl;
    }

    cout << "== em voo ==" << endl;
    encontrou = false;

    for (int i = 0; i < astronautas.size(); i++) {
        if (astronautas[i].getVivo() && !astronautas[i].getDisponivel()) {
            for (int j = 0; j < voos.size(); j++) {
                if (!voos[j].getEmCurso()) {
                    continue;
                }

                vector<string> passageiros = voos[j].getPassageiros();
                bool participa = false;

                for (int k = 0; k < passageiros.size(); k++) {
                    if (passageiros[k] == astronautas[i].getCpf()) {
                        participa = true;
                        break;
                    }
                }

                if (participa) {
                    encontrou = true;

                    cout << astronautas[i].getCpf() << " "
                         << astronautas[i].getNome() << " ("
                         << astronautas[i].getIdade() << " anos) - voo "
                         << voos[j].getCodigo() << endl;
                    break;
                }
            }
        }
    }

    if (!encontrou) {
        cout << "(nenhum)" << endl;
    }

    cout << "== mortos ==" << endl;
    encontrou = false;

    for (int i = 0; i < astronautas.size(); i++) {
        if (!astronautas[i].getVivo()) {
            encontrou = true;

            cout << astronautas[i].getCpf() << " "
                 << astronautas[i].getNome() << " ("
                 << astronautas[i].getIdade() << " anos)" << endl;
        }
    }

    if (!encontrou) {
        cout << "(nenhum)" << endl;
    }
}

void Agencia::historicoAstronauta(string cpf) {
    bool encontrado = false;
    string nome;

    for (int i = 0; i < astronautas.size(); i++) {
        if (astronautas[i].getCpf() == cpf) {
            encontrado = true;
            nome = astronautas[i].getNome();
            break;
        }
    }

    if (!encontrado) {
        cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
        return;
    }

    cout << "HISTORICO DE " << cpf << " " << nome << endl;

    bool encontrou = false;

    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].getEmPlanejamento()) {
            continue;
        }

        vector<string> passageiros = voos[i].getPassageiros();
        bool participa = false;

        for (int j = 0; j < passageiros.size(); j++) {
            if (passageiros[j] == cpf) {
                participa = true;
                break;
            }
        }

        if (!participa) {
            continue;
        }

        encontrou = true;

        cout << "voo " << voos[i].getCodigo() << ": ";

        if (voos[i].getEmCurso()) {
            cout << "em curso";
        } else if (voos[i].getExplodido()) {
            cout << "finalizado com explosao";
        } else {
            cout << "finalizado com sucesso";
        }

        cout << endl;
    }

    if (!encontrou) {
        cout << "(nenhum voo)" << endl;
    }
}