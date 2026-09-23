from colecoes import Catalogo, Medicao
from historico import Historico
from identidade import IdSensor


def main():
    a = IdSensor("LT-101")
    b = IdSensor("LT-101")
    alias = a
    print(f"Mesma instancia: {a is b} | Alias: {a is alias} | Iguais: {a == b}")
    catalogo = Catalogo[Medicao]()
    print(f"Primeira: {catalogo.inserir(a, Medicao(12, '%'))}")
    print(f"Duplicada: {catalogo.inserir(b, Medicao(99, '%'))}")
    item = catalogo.buscar(b)
    if item is not None:
        print(f"Preservada: {item.valor} {item.unidade}")
    else:
        print("PENDENTE 01: insercao/busca ainda sem comportamento")
    historico = Historico()
    for valor in (12, 12, 15):
        historico.registrar(Medicao(valor, "%"))
    recentes = historico.ultimas(2)
    print(f"Historico: {historico.quantidade()} | Recentes: {len(recentes)}")
    if not recentes:
        print("PENDENTE 02: consulta das ultimas leituras")
    else:
        for leitura in recentes:
            print(f"Recente: {leitura.valor} {leitura.unidade}")
    print(f"Removida: {catalogo.remover(b)} | Historico preservado: {historico.quantidade()}")


if __name__ == "__main__":
    main()
