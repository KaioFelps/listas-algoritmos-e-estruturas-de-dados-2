/**
 * Código retirado de: https://github.com/julianofoleiss/BCC4001
 */

#pragma once

#include <vector>

namespace external::utils
{
void trocar(int *v, int a, int b);

std::vector<int> gerar_vetor_aleatorio(int n, int seed, int max);

void imprimir_vetor(int *v, int n);

std::vector<int> gerar_vetor_aleatorio_sem_reps(int n, int seed);
}