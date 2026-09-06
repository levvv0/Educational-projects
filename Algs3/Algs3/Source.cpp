#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>
#include "DSU.cpp"

using namespace std;

double distanceBetweenPoints(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) +
        (a.y - b.y) * (a.y - b.y));
}

int main() {
    setlocale(LC_ALL, "Russian");

    int N, K;

    cout << "Введите количество точек N: ";
    cin >> N;

    cout << "Введите количество кластеров K: ";
    cin >> K;
    

    if (K <= 0 || K > N) {
        cout << "K должно быть больше 1 и меньше N.\n";
        return 0;
    }

    vector<Point> points(N);

    cout << "\nВведите координаты точек:\n";
    for (int i = 0; i < N; i++) {
        cout << "Точка " << i + 1 << " (x y): ";
        points[i].x = rand() % 11;
        points[i].y = rand() % 11;
    }

    vector<vector<double>> weightMatrix(N, vector<double>(N, 0.0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                weightMatrix[i][j] = distanceBetweenPoints(points[i], points[j]);
            }
        }
    }

    cout << "\nМатрица весов полного графа:\n";
    cout << fixed << setprecision(2);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(8) << weightMatrix[i][j] << " ";
        }
        cout << endl;
    }

    vector<Edge> edges;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            Edge e;
            e.u = i;
            e.v = j;
            e.w = weightMatrix[i][j];
            edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
        });

    DSU dsu(N);
    vector<Edge> mst;

    for (const Edge& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
        }

        if ((int)mst.size() == N - 1) {
            break;
        }
    }

    cout << "\nРебра минимального остова:\n";
    for (const Edge& e : mst) {
        cout << "(" << e.u + 1 << " - " << e.v + 1 << ") "
            << "вес = " << e.w << endl;
    }

    int edgesToTake = N - K;

    vector<vector<int>> adjacencyMatrix(N, vector<int>(N, 0));

    for (int i = 0; i < edgesToTake; i++) {
        int u = mst[i].u;
        int v = mst[i].v;

        adjacencyMatrix[u][v] = 1;
        adjacencyMatrix[v][u] = 1;
    }

    cout << "\nМатрица смежности:\n";

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(3) << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    vector<bool> visited(N, false);
    vector<vector<int>> components;

    for (int start = 0; start < N; start++) {
        if (!visited[start]) {
            vector<int> component;
            queue<int> q;

            q.push(start);
            visited[start] = true;

            while (!q.empty()) {
                int current = q.front();
                q.pop();

                component.push_back(current);

                for (int next = 0; next < N; next++) {
                    if (adjacencyMatrix[current][next] == 1 && !visited[next]) {
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }

            components.push_back(component);
        }
    }

    cout << "\nКомпненты связности:\n";

    for (int i = 0; i < (int)components.size(); i++) {
        double minX = points[components[i][0]].x;
        double maxX = points[components[i][0]].x;
        double minY = points[components[i][0]].y;
        double maxY = points[components[i][0]].y;

        double sumX = 0.0;
        double sumY = 0.0;

        cout << "\nКластер " << i + 1 << ":\n";
        cout << "Вершины: ";

        for (int v : components[i]) {
            cout << v + 1 << " ";

            double x = points[v].x;
            double y = points[v].y;

            minX = min(minX, x);
            maxX = max(maxX, x);
            minY = min(minY, y);
            maxY = max(maxY, y);

            sumX += x;
            sumY += y;
        }

        double centroidX = sumX / components[i].size();
        double centroidY = sumY / components[i].size();

        cout << endl;
        cout << "Количество вершин: " << components[i].size() << endl;
        cout << "Минимальное значение x: " << minX << endl;
        cout << "Максимальное значение x: " << maxX << endl;
        cout << "Минимальное значение y: " << minY << endl;
        cout << "Максимальное значение y: " << maxY << endl;
        cout << "Центроид: (" << centroidX << "; " << centroidY << ")" << endl;
    }

    return 0;
}