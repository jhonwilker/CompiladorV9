#include "lexico.h"
Token *tk = new Token();

void declara_procedimento();
void bloco();
void subRotinas();
void parametro_formais();
void expressao();
void listaDeExpressao();
void comandoSemRotulo();
string backspace = "    ";
string a;

/**
    incrementaBackSpace();
    cout<<a<<"<cham_procedimento>"<<endl;

    **--**

    decrementaBackSpace();
**/

void incrementaBackSpace(){
    a.push_back(' ');a.push_back(' ');a.push_back(' ');
}

void decrementaBackSpace(){
    a.pop_back();a.pop_back();a.pop_back();
}

void listaDeIdentificadores(){
    incrementaBackSpace();
    cout<<a<<"<listaDeIdentificadores>"<<endl;

    do{
        //cout<<tk->getValor()<<endl;
        if(tk->getTipo() != "ID"){
            cout<<"ERRO esperava identificador <list_Id> linha:"<<contadorLinha-1<<endl;
            exit(0);
        }
        tk = tokenLexico();
        if(tk->getValor() == ","){
           tk = tokenLexico();

        }
    }while(tk->getTipo() == "ID");
    cout<<a<<"</listaDeIdentificadores>"<<endl;
    decrementaBackSpace();
}

void declara_tipo(){
    incrementaBackSpace();
    cout<<a<<"<declara_tipo>"<<endl;
    tk = tokenLexico();
    //cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
    do{
        if(tk->getValor() != "real" && tk->getValor() != "boleano" && tk->getValor() != "inteiro"){
            cout<<"ERRO esperava PR-real-inteiro-boleano <declara_tipo> linha:"<<contadorLinha-1<<endl;
            cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
            exit(0);
        }
        tk = tokenLexico();
        //cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
        if(tk->getValor() != "="){
            cout<<"ERRO esperava '=' <declara_tipo> linha:"<<contadorLinha-1<<endl;
            cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
            exit(0);
        }
        tk = tokenLexico();
        //cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
        if(tk->getTipo() != "ID"){
            cout<<"ERRO esperava identificador <declara_tipo> linha:"<<contadorLinha-1<<endl;
            cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
            exit(0);
        }
        tk = tokenLexico();
        //cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
        if(tk->getValor() != ";"){
            cout<<"ERRO esperava ';' <declara_tipo> linha:"<<contadorLinha-1<<endl;
            cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
            exit(0);
        }
        tk = tokenLexico();
    }while(tk->getTipo()=="PR" && tk->getValor() != "var" && tk->getValor() != "procedimento" && tk->getValor() != "funcao" && tk->getValor() != "inicio");
    cout<<a<<"</declara_tipo>"<<endl;
    decrementaBackSpace();
}

void definicao_var(){
    incrementaBackSpace();
    cout<<a<<"<definicao_var>"<<endl;
    tk = tokenLexico();
    do{
        listaDeIdentificadores();
        if(tk->getValor() != ":"){
            cout<<"ERRO esperava ':' <definicao_var> linha:"<<contadorLinha-1<<endl;

            exit(0);
        }
        tk = tokenLexico();
        if(tk->getTipo() != "PR"){
            cout<<"ERRO esperava PR(boleano,real,inteiro..) <definicao_var> linha:"<<contadorLinha-1<<endl;
            exit(0);
        }
        tk = tokenLexico();
        if(tk->getValor() != ";"){
            cout<<"ERRO esperava ';' <definicao_var> linha:"<<contadorLinha-1<<endl;
            cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
            exit(0);
        }
        tk = tokenLexico();

    }while(tk->getTipo() == "ID");
    cout<<a<<"</definicao_var>"<<endl;
    decrementaBackSpace();
}

void declara_funcao(){
    incrementaBackSpace();
        cout<<a<<"<declara_funcao>"<<endl;
        tk = tokenLexico();
        if(tk->getTipo() != "ID"){
            cout<<"ERRO esperava identificador <def_func> linha:"<<contadorLinha-1<<endl;
            exit(0);
        }
        tk = tokenLexico();
        if(tk->getValor() == "("){
            parametro_formais();
        }
        if(tk->getValor() != ":"){
            cout<<"ERRO esperava ':' <d_p> linha:"<<contadorLinha-1<<endl;
            cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
            exit(0);
        }
        tk = tokenLexico();
        if(tk->getTipo() != "ID"){
            cout<<"ERRO esperava identificador <def_func> linha:"<<contadorLinha-1<<endl;
            cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
            exit(0);
        }
        tk = tokenLexico();
        if(tk->getValor() != ";"){
            cout<<"ERRO esperava ';' <def_func-> linha:"<<contadorLinha-1<<endl;
            cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
            exit(0);
        }
        bloco();
    cout<<a<<"</declara_funcao>"<<endl;
    decrementaBackSpace();
}

void parametro_formais(){
    incrementaBackSpace();
    cout<<a<<"<param_formais>"<<endl;
    do{
        tk = tokenLexico();
        if(tk->getValor() == "var"){
            tk = tokenLexico();
        }
        listaDeIdentificadores();
        if(tk->getValor() != ":"){
            cout<<"ERRO esperava ':' <d_pf> linha:"<<contadorLinha-1<<endl;

            exit(0);
        }
        tk = tokenLexico();
        if(tk->getTipo() != "PR"){
            cout<<"ERRO esperava PR(boleano,real,inteiro..) <d_pf> linha:"<<contadorLinha-1<<endl;
            exit(0);
        }
        tk = tokenLexico();

    }while(tk->getValor() == ";");

    if(tk->getValor() != ")"){
        cout<<"ERRO esperava ')' <d_pf> linha:"<<contadorLinha-1<<endl;
        cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
        exit(0);
    }
    tk = tokenLexico();
    cout<<a<<"</param_formais>"<<endl;
    decrementaBackSpace();
}

void declara_procedimento(){
    incrementaBackSpace();
        cout<<a<<"<declara_procedimento>"<<endl;
        tk = tokenLexico();
        if(tk->getTipo() != "ID"){
            cout<<"ERRO esperava identificador <declara_procedimento> linha:"<<contadorLinha-1<<endl;
            cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
            exit(0);
        }
        tk = tokenLexico();
        if(tk->getValor() == "("){
            parametro_formais();
        }
        if(tk->getValor() != ";"){
            cout<<"ERRO esperava ';' <declara_procedimento> linha:"<<contadorLinha-1<<endl;
            cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
            exit(0);
        }
        bloco();
        cout<<a<<"</declara_procedimento>"<<endl;
    decrementaBackSpace();
}

void subRotinas(){
    incrementaBackSpace();
    cout<<a<<"<sub_rotina>"<<endl;
    if(tk->getValor() == "funcao"){

            declara_funcao();

        }else{

            declara_procedimento();

        }
    cout<<a<<"</sub_rotina>"<<endl;
    decrementaBackSpace();
}

void variavel(){
    incrementaBackSpace();
    cout<<a<<"<variavel>";
    tk = tokenLexico();
    cout<<"</variavel>"<<endl;
    decrementaBackSpace();
}

void numero(){
    incrementaBackSpace();
    cout<<a<<"<numero>"<<endl;
    tk = tokenLexico();
    cout<<a<<"</numero>"<<endl;
    decrementaBackSpace();
}

void chamadaDeFuncao(){
    incrementaBackSpace();
    cout<<a<<"<chamda_de_funcao>"<<endl;
    listaDeExpressao();
    cout<<a<<"</chamda_de_funcao>"<<endl;
    decrementaBackSpace();
}

void fator(){
    incrementaBackSpace();
    cout<<a<<"<fator>"<<endl;
    if(tk->getTipo() == "ID"){
        variavel();
        if(tk->getValor() == "(" ){
            tk = tokenLexico();
            chamadaDeFuncao();
            if(tk->getValor()!= ")"){
                cout<<"ERRO esperava ')' <fator> linha:"<<contadorLinha-1<<endl;
                cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
                exit(0);
            }
        }
    }else if(tk->getTipo() == "NUM"){
        numero();
    }else if(tk->getValor()=="("){
        expressao();
        if(tk->getValor()!= ")"){
                cout<<"ERRO esperava ')' <fator> linha:"<<contadorLinha-1<<endl;
                cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
                exit(0);
        }
        tk = tokenLexico();
    }else{
        cout<<"ERRO esperava 'ID ou um NUM' <fator> linha:"<<contadorLinha-1<<endl;
        cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
        exit(0);
    }
    cout<<a<<"</fator>"<<endl;
    decrementaBackSpace();
}

void termo(){
    incrementaBackSpace();
    cout<<a<<"<termo>"<<endl;
    do{
        fator();
    }while(tk->getValor() == "*" || tk->getValor() == "/" || tk->getValor() == "&&");
    cout<<a<<"</termo>"<<endl;
    decrementaBackSpace();
}

void relacao(){
    incrementaBackSpace();
    cout<<a<<"<relacao>"<<endl;
    tk= tokenLexico();
    cout<<a<<"</relacao>"<<endl;
    decrementaBackSpace();
}

void expressaoSimples(){
    incrementaBackSpace();
    cout<<a<<"<expre_simples>"<<endl;
    if(tk->getValor() == "+" || tk->getValor()== "-"){
        tk = tokenLexico();
    }
    termo();
    if(tk->getValor() == "+" || tk->getValor() == "-" || tk->getValor() == "||"){
            //cout<<a<<"aaaaaaaaaaaaaaaaaaa"<<endl;
        do{
            tk = tokenLexico();
            termo();
        }while(tk->getValor()== "+" || tk->getValor()== "-" || tk->getValor()== "||");
    }
    cout<<a<<"</expre_simples>"<<endl;
    decrementaBackSpace();
}

void expressao(){
    incrementaBackSpace();
    cout<<a<<"<expressao>"<<endl;
    expressaoSimples();
    if(tk->getValor() == "=" || tk->getValor() == "<>" || tk->getValor() == "<=" || tk->getValor() == ">=" ||  tk->getValor() == "<" || tk->getValor() == ">"){
        relacao();
        expressaoSimples();
    }
    cout<<a<<"</expressao>"<<endl;
    decrementaBackSpace();
}

void atribuicao(){
    incrementaBackSpace();
    cout<<a<<"<atribuicao>"<<endl;
    tk = tokenLexico();
    expressao();
    cout<<a<<"</atribuicao>"<<endl;
    decrementaBackSpace();
}

void listaDeExpressao(){
    incrementaBackSpace();
    cout<<a<<"<lista_de_expres>"<<endl;
    do{
        expressao();
        if(tk->getValor()== ";"){
            tk = tokenLexico();
        }
    }while(tk->getValor()== "(" || tk->getTipo()== "ID" || tk->getTipo()== "NUM");
    //tk = tokenLexico();
    cout<<a<<"</lista_de_expres>"<<endl;
    decrementaBackSpace();
}

void chamadaDeProcedimento(){
    incrementaBackSpace();
    cout<<a<<"<cham_procedimento>"<<endl;
    tk = tokenLexico();
    listaDeExpressao();
    if(tk->getValor()!= ")"){
        cout<<"ERRO esperava ')' <cham_procedimento> linha:"<<contadorLinha-1<<endl;
        cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
        exit(0);
    }
    tk = tokenLexico();
    cout<<a<<"</cham_procedimento>"<<endl;
    decrementaBackSpace();
}

void comandoCondicional(){
    incrementaBackSpace();
    cout<<a<<"<cmd_condicional>"<<endl;
    expressao();
    if(tk->getValor()!="entao"){
        cout<<"ERRO esperava 'entao' <cmd_condicional> linha:"<<contadorLinha-1<<endl;
        cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
        exit(0);
    }
    tk = tokenLexico();
    comandoSemRotulo();
    if(tk->getValor()=="senao"){
        tk = tokenLexico();
        comandoSemRotulo();
    }
    cout<<a<<"</cmd_condicional>"<<endl;
    decrementaBackSpace();
}

void comandoRepetitivo(){
    incrementaBackSpace();
    cout<<a<<"<cmd_repeat>"<<endl;
    //cout<<tk->getValor()<<endl;
    expressao();
    if(tk->getValor()!="do"){
        cout<<"ERRO esperava 'do' <cmd_repeat> linha:"<<contadorLinha-1<<endl;
        cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
        exit(0);
    }
    tk = tokenLexico();
    comandoSemRotulo();
    cout<<a<<"</cmd_repeat>"<<endl;
    decrementaBackSpace();

}

void comandoLeia(){
    incrementaBackSpace();
    cout<<a<<"<cmd_leia>"<<endl;
    if(tk->getValor()!="("){
        cout<<"ERRO esperava '(' <-cmd_leia> linha:"<<contadorLinha-1<<endl;
        cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
        exit(0);
    }
    tk = tokenLexico();
    listaDeIdentificadores();
    if(tk->getValor()!=")"){
        cout<<"ERRO esperava ')' <-cmd_leia> linha:"<<contadorLinha-1<<endl;
        cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
        exit(0);
    }
    cout<<a<<"</cmd_leia>"<<endl;
    decrementaBackSpace();
    tk = tokenLexico();
}

void comandoImprima(){
    incrementaBackSpace();
    cout<<a<<"<cmd_imprima>"<<endl;
    if(tk->getValor()!="("){
         cout<<"ERRO esperava '(' <-cmd_imprima> linha:"<<contadorLinha-1<<endl;
        exit(0);
    }
    tk = tokenLexico();
    listaDeExpressao();
    if(tk->getValor()!=")"){
        cout<<"ERRO esperava ')' <-cmd_imprima> linha:"<<contadorLinha-1<<endl;
        exit(0);
    }
   cout<<a<<"</cmd_imprima>"<<endl;
    decrementaBackSpace();
    tk = tokenLexico();
}

void comandoSemRotulo(){
    incrementaBackSpace();
    cout<<a<<"<cmd_sem_rotulo>"<<endl;
    //cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;

    if(tk->getTipo()=="ID"){
            tk = tokenLexico();
            if(tk->getValor()==":="){//atriubuicao
                atribuicao();
            }else if(tk->getValor()=="("){//chamada de procedimento
                chamadaDeProcedimento();
            }else{
                cout<<a<<"erro esperava ':=' ou '(' "<<endl;
            }

    }else if(tk->getValor() == "se"){
        tk = tokenLexico();
        comandoCondicional();
    }else if(tk->getValor() == "enquanto"){
        tk = tokenLexico();
        comandoRepetitivo();
    }else if(tk->getValor() == "leia"){
        tk = tokenLexico();
        comandoLeia();
    }else if(tk->getValor() == "imprima"){
        tk = tokenLexico();
        comandoImprima();
    }else{
        cout<<a<<"-=nenhum comando encontrado"<<endl;
    }
    cout<<a<<"</cmd_sem_rotulo>"<<endl;


    decrementaBackSpace();
}

void comandoComposto(){
    incrementaBackSpace();
    cout<<a<<"<cmd_comp>"<<endl;
    do{
        comandoSemRotulo();

        //tk = tokenLexico();
        if(tk->getValor() != ";"){
            cout<<"ERRO esperava ';' <cmd_comp> linha:"<<contadorLinha-1<<endl;
            cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
            exit(0);
        }
        if(tk->getValor() == ";"){
            tk = tokenLexico();
        }
    }while(tk->getValor() != "fim");
    cout<<a<<"</cmd_comp>"<<endl;
    tk = tokenLexico();
    decrementaBackSpace();/** proximo puxa token **/
}

void bloco(){
    incrementaBackSpace();
    cout<<a<<"<bloco>"<<endl;
    tk = tokenLexico();

    if(tk->getValor() == "tipo"){
       declara_tipo();
    }

    if(tk->getValor() == "var"){
       definicao_var();
    }
    if(tk->getValor() == "procedimento" || tk->getValor() == "funcao"){

        do{
            subRotinas();
        }while(tk->getValor() == "procedimento" || tk->getValor() == "funcao");

    }

    if(tk->getValor()=="inicio"){
         tk = tokenLexico();
         comandoComposto();
    }
    //tk = tokenLexico();/**deve ser um ponto**/
    cout<<a<<"</bloco>"<<endl;
    decrementaBackSpace();
}

void sintatico(){
    ponteiro = fgetc(arquivo);
    tk = tokenLexico();
    cout<<a<<"<programa>"<<endl;
    if(tk->getValor()!= "programa"){
       cout<<"ERRO esperava programa <s> linha:"<<contadorLinha-1<<endl;
       exit(0);
    }
    tk = tokenLexico();

    if(tk->getTipo() != "ID"){
       cout<<"ERRO esperava identificador <s> linha:"<<contadorLinha-1<<endl;
       exit(0);
    }
    tk = tokenLexico();
    if(tk->getValor() != ";"){
       cout<<"ERRO esperava ';' <s>"<<tk->getValor()<<" linha:"<<contadorLinha-1<<endl;
       exit(0);
    }
    bloco();
    if(tk->getValor() != "."){
       cout<<tk->getValor()<<":"<<tk->getTipo()<<endl;
       cout<<"ERRO esperava '.' linha:"<<contadorLinha-1<<endl;
       exit(0);
    }
    cout<<a<<"</programa>"<<endl;
}
