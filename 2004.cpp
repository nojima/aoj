#include <algorithm>
#include <numeric>
#include <queue>
#include <iostream>
#include <iomanip>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); ++i)

struct Event {
  double time;
  function<void ()> proc;

  Event(double time, function<void ()> proc): time(time), proc(proc) {}
  bool operator<(const Event& rhs) const { return rhs.time < time; }
};

struct Elevator {
  int capacity, speed, stopTime, target, size, rev, dir;
  double pos, time;

  Elevator(): size(0), rev(0), dir(1), time(0) {}
};

int floorCount, elevatorCount, floorDistance;
int initFireFloor, burningTime, upSpreadTime, downSpreadTime;
vector<Elevator> elevators;
vector<int> deviceCount;
vector<bool> floorBurned;
priority_queue<Event> Q;
double ansTime;
int ansCount;

void changeTarget(double time, int elevator, int stopTime);

int newTarget(int elevator, int currentTarget) {
  Elevator& e = elevators[elevator];
  if (e.size == e.capacity)
    return 0;
  for (int i = currentTarget - 1; i > 0; --i)
    if (!floorBurned[i] && deviceCount[i] > 0)
      return i;
  return 0;
}

void onReach(double time, int floor, int elevator, int rev) {
  Elevator& e = elevators[elevator];
  if (rev < e.rev) return;

  int n = min(deviceCount[floor], e.capacity - e.size);
  deviceCount[floor] -= n;
  e.size += n;
  if (floor == 0) {
    if (e.size > 0) {
      ansTime = max(ansTime, time + e.stopTime);
      ansCount += e.size;
      e.size = 0;
      e.target = floorCount;
      changeTarget(time, elevator, e.stopTime);
    }
  } else {
    if (deviceCount[floor] == 0) {
      REP(i, elevatorCount)
        if (i != elevator && elevators[i].target == floor)
          changeTarget(time, i, 0);
    }
    changeTarget(time, elevator, e.stopTime);
  }
}

void onBurned(double time, int floor) {
  floorBurned[floor] = true;
  REP(i, elevatorCount)
    if (elevators[i].target == floor)
      changeTarget(time, i, 0);
}

void changeTarget(double time, int elevator, int stopTime) {
  Elevator& e = elevators[elevator];
  int nextTarget = newTarget(elevator, e.target);
  if (e.target == nextTarget) return;
  e.target = nextTarget;
  e.pos += e.dir * (time - e.time) * e.speed;
  e.time = time + stopTime;
  double dist = e.target * floorDistance - e.pos;
  e.dir = dist >= 0 ? 1 : -1;
  e.rev += 1;
  double newTime = time + stopTime + fabs(dist) / e.speed;
  Q.push(Event(newTime, bind(onReach, newTime, e.target, elevator, e.rev)));
}

int main() {
  while (cin >> floorCount >> elevatorCount, floorCount | elevatorCount) {
    deviceCount.resize(floorCount);
    elevators.assign(elevatorCount, Elevator());
    floorBurned.assign(floorCount, false);

    cin >> floorDistance;
    REP(i, floorCount) cin >> deviceCount[i];
    REP(i, elevatorCount) {
      Elevator& e = elevators[i];
      cin >> e.capacity >> e.speed >> e.stopTime >> e.pos;
      e.pos = (e.pos - 1) * floorDistance;
      e.target = floorCount;
    }
    cin >> initFireFloor >> burningTime >> upSpreadTime >> downSpreadTime; --initFireFloor;

    ansTime = 0;
    ansCount = deviceCount[0];
    deviceCount[0] = 0;
    REP(floor, floorCount) {
      double t = floor >= initFireFloor ? upSpreadTime * (floor - initFireFloor) + burningTime
                                        : downSpreadTime * (initFireFloor - floor) + burningTime;
      Q.push(Event(t, bind(onBurned, t, floor)));
    }
    REP(i, elevatorCount) changeTarget(0, i, 0);

    for (; !Q.empty(); Q.pop()) { Q.top().proc(); }

    cout << setprecision(20);
    cout << ansCount << " " << ansTime << endl;
  }
}
