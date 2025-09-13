package org.leplus.asn1dump;

import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import org.bouncycastle.asn1.ASN1InputStream;
import org.bouncycastle.asn1.ASN1Primitive;
import org.bouncycastle.asn1.util.ASN1Dump;

/** Main class. */
public final class Main {

  private Main() {
    super();
  }

  /**
   * Main method.
   *
   * @param args the command line arguments, files to be dumped.
   * @throws IOException if an I/O error occurs.
   */
  @SuppressFBWarnings("PATH_TRAVERSAL_IN")
  public static void main(final String[] args) throws IOException {
    for (final String arg : args) {
      try (FileInputStream in = new FileInputStream(new File(arg))) {
        readAndPrint(in, System.out);
      }
    }
  }

  /**
   * Reads an ASN.1 stream and prints it to a print stream.
   *
   * @param in the input stream.
   * @param out the output stream.
   * @throws IOException if an I/O error occurs.
   */
  public static void readAndPrint(final InputStream in, final PrintStream out) throws IOException {
    try (ASN1InputStream asn1InputStream = new ASN1InputStream(in)) {
      ASN1Primitive obj;
      while ((obj = asn1InputStream.readObject()) != null) {
        out.println(ASN1Dump.dumpAsString(obj, true));
      }
    }
  }
}
