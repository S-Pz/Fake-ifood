#include <stdio.h>
#include <stdlib.h>

void printarTabuleiro(int tabuleiro[9][9]);
void salvarArquivo(int jogo[9][9],int mascara[9][9], int jogoResolvido[9][9]);

int menu(){
    
    int opcao;
    
    printf("----BEM VINDO AO SUDOKU----\n");
    printf("1-Carregar jogo \n2-Novo Jogo Aleatorio \n3-Sair\n");
    scanf("%d", &opcao);

    if (opcao != 1 && opcao != 2 && opcao != 3 ){
        system("clear");
       printf("OPCAO INVALIDA\n");

        opcao = menu();
    }
    return opcao;
}

void lerArquivo(FILE *table, int jogo[9][9], int jogoResolvido[9][9]){

    char c;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){

            fscanf(table,"%c", &c);

            if(c == '.'){
                jogo[i][j] = 0;

            }else{
                jogo[i][j] = atoi(&c);
            }
        }

        fscanf(table,"%c", &c);
    }
    
    //ler o \n
    fscanf(table,"%c", &c);

    //jogo resolvido
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fscanf(table,"%c", &c);
            jogoResolvido[i][j] = atoi(&c);
        }
        fscanf(table,"%c", &c);
    }
}

int menuJogada(int jogo[9][9]){

    int opcao;

    printf("1-Adicionar Jogada\n");
    printf("2-Remover Jogada\n");
    printf("3-Salvar Jogo\n");
    printf("4-Sair do jogo\n");
    scanf("%d", &opcao);

    if (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4){
        system("clear");
        printarTabuleiro(jogo);
        printf("OPCAO INVALIDA\n");
        opcao = menuJogada(jogo);
    }
    return opcao;
}

void removerJogada(int jogo[9][9], int mascara[9][9]){
    int linha,coluna;

    printf("Digite a linha coluna para excluir: ");
    scanf("%d %d", &linha, &coluna);

    if ((linha <= 9 && linha > 0) && (coluna <= 9 && coluna > 0)){
       if(mascara[linha-1][coluna-1] == 0){
           jogo[linha-1][coluna-1] = 0;
        }else{
           printf("Posicao Fixa!\n");
           removerJogada(jogo, mascara);
        }
    }else{
        printf("Posicao invalida!\n");
        removerJogada(jogo, mascara);
    }
}

void adicionarJogada(int jogo[9][9], int mascara[9][9]){
    int linha,coluna,valor;

    printf("Digite a linha coluna e valor: ");
    scanf("%d %d %d", &linha, &coluna, &valor);

    if ((linha <= 9 && linha > 0) && (coluna <= 9 && coluna > 0) && (valor <=9 && valor > 0)){

       if(mascara[linha-1][coluna-1] == 0){
           jogo[linha-1][coluna-1] = valor;
        }else{
           printf("Posicao Fixa!\n");
           adicionarJogada(jogo, mascara);
        }
    }else{
        printf("Posicao ou valor invalidos!\n");
        adicionarJogada(jogo, mascara);
    }
} 

void printarTabuleiro(int tabuleiro[9][9]){

    system("clear");

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if( tabuleiro[i][j] == 0){
                printf("|   ");
            }else{
                printf("| %d ", tabuleiro[i][j]);
            }
        }

        printf("|");
        printf("\n-------------------------------------\n");
    }
}

void criarMascara(int jogo[9][9], int mascara[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            mascara[i][j] = jogo[i][j];
        }
    }
}

void salvarArquivo(int jogo[9][9],int mascara[9][9], int jogoResolvido[9][9]){

    FILE *arq;
    arq = fopen("savedGame.txt","w");

    for(int i= 0; i<9; i++){
        for(int j=0; j<9; j++){
            if(jogo[i][j] == 0){
                fprintf(arq, ".");
            }
            else{
                fprintf(arq, "%d", jogo[i][j]);
            }
        }
        fprintf(arq,"\n");
    }
    fprintf(arq,"\n");

    for(int i= 0; i<9; i++){
        for(int j=0; j<9; j++){
            if(mascara[i][j] == 0){
                fprintf(arq, ".");
            }
            else{
                fprintf(arq, "%d", mascara[i][j]);
            }
        }
        fprintf(arq, "\n");
    }
    fprintf(arq,"\n");

    for(int i= 0; i<9; i++){
        for(int j=0; j<9; j++){
            if(jogoResolvido[i][j] == 0){
                fprintf(arq, ".");
            }
            else{
                fprintf(arq, "%d", jogoResolvido[i][j]);
            }
        }
        fprintf(arq,"\n");
    }
    fclose(arq);
}

void loadGame(int jogo[9][9], int mascara[9][9], int jogoResolvido[9][9]){

    FILE *arq;
    arq = fopen("savedGame.txt","r");

    char c;

    //Lê o jogo salvo
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){

            fscanf(arq,"%c", &c);

            if(c == '.'){
                jogo[i][j] = 0;

            }else{
                jogo[i][j] = atoi(&c);
            }
        }
        fscanf(arq,"%c", &c);
    }
    
    //Lê o '\n'
    fscanf(arq,"%c", &c);

    //Lê a máscara
    for(int i = 0; i < 9; i++){
        for(int j = 0; j<9; j++){

            fscanf(arq, "%c",&c);

            if(c == '.'){
                mascara[i][j] = 0;
            }else{
                mascara[i][j] = atoi(&c);
            }
        }
        fscanf(arq, "%c", &c);
    }

    //Lê o '\n'
    fscanf(arq,"%c", &c);

    //Lê o jogo resolvido
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            
            fscanf(arq,"%c", &c);
            jogoResolvido[i][j] = atoi(&c);
        }
        fscanf(arq,"%c", &c);
    }
    fclose(arq);
}

int main(){

    FILE *table;
    table = fopen("table2.txt", "r");
    
    int jogo[9][9];
    int jogoResolvido[9][9];
    int mascara[9][9];

    int opcaoMenuInicial = menu();
    int opcaoMenuJogo;
    
    switch (opcaoMenuInicial){

        case 1: // Carregar jogo salvo

            loadGame(jogo, mascara, jogoResolvido);
            printarTabuleiro(jogo);

            while(1){

                opcaoMenuJogo = menuJogada(jogo);

                switch (opcaoMenuJogo){
                    case 1: //adicionar jogada
                        adicionarJogada(jogo, mascara);
                        printarTabuleiro(jogo);
                    break;
                    case 2: //remover jogada
                        removerJogada(jogo, mascara);
                        printarTabuleiro(jogo);
                    break;
                    case 3: //salvar
                        salvarArquivo(jogo, mascara, jogoResolvido);
                    break;
                    default: //sair
                        return 0;
                    break;
                }
            }
        break;

        case 2: //Jogo novo

            lerArquivo(table, jogo, jogoResolvido);
            criarMascara(jogo, mascara);
            printarTabuleiro(jogo);
            
            while(1){

                opcaoMenuJogo = menuJogada(jogo);

                switch (opcaoMenuJogo){
                    case 1: //adicionar jogada
                        adicionarJogada(jogo, mascara);
                        printarTabuleiro(jogo);
                    break;
                    case 2: //remover jogada
                        removerJogada(jogo, mascara);
                        printarTabuleiro(jogo);
                    break;
                    case 3: //salvar
                        salvarArquivo(jogo, mascara, jogoResolvido);
                    break;
                    default: //sair
                        return 0;
                    break;
                }
            }
        break;

        default:
            return 0;
        break;
    }

    fclose(table);
    return 0;
}