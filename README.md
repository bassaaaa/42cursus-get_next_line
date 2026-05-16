*This project has been created as part of the 42 curriculum by tsito.*

# get_next_line

## Description

`get_next_line` is a 42 Common Core C project that implements a function which
returns the next line read from a file descriptor.

```c
char	*get_next_line(int fd);
```

Each successful call returns a newly allocated string. The returned string
includes the trailing newline character when that newline exists in the input.
At EOF, if the last line does not end with `\n`, that final line is returned
without adding one. When there is no more data to read, or when an error occurs,
the function returns `NULL`.

This repository contains the mandatory implementation only:

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

The implementation follows the 42 Norm and uses only the allowed external
functions: `read`, `malloc`, and `free`.

## Instructions

### Build

Compile the mandatory files from the repository root:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

`BUFFER_SIZE` can be changed at compile time:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c
```

If `BUFFER_SIZE` is not provided by the compiler command, `get_next_line.h`
defines it as `42`.

### Usage

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

This implementation reads by chunks of `BUFFER_SIZE` bytes and stores unread
data in one static buffer named `stash`.

For each call to `get_next_line`:

1. Validate `fd`, `BUFFER_SIZE`, and the readability of `fd` with
   `read(fd, 0, 0)`.
2. Read `BUFFER_SIZE` bytes at a time into a temporary buffer.
3. Append each read chunk to the static `stash`.
4. Stop reading when `stash` contains a newline or when `read` reaches EOF.
5. Extract the next line from the beginning of `stash`.
6. Update `stash` so it keeps only the bytes after the returned line.
7. Return the extracted line.

The helper functions are:

- `append_str`: joins the current `stash` with the latest read buffer and frees
  the old `stash`.
- `read_until_line`: fills `stash` until a full line is available or EOF/error
  is reached.
- `extract_line`: allocates and returns the next line from `stash`.
- `update_stash`: removes the returned line from `stash` and keeps the
  remaining unread data for the next call.
- `gnl_strlen`, `gnl_strchr`, `gnl_strjoin`, and `gnl_substr`: small local
  string utilities used instead of libft.

## Resources

- `man read`
- `man malloc`
- `man free`
- [Tripouille/gnlTester](https://github.com/Tripouille/gnlTester)

## 日本語

`get_next_line` は、ファイルディスクリプタから次の1行を読み取り、動的確保した
文字列として返す 42 Common Core の C 課題である。

```c
char	*get_next_line(int fd);
```

返される文字列には、入力に存在する場合は末尾の改行文字も含まれる。EOF に到達
し、最後の行が改行で終わっていない場合は、改行を追加せずそのまま返す。読む
内容が残っていない場合、またはエラーが発生した場合は `NULL` を返す。

このリポジトリは mandatory 実装のみを含む。

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

### ビルド

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

`BUFFER_SIZE` はコンパイル時に変更できる。

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c
```

コンパイル時に `BUFFER_SIZE` が指定されない場合、`get_next_line.h` で `42` が
定義される。

### アルゴリズム

`BUFFER_SIZE` バイト単位で読み取り、
未返却のデータを static 変数 `stash` に保持する方式。

`get_next_line` の各呼び出しでは次の処理を行う。

1. `fd`、`BUFFER_SIZE`、`read(fd, 0, 0)` による読み取り可否を検証する。
2. 一時バッファに `BUFFER_SIZE` バイトずつ読み取る。
3. 読み取った内容を static の `stash` に連結する。
4. `stash` 内に改行が見つかるか、EOF に到達するまで読み続ける。
5. `stash` の先頭から返却する1行を切り出す。
6. 返却した行より後ろの残りを、新しい `stash` として保持する。
7. 切り出した行を返す。

補助関数の役割は次のとおり。

- `append_str`: 現在の `stash` と直近の読み取りバッファを連結し、古い `stash`
  を解放する。
- `read_until_line`: 1行分のデータが揃うか EOF/error になるまで `stash` を
  埋める。
- `extract_line`: `stash` の先頭から次に返す1行を確保して返す。
- `update_stash`: 返却済みの行を `stash` から取り除き、次回用の残りだけを
  保持する。
- `gnl_strlen`, `gnl_strchr`, `gnl_strjoin`, `gnl_substr`: libft を使わない
  ための最小限の文字列操作関数。
