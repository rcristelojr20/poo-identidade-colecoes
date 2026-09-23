---
layout: default
title: "Prática 11 — identidade, igualdade e coleções"
---

# Prática 11: reconhecer, guardar e consultar objetos

**Objetivos de aprendizagem**

- Diferenciar identidade, igualdade e identificação usando evidências em C++ e Python.
- Implementar o contrato de um catálogo e consultar uma sequência sem perder ocorrências.
- Justificar escolhas de retenção, imutabilidade e compartilhamento, além de executar testes.

**Tempo estimado:** 2h de prática, sendo 40 min em sala e cerca de 80 min de conclusão orientada. Os programas completos e as explicações estão na [seção 7 do capítulo 11](https://rafaelrezo.github.io/curso-poo/fundamentos_poo_cpp_python/12_igualdade_identidade/#7-aplicacao-da-comparacao-ao-catalogo). Esta atividade é independente do capítulo 12.

[Repositório-base público](https://github.com/rafaelrezo/poo-identidade-colecoes) · [Contrato completo](https://github.com/rafaelrezo/poo-identidade-colecoes/blob/main/docs/contrato.md)

## 1. O problema que vamos resolver

A estação recebe identificadores criados em momentos diferentes. Duas instâncias de `LT-101` precisam localizar o mesmo cadastro. Uma tentativa de cadastrar 99% não deve substituir a medição de 12% já registrada.

Ao mesmo tempo, o histórico de **um sensor** recebe `[12%, 12%, 15%]`: as duas ocorrências de 12% devem permanecer. O operador quer consultar as últimas leituras e remover cadastros sem apagar esse histórico independente.

| Pergunta | Estrutura fornecida | Responsabilidade do aluno |
|---|---|---|
| Qual medição está cadastrada para esta tag? | `Catalogo<T>` / `Catalogo[T]` com mapa/dicionário | inserir, buscar e remover |
| Quais foram as últimas ocorrências? | `Historico` com vetor/lista | devolver últimas leituras sem modificar o original |
| Quando duas chaves são equivalentes? | `IdSensor`, comparação, ordem e hash | ler, prever e explicar; não reimplementar |

Tudo fica em memória. Consulta das últimas leituras não é uma janela de descarte nem persistência em arquivo. Essa diferença fará parte de sua justificativa.

## 2. Preparar o próprio fork e prever o resultado

Faça **Fork** do repositório-base em sua conta. Substitua `SEU_USUARIO` nos comandos:

```bash
git clone https://github.com/SEU_USUARIO/poo-identidade-colecoes.git
cd poo-identidade-colecoes
git remote -v
git switch -c pratica/01-catalogo
make run
```

O único remoto deve ser `origin`, apontando para seu fork. Não adicione `upstream`. Requisitos: g++ com C++17, Python 3.10+, GNU Make e Git.

Antes de executar, preencha a primeira previsão de `docs/decisoes.md`: `a` e `b` têm a mesma tag; `alias` se refere a `a`. Qual comparação usa identidade e qual usa igualdade?

A base mostra `Mesma instancia: false | Alias: true | Iguais: true` em C++ e os mesmos valores com iniciais maiúsculas em Python. Também mostra `Historico: 3 | Recentes: 0` e os marcadores `PENDENTE`. O código já executa; os métodos autorais ainda não fazem o que o contrato pede.

## 3. Etapa 01 — incremento guiado: inserir e buscar

**Arquivos editáveis:** `include/colecoes.hpp` e `src/colecoes.py`. Complete apenas os dois métodos com `TODO 01`; mantenha `remover` pendente.

```bash
make test ETAPA=01
```

A primeira falha esperada é `01: primeira insercao deve retornar true/True; complete inserir`. A execução confere C++ e Python, mesmo se uma delas falhar.

### 3.1 Inserir sem sobrescrever

Retome os programas completos das seções **7.3 e 7.4 do capítulo 11**. O starter usa `T` no lugar de `Medicao`; a regra é a mesma.

1. Em C++, use `itens_.emplace(id, item)` e observe o `second` do resultado: ele informa se houve nova entrada. Preserve o armazenamento privado.
2. Em Python, consulte primeiro se `id` está em `self._itens`. Se estiver, recuse; caso contrário, armazene o item e informe sucesso. Atribuir diretamente à chave substituiria o valor anterior.
3. Execute `make test ETAPA=01`. Com a inserção correta e a busca incompleta, a próxima falha será `buscar pela tag equivalente deve encontrar; complete buscar`.

**Pense antes de editar:** o identificador da segunda inserção é outro objeto. Por que isso não autoriza um segundo cadastro? O que mudaria se a leitura participasse da chave?

### 3.2 Buscar sem criar uma entrada

1. Em C++, use `find`. Se a posição for `end()`, devolva `nullptr`; caso contrário, devolva o endereço de `it->second`. Esse segundo `second` é o item, não o booleano de inserção.
2. Em Python, consulte com `get` para obter o item ou `None` sem criar a chave.
3. Execute novamente `make test ETAPA=01` e `make run`.

Resultado: `OK etapa 01 cumulativa (C++ e Python)`. A demonstração passa a mostrar primeira inserção verdadeira, duplicada falsa e `Preservada: 12 %`. O aviso da etapa 02 ainda é esperado.

**Confirme o conceito:** explique por que leitura zero difere de ausência e por que `std::map` usa ordem enquanto `dict` usa hash e igualdade. Preencha a etapa 01 de `docs/decisoes.md` e `AI_LOG.md`.

### 3.3 Validar remotamente e integrar

```bash
git add include/colecoes.hpp src/colecoes.py docs/decisoes.md AI_LOG.md
git commit -m "implementa insercao e busca por identificador"
git push -u origin pratica/01-catalogo
```

Na aba **Actions do seu fork**, confira o workflow `Contratos C++ e Python` associado ao commit enviado: ele executa `make test ETAPA=01`. Se os workflows estiverem desativados, habilite-os e envie o próximo commit; não trate ausência de execução como aprovação.

Abra uma PR com **base: SEU_USUARIO/poo-identidade-colecoes, branch main** e **compare: pratica/01-catalogo do mesmo fork**. O GitHub pode sugerir o repositório do docente: altere a base antes de criar. Inclua saída local e URL da execução de Actions. Revise o diff e integre somente após a etapa 01 passar.

## 4. Etapa 02 — extensão: remover e consultar sem perder dados

Atualize a main do próprio fork e crie a segunda branch:

```bash
git switch main
git pull --ff-only origin main
git switch -c pratica/02-historico
make test ETAPA=02
```

A etapa 02 repete os contratos de identificação e catálogo. Com a etapa 01 concluída, a primeira pendência será a remoção de uma chave existente.

### 4.1 Remover uma entrada

Complete `remover` nos mesmos arquivos da etapa 01. Consulte a documentação das operações de remoção da coleção escolhida e decida como converter seu resultado em sucesso/ausência. Não altere `IdSensor`, assinaturas ou infraestrutura genérica.

| Situação | Resultado exigido |
|---|---|
| Remover de catálogo vazio | falso; permanece vazio |
| Remover chave existente por outra instância equivalente | verdadeiro; quantidade diminui e busca passa a indicar ausência |
| Remover outra vez | falso; demais entradas preservadas |
| Inserir novamente a chave removida | verdadeiro; novo item armazenado |

**Preveja:** a chave removida deve continuar em `ids()`? O que acontece a um ponteiro C++ para a entrada apagada? Compare com uma referência Python ao registro imutável.

### 4.2 Consultar as últimas ocorrências

Complete `ultimas` em `include/historico.hpp` e `src/historico.py`. O método retorna uma coleção independente com até `limite` leituras recentes, **na ordem em que chegaram**. Não modifica o histórico e não elimina repetições.

| Histórico | Limite | Retorno | Quantidade original depois |
|---|---:|---|---:|
| vazio | 2 | vazio | 0 |
| 12%, 12%, 15% | 0 | vazio | 3 |
| 12%, 12%, 15% | 1 | 15% | 3 |
| 12%, 12%, 15% | 2 | 12%, 15% | 3 |
| 12%, 12%, 15% | 100 | 12%, 12%, 15% | 3 |

A rejeição de limite negativo em Python está fornecida; C++ recebe `std::size_t`. Escolha seu algoritmo e confira as fronteiras antes de acessar posições. Os testes também verificam se alterar a coleção devolvida preserva o histórico. C++ copia os registros; Python pode compartilhar as medições imutáveis, mas deve devolver outra lista.

**Decisão crítica:** mostrar as últimas dez leituras limita a memória usada pelo histórico? Se o requisito mudasse para reter somente dez, qual operação teria de mudar e que informação seria perdida? Responda sem implementar esse descarte, pois ele violaria o contrato atual.

### 4.3 Confirmar o comportamento e entregar

```bash
make run
make test ETAPA=02
```

A demonstração final mostra `Historico: 3 | Recentes: 2`, as leituras 12% e 15%, e remoção verdadeira com histórico ainda contendo três ocorrências. Os testes encerram com `OK etapa 02 cumulativa (C++ e Python)`.

Preencha as previsões/evidências da etapa 02, registre uma alternativa rejeitada e atualize a rastreabilidade. Faça commits pequenos quando houver avanços verificáveis. Ao concluir:

```bash
git add include/colecoes.hpp src/colecoes.py include/historico.hpp src/historico.py docs/decisoes.md AI_LOG.md
git commit -m "remove cadastros e consulta ultimas leituras sem perder historico"
git push -u origin pratica/02-historico
```

Abra a segunda PR para a **main do próprio fork**. A CI desta branch executa `make test ETAPA=02`. Integre após revisar o diff e obter os testes verdes. O capítulo 12 trata de modelagem; não há implementação de UML necessária para concluir esta prática.

## 5. Evidências e limites

- [ ] As duas linguagens atendem aos mesmos contratos e às fronteiras.
- [ ] Cada PR aponta para o próprio fork e inclui validação local e remota do commit.
- [ ] `docs/decisoes.md` distingue previsão, observação e justificativa.
- [ ] `AI_LOG.md` registra pedidos, decisões e verificações, ou ausência de IA.
- [ ] O aluno explica identidade/igualdade, hash, duplicatas e retenção em memória.

A main roda apenas a verificação da base (`ETAPA=00`), adequada ao starter incompleto. A conclusão é demonstrada nas PRs das etapas 01 e 02. Testes visíveis não comprovam autoria nem entendimento: revisão do diff e explicação técnica complementam a CI. Em avaliação, haverá defesa oral curta.

## 6. Diagnóstico rápido

| Sintoma | Confira |
|---|---|
| Primeira inserção continua falsa | se editou o arquivo da linguagem indicada pelo diagnóstico |
| 99% substituiu 12% | se a duplicata foi recusada antes da atribuição |
| Busca ausente aumentou a quantidade | se usou uma operação que cria entrada |
| `ultimas(0)` devolveu tudo | se tratou explicitamente a fronteira zero |
| Limpar o retorno apagou o histórico | se devolveu a própria coleção interna |
| Etapa 01 regrediu ao fazer a 02 | se alterou comparação ou comportamento já aprovado |
| CI não executou | nome exato da branch, Actions habilitado e push no próprio fork |

## Referências

- [C++ — map::emplace](https://en.cppreference.com/w/cpp/container/map/emplace), [map::find](https://en.cppreference.com/w/cpp/container/map/find) e [map::erase](https://en.cppreference.com/w/cpp/container/map/erase).
- [C++ — vector](https://en.cppreference.com/w/cpp/container/vector).
- [Python — dataclasses](https://docs.python.org/3/library/dataclasses.html), [sequências e mapeamentos](https://docs.python.org/3/library/stdtypes.html).
- [GitHub — criar PR a partir de um fork](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request-from-a-fork).
