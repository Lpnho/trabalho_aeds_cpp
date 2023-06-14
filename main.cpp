#include <iostream>
#include "manip_udados.hpp"

int main()
{
    ManipUDados variavel("batata");
    // variavel.abrir_arquivo();
    variavel.inicializar_lista_registros(10);
    variavel.inserir_registro({10});
    variavel.inserir_registro({1});

    variavel.imprimir_cabecalho();
    variavel.imprimir_registros_validos();
    variavel.remover_registro({10});
    variavel.imprimir_cabecalho();
    variavel.imprimir_registros_validos();


    return EXIT_SUCCESS;
}