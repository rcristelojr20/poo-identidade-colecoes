from dataclasses import FrozenInstanceError
import sys
from colecoes import Catalogo, Medicao
from historico import Historico
from identidade import IdSensor


def exigir(condicao, mensagem):
    if not condicao:
        raise AssertionError(mensagem)


def base():
    a, b, diferente = IdSensor("LT-101"), IdSensor("LT-101"), IdSensor("LT-102")
    alias = a
    exigir(a is not b and alias is a, "00: distinguir identidade e alias")
    exigir(a == b and b == a and a == a and a != diferente, "00: igualdade pela tag")
    exigir(a != IdSensor("lt-101"), "00: preservar maiusculas")
    exigir(hash(a) == hash(b), "00: iguais exigem hashes iguais")
    exigir(len({a, b, diferente}) == 2, "00: conjunto deve reunir dois valores distintos")
    try:
        IdSensor("")
    except ValueError:
        pass
    else:
        raise AssertionError("00: recusar tag vazia")
    try:
        a.valor = "outra"
    except FrozenInstanceError:
        pass
    else:
        raise AssertionError("00: chave deve impedir reatribuicao usual")
    h = Historico()
    exigir(h.quantidade() == 0, "00: historico nasce vazio")
    h.registrar(Medicao(12, "%")); h.registrar(Medicao(12, "%"))
    exigir(h.quantidade() == 2, "00: preservar ocorrencias repetidas")
    c = Catalogo[Medicao]()
    exigir(c.quantidade() == 0 and c.ids() == set(), "00: catalogo nasce vazio")


def catalogo():
    c = Catalogo[Medicao]()
    exigir(c.buscar(IdSensor("ausente")) is None and c.quantidade() == 0,
           "01: buscar no vazio deve retornar None sem criar entrada")
    exigir(c.inserir(IdSensor("LT-101"), Medicao(12, "%")) is True,
           "01: primeira insercao deve retornar True; complete inserir")
    exigir(c.inserir(IdSensor("LT-101"), Medicao(99, "%")) is False,
           "01: recusar outra instancia da mesma tag")
    m = c.buscar(IdSensor("LT-101"))
    exigir(m is not None, "01: buscar pela tag equivalente deve encontrar; complete buscar")
    exigir(m == Medicao(12, "%"), "01: duplicata deve preservar valor E unidade originais")
    exigir(c.inserir(IdSensor("LT-101"), Medicao(800, "cm")) is False, "01: mudar unidade nao cria nova chave")
    exigir(c.buscar(IdSensor("LT-101")).unidade == "%", "01: unidade original preservada")
    exigir(c.inserir(IdSensor("LT-102"), Medicao(0, "%")) is True, "01: aceitar leitura zero")
    exigir(c.inserir(IdSensor("lt-101"), Medicao(7, "%")) is True, "01: tag minuscula e distinta")
    exigir(c.quantidade() == 3 and len(c.ids()) == 3, "01: contar chaves, nao tentativas")
    exigir(c.buscar(IdSensor("LT-102")).valor == 0, "01: zero nao representa ausencia")
    exigir(c.buscar(IdSensor("outra")) is None and c.quantidade() == 3, "01: busca ausente nao altera quantidade")
    exigir(IdSensor("LT-101") in c.ids(), "01: conjunto de ids acompanha o mapa")
    exigir(Catalogo().quantidade() == 0, "01: catalogos nao compartilham armazenamento")
    nomes = Catalogo[str]()
    exigir(nomes.inserir(IdSensor("X"), "Bancada A") is True, "01: genericidade deve aceitar texto")
    exigir(nomes.buscar(IdSensor("X")) == "Bancada A", "01: busca generica preserva texto")


def ultimas(h, n, valores):
    dados = h.ultimas(n)
    exigir(isinstance(dados, list), "02: ultimas deve devolver uma lista independente")
    exigir(dados == [Medicao(v, "%") for v in valores],
           f"02: ultimas({n}) deve retornar valores {valores}, na ordem de chegada, com unidade %")


def extensao():
    c = Catalogo[Medicao]()
    exigir(c.remover(IdSensor("vazio")) is False, "02: remover no vazio retorna False")
    c.inserir(IdSensor("A"), Medicao(12, "%")); c.inserir(IdSensor("B"), Medicao(20, "%"))
    exigir(c.remover(IdSensor("X")) is False and c.quantidade() == 2, "02: ausente preserva entradas")
    exigir(c.remover(IdSensor("A")) is True, "02: remover existente deve retornar True; complete remover")
    exigir(c.quantidade() == 1 and c.buscar(IdSensor("A")) is None, "02: atualizar quantidade e busca")
    exigir(c.ids() == {IdSensor("B")}, "02: ids deve refletir remocao")
    exigir(c.buscar(IdSensor("B")) == Medicao(20, "%"), "02: preservar outra chave")
    exigir(c.remover(IdSensor("A")) is False, "02: segunda remocao retorna False")
    exigir(c.inserir(IdSensor("A"), Medicao(33, "%")) is True, "02: permitir reinsercao")
    exigir(c.buscar(IdSensor("A")).valor == 33, "02: reinsercao guarda novo valor")
    h = Historico()
    ultimas(h, 0, []); ultimas(h, 4, [])
    for valor in (12, 12, 15):
        h.registrar(Medicao(valor, "%"))
    for n, esperados in [(0, []), (1, [15]), (2, [12, 15]), (3, [12, 12, 15]), (100, [12, 12, 15])]:
        ultimas(h, n, esperados)
    exigir(h.quantidade() == 3, "02: consultar nao descarta historico")
    copia = h.ultimas(3)
    copia[0] = Medicao(999, "%"); copia.clear()
    ultimas(h, 3, [12, 12, 15])
    externa = Medicao(40, "%"); h.registrar(externa)
    exigir(h.ultimas(1)[0] is externa, "02: Python guarda referencias aos registros imutaveis")
    try:
        externa.valor = 99
    except FrozenInstanceError:
        pass
    else:
        raise AssertionError("02: Medicao deve manter campos imutaveis")
    exigir(c.remover(IdSensor("A")) is True and h.quantidade() == 4,
           "02: remover cadastro nao apaga historico independente")
    h.registrar(Medicao(5, "%")); ultimas(h, 2, [40, 5])
    try:
        h.ultimas(-1)
    except ValueError:
        pass
    else:
        raise AssertionError("02: preservar rejeicao fornecida para limite negativo")


def main():
    etapa = sys.argv[1]
    exigir(etapa in ("00", "01", "02"), "etapa invalida")
    base()
    if etapa >= "01":
        catalogo()
    if etapa == "02":
        extensao()
    print(f"OK Python etapa {etapa}")


if __name__ == "__main__":
    try:
        main()
    except Exception as erro:
        print(f"FALHA Python: {erro}", file=sys.stderr)
        raise SystemExit(1)
