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