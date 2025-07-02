# 🐚 microshell

Implementação simples de um interpretador de comandos com suporte a `;` e `|`, conforme exigido no exame da 42.

## 🎯 Objetivo

Criar uma mini shell que suporte:

- Execução de comandos com argumentos
- Separação por ponto e vírgula (`;`)
- Encadeamento de comandos com pipe (`|`)

## 🧠 Funcionalidades

- Separação de comandos por `;` e execução sequencial
- Suporte a pipes (`|`) entre comandos
- Criação de processos com `fork()`
- Substituição do processo com `execve()`
- Comunicação entre processos com `pipe()`
- Espera dos processos filhos com `waitpid()`

## 🚫 Limitações

- **Não** há suporte a redirecionamentos (`<`, `>`, `>>`, `<<`)
- **Não** há suporte a variáveis de ambiente (`$VAR`)
- **Não** há comandos built-in (`export`, etc.)
- **Sem tratamento de aspas, escape, nem expansão**

## 🛠️ Compilação

```bash
gcc -Wall -Wextra -Werror microshell.c -o microshell
