# Decisões de desenho

## 1. Por que a base é abstrata?

Na estante não existe "item genérico". Existe o livro, a revista e o DVD. Perguntar a um `ItemAcervo` qualquer qual é o prazo de empréstimo dele, ou que detalhe aparece na ficha, não tem resposta: o livro fica 14 dias, a revista 3, o DVD 7, e cada um se descreve de um jeito (autor, número da edição, duração). Se `prazo_emprestimo_dias()` tivesse um corpo padrão, digamos 7 dias, um tipo novo que esquecesse de sobrescrever compilaria normalmente e sairia emprestando com o prazo errado, sem ninguém perceber. Além disso, daria para criar um item que não é nada. Deixando as funções puras, o compilador cobra de cada tipo a sua resposta e proíbe instanciar a base.

## 2. Por que cada herança é da forma que é?

**Pública:** livro, revista e DVD *são* itens do acervo de verdade. Em qualquer lugar onde a biblioteca espera um item (no acervo, na ficha, no empréstimo), qualquer um dos três tem de servir.

**Múltipla:** o livro é um item e, além disso, *cumpre* o contrato de renovação. A revista não cumpre, porque precisa voltar logo para a estante antes da próxima edição. Por isso a renovação ficou numa interface separada, e não na base. Como `Renovavel` não tem nenhum dado, herdar das duas não duplica estado nem cria ambiguidade.

**Privada:** o acervo é *feito com* um vector, mas não *é* um vector. Se a herança fosse pública, qualquer um poderia usar o acervo como um vector comum. Reexpus só `size`, `empty`, `begin` e `end`, ou seja, saber quantos itens há e percorrer a estante. Deixei de fora `push_back`, `insert`, `erase`, `clear`, `pop_back`, `operator[]` e `resize`. De fora ninguém pode enfiar um item no meio, tirar um item do catálogo, esvaziar a estante ou criar posições vazias: a única porta de entrada é o `+=`, que recusa `nullptr`. Tem uma brecha que eu reconheço: o `begin`/`end` não-const devolvem iteradores para `unique_ptr` modificáveis, então quem tem um `Acervo` não-const ainda poderia fazer `*it = nullptr` ou mover um item para fora. No `main` eu percorro o acervo por referência const para não depender disso. Fechar de vez exigiria escrever `begin`/`end` próprios que devolvessem só iteradores const, em vez do `using`.

## 3. Quem é dono de quê?

O `Acervo` é o único dono de todos os itens, e isso está no tipo: ele é um `vector<unique_ptr<ItemAcervo>>`, e `unique_ptr` quer dizer exatamente "um dono só". O `operator+=` recebe o `unique_ptr` por valor, então quem chama precisa entregar a posse com `std::move`, e o ponteiro dele fica vazio. Quando o acervo sai de escopo, o vector destrói os `unique_ptr`, e cada um destrói o seu item pelo destrutor virtual da base. É por isso que o livro, a revista e o DVD morrem certinhos e os contadores fecham em zero. No `main`, a referência `Livro& vidas_secas` é só para observar o livro: ela não destrói nada e só vale enquanto o acervo existir. Título, autor e os outros textos são `std::string` por valor, então cada item é dono dos seus.

## 4. Por que cada operador é membro ou livre?

O `operator<<` é livre porque o lado esquerdo é o `std::ostream`, que não é classe minha. Eu não tenho como acrescentar um membro ao `ostream`, e como membro do `ItemAcervo` a escrita ficaria invertida (`item << cout`). Ele também não precisa de acesso privado, porque usa a `ficha()` pública. O `operator+=` é membro porque o lado esquerdo é o próprio acervo, que é quem muda: o item entra nele. Ele também precisa enxergar o `push_back` da base privada, que só a própria classe acessa. Devolve `Acervo&` (o `*this`), como o `+=` embutido devolve o objeto da esquerda, e por isso dá para encadear `(acervo += a) += b`.

## Uso de assistente de IA

**Assistente:** Claude Code (modelo Claude Opus 5.5, da Anthropic), usado no VS Code.

**Para quê.** A partir do enunciado, do código da Unidade I e de um desenho de classes que eu defini e entreguei a ele, o assistente:

- montou a estrutura do repositório, o `CMakeLists.txt` (biblioteca `biblioteca_core` com o portão de avisos e executável `demo`), o `Makefile` com os alvos `make`, `roda`, `verifica` e `limpa`, e o `.gitignore`;
- escreveu `ItemAcervo`, `Renovavel`, `Livro`, `Revista`, `Dvd` e `Acervo`, reaproveitando as validações `exigir_nao_vazio` e `exigir_positivo` da Unidade I como funções estáticas protegidas da base;
- propôs, por conta própria, o gancho privado `ao_devolver()` (virtual com corpo vazio), para que o `Livro` zere as renovações a cada devolução sem tornar `devolver()` virtual;
- escreveu o `contrato.hpp`, com 17 `static_assert`, e o `main.cpp` com as três seções;
- rodou `make limpa && make verifica` a cada etapa e fez os commits por etapa;
- escreveu o `README.md`, colando a saída real de `make roda`;
- a meu pedido, redigiu as quatro respostas acima a partir do desenho que eu escolhi. Eu as revisei.

**Na conversa, o assistente apontou que** os iteradores não-const reexpostos pelo `using` permitem esvaziar posições do acervo (citado na resposta 2).

**O que ele errou:**

- Ao escrever esta seção pela primeira vez, afirmou que o `contrato.hpp` tinha 19 `static_assert`, mas são 17. Ele mesmo percebeu a diferença quando conferiu com `grep -c static_assert`, e corrigiu no último commit antes de qualquer publicação.
