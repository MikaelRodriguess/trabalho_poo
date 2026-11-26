#include "biblioteca/revista.hpp"

namespace biblioteca {

Revista::Revista(const std::string& titulo, int ano, int numero_edicao)
    : ItemAcervo(titulo, ano), numero_edicao_(exigir_positivo(numero_edicao, "numero da edicao")) {
  ++criados_;
  ++vivos_;
}

Revista::~Revista() { --vivos_; }

std::string Revista::tipo() const { return "Revista"; }

int Revista::prazo_emprestimo_dias() const { return prazo_dias; }

std::string Revista::detalhe() const { return "edicao n. " + std::to_string(numero_edicao_); }

}  // namespace biblioteca
