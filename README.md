# Asn1dump

Dump the structure of an ASN.1 file.

[![Maven](https://github.com/thomasleplus/Asn1dump/workflows/Maven/badge.svg)](https://github.com/thomasleplus/Asn1dump/actions?query=workflow:"Maven")
[![CodeQL](https://github.com/thomasleplus/Asn1dump/workflows/CodeQL/badge.svg)](https://github.com/thomasleplus/Asn1dump/actions?query=workflow:"CodeQL")

> [!NOTE]
> This project was rewritten in Java to use a memory-safe language. If
> you are looking for the original C code, have a look at tag
> [v0.0.1](https://github.com/thomasleplus/asn1dump/tree/v0.0.1). You
> can also download that [release](https://github.com/thomasleplus/asn1dump/tree/v0.0.1).

## Running

**Mac/Linux**

```bash
./mvnw exec:java -Dexec.mainClass=org.leplus.asn1dump.Main -Dexec.args='cert1.der cert2.der'
```

**Windows**

In `cmd`:

```batch
mvnw.cmd exec:java -Dexec.mainClass=org.leplus.asn1dump.Main -Dexec.args='cert1.der cert2.der'
```

In PowerShell:

```pwsh
.\mvnw.cmd exec:java -Dexec.mainClass=org.leplus.asn1dump.Main -Dexec.args='cert1.der cert2.der'
```
