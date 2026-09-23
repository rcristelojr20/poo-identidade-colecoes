# Contrato da prática

## 1. Identificação — código fornecido

A tag não pode ser vazia, distingue maiúsculas e é única dentro de uma estação. Duas instâncias da mesma tag são iguais. Não normalizar, não comparar pelo endereço e não usar leitura/unidade como chave.

C++: `operator<` organiza o `map`, `operator==` expressa igualdade, `HashId` permite experimentar `unordered_set`. Python: `dataclass(frozen=True)` produz igualdade e hash pela string e bloqueia reatribuição usual. Hashes de chaves diferentes não precisam ser diferentes.

## 2. Catálogo — etapas 01 e 02

| Operação | Resultado | Estado depois |
|---|---|---|
| inserir tag nova | true / True | uma nova entrada |
| inserir outra instância de tag existente | false / False | primeiro valor e unidade preservados |
| buscar existente | ponteiro const / referência ao item | inalterado |
| buscar ausente | nullptr / None | inalterado; não cria chave |
| remover existente | true / True | exclui só a entrada correspondente |
| remover ausente ou repetir remoção | false / False | inalterado |
| reinserir após remover | true / True | armazena o novo item |

A quantidade conta chaves; `ids` devolve o conjunto atual das chaves. Não exigir a mesma ordem de iteração entre C++ e Python. O tipo `T` permite também textos, não somente medições. No contrato Python, `None` não é item válido: fica reservado à ausência, sem validação de tipos na execução.

C++: não usar o ponteiro retornado depois da remoção de sua entrada ou destruição do catálogo. Python: uma referência externa a uma medição pode continuar existindo após a remoção da entrada. Alterar ou remover um cadastro não comanda equipamentos físicos.

## 3. Histórico de um sensor — etapa 02

`registrar` e `quantidade` estão prontos. A sequência guarda todas as ocorrências, inclusive medições iguais. Implemente `ultimas(limite)`:

- devolve no máximo `limite` leituras mais recentes, **na ordem de chegada**;
- limite zero ou histórico vazio: coleção vazia;
- limite maior que a quantidade: devolve todas;
- preserva repetições e unidades;
- não remove nem reordena a coleção original;
- devolve um novo vetor/lista: alterar essa coleção retornada não altera o histórico;
- C++ contém valores copiados; Python mantém referências às mesmas medições imutáveis;
- limite negativo não faz parte do domínio: C++ recebe `std::size_t`; Python já tem a rejeição fornecida.

Para `[12 %, 12 %, 15 %]`, `ultimas(2)` devolve `[12 %, 15 %]` e a quantidade original continua 3. Essa consulta **não limita o crescimento do histórico**. Implementar descarte de antigos mudaria o contrato e não é parte desta entrega.

A remoção do catálogo não apaga o histórico independente. Uma coleção recém-criada nasce vazia: nada é recuperado automaticamente entre execuções.
