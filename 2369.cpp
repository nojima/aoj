#include <cstdio>
using namespace std;

char buffer[512];

int parse(int i) {
  if (buffer[i] == 'm') {
    int next1 = parse(i+1);
    if (buffer[next1] == 'e') {
      int next2 = parse(next1+1);
      if (buffer[next2] == 'w') { return next2+1; }
    }
  }
  return i;
}

int main() {
  while (fgets(buffer, sizeof(buffer), stdin)) {
    int ret = parse(0);
    if (buffer[ret] == '\0' || buffer[ret] == '\n') {
      puts("Cat");
    } else {
      puts("Rabbit");
    }
  }
}
