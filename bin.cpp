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
#include <iostream>
#include <fstream>

using namespace std;

/*defini��o da estrutura a ser armazenado no arquivo*/
union dado
{
    struct
    {
        int quant, first, last, free;
    } cab;
    struct
    {
        int chave, next, prev;
    } reg;
};

void inicializar(fstream &arq)
{
    /*Inicializando a estrutura*/

    cout << endl
         << endl
         << "Inicializando a estrutura de registros" << endl
         << endl;

    dado d;
    /*Posicionando o ponteiro de escrita no in�cio do arquivo*/
    arq.seekp(0, arq.beg);

    /*preenchendo o cabe�alho*/
    d.cab.quant = 0;
    d.cab.first = -1;
    d.cab.last = -1;
    d.cab.free = 1;

    /*Gravando o cabe�alho*/
    arq.write((char *)&d, sizeof(d));

    /*Gravando os 8 registros*/
    for (int i = 1; i <= 8; i++)
    {
        if (i == 8)
            d.reg.next = -1;
        else
            d.reg.next = i + 1;

        arq.write((char *)&d, sizeof(d));
    }
}

void imprimir(fstream &arq)
{
    dado d;

    cout << endl
         << endl
         << "Imprimindo a estrutura de registros" << endl;

    /*posicionando o ponteiro de leitura no in�cio do arquivo*/
    arq.seekg(0, arq.beg);

    /*lendo o cabe�alho*/
    arq.read((char *)&d, sizeof(d));

    /*imprimindo o cabe�alho*/
    cout << "cab\n";
    cout << "Quant: " << d.cab.quant << endl;
    cout << "First: " << d.cab.first << endl;
    cout << "Last: " << d.cab.last << endl;
    cout << "Free: " << d.cab.free << endl;

    /*lendo e imprimindo os 8 registros*/
    cout << "Registros\n";
    for (int i = 1; i <= 8; i++)
    {
        arq.read((char *)&d, sizeof(d));
        cout << i << "- Chave: " << d.reg.chave << endl;
        cout << i << "- Next: " << d.reg.next << endl;
        cout << i << "- Prev: " << d.reg.prev << endl
             << endl;
    }
}

void imprimirSeq(fstream &arq)
{
    dado c, r;

    cout << endl
         << endl
         << "Imprimindo registros validos" << endl;

    /*posicionando o ponteiro de leitura no in�cio do arquivo*/
    arq.seekg(0, arq.beg);

    /*lendo o cabe�alho*/
    arq.read((char *)&c, sizeof(c));
    /*imprimindo o cabe�alho*/
    cout << "cab\n";
    cout << "Quant: " << c.cab.quant << endl;
    cout << "First: " << c.cab.first << endl;
    cout << "Last: " << c.cab.last << endl;
    cout << "Free: " << c.cab.free << endl;

    /*lendo e imprimindo os registros com dados*/
    cout << "\nRegistros\n\n";
    if (c.cab.first == -1)
    {
        cout << "N�o existe registros";
        return;
    }

    /*posiciona o ponteiro de leitura no primeiro registro apontado por first*/
    arq.seekg(c.cab.first * sizeof(c), arq.beg);

    do
    {
        /*lendo o registro*/
        arq.read((char *)&r, sizeof(r));
        /*imprimindo o registro*/
        cout << "Chave: " << r.reg.chave << endl;
        cout << "Next: " << r.reg.next << endl;
        cout << "Prev: " << r.reg.prev << endl
             << endl;
        /*localizando o pr�ximo registro*/
        if (r.reg.next != -1)
            arq.seekg(r.reg.next * sizeof(r), arq.beg);

    } while (r.reg.next != -1);
}

void insere(fstream &arq, dado d)
{
    dado aux, c;
    int free;
    // cout<<endl<<endl<<"Inserindo registros"<<endl;

    /*posiciona o ponteiro de leitura no in�cio do arquivo*/
    arq.seekg(0, arq.beg);

    /*le o cabe�alho*/
    arq.read((char *)&c, sizeof(c));

    /*posiciona o ponteiro de leitura na primeira posi��o livre no arquivo*/
    arq.seekg(sizeof(c) * c.cab.free, arq.beg);

    /*le as informa��es do registro livre*/
    arq.read((char *)&aux, sizeof(aux));

    /*grava em free o pr�ximo registro livre*/
    free = aux.reg.next;

    /*atribuindo as informa��es do novo registro*/
    aux = d;
    aux.reg.next = -1;
    aux.reg.prev = c.cab.last;

    /*atualizando o next do registro que vai apontar para o novo registro aux*/
    if (aux.reg.prev != -1)
    {
        dado bob;
        /*posiciona o ponteiro de leitura para o registro que vai apontar para o novo registro aux*/
        arq.seekg(sizeof(aux) * aux.reg.prev, arq.beg);
        /*lendo o registro*/
        arq.read((char *)&bob, sizeof(bob));
        /*atualizando o next*/
        bob.reg.next = c.cab.free;

        /*posiciona o ponteiro de escrita para o registro que vai apontar para o novo registro aux*/
        arq.seekp(sizeof(aux) * aux.reg.prev, arq.beg);
        /*gravando o registro*/
        arq.write((char *)&bob, sizeof(bob));
    }
    /*posiciona o ponteiro de leitura para a posi��o do novo registro aux*/
    arq.seekp(sizeof(c) * c.cab.free, arq.beg);
    /*gravando o registro*/
    arq.write((char *)&aux, sizeof(aux));

    /*Atualiza��o o cabe�alho*/
    if (c.cab.first == -1)
        c.cab.first = c.cab.free;

    c.cab.quant++;
    c.cab.last = c.cab.free;
    c.cab.free = free;

    /*posiciona o ponteiro de escrita no in�cio do arquivo*/
    arq.seekp(0, arq.beg);
    /*gravado o cabe�alho*/
    arq.write((char *)&c, sizeof(c));
}

int main()
{
    dado d;
    fstream arq;
    arq.open("pagina.dat", ios::binary | fstream::in | fstream::out);
    if (!arq.is_open())
    {
        arq.open("pagina.dat", ios::binary | fstream::in | fstream::out | fstream::trunc);
        if (!arq.is_open())
        {
            cout << "Erro ao abrir o arquivo!!";
            return 0;
        }
    }

    inicializar(arq);

    /*lendo os dados para o novo registro*/
    cout << "Inserindo novo registro:\nDigite a chave: ";
    cin >> d.reg.chave;
    insere(arq, d);

    cout << "\nInserindo novo registro:\nDigite a chave: ";
    cin >> d.reg.chave;
    insere(arq, d);

    imprimirSeq(arq);
    imprimir(arq);
    arq.close();
    return 0;
}