*This project has been created as part of the 42 curriculum by tsito.*

# get_next_line

## Description

`get_next_line` is a 42 Common Core C project whose goal is to implement a
function that reads and returns the next line from a file descriptor.

The project provides the following function:

```c
char	*get_next_line(int fd);
```

The function returns one dynamically allocated line at a time. The returned
string includes the trailing newline character when one is read, except when
EOF is reached and the file does not end with a newline. If there is nothing
left to read, or if an error occurs, the function returns `NULL`.

### Mandatory Requirements

The mandatory part uses the following files:

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

Subject constraints:

- the project must be written in C,
- the code must follow the 42 Norm,
- the project must compile with `cc -Wall -Wextra -Werror`,
- allowed external functions are `read`, `malloc`, and `free`,
- libft is forbidden,
- `lseek()` is forbidden,
- global variables are forbidden,
- `get_next_line.h` must contain at least the prototype of `get_next_line()`,
- helper functions must be added to `get_next_line_utils.c`,
- `BUFFER_SIZE` must be handled when defined at compile time with
  `-D BUFFER_SIZE=n`,
- the implementation must work both with files and standard input.

The behavior is undefined if the file changes between two calls before EOF is
reached. Binary file handling is also considered undefined by the subject.

### Bonus Requirements

The bonus part is optional and is evaluated only if the mandatory part is
perfect.

The subject lists the following bonus requirements:

- use only one static variable,
- manage multiple file descriptors at the same time,
- preserve the reading state of each file descriptor when calls are interleaved.

Bonus files should follow the subject convention by using `_bonus.c` and
`_bonus.h` filenames.

## Instructions

### Build

Compile the mandatory files from the repository root:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

`BUFFER_SIZE` may be changed at compile time:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c
```

If `BUFFER_SIZE` is not defined by the compiler command, the fallback value in
`get_next_line.h` is used.

### Use in another C file

Include the header:

```c
#include "get_next_line.h"
```

Example:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("sample.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Compile the example with the project files:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

## Algorithm

The chosen algorithm reads from the file descriptor one character at a time and
grows the returned line buffer when necessary.

For each call to `get_next_line`:

1. Validate the file descriptor and `BUFFER_SIZE`.
2. Allocate an initial buffer for the returned line.
3. Read one character from the file descriptor.
4. If the character is a newline, include it in the line and stop reading.
5. If EOF is reached after reading at least one character, return the final
   line without appending a newline.
6. If EOF is reached before reading any character, free the buffer and return
   `NULL`.
7. If the line buffer is full, allocate a larger buffer, copy the current
   content, and free the old buffer.
8. Null-terminate the returned string before returning it.

## Resources

Classic references used for this topic:

- `man read`
- `man malloc`
- `man free`
- [Tripouille/gnlTester](https://github.com/Tripouille/gnlTester) - test tool

AI usage:

| Purpose | Target part |
| --- | --- |
| Japanese translation of requirements | Used to accurately understand the subject requirements |
| README.md proofreading | Used to revise wording and phrasing |
| English translation of README.md | Used to produce an accurate English translation of the README |

---

## Description

`get_next_line` は、ファイルディスクリプタから次の 1 行を読み取り、返す関数を
実装する 42 Common Core の C 課題である。

このプロジェクトでは、次の関数を作成する。

```c
char	*get_next_line(int fd);
```

この関数は、動的に確保した文字列として 1 行を返す。返される文字列には、
実際に読み取った行末の改行文字が含まれる。ただし、EOF に到達し、かつファイルが
改行で終わっていない場合、最後の行には改行文字を含めない。読み取る内容が
残っていない場合、またはエラーが発生した場合は `NULL` を返す。

### 必須要件

mandatory part では次のファイルを使用する。

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

subject 上の制約は次のとおりである。

- プロジェクトは C で書くこと
- コードは 42 Norm に従うこと
- `cc -Wall -Wextra -Werror` でコンパイルできること
- 使用可能な外部関数は `read`, `malloc`, `free`
- libft は禁止
- `lseek()` は禁止
- グローバル変数は禁止
- `get_next_line.h` には少なくとも `get_next_line()` のプロトタイプを含めること
- 必要な補助関数は `get_next_line_utils.c` に追加すること
- `-D BUFFER_SIZE=n` によってコンパイル時に指定される `BUFFER_SIZE` を扱うこと
- ファイルと標準入力の両方で動作すること

EOF に到達する前に、最後の呼び出し以降で対象ファイルが変更された場合の動作は
未定義である。バイナリファイルを読み取る場合の動作も subject 上は未定義である。

### ボーナス要件

ボーナスは任意である。必須部分が完全に正しく実装されている場合のみ評価される。

subject では次の対応がボーナスとして挙げられている。

- 1 つの static 変数だけを使うこと
- 複数のファイルディスクリプタを同時に管理できること
- 複数 fd の呼び出しが交互になっても、それぞれの読み取り状態を保持すること

ボーナス用ファイルは、subject の慣例に従って `_bonus.c` や `_bonus.h` を使う。

## Instruction

### ビルド

リポジトリのルートで mandatory ファイルをコンパイルする。

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

`BUFFER_SIZE` はコンパイル時に変更できる。

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c
```

`BUFFER_SIZE` がコンパイル時に指定されない場合は、`get_next_line.h` 内の
デフォルト値を使用する。

### 他の C ファイルから使う例

ヘッダーを include する。

```c
#include "get_next_line.h"
```

使用例:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("sample.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

プロジェクトのファイルと一緒にコンパイルする。

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

### Algorithm

採用するアルゴリズムは、ファイルディスクリプタから 1 文字ずつ読み取り、必要に
応じて返却用バッファを拡張する方式である。

`get_next_line` の各呼び出しでは次の処理を行う。

1. ファイルディスクリプタと `BUFFER_SIZE` を検証する。
2. 返却する行のための初期バッファを確保する。
3. ファイルディスクリプタから 1 文字を読み取る。
4. 読み取った文字が改行であれば、その文字を行に含めて読み取りを終了する。
5. 1 文字以上読んだあとに EOF へ到達した場合、改行を追加せず最後の行を返す。
6. 1 文字も読まずに EOF へ到達した場合、バッファを解放して `NULL` を返す。
7. 行バッファが足りなくなった場合、より大きいバッファを確保し、現在の内容を
   コピーして古いバッファを解放する。
8. 返却する文字列を null 終端して返す。

### 参考資料

このトピックに関する基本的な参考資料:

- `man read`
- `man malloc`
- `man free`
- [Tripouille/gnlTester](https://github.com/Tripouille/gnlTester) - テストツール

AI の使用について:

| 用途 | 対象部分 |
|------|---------|
| 要件の日本語訳 | 課題要件の正確な把握のため、翻訳に利用 |
| README.md の添削 | 文言や言い回しの修正 |
| README.md 英語訳 | READMEの正確な英訳に利用 |
