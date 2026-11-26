#pragma once

namespace biblioteca {

// Contrato: "este item aceita ter o empréstimo prorrogado". É algo que uma
// classe cumpre, não algo que ela é. Sem dados, para que herdar dela junto
// com ItemAcervo não traga estado duplicado nem ambíguo.
class Renovavel {
 public:
  virtual ~Renovavel() = default;

  // Prorroga o empréstimo em curso; false se não estiver emprestado ou se
  // as renovações se esgotaram.
  virtual bool renovar() = 0;
  [[nodiscard]] virtual int renovacoes_restantes() const = 0;
};

}  // namespace biblioteca
