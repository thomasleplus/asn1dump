# Asn1dump - Dump the structure of an ASN1 file.

all: asn1dump.c
	gcc asn1dump.c -pedantic -ansi -Wall -O3 -o asn1dump
