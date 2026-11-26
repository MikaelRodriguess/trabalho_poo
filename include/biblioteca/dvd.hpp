#pragma once

#include <string>

#include "biblioteca/item_acervo.hpp"

namespace biblioteca {

// Mídia audiovisual do acervo: prazo intermediário, sem renovação.
class Dvd final : public ItemAcervo {
 public:
  static constexpr int prazo_dias = 7;

  Dvd(const std::string& titulo, int ano, int duracao_minutos);
  ~Dvd() override;

  Dvd(const Dvd&) = delete;
  Dvd& operator=(const Dvd&) = delete;

  [[nodiscard]] int get_duracao_minutos() const { return duracao_minutos_; }

  [[nodiscard]] static int get_vivos() { return vivos_; }
  [[nodiscard]] static int get_criados() { return criados_; }

 private:
  [[nodiscard]] std::string tipo() const override;
  [[nodiscard]] int prazo_emprestimo_dias() const override;
  [[nodiscard]] std::string detalhe() const override;

  inline static int vivos_ = 0;
  inline static int criados_ = 0;

  int duracao_minutos_;
};

}  // namespace biblioteca
