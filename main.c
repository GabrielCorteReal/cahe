
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// define o tamanho da MP(BITS)
const int MP = 32;

int main()
{
  srand(time(NULL));
  int teste2 = 0;
  int teste = 0;
  float hope = 0;
  int conj, tag, ass, palv, lmc, x, esrt, sub, tagf, conjf, aux, auxx, auxxx, PosCh, EndR, EndW, HitC, MissC, EscMP, op, quncon, j, dor, sofrimento;
  register int i;
  char Caux;
  i = 0;
  HitC = 0;
  MissC = 0;
  EndR = 0;
  EndW = 0;
  EscMP = 0;
  quncon = 0;
  dor = 0;
  sofrimento = 0;
  ///// int *cache;
  FILE *fp;
  aux = 0;
  // Meditation-------------------------------------------------------------------------------
  printf("linhas da Memoria cache\n");
  scanf("%d", &lmc);
  printf("assosiatividade por conjunto\n");
  scanf("%d", &ass);
  printf("tamanho da palvara em bits\n");
  scanf("%d", &palv);
  while (ass > lmc)
  {
    printf("assosiatividade por conjunto não pode ser maior q o numero de linhas da cache\n");
    printf("assosiatividade por conjunto em bits\n");
    scanf("%d", &ass);
  }
  int *cache = (int *)malloc(sizeof(int) * (lmc));
  int *Dbit = (int *)malloc(sizeof(int) * (lmc));
  int *lru = (int *)malloc(sizeof(int) * (lmc));
  for (i = 0; i < lmc; i++)
  {
    cache[i] = 0;
    Dbit[i] = 0;
    lru[i] = 0;
  }

  conj = (pontesificador(lmc) - pontesificador(ass));
  tag = MP - (conj + palv);
  if (tag<0)
  {
    tag=0;
  }
  
  printf("politica de escrita\n");
  printf("0 - write-through  1 - write-back\n");
  scanf(" %d", &esrt);
  printf("politica de subititiciao\n");
  printf("0 - LRU  1 - Aleatória\n");
  scanf(" %d", &sub);
  printf("Tamano da MP: %d \n", MP);
  printf("numero de linhas da memora cache: %d \n", lmc);
  printf("assosiatividae: %d \n", ass);
  printf("Tamano da palvara: %d \n", palv);
  printf("Tamano do conjunto: %d \n", conj);
  printf("Tamano da tag: %d \n", tag);
  printf("politica de escrita %d \n", esrt);
  printf("politica de subititiciao %d \n", sub);
  printf("confirmar?\n");
  printf("1-sim 2-nao\n");
  scanf(" %d", &aux);
  if (aux == 2)
  {
    return 0;
  }
  if ((fp = fopen("MP.txt", "r")) == NULL)
  {
    printf("FALHA ao abrir o aqruivo\n");
    exit(1);
  }
  // Meditation-----------------------------------------------------------------------------
  // Flèche---------------------------------------------------------------------------------
  // tag----------------------
  auxxx = 0;
  do
  {
    teste2++;
    i = tag;
    tagf = 0;
    teste = 0;
    while (i >= 4)
    {
      teste = fgetc(fp);
      tagf = hexdecimaccao(teste) + tagf;
      ;
      i = i - 4;
    }
    if (i != 0)
    {
      aux = fgetc(fp);
      auxx = hexdecimaccao(aux);
      tagf = breakthem(auxx, i) + tagf;
    }
    printf("tagf:%d\n", tagf);
    // tag----------------------
    // conj---------------------
    conjf = 0;
    if (i != 0)
    {
      conjf = aindatemesperaca(auxx, i) + conjf;
    }
    auxxx = conj;
    auxxx = auxxx - i;
    while (auxxx >= 4)
    {
      conjf = hexdecimaccao(fgetc(fp)) + conjf;
      auxxx = auxxx - 4;
    }
    if (auxxx != 0)
    {
      aux = fgetc(fp);
      auxx = hexdecimaccao(aux);
      conjf = breakthem(auxx, auxxx) + conjf;
    }
    printf("conjf:%d\n", conjf);
    do
    {
      Caux = fgetc(fp);
      if (Caux == 'W')
      {
        break;
      }

    } while (Caux != 'R');
    op = Caux;
    if (op == 'R')
    {
      EndR++;
    }
    else
    {
      EndW++;
    }
    printf("op: %c\n", op);
    Caux = fgetc(fp);

    // conj-----------------------
    i = conjf;
    aux = pow(2, conj);
    while (i > 0)
    {
      i = i - aux;
    }
    if (i == 0)
    {
      i = i - aux;
    }
    PosCh = i = i + aux;
    auxx = 0;
    auxxx = 0;
    while (i < lmc)
    {

      if (cache[i] == tagf)
      {
        HitC++;
        auxx++;
        if (op == 'W')
        {
          if (esrt == 0)
          {
            EscMP++;
          }
          if (esrt == 1)
          {
            Dbit[i] = 1;
          }
        }
        teste = PosCh;
        do
        {
          lru[teste] = 0;
          teste = aux + teste;
        } while (teste < lmc);
        lru[i] = 1;

        break;
      }
      else if (cache[i] == 0)
      {
        auxx++;
        auxxx++;
        cache[i] = tagf;
        if (op == 'W')
        {
          if (esrt == 0)
          {
            EscMP++;
          }
          else if (esrt == 1)
          {
            Dbit[i] = 1;
          }
        }
        break;
      }
      
      i = aux + i;
    }
    if (auxxx == 0)
    {
      i = PosCh;
      do
      {

        i = aux + i;
      } while (i < lmc);
    }
    if (auxx == 0) // aq
    {
      MissC++;
    }

    if (sub == 1 && auxx == 0)
    {
      auxx = 0;
      i = PosCh;
      quncon = 0;
      do
      {
        i = aux + i;
        quncon++;
      } while (i < lmc);

      auxx = rand() % quncon + 1;
      i = PosCh;
      j = 1;
      while (j != auxx)
      {
        i = aux + i;
        j++;
      }
      printf("one ele subistui %d\n", i);
      printf("por %d\n", tagf);
      cache[i] = tagf;
      if (op == 'W')
      {
        if (esrt == 0)
        {
          EscMP++;
        }
      }
      if (Dbit[i] == 1)
      {
        EscMP++;
        if (op == 'W')
        {
          Dbit[i] = 1;
        }
        else
        {
          Dbit[i] = 0;
        }
      }
      else if (op == 'R')
      {
        Dbit[i] = 0;
      }
    }
    else if (sub == 0 && auxx == 0)
    {
      auxx = 0;
      i = PosCh;
      do
      {
        if (lru[i] == 0)
        {
          cache[i] = tagf;
          auxx++;
          teste = PosCh;
          do
          {
            lru[teste] = 0;
            teste = aux + teste;
          } while (teste < lmc);
          lru[i] = 1;
          break;
        }
        lru[i] = 0;
        i = aux + i;
      } while (i < lmc);
      if (auxx == 0)
      {
        printf("//////////////////////////////////////////////////////////////nao subt\n");
      }
      if (op == 'W')
      {
        if (esrt == 0)
        {
          EscMP++;
        }
      }
      if (Dbit[i] == 1)
      {
        EscMP++;
        if (op == 'W')
        {
          Dbit[i] = 1;
        }
        else
        {
          Dbit[i] = 0;
        }
      }
      else if (op == 'R')
      {
        Dbit[i] = 0;
      }
    }

  } while (Caux != EOF);
  // aux-n mecher super ocupada
  // auxx-falg para hit/miss
  // auxxx flag de escrita na cah vazi
  aux = pow(2, palv);
  printf("R: %d\n", EndR);
  printf("W: %d\n", EndW);
  printf("toatl: %d\n", EndR + EndW);
  printf("hit: %d\n", HitC);
  printf("miss: %d\n", MissC);
  printf("EsMP %d\n", EscMP);
  printf("Tamanho da mc %d\n", aux * lmc);
  // arcrt/ender
  hope = EndR + EndW;
  hope = HitC / hope;
  printf("taxa de acero %f\n", hope * 100);
  // printf("0:%d d:%d lru:%d\n", cache[0], Dbit[0], lru[0]);
  // printf("1:%d d:%d lru:%d\n", cache[1], Dbit[1], lru[1]);
  // printf("2:%d d:%d lru:%d\n", cache[2], Dbit[2], lru[2]);
  // printf("3:%d d:%d lru:%d\n", cache[3], Dbit[3], lru[3]);
  // printf("4:%d d:%d lru:%d\n", cache[4], Dbit[4], lru[4]);
  // printf("5:%d d:%d lru:%d\n", cache[5], Dbit[5], lru[5]);
  // printf("6:%d d:%d lru:%d\n", cache[6], Dbit[6], lru[6]);
  // printf("7:%d d:%d lru:%d\n", cache[7], Dbit[7], lru[7]);
  //  printf("teste: %d\n", teste);
  //  printf("teste2: %d\n", teste2);
  fclose(fp);
}
int pontesificador(int x)
{
  int aux = 0;
  while (x != 1)
  {
    x = x / 2;
    aux++;
  }
  return aux;
}
int hexdecimaccao(int x)
{
  if (x > 57)
  {
    x = x - 'W';
    return x;
  }
  x = x - '0';
  return x;
}
int breakthem(int x, int y)
{
  int aux = 4;
  aux = aux - y;
  x = x >> aux;
  return x;
}
int cleavethem(int x, int y)
{

  x = x << 28;
  x = x << y;
  x = x >> 28 + y;
  printf("1x:%d\n", x);
  if (x < 0)
  {
    x = -1 * x;
  }
  printf("2x:%d\n", x);

  return x;
}
int aindatemesperaca(int num, int qnt)
{
  int aux = 0x0F;
  num = num << qnt;
  num = num & aux;
  num = num >> qnt;
  return num;
}
