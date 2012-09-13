#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace std::placeholders;

enum Relation {
  FATHER, MOTHER, SON, DAUGHTER, HUSBAND, WIFE, BROTHER, SISTER, GRANDFATHER,
  GRANDMOTHER, GRANDSON, GRANDDAUGHTER, UNCLE, AUNT, NEPHEW, NIECE
};

enum Sex { MALE, FEMALE };

struct Node {
  Node* parent[2];
  vector<Node*> sons;
  vector<Node*> daughters;
  int distance;

  explicit Node(int distance): distance(distance) {
    parent[MALE] = parent[FEMALE] = nullptr;
  }
};

template <class T> inline int size(const T& x) { return x.size(); }

vector<string> split(const string& str, char delimiter) {
  vector<string> result;
  for (int i = 0; i < size(str); ++i) {
    string word;
    for ( ; i < size(str) && str[i] != delimiter; ++i)
      word += str[i];
    result.push_back(move(word));
  }
  return result;
}

bool startsWith(const string& str, const string& prefix) {
  if (str.size() < prefix.size()) return false;
  for (int i = 0; i < size(prefix); ++i)
    if (str[i] != prefix[i])
      return false;
  return true;
}

vector<Relation> relations;
int ansMax, ansMin;

void withParent(Node* node, Sex sex, function<void (Node*)> proc) {
  if (node->parent[sex]) {
    proc(node->parent[sex]);
  } else {
    Node n(node->distance + 1);
    if (sex == MALE)
      n.sons.push_back(node);
    else
      n.daughters.push_back(node);
    node->parent[sex] = &n;
    proc(&n);
    node->parent[sex] = nullptr;
  }
}

void withSon(Node* node, Sex sex, function<void (Node*)> proc) {
  for (int i = 0; i < size(node->sons); ++i)
    proc(node->sons[i]);
  Node n(node->distance + 1);
  n.parent[MALE] = node;
  node->sons.push_back(&n);
  proc(&n);
  node->sons.pop_back();
}

void withDaughter(Node* node, Sex sex, function<void (Node*)> proc) {
  for (int i = 0; i < size(node->daughters); ++i)
    proc(node->daughters[i]);
  Node n(node->distance + 1);
  n.parent[FEMALE] = node;
  node->daughters.push_back(&n);
  proc(&n);
  node->daughters.pop_back();
}

void withBrother(Node* node, Sex sex, function<void (Node*)> proc) {
  auto inner = [=](Node* s){ if (s != node) proc(s); };
  withParent(node, sex, bind(withSon, _1, MALE, inner));
}

void withSister(Node* node, Sex sex, function<void (Node*)> proc) {
  auto inner = [=](Node* d){ if (d != node) proc(d); };
  withParent(node, sex, bind(withDaughter, _1, MALE, inner));
}

void dfs(Node* node, Sex sex, int index) {
  if (index == size(relations)) {
    ansMax = max(ansMax, node->distance);
    ansMin = min(ansMin, node->distance);
    return;
  }

  Relation r = relations[index];
  function<void (Node*)> dfsMale = bind(dfs, _1, MALE, index + 1);
  function<void (Node*)> dfsFemale = bind(dfs, _1, FEMALE, index + 1);

  if (r == FATHER) {
    withParent(node, sex, dfsMale);
  } else if (r == MOTHER) {
    withParent(node, sex, dfsFemale);
  } else if (r == SON) {
    withSon(node, sex, dfsMale);
  } else if (r == DAUGHTER) {
    withDaughter(node, sex, dfsFemale);
  } else if (r == HUSBAND) {
    dfs(node, MALE, index + 1);
  } else if (r == WIFE) {
    dfs(node, FEMALE, index + 1);
  } else if (r == BROTHER) {
    withBrother(node, sex, dfsMale);
  } else if (r == SISTER) {
    withSister(node, sex, dfsFemale);
  } else if (r == GRANDFATHER) {
    withParent(node, sex, bind(withParent, _1, MALE, dfsMale));
    withParent(node, sex, bind(withParent, _1, FEMALE, dfsMale));
  } else if (r == GRANDMOTHER) {
    withParent(node, sex, bind(withParent, _1, MALE, dfsFemale));
    withParent(node, sex, bind(withParent, _1, FEMALE, dfsFemale));
  } else if (r == GRANDSON) {
    withSon(node, sex, bind(withSon, _1, MALE, dfsMale));
    withDaughter(node, sex, bind(withSon, _1, FEMALE, dfsMale));
  } else if (r == GRANDDAUGHTER) {
    withSon(node, sex, bind(withDaughter, _1, MALE, dfsFemale));
    withDaughter(node, sex, bind(withDaughter, _1, FEMALE, dfsFemale));
  } else if (r == UNCLE) {
    withParent(node, sex, bind(withBrother, _1, MALE, dfsMale));
    withParent(node, sex, bind(withBrother, _1, FEMALE, dfsMale));
  } else if (r == AUNT) {
    withParent(node, sex, bind(withSister, _1, MALE, dfsFemale));
    withParent(node, sex, bind(withSister, _1, FEMALE, dfsFemale));
  } else if (r == NEPHEW) {
    withBrother(node, sex, bind(withSon, _1, MALE, dfsMale));
    withSister(node, sex, bind(withSon, _1, FEMALE, dfsMale));
  } else if (r == NIECE) {
    withBrother(node, sex, bind(withDaughter, _1, MALE, dfsFemale));
    withSister(node, sex, bind(withDaughter, _1, FEMALE, dfsFemale));
  } else {
    assert(false);
  }
}

int main() {
  string line;
  getline(cin, line);
  for (int T = atoi(line.c_str()); T; --T) {
    ansMax = 0;
    ansMin = INT_MAX;
    relations.clear();

    getline(cin, line);
    vector<string> words(split(line, ' '));
    for (int i = 3; i < size(words); ++i) {
      if (startsWith(words[i], "father"))
        relations.push_back(FATHER);
      else if (startsWith(words[i], "mother"))
        relations.push_back(MOTHER);
      else if (startsWith(words[i], "son"))
        relations.push_back(SON);
      else if (startsWith(words[i], "daughter"))
        relations.push_back(DAUGHTER);
      else if (startsWith(words[i], "husband"))
        relations.push_back(HUSBAND);
      else if (startsWith(words[i], "wife"))
        relations.push_back(WIFE);
      else if (startsWith(words[i], "brother"))
        relations.push_back(BROTHER);
      else if (startsWith(words[i], "sister"))
        relations.push_back(SISTER);
      else if (startsWith(words[i], "grandfather"))
        relations.push_back(GRANDFATHER);
      else if (startsWith(words[i], "grandmother"))
        relations.push_back(GRANDMOTHER);
      else if (startsWith(words[i], "grandson"))
        relations.push_back(GRANDSON);
      else if (startsWith(words[i], "granddaughter"))
        relations.push_back(GRANDDAUGHTER);
      else if (startsWith(words[i], "uncle"))
        relations.push_back(UNCLE);
      else if (startsWith(words[i], "aunt"))
        relations.push_back(AUNT);
      else if (startsWith(words[i], "nephew"))
        relations.push_back(NEPHEW);
      else if (startsWith(words[i], "niece"))
        relations.push_back(NIECE);
      else
        assert(false);
    }

    Node root(0);
    dfs(&root, MALE, 0);
    dfs(&root, FEMALE, 0);
    cout << ansMax << " " << ansMin << endl;
  }
}
