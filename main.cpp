#include "sintatico.h" // contem analisador léxico

#include <conio.h>
#include <stdio.h>

string caminhoArquivo = "fonte.txt";
FILE *arquivo;

int main(){
    arquivo = fopen("fonte.txt","rt");
    if(arquivo ==NULL){
        cout<<"arquivo nao abriu"<<endl;
        exit(0);
    }
    cout<<">>-compilando-<<"<<endl;

    //analiseLexicaArquivo();

    sintatico();
    cout<<">>-fim compilacao-<<"<<endl;
    fclose(arquivo);
    printf("Tecle ESC Para Sair");
    int tecla;
    getch();
    system("PAUSE");
}
