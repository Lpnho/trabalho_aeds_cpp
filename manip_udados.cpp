#include "manip_udados.hpp"

void ManipUDados::abrir_arquivo()
{
    _arquivo.open(_caminho_arquivo, std::ios::binary | std::fstream::in | std::fstream::out);
    if (!_arquivo.is_open())
    {
        _arquivo.open(_caminho_arquivo, std::ios::binary | std::fstream::in | std::fstream::out | std::fstream::trunc);
    }
    if (!_arquivo.is_open())
    {
    }
}

void ManipUDados::fechar_aquivo()
{
    if (_arquivo.is_open())
    {
        _arquivo.close();
    }
}

ManipUDados &ManipUDados::posicionar_ponteiro_get(std::streamsize posicao)
{
    _arquivo.seekg(posicao * _tamanho_udados, _arquivo.beg); // a partir do begin do arquivo, ele posiciona o ponteiro get em posicao.
    if (!_arquivo.good())
    {
        throw std::runtime_error("Erro ao posicionar o ponteiro get no arquivo: " + _caminho_arquivo); // lança a excessao
    }
    return (*this);
}

ManipUDados &ManipUDados::posicionar_ponteiro_put(std::streamsize posicao)
{
    _arquivo.seekp(posicao * _tamanho_udados, _arquivo.beg);
    if (!_arquivo.good())
    {
        throw std::runtime_error("Erro ao posicionar o ponteiro put no arquivo: " + _caminho_arquivo);
    }
    return (*this);
}

void ManipUDados::ler_udados(UDados &entrada)
{
    _arquivo.read(reinterpret_cast<char *>(&entrada), _tamanho_udados);
    if (!_arquivo.good())
    {
        throw std::runtime_error("Erro ao ler dados no arquivo: " + _caminho_arquivo);
    }
}

void ManipUDados::gravar_udados(UDados &entrada)
{
    _arquivo.write(reinterpret_cast<char *>(&entrada), _tamanho_udados);
    if (!_arquivo.good())
    {
        throw std::runtime_error("Erro ao gravar dados no arquivo: " + _caminho_arquivo);
    }
}

void ManipUDados::inicializar_registro(int quantidade_registros)
{
    UDados dados;
    dados.cabecalho = {0, -1, -1, 1};

    posicionar_ponteiro_put(0);
    gravar_udados(dados);
    for (int i{1}; i <= quantidade_registros; ++i)
    {
        dados.registro.proximo = ((i == quantidade_registros) ? -1 : i + 1);
        gravar_udados(dados);
    }
}
