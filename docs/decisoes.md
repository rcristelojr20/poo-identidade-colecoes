# Previsões, evidências e decisões

## Etapa 01 — reconhecer e cadastrar

| Situação | Minha previsão antes de executar | Evidência observada e explicação |
|---|---|---|
| Duas instâncias com LT-101: identidade e igualdade | Achei que seriam instâncias diferentes, mas iguais por terem a mesma tag. | Apareceu `Mesma instancia: false` e `Iguais: true`. Então são objetos diferentes, mas representam o mesmo sensor. |
| Inserir 12% e depois 99% com a mesma tag | A primeira inserção deveria funcionar e a segunda ser recusada. | Apareceu `Primeira: true`, `Duplicada: false` e `Preservada: 12 %`. A segunda não substituiu a primeira. |
| Buscar outra instância da mesma tag | Deveria encontrar o cadastro já existente. | A busca usa a tag para encontrar o cadastro, mesmo sendo outra instância. |
| Buscar chave ausente e consultar leitura zero | Uma chave que não existe deveria ser diferente de uma leitura com valor zero. | A chave ausente retorna ausência, enquanto zero pode ser uma leitura válida. |

### 1. De onde vêm os dois `second` do C++? Por que o `map` precisa de ordem e o `dict` precisa de hash e igualdade?

No `emplace`, o `second` diz se a inserção deu certo. No `map`, o `second` de uma entrada representa o valor guardado. O `map` organiza as chaves por ordem, enquanto o `dict` usa hash e igualdade para encontrar as chaves.

### 2. Qual comportamento mudaria se cada tentativa sobrescrevesse o cadastro? Em que requisito essa alternativa seria adequada?

A segunda inserção substituiria a primeira. Nesse caso, 99% substituiria 12%. Isso seria adequado se o objetivo fosse sempre atualizar o valor de um cadastro existente.

### 3. Por que um conjunto de tags não substitui o catálogo de medições? Hashes diferentes para objetos iguais seriam aceitáveis?

Um conjunto guarda apenas as tags, enquanto o catálogo também guarda as medições. Por isso, o conjunto não substitui o catálogo. Objetos iguais devem ter o mesmo hash quando são usados como chaves.

## Etapa 02 — remover, consultar e pensar na memória

| Situação | Minha previsão | Evidência C++ e Python |
|---|---|---|
| Remover chave existente duas vezes | A primeira remoção deveria retornar true e a segunda false. | A remoção funcionou e o cadastro foi retirado. |
| Consultar 0, 2 e 100 últimas leituras de [12, 12, 15] | 0 deveria retornar vazio, 2 deveria retornar as duas últimas e 100 deveria retornar todas. | Os testes da Etapa 02 passaram para C++ e Python. |
| Limpar a coleção devolvida e consultar novamente | Limpar o resultado não deveria apagar o histórico original. | `ultimas` retorna uma nova coleção, mantendo o histórico original. |
| Remover cadastro e consultar histórico independente | Remover o cadastro não deveria apagar o histórico. | A saída mostrou `Removida: true | Historico preservado: 3`. |

### 1. Descreva seu algoritmo para `ultimas`, sobretudo o caso zero. Cite a decisão de fronteira que precisou adaptar em cada linguagem.

Primeiro verifico se o limite é zero e retorno uma coleção vazia. Depois, se o limite for maior que a quantidade de leituras, retorno todas. Caso contrário, retorno somente as últimas leituras. No Python precisei tratar limites negativos, pois eles têm um comportamento diferente no fatiamento de listas.

### 2. A consulta limita a memória do histórico? Para apenas exibir os últimos dez valores, quando bastaria esta consulta e quando seria necessário descartar dados antigos? O que se perde ao descartar?

Não. A consulta apenas pega as últimas leituras e mantém o histórico completo. Para apenas exibir os últimos dez valores, a consulta já é suficiente. Seria necessário descartar dados antigos se o objetivo fosse limitar o tamanho da memória. Nesse caso, perderíamos as leituras mais antigas.

### 3. Compare posse e referências: se o chamador ainda tem uma medição Python, apagar a entrada do catálogo a destrói? E um ponteiro C++ para uma entrada removida pode continuar sendo usado?

Apagar a entrada do catálogo Python não destrói necessariamente a medição se ainda existir outra referência para ela. No C++, um ponteiro para uma entrada removida não deve continuar sendo usado, pois a entrada deixou de existir no catálogo.

### 4. Escolha uma alternativa rejeitada (eliminar repetições, retornar a coleção interna, ordenar por valor ou guardar apenas uma soma). Indique qual requisito ela violaria e um cenário em que seria útil.

Escolhi retornar a coleção interna. Isso violaria o requisito de que a consulta deve devolver uma coleção independente, pois o chamador poderia alterar diretamente o histórico. Essa alternativa poderia ser útil em um sistema interno em que fosse permitido modificar diretamente a coleção original.