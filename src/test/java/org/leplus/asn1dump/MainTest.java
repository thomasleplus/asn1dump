package org.leplus.asn1dump;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

class MainTest {

  public static final String INPUT_1 = "src/test/resources/sample1.der";
  public static final String INPUT_2 = "src/test/resources/sample2.der";
  public static final String INPUT_3 = "src/test/resources/sample3.der";
  public static final String OUTPUT_1 = "src/test/resources/sample1.txt";
  public static final String OUTPUT_2 = "src/test/resources/sample2.txt";
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
