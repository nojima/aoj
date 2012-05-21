module aoj;
import std.array;
import std.algorithm;
import std.conv;
import std.range;
import std.stdio;
import std.string;
import std.typecons;

class FixedQueue(T) {
  private T[] mData;
  private int mCapacity;
  private int mHead;
  private int mTail;

  this(int capacity) {
    mHead = mTail = 0;
    mCapacity = capacity;
    mData = new T[capacity];
  }

  void push(T x) {
    mData[mHead] = x;
    mHead = (mHead + 1) % mCapacity;
  }

  T pop() {
    scope(exit) { mTail = (mTail + 1) % mCapacity; }
    return mData[mTail];
  }

  bool empty() { return mHead == mTail; }
}

string getLine() {
  string ret;
  do {
    ret = chomp(readln());
  } while (ret.length == 0);
  return ret;
}

void main() {
  for (;;) {
    // Input
    string[] input = split(getLine());
    int H = to!int(input[0]);
    int W = to!int(input[1]);
    auto field = new char[][](H, W);
    if (H == 0 && W == 0) { break; }
    int ay = -1, ax = -1;
    int by = -1, bx = -1;
    foreach (y; 0 .. H) {
      string line = readln();
      foreach (x; 0 .. W) {
        if (line[x] == 'A') {
          ay = y;
          ax = x;
          field[y][x] = '.';
        } else if (line[x] == 'B') {
          by = y;
          bx = x;
          field[y][x] = '.';
        } else {
          field[y][x] = line[x];
        }
      }
    }
    string pattern = chomp(readln());

    // BFS
    immutable(int[]) dy = [-1, 0, 1, 0];
    immutable(int[]) dx = [0, -1, 0, 1];
    alias Tuple!(int, "y", int, "x") State;
    auto Q = new FixedQueue!State(2 * (H + W));
    auto cost = new int[][](H, W);
    foreach (c; cost) { c[] = -1; }
    Q.push(State(ay, ax));
    cost[ay][ax] = 0;
    while (!Q.empty()) {
      State s = Q.pop();
      foreach (k; 0 .. 4) {
        int ny = s.y + dy[k];
        int nx = s.x + dx[k];
        if (0 <= ny && ny < H && 0 <= nx && nx < W) {
          if (field[ny][nx] == '.' && cost[ny][nx] == -1) {
            cost[ny][nx] = cost[s.y][s.x] + 1;
            Q.push(State(ny, nx));
          }
        }
      }
    }

    // Simulation
    bool ok = false;
    int limit = cast(int)pattern.length * H * W;
    foreach (time; 0 .. limit) {
      if (cost[by][bx] != -1 && cost[by][bx] <= time) {
        writefln("%d %d %d", time, by, bx);
        ok = true;
        break;
      }
      switch (pattern[time % pattern.length]) {
      case '5': break;
      case '8': by -= 1; break;
      case '6': bx += 1; break;
      case '4': bx -= 1; break;
      case '2': by += 1; break;
      default: assert(false);
      }
      by = max(0, min(H - 1, by));
      bx = max(0, min(W - 1, bx));
    }
    if (!ok) { writeln("impossible"); }
  }
}
