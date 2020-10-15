#include <vector>
#include "estruturaToken.h"

Token *tokeny = new Token();

int estado;
int contadorLinha = 1;
string palavra;
char ponteiro;
extern FILE *arquivo;

vector <string> listaPalavrasReservadas = {"do","imprima","leia","inicio","programa","fim","se","entao","senao", "enquanto","faca","ate","repita","inteiro","real","caractere","boleano","caso","escolha","fim_escolha","procedimento","funcao","de","para","fim_do_se","var","tipo"};

char tipoDoPonteiro(char ponteiro){

    if(isalpha(ponteiro)){ //se � letra
        if(islower(ponteiro)){ //se � minuscula
            return 'l';
        }else{  //se � maiuscula
            return 'L';
        }
    }else if(isdigit(ponteiro)){ //se � digito
        return 'n';
    }else if(ponteiro == ' '){ //se � espa�o em branco
        return 'e';
    }else if(ponteiro == '\n'){ //se � quebra de linha
        return 'q';
    }else if(ponteiro == '#'){ //se � simbolo que pode ser incluso no identificador
        return '#';
    }else if(ponteiro == '_'){ //se � simbolo que pode ser incluso no identificador
        return '_';
    }else if(ponteiro == '&' ||ponteiro == '|' || ponteiro == ';' || ponteiro == '*'|| ponteiro == ','|| ponteiro == '.'|| ponteiro == '+'|| ponteiro == '-'|| ponteiro == '('|| ponteiro == ')'|| ponteiro == '<'|| ponteiro == '>'|| ponteiro == ':'|| ponteiro == '='|| ponteiro == '}'|| ponteiro == '{'|| ponteiro == '@'|| ponteiro == '/'){  //se � outro simbolo especial
        return 's';
    }else{
        return 'm';
    }
}

void lexico(){
    tokeny->clearToken();
    estado = 0;
    while(!feof(arquivo)){
        //cout<<"<e:"<<estado<<">";
        char tpont = tipoDoPonteiro(ponteiro);
        //cout<<"."<<ponteiro<<"."<<endl;

        if(ponteiro == '\n'){
            contadorLinha++;
            //cout<<"<li:"<<contadorLinha<<">";
        }
        if (ponteiro == '\n' && estado==0){
            //cout<<"<->";
            ponteiro = fgetc(arquivo);
            return ;//tokeny.valor;
        }else if(tpont == 'q' && estado!=0){
            ponteiro = fgetc(arquivo);
            //return tokeny.valor;
        }else if(tpont == 'e'){
            ponteiro = fgetc(arquivo);
            //return ;//tokeny.valor;
        }else if(ponteiro == '\t' ){
            ponteiro = fgetc(arquivo);
            return;
            //return ;//tokeny.valor;
        }
            switch (estado){

                case 0:
                    tokeny->setAddChar(ponteiro);
                    switch (tpont){
                        case 'l'://letra minuscula
                            tokeny->setTipo("ID");
                            estado=2;
                            //tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://letra maiuscula
                            estado=1;
                            //tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'n':/*letra numero*/
                            estado=13;
                            //tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 's'://simbolo
                            tokeny->setTipo("SE");
                            //tokeny->setAddChar(ponteiro);
                            switch(ponteiro){
                                case '/':
                                    estado=16;
                                    ponteiro = fgetc(arquivo);
                                    break;
                                case '*':
                                    estado=27;
                                    ponteiro = fgetc(arquivo);
                                    break;
                                case '@':
                                    estado=20;
                                    ponteiro = fgetc(arquivo);
                                    break;
                                case ':':
                                    estado=23;
                                    ponteiro = fgetc(arquivo);
                                    break;
                                case '+':
                                    estado=23;
                                    ponteiro = fgetc(arquivo);
                                    break;
                                case '=':
                                    estado=23;
                                    ponteiro = fgetc(arquivo);
                                    break;
                                case '>':
                                    estado=23;
                                    ponteiro = fgetc(arquivo);
                                    break;
                                case '<':
                                    estado=25;
                                    ponteiro = fgetc(arquivo);
                                    break;
                                case '&':
                                    estado=32;
                                    ponteiro = fgetc(arquivo);
                                    break;
                                case '|':
                                    estado=34;
                                    ponteiro = fgetc(arquivo);
                                    break;
                                default:
                                    estado=31;
                                    ponteiro = fgetc(arquivo);
                                    //return ;//tokeny.valor;
                                    break;
                            }
                            break;
                        default://quebra de linha ou vazio
                            //tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            //return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 0
                case 1:
                     tokeny->setTipo("ID");
                    switch (tpont){
                        case 'l'://letra minuscula
                            estado=3;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://letra maiuscula
                            estado=3;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'n'://letra numero
                            estado=3;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case '_'://letra numero
                            estado=3;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case '#'://letra numero
                            estado=7;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha

                            ponteiro = fgetc(arquivo);
                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 1
                case 2:

                    switch (tpont){
                        case 'l'://letra minuscula
                            tokeny->setTipo("PPR");
                            estado=5;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://letra maiuscula
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'n'://letra numero
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case '_'://letra numero
                            estado=3;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case '#'://letra numero
                            estado=7;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha
                            //ponteiro = fgetc(arquivo);

                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 2
                case 3:/**/
                    tokeny->setTipo("ID");
                    switch (tpont){
                        case 'l'://letra minuscula
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://letra maiuscula
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'n'://letra numero
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case '#'://letra numero
                            estado=7;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha

                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 3
                case 4:
                    switch (tpont){
                        case 'l'://letra minuscula
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://letra maiuscula
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'n'://letra numero
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case '#'://letra numero
                            estado=7;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha
                            //ponteiro = fgetc(arquivo);

                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 4
                case 5:
                    tokeny->setTipo("PPR");
                    switch (tpont){
                        case 'l'://letra minuscula
                            estado=6;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://letra maiuscula
                            tokeny->setTipo("ID");
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'n'://letra numero
                             tokeny->setTipo("ID");
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case '#'://letra numero
                            tokeny->setTipo("ID");
                            estado=7;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha
                            //ponteiro = fgetc(arquivo);
                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 5
                case 6:
                    switch (tpont){
                        case 'l'://letra minuscula
                            tokeny->setTipo("PPR");
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://letra maiuscula
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'n'://letra numero
                            estado=4;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case '#'://letra numero
                            tokeny->setTipo("ID");
                            estado=7;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case '_'://letra numero
                            estado=9;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha
                            return ;//tokeny.valor;
                            break;

                    }
                    break;//fim case 6
                case 7:/**/
                    switch (tpont){
                        case 'l'://letra minuscula
                            estado=8;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://letra maiuscula
                            estado=8;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha

                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 7
                case 8:
                    switch (tpont){
                        case 'l'://letra minuscula
                            estado=8;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://letra maiuscula
                            estado=8;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 'n'://letra numero
                            estado=8;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha
                            //ponteiro = fgetc(arquivo);

                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 8
                case 9:/**/
                    switch (tpont){
                        case 'l'://letra minuscula
                            estado=10;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha

                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 9
                case 10:
                    switch (tpont){
                        case 'l'://letra minuscula
                            estado=10;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case '_'://letra numero
                            estado=11;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha
                            //ponteiro = fgetc(arquivo);

                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 10
                case 11:/**/
                    switch (tpont){
                        case 'l'://letra minuscula
                            estado=12;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha

                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 11
                case 12:
                    switch (tpont){
                        case 'l'://letra minuscula
                            estado=12;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha
                            //ponteiro = fgetc(arquivo);
                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 12
                case 13:
                    tokeny->setTipo("NUM");
                    switch (tpont){
                        case 'n'://letra minuscula
                            estado=13;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        case 's'://letra minuscula
                            if(ponteiro==','){
                                estado=14;
                                tokeny->setAddChar(ponteiro);
                                ponteiro = fgetc(arquivo);
                            }else{
                                return ;//tokeny.valor;
                            }
                            break;
                        default://quebra de linha
                            //ponteiro = fgetc(arquivo);
                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 13
                case 14:/**/
                    switch (tpont){
                        case 'n'://letra minuscula
                            estado=15;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                         default://quebra de linha
                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 14
                case 15:
                    switch (tpont){
                        case 'n'://letra minuscula
                            estado=15;
                            tokeny->setAddChar(ponteiro);
                            ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha
                            //ponteiro = fgetc(arquivo);
                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 15
                case 16:
                    switch (tpont){
                        case 's'://simbolo
                            if(ponteiro=='/'){
                                estado=17;
                                tokeny->setRemoveChar();
                                cout<<"<inicio de comentario vl>"<<endl;
                                ponteiro = fgetc(arquivo);
                            }else{
                                return;//tokeny.valor;
                            }
                        break;
                        default:

                            //quebra de linha
                           // ponteiro = fgetc(arquivo);
                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 16
                case 17:/**/
                    //cout<<"."<<ponteiro<<"."<<endl;
                    switch (tpont){
                        case 's'://simbolo
                            if(ponteiro == '/'){
                                estado=18;
                                ponteiro = fgetc(arquivo);
                            }else{
                                estado=17;
                                ponteiro = fgetc(arquivo);
                                //cout<<"else*"<<ponteiro;
                            }
                            break;
                        case 'l'://minuscula
                                estado=17;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://maiuscula
                                estado=17;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 'n'://numero
                                estado=17;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 'm'://numero
                                estado=17;
                                ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha
                            //cout<<"default do caso 17 algo raro:"<<ponteiro;
                            if(ponteiro == '/'){
                                estado=18;
                                ponteiro = fgetc(arquivo);
                                //cout<<"if"<<ponteiro;
                            }else{
                                estado=17;
                                ponteiro = fgetc(arquivo);
                                //cout<<"else**"<<ponteiro;
                            }
                            break;
                    }
                    break;//fim case 17
                case 18:/**/
                    switch (tpont){
                        case 's'://simbolo
                            if(ponteiro == '/'){
                                //tokeny->setAddChar(ponteiro);
                                estado=19;
                                cout<<"<fim de comentario vl>"<<endl;
                                ponteiro = fgetc(arquivo);
                            }else{
                                estado=17;
                                ponteiro = fgetc(arquivo);
                            }
                            break;
                        case 'l'://minuscula
                                estado=17;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://maiuscula
                                estado=17;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 'n'://numero
                                estado=17;
                                ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha
                            //cout<<"default do caso 18 algo raro";
                            if(ponteiro == '/' ){
                                //tokeny->setAddChar(ponteiro);
                                estado=19;
                                cout<<"<fim de comentario vl>"<<endl;
                                ponteiro = fgetc(arquivo);
                            }else{
                                estado=17;
                                ponteiro = fgetc(arquivo);
                            }
                            //return tokeny.valor;
                            break;
                    }
                    break;//fim case 18
                case 19:
                    estado=0;
                    //ponteiro = fgetc(arquivo);
                    //return ;//tokeny.valor;
                    break;//fim case 19
                case 20:
                    switch (tpont){
                        case 's'://simbolo
                            if(ponteiro=='@'){
                                estado=21;
                                tokeny->setRemoveChar();
                                ponteiro = fgetc(arquivo);
                                cout<<"<inicio de comentario ul>"<<endl;
                            }else{
                                ponteiro = fgetc(arquivo);
                                return ;//tokeny.valor;
                            }
                            break;
                        default:

                            //quebra de linha
                            //ponteiro = fgetc(arquivo);
                            return ;//tokeny.valor;
                            break;
                    }
                    break;//fim case 20
                case 21:/**/
                    switch (tpont){
                        case 'l'://minuscula
                                estado=21;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://maiuscula
                                estado=21;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 'n'://numero
                                estado=21;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 'q'://simbolo
                                estado=22;
                                cout<<"<fim de comentario ul*>"<<endl;
                                //return ;//tokeny.valor;
                            break;
                        case 'm'://numero
                                estado=21;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 's'://simbolo
                                estado=21;
                                //cout<<ponteiro;
                                ponteiro = fgetc(arquivo);
                                //cout<<":<entrou simbolo>"<<endl;
                                //return ;//tokeny.valor;
                            break;
                        default://simbolo
                                estado=21;
                                //cout<<ponteiro;
                                ponteiro = fgetc(arquivo);
                                //cout<<":<entrou DEFALT>"<<endl;
                                //return ;//tokeny.valor;
                            break;

                    }
                    break;//fim case 21
                case 22:
                    estado=0;
                    //return ;
                    //tokeny.valor;
                    break;//fim case 22*/
                case 23:
                    if (ponteiro == '='){
                        tokeny->setAddChar(ponteiro);
                        estado = 24;
                        ponteiro = fgetc(arquivo);
                    }else{
                        return ;//tokeny.valor;
                    }
                    break;//fim case 23
                case 24:
                    return ;//tokeny.valor;
                    break;//fim case 24*/
                case 25:
                    if (ponteiro == '>'||ponteiro == '='){
                        tokeny->setAddChar(ponteiro);
                        estado = 26;
                        ponteiro = fgetc(arquivo);
                    }else{
                        //ponteiro = fgetc(arquivo);
                        return ;//tokeny.valor;
                    }
                    break;//fim case 25
                case 26:
                    return ;//tokeny.valor;
                    break;//fim case 26*/
                case 27:
                    switch (tpont){
                        case 's'://simbolo
                            if(ponteiro=='*'){
                                estado=28;
                                tokeny->setRemoveChar();
                                cout<<"<inicio de comentario vl>"<<endl;
                                ponteiro = fgetc(arquivo);
                            }else{
                                return;// tokeny.valor;
                            }
                        break;
                        default:
                            return ;
                            break;
                    }
                    break;//fim case 27
                case 28:/**/
                    //cout<<"."<<ponteiro<<"."<<endl;
                    switch (tpont){
                        case 's'://simbolo
                            if(ponteiro == '*'){
                                estado=29;
                                ponteiro = fgetc(arquivo);
                            }else{
                                estado=28;
                                ponteiro = fgetc(arquivo);
                                //cout<<"else*"<<ponteiro;
                            }
                            break;
                        case 'l'://minuscula
                                estado=28;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://maiuscula
                                estado=28;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 'n'://numero
                                estado=28;
                                ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha
                            //cout<<"default do caso 17 algo raro:"<<ponteiro;
                            if(ponteiro == '*'){
                                estado=29;
                                ponteiro = fgetc(arquivo);
                                //cout<<"if"<<ponteiro;
                            }else{
                                estado=28;
                                ponteiro = fgetc(arquivo);
                                //cout<<"else**"<<ponteiro;
                            }
                            break;
                    }
                    break;//fim case 28
            case 29:/**/
                    switch (tpont){
                        case 's'://simbolo
                            if(ponteiro == '*'){
                                //tokeny->setAddChar(ponteiro);
                                estado=19;
                                cout<<"<fim de comentario vl>"<<endl;
                                ponteiro = fgetc(arquivo);
                            }else{
                                estado=28;
                                ponteiro = fgetc(arquivo);
                            }
                            break;
                        case 'l'://minuscula
                                estado=28;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 'L'://maiuscula
                                estado=28;
                                ponteiro = fgetc(arquivo);
                            break;
                        case 'n'://numero
                                estado=28;
                                ponteiro = fgetc(arquivo);
                            break;
                        default://quebra de linha
                            //cout<<"default do caso 18 algo raro";
                            if(ponteiro == '*' ){
                                //tokeny->setAddChar(ponteiro);
                                estado=30;
                                cout<<"<fim de comentario vl>"<<endl;
                                ponteiro = fgetc(arquivo);
                            }else{
                                estado=28;
                                ponteiro = fgetc(arquivo);
                            }
                            //return tokeny.valor;
                            break;
                    }
                    break;//fim case 29
                case 30:
                    estado=0;
                    //ponteiro = fgetc(arquivo);
                    //return ;//tokeny.valor;
                    break;//fim case 30
                case 31:
                    return ;//tokeny.valor;
                    break;//fim case 31*/
                case 32:
                    if (ponteiro == '&'){
                        tokeny->setAddChar(ponteiro);
                        estado = 33;
                        ponteiro = fgetc(arquivo);
                    }else{
                        return ;//tokeny.valor;
                    }
                    break;//fim case 32
                case 33:
                    return ;//tokeny.valor;
                    break;//fim case 33*/
                case 34:
                    if (ponteiro == '|'){
                        tokeny->setAddChar(ponteiro);
                        estado = 35;
                        ponteiro = fgetc(arquivo);
                    }else{
                        return ;//tokeny.valor;
                    }
                    break;//fim case 34
                case 35:
                    return ;//tokeny.valor;
                    break;//fim case 35*/
                default:
                   cout<<"default automato";
                   return ;//tokeny.valor;
                   break;//fim case default
            }
        /*}*/
    }
    return ;//tokeny.valor;
}

void analisePalavraReservada(){
    bool existe = false;
    if(tokeny->getTipo() == "PPR"){
            for(int i=0 ;i<listaPalavrasReservadas.size();i++){
                if(tokeny->getValor() == listaPalavrasReservadas[i]){
                        existe = true;
                }
            }
            if(existe){
                //cout<<"Verificando...  PR"<<listaPalavrasReservadas[i]<<" ";
                tokeny->setTipo("PR");
            }else{
                //cout<<"Verificando...  PR"<<listaPalavrasReservadas[i]<<" ";
                tokeny->setTipo("ID");
            }

    }else{

    }
}

//se declarar o lexico.h na main pode invocar que ele fará toda a analise lexica do arquivo.
void analiseLexicaArquivo(){
    ponteiro = fgetc(arquivo);
     while(!feof(arquivo)){
        lexico();
        palavra  = tokeny->getValor();

        if(/*(estado == 0 && palavra!="" ) ||*/ estado == 3 || estado == 7 || estado == 9 || estado == 11 || estado == 14 || estado == 17|| estado == 18|| estado == 21 ||estado == 32){
            cout<<"ERRO linha:"<<contadorLinha<<" estado:"<<estado<<" estado invalido, ponteiro:"<<ponteiro<<endl;
            break;
        }else{
            if(palavra==""){
                    /**
                tokeny->setTipo("NULL");
                tokeny->setValor("NULL");
                cout<<tokeny->getValor()<<"<>"<<tokeny->getTipo()<<endl;
                **/
            }else{
                analisePalavraReservada();
                  cout<<tokeny->getValor()<<" "<<tokeny->getTipo()<<endl;
            }

        }

     }
    fclose(arquivo);
}

Token *tokenLexico(){
    //cout<<">>compilando<<"<<endl;

    lexico();
    palavra  = tokeny->getValor();
    if(/*(estado == 0 && palavra!="" ) ||*/ estado == 3 || estado == 7 || estado == 9 || estado == 11 || estado == 14 || estado == 17|| estado == 18|| estado == 21){
        cout<<"ERRO linha:"<<contadorLinha<<" estado:"<<estado<<" estado invalido, ponteiro:"<<ponteiro<<endl;
        exit(0);
    }else{
        if(palavra==""){
            tokeny->setTipo("NULL");
            tokeny->setValor("NULL");
            tokeny = tokenLexico();
            return tokeny;
        }else{
            analisePalavraReservada();
            return tokeny;
        }

    }
}
