#pragma once
#include "manip_udados.hpp"

class Operacoes
{
private:
    ManipUDados _arquivo;

public:
    Operacoes(std::string caminho_arquivo) : _arquivo(std::move(caminho_arquivo))
    {
    }
    Operacoes(std::string caminho_arquivo, int quatidade_dados) : _arquivo(std::move(caminho_arquivo))
    {
        _arquivo.inicializar_lista_registros(quatidade_dados);
    }
    /* Inseri o registro com base na chave*/
    void inserir(int chave)
    {
        try
        {
            _arquivo.inserir_registro({chave});
        }
        catch (const std::runtime_error &erro)
        {
            std::cerr << erro.what() << '\n';
        }
    }
    void inserir_ordenado(int chave)
    {
        try
        {
            _arquivo.inserir_registro_ordenado({chave});
        }
        catch (const std::runtime_error &erro)
        {
            std::cerr << erro.what() << '\n';
        }
    }
    void remover(int chave)
    {
        try
        {
            _arquivo.remover_registro({chave});
        }
        catch (const std::runtime_error &erro)
        {
            std::cerr << erro.what() << '\n';
        }
    }

    // Interface de Operações

    void inserir_elemento()
    {
        int entrada{0};
        std::cout << "Entre com o elemento a ser inserido: ";
        std::cin >> entrada;
        inserir(entrada);
    }
    void inserir_elemento_ordenado()
    {
        int entrada{0};
        std::cout << "Entre com o elemento a ser inserido: ";
        std::cin >> entrada;
        inserir_ordenado(entrada);
    }
    void remover_elemento()
    {
        int entrada{0};
        std::cout << "Entre com o elemento a ser removido: ";
        std::cin >> entrada;
        remover(entrada);
    }
    void imprimir_registros_livres()
    {
        try
        {
            _arquivo.imprimir_registros_livres();
        }
        catch (const std::runtime_error &erro)
        {
            std::cerr << erro.what() << '\n';
        }
    }
    void imprimir_registros_ocupados()
    {
        try
        {
            _arquivo.imprimir_registros_validos();
        }
        catch (const std::runtime_error &erro)
        {
            std::cerr << erro.what() << '\n';
        }
    }
    void imprimir_estrutura_completa()
    {
        try
        {
            _arquivo.imprimir_cabecalho();
            _arquivo.imprimir_registros_validos();
            _arquivo.imprimir_registros_livres();
        }
        catch (const std::runtime_error &erro)
        {
            std::cerr << erro.what() << '\n';
        }
    }
    void buscar_registro()
    {
        int entrada{0};
        std::cout << "Entre com o elemento a ser pesquisado: ";
        std::cin >> entrada;
        try
        {
            UDados::Registro registro{entrada};
            int resultado = _arquivo.buscar_registro(registro);
            if (resultado == -1)
            {
                std::cout << "Elemento não encontrado.\n";
            }
            else
            {
                _arquivo.imprimir_registro(registro);
            }
        }
        catch (const std::runtime_error &erro)
        {
            std::cerr << erro.what() << '\n';
        }
    }

    void imprimir_cabecalho()
    {
        try
        {
            _arquivo.imprimir_cabecalho();
        }
        catch (const std::runtime_error &erro)
        {
            std::cerr << erro.what() << '\n';
        }
    }
    void imprimir_registro_por_posicao()
    {

        UDados dados;
        int entrada{0};
        std::cout << "Entre com a posição do elemento para ser imprimido: ";
        std::cin >> entrada;
        try
        {
            _arquivo[entrada].ler_udados(dados);
            _arquivo.imprimir_registro(dados.registro);
        }
        catch (const std::runtime_error &erro)
        {
            std::cerr << erro.what() << '\n';
        }
    }

    ManipUDados &arquivo() & { return _arquivo; }
};