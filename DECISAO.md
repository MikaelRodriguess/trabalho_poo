# Decisões de desenho

## 1. Por que a base é abstrata?

<!-- TODO: resposta do aluno (que operação não faz sentido em ItemAcervo e o que aconteceria se tivesse corpo padrão) -->

## 2. Por que cada herança é da forma que é?

<!-- TODO: resposta do aluno (uma frase para a pública, uma para a múltipla e uma para a privada; na privada, o que o Acervo deixou de expor) -->

<!-- Ponto a citar: o Acervo reexpõe begin/end com `using`, e as versões não-const
     devolvem iteradores para unique_ptr modificáveis. Com um Acervo não-const,
     quem está de fora poderia fazer `*it = nullptr` ou mover um item para fora,
     furando a regra de "só entra pelo +=". O main percorre o acervo por
     referência const para não depender disso. -->

## 3. Quem é dono de quê?

<!-- TODO: resposta do aluno (quem destrói cada objeto, e como isso está escrito no tipo) -->

## 4. Por que cada operador é membro ou livre?

<!-- TODO: resposta do aluno (a razão é sobre o lado esquerdo: operator<< e operator+=) -->

## Uso de assistente de IA

**Assistente:** Claude Code (modelo Claude Opus 5.5, da Anthropic), usado no VS Code.

**Para quê.** A partir do enunciado, do código da Unidade I e de um desenho de classes que eu defini e entreguei a ele, o assistente:

- montou a estrutura do repositório, o `CMakeLists.txt` (biblioteca `biblioteca_core` com o portão de avisos e executável `demo`), o `Makefile` com os alvos `make`, `roda`, `verifica` e `limpa`, e o `.gitignore`;
- escreveu `ItemAcervo`, `Renovavel`, `Livro`, `Revista`, `Dvd` e `Acervo`, reaproveitando as validações `exigir_nao_vazio` e `exigir_positivo` da Unidade I como funções estáticas protegidas da base;
- propôs, por conta própria, o gancho privado `ao_devolver()` (virtual com corpo vazio), para que o `Livro` zere as renovações a cada devolução sem tornar `devolver()` virtual;
- escreveu o `contrato.hpp`, com 17 `static_assert`, e o `main.cpp` com as três seções;
- rodou `make limpa && make verifica` a cada etapa e fez os commits por etapa;
- escreveu o `README.md`, colando a saída real de `make roda`, e este modelo de `DECISAO.md`. As quatro respostas acima são minhas.

**Na conversa, o assistente apontou que** os iteradores não-const reexpostos pelo `using` permitem esvaziar posições do acervo (ver o comentário na pergunta 2).

**O que ele errou:**

<!-- TODO: registrar aqui o que o assistente errou -->
