#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

#include "biblioteca/acervo.hpp"
#include "biblioteca/contrato.hpp"
#include "biblioteca/dvd.hpp"
#include "biblioteca/item_acervo.hpp"
#include "biblioteca/livro.hpp"
#include "biblioteca/revista.hpp"

using biblioteca::Acervo;
using biblioteca::Dvd;
using biblioteca::ItemAcervo;
using biblioteca::Livro;
using biblioteca::Revista;

namespace {

int vivos_total() { return Livro::get_vivos() + Revista::get_vivos() + Dvd::get_vivos(); }

void imprimir_contadores(const char* momento) {
  std::cout << "  " << momento << ": livros vivos=" << Livro::get_vivos()
            << " criados=" << Livro::get_criados() << " | revistas vivos=" << Revista::get_vivos()
            << " criados=" << Revista::get_criados() << " | dvds vivos=" << Dvd::get_vivos()
            << " criados=" << Dvd::get_criados() << " | total vivos=" << vivos_total() << "\n";
}

const char* sim_nao(bool valor) { return valor ? "ok" : "recusado"; }

}  // namespace

int main() {
  {  // escopo do acervo: ao fechar a chave, o acervo destrói todos os itens
    Acervo acervo;

    std::cout << "=== 1. o acervo polimorfico ===\n";
    acervo += std::make_unique<Livro>("Dom Casmurro", 1899, "Machado de Assis");
    acervo += std::make_unique<Revista>("Revista Piaui", 2024, 218);
    acervo += std::make_unique<Dvd>("Central do Brasil", 1998, 113);

    // Percorrido por referência const à base: ficha() chama as virtuais de
    // cada tipo, sem perguntar qual é o tipo de ninguém.
    const Acervo& consulta = acervo;
    for (const std::unique_ptr<ItemAcervo>& item : consulta) {
      std::cout << "  " << item->ficha() << "\n";
    }
    for (const auto& item : acervo) {
      item->emprestar();
    }
    std::cout << "  -- depois de emprestar todos --\n";
    for (const auto& item : consulta) {
      std::cout << "  " << *item << "\n";
    }

    std::cout << "\n=== 2. os operadores ===\n";
    auto novo = std::make_unique<Livro>("Vidas Secas", 1938, "Graciliano Ramos");
    Livro& vidas_secas = *novo;  // observador: a posse vai para o acervo logo abaixo
    (acervo += std::move(novo)) += std::make_unique<Livro>("A Hora da Estrela", 1977,
                                                            "Clarice Lispector");
    std::cout << "  += encadeado: o acervo agora tem " << acervo.size() << " itens\n";
    std::cout << "  << no novo livro: " << vidas_secas << "\n";

    try {
      acervo += nullptr;
    } catch (const std::invalid_argument& erro) {
      std::cout << "  += com nullptr rejeitado: " << erro.what() << "\n";
    }

    std::cout << "  renovar sem emprestar: " << sim_nao(vidas_secas.renovar()) << "\n";
    vidas_secas.emprestar();
    std::cout << "  renovar 1: " << sim_nao(vidas_secas.renovar()) << "\n";
    std::cout << "  renovar 2: " << sim_nao(vidas_secas.renovar()) << "\n";
    std::cout << "  renovar 3: " << sim_nao(vidas_secas.renovar()) << "\n";
    std::cout << "  " << vidas_secas << "\n";
    vidas_secas.devolver();
    std::cout << "  apos devolver: " << vidas_secas << "\n";

    std::cout << "\n=== 3. os contadores ===\n";
    imprimir_contadores("dentro do escopo");
  }
  imprimir_contadores("depois do escopo");
  std::cout << "vivos=" << vivos_total() << "\n";
  return 0;
}
