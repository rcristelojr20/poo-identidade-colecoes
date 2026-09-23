# Operação e avaliação — capítulo 11

## Recorte e tempo

Uma prática independente, com dois incrementos em branches cumulativas e duas PRs no próprio fork. Estimativa: 15 min de previsão/preparo, 35 min no incremento guiado, 45 min na extensão e 25 min para justificativa, testes e revisão (120 min; 40 em sala e 80 externos). Calibrar com a turma; evitar acrescentar arquivos/banco, normalização de tags ou implementação de estruturas de dados.

O capítulo 12 trabalha modelagem e não exige completar código adicional. O starter não depende da prática A nem de forks antigos. As assinaturas de `Catalogo<T>`/`Catalogo[T]` são compatíveis com o starter de fundamentos da Parte 2; a transferência se limita aos três métodos, conforme o curso.

## Estado esperado

- `make run`: compila e executa, exibindo pendências explícitas.
- `make test ETAPA=00`: base fornecida passa em C++ e Python.
- Starter com ETAPA=01 ou 02: falha na primeira inserção em ambas as linguagens.
- Após implementar inserir/buscar: 01 passa; 02 aponta remoção incompleta.
- Após implementar remover: 02 aponta últimas leituras.
- Após completar a extensão: 02 passa e repete os contratos de 00 e 01.

Não há solução de referência neste repositório, em branches, tags ou no histórico. Validar em cópia local separada antes de publicar atualizações. O guia público orienta o incremento 01 com os programas do curso; a extensão apresenta contratos e perguntas, sem algoritmo pronto.

## CI e Pages

Workflow `contratos.yml`: push das branches previstas e PR para main; etapa selecionada pela branch de origem, nunca por título ou mensagem de commit. Branch desconhecida em PR falha com orientação. Usa `contents: read`, checkout sem credenciais persistidas e sem secrets. Executa exatamente `make test ETAPA=01` ou `02` e também a demonstração.

Na main, executa somente ETAPA=00 (sanidade da base), inclusive em forks; sucesso da main NÃO certifica a prática. Evidência de entrega é a execução da branch/PR no commit revisado. Habilitar Actions no fork antes do primeiro push se necessário. Evitar regras de proteção que exijam o contrato 02 para integrar a etapa 01.

Pages: publicar `main:/docs` no repositório-base. O guia tem links para arquivos em GitHub; não exige Pages no fork do estudante. Documentação operacional: [eventos e filtros](https://docs.github.com/en/actions/how-tos/write-workflows/choose-when-workflows-run/trigger-a-workflow) e [origem do Pages](https://docs.github.com/en/pages/getting-started-with-github-pages/configuring-a-publishing-source-for-your-github-pages-site).

## Avaliação

| Critério | Evidência | Peso sugerido |
|---|---|---|
| Contratos em C++ e Python | duas etapas verdes; vazio, duplicata, zero, remoção e fronteiras | 40% |
| Fundamentos | distingue identidade/igualdade, ordem/hash, posse/referências | 25% |
| Pensamento crítico | previsões, alternativa rejeitada e análise de retenção/durabilidade | 25% |
| Processo | commits, PRs, revisão e rastreabilidade | 10% |

Testes e workflow são visíveis e podem ser modificados no fork. Conferir diff, assinaturas e explicações; um selo verde não comprova autoria ou entendimento. Na avaliação oral (3–5 min), escolha uma pergunta: por que `ultimas(0)` é uma fronteira? Por que consultar as últimas não limita a memória? O que aconteceria sem o teste de duplicata em Python? Qual `second` é booleano? O que permanece após remover a entrada?
