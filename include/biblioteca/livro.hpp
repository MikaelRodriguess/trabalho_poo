#pragma once

#include <string>

#include "biblioteca/item_acervo.hpp"
#include "biblioteca/renovavel.hpp"

namespace biblioteca {

// Livro é um item do acervo E cumpre o contrato de renovação. Herança
// múltipla segura: Renovavel não tem estado.
class Livro final : public ItemAcervo, public Renovavel {
 public:
  static constexpr int prazo_dias = 14;
  static constexpr int max_renovacoes = 2;

  Livro(const std::string& titulo, int ano, const std::string& autor);
  ~Livro() override;

  Livro(const Livro&) = delete;
  Livro& operator=(const Livro&) = delete;

  [[nodiscard]] const std::string& get_autor() const { return autor_; }

  bool renovar() override;
  [[nodiscard]] int renovacoes_restantes() const override;

  [[nodiscard]] static int get_vivos() { return vivos_; }
  [[nodiscard]] static int get_criados() { return criados_; }

 private:
  [[nodiscard]] std::string tipo() const override;
  [[nodiscard]] int prazo_emprestimo_dias() const override;
  [[nodiscard]] std::string detalhe() const override;
  void ao_devolver() override;

  // O contador mora na concreta: cada tipo responde pelos próprios objetos.
  inline static int vivos_ = 0;
  inline static int criados_ = 0;

  std::string autor_;
  int renovacoes_feitas_ = 0;  // zera a cada devolução: o limite é por empréstimo
};

}  // namespace biblioteca
