# Asn1dump - Dump the structure of an ASN1 file.

all: src/asn1dump.c
	mkdir -p bin
	gcc src/asn1dump.c -pedantic -ansi -Wall -O3 -o bin/asn1dump

clang-tidy: src/asn1dump.c
	clang-tidy src/asn1dump.c
