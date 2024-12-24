all: target

target: main.c
	gcc -Wall -Wextra -Werror $< -o program

test: .venv/bin/activate
	source $< && pytest -sv

.PHONY: test
