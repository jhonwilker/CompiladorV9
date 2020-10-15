#include <iostream>
#include <string.h>

using namespace std;

class Token{

    string valor;
    string tipo;
    public:
        string getValor();
        string getTipo();
        void setValor(string valor);
        void setAddChar(char caracter);
        void setTipo(string tipo);
        void clearToken();
        void setRemoveChar();
};

string Token::getTipo(){
    return this->tipo;
}

void Token::setTipo(string tipo){
    this->tipo = tipo;
}

string Token::getValor(){
    return this->valor;
}

void Token::setValor(string valor){
    this->valor = valor;
}

void Token::clearToken(){
    this->valor.clear();
    this->tipo = "X";
}

void Token::setAddChar(char caracter){
this->valor.push_back(caracter);
}

void Token::setRemoveChar(){
this->valor.pop_back();
}



