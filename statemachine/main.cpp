//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DadosDoProcessamentoDTO.h"
#include "FiniteStateMachine.h"
#include <iostream>
#include <ctype.h>
#include <algorithm>
#include "JsonToList.h"
//---------------------------------------------------------------------------

#pragma argsused

HINSTANCE DLLINSTANCE = LoadLibrary("C://sistemaswindows//SMPM//WSTM//debug_IPTU//IntegracaoDLL.dll");

FiniteStateMachine* jsonFSM(State* first )
{
    State* second    = new State();
    State* third     = new State();
    third->hasValue  = true;
    third->type      = "T";

    State* fourth    = new State();
    State* fifth      = new State();
    State* sixth      = new State();
    sixth->hasValue   = true;
    sixth->type      = "V";

    State* seventh    = new State();
    State* eighth     = new State(true);

    first->with('{', new Transition(second));
    second->with('\"', new Transition(third));

    // Add transitions with chars 0-9 and a-z
    for (int i = 0; i < 26; i++)
    {
        if (i < 10)
        {
            third = third->with( (char)(i +'0'), new Transition(third));
            sixth = sixth->with((char)(i +'0'), new Transition(sixth));
        }

        third = third->with((toupper((char) ('a' + i))), new Transition(third));
        sixth = sixth->with((toupper((char) ('a' + i))), new Transition(sixth));

        third = third->with(((char) ('a' + i)), new Transition(third));
        sixth = sixth->with(((char) ('a' + i)), new Transition(sixth));
    }
    sixth = sixth->with('/', new Transition(sixth));
    sixth = sixth->with(' ', new Transition(sixth));

    third->with('\"', new Transition(fourth));
    fourth->with(':', new Transition(fifth));
    fifth->with('\"', new Transition(sixth));
    sixth->with('\"', new Transition(seventh));
    seventh->with(',', new Transition(second));
    seventh->with('}', new Transition(eighth));

    return new FiniteStateMachine(first);
}

FiniteStateMachine* jsonListFSM(State* first)
{
    State* second     = new State();
    State* third      = new State();
    State* fourth     = new State();
    fourth->hasValue  = true;
    fourth->type      = "T";

    State* fifth       = new State();
    State* sixth       = new State();
    State* seventh     = new State();
    seventh->hasValue  = true;
    seventh->type      = "V";

    State* eighth      = new State();
    State* ninth       = new State();
    State* tenth       = new State(true);


    first->with('[', new Transition(second));
    second->with('{', new Transition(third));
    third->with('\"', new Transition(fourth));

    // Add transitions with chars 0-9 and a-z A-Z
    for (int i = 0; i < 26; i++)
    {
        if (i < 10)
        {
            fourth = fourth->with( (char)(i +'0'), new Transition(fourth));
            seventh = seventh->with((char)(i +'0'), new Transition(seventh));
        }

        fourth = fourth->with((toupper((char) ('a' + i))), new Transition(fourth));
        seventh = seventh->with((toupper((char) ('a' + i))), new Transition(seventh));

        fourth = fourth->with(((char) ('a' + i)), new Transition(fourth));
        seventh = seventh->with(((char) ('a' + i)), new Transition(seventh));
    }
    seventh = seventh->with('/', new Transition(seventh));
    seventh = seventh->with(':', new Transition(seventh));
    seventh = seventh->with(' ', new Transition(seventh));

    fourth->with('\"', new Transition(fifth));
    fifth->with(':', new Transition(sixth));
    sixth->with('\"', new Transition(seventh));
    seventh->with('\"', new Transition(eighth));

    eighth->with(',', new Transition(third));
    eighth->with('}', new Transition(ninth));

    ninth->with(',', new Transition(second));
    ninth->with(']', new Transition(tenth));

    return new FiniteStateMachine(first);
}

bool teste1(FiniteStateMachine* fsm)
{
    string values = "";
    string json = "{\"key\":\"value\"}";
    for (unsigned int i = 0; i < json.length(); i++)
    {
        string value;
        value.push_back(json.at(i));
        fsm->switchState(json.at(i), values);
    }

    for(int i = 0; i < fsm->values.size(); i++)
    {
        cout << " tags: " << fsm->tags[i] << " values: " << fsm->values[i] <<  endl;
    }
    cout << values << endl;
    cout << (string)(fsm->canStop() ? "isFinal" : "isNot") << endl;
}

void processarEventos()
{
    typedef string (__stdcall* PROCESSAREVENTOS) ();

    PROCESSAREVENTOS processarEventosDll =
        (PROCESSAREVENTOS) GetProcAddress(DLLINSTANCE, "processarEventos");

    cout << processarEventosDll() << endl;
}

bool teste2(FiniteStateMachine* fsm)
{
    string values = "";
    const string json = "{\"codigo\":\"10\",\"dataInicio\":\"28/10/19\",\"dataFim\":\"\",\"status\":\"EM PROCESSAMENTO\",\"descricaoStatus\":\"Dados do log recebido e executando o processamento dos dados\"}";



    for (unsigned int i = 0; i < json.length(); i++)
    {
        fsm->switchState(json.at(i), values);
    }

    for(int i = 0; i < fsm->values.size(); i++)
    {
        cout << " tags: " << fsm->tags[i] << " values: " << fsm->values[i] <<  endl;
    }
    cout << values << endl;
    cout << (string)(fsm->canStop() ? "isFinal" : "isNot") << endl;
}

int main(int argc, char* argv[])
{
    State* first     = new State();
    FiniteStateMachine* fsm = jsonListFSM(first);

//    FiniteStateMachine* fsm = jsonFSM(first );
//
//    cout << "Teste1" << endl;
//    teste1(fsm);
//
//    cout << endl;
//    fsm->reset(first);
//    cout << "Teste2" << endl;
//    teste2(fsm);

//      RECUPERAR TOKEN
//--------------------------------------------------------------------------------------------------------------

//
//    typedef string (__stdcall* GERARTOKEN) ();
//    GERARTOKEN gerarToken = (GERARTOKEN) GetProcAddress(DLLINSTANCE, "gerarToken");
//
//    cout << "retorno" << gerarToken() << endl;
//--------------------------------------------------------------------------------------------------------------
    // RECUPERAR PROCESSAMENTOS
//--------------------------------------------------------------------------------------------------------------
    typedef string (__stdcall* TESTE) ();

    TESTE teste =
        (TESTE) GetProcAddress(DLLINSTANCE, "recuperarListaProcessamento");

    cout << endl;

    string values = "";
    string json = teste();

    json.erase( remove(json.begin(), json.end(), '\r'), json.end() );

    for (unsigned int i = 0; i < json.length(); i++)
    {
        string value;
        value.push_back(json.at(i));
        fsm->switchState(json.at(i), values);
    }

    JsonToList* jsonList = new JsonToList();

    //for(int i =0; i < fsm->values.size(); i++)
//    {
//        cout << "values " <<  fsm->values[i];
//    }
    vector<TDadosDoProcessamentoDTO*> listaHistorico;
    jsonList->toList<TDadosDoProcessamentoDTO>(fsm->tags, fsm->values, listaHistorico);

//--------------------------------------------------------------------------------------------------------------
    // PROCESSAR EVENTOS
//--------------------------------------------------------------------------------------------------------------
    processarEventos();

    FreeLibrary(DLLINSTANCE);
    DLLINSTANCE = NULL;

    return 0;
}
//---------------------------------------------------------------------------


