
check:
	clang -fsyntax-only -Isrc/compat -Isrc/ext -Isrc/lib src/lib/*.c
	clang -fsyntax-only -Isrc/compat -Isrc/ext -Isrc/lib -Isrc/tasks/score -Isrc/tasks/button -Isrc/tasks/joystick -Isrc/tasks/game_loop src/main.c
	clang -fsyntax-only -Isrc/compat -Isrc/ext -Isrc/lib -Isrc/tasks/score -Isrc/tasks/button -Isrc/tasks/joystick -Isrc/tasks/game_loop src/tasks/*/*.c

format:
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" src/lib/*.{c,h} -i -sort-includes
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" src/tasks/*/*.{c,h} -i -sort-includes
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" src/main.c -i -sort-includes
