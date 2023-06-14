#include <iostream>
#include "manip_udados.hpp"

int main()
{
    try
    {
        ManipUDados variavel("batata");
        UDados reg;
        variavel.inicializar_lista_registros(10);
    }
    catch (const std::runtime_error &erro)
    {
        cout << erro.what() << '\n';
    }

    return EXIT_SUCCESS;
}