#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

struct Coords {
    int x, y, z;
};

struct BoxDistance {
    int i, j;
    double dist;
};

struct UnionFind {
    vector<int> parent, rank;
    int components;

    UnionFind(int n) : parent(n), rank(n, 0), components(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;

        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        components--;
        return true;
    }
};

double distance(const Coords& a, const Coords& b);

int main() {

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file";
        return 1;
    }

    auto start_time = chrono::high_resolution_clock::now();

    vector<Coords> boxes;
    string line;

    while (getline(file, line)) {
        
        stringstream ss(line);
        string value;

        Coords p;
        getline(ss, value, ',');
        p.x = stoi(value);

        getline(ss, value, ',');
        p.y = stoi(value);

        getline(ss, value, ',');
        p.z = stoi(value);

        boxes.push_back(p);
    }

    vector<BoxDistance> distances;

    for (int i = 0; i < boxes.size(); i++) {
        for (int j = i + 1; j < boxes.size(); j++) {
            distances.push_back({i, j, distance(boxes[i], boxes[j])
        });
        }
    }

    sort(distances.begin(), distances.end(),
    [](const BoxDistance& a, const BoxDistance& b) {
        return a.dist < b.dist;
    });


    UnionFind uf(boxes.size());

    int last_u = -1, last_v = -1;

    for (const auto& e : distances) {
        if (uf.unite(e.i, e.j)) {
            last_u = e.i;
            last_v = e.j;

            if (uf.components == 1)
                break;
        }
    }

    long long final_product =
    static_cast<long long>(boxes[last_u].x) *
    static_cast<long long>(boxes[last_v].x);

    cout << "Final X multiplication: " << final_product << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time: " << duration.count() << " ms\n";

    file.close();

    return 0;
}

double distance(const Coords& a, const Coords& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    long long dz = a.z - b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}