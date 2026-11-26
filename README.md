# Biblioteca: acervo polimórfico em C++17

Trabalho prático da Unidade II de Programação Orientada a Objetos (UFPB, 2026.2), no mesmo tema da Unidade I: o acervo de uma biblioteca. Na Unidade I a biblioteca guardava só livros, por meio de ponteiros crus. Agora o acervo guarda itens de tipos diferentes (livros, revistas e DVDs), e todos podem ser emprestados e devolvidos. Cada tipo tem o seu prazo de empréstimo e a sua forma de se descrever na ficha catalográfica.

Nem todo item aceita renovação. O livro pode ter o empréstimo prorrogado até duas vezes por empréstimo. A revista volta em três dias e não renova, porque a próxima edição chega logo. O DVD tem prazo de uma semana. O `Acervo` é o único dono dos itens: eles só entram pelo `+=`, como `std::unique_ptr`, e são destruídos junto com ele, o que os contadores estáticos comprovam ao fim do programa.

## Como compilar e rodar

Requisitos: CMake 3.16 ou superior, um compilador C++17 (GCC ou Clang) e `make`.

| Comando | O que faz |
|---|---|
| `make` | configura e compila em `build/` |
| `make roda` | compila e executa a demonstração |
| `make verifica` | compila sob o portão de avisos (`-Werror`), roda e confere que a última linha é `vivos=0` |
| `make limpa` | apaga a pasta `build/` |

## As classes

| Classe | Papel no domínio | Forma de herança |
|---|---|---|
| `ItemAcervo` | Base abstrata de tudo que se empresta. Guarda título, ano e situação. `ficha()` é a moldura não virtual (NVI) que chama as puras `tipo()`, `prazo_emprestimo_dias()` e `detalhe()`. | Raiz da hierarquia. Destrutor virtual, cópia deletada. |
| `Renovavel` | Interface pura: o contrato de quem aceita prorrogar o empréstimo (`renovar()`, `renovacoes_restantes()`). Não tem dados. | Raiz. Só funções puras e destrutor virtual. |
| `Livro` | Item com autor, prazo de 14 dias e até 2 renovações por empréstimo. | `final`, pública e **múltipla**: `public ItemAcervo, public Renovavel` |
| `Revista` | Periódico com número de edição, prazo de 3 dias, sem renovação. | `final`, `public ItemAcervo` |
| `Dvd` | Mídia com duração em minutos, prazo de 7 dias, sem renovação. | `final`, `public ItemAcervo` |
| `Acervo` | Coleção dona dos itens. Reexpõe só `size`, `empty`, `begin` e `end`. A inserção é só por `operator+=`. | **privada**: `private std::vector<std::unique_ptr<ItemAcervo>>` |

O arquivo `include/biblioteca/contrato.hpp` reúne, em `static_assert`, as propriedades do desenho (base abstrata, interface sem dados, concretas `final`, herança múltipla e privada). Ele é incluído pelo `main.cpp`, então o projeto não compila se alguma deixar de valer.

## Estrutura

```
include/biblioteca/   cabeçalhos (um por classe) e contrato.hpp
src/                  implementações e main.cpp
CMakeLists.txt        biblioteca biblioteca_core + executável demo, portão de avisos
Makefile              alvos make, roda, verifica e limpa
DECISAO.md            as decisões de desenho e o registro do uso de IA
```

## Saída de `make roda`

```
./build/demo
=== 1. o acervo polimorfico ===
  [Livro] "Dom Casmurro" (1899) - Machado de Assis, renovacoes restantes: 2 | prazo 14 dias | disponivel
  [Revista] "Revista Piaui" (2024) - edicao n. 218 | prazo 3 dias | disponivel
  [DVD] "Central do Brasil" (1998) - 113 min | prazo 7 dias | disponivel
  -- depois de emprestar todos --
  [Livro] "Dom Casmurro" (1899) - Machado de Assis, renovacoes restantes: 2 | prazo 14 dias | emprestado
  [Revista] "Revista Piaui" (2024) - edicao n. 218 | prazo 3 dias | emprestado
  [DVD] "Central do Brasil" (1998) - 113 min | prazo 7 dias | emprestado

=== 2. os operadores ===
  += encadeado: o acervo agora tem 5 itens
  << no novo livro: [Livro] "Vidas Secas" (1938) - Graciliano Ramos, renovacoes restantes: 2 | prazo 14 dias | disponivel
  += com nullptr rejeitado: nao se cataloga um item inexistente (nullptr)
  renovar sem emprestar: recusado
  renovar 1: ok
  renovar 2: ok
  renovar 3: recusado
  [Livro] "Vidas Secas" (1938) - Graciliano Ramos, renovacoes restantes: 0 | prazo 14 dias | emprestado
  apos devolver: [Livro] "Vidas Secas" (1938) - Graciliano Ramos, renovacoes restantes: 2 | prazo 14 dias | disponivel

=== 3. os contadores ===
  dentro do escopo: livros vivos=3 criados=3 | revistas vivos=1 criados=1 | dvds vivos=1 criados=1 | total vivos=5
  depois do escopo: livros vivos=0 criados=3 | revistas vivos=0 criados=1 | dvds vivos=0 criados=1 | total vivos=0
vivos=0
```
