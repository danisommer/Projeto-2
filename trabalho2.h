/*============================================================================*/
/* CSF13 - 2023-1 - TRABALHO 2                                                */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu - btnassu@utfpr.edu.br                                     */
/* Leyza E. B. Dorini - leyza@utfpr.edu.br                                    */
/*============================================================================*/
/** Funções pedidas para o 2o trabalho da disciplina Fundamentos de Programação
 * 1, 1o semestre de 2023, prof. Bogdan T. Nassu e Leyza E. B. Dorini,
 * Universidade Tecnológica Federal do Paraná. */
/*============================================================================*/

#ifndef __TRABALHO2_H
#define __TRABALHO2_H

/*============================================================================*/

void mudaGanho (double* dados, int n_amostras, double ganho);
void misturaDados (double* dados1, double* dados2, double* saida, int n_amostras);
void inverteSinal (double* dados, int n_amostras);
void atrasaSinal (double* dados, int n_amostras, int atraso);
void filtroDaMedia (double* dados, int n_amostras, unsigned short largura);
void ecos (double* dados, int n_amostras, unsigned short n_repeticoes, int atraso, unsigned short abafamento, double decaimento);


/*============================================================================*/
#endif /* __TRABALHO2_H */
