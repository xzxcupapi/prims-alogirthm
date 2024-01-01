#include <iostream>
#include <climits>

using namespace std;

const int INF = INT_MAX;

int main() {
    int simpul, sisi;

    // Input jumlah simpul & sisi
    cout << "Prim's Algorithm \n";
    cout << "Masukkan jumlah simpul: ";
    cin >> simpul;

    cout << "Masukkan jumlah sisi: ";
    cin >> sisi;

    int graph[100][100] = {0};

    // Input (simpul awal, simpul tujuan, bobot)
    cout << "Input bobot sisi dengan format simpul awal, simpul akhir, dan bobot (format: A B 2):\n";
    char from, to;
    int weight;

    for (int i = 0; i < sisi; ++i) {
        cout << "Sisi ke - " << i + 1 << " : ";
        cin >> from >> to >> weight;
        graph[from - 'A'][to - 'A'] = graph[to - 'A'][from - 'A'] = weight;
    }

    // Inisialisasi variabel untuk algoritma Prim
    int parent[100];
    int key[100];
    bool mstSet[100];

    // Inisialisasi key dan mstSet
    for (int i = 0; i < simpul; ++i) {
        key[i] = INF;
        mstSet[i] = false;
    }

    key[0] = 0;

    // Inisialisasi variabel untuk output yang diminta
    bool known[100] = {false};
    int dv[100];
    int pv[100];

    // Inisialisasi dv dan pv
    for (int i = 0; i < simpul; ++i) {
        dv[i] = INF;
        pv[i] = -1;
    }

    dv[0] = 0;
    known[0] = true;  // Inisialisasi simpul awal sebagai yang telah diketahui

    // Algoritma prim: looping bobot terendah yang terhubung ke simpul
    // Dilanjutkan dari simpul tujuan dari sisi dengan bobot terendah dari simpul sebelumnya
    for (int count = 0; count < simpul - 1; ++count) {
        int u = -1;
        for (int v = 0; v < simpul; ++v) {
            if (!mstSet[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        mstSet[u] = true;

        for (int v = 0; v < simpul; ++v) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];

                // Update dv dan pv
                dv[v] = graph[u][v];
                pv[v] = u;

                // Update known berdasarkan simpul yang sudah termasuk dalam MST
                known[v] = true;
            }
        }
    }

    // Menampilkan MST
    cout << "Minimum Spanning Tree (MST):\n";
    cout << "Step \t Sisi \t Bobot\n";
    int totalWeight = 0;

    for (int step = 1; step < simpul; ++step) {
        int i = step;
        totalWeight += graph[i][parent[i]];

        cout << step << " \t " << char(parent[i] + 'A') << " - " << char(i + 'A') << " \t " << graph[i][parent[i]] << "\n";
    }

    cout << "\nTotal bobot: " << totalWeight << "\n";

    // Menampilkan output yang diminta
    cout << "\nV \t known \t dv \t pv\n";
    for (int i = 0; i < simpul; ++i) {
        cout << "V" << i + 1 << " \t " << (known[i] ? "1" : "0") << " \t " << dv[i] << " \t ";
        if (pv[i] != -1) {
            cout << "V" << pv[i] + 1 << "\n";
        } else {
            cout << "0\n";
        }
    }

    return 0;
}
