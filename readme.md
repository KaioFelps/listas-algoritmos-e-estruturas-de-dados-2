# Algoritmos e Estruturas De Dados 2
Nesse repositório estão as resoluções das listas de exercícios da matéria Algoritmos e
Estruturas de Dados 2.

## Instalando easexx
Copie e cole o script abaixo para baixar e compilar o easexx.
Garanta que exista uma [instalação do (Rust e) Cargo] para compilar.

```
curl https://raw.githubusercontent.com/kaiofelps/easexx/main/install.sh | sh
```

[instalação do (Rust e) Cargo]: https://www.rust-lang.org/tools/install

## Árvore de Busca Binária
Seja $N$ o um nó qualquer de uma árvore, $E$ o nó-filho esquerdo de $N$, e $D$ o nó-filho direito.
A árvore de busca binária deve ser garantida que $\forall N \quad E < N < D$, isso é, todos os
nós à direita de $N$ são menores que ele, e os à esquerda, maiores. Essa propriedade **deve ser
garantida antes e após todas as operações realizadas na árvore**.
