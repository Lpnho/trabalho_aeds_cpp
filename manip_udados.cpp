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

void ManipUDados::inicializar_lista_registros(int quantidade_registros)
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

void ManipUDados::inserir_registro(UDados::Registro entrada)
{
    UDados cabecalho, registro, auxiliar;
    int proxima_posicao_livre{0};

    posicionar_ponteiro_get(0).ler_udados(cabecalho);
    if (cabecalho.cabecalho.livre == -1)
    {
        std::string frase_erro = "Erro ao inserir o registro de chave: " + std::to_string(entrada.chave) + ". Espaço insuficiênte!\n";
        throw std::runtime_error(std::move(frase_erro));
    }
    posicionar_ponteiro_get(cabecalho.cabecalho.livre).ler_udados(registro);

    proxima_posicao_livre = registro.registro.proximo;
    auxiliar.registro = entrada;
    auxiliar.registro.proximo = -1;
    auxiliar.registro.anterior = cabecalho.cabecalho.ultimo;

    if (auxiliar.registro.anterior != -1)
    {
        UDados anterior;
        posicionar_ponteiro_get(auxiliar.registro.anterior);
        ler_udados(anterior);
        anterior.registro.proximo = cabecalho.cabecalho.livre;
        posicionar_ponteiro_put(auxiliar.registro.anterior);
        gravar_udados(anterior);
    }

    posicionar_ponteiro_put(cabecalho.cabecalho.livre).gravar_udados(auxiliar);

    if (cabecalho.cabecalho.primeiro == -1)
        cabecalho.cabecalho.primeiro = 1;
    cabecalho.cabecalho.quantidade++;
    cabecalho.cabecalho.ultimo = cabecalho.cabecalho.livre;
    cabecalho.cabecalho.livre = proxima_posicao_livre;
    posicionar_ponteiro_put(0).gravar_udados(cabecalho);
}

void ManipUDados::remover_registro(UDados::Registro entrada)
{
    int posicao_registro = buscar_registro(entrada);
    std::cout << "Posição: " << posicao_registro << '\n';
    if (posicao_registro != -1)
    {
        UDados cabecalho, registro_anterior, registro_posterior;
        int posicao_registro_anterior = entrada.anterior;
        int posicao_registro_posterior = entrada.proximo;

        posicionar_ponteiro_get(0).ler_udados(cabecalho);

        if (entrada.anterior != -1)
        {
            posicionar_ponteiro_get(entrada.anterior).ler_udados(registro_anterior);
            registro_anterior.registro.proximo = entrada.proximo;
            posicionar_ponteiro_put(posicao_registro_anterior).gravar_udados(registro_anterior);
        }
        else
        {
            cabecalho.cabecalho.primeiro = entrada.proximo;
        }

        if (entrada.proximo != -1)
        {
            posicionar_ponteiro_get(entrada.proximo).ler_udados(registro_posterior);
            registro_posterior.registro.anterior = entrada.anterior;
            posicionar_ponteiro_put(posicao_registro_posterior).gravar_udados(registro_posterior);
        }
        else
        {
            cabecalho.cabecalho.ultimo = entrada.anterior;
        }

        entrada.proximo = cabecalho.cabecalho.livre;
        cabecalho.cabecalho.livre = posicao_registro;
        cabecalho.cabecalho.quantidade--;
        posicionar_ponteiro_put(posicao_registro).gravar_registro(entrada);
        posicionar_ponteiro_put(0).gravar_udados(cabecalho);
    }
    else
    {
        std::string erro = "Registro chave: " + std::to_string(entrada.chave) + " inexistente!\n";
        throw std::runtime_error(std::move(erro));
    }
}

void ManipUDados::imprimir_registros_validos()
{
    UDados dados;
    posicionar_ponteiro_get(0).ler_udados(dados);
    std::cout << "\n*** Registros ***\n";
    if (dados.cabecalho.primeiro == -1)
    {
        std::cout << "Não existe registros\n";
        return;
    }

    posicionar_ponteiro_get(dados.cabecalho.primeiro);
    do
    {
        /*lendo o registro*/
        ler_udados(dados);
        imprimir_registro(dados.registro);
        if (dados.registro.proximo != -1)
            posicionar_ponteiro_get(dados.registro.proximo);

    } while (dados.registro.proximo != -1);
}

void ManipUDados::imprimir_registros_livres()
{
    UDados dados;
    posicionar_ponteiro_get(0).ler_udados(dados);
    std::cout << "\n\nRegistros\n\n";
    if (dados.cabecalho.livre == -1)
    {
        std::cout << "Não existe registros livres\n";
        return;
    }

    posicionar_ponteiro_get(dados.cabecalho.livre);
    do
    {
        /*lendo o registro*/
        ler_udados(dados);
        imprimir_registro(dados.registro);
        if (dados.registro.proximo != -1)
            posicionar_ponteiro_get(dados.registro.proximo);

    } while (dados.registro.proximo != -1);
}

void ManipUDados::imprimir_cabecalho()
{
    UDados cabecalho;
    posicionar_ponteiro_get(0).ler_udados(cabecalho);
    imprimir_cabecalho(cabecalho.cabecalho);
}

int ManipUDados::buscar_registro(UDados::Registro &registro)
{
    UDados auxiliar;
    posicionar_ponteiro_get(0).ler_udados(auxiliar);
    int retorno = auxiliar.cabecalho.primeiro;
    if (auxiliar.cabecalho.primeiro != -1)
    {
        posicionar_ponteiro_get(auxiliar.cabecalho.primeiro).ler_udados(auxiliar);
        do
        {
            if (auxiliar.registro.chave == registro.chave)
            {
                registro.anterior = auxiliar.registro.anterior;
                registro.proximo = auxiliar.registro.proximo;
                return retorno;
            }
            retorno = auxiliar.registro.proximo;
            if (retorno == -1)
                break;
            posicionar_ponteiro_get(auxiliar.registro.proximo).ler_udados(auxiliar);
        } while (auxiliar.registro.proximo != -1);
    }
    return -1;
}
