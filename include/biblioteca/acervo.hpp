#pragma once

#include <memory>
#include <vector>

#include "biblioteca/item_acervo.hpp"

namespace biblioteca {

// O acervo é FEITO COM um vector, não É um vector. A herança privada (escrita
// explicitamente) impede que o acervo seja usado como vector qualquer: quem
// está de fora não pode inserir no meio, apagar ou esvaziar a estante. A
// entrada prevista é o +=, e o acervo é o único dono de cada item.
// Limite conhecido: begin/end não-const dão acesso ao unique_ptr, o que ainda
// permitiria trocar ou anular um item (ver DECISAO.md, pergunta 2).
class Acervo final : private std::vector<std::unique_ptr<ItemAcervo>> {
  using Estante = std::vector<std::unique_ptr<ItemAcervo>>;

 public:
  // Reexpostos: só consultar o tamanho e percorrer.
  using Estante::begin;
  using Estante::empty;
  using Estante::end;
  using Estante::size;

  // Membro: altera o acervo da esquerda e devolve *this, como o += embutido.
  // Recebe o unique_ptr por valor: a posse do item passa para o acervo.
  Acervo& operator+=(std::unique_ptr<ItemAcervo> item);
};

}  // namespace biblioteca
