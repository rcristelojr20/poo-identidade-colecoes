#pragma once
#include <functional>
#include <stdexcept>
#include <string>

// Fornecido: a tag exata é o valor de identificação dentro de uma estação.
class IdSensor {
    std::string valor_;
public:
    explicit IdSensor(const std::string& valor) : valor_(valor) {
        if (valor.empty()) throw std::invalid_argument("tag vazia");
    }
    const std::string& valor() const { return valor_; }
    bool operator==(const IdSensor& outro) const { return valor_ == outro.valor_; }
    // std::map usa esta ordenação, e não operator==, para distinguir chaves.
    bool operator<(const IdSensor& outro) const { return valor_ < outro.valor_; }
};
struct HashId {
    std::size_t operator()(const IdSensor& id) const {
        return std::hash<std::string>{}(id.valor());
    }
};
