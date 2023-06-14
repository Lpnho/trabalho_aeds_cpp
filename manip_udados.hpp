#pragma once

#include <iostream>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::string;

union UDados
{
    struct Cabecalho
    {
        int quantidate, primeiro, ultimo, livre;
    } cabecalho;

    struct Registro
    {
        int chave, proximo, anterior;
    } registro;
};

class ManipUDados
{
private:
    std::fstream _arquivo;
    string _caminho_arquivo;
    int _tamanho_udados;

public:
    ManipUDados(string caminho_arquivo) : _tamanho_udados(sizeof(UDados)),
                                          _caminho_arquivo(std::move(caminho_arquivo))
    {
    }
    ~ManipUDados() { fechar_aquivo(); }
    void abrir_arquivo();
    void fechar_aquivo();
    void imprimir_arquivo();

    ManipUDados &posicionar_ponteiro_get(std::streamsize posicao);
    ManipUDados &posicionar_ponteiro_put(std::streamsize posicao);
    ManipUDados &posicionar_ponteiros(std::streamsize posicao);

    void ler_udados(UDados &entrada);
    void gravar_udados(UDados &entrada);

    void inicializar_registro();
    void inserir_registro();
    void inserir_registro_ordenado();
    void remover_registro();
    void imprimir_registros_validos();
    void imprimir_registros_livres();
    int buscar_registro(UDados::Registro registro);

    void imprimir_cabecalho(const UDados::Cabecalho &registro);
    void imprimir_registro(const UDados::Registro &registro);
};