module aoj;
import std.algorithm;
import std.ascii;
import std.range;
import std.stdio;
import std.string;

void main() {
  string name, type;
  for (;;) {
    string[] line = split(readln());
    name = line[0];
    type = line[1];
    if (type == "X") { break; }
    string[] words;
    ulong prev = 0;
    foreach (i; 1 .. name.length) {
      if (name[i] == '_') {
        words ~= name[prev .. i];
        prev = i + 1;
      } else if (isUpper(name[i])) {
        words ~= name[prev .. i];
        prev = i;
      }
    }
    words ~= name[prev .. $];
    if (type == "U") {
      writeln(join(words.map!capitalize, ""));
    } else if (type == "L") {
      write(toLower(words[0]));
      writeln(join(words[1 .. $].map!capitalize, ""));
    } else if (type == "D") {
      writeln(join(words.map!toLower, "_"));
    } else {
      assert(false);
    }
  }
}
