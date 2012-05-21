module aoj;
import std.array;
import std.algorithm;
import std.conv;
import std.range;
import std.stdio;
import std.string;

void main() {
  int n;
  while ((n = to!int(chomp(readln()))) != 0) {
    int[] I = new int[n];
    int[] U = new int[n];
    int[] A = new int[n];
    int[] P = new int[n];

    foreach (i; 0 .. n) {
      string[] line = split(readln());
      I[i] = to!int(line[0]);
      U[i] = to!int(line[1]);
      A[i] = -to!int(line[2]);
      P[i] = to!int(line[3]);
    }

    sort(zip(A, P, I, U));

    int[] ans;
    int[] count = new int[1001];

    foreach (i; 0 .. n) {
      foreach (j; 0 .. 3) {
        if (ans.length < [10, 20, 26][j]) {
          if (count[U[i]] < 3 - j) {
            ans ~= I[i];
            count[U[i]] += 1;
            break;
          }
        }
      }
    }

    foreach (id; ans) { writeln(id); }
  }
}
