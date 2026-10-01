#include <iostream>
#include <string>
#include <vector>
#include "agencia.h"

using namespace std;

int main() {
    Agencia agencia;
    string comando;

    while (cin >> comando) {

        if (comando == "FIM") {
            break;

        } else if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;

            cin >> cpf >> idade;
            getline(cin >> ws, nome);

            agencia.cadastrarAstronauta(cpf, nome, idade);

        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;

            agencia.cadastrarVoo(codigo);

        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;

            agencia.adicionarAstronauta(cpf, codigo);

        } else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;

            agencia.removerAstronauta(cpf, codigo);

        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;

            agencia.lancarVoo(codigo);

        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;

            agencia.explodirVoo(codigo);

        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;

            agencia.finalizarVoo(codigo);

        } else if (comando == "LISTAR_VOOS") {
            agencia.listarVoos();

        } else if (comando == "LISTAR_MORTOS") {
            agencia.listarMortos();

        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;
}