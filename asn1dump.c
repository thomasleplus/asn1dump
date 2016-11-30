/*
 * Asn1dump - Dump the structure of an ASN1 file.
 * Copyright (C) 2012 Thomas Leplus
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
  
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define ulint unsigned long int

ulint asn1parse (FILE *, ulint, int, int *);
void printinfo(ulint, int *, ulint, int, char *, int);
ulint printdata(ulint, ulint, FILE *);

char *prog;
char *file;

int main(int argc, char **argv)
{
	int c, i;
	FILE *data;
	prog = argv[0];
	for (i = 1; i < argc; i++) {
		file = argv[i];
		if ((data = fopen(argv[i], "rb")) == NULL) {
			fprintf(stderr, "%s: can't read file %s\n", prog, file);
			continue;
		}
		asn1parse(data, 0, 0, NULL);
		if ((c = fgetc(data)) != EOF) {
			fprintf(stderr, "%s: extra data remainig in %s\n", prog, file);
			continue;
		}
		fclose(data);
	}
	return 0;
}

ulint asn1parse(FILE *data, ulint offset, int level, int *bool)
{
	int buffer[6];
	int b, c, header, tag, class, type;
	ulint size, pos;
	char string[14];

	if ((buffer[0] = fgetc(data)) == EOF) {
		fprintf(stderr, "%s: %s: unexpected end of file\n", prog, file);
		return 0;
	}
	if ((buffer[0] & 0x1F) == 0x1F) {
		fprintf(stderr, "%s: %s: unsupported encoding identifier\n", prog, file);
		return 0;
	}
	tag = buffer[0] & 0x3F;
	class = buffer[0] >> 6;
	type = (buffer[0] & 0x20) ? TRUE : FALSE;

	if ((buffer[1] = fgetc(data)) == EOF) {
		fprintf(stderr, "%s: %s: unexpected end of file\n", prog, file);
		return 0;
	}
	if (buffer[1] < 0x80) {
		size = buffer[1];
		b = FALSE;
		header = 2;
		pos = offset + 2;
		buffer[2] = EOF;
	}
	else if (buffer[1] == 0x80) {
		size = 0;
		b = TRUE;
		header = 2;
		pos = offset + 2;
		buffer[2] = EOF;
	} else if (buffer[1] < 0x84) {
		size = 0;
		for (c = 0; c < buffer[1] - 0x80; c++) {
			if ((buffer[2 + c] = fgetc(data)) == EOF) {
				fprintf(stderr, "%s: %s: unexpected end of file\n", prog, file);
				return 0;
			}
			size *= 0x100;
			size += buffer[2 + c];
		}
		b = FALSE;
		header = 2 + c;
		pos = offset + header;
		buffer[header] = EOF;
	} else {
		fprintf(stderr, "%s: %s: encoding length too long\n", prog, file);
		return 0;
	}
  
	if (!type && b) {
		fprintf(stderr, "%s: %s: unexpected undefined length\n", prog, file);
		return 0;
	}

	if (class == 0)
		switch (tag) {
		case 0x00:
			printinfo(offset, buffer, size, level, "EOC", FALSE);
			if (bool)
				*bool = FALSE;
			break;
		case 0x01:
			printinfo(offset, buffer, size, level, "Boolean", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x02:
			printinfo(offset, buffer, size, level, "Integer", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x03:
			printinfo(offset, buffer, size, level, "BitString", FALSE);
			if (size) {
				if ((c = fgetc(data)) == EOF) {
					fprintf(stderr, "%s: %s: unexpected end of file\n", prog, file);
					return 0;
				}
				fprintf(stdout, "                               : %s%X (unused bits)\n",
						c > 0x0F ? "" : "0", c);
				if ((pos = printdata(pos + 1, size - 1, data)) == 0)
					return 0;
			}
			break;
		case 0x04:
			printinfo(offset, buffer, size, level, "OctetString", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x05:
			printinfo(offset, buffer, size, level, "Null", FALSE);
			break;
		case 0x06:
			printinfo(offset, buffer, size, level, "ObjectIdentifier", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x07:
			printinfo(offset, buffer, size, level, "ObjectDescriptor", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x09:
			printinfo(offset, buffer, size, level, "Real", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x0C:
			printinfo(offset, buffer, size, level, "UTF8String", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x12:
			printinfo(offset, buffer, size, level, "NumericString", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x13:
			printinfo(offset, buffer, size, level, "PrintableString", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x14:
			printinfo(offset, buffer, size, level, "TeletexString", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x15:
			printinfo(offset, buffer, size, level, "VideotexString", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x16:
			printinfo(offset, buffer, size, level, "IA5String", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x17:
			printinfo(offset, buffer, size, level, "UTCTime", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x18:
			printinfo(offset, buffer, size, level, "GeneralizedTime", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x19:
			printinfo(offset, buffer, size, level, "GraphicString", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x1A:
			printinfo(offset, buffer, size, level, "VisibleString", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x1B:
			printinfo(offset, buffer, size, level, "GeneralString", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x1C:
			printinfo(offset, buffer, size, level, "UniversalString", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x1D:
			printinfo(offset, buffer, size, level, "BMPString", FALSE);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
			break;
		case 0x30:
			printinfo(offset, buffer, size, level, "SEQUENCE", FALSE);
			if (b) {
				while (b)
					if ((pos = asn1parse(data, pos, level + 1, &b)) == 0)
						return 0;
			} else if (size) {
				while (pos < offset + header + size)
					if ((pos = asn1parse(data, pos, level + 1, NULL)) == 0)
						return 0;
			}
			break;
		case 0x31:
			printinfo(offset, buffer, size, level, "SET", FALSE);
			if (b) {
				while (b)
					if ((pos = asn1parse(data, pos, level + 1, &b)) == 0)
						return 0;
			} else if (size) {
				while (pos < offset + header + size)
					if ((pos = asn1parse(data, pos, level + 1, NULL)) == 0)
						return 0;
			}
			break;
		default:
			if (type) {
				printinfo(offset, buffer, size, level,
						  "Unknown constructed encoding", b);
				if (b) {
					while (b)
						if ((pos = asn1parse(data, pos, level + 1, &b)) == 0)
							return 0;
				} else if (size) {
					while (pos < offset + header + size)
						if ((pos = asn1parse(data, pos, level + 1, NULL)) == 0)
							return 0;
				}
			} else {
				printinfo(offset, buffer, size, level,
						  "Unknown primitive encoding", b);
				if (size)
					if ((pos = printdata(pos, size, data)) == 0)
						return 0;
			}
			break;
		} else if (class == 2) {
			if (type) {
				sprintf(string, "[%d]", buffer[0] & 0x1F);
				printinfo(offset, buffer, size, level, string, b);
				if (b) {
					while (b)
						if ((pos = asn1parse(data, pos, level + 1, &b)) == 0)
							return 0;
				} else if (size) {
					while (pos < offset + header + size)
						if ((pos = asn1parse(data, pos, level + 1, NULL)) == 0)
							return 0;
				}
			} else {
				sprintf(string, "[%d] IMPLICIT", buffer[0] & 0x1F);
				printinfo(offset, buffer, size, level, string, b);
				if (size)
					if ((pos = printdata(pos, size, data)) == 0)
						return 0;
			}
		} else if (type) {
			printinfo(offset, buffer, size, level,
					  "Unknown constructed encoding", b);
			if (b) {
				while (b)
					if ((pos = asn1parse(data, pos, level + 1, &b)) == 0)
						return 0;
			} else if (size) {
				while (pos < offset + header + size)
					if ((pos = asn1parse(data, pos, level + 1, NULL)) == 0)
						return 0;
			}
		} else {
			printinfo(offset, buffer, size, level, "Unknown primitive encoding", b);
			if (size)
				if ((pos = printdata(pos, size, data)) == 0)
					return 0;
		}
	return pos;
}

void printinfo(ulint offset, int *buffer, ulint size,
			   int level, char *name, int bool)
{
	char tmp[9];
	int i;
	sprintf(tmp, "%6lX", offset);
	for (i = 0; tmp[i] == ' '; i++)
		tmp[i] = '0';
	fprintf(stdout, "%s: ", tmp);
	for (i = 0; buffer[i] != EOF; i++)
		fprintf(stdout, "%s%X ", buffer[i] > 0x0F ? "" : "0", buffer[i]);
	for (; i < 5; i ++)
		fprintf(stdout, "   ");
	if (bool) {
		fprintf(stdout, "                  : ");
		for (i = 0; i < level; i++)
			fprintf(stdout, ". ");
		fprintf(stdout, "%s (size undefined)\n", name);
	} else {
		fprintf(stdout, "%8lu: ", size);
		for (i = 0; i < level; i++)
			fprintf(stdout, ". ");
		fprintf(stdout, "%s\n", name);
	}
	return;
}

ulint printdata(ulint offset, ulint size, FILE *data)
{
	int c;
	ulint n = 0;
	while (n++ < size) {
		if (n % 16 == 1)
			fprintf(stdout, "                               : ");
		if ((c = fgetc(data)) == EOF) {
			fprintf(stderr, "%s: %s: unexpected end of file\n", prog, file);
			return 0;
		}
		fprintf(stdout, "%s%X", c > 0x0F ? "" : "0", c);
		if (n % 16 == 0 || n == size)
			fprintf(stdout, "\n");
		else
			fprintf(stdout, " ");
	}
	return offset + size;
}
