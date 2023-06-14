#include <iostream>
#include "manip_udados.hpp"
#include "menu.hpp"
int main()
{
    try
    {
        aplicacao();
    }
    catch (const std::runtime_error &erro)
    {
        cout << erro.what() << '\n';
    }

    return EXIT_SUCCESS;
}