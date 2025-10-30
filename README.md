# asn1dump

Dump the structure of an ASN.1 file.

[![Maven](https://github.com/thomasleplus/asn1dump/workflows/Maven/badge.svg)](https://github.com/thomasleplus/asn1dump/actions?query=workflow:"Maven")

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

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct and the process for submitting pull requests.

## Security

Please read [SECURITY.md](SECURITY.md) for details on our security policy and how to report security vulnerabilities.

## Code of Conduct

Please read [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) for details on our code of conduct.

## License

This project is licensed under the terms of the [LICENSE](LICENSE) file.
