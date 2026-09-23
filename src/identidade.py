from dataclasses import dataclass


# Fornecido: igualdade e hash pela tag, sem reatribuição usual do campo.
@dataclass(frozen=True)
class IdSensor:
    valor: str

    def __post_init__(self):
        if not self.valor:
            raise ValueError("tag vazia")
