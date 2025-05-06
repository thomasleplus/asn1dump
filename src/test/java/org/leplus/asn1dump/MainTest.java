package org.leplus.asn1dump;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

class MainTest {

  public static final String INPUT_1 = "src/test/resources/sample1.der";
  public static final String INTPUT_2 = "src/test/resources/sample2.der";
  public static final String OUTPUT = "src/test/resources/samples.txt";

  @Test
  void readAndPrint1() throws IOException {
    final byte[] expected = Files.readAllBytes(Paths.get(OUTPUT));
    final ByteArrayOutputStream out = new ByteArrayOutputStream();
    Main.readAndPrint(new FileInputStream(INPUT_1), new PrintStream(out));
    Main.readAndPrint(new FileInputStream(INTPUT_2), new PrintStream(out));
    Assertions.assertArrayEquals(expected, out.toByteArray());
  }

  @Test
  void readAndPrint2() throws IOException {
    final byte[] expected = Files.readAllBytes(Paths.get(OUTPUT));
    final ByteArrayOutputStream out = new ByteArrayOutputStream();
    Main.readAndPrint(
        new SequenceInputStream(new FileInputStream(INPUT_1), new FileInputStream(INTPUT_2)),
        new PrintStream(out));
    Assertions.assertArrayEquals(expected, out.toByteArray());
  }
}
