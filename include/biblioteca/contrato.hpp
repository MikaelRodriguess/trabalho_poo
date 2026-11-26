#pragma once

// O contrato do desenho, verificado pelo compilador. Se alguma afirmação
// deixar de valer, o projeto não compila.

#include <memory>
#include <type_traits>
#include <vector>

#include "biblioteca/acervo.hpp"
#include "biblioteca/dvd.hpp"
#include "biblioteca/item_acervo.hpp"
#include "biblioteca/livro.hpp"
#include "biblioteca/renovavel.hpp"
#include "biblioteca/revista.hpp"

// (a) R5: a base é abstrata
static_assert(std::is_abstract_v<biblioteca::ItemAcervo>,
              "R5: ItemAcervo deve ser abstrata (nao existe item generico na estante)");

// (b) R5: a base tem destrutor virtual
static_assert(std::has_virtual_destructor_v<biblioteca::ItemAcervo>,
              "R5: ItemAcervo precisa de destrutor virtual (destruida via unique_ptr<ItemAcervo>)");

// (c) R5: a base não é copiável
static_assert(!std::is_copy_constructible_v<biblioteca::ItemAcervo>,
              "R5: ItemAcervo nao pode ter construtor de copia");
static_assert(!std::is_copy_assignable_v<biblioteca::ItemAcervo>,
              "R5: ItemAcervo nao pode ter operator= de copia");

// (d) R6: a interface pura não tem dado algum (só o ponteiro da vtable)
static_assert(sizeof(biblioteca::Renovavel) == sizeof(void*),
              "R6: Renovavel nao pode ter dados, apenas o ponteiro da vtable");
static_assert(std::is_abstract_v<biblioteca::Renovavel> &&
                  std::has_virtual_destructor_v<biblioteca::Renovavel>,
              "R6: Renovavel deve ser abstrata e ter destrutor virtual");

// (e) R7: as concretas não são abstratas e são final
static_assert(!std::is_abstract_v<biblioteca::Livro> && std::is_final_v<biblioteca::Livro>,
              "R7: Livro deve ser concreta e final");
static_assert(!std::is_abstract_v<biblioteca::Revista> && std::is_final_v<biblioteca::Revista>,
              "R7: Revista deve ser concreta e final");
static_assert(!std::is_abstract_v<biblioteca::Dvd> && std::is_final_v<biblioteca::Dvd>,
              "R7: Dvd deve ser concreta e final");

// (f) R7: as concretas convertem para a base (herança pública)
static_assert(std::is_convertible_v<biblioteca::Livro*, biblioteca::ItemAcervo*>,
              "R7: Livro* deve converter para ItemAcervo* (heranca publica)");
static_assert(std::is_convertible_v<biblioteca::Revista*, biblioteca::ItemAcervo*>,
              "R7: Revista* deve converter para ItemAcervo* (heranca publica)");
static_assert(std::is_convertible_v<biblioteca::Dvd*, biblioteca::ItemAcervo*>,
              "R7: Dvd* deve converter para ItemAcervo* (heranca publica)");

// (g) R8: Livro deriva das duas bases, ambas publicamente
static_assert(std::is_base_of_v<biblioteca::ItemAcervo, biblioteca::Livro>,
              "R8: Livro deve derivar de ItemAcervo");
static_assert(std::is_base_of_v<biblioteca::Renovavel, biblioteca::Livro>,
              "R8: Livro deve derivar de Renovavel");
static_assert(std::is_convertible_v<biblioteca::Livro*, biblioteca::Renovavel*>,
              "R8: Livro* deve converter para Renovavel* (heranca publica)");

// (h) R9: Acervo deriva do vector, mas não converte para ele (herança privada)
static_assert(std::is_base_of_v<std::vector<std::unique_ptr<biblioteca::ItemAcervo>>,
                                biblioteca::Acervo>,
              "R9: Acervo deve derivar de std::vector<std::unique_ptr<ItemAcervo>>");
static_assert(!std::is_convertible_v<biblioteca::Acervo*,
                                     std::vector<std::unique_ptr<biblioteca::ItemAcervo>>*>,
              "R9: Acervo* NAO pode converter para vector* (a heranca deve ser privada)");
