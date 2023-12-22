# get_next_line

- 반복문 없이 재귀함수로만 구현한 gnl.
- 모든 재귀함수는 Tail Call Optimization 가능합니다.
- 내부 구현에 hash table, vector, circular queue, splay tree를 이용했습니다.

test:

```bash
make test
```

`BUFFER_SIZE`, `NUMBER_OF_FILES`, `FILE_SIZE_LIMIT`을 지정할 수 있습니다.

e.g.:

```bash
BUFFER_SIZE=1 NUMBER_OF_FILES=100 make
make test
```
