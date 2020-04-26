include ../build_config.mk

OBJS += ../src/net/link.o ../src/net/fde.o ../src/util/log.o ../src/util/bytes.o
CFLAGS += -I../src
EXES = ssdb-bench ssdb-dump ssdb-repair leveldb-import

all: ssdb-bench.o ssdb-dump.o ssdb-repair.o leveldb-import.o ssdb-migrate.o
	${CXX} -g -o ssdb-bench ssdb-bench.o ${OBJS} ${UTIL_OBJS} ${CLIBS}
	${CXX} -g -o ssdb-dump ssdb-dump.o ${OBJS} ${UTIL_OBJS} ${CLIBS}
	${CXX} -g -o ssdb-repair ssdb-repair.o ${OBJS} ${UTIL_OBJS} ${CLIBS}
	${CXX} -g -o leveldb-import leveldb-import.o ${OBJS} ${UTIL_OBJS} ${CLIBS}
	${CXX} -g -o ssdb-migrate ssdb-migrate.o ../api/cpp/libssdb-client.a ../src/util/libutil.a

ssdb-migrate.o: ssdb-migrate.cpp
	${CXX} ${CFLAGS} -g3 -I../api/cpp -c ssdb-migrate.cpp
ssdb-bench.o: ssdb-bench.cpp
	${CXX} ${CFLAGS} -g3 -c ssdb-bench.cpp
ssdb-dump.o: ssdb-dump.cpp
	${CXX} ${CFLAGS} -g3 -c ssdb-dump.cpp
ssdb-repair.o: ssdb-repair.cpp
	${CXX} ${CFLAGS} -g3 -c ssdb-repair.cpp
leveldb-import.o: leveldb-import.cpp
	${CXX} ${CFLAGS} -g3 -c leveldb-import.cpp

clean:
	rm -f *.exe *.exe.stackdump *.o ${EXES}
	rm -rf _cpy_

