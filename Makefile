UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	CXX=clang++-mp-13
    EXT=-mp-13
endif

ANALYSIS="-*,cert-*,clang-analyzer-*,modernize-*,performance-*,cppcoreguidelines-*,google-*,bugprone-*,misc-*,-google-runtime-references,-cppcoreguidelines-avoid-magic-numbers,-modernize-use-trailing-return-type,-misc-redundant-expression,-bugprone-easily-swappable-parameters"

SRC=$(wildcard *.cpp)
HDR=$(wildcard *.hh)

a.out : ${SRC} ${HDR} Makefile
	${CXX} -Wall -Wextra -Wshadow -O2 --std=c++20 -I . -I /opt/local/include -D__USE_ISOC99 ${SRC} -o a.out


test: a.out
	./a.out

help:
	@echo "make [a.out]        : compile a.out"
	@echo "make test           : compile and test a.out"
	@echo "make format         : format the source code"
	@echo "make analyze        : clang-tidy code analysis"
	@echo "make fix            : clang-tidy code fix"
	@echo "make clean          : delete all generated files"

format :
	clang-format${EXT} -i -style=file ${SRC} ${HDR}

clean :
	rm -f a.out *.orig *.plist

analyze :
	clang-tidy${EXT} --extra-arg="--std=c++17" -checks=${ANALYSIS}  *.cpp  -- -I . -I /opt/local/include -D__USE_ISOC99

check :
	cppcheck --enable=all --inconclusive --language=c++ --std=c++20 -I . -I /opt/local/include -D__USE_ISOC99 --quiet --suppress=missingIncludeSystem *.ccp *.h --template='{severity}:{file}:{line}:{message}'


fix :
	clang-tidy${EXT} --extra-arg="--std=c++20" -checks=${ANALYSIS}  *.cpp -fix  -- -I . -I /opt/local/include -D__USE_ISOC99

