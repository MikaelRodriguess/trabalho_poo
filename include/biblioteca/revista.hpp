#pragma once

#include <string>

#include "biblioteca/item_acervo.hpp"

namespace biblioteca {

// Periódico: prazo curto e sem renovação, porque a próxima edição chega logo
// e a atual precisa voltar à estante. Por isso não herda de Renovavel.
class Revista final : public ItemAcervo {
 public:
  static constexpr int prazo_dias = 3;

  Revista(const std::string& titulo, int ano, int numero_edicao);
  ~Revista() override;

  Revista(const Revista&) = delete;
  Revista& operator=(const Revista&) = delete;

  [[nodiscard]] int get_numero_edicao() const { return numero_edicao_; }

  [[nodiscard]] static int get_vivos() { return vivos_; }
  [[nodiscard]] static int get_criados() { return criados_; }

 private:
  [[nodiscard]] std::string tipo() const override;
  [[nodiscard]] int prazo_emprestimo_dias() const override;
  [[nodiscard]] std::string detalhe() const override;

  inline static int vivos_ = 0;
  inline static int criados_ = 0;

  int numero_edicao_;
};

}  // namespace biblioteca
