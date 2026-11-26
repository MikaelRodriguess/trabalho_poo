#pragma once

#include <iosfwd>
#include <string>

namespace biblioteca {

// Tudo o que a biblioteca empresta. Não existe "item genérico" na estante:
// existe livro, revista, DVD. Por isso a base é abstrata.
class ItemAcervo {
 public:
  virtual ~ItemAcervo() = default;

  // Base polimórfica não se copia por valor: copiar por ItemAcervo& fatiaria
  // a derivada, e dois exemplares com a mesma identidade não fazem sentido.
  ItemAcervo(const ItemAcervo&) = delete;
  ItemAcervo& operator=(const ItemAcervo&) = delete;

  [[nodiscard]] const std::string& get_titulo() const { return titulo_; }
  [[nodiscard]] int get_ano() const { return ano_; }
  [[nodiscard]] bool esta_disponivel() const { return disponivel_; }

  // Empréstimo e devolução são iguais para todo item: não são virtuais.
  bool emprestar();
  void devolver();

  // R11: a moldura é da base (não virtual); o conteúdo vem das puras abaixo.
  [[nodiscard]] std::string ficha() const;

 protected:
  ItemAcervo(const std::string& titulo, int ano);

  // Validações da Unidade I: o objeto nunca nasce inválido.
  static const std::string& exigir_nao_vazio(const std::string& valor, const char* campo);
  static int exigir_positivo(int valor, const char* campo);

 private:
  // NVI: as puras são privadas. Quem está de fora só enxerga ficha();
  // as derivadas preenchem as partes, mas não reescrevem a moldura.
  [[nodiscard]] virtual std::string tipo() const = 0;
  [[nodiscard]] virtual int prazo_emprestimo_dias() const = 0;
  [[nodiscard]] virtual std::string detalhe() const = 0;

  // Gancho opcional chamado por devolver(); o padrão é não fazer nada.
  virtual void ao_devolver() {}

  std::string titulo_;
  int ano_;
  bool disponivel_;
};

// Livre: o operando da esquerda é o ostream, que não é classe nossa.
std::ostream& operator<<(std::ostream& saida, const ItemAcervo& item);

}  // namespace biblioteca
