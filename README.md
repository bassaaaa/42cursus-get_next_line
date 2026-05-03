*This project has been created as part of the 42 curriculum by tsito.*

# get_next_line

## Description

`get_next_line` は、ファイルディスクリプタから次の1行を読み取り、動的に確保した文字列として返す C 言語の関数である。

この課題の目的は、`read`、`malloc`、`free` だけを使って、ファイルや標準入力からの逐次読み取りを正しく扱うことである。関数を繰り返し呼び出すことで、対象の入力を1行ずつ取得できる。

返される文字列には、実際に読み取った行末の改行文字 `\n` が含まれる。ただし、EOF に到達し、かつファイルが改行で終わっていない場合、最後の行には `\n` は含まれない。読み取る内容が残っていない場合、またはエラーが発生した場合は `NULL` を返す。

## Instructions

### 提出ファイル

Mandatory part では、以下のファイルを使用する。

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

実装する関数のプロトタイプは以下である。

```c
char	*get_next_line(int fd);
```

### コンパイル

`BUFFER_SIZE` はコンパイル時に指定できる。

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

`BUFFER_SIZE` が指定されない場合は、`get_next_line.h` 内のデフォルト値が使用される。

### 使用例

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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

## Algorithm

この実装では、`get_next_line` が呼び出されるたびに、現在のファイルディスクリプタから1文字ずつ読み取る。

読み取り処理では、まず返却用のバッファを確保する。その後、`read(fd, &buf[i], 1)` によって1文字ずつ読み込み、読み込めた文字数を `i` で管理する。改行文字 `\n` を読み取った場合、その文字も返却する文字列に含めたうえで読み取りを終了する。

EOF に到達した場合は、それまでに1文字以上読めていれば、その内容を最後の行として返す。このとき、ファイルが改行で終わっていなければ、返却文字列の末尾に `\n` は追加しない。まだ1文字も読めていない状態で EOF に到達した場合は、読み取る行が残っていないため `NULL` を返す。

読み取り中にバッファの容量が足りなくなった場合は、補助関数で新しいバッファを確保し、既に読み取った内容をコピーしてから古いバッファを解放する。これにより、行の長さが `BUFFER_SIZE` より大きい場合でも、必要な分だけ領域を広げて1行全体を返せる。

この方式では1文字ずつ読み取るため、改行を越えて余分な文字を読み込むことがない。そのため、次回の `get_next_line` 呼び出し時にもファイルディスクリプタの読み取り位置は次の行の先頭にある。余分に読み込んだデータを保持するための追加状態を持たずに、行単位の読み取りを実現できる。

一方で、`read` の呼び出し回数は多くなるため、性能面ではまとめて読み込む実装より不利である。この課題では、まず正しい行境界、EOF、改行なしの最終行、メモリ確保失敗を明確に扱うことを優先している。

## Resources

参考にした一般的な資料:

- `man read`
- `man malloc`
- `man free`
- [Tripouille/gnlTester](https://github.com/Tripouille/gnlTester) - GNL Tester

AI の使用:

- README 要件の整理
- 日本語 README の構成作成
- アルゴリズム説明文の表現調整
