#include "biblioteca/livro.hpp"

namespace biblioteca {

Livro::Livro(const std::string& titulo, int ano, const std::string& autor)
    : ItemAcervo(titulo, ano), autor_(exigir_nao_vazio(autor, "autor")) {
  // No corpo: só conta se a validação passou e o objeto de fato nasceu.
  ++criados_;
  ++vivos_;
}

Livro::~Livro() { --vivos_; }

bool Livro::renovar() {
  if (esta_disponivel() || renovacoes_feitas_ >= max_renovacoes) return false;
  ++renovacoes_feitas_;
  return true;
}

int Livro::renovacoes_restantes() const { return max_renovacoes - renovacoes_feitas_; }

std::string Livro::tipo() const { return "Livro"; }

int Livro::prazo_emprestimo_dias() const { return prazo_dias; }

std::string Livro::detalhe() const {
  return autor_ + ", renovacoes restantes: " + std::to_string(renovacoes_restantes());
}

void Livro::ao_devolver() { renovacoes_feitas_ = 0; }

}  // namespace biblioteca
