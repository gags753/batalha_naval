#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//estrutura responsavel por armazenar as informacoes dos barcos atingidos e afundados
struct POSICOES
{
    int submarinos;
    int barco2_1;
    int barco2_2;
    int barco3;
    int barco4;
    int barco5;
    int barcos_acertados;
};

//função que irá montar o tabuleiro, definir onde existe embarcações e onde não existe
void construir_tabuleiro(int tabuleiro[][10]);

struct POSICOES acertou(int tabuleiro[][10], struct POSICOES acertos, int coordenadas[],int vez_atual);

void mostrar_tabuleiro(int tabuleiro[][10], struct POSICOES acertos,int vez_atual);


int main()
{
    //definindo os tabuleiros e as embarcações
    int mapa_jogador[10][10];
    int mapa_CPU[10][10];
    struct POSICOES acertos_jogador = {0,0,0,0,0,0,0};
    //variavel para a cpu
    struct POSICOES acertos_cpu = {0,0,0,0,0,0,0};


    int coordenadas[2]; //vetor que recebe as posicoes das jogadas
    int vez_atual; //variavél para definir a vez, se é do jogador ou dá máquina
    srand(time(NULL));

    // iniciando os tabuleiros com o valor 0
    construir_tabuleiro(mapa_CPU);
    construir_tabuleiro(mapa_jogador);


    vez_atual = rand() %101; //determinar quem comeca jogando
    if(vez_atual <= 50)
    {
        vez_atual = 1; //vez do usuario
    }
    else
    {
        vez_atual = 2; //vez da maquina
    }

    while(1) //laço onde vai rodar o programa
    {
        if(vez_atual == 1) //vez do jogador
        {
            mostrar_tabuleiro(mapa_CPU,acertos_jogador,vez_atual);
            printf("\nSua vez\n");
            while(2) //validacao de dados
            {
                printf("Digite a linha e coluna: ");
                scanf("%d %d",&coordenadas[0], &coordenadas[1]);
                coordenadas[0] --; //as linhas e colunas de uma matriz 10x10 vao de 0-9
                coordenadas[1] --; //por tanto, deve ter seu valor diminuido, o usuario nao precisa usar essa logica
                //validando por posição existente no tabuleiro
                if((coordenadas[0] < 0 || coordenadas[0] > 9) || (coordenadas[1] < 0 || coordenadas[1] > 9))
                {
                    printf("Coordenadas inválidas");
                }
                else if(mapa_CPU[coordenadas[0]][coordenadas[1]] < 0)
                {
                    printf("Posição já atingida");
                }
                else
                {
                    break;
                }
            }
            acertos_jogador = acertou(mapa_CPU,acertos_jogador,coordenadas,vez_atual); // onde a jogada será feita no tabuleiro

            if(acertos_jogador.barcos_acertados == 8)
            {
                printf("Você ganhou");
                break;
            }
            else
            {
                vez_atual = 2;
            }
        }
        else if(vez_atual ==2) // vez da maquina
        {
            mostrar_tabuleiro(mapa_jogador,acertos_cpu,vez_atual);
            printf("Vez da CPU");
            system("pause");
            while(2) //garantir que a cpu nao escolha uma posicao preenchida
            {
                coordenadas[0] = rand() %10;
                coordenadas[1] = rand() %10;
                if(mapa_jogador[coordenadas[0]][coordenadas[1]] > -1)
                {
                    break;
                }
            }
            acertos_cpu = acertou(mapa_jogador,acertos_cpu,coordenadas,vez_atual);

            if(acertos_cpu.barcos_acertados == 8)
            {
                printf("A cpu ganhou");
                break;
            }
            else
            {
                vez_atual = 1;
            }
        }
    }



    return 0;
}

void construir_tabuleiro(int tabuleiro[][10])
{
    for (int i = 0; i < 10; i ++)
    {
        for(int j = 0; j < 10; j ++)
        {
            tabuleiro[i][j] = 0; //primeiro passo, inciando tudo em 0
        }
    }

    srand(time(NULL));
    int linha_ale;
    int coluna_ale;
    int barco_atual = 0;


    //preenchendo porta avioes
    linha_ale = rand() % 8;
    coluna_ale = rand() % 8;

    tabuleiro[linha_ale][coluna_ale] = 6;
    tabuleiro[linha_ale][coluna_ale+1] = 6;
    tabuleiro[linha_ale][coluna_ale+2] = 6;
    tabuleiro[linha_ale+1][coluna_ale+1] = 6;
    tabuleiro[linha_ale+2][coluna_ale+1] = 6;

    //preenchendo embarcação de até 4 peças

    while(1)
    {
        barco_atual ++;
        int barco_preenchido = 0;
        int posicoes_livres = 0;

        switch(barco_atual)
        {
            case 1:
                barco_preenchido = 0;
                while(1)
                {
                    linha_ale = rand() %10;
                    coluna_ale = rand() % 10;
                    posicoes_livres = tabuleiro[linha_ale][coluna_ale];
                    if(posicoes_livres == 0)
                    {
                        tabuleiro[linha_ale][coluna_ale] = 1;
                        barco_preenchido ++;
                    }
                    if(barco_preenchido == 3)
                    {
                        break;
                    }
                }
                break;

            case 2:
                barco_preenchido = 0;
                while(2)
                {
                    posicoes_livres = 0;
                    linha_ale = rand() %10;
                    coluna_ale = rand() %9;
                    posicoes_livres = tabuleiro[linha_ale][coluna_ale] + tabuleiro[linha_ale][coluna_ale+1];
                    if(posicoes_livres == 0)
                    {
                        if(barco_preenchido == 0)
                        {
                            tabuleiro[linha_ale][coluna_ale] = 2;
                            tabuleiro[linha_ale][coluna_ale + 1] = 2;
                            barco_preenchido ++;
                        }
                        else if(barco_preenchido == 1)
                        {
                            tabuleiro[linha_ale][coluna_ale] = 3;
                            tabuleiro[linha_ale][coluna_ale + 1] = 3;
                            barco_preenchido ++;
                        }
                    }
                    if(barco_preenchido == 2)
                    {
                        break;
                    }
                }
                break;
            case 3:
                barco_preenchido = 0;
                while(1)
                {
                    posicoes_livres = 0;
                    linha_ale = rand() % 10;
                    coluna_ale = rand() % 8;

                    for(int i = 0; i < 3; i ++)
                    {
                        posicoes_livres = 0 + tabuleiro[linha_ale][coluna_ale + i];
                    }

                    if(posicoes_livres == 0)
                    {
                        for(int i = 0; i < 3; i ++)
                        {
                            tabuleiro[linha_ale][coluna_ale + i] = 4;
                        }
                        barco_preenchido ++;
                        if(barco_preenchido == 1)
                        {
                            break;
                        }
                    }
                }
                break;
            case 4:
                barco_preenchido = 0;
                while(1)
                {
                    posicoes_livres = 0;
                    linha_ale = rand() % 7;
                    coluna_ale = rand() % 10;

                    for(int i = 0; i < 4; i ++)
                    {
                        posicoes_livres = 0 + tabuleiro[linha_ale + i][coluna_ale];
                    }

                    if(posicoes_livres == 0)
                    {
                        for(int i = 0; i < 4; i ++)
                        {
                            tabuleiro[linha_ale + i][coluna_ale] = 5;
                        }
                        barco_preenchido ++;
                        if(barco_preenchido == 1)
                        {
                            break;
                        }
                    }
                }
                break;
        }


        if(barco_atual > 4)
        {
            break;
        }

    }
}

void mostrar_tabuleiro(int tabuleiro[][10], struct POSICOES acertos,int vez_atual)
{
    system("cls");
    if(vez_atual == 2)
    {
        printf("\nColunas:   1    2    3    4    5    6    7    8    9    10 ");
        for (int i = 0; i < 10; i ++)
        {
            if(i == 9)
            {
                printf("\nLinha 10 ");
            }
            else
            {
                printf("\nLinha 0%d ",i+1);
            }
            for(int j = 0; j < 10; j ++)
            {
                switch(tabuleiro[i][j])
                {
                    case -1:
                        printf("| # |");
                        break;
                    case -2:
                        printf("| * |");
                        break;
                    case 1:
                        printf("| X |");
                        break;
                    case 2:
                        printf("| W |");
                        break;
                    case 3:
                        printf("| W |");
                        break;
                    case 4:
                        printf("| Y |");
                        break;
                    case 5:
                        printf("| O |");
                        break;
                    case 6:
                        printf("| V |");
                        break;
                    default:
                        printf("|   |");
                        break;
                }
            }
        }
    }

    else
    {
        printf("\nColunas:   1    2    3    4    5    6    7    8    9    10 ");
        for (int i = 0; i < 10; i ++)
        {
            if(i == 9)
            {
                printf("\nLinha 10 ");
            }
            else
            {
                printf("\nLinha 0%d ",i+1);
            }
            for(int j = 0; j < 10; j ++)
            {
                switch(tabuleiro[i][j])
                {
                    case -1:
                        printf("| # |");
                        break;
                    case -2:
                        printf("| * |");
                        break;
                    default:
                        printf("|   |");
                        break;
                }
            }
        }
    }
    printf("\nbarcos restantes: %d\n",8 - acertos.barcos_acertados);
}

struct POSICOES acertou(int tabuleiro[][10], struct POSICOES acertos, int coordenadas[],int vez_atual)
{
    int linha = coordenadas[0];
    int coluna = coordenadas[1];

    if(tabuleiro[linha][coluna] == 0) // caso tiro seja na agua
    {
        printf("\nTiro na água \n");
        tabuleiro[linha][coluna] = -1;
    }
    else
    {
        printf("\nVocê atingiu uma embarcação \n");
        if(tabuleiro[linha][coluna] == 1) //caso seja em um submarino
        {
            printf("\nSubmarino afundado ");
            tabuleiro[linha][coluna] = -2;
            acertos.submarinos ++;
            printf("\n%d\n",acertos.submarinos);
            acertos.barcos_acertados ++;
            printf("\n%d\n",acertos.barcos_acertados);
            if(acertos.submarinos == 3)
            {
                printf("\nÚltimo submarino afundado \n");
            }
        }
        else if(tabuleiro[linha][coluna] == 2) //primeiro navio de duas posicoes
        {
            tabuleiro[linha][coluna] = -2;
            acertos.barco2_1 ++;
            printf("%d",acertos.barco2_1);
            if(acertos.barco2_1 == 2)
            {
                printf("\nEmbarcação de duas posições afundada \n");
                acertos.barcos_acertados ++;
            }
        }
        else if(tabuleiro[linha][coluna] == 3) //segundo navio de duas posicoes
        {
            tabuleiro[linha][coluna] = -2;
            acertos.barco2_2 ++;
            printf("%d",acertos.barco2_2);
            if(acertos.barco2_2 == 2)
            {
                printf("\nEmbarcação de duas posições afundada \n");
                acertos.barcos_acertados ++;
            }
        }
        else if(tabuleiro[linha][coluna] == 4) // barco de tres posicoes
        {
            tabuleiro[linha][coluna] = -2;
            acertos.barco3 ++;
            if(acertos.barco3 == 3)
            {
                printf("\nEmbarcação de tres posições afundada \n");
                acertos.barcos_acertados ++;
            }
        }
        else if(tabuleiro[linha][coluna] == 5) // barco de 4 posicoes
        {
            tabuleiro[linha][coluna] = -2;
            acertos.barco4 ++;
            if(acertos.barco4 == 4)
            {
                printf("\nEmbarcação de quatro posições afundada \n");
                acertos.barcos_acertados ++;
            }
        }
        else if(tabuleiro[linha][coluna] == 6)
        {
            tabuleiro[linha][coluna] = -2;
            acertos.barco5 ++;
            if(acertos.barco5 == 5)
            {
                printf("\nEmbarcação de cinco posições afundada ");
                acertos.barcos_acertados ++;
            }
        }
    }
    system("pause");
    mostrar_tabuleiro(tabuleiro,acertos,vez_atual);
    system("pause");
    return acertos;
}
