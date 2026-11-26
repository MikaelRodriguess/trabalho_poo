#include "biblioteca/item_acervo.hpp"

#include <ostream>
#include <stdexcept>

namespace biblioteca {

ItemAcervo::ItemAcervo(const std::string& titulo, int ano)
    : titulo_(exigir_nao_vazio(titulo, "titulo")),
      ano_(exigir_positivo(ano, "ano")),
      disponivel_(true) {}

const std::string& ItemAcervo::exigir_nao_vazio(const std::string& valor, const char* campo) {
  if (valor.empty()) {
    throw std::invalid_argument(std::string(campo) + " nao pode ser vazio");
  }
  return valor;
}

int ItemAcervo::exigir_positivo(int valor, const char* campo) {
  if (valor <= 0) {
    throw std::invalid_argument(std::string(campo) + " deve ser positivo");
  }
  return valor;
}

bool ItemAcervo::emprestar() {
  if (!disponivel_) return false;
  disponivel_ = false;
  return true;
}

void ItemAcervo::devolver() {
  if (disponivel_) return;
  disponivel_ = true;
  ao_devolver();
}

std::string ItemAcervo::ficha() const {
  return "[" + tipo() + "] \"" + titulo_ + "\" (" + std::to_string(ano_) + ") - " + detalhe() +
         " | prazo " + std::to_string(prazo_emprestimo_dias()) + " dias | " +
         (disponivel_ ? "disponivel" : "emprestado");
}

std::ostream& operator<<(std::ostream& saida, const ItemAcervo& item) {
  return saida << item.ficha();
}

}  // namespace biblioteca
