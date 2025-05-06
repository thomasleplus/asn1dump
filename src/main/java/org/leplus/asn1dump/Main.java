package org.leplus.asn1dump;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;
import org.bouncycastle.asn1.ASN1InputStream;
import org.bouncycastle.asn1.ASN1Primitive;
import org.bouncycastle.asn1.util.ASN1Dump;

/** Main class. */
public final class Main {

  @SuppressFBWarnings("PATH_TRAVERSAL_IN")
  public static void main(final String[] args) throws IOException {
    for (final String arg : args) {
      try (FileInputStream fis = new FileInputStream(new File(arg));
          ASN1InputStream asn1InputStream = new ASN1InputStream(fis)) {
        ASN1Primitive obj;
        while ((obj = asn1InputStream.readObject()) != null) {
          System.out.println(ASN1Dump.dumpAsString(obj, true));
        }
      }
    }
  }
}
