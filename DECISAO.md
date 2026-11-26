# Decisões de desenho

## 1. Por que a base é abstrata?

Porque não existe "item genérico" na estante. Prazo de empréstimo e detalhe da ficha só têm resposta no livro (14 dias, autor), na revista (3 dias, edição) ou no DVD (7 dias, duração). Com um corpo padrão, um tipo novo que esquecesse de sobrescrever sairia emprestando com o prazo errado sem ninguém perceber.

## 2. Por que cada herança é da forma que é?

- **Pública:** livro, revista e DVD *são* itens; onde a biblioteca espera um item, qualquer um deles serve.
- **Múltipla:** o livro é um item e *cumpre* o contrato de renovação; a revista não, porque precisa voltar logo. Como `Renovavel` não tem dados, herdar das duas não duplica estado.
- **Privada:** o acervo é *feito com* um vector, não *é* um. Expus só `size`, `empty`, `begin` e `end`. Deixei de fora `push_back`, `insert`, `erase`, `clear` e `operator[]`, para que ninguém de fora insira no meio, remova itens ou esvazie a estante: só se entra pelo `+=`, que recusa `nullptr`. Limite: o `begin`/`end` não-const ainda permitem trocar um `unique_ptr`; por isso o `main` só percorre o acervo por referência const.

## 3. Quem é dono de quê?

O `Acervo` é o único dono dos itens, e isso está no tipo: `vector<unique_ptr<ItemAcervo>>`. O `+=` recebe o `unique_ptr` por valor, então a posse passa para o acervo. Quando ele sai de escopo, cada item é destruído pelo destrutor virtual da base, e os contadores fecham em zero. A referência `Livro& vidas_secas` no `main` só observa: não destrói nada.

## 4. Por que cada operador é membro ou livre?

- **`operator<<` é livre:** o lado esquerdo é o `ostream`, que não é classe minha.
- **`operator+=` é membro:** o lado esquerdo é o próprio acervo, que é quem muda. Ele devolve `*this`, como o `+=` embutido.

## Uso de assistente de IA

**Assistente:** Claude Code (Claude Opus 5.5).

**Para quê:** eu defini o tema, as classes e o papel de cada uma no desenho. A partir disso, o assistente me ajudou a escrever o código (classes, `contrato.hpp`, `main.cpp`, CMake e Makefile), o README que eu revisei e um rascunho das respostas. Os commits foram feitos por etapa, rodando `make verifica` a cada uma.

**O que ele errou:**
- Escreveu que o `contrato.hpp` tinha 19 `static_assert`; são 17.
- Afirmou que o `main` percorria o acervo só por referência const, mas um dos laços usava o acervo não-const. Corrigido depois de conferir o texto contra o código.
