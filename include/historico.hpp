#pragma once
#include "colecoes.hpp"
#include <vector>

// Histórico de UM sensor. Repetições são ocorrências, não duplicatas de cadastro.
class Historico {
    std::vector<Medicao> leituras_;
public:
    void registrar(const Medicao& leitura) { leituras_.push_back(leitura); }
    std::size_t quantidade() const { return leituras_.size(); }
    std::vector<Medicao> ultimas(std::size_t limite) const {
        // TODO 02: devolver até limite leituras, na ordem de chegada.
        // Consulta sem remoção: o histórico original deve permanecer intacto.
        (void)limite;
        return {};
    }
};
