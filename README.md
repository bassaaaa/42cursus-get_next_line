# 42 C Project Template

42 の C 課題用テンプレートです。

このリポジトリは、C 課題を始めるときの最低限の土台として使うことを想定しています。Makefile と GitHub Actions の雛形を含みますが、各課題の要件を自動で満たすものではありません。

## 重要な注意

課題要件に `README.md` の作成や内容指定がある場合は、必ずその課題要件に従って `README.md` を書いてください。

本テンプレートを使用した結果、レビュー、機械採点、Norminette、提出チェック、その他の評価に通らなかったとしても、テンプレート作成者は一切責任を負いません。提出前の確認責任は、使用者本人にあります。

42 の課題では、ファイル名、ディレクトリ構成、Makefile のターゲット、提出対象、使用可能な関数、禁止事項が課題ごとに異なります。テンプレートをそのまま使わず、必ず subject を読み、課題ごとに調整してください。

## 使い方

1. このテンプレートからリポジトリを作成する
2. 課題の subject を読む
3. 必要なファイルとディレクトリだけを配置する
4. `Makefile` を課題要件に合わせて書き換える
5. ローカルでコンパイル、Norminette、動作確認を行う
6. 提出前に subject の提出条件と差分を確認する

## ディレクトリ構成

このテンプレートは、特定の課題構成を強制しません。

課題によっては、以下のような指定があり得ます。

- ルート直下に `.c` / `.h` / `Makefile` を置く
- `src/` や `includes/` などのディレクトリを使う
- bonus 用ファイルを別名または別ディレクトリに分ける
- 提出してよいファイルが限定されている

ディレクトリ名やファイル配置は、必ず課題要件に合わせてください。

## Makefile

`Makefile` は雛形です。課題ごとに必ず見直してください。

確認する項目の例:

- `NAME` が課題で指定された成果物名になっているか
- ライブラリ課題なら `.a` を作る構成になっているか
- 実行ファイル課題なら実行ファイルを作る構成になっているか
- `SRCS` に必要なソースファイルがすべて含まれているか
- `INCDIR` がヘッダーファイルの配置と合っているか
- `all`, `clean`, `fclean`, `re` など、課題で求められるターゲットがあるか
- bonus が必要な場合、`bonus` ターゲットの要件を満たしているか

テンプレートの Makefile は、すべての課題にそのまま使えるものではありません。

## GitHub Actions

このテンプレートには、簡単な GitHub Actions のフローが含まれています。

- `format-c.yml`
  - `c_formatter_42` をインストールします
  - リポジトリ内の `.c` と `.h` をフォーマットします
  - 差分があれば bot が commit / push します
- `norminette.yml`
  - `main` への push と pull request で実行されます
  - 先にフォーマット用 workflow を呼び出します
  - その後、`norminette` を実行します
- `notify-discord.yml`
  - `DISCORD_WEBHOOK_URL` secret が設定されている場合、結果を Discord に通知します

Actions は補助ツールです。ローカル環境、校舎環境、提出システムの結果と完全に一致する保証はありません。

## 提出前チェック

提出前に少なくとも以下を確認してください。

- subject の提出ファイル一覧と一致している
- 不要なファイルやテストコードを提出対象に含めていない
- `make`, `make clean`, `make fclean`, `make re` が期待通りに動く
- `-Wall -Wextra -Werror` でコンパイルできる
- Norminette に通る
- メモリリーク、未初期化値、未定義動作がない
- 許可されていない関数を使っていない
- bonus の扱いが課題要件と一致している

## この README について

この README はテンプレートの説明用です。課題で README の内容が指定されている場合は、この内容を残すのではなく、課題要件に合わせて書き直してください。

---

# 42 C Project Template

This is a template repository for 42 C projects.

It is intended to provide a minimal starting point for C assignments. It includes a Makefile template and GitHub Actions workflows, but it does not automatically satisfy the requirements of every project.

## Important Notes

If the assignment requires a `README.md` file or specifies what must be written in it, you must write `README.md` according to the assignment requirements.

The template author assumes no responsibility if using this template causes you to fail a review, automated grading, Norminette, submission check, or any other evaluation. You are responsible for verifying your own submission before turning it in.

In 42 projects, file names, directory structure, Makefile targets, submitted files, allowed functions, and forbidden items differ by assignment. Do not use this template as-is. Always read the subject and adjust the project accordingly.

## Usage

1. Create a repository from this template
2. Read the assignment subject
3. Place only the required files and directories
4. Rewrite `Makefile` to match the assignment requirements
5. Run compilation, Norminette, and behavior checks locally
6. Before submission, verify the subject requirements and your final diff

## Directory Structure

This template does not enforce a specific project structure.

Depending on the assignment, you may be required to:

- Place `.c` / `.h` / `Makefile` directly at the repository root
- Use directories such as `src/` or `includes/`
- Separate bonus files by file name or directory
- Submit only a limited set of files

Always follow the assignment requirements for directory names and file placement.

## Makefile

`Makefile` is only a template. Review and update it for each assignment.

Examples of items to check:

- Whether `NAME` matches the required output name
- Whether library projects build a `.a` archive
- Whether executable projects build the required executable
- Whether `SRCS` includes all required source files
- Whether `INCDIR` matches the header file location
- Whether required targets such as `all`, `clean`, `fclean`, and `re` are present
- Whether the `bonus` target satisfies the assignment requirements, if bonus is required

The template Makefile is not suitable for every assignment as-is.

## GitHub Actions

This template includes simple GitHub Actions workflows.

- `format-c.yml`
  - Installs `c_formatter_42`
  - Formats `.c` and `.h` files in the repository
  - Commits and pushes changes as a bot if formatting creates a diff
- `norminette.yml`
  - Runs on push and pull request to `main`
  - Calls the formatting workflow first
  - Runs `norminette` afterward
- `notify-discord.yml`
  - Sends the result to Discord if the `DISCORD_WEBHOOK_URL` secret is configured

Actions are helper tools only. Their results are not guaranteed to match your local environment, campus environment, or the official submission system.

## Pre-Submission Checklist

Before submitting, check at least the following:

- The submitted files match the subject
- Unnecessary files and test code are not included in the submission
- `make`, `make clean`, `make fclean`, and `make re` work as expected
- The project compiles with `-Wall -Wextra -Werror`
- Norminette passes
- There are no memory leaks, uninitialized values, or undefined behavior
- No forbidden functions are used
- Bonus handling matches the assignment requirements

## About This README

This README explains the template itself. If an assignment specifies README requirements, do not keep this content as-is. Rewrite it according to the assignment requirements.
