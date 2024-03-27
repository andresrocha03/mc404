arquivo1.s: arquivo1.c
	clang --target=riscv32 -march=rv32g -mabi=ilp32d -mno-relax arquivo1.c -S -o arquivo1.s
arquivo2.s: arquivo2.c
	clang --target=riscv32 -march=rv32g -mabi=ilp32d -mno-relax arquivo2.c -S -o arquivo2.s
arquivo1.o: arquivo1.s
	clang --target=riscv32 -march=rv32g -mabi=ilp32d -mno-relax arquivo1.s -c -o  arquivo1.o
	
arquivo2.o: arquivo2.s
	clang --target=riscv32 -march=rv32g -mabi=ilp32d -mno-relax arquivo2.s -c -o  arquivo2.o

arquivo.x: arquivo1.o arquivo2.o
	ld.lld arquivo1.o arquivo2.o -o arquivo.x
