#include "sort_algorithms.hpp"
#include <iostream>

namespace core::sort_algorithms
{

void static merge(int *v, int p, int q, int r)
{
  // 0 - Calcular n1 e n2
  int n1 = q - p + 1;
  int n2 = r - q;

  // 1 - criar e com os elementos de v[p..q]
  int *e = new int[n1];
  for (int i = 0; i < n1; i++)
    e[i] = v[p + i];

  // 2 - criar d com os elementos de v[q+1..r]
  int *d = new int[n2];
  for (int j = 0; j < n2; j++)
    d[j] = v[q + 1 + j];

  int k = p;
  int i = 0, j = 0;

  while (i < n1 && j < n2)
  {
    if (e[i] <= d[j])
    {
      v[k] = e[i];
      i++;
    }
    else
    { // d[j] < e[i]
      v[k] = d[j];
      j++;
    }
    k++;
  }
  while (i < n1)
  {
    // copiar em v o que sobrou em E
    v[k] = e[i];
    i++, k++;
  }
  while (j < n2)
  {
    // copiar em v o que sobrou em D
    v[k] = d[j];
    j++, k++;
  }

  delete[] e;
  delete[] d;
}

void merge_sort(int *v, int p, int r)
{
  if (p < r)
  {
    int m = (p + r) / 2;
    merge_sort(v, p, m);
    merge_sort(v, m + 1, r);
    merge(v, p, m, r);
  }
}

} // namespace core::sort_algorithms