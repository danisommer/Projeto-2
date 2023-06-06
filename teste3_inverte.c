/*============================================================================*/
/* Exemplo: Inverte um sinal. */

#include <stdlib.h>
#include "wavfile.h"
#include "trabalho2.h"

/*============================================================================*/

#define INPUT_FILE "data/sonic2_gui.wav"
#define OUTPUT_FILE "data/teste3_inverte.wav"

/*============================================================================*/

int main ()
{
	WavHeader header; /* Cabeçalho para as informações sobre o arquivo. */
	double* dados_l; /* Dados do canal esquerdo. Alocado na readWavFile. */
	double* dados_r; /* Dados do canal direito. Alocado na readWavFile. */
	int n_amostras;

    /* Lê um arquivo. */
    n_amostras = readWavFile (INPUT_FILE, &header, &dados_l, &dados_r);
    if (!n_amostras)
    {
        printf ("Erro lendo %s.\n", INPUT_FILE);
        return (1);
    }

    /* Inverte. */
    inverteSinal (dados_l, n_amostras);
    if (dados_r)
        inverteSinal (dados_r, n_amostras);

    /* Salva. */
    if (!writeWavFile (OUTPUT_FILE, &header, dados_l, dados_r))
    {
        printf ("Erro salvando %s.\n", OUTPUT_FILE);
        return (1);
    }

    /* Desaloca os vetores. */
	free (dados_l);
	if (dados_r)
        free (dados_r);

	return (0);
}

/*============================================================================*/
