# Asn1dump - Dump the structure of an ASN1 file.

all: src/asn1dump.c
	mkdir -p bin
	gcc src/asn1dump.c -pedantic -ansi -fanalyzer -Wall -O3 -o bin/asn1dump

clang-tidy: src/asn1dump.c
	clang-tidy '--checks=*' '--warnings-as-errors=*' src/asn1dump.c

splint: src/asn1dump.c
	splint -checks src/asn1dump.c

cppcheck: src/asn1dump.c
	cppcheck --check-level=exhaustive src/asn1dump.c
