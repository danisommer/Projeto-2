/*============================================================================*/
/* CSF13 - 2023-1 - TRABALHO 2                                                */
/*----------------------------------------------------------------------------*/
/* AUTORES:                                                                   */
/* - DANIEL ZAKI SOMMER, 2582708                                              */
/* - LUCAS DAVID ROSCZINIAK COSTA, 2582732                                    */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*============================================================================*/

#include "trabalho2.h"
#include "wavfile.h"

//Função 1
void mudaGanho(double* dados, int n_amostras, double ganho)
{
    int i;

    for (i = 0; i < n_amostras; i++) {
        dados[i] = dados[i] * ganho;
    }
}

//Função 2
void misturaDados (double* dados1, double* dados2, double* saida, int n_amostras)
{
    int i;

    for(i=0;i<n_amostras;i++)
        saida[i]=dados1[i]+dados2[i];
}

//Função 3
void inverteSinal(double* dados, int n_amostras)
{
    int i, j;
    double temp;

    for (i = 0, j = n_amostras - 1; i < j; i++, j--)
    {
        temp = dados[i];
        dados[i] = dados[j];
        dados[j] = temp;
    }
}
//Função 4
void atrasaSinal(double* dados, int n_amostras, int atraso) {
    if (atraso == 0)
        return;
    else if (atraso > 0)
    {
        int i;
        for (i = n_amostras - 1; i >= atraso; i--)
            dados[i] = dados[i - atraso];
        for (; i >= 0; i--)
            dados[i] = 0.0;

    }
    else
    {
        atraso = -atraso;
        int i;
        for (i = 0; i < n_amostras - atraso; i++)
            dados[i] = dados[i + atraso];
        for (; i < n_amostras; i++)
            dados[i] = 0.0;
    }
}
//Função 5
void filtroDaMedia(double* dados, int n_amostras, unsigned short largura)
{
    if (largura < 3 || largura > n_amostras || largura % 2 == 0)
        return;

    int metade_largura = (largura - 1) / 2;

    int i;
    for (i = metade_largura; i < n_amostras - metade_largura; i++)
    {
        double soma = 0.0;
        int j;
        for (j = i - metade_largura; j <= i + metade_largura; j++)
            soma += dados[j];
        dados[i] = soma / largura;
    }
}
//Função 6
void ecos(double* dados, int n_amostras, unsigned short n_repeticoes, int atraso, unsigned short abafamento, double decaimento) {
    double* ecos = (double*)malloc(n_amostras * sizeof(double));
    int i;

    for (i = 0; i < n_amostras; i++) {
        ecos[i] = dados[i];
    }

    for (i = 1; i <= n_repeticoes; i++) {
        atrasaSinal(ecos, n_amostras, atraso * i);

        filtroDaMedia(ecos, n_amostras, abafamento);

        int j;
        for (j = 0; j < n_amostras; j++)
            ecos[j] *= decaimento;

        int k;
        for (k = 0; k < n_amostras; k++)
            dados[k] += ecos[k];
    }

    free(ecos);
}


