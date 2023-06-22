#pragma once

#include <string>
#include <cstdlib>
#include <iostream>
#include "operacoes.hpp"
using std::cin;
using std::cout;

#ifdef _WIN32
void clear()
{
    system("cls");
}
#else
void clear()
{
    system("clear");
}
#endif

/*1 - Definir a estrutura Registro
2 - Inicialização
3 - Inserção
4 - Inserção ordenada
5 - Remoção
6 - Pesquisa
7 - Impressão dos registros inseridos
8 - Impressão dos registros livre
9 - Impressão da estrutura
*/
void inicializacao(int &entrada, std::string &caminho_arquivo);
int menu_opcoes();
void aplicacao();
void sistema(Operacoes *operador);

void inicializacao(int &entrada, std::string &caminho_arquivo)
{
    clear();
    std::string frase = R"(
----------------  Seja bem vindo!   -----------------
                        
        1) Para criar um novo arquivo
        2) Para carregar um arquivo existente
        ...
-----------------------------------------------------        
        )";
    cout << frase;
    cin >> entrada;
    cin.get();
    cout << "Entre com o nome ou o caminho do arquivo: ";
    std::getline(cin, caminho_arquivo);
}

int menu_opcoes()
{
    int entrada{0};
    std::string frase = R"(
        
----------------  Seja bem vindo!   -----------------
        Digite:

     0 -> Para sair
     1 -> Para inserir um elemento
     2 -> Para remover um elemento
     3 -> Para inserir um elemento de maneira ordenada
     4 -> Para imprimir tudo contido no arquivo
     5 -> Para imprimir registro preenchidos
     6 -> Para imprimir registro livres
     7 -> Para buscar um registro
     8 -> Para imprimir o cabeçalho
     9 -> Para imprimir um registro por posição
     10 -> Para limpar o console

        ...
-----------------------------------------------------        
        )";

    cout << frase;
    cin >> entrada;
    return entrada;
}

void sistema(Operacoes *operador)
{
    int entrada{0};
    do
    {
        entrada = menu_opcoes();
        switch (entrada)
        {
        case 0:
            break;
        case 1:
            operador->inserir_elemento();
            break;
        case 2:
            operador->remover_elemento();
            break;
        case 3:
            operador->inserir_elemento_ordenado();
            break;
        case 4:
            operador->imprimir_estrutura_completa();
            break;
        case 5:
            operador->imprimir_registros_ocupados();
            break;
        case 6:
            operador->imprimir_registros_livres();
            break;
        case 7:
            operador->buscar_registro();
            break;
        case 8:
            operador->imprimir_cabecalho();
            break;
        case 9:
            operador->imprimir_registro_por_posicao();
            break;
        case 10:
            clear();
            break;
        default:
            cout << "Opção inválida!\n";
            break;
        }

    } while (entrada);
}

void aplicacao()
{
    int entrada{0};
    std::string caminho_arquivo;
    inicializacao(entrada, caminho_arquivo);
    Operacoes *operador = nullptr;
    try
    {
        if (entrada == 1)
        {
            int quantidade_elementos;
            cout << "Entre com a quantidade de elemetos: ";
            cin >> quantidade_elementos;
            operador = new Operacoes(std::move(caminho_arquivo), quantidade_elementos);
        }
        else if (entrada == 2)

            operador = new Operacoes(std::move(caminho_arquivo));

        sistema(operador);
    }
    catch (const std::runtime_error &erro)
    {
        std::cerr << erro.what() << '\n';
    }
    delete operador;
}
