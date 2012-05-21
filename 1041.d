module aoj;
import std.conv;
import std.stdio;
import std.string;

int getInt() { return to!int(chomp(readln())); }

void main() {
  int n;
  while ((n = getInt()) != 0) {
    int sum = 0;
    foreach (i; 0 .. n/4) {
      sum += getInt();
    }
    writeln(sum);
  }
}
