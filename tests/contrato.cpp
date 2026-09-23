#include "colecoes.hpp"
#include "historico.hpp"
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <vector>

void exigir(bool condicao, const std::string& mensagem) {
    if (!condicao) throw std::runtime_error(mensagem);
}
void base() {
    IdSensor a{"LT-101"}, b{"LT-101"}, diferente{"LT-102"}, minuscula{"lt-101"};
    const IdSensor& alias = a;
    exigir(&a != &b && &a == &alias, "00: distinguir identidade e alias");
    exigir(a == b && b == a && a == a && !(a == diferente), "00: igualdade pela tag");
    exigir(!(a == minuscula), "00: preservar maiusculas na tag exata");
    exigir(!(a < b) && !(b < a), "00: chaves iguais devem ser equivalentes no mapa");
    exigir(HashId{}(a) == HashId{}(b), "00: iguais exigem hashes iguais");
    std::unordered_set<IdSensor, HashId> unicos{a, b, diferente};
    exigir(unicos.size() == 2, "00: conjunto deve reunir dois valores distintos");
    bool rejeitou = false;
    try { IdSensor vazio{""}; } catch (const std::invalid_argument&) { rejeitou = true; }
    exigir(rejeitou, "00: recusar tag vazia");
    Historico h;
    exigir(h.quantidade() == 0, "00: historico nasce vazio");
    h.registrar({12, "%"}); h.registrar({12, "%"});
    exigir(h.quantidade() == 2, "00: historico deve guardar ocorrencias repetidas");
    Catalogo<Medicao> c;
    exigir(c.quantidade() == 0 && c.ids().empty(), "00: catalogo nasce vazio");
}
void catalogo() {
    Catalogo<Medicao> c;
    exigir(c.buscar(IdSensor{"ausente"}) == nullptr && c.quantidade() == 0,
           "01: buscar no vazio deve retornar nullptr sem criar entrada");
    exigir(c.inserir(IdSensor{"LT-101"}, {12, "%"}),
           "01: primeira insercao deve retornar true; complete inserir");
    exigir(!c.inserir(IdSensor{"LT-101"}, {99, "%"}), "01: recusar outra instancia da mesma tag");
    const auto* m = c.buscar(IdSensor{"LT-101"});
    exigir(m != nullptr, "01: buscar pela tag equivalente deve encontrar; complete buscar");
    exigir(m->valor == 12 && m->unidade == "%", "01: duplicata deve preservar valor E unidade originais");
    exigir(!c.inserir(IdSensor{"LT-101"}, {800, "cm"}), "01: mudar unidade nao cria nova chave");
    exigir(c.buscar(IdSensor{"LT-101"})->unidade == "%", "01: unidade original preservada");
    exigir(c.inserir(IdSensor{"LT-102"}, {0, "%"}), "01: aceitar segunda chave com leitura zero");
    exigir(c.inserir(IdSensor{"lt-101"}, {7, "%"}), "01: tag minuscula e distinta");
    exigir(c.quantidade() == 3 && c.ids().size() == 3, "01: contar chaves, nao tentativas");
    exigir(c.buscar(IdSensor{"LT-102"})->valor == 0, "01: zero nao representa ausencia");
    exigir(c.buscar(IdSensor{"outra"}) == nullptr && c.quantidade() == 3,
           "01: busca ausente nao pode alterar quantidade");
    exigir(c.ids().count(IdSensor{"LT-101"}) == 1, "01: conjunto de ids acompanha o mapa");
    Catalogo<Medicao> independente;
    exigir(independente.quantidade() == 0, "01: catalogos nao compartilham armazenamento");
    Catalogo<std::string> nomes;
    exigir(nomes.inserir(IdSensor{"X"}, "Bancada A"), "01: genericidade deve aceitar texto");
    const auto* nome = nomes.buscar(IdSensor{"X"});
    exigir(nome && *nome == "Bancada A", "01: busca generica preserva texto");
}
void ultimas(const Historico& h, std::size_t n, const std::vector<double>& valores) {
    const auto dados = h.ultimas(n);
    exigir(dados.size() == valores.size(), "02: ultimas(" + std::to_string(n) + ") retornou quantidade incorreta");
    for (std::size_t i = 0; i < dados.size(); ++i) {
        exigir(dados[i].valor == valores[i] && dados[i].unidade == "%",
               "02: ultimas deve preservar ordem de chegada, repeticoes e unidade");
    }
}
void extensao() {
    Catalogo<Medicao> c;
    exigir(!c.remover(IdSensor{"vazio"}), "02: remover no vazio deve retornar false");
    c.inserir(IdSensor{"A"}, {12, "%"}); c.inserir(IdSensor{"B"}, {20, "%"});
    exigir(!c.remover(IdSensor{"X"}) && c.quantidade() == 2, "02: remover ausente preserva as demais entradas");
    exigir(c.remover(IdSensor{"A"}), "02: remover chave existente deve retornar true; complete remover");
    exigir(c.quantidade() == 1 && c.buscar(IdSensor{"A"}) == nullptr, "02: remover deve alterar quantidade e busca");
    exigir(c.ids().count(IdSensor{"A"}) == 0 && c.ids().count(IdSensor{"B"}) == 1, "02: ids deve refletir a remocao");
    exigir(c.buscar(IdSensor{"B"}) && c.buscar(IdSensor{"B"})->valor == 20, "02: preservar outra chave");
    exigir(!c.remover(IdSensor{"A"}), "02: segunda remocao retorna false");
    exigir(c.inserir(IdSensor{"A"}, {33, "%"}), "02: permitir reinsercao depois de remover");
    exigir(c.buscar(IdSensor{"A"})->valor == 33, "02: reinsercao armazena novo valor");
    Historico h;
    ultimas(h, 0, {}); ultimas(h, 4, {});
    h.registrar({12, "%"}); h.registrar({12, "%"}); h.registrar({15, "%"});
    ultimas(h, 0, {}); ultimas(h, 1, {15}); ultimas(h, 2, {12, 15});
    ultimas(h, 3, {12, 12, 15}); ultimas(h, 100, {12, 12, 15});
    exigir(h.quantidade() == 3, "02: consultar ultimas nao pode descartar o historico");
    auto copia = h.ultimas(3);
    copia[0].valor = 999; copia.clear();
    ultimas(h, 3, {12, 12, 15});
    Medicao externa{40, "%"}; h.registrar(externa); externa.valor = 99;
    ultimas(h, 1, {40});
    exigir(c.remover(IdSensor{"A"}) && h.quantidade() == 4,
           "02: remover cadastro nao apaga ocorrencias do historico independente");
    h.registrar({5, "%"}); ultimas(h, 2, {40, 5});
}
int main(int argc, char** argv) {
    try {
        exigir(argc == 2, "informe etapa");
        const std::string etapa = argv[1];
        exigir(etapa == "00" || etapa == "01" || etapa == "02", "etapa invalida");
        base();
        if (etapa >= "01") catalogo();
        if (etapa == "02") extensao();
        std::cout << "OK C++ etapa " << etapa << '\n';
    } catch (const std::exception& e) {
        std::cerr << "FALHA C++: " << e.what() << '\n';
        return 1;
    }
}
