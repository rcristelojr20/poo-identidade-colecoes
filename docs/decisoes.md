# Previsões, evidências e decisões

Preencha antes e depois da execução. Explique com suas palavras; resultados de testes sozinhos não respondem às perguntas.

## Etapa 01 — reconhecer e cadastrar (até 300 palavras)

| Situação | Minha previsão antes de executar | Evidência observada e explicação |
|---|---|---|
| Duas instâncias com LT-101: identidade e igualdade | preencher | preencher |
| Inserir 12% e depois 99% com a mesma tag | preencher | preencher |
| Buscar outra instância da mesma tag | preencher | preencher |
| Buscar chave ausente e consultar leitura zero | preencher | preencher |

1. De onde vêm os dois `second` do C++? Por que o `map` precisa de ordem e o `dict` precisa de hash e igualdade?
2. Qual comportamento mudaria se cada tentativa sobrescrevesse o cadastro? Em que requisito essa alternativa seria adequada?
3. Por que um conjunto de tags não substitui o catálogo de medições? Hashes diferentes para objetos iguais seriam aceitáveis?

## Etapa 02 — remover, consultar e pensar na memória (até 350 palavras)

| Situação | Minha previsão | Evidência C++ e Python |
|---|---|---|
| Remover chave existente duas vezes | preencher | preencher |
| Consultar 0, 2 e 100 últimas leituras de [12, 12, 15] | preencher | preencher |
| Limpar a coleção devolvida e consultar novamente | preencher | preencher |
| Remover cadastro e consultar histórico independente | preencher | preencher |

1. Descreva seu algoritmo para `ultimas`, sobretudo o caso zero. Cite a decisão de fronteira que precisou adaptar em cada linguagem.
2. A consulta limita a memória do histórico? Para apenas exibir os últimos dez valores, quando bastaria esta consulta e quando seria necessário descartar dados antigos? O que se perde ao descartar?
3. Compare posse e referências: se o chamador ainda tem uma medição Python, apagar a entrada do catálogo a destrói? E um ponteiro C++ para uma entrada removida pode continuar sendo usado?
4. Escolha uma alternativa rejeitada (eliminar repetições, retornar a coleção interna, ordenar por valor ou guardar apenas uma soma). Indique qual requisito ela violaria e um cenário em que seria útil.

## Evidências da entrega

- Comando local, resultado e commit testado:
- URL da execução de Actions desse commit:
- Um diagnóstico de falha encontrado e como o corrigiu:
- Limite observado dos testes: o que ainda exige inspeção/explicação?
