#include "colecoes.hpp"
#include "historico.hpp"
#include <iostream>

int main() {
    IdSensor a{"LT-101"}, b{"LT-101"};
    const IdSensor& alias = a;
    std::cout << std::boolalpha;
    std::cout << "Mesma instancia: " << (&a == &b) << " | Alias: " << (&a == &alias)
              << " | Iguais: " << (a == b) << '\n';
    Catalogo<Medicao> catalogo;
    std::cout << "Primeira: " << catalogo.inserir(a, {12, "%"}) << '\n';
    std::cout << "Duplicada: " << catalogo.inserir(b, {99, "%"}) << '\n';
    const auto* item = catalogo.buscar(b);
    if (item) std::cout << "Preservada: " << item->valor << ' ' << item->unidade << '\n';
    else std::cout << "PENDENTE 01: insercao/busca ainda sem comportamento\n";
    Historico historico;
    for (double valor : {12.0, 12.0, 15.0}) historico.registrar({valor, "%"});
    const auto recentes = historico.ultimas(2);
    std::cout << "Historico: " << historico.quantidade() << " | Recentes: " << recentes.size() << '\n';
    if (recentes.empty()) std::cout << "PENDENTE 02: consulta das ultimas leituras\n";
    else for (const auto& leitura : recentes) std::cout << "Recente: " << leitura.valor << ' ' << leitura.unidade << '\n';
    std::cout << "Removida: " << catalogo.remover(b) << " | Historico preservado: " << historico.quantidade() << '\n';
}
