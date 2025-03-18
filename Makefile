# Asn1dump - Dump the structure of an ASN1 file.

all: asn1dump.c
	mkdir -p bin
	gcc src/*.c -pedantic -ansi -Wall -O3 -o bin/asn1dump
