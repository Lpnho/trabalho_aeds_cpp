#include "manip_udados.hpp"

void Manip_UDados::abrir_arquivo()
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
