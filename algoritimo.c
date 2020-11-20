#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct snotas
{

    float nota[5];

} Notas;

typedef struct sQuesitos
{

    Notas Bateria;
    Notas Sambaenredo;
    Notas Harmonia;
    Notas Evolucao;
    Notas Enredo;
    Notas Conjunto;
    Notas AlegoriaseAderecos;
    Notas Fantasias;
    Notas ComissaodeFrente ;
    Notas MestreSalaPortaBandeira;
    Notas Ousadia;
    Notas Simpatia;
    Notas SambanoPe;

} Quesitos;

typedef struct sescola
{

    char nome[21];
    char responsavel[21];
    Quesitos que;

} Escola;


float somanotaquesito(float nota[],int tamanho,int i)           //Função recursiva que soma as  notas de cada quesito digitadas pelo usuario
{
    if (i < tamanho)
    {
        return nota[i] + somanotaquesito(nota,tamanho,i+1);
    }
    else
    {
        return 0;
    }

}

float calcula(float pegaQ[],int tamanho,int i)  // Função recursiva feita para calcular a nota final de cada escola
{
    if (i < tamanho)
    {
        return pegaQ[i] + calcula(pegaQ,tamanho,i+1);
    }
    else
    {
        return 0;
    }
}

float verificanota(float nota[],int i)     //função que verifica se a nota digitada pelo usuario esta entre 7 e 10
{

    while (nota[i] <= 6.9 || nota[i] >= 10.1)
    {
        printf("digite a nota novamente:\t\n"); //verificar se nota digitada é valida
        fflush(stdin);
        scanf("%f",&nota[i]);
    }

    return *nota;
}

float retiranotas(float nota[],int i) // Função que retira a maior e a menor nota de cada quesito
{
    float retorna,menor;
    static float maior;

    if(i == 0)
    {
        menor = nota[i];
        maior = 0;
    }

    if(nota[i] > maior)
    {
        maior = nota[i];

    }
    if(nota[i] < menor)
    {
        menor = nota[i];
    }

    retorna = (maior + menor);

    return retorna;

}

int verificar(char cadastro[50])   //Função para verficar se o nome da escola cadastrada tem mais de 8 caracteres
{

    int count=0;
    int j;

    for (j = 0 ; j < 50 ; j++)
    {
        if (cadastro[j] != '\0')
        {
            count++;
        }
        else
        {
            break;
        }

    }
    if (count>8)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

int menu ()     //Função do menu de opções
{
    int Menu;
    printf ("***MENU***:\n");
    printf ("\n\n");
    printf ("Sair do progrma [1]: \n");
    printf ("\n");
    printf ("Cadastro uma Escola [2]: \n");
    printf ("\n");
    printf ("Buscar Dados de uma Escola: [3] \n");
    printf ("\n");
    printf ("Usar Funcao Recursiva para Calcular Nota final das Escolas: [4] \n");
    printf ("\n");
    printf ("Exibir Escolas Cadastradas: [5] \n");
    printf ("\n");
    printf ("Mostrar as Escolas Campeas: [6] \n");
    printf ("\n");
    printf ("Exibir Escolas Rebaixadas: [7] \n");
    printf ("\n");
    printf ("Gravar o Cadastro das Escolas de Samba: [8] \n");
    printf ("\n");
    printf ("Carregar o Cadastro das Escolas de Samba.: [9] \n");
    printf ("\n\n");

}

int main ()
{

    int Menu,i,erro,z=0,x,j=0,tam,opc,pos,pos2,posm,posm2,aux = 0,p=0;
    char pesq[50];
    float **matriz,soma,recebe,nota[5],maior,maior2,menor,menor2,**mediaEscolas,*resultado;
    float *final,result,pegaQ[13];
    Escola *cadastro;
    FILE* f;

    printf ("***QUESITOS A SEREM JULGADOS***\n");

    printf ("1 - Bateria               2 - Samba-Enredo\n");
    printf ("3 - Harmonia              4 - Evolução\n");
    printf ("5 - Enredo                6 - Conjunto\n");
    printf ("7 - Fantasias             8 - Alegorias e Adereços \n");
    printf ("9 - Comissão de Frente    10 - Mestre-Sala e Porta-Bandeira\n");
    printf ("11 - Ousadia     12 - Simpatia    13 - Samba no Pe\n");
    printf ("\n\n");

    printf ("Deseja abrir o menu de opcoes 1 = Sim  2 = Nao\n");   //Dá a opção ao usuario de entrar ou sair do programa
    scanf ("%d",&opc);

    if (opc == 1)
    {
        menu();
        scanf ("%d",&Menu);

    }
    else
    {
        printf ("Programa encerrado\n");
    }


    if (Menu == 1 || Menu == 2 || Menu == 3 || Menu == 4 || Menu == 5 || Menu == 6 || Menu == 7 || Menu == 8 || Menu == 9) //Opções do menu
    {
        printf ("Comando Aceito\n");
    }
    else
    {
        printf ("Comando nao aceito\n");
    }

    system ("cls");

    while (opc == 1) // Um while que controla quando o switch deve ser encerrado
    {
        switch (Menu)
        {

        case  1:                           // Opção 1 encerra o programa

            if (Menu == 1)
            {
                printf ("FIM DO PROGRAMA\n");
                opc = 0;
            }
            break;


        case 2:

            soma = 0;                                    // Variavel soma utilizda para somar a nota de cada quesito

            if (Menu == 2)
            {
                printf ("**CADASTRO DE ESCOLA SELECIONADO**\n");
                printf ("\n\n");

                x = 0;

                if ( z == 0 )                // A primeria vez que a opção 2 é selecionada é aberto um if que contem varias alocações dinamicas dentro dele, que cria vetores e matrizes que serão usadas posteriormente
                {
                    printf ("Digite quantas escolas deseja cadastrar\n"); // Pergunta ao usuario quantas escolas serão cadastradas
                    scanf ("%d",&tam);
                    matriz = (float **) malloc( tam*sizeof(float*) );         // cria uma matriz para armazenar as as 5 notas atribuidas pelos jurados e exibi-las na opção 5

                    if ( matriz == NULL )                                        // Verifica se foi possivel alocar memoria
                    {
                        printf("Não foi possível alocar memória.\n");
                        exit(1);
                    }

                    for(i = 0; i < tam ; i++)
                    {
                        matriz[i] = (float*) malloc(65*sizeof(float));
                    }

                    mediaEscolas = (float **) malloc( tam*sizeof(float*) );

                    if ( mediaEscolas == NULL )
                    {

                        printf("Não foi possível alocar memória.\n");
                        exit(1);
                    }

                    for(i = 0; i < tam ; i++)
                    {

                        mediaEscolas[i] = (float*) malloc(13*sizeof(float));    // Cria um vetor para armazenar a soma das 3 notas de cada quesito e exibi-las posteriormente na opção 5
                    }

                    for (i = 0 ; i < tam ; i++)
                    {
                        final = (float*) malloc(tam*sizeof (float));           // Cria um vetor responsavel por armazenar a nota final de cada escolas e a usa para comparar as notas na opção 6 e 7. Esse vetor age de formar indepedente a função recursiva

                        if ( final == NULL)
                        {
                            printf ("Erro\n");
                            exit(1);
                        }
                    }

                    for (i = 0 ; i < tam ; i++)
                    {
                        cadastro = (Escola*) malloc(tam*sizeof (Escola));     // Vetor de cadastro para armazenar a quantidade de escolas digitadas pelo usuario

                        if ( final == NULL)
                        {
                            printf ("Erro\n");
                            exit(1);
                        }
                    }

                    for (i = 0 ; i < tam ; i++)
                    {
                        resultado = (float*) malloc(tam*sizeof (float));

                        if ( resultado == NULL)
                        {
                            printf ("Erro\n");
                            exit(1);
                        }
                    }
                }

                if (j == tam)    // J é responsavel por controlar o numero de cadastros feitos, quando ele é igual ao numero de escolas o programa sempre volta ao menu impedindo assim novos cadastros
                {
                    printf ("impossivel cadastrar mais escolas\n");
                    printf ("Vc so pode cadastrar %d escolas como havia informado\n",tam);

                    printf ("\n\n");
                    menu(); // exibindo menu
                    scanf ("%d",&Menu);
                    break;
                }

                printf ("Digite o nome da escola %d\n", j+1);
                fflush(stdin);
                gets (cadastro[j].nome);

                printf ("Digite o responsavel pela escola\n",j+1);
                fflush (stdin);
                gets (cadastro[j].responsavel);

                if(verificar(cadastro[j].nome) == 1)        // Chama a função que verifica quantas letras tem o nome digitado
                {

                    printf("nome aceito\n");

                }
                else
                {

                    printf("nao aceito!\n");

                    while(verificar(cadastro[j].nome)==0)
                    {
                        printf ("Digite o nome da escola %d novamente\n", j+1);
                        fflush(stdin);
                        gets (cadastro[j].nome);
                    }
                }

                soma = 0;
                p = 0;
                for (i = 0 ; i < 5 ; i++)    // Pega do usuario a nota do quesito Bateria
                {

                    printf ("Digite a nota %d no quesito Bateria \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);   	        // Verifica se a nota esta entre 7 e 10
                    matriz[j][i] = nota[i];              // matriz recebe as notas para posteriormente exibi-las na opção 5
                    cadastro[j].que.Bateria.nota[i] = nota[i];  // Armazena a nota na estrutura
                    recebe = retiranotas(nota,i);               // recebe as notas retiradas na função retiranotas
                    soma = somanotaquesito(nota,5,0);   // Soma manda as notas digitadas pra função recursiva que realiza a soma


                }
                soma = soma - recebe;                         // Soma recebe a soma das 5 notas e retiras as 2 retiradas(a menor e a maior)
                pegaQ[p] = soma;                              // Vetor que pega a soma das notas do quesito / responsavel pela função recursiva do item 4
                mediaEscolas[j][x] = soma;	                  // Matriz que exibira a media dos quesitos no item 5
                final[j] = soma;                              // Vetor que recebe a nota final da cada quesito e faz a soma/ esse vetor é utilizddo nas opções 6 e 7
                p++;                                          // p é responsavel por incrementar o vetor PegaQ que recebe a soma da notas dos quesitos
                x++;                                          // x incrementa a posição da matriz mediaEscolas
                soma = 0;


                // Daqui em diante é repetido o mesmo processo para cada um dos treze quesitos
                for (i = 0,aux = 5 ; i < 5, aux < 10 ; i++, aux++)      // posição aux controla exclusivamente as linhas da matriz que armazena 65 notas
                {
                    printf ("Digite a nota  %d no quesito Samba Enredo \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);
                    matriz[j][aux] = nota[i];
                    cadastro[j].que.Sambaenredo.nota[i]	 = nota[i];
                    recebe = retiranotas(nota,i);
                    soma = somanotaquesito(nota,5,0);
                }

                soma = soma - recebe;
                pegaQ[p] = soma;
                mediaEscolas [j][x] = soma;
                final[j] = final[j] + soma;
                p++;
                soma = 0;
                x++;

                for (i = 0,aux = 10 ; i < 5, aux < 15 ; i++, aux++)
                {

                    printf ("Digite a nota  %d no quesito Harmonia \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);
                    matriz[j][aux] = nota[i];
                    cadastro[j].que.Harmonia.nota[i]	 = nota[i];
                    recebe = retiranotas(nota,i);
                    soma = somanotaquesito(nota,5,0);


                }
                soma = soma - recebe;
                pegaQ[p] = soma;
                mediaEscolas[j][x] = soma;
                final[j] = final[j] + soma;

                p++;
                soma = 0;

                x++;

                for (i = 0,aux = 15 ; i < 5, aux < 20 ; i++, aux++)
                {

                    printf ("Digite a nota  %d no quesito Evolucao \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);
                    matriz[j][aux] = nota[i];
                    cadastro[j].que.Evolucao.nota[i]	 = nota[i];
                    recebe = retiranotas(nota,i);
                    soma = somanotaquesito(nota,5,0);


                }
                soma = soma - recebe;
                pegaQ[p] = soma;
                mediaEscolas[j][x] = soma;
                final[j] = final[j] + soma;

                p++;
                soma = 0;

                x++;

                for (i = 0,aux = 20 ; i < 5, aux < 25 ; i++, aux++)
                {

                    printf ("Digite a nota %d no quesito Enredo \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);
                    matriz[j][aux] = nota[i];
                    cadastro[j].que.Enredo.nota[i]	 = nota[i];
                    recebe = retiranotas(nota,i);
                    soma = somanotaquesito(nota,5,0);


                }
                soma = soma - recebe;
                pegaQ[p] = soma;
                mediaEscolas[j][x] = soma;
                final[j] = final[j] + soma;

                p++;
                soma = 0;
                x++;

                for (i = 0,aux = 25 ; i < 5, aux < 30 ; i++, aux++)
                {

                    printf ("Digite a nota %d no quesito Conjunto \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);
                    matriz[j][aux] = nota[i];
                    cadastro[j].que.Conjunto.nota[i]	 = nota[i];
                    recebe = retiranotas(nota,i);
                    soma = somanotaquesito(nota,5,0);

                }
                soma = soma - recebe;
                pegaQ[p] = soma;
                mediaEscolas[j][x] = soma;
                final[j] = final[j] + soma;

                p++;
                soma = 0;

                x++;

                for (i = 0,aux = 30 ; i < 5, aux < 35 ; i++, aux++)
                {

                    printf ("Digite a nota %d no quesito Alegorias e Aderecos \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);
                    matriz[j][aux] = nota[i];
                    cadastro[j].que.AlegoriaseAderecos.nota[i]	 = nota[i];
                    recebe = retiranotas(nota,i);
                    soma = somanotaquesito(nota,5,0);

                }
                soma = soma - recebe;
                pegaQ[p] = soma;
                mediaEscolas[j][x] = soma;
                final[j] = final[j] + soma;

                p++;
                soma = 0;

                x++;

                for (i = 0,aux = 35 ; i < 5, aux < 40 ; i++, aux++)
                {

                    printf ("Digite a nota  %d no quesito Fantasias \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);
                    matriz[j][aux] = nota[i];
                    cadastro[j].que.Fantasias.nota[i]	 = nota[i];
                    recebe = retiranotas(nota,i);
                    soma = somanotaquesito(nota,5,0);

                }
                soma = soma - recebe;
                pegaQ[p] = soma;
                mediaEscolas[j][x] = soma;
                final[j] = final[j] + soma;

                p++;
                soma = 0;

                x++;

                for (i = 0,aux = 40 ; i < 5, aux < 45 ; i++, aux++)
                {

                    printf ("Digite a nota  %d no quesito Comissao de Frente \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);
                    matriz[j][aux] = nota[i];
                    cadastro[j].que.ComissaodeFrente.nota[i]	 = nota[i];
                    recebe = retiranotas(nota,i);
                    soma = somanotaquesito(nota,5,0);

                }
                soma = soma - recebe;
                pegaQ[p] = soma;
                mediaEscolas[j][x] = soma;
                final[j] = final[j] + soma;

                p++;
                soma = 0;
                x++;

                for (i = 0,aux = 45 ; i < 5, aux < 50 ; i++, aux++)
                {

                    printf ("Digite a nota  %d no quesito Mestre Sala e Porta Bandeira \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);
                    matriz[j][aux] = nota[i];
                    cadastro[j].que.MestreSalaPortaBandeira.nota[i]	 = nota[i];
                    recebe = retiranotas(nota,i);
                    soma = somanotaquesito(nota,5,0);

                }
                soma = soma - recebe;
                pegaQ[p] = soma;
                mediaEscolas[j][x] = soma;
                final[j] = final[j] + soma;

                p++;
                soma = 0;

                x++;

                for (i = 0,aux = 50 ; i < 5, aux < 55 ; i++, aux++)
                {

                    printf ("Digite a nota no %d no quesito  Ousadia \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);
                    matriz[j][aux] = nota[i];
                    cadastro[j].que.Ousadia.nota[i]	 = nota[i];
                    recebe = retiranotas(nota,i);
                    soma = somanotaquesito(nota,5,0);


                }
                soma = soma - recebe;
                pegaQ[p] = soma;
                mediaEscolas[j][x] = soma;
                final[j] = final[j] + soma;

                p++;
                soma = 0;


                x++;

                for (i = 0,aux = 55 ; i < 5, aux < 60 ; i++, aux++)
                {

                    printf ("Digite a nota %d no quesito Simpatia  \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);
                    matriz[j][aux] = nota[i];
                    cadastro[j].que.Simpatia.nota[i]	 = nota[i];
                    recebe = retiranotas(nota,i);
                    soma = somanotaquesito(nota,5,0);

                }
                soma = soma - recebe;
                pegaQ[p] = soma;
                mediaEscolas[j][x] = soma;
                final[j] = final[j] + soma;

                p++;
                soma = 0;

                x++;

                for (i = 0,aux = 60 ; i < 5, aux < 65 ; i++, aux++)
                {

                    printf ("Digite a nota %d no quesito Samba no Pe \n",i+1);
                    scanf ("%f",&nota[i]);

                    verificanota(nota,i);
                    matriz[j][aux] = nota[i];
                    cadastro[j].que.SambanoPe.nota[i]	 = nota[i];
                    recebe = retiranotas(nota,i);
                    soma = somanotaquesito(nota,5,0);


                }
                soma = soma - recebe;
                pegaQ[p] = soma;
                mediaEscolas[j][x] = soma;
                final[j] = final[j] + soma;


                for (p = 0 ; p < 13 ; p++)        // Função recursiva que ira somar as notas de cada quesito afim de obter a nota final da escola
                {
                    resultado[j] = calcula(pegaQ,13,0);
                }
                
                z++; // incrementa z, que na segunda vez que o usuario entrar na opção 2 não mais perguntara quantas esscolas ele deseja cadastrar
                j++;

                printf ("Deseja voltar ao menu? 1-SIM 2-NAO");   // Pergunta ao usuario se ele deseja voltar ao menu principal
                scanf("%d",&opc);

                if (opc == 1)
                {
                    system("cls"); // lipando tela
                    menu(); // exibindo menu
                    scanf ("%d",&Menu); // lendo e armazenando na variavel menu
                }
                else
                {
                    printf ("Fim do Programa");
                }


            }

            break;

        case 3:

            if (Menu == 3)
            {

                printf ("***Pesquisa de escola selecionada***");
                printf ("\n\n");

                printf ("Digite o nome da escola a ser pesquisada\n");
                fflush (stdin);
                gets (pesq);

                for (i = 0 ; i < tam ; i ++)      // A função strcmp compara se o nome digitado em pesq esta armazanado se sim exibe os dados
                {
                    if (strcmp (cadastro[i].nome,pesq) == 0)
                    {
                        printf ("***DADOS DA ESCOLA***\n");
                        printf ("\n\n");
                        printf ("Nome da Escola :%s -  Responsavel :%s\n",cadastro[i].nome,cadastro[i].responsavel);
                        printf ("Nota Final da Escola: %f\n",final[i]);
                        printf ("\n");
                        break;
                    }
                    else
                    {
                        printf ("Escola nao cadastrada\n");
                        break;
                    }
                }

                printf ("Deseja voltar ao menu? 1-SIM 2-NAO");
                scanf("%d",&opc);

                if (opc == 1)
                {
                    system("cls"); // lipando tela
                    menu(); // exibindo menu
                    scanf ("%d",&Menu); // lendo e armazenando na variavel menu
                }
                else
                {
                    printf ("Fim do Programa");
                }

            }
            break;

        case 4:

            if (Menu == 4)
            {
                printf ("EXIBINDO NOTAS FUNCAO RECURSIVA\n");    // Chama a função recursiva e exibe as notas
                printf ("\n\n");

                for (p = 0 ; p < tam ; p++)
                {
                    printf ("Escola: %s - Responsavel: %s\n",cadastro[p].nome,cadastro[p].responsavel);
                    printf ("Nota Final: %f\n",resultado[p]);
                }


                printf ("Deseja voltar ao menu? 1-SIM 2-NAO");
                scanf("%d",&opc);

                if (opc == 1)
                {
                    system("cls"); // lipando tela
                    menu(); // exibindo menu
                    scanf ("%d",&Menu); // lendo e armazenando na variavel menu
                }
                else
                {
                    printf ("Fim do Programa");
                }
            }

            break;

        case 5:

            if (Menu == 5)
            {
                printf ("***Exibir Todas as Escolas Cadastradas***");     // Exibe todas as escolas cadastradas
                printf ("\n\n");
                for (j = 0 ; j < tam ; j++)
                {
                    printf ("Nome da Escola %s - Nome do responsavel %s\n",cadastro[j].nome,cadastro[j].responsavel);   //Nome da escola e responsavel
                    printf ("\n");

                    int y = 0;                                               // y é responsavel por controlar a linha da matriz indo de 0 a 12
                    for (i = 0 ; i < 5; i++)                                // i vai de 0 a 64 correspondente ao numero de  notas
                    {
                        printf ("Notas por quesito Bateria: %f\n",matriz[j][i]);     //Aqui são exibidas notas por quesito que foram armazendas na matriz e a nota final armazenada na matriz mediaEscolas
                    }
                    printf ("Nota final Bateria: %f \n",mediaEscolas[j][y]);
                    y = 1;

                    for (i = 5 ; i < 10; i++)
                    {
                        printf ("Notas por quesito Samba-Enredo: %f\n",matriz[j][i]);
                    }

                    printf ("Nota final Samba Enredo: %f \n",mediaEscolas[j][y]);

                    y = 2;
                    for (i = 10 ; i < 15; i++)
                    {
                        printf ("Notas por quesito Harmonia: %f\n",matriz[j][i]);
                    }
                    printf ("Nota final Harmonia: %f \n",mediaEscolas[j][y]);

                    y = 3;
                    for (i = 15 ; i < 20; i++)
                    {
                        printf ("Notas por quesito Evolucao: %f\n",matriz[j][i]);
                    }
                    printf ("Nota final Evolucao: %f \n",mediaEscolas[j][y]);

                    y = 4;
                    for (i = 20 ; i < 25; i++)
                    {
                        printf ("Notas por quesito Enredo: %f\n",matriz[j][i]);
                    }
                    printf ("Nota final Enredo: %f \n",mediaEscolas[j][y]);

                    y = 5;
                    for (i = 25 ; i < 30; i++)
                    {
                        printf ("Notas por quesito Conjunto: %f\n",matriz[j][i]);
                    }
                    printf ("Nota final Conjunto: %f \n",mediaEscolas[j][y]);

                    y = 6;
                    for (i = 30 ; i < 35; i++)
                    {
                        printf ("Notas por quesito Alegorias e Aderecos: %f\n",matriz[j][i]);
                    }
                    printf ("Nota final Alegoria e aderecos: %f \n",mediaEscolas[j][y]);

                    y = 7;
                    for (i = 35 ; i < 40; i++)
                    {
                        printf ("Notas por quesito Fantasias: %f\n",matriz[j][i]);
                    }
                    printf ("Nota final Fantasias: %f \n",mediaEscolas[j][y]);

                    y = 8;
                    for (i = 40 ; i < 45; i++)
                    {
                        printf ("Notas por quesito Comissao de Frente: %f\n",matriz[j][i]);
                    }
                    printf ("Nota final Comissao de Frente: %f \n",mediaEscolas[j][y]);

                    y = 9;
                    for (i = 45 ; i < 50; i++)
                    {
                        printf ("Notas por quesito Mestre Salas e Porta Bandeira: %f\n",matriz[j][i]);
                    }
                    printf ("Nota final Mestre Salas e Porta Bandeira: %f \n",mediaEscolas[j][y]);

                    y = 10;
                    for (i = 50 ; i < 55; i++)
                    {
                        printf ("Notas por quesito Ousadia: %f\n",matriz[j][i]);
                    }
                    printf ("Nota final OUsadia: %f \n",mediaEscolas[j][y]);

                    y = 11;
                    for (i = 55 ; i < 60; i++)
                    {
                        printf ("Notas por quesito Simpatia: %f\n",matriz[j][i]);
                    }
                    printf ("Nota final Simpatia: %f \n",mediaEscolas[j][y]);

                    y = 12;
                    for (i = 60 ; i < 65; i++)
                    {
                        printf ("Notas por quesito Samba no Pe: %f\n",matriz[j][i]);
                    }
                    printf ("Nota final Samba no Pe: %f \n",mediaEscolas[j][y]);

                    printf ("\n\n\n");
                    y = 0;
                }
                printf ("Deseja voltar ao menu? 1-SIM 2-NAO\n");
                scanf ("%d",&opc);

                if (opc == 1)
                {
                    system("cls"); // lipando tela
                    menu(); // exibindo menu
                    scanf ("%d",&Menu); // lendo e armazenando na variavel menu
                }
                else
                {
                    printf ("Fim do Programa\n");
                }

            }
            break;

        case 6:

            if (Menu == 6)
            {
                printf ("CAMPEA E VICE-CAMPEA\n");

                for (j = 0 ; j < tam ; j++)
                {
                    // Aqui a vaiavel maior pega a maior nota;

                    if (j == 0)
                    {
                        maior = 0 ;
                    }

                    if (final[j] > maior)     // Apos descobrir a maior nota a variavel substitui a posição da mesma para um valor muito pequeno afim de descobrir a segunda maior
                    {
                        maior = final[j];
                        pos = j;
                    }
                }

                final[pos] = 0;

                for (j = 0 ; j < tam ; j++)         //Aqui a segunda maior nota é armazenada em maior2
                {

                    if (final[j] > final[pos])
                    {
                        maior2 = final[j];
                        pos2 = j;
                    }
                }

                final[pos2] = maior2;
                final[pos] = maior;
                // Exibe a esola campea e a vice
                printf ("Escola Campea: %s - Reposnsavel: %s Nota Final: %f\n",cadastro[pos].nome,cadastro[pos].responsavel,maior);
                printf ("Vice-Campea: %s - Reposnsavel: %s Nota Final: %f\n",cadastro[pos2].nome,cadastro[pos2].responsavel,maior2);

                printf ("Deseja voltar ao menu? 1-SIM 2-NAO\n");
                scanf ("%d",&opc);

                if (opc == 1)
                {
                    system("cls"); // lipando tela
                    menu(); // exibindo menu
                    scanf ("%d",&Menu); // lendo e armazenando na variavel menu
                }
                else
                {
                    printf ("Fim do Programa\n");
                }

            }

            break;

        case 7:

            if (Menu == 7)
            {
                printf ("ESCOLAS REBAIXADAS\n");

                for (j = 0 ; j < tam ; j++) 	// Aqui a vaiavel menor pega a menor nota;
                {
                    if (j == 0)
                    {
                        menor = 10000 ;
                    }

                    if (final[j] < menor)
                    {
                        menor = final[j];
                        posm = j;

                    }
                }

                final[posm] = 10000;   // Apos descobrir a menor nota a variavel substitui a posição da mesma para um valor muito grande afim de descobrir a segunda menor


                for (j = 0 ; j < tam ; j++)
                {
                    if(j == 0)                         //Em seguida busca a segunda menor
                    {
                        menor2 = 1000;
                    }

                    if (final[j] < menor2)
                    {
                        menor2 = final[j];
                        posm2 = j;
                    }
                }

                final[posm2] = menor2;
                final[posm] = menor;
                //Exibe as duas escolas rebaixadas
                printf ("Primeira Rebaixada: %s - Reposnsavel: %s Nota Final: %f\n",cadastro[posm].nome,cadastro[posm].responsavel,menor);
                printf ("Segunda Rebaixada: %s - Reposnsavel: %s Nota Final: %f\n",cadastro[posm2].nome,cadastro[posm2].responsavel,menor2);

                printf ("Deseja voltar ao menu? 1-SIM 2-NAO\n");
                scanf ("%d",&opc);

                if (opc == 1)
                {
                    system("cls"); // lipando tela
                    menu(); // exibindo menu
                    scanf ("%d",&Menu); // lendo e armazenando na variavel menu
                }
                else
                {
                    printf ("Fim do Programa\n");
                }
            }
            break;


        case 8:            //Salva os dados das escolas em um arquivo

            if (Menu == 8)
            {
                printf ("GRAVAR DADOS DAS ESCOLAS\n");

                f = fopen("dados.txt", "w");
                if(f == NULL)
                {
                    printf("Erro na abertura\n");
                    exit(1);//aborta o programa
                }
                for ( j = 0 ; j < tam ; j++)
                {
                    char texto[20] = "Nome: ";
                    char texto2[20] = "Responsavel: ";
                    char texto3[20] = "Nota Final: ";

                    fputs (texto,f);
                    fprintf(f,"%s\n",cadastro[j].nome);
                    fputs (texto2,f);
                    fprintf(f,"%s\n",cadastro[j].responsavel);
                    fputs (texto3,f);
                    fprintf(f, "%f\n",final[j]);
                }

                erro = fclose(f);
                if (erro == 0)
                {
                    printf("\nArquivo fechado com sucesso.\n");
                }
                else
                {
                    printf("\nErro no fechamento.\n");
                }


                printf ("Deseja voltar ao menu? 1-SIM 2-NAO\n");
                scanf ("%d",&opc);

                if (opc == 1)
                {
                    system("cls"); // lipando tela
                    menu(); // exibindo menu
                    scanf ("%d",&Menu); // lendo e armazenando na variavel menu
                }
                else
                {
                    printf ("Fim do Programa\n");
                }
            }

            break;

        case 9:     //Carrega os dados das escolas armazendas no arquivo

            if (Menu == 9)
            {
                printf ("CARREGAR DADOS DAS ESCOLAS\n");


                f = fopen("dados.txt", "w");
                if(f == NULL)
                {
                    printf("Erro na abertura\n");
                    exit(1);//aborta o programa
                }
                for (j = 0 ; j < tam ; j++)
                {
                    fscanf(f,"%s\n",cadastro[j].nome);
                    printf ("%s\n",cadastro[j].nome);
                    fscanf(f,"%s\n",cadastro[j].responsavel);
                    printf ("%s\n",cadastro[j].responsavel);
                    fscanf(f, "%f\n",final[j]);
                    printf ("Nota final %f\n",final[j]);
                }
                erro = fclose(f);
                if (erro == 0)
                {
                    printf("\nArquivo fechado com sucesso.\n");
                }
                else
                {
                    printf("\nErro no fechamento.\n");
                }

                printf ("Deseja voltar ao menu? 1-SIM 2-NAO\n");
                scanf ("%d",&opc);

                if (opc == 1)
                {
                    system("cls"); // lipando tela
                    menu(); // exibindo menu
                    scanf ("%d",&Menu); // lendo e armazenando na variavel menu
                }
                else
                {
                    printf ("Fim do Programa\n");
                }

            }


        }

        // saindo do programa

    }

    return 0;
}