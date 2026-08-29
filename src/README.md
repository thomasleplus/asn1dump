# Source

Maven sources for `asn1dump`, a small Java CLI that reads a DER-encoded ASN.1
file and prints its structure.

Standard Maven layout:

- **`main/java/org/leplus/asn1dump/`** — the application.
  - `Main.java` — entry point; parses the DER file(s) passed as arguments and
    writes the decoded ASN.1 structure to stdout. Run it with the `./mvnw`
    command shown in the [root README](../README.md).
- **`test/java/org/leplus/asn1dump/`** — JUnit tests.
- **`test/resources/`** — fixtures: `sampleN.der` inputs paired with the
  expected `sampleN.txt` output the tests assert against.

To add a regression case, drop a new `.der`/`.txt` pair in `test/resources/`.
