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
        int quantidade, primeiro, ultimo, livre;
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
        abrir_arquivo();
    }
    ~ManipUDados() { fechar_aquivo(); }
    
    void abrir_arquivo();
    void fechar_aquivo()
    {
        if (_arquivo.is_open())
        {
            _arquivo.close();
        }
    }

    ManipUDados &posicionar_ponteiro_get(std::streamsize posicao);
    ManipUDados &posicionar_ponteiro_put(std::streamsize posicao);
    ManipUDados &posicionar_ponteiros(std::streamsize posicao)
    {
        posicionar_ponteiro_put(posicao);
        posicionar_ponteiro_get(posicao);
        return (*this);
    }
    ManipUDados &operator[](std::streamsize posicao) { return posicionar_ponteiros(posicao); }

    void ler_udados(UDados &entrada);
    void gravar_udados(UDados &entrada);

    void ler_udados(UDados &entrada, std::streamsize posicao)
    {
        posicionar_ponteiro_get(posicao);
        ler_udados(entrada);
    }
    void gravar_udados(UDados &entrada, std::streamsize posicao)
    {
        posicionar_ponteiro_put(posicao);
        gravar_udados(entrada);
    }
    
    void gravar_registro(UDados::Registro &registro)
    {
        UDados dados;
        dados.registro = registro;
        gravar_udados(dados);
    }

    void inicializar_lista_registros(int quantidade_registros);

    void inserir_registro(UDados::Registro entrada);
    void inserir_registro_ordenado(UDados::Registro entrada);
    void remover_registro(UDados::Registro entrada);

    void imprimir_registros_validos();
    void imprimir_registros_livres();
    void imprimir_cabecalho();

    int buscar_registro(UDados::Registro &registro);

    void imprimir_cabecalho(const UDados::Cabecalho &cabecalho)
    {
        cout << "********** Cabeçalho ********** \n"
             << "Quantidade: " << cabecalho.quantidade << '\n'
             << "Primeiro: " << cabecalho.primeiro << '\n'
             << "Último: " << cabecalho.ultimo << '\n'
             << "Livre: " << cabecalho.livre << '\n';
    }
    void imprimir_registro(const UDados::Registro &registro)
    {
        cout << "Chave: " << registro.chave << '\n'
             << "Próximo: " << registro.proximo << '\n'
             << "Anterior: " << registro.anterior << "\n\n";
    }
};