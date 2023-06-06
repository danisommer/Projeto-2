/*============================================================================*/
/* Exemplo: Junta 3 sinais. */

#include <stdlib.h>
#include "wavfile.h"

#include "trabalho2.h"

/*============================================================================*/

#define INPUT_FILE1 "data/sonic2_gui.wav"
#define INPUT_FILE2 "data/sonic2_vio.wav"
#define INPUT_FILE3 "data/sonic2_per.wav"
#define OUTPUT_FILE "data/teste2_mistura.wav"

/*============================================================================*/

int main ()
{
	WavHeader header1; /* Cabeçalho para as informações sobre o arquivo. */
	WavHeader header2; /* Cabeçalho para as informações sobre o arquivo. */

	/* Usamos somente 2 pares de buffers para os 3 sinais. Para isso, misturamos 2 sinais antes de ler o 3o. */
	double* dados_l1; /* Dados do canal esquerdo. Alocado na readWavFile. */
	double* dados_r1; /* Dados do canal direito. Alocado na readWavFile. */
	double* dados_l2; /* Dados do canal esquerdo. Alocado na readWavFile. */
	double* dados_r2; /* Dados do canal direito. Alocado na readWavFile. */

	int n_amostras;

    /* Lê os arquivos, confirma que são stereo e têm o mesmo tamanho. */
    n_amostras = readWavFile (INPUT_FILE1, &header1, &dados_l1, &dados_r1);
    if (!n_amostras)
    {
        printf ("Erro lendo %s.\n", INPUT_FILE1);
        return (1);
    }

    if (!dados_r1)
    {
        printf ("%s nao eh um arquivo stereo.\n", INPUT_FILE1);
        return (1);
    }

    if (readWavFile (INPUT_FILE2, &header2, &dados_l2, &dados_r2) != n_amostras || !dados_r2)
    {
        printf ("%s tem um formato ou tamanho diferente de %s!\n", INPUT_FILE2, INPUT_FILE1);
        return (1);
    }

    /* Guitarra para a esquerda, violão para a direita. */
    mudaGanho (dados_r1, n_amostras, 0.5);
    mudaGanho (dados_l2, n_amostras, 0.5);

    /* Mistura. */
    misturaDados (dados_l1, dados_l2, dados_l1, n_amostras);
    misturaDados (dados_r1, dados_r2, dados_r1, n_amostras);

    free (dados_l2);
    free (dados_r2);

    /* Lê outro arquivo. */
    if (readWavFile (INPUT_FILE3, &header2, &dados_l2, &dados_r2) != n_amostras || !dados_r2)
    {
        printf ("%s tem um formato ou tamanho diferente de %s!\n", INPUT_FILE3, INPUT_FILE1);
        return (1);
    }

    /* Mistura. */
    misturaDados (dados_l1, dados_l2, dados_l1, n_amostras);
    misturaDados (dados_r1, dados_r2, dados_r1, n_amostras);

    /* Salva. */
    if (!writeWavFile (OUTPUT_FILE, &header1, dados_l1, dados_r1))
    {
        printf ("Erro salvando %s.\n", OUTPUT_FILE);
        return (1);
    }

    /* Desaloca os vetores. */
	free (dados_l1);
    free (dados_r1);
    free (dados_l2);
    free (dados_r2);

	return (0);
}

/*============================================================================*/
