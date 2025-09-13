package org.leplus.asn1dump;

import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class MainTest {

  /** Path to the first sample DER file. */
  public static final String INPUT_1 = "src/test/resources/sample1.der";

  /** Path to the second sample DER file. */
  public static final String INPUT_2 = "src/test/resources/sample2.der";

  /** Path to the third sample DER file. */
  public static final String INPUT_3 = "src/test/resources/sample3.der";

  /** Path to the first expected output file. */
  public static final String OUTPUT_1 = "src/test/resources/sample1.txt";

  /** Path to the second expected output file. */
  public static final String OUTPUT_2 = "src/test/resources/sample2.txt";

  /** Path to the third expected output file. */
  public static final String OUTPUT_3 = "src/test/resources/sample3.txt";

  @Test
  void readAndPrint1() throws IOException {
    final byte[] expected = Files.readAllBytes(Paths.get(OUTPUT_1));
    final ByteArrayOutputStream out = new ByteArrayOutputStream();
    Main.readAndPrint(new FileInputStream(INPUT_1), new PrintStream(out));
    Assertions.assertArrayEquals(expected, out.toByteArray());
  }

  @Test
  void readAndPrint2() throws IOException {
    final byte[] expected = Files.readAllBytes(Paths.get(OUTPUT_2));
    final ByteArrayOutputStream out = new ByteArrayOutputStream();
    Main.readAndPrint(new FileInputStream(INPUT_2), new PrintStream(out));
    Assertions.assertArrayEquals(expected, out.toByteArray());
  }

  @Test
  void readAndPrint3() throws IOException {
    final byte[] expected = Files.readAllBytes(Paths.get(OUTPUT_3));
    final ByteArrayOutputStream out = new ByteArrayOutputStream();
    Main.readAndPrint(new FileInputStream(INPUT_3), new PrintStream(out));
    Assertions.assertArrayEquals(expected, out.toByteArray());
  }
}
