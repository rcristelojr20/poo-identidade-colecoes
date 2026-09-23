from dataclasses import dataclass
from typing import Generic, TypeVar
from identidade import IdSensor


@dataclass(frozen=True)
class Medicao:
    valor: float
    unidade: str


T = TypeVar("T")


class Catalogo(Generic[T]):
    def __init__(self):
        self._itens: dict[IdSensor, T] = {}

    def inserir(self, id: IdSensor, item: T) -> bool:
        # TODO 01: recusar duplicata e preservar o primeiro item.
        return False

    def buscar(self, id: IdSensor) -> T | None:
        # TODO 01: consultar sem criar entrada; None indica ausência.
        return None

    def remover(self, id: IdSensor) -> bool:
        # TODO 02: True somente quando uma entrada for removida.
        return False

    def quantidade(self):
        return len(self._itens)

    def ids(self):
        return set(self._itens)
