#include "biblioteca/dvd.hpp"

namespace biblioteca {

Dvd::Dvd(const std::string& titulo, int ano, int duracao_minutos)
    : ItemAcervo(titulo, ano), duracao_minutos_(exigir_positivo(duracao_minutos, "duracao")) {
  ++criados_;
  ++vivos_;
}

Dvd::~Dvd() { --vivos_; }

std::string Dvd::tipo() const { return "DVD"; }

int Dvd::prazo_emprestimo_dias() const { return prazo_dias; }

std::string Dvd::detalhe() const { return std::to_string(duracao_minutos_) + " min"; }

}  // namespace biblioteca
