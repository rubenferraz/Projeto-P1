/*
 * Nome, numero de aluno, e turno pratico dos elementos do grupo:
 * Aluno 1: a45763 - PL4 - Ruben Jorge Sampaio
 * Aluno 2: a45590 - PL3 - Rúben Duarte Ferraz
 */

/*Nao pode incluir headers adicionais*/
#include <stdio.h>
#define N 3


void inicializaGrelha(char grid[N][N])
{
  /* Implementar */
  /* E' obrigatorio usar ciclos for.
   * Inicializacao manual resulta em penalizacao */
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      grid[i][j] = ' ';
    }
  }
}


void imprimeGrelha(char grid[N][N])
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      // Imprime o Simbolo do espaco currente
      printf(" %c ", grid[i][j]);

      // Adiciona um Separador de Colunas caso nao seja a ultima Coluna
      if (j != N - 1) {
        printf("|");
      }
    }
    printf("\n");

    // Adiciona um Separador de Linhas caso nao seja a ultima Linha
    if (i != N - 1)
    {
      printf("--- --- --- \n");
    }
  }
}


int jogada(char grid[N][N], int x, int y, int jogador)
{
	if ((x < 0 || x > 2) || (y < 0 || y > 2)) {
    // Valores Invalidos
		return 1;
	}
	else if (grid[x][y] == 'X' || grid[x][y] == 'O')
	{
    // Retorna caso o Espaco escolhido nao esteja vazio
		return 2;
	}
	else
	{
    // Adicionar Jogada ao array "grid"
    if (jogador == 0)
    {
      grid[x][y] = 'O';
    } else {
      grid[x][y] = 'X';
    }

    // Retorna se a jogada e' Possivel e foi Executada
		return 0;
	}
}


int tresEmLinha(char grid[N][N], int x, int y)
{
  if (grid[x][y] == ' ') { // Verifica se o lugar que foi escolhido esta vazio
    return -1;
  } else if (grid[x][0] == grid[x][1] && grid[x][0] == grid[x][2]) // Verifica tres em linha na Linha
  {
    return 1;
  } else if (grid[0][y] == grid[1][y] && grid[0][y] == grid[2][y]) // Verifica tres em linha na Coluna
  {
    return 1;
  } else if (grid[1][1] != ' ' && (x == y || (x == 2 && y == 0) || (x == 0 && y == 2))) // Verifica se o Espaço escolhido esta numa Diagonal
  {
    if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2]) // Verifica tres em linha na Diagonal Principal
    {
      return 1;
    } else if (grid[2][0] == grid[1][1] && grid[2][0] == grid[0][2]) // Verifica tres em linha na Diagonal Principal
    {
      return 1;
    }
  }


  return 0;
}


int main(void)
{
  char repeatGame = 'N';


  do {
    int jogador = 0;
    char grid[N][N];
    int wrongAnswer = 0;


    // Inicializa a Grelha
    inicializaGrelha(grid);


    for (int round = 0; round < N*N; round++)
    {
      int x;
      int y;

      do {
        // Imprime a Grelha pela Primeira Vez
        printf("\e[1;1H\e[2J");
        imprimeGrelha(grid);
        printf("\n");

        // Adquirindo as Cordenadas da Jogada
        printf("-------------------------\n");
        printf("É o seu turno Jogador %c:\n", jogador == 0 ? 'O' : 'X');
        printf("-------------------------\n");

        (wrongAnswer)
          ? printf("Por favor coloque as cordenadas corretamente:\n----------------------------------------------\n")
          : printf("\n");

        printf("Linha: ");
        scanf("%d", &x);
        printf("Coluna: ");
        scanf("%d", &y);
        printf("\n");

        wrongAnswer = (jogada(grid, x, y, jogador) != 0)
          ? 1 : 0;

      } while (wrongAnswer);
      printf("\n\n");


      // Imprime a Grelha do Jogo
      printf("\e[1;1H\e[2J");
      imprimeGrelha(grid);
      printf("\n");


      // Verifica se Houve Tres em Linha
      if (tresEmLinha(grid, x , y) == 1)
      {
        printf("O Jogador %c é o Vencedor.\n", jogador == 0 ? 'O' : 'X');
        break;
      } else if (tresEmLinha(grid, x , y) == 0) {
        if (round == N*N - 1)
        {
          printf("O Jogo ficou Empatado.\n");
          break;
        }
      } else if (tresEmLinha(grid, x , y) == -1) {
        printf("O Espaço escolhido está vazio.\n");
      }


      // Troca de Jogador
      jogador = jogador == 0 ? 1 : 0;
    }


    repeatGame = 'N';
    printf("-------------------------\n");
    printf("Se Deseja Repetir o Jogo prima Y? (Y/N): ");
    scanf(" %c", &repeatGame);
    printf("-------------------------\n");
  } while (repeatGame == 'y' || repeatGame == 'Y');


  return 0;
}
