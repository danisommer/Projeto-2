/*============================================================================*/
/* Exemplo: Adiciona um atraso ao lado esquerdo do sinal. */

#include <stdlib.h>
#include "wavfile.h"

#include "trabalho2.h"

/*============================================================================*/

#define INPUT_FILE "data/sonic2_gui.wav"
#define OUTPUT_FILE "data/teste4_atraso.wav"

/*============================================================================*/

int main ()
{
	WavHeader header; /* Cabe�alho para as informa��es sobre o arquivo. */
	double* dados_l; /* Dados do canal esquerdo. Alocado na readWavFile. */
	double* dados_r; /* Dados do canal direito. Alocado na readWavFile, se necess�rio. */
	int n_amostras; /* N�mero de amostras nos buffers. */

    /* L� um arquivo. */
    n_amostras = readWavFile (INPUT_FILE, &header, &dados_l, &dados_r);
    if (!n_amostras)
    {
        printf ("Erro lendo %s.\n", INPUT_FILE);
        return (1);
    }

	/* Confirma que o arquivo � stereo. */
    if (!dados_r)
    {
        printf ("%s nao eh um arquivo stereo.\n", INPUT_FILE);
        return (1);
    }

    /* Adiciona um atraso de 2 segundos no lado esquerdo. */
    atrasaSinal (dados_l, n_amostras, 88200);

    /* Escreve em outro arquivo. */
    if (!writeWavFile (OUTPUT_FILE, &header, dados_l, dados_r))
    {
        printf ("Erro salvando %s.\n", OUTPUT_FILE);
        return (1);
    }

    /* Desaloca os vetores. O direito s� vai ter sido alocado se o arquivo for est�reo. */
	free (dados_l);
	if (dados_r)
        free (dados_r);

	return (0);
}

/*============================================================================*/
