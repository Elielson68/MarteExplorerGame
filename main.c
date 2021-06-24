#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void Clear(){
  printf("\033[0;0H\033[2J");
}
void ValidacaoCaminho(int pos1,int pos2){
    if(pos1 == pos2){
      printf("\nSUCESS\n");
    }
    else{
      printf("\nFAILED\n");
    }
}
void IniciarPlato(int plato[10][20]){
  srand( (unsigned)time(NULL) );
  for(int x=0;x<10;x++){
    for(int y=0; y<20; y++){
      if(y<5){
        int posY = rand()%20;
        if(plato[x][posY]==2){
          posY = rand()%20;
        }
        plato[x][posY] = 2;
      }
      if(plato[x][y] != 2){
        plato[x][y] = 0;
      }
    }
  }
}
void PousarRobo(int *robo, int plato[10][20]){
  int x = rand()%10;
  int y = rand()%20;
  while(plato[x][y] == 2){
      x = rand()%10;
      y = rand()%20;
  }
  robo[0] = x;
  robo[1] = y;
}
void MostrarPlato(int *robo, int plato[10][20]){
  for(int x=0;x<10;x++){
    for(int y=0; y<20; y++){
      if(robo[0] == x && robo[1] == y){
        printf("x ");
      }
      else if(plato[x][y] == 1){
        printf("1 ");
      }
      else if(plato[x][y] == 3){
        printf("# ");
      }
      else{
        printf("0 ");
      }
    }
    printf("\n");
  }
}

void Movimentar(char Orientacao[], int passos, int *robo, int plato[10][20]){
  if(passos < 0){
    passos = passos * -1;
    printf("\nPassos: %d\n", passos);
  }
  if(strcmp(Orientacao, "N") == 0 || strcmp(Orientacao, "n") == 0){
    int pontoFinal = robo[0] - passos;
    int posY = robo[1];
    for(int x=10;x>0;x--){
        if(robo[0] == x && robo[0] != pontoFinal){
        if(plato[x-1][posY] == 2){
          plato[x-1][posY] = 3;
          break;
         }
         if(plato[x-1][posY] != 3){
          plato[x][posY] = 1;
          robo[0] -= 1;
         }

        }
    }
    ValidacaoCaminho(robo[0], pontoFinal);
  }
  if(strcmp(Orientacao, "S") == 0 || strcmp(Orientacao, "s") == 0){
    int pontoFinal = robo[0] + passos;
    int posY = robo[1];
    for(int x=0;x<10;x++){
      if(robo[0] == x && robo[0] != pontoFinal){
        if(plato[x+1][posY] == 2){
          plato[x+1][posY] = 3;
          break;
        }
        if(plato[x+1][posY] != 3){
          plato[x][posY] = 1;
          robo[0] += 1;
          robo[0] = robo[0] > 9 ? 9:robo[0]; 
        }
      }
    }
    ValidacaoCaminho(robo[0], pontoFinal);
  }
  if(strcmp(Orientacao, "L") == 0 || strcmp(Orientacao, "l") == 0){
    int pontoFinal = robo[1] + passos;
    int posX = robo[0];
    for(int y=0; y<20; y++){
      if(robo[1] == y && robo[1] != pontoFinal){
        if(plato[posX][y+1] == 2){
          plato[posX][y+1] = 3;        
          break;
        }
        if(plato[posX][y+1] != 3){
          plato[posX][y] = 1;
          robo[1] += 1; 
          robo[1] = robo[1] > 19 ? 19:robo[1];
        }
      }
    }
    ValidacaoCaminho(robo[1], pontoFinal);
  }
  if(strcmp(Orientacao, "O") == 0 ||strcmp(Orientacao, "o") == 0 ){
    int pontoFinal = robo[1] - passos;
    int posX = robo[0];
    for(int y=20; y>0; y--){
      if(robo[1] == y && robo[1] != pontoFinal){
        if(plato[posX][y-1] == 2){
          plato[posX][y-1] = 3;
          break;
        }
        if(plato[posX][y-1] != 3){
          plato[posX][y] = 1;
          robo[1] -= 1;
        }

      }
    }
    ValidacaoCaminho(robo[1], pontoFinal);
  }
  if((strcmp(Orientacao, "0") == 0 || strcmp(Orientacao, "o") == 0) && passos==0){
    MostrarPlato(robo, plato);
  }
}

int main(void) {
  char pergunta;
  int *robo = (int *) calloc(2,sizeof(int));
  int plato[10][20];
  IniciarPlato(plato);
  PousarRobo(robo, plato);
  int passos;
  Clear();
  MostrarPlato(robo, plato);
  printf("\nPara a movimentação do robô, utilizar [(orientação) (quantidade de passos)] para o locomover, onde:\nOrientação:\n N - Norte\n S - Sul\n L - Leste\n O - Oeste\nQuantidade de passos: um número inteiro positivo.");
  while(1){
    printf("\nComando: ");
    scanf("[%c %d]", &pergunta, &passos);
    scanf("%*c");
    Clear();
    Movimentar(&pergunta, passos, robo, plato);
    MostrarPlato(robo, plato);
  }
  return 0;
}