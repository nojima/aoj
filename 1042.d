module aoj;
import std.array;
import std.stdio;
import std.string;

void main() {
  string line;
  while ((line = chomp(readln())) != "END OF INPUT") {
    foreach (word; split(line, " ")) {
      write(word.length);
    }
    writeln();
  }
}
