#pragma once
#include "identidade.hpp"
#include <map>
#include <set>

struct Medicao {
    double valor;
    std::string unidade;
};

// Fornecido: T varia o item, preservando a chave e o contrato do catálogo.
template<typename T>
class Catalogo {
    std::map<IdSensor, T> itens_;
public:
    bool inserir(const IdSensor& id, const T& item) {
        // TODO 01: inserir somente quando a chave ainda não existir.
        (void)id;
        (void)item;
        return false;
    }
    const T* buscar(const IdSensor& id) const {
        // TODO 01: localizar sem criar entrada; nullptr indica ausência.
        (void)id;
        return nullptr;
    }
    bool remover(const IdSensor& id) {
        // TODO 02: true somente quando uma entrada for removida.
        (void)id;
        return false;
    }
    std::size_t quantidade() const { return itens_.size(); }
    std::set<IdSensor> ids() const {
        std::set<IdSensor> resultado;
        for (const auto& entrada : itens_) resultado.insert(entrada.first);
        return resultado;
    }
};
