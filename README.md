# Identidade, igualdade e coleções — prática do capítulo 11

Prática independente em **C++17 e Python 3.10+**, sem pré-requisito de arquivos dos capítulos 07, 10 ou 12. Você completa um catálogo e uma consulta ao histórico de leituras, explica suas decisões e verifica o mesmo contrato nas duas linguagens.

**Tempo:** 2h de prática (40 min para iniciar em sala e cerca de 80 min de conclusão orientada). Os fundamentos são estudados no [capítulo 11](https://rafaelrezo.github.io/curso-poo/fundamentos_poo_cpp_python/12_igualdade_identidade/). A modelagem do capítulo 12 é separada.

- [Guia passo a passo no GitHub Pages](https://rafaelrezo.github.io/poo-identidade-colecoes/)
- [Guia em Markdown](docs/index.md)
- [Contrato e limites](docs/contrato.md)
- [Decisões do estudante](docs/decisoes.md)
- [Orientações do docente](GUIA_DOCENTE.md)

## Requisitos

Git, GNU Make, g++ com C++17 e Python 3.10 ou superior. Linux, WSL ou ambiente equivalente; nenhuma dependência Python externa. Confira `git --version`, `make --version`, `g++ --version` e `python3 --version`.

## Fluxo

1. Faça fork de `rafaelrezo/poo-identidade-colecoes` e clone **seu fork**. Mantenha somente `origin` apontando para ele.
2. Execute `make run`: a base já mostra identidade, igualdade e três ocorrências no histórico. Os avisos `PENDENTE 01` e `PENDENTE 02` marcam funcionalidades ainda não implementadas.
3. Na branch `pratica/01-catalogo`, complete `inserir` e `buscar` em `include/colecoes.hpp` e `src/colecoes.py`, seguindo o guia. Valide com `make test ETAPA=01`.
4. Faça commits pequenos, push e **PR para a main do próprio fork**. Registre saída local, link da CI do commit e suas decisões; integre após a validação.
5. A partir da main atualizada, crie `pratica/02-historico`. Implemente `remover` e `Historico.ultimas` nas duas linguagens, sem alterar as assinaturas.
6. Valide com `make test ETAPA=02`, que repete os testes anteriores. Entregue a segunda PR com a explicação da extensão.

Nunca abra PR contra o repositório-base. Não configure `upstream`. Código, testes e revisão ficam no próprio fork. Cada push das branches previstas roda o mesmo comando local; PRs para main usam a etapa da branch de origem.

## O que está pronto e o que você implementa

| Fornecido para leitura | Tarefa autoral |
|---|---|
| `IdSensor`: igualdade, ordenação C++ e hash; imutabilidade Python | explicar identidade e igualdade com evidências |
| Estrutura genérica de `Catalogo`, `quantidade` e `ids` | inserir, buscar e remover |
| `Medicao`, registro no histórico e contagem | consultar últimas leituras sem apagar o histórico |
| Demonstração, compilação, testes e CI | prever resultados, corrigir comportamento e justificar decisões |

Não editar testes, workflow ou tipos fornecidos para esconder falhas. A CI verifica contratos observáveis; a autoria e o entendimento são conferidos pelo diff, por `docs/decisoes.md` e por defesa oral em avaliações. Registre uso ou ausência de IA em `AI_LOG.md`.

## Comandos

```bash
make run
make test ETAPA=01
make test ETAPA=02
```

`make test ETAPA=00` testa **somente a base fornecida**, não aprova a atividade. A CI da main usa essa verificação para que o starter incompleto possa ser distribuído. As evidências de conclusão são os testes funcionais nas branches e PRs das etapas 01 e 02.

O código inicial executa, mas os contratos 01 e 02 falham intencionalmente. O aluno implementa quatro métodos em cada linguagem. O histórico fica em memória; não há arquivo, banco de dados ou janela com descarte automático nesta atividade.
