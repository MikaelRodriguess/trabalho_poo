#include "biblioteca/acervo.hpp"

#include <stdexcept>
#include <utility>

namespace biblioteca {

Acervo& Acervo::operator+=(std::unique_ptr<ItemAcervo> item) {
  // Uma posição vazia na estante quebraria quem percorre o acervo.
  if (!item) {
    throw std::invalid_argument("nao se cataloga um item inexistente (nullptr)");
  }
  push_back(std::move(item));
  return *this;
}

}  // namespace biblioteca
