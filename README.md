### GDBM(GNU DataBase Manager) Benchmark Programming
`RDBMS`와는 달리 하나하나의 데이터가 별개로 존재하므로 `RDBMS`처럼 데이터간 관계에 의한 질의 언어가 필요없이 간단하게 Key만 호출하면, 해당 Value를 얻을 수 있다.
```c
#include <gdbm.h>

GDBM_FILE gdbm_open(name, block_size, flags, mode, fatal_func); // DB open
void gdbm_close(dbf);                                           // DB close
int gdbm_store(dbf, key, content, flag);                        // 삽입 또는 대체
datum gdbm_fetch(dbf, key);                                     // 레코드 검색
int gdbm_delete(dbf, key);                                      // 레코드 제거
datum gdbm_firstkey(dbf);                                       // DB에서 모든 키를 방문하기 시작하는 역할
datum gdbm_nextkey(dbf, key);                                   // 'dbf' 의 해쉬 구조에서 다음 엔트리를 찾고 읽는다.
int gdbm_reorganize(dbf); 
void gdbm_sync(dbf);
int gdbm_exists(dbf, key);                                      // key에 대응하는 데이터 존재하는지 확인
char *gdbm_strerror(errno);                                     // 에러 메세지
int gdbm_setopt(dbf, option, value, size);
```