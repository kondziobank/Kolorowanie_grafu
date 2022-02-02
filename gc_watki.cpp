#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<cstdlib>
#include <thread>
using namespace std;
class Graph
{
public:
    Graph(const Graph& graph)
    {
        V = graph.V;
        E = graph.E;
        for (int i = 0; i <= V; i++)
        {
            Edges.push_back({});
        }
        for (int i = 0; i <= V; i++)
        {
            for (int j = 0; j < graph.Edges[i].size(); j++)
            {
                Edges[i][j] = graph.Edges[i][j];
            }
        }
    }
    Graph(int V)
    {
        this->V = V;
        for (int i = 0; i <= V; i++)
        {
            this->Edges.push_back({}); //ustawiamy macierz sąsiedztwa na pustą 
        }
    }
    void read_graph()
    {
        int v1, v2;
        char e;
        while (cin >> v1 >> v2)  // wczytujemy krawędzie i dodajemy 
        {
            this->Edges[v1].push_back(v2);
            this->Edges[v2].push_back(v1);
            this->E++; // aktualizujemy liczbe krawędzi
        }
    }
    void add_edges(int a, int b) // można dodać krawędź w celach testowych  poza wczytaniem grafu
    {
        this->Edges[a].push_back(b);
        this->Edges[b].push_back(a);
        this->E++;
        //aktualizujemy liczbę krawędzi
    }
    int Brutal_solution()
    {
        /*
            sprawdzamy wszystkie kolejności wierzchołków
        */
        vector<int> order;
        for (int i = 1; i <= V; i++)
        {
            order.push_back(i);
        }
        int result = this->V + 1;
        while (next_permutation(order.begin(), order.end()))
        {
            result = min(result, solution(order));
        }
        return result;
    }
    int greedy_solution()
    {
        vector<pair<int, int>>tmp_order; // przygotowywujemy wektor kolejności w postaci,
        // par <wierzchołek, stopień wierzchołka>
        for (int i = 1; i <= this->V; i++)
        {
            tmp_order.push_back({ this->Edges[i].size(),i });
        }
        sort(tmp_order.begin(), tmp_order.end());
        vector<int>order; // właściwiy wektor kolejności
        for (pair<int, int> i : tmp_order)
        {
            order.push_back(i.second);
        }
        return solution(order);
    }
    int V;  //liczba wierzchołków
    int E = 0;  //liczba krawędzi, aktualizowana przy dodawaniu krawędzi
    vector<vector<int>>Edges; // macierz następników 
private:
    int solution(vector<int>order)
    {
        int result = this->V + 1;
        vector<int>color(this->V + 1); //tutaj trzymamy aktualne kolory wierzchołków
        vector<vector<int>>vertex_colors(this->V + 1); //tutaj trzymamy kolory z którymi sąsiaduje dany wierzchołek
        int max_color_for_order = 0;
        for (int v : order)  // iterujemy się po każdym wierzchołku
        {
            int min_color = 1;
            while (find(vertex_colors[v].begin(), vertex_colors[v].end(), min_color) != vertex_colors[v].end())
                //szukamy najmniejszego dobrego koloru
            {
                min_color++;
            }
            max_color_for_order = max(max_color_for_order, min_color);
            color[v] = min_color;
            for (int neig : this->Edges[v])
            {
                vertex_colors[neig].push_back(min_color);
            }
        }
        return max_color_for_order;
    }
public:
    pair<int, vector<int>> Heurystyka(int pocz, int m, int e, int nep, int nsp, int k)
    {
        /*
        int pocz; początkowa liczba pszczół
        int m; liczba wybranych lokalizacji
        int e;elitarne lokalizacje
        int nep;  pszczoły rekrutowane do najlepszych lokalizacji
        int nsp;pszczoly rekrutowane do gorszych lokalizacji
        int k;  rozmiar  przeszukiwanego sąsiedzstwa*/
        pair<int, vector<int>> global_min = { V + 1, {} };
        vector<vector<int>>Populacja(pocz);
        vector<int>number(V);
        for (int i = 0; i < V; i++)
        {
            number[i] = (i + 1);
        }
        for (int i = 0; i < pocz; i++)
        {
            random_shuffle(number.begin(), number.end());
            Populacja[i] = number;
        }
        int licznik = 0;
        while (true)
        {
            licznik++;
            if (licznik == 11)
            {
                return global_min;
            }
            vector<pair<int, vector<int>>>ranking;  // <jakość rozwiązania, permutacja>
            for (int i = 0; i < Populacja.size(); i++)
            {
                ranking.push_back({ solution(Populacja[i]),Populacja[i] });
            }
            sort(ranking.begin(), ranking.end());
            vector<pair<int, vector<int>>>Elitarne; // zbiór rozwiązań elitarnych
            Elitarne.insert(Elitarne.begin(), ranking.begin(), ranking.begin() + e);
            vector<pair<int, vector<int>>>Mocne; // zbiór M-El
            Mocne.insert(Mocne.begin(), ranking.begin() + e + 1, ranking.begin() + e + m + 1);
            pair<int, vector<int>>bestEl = ranking[0];
            global_min = min(bestEl, global_min);
            // cout<<global_min.first<<"\n";
            bool warunek = true;
            if (warunek) {}//dopóki nie jest skończony warunek zatrzymania obliczeń 
            //tego ifa trzeba dopisać
            Populacja.clear();
            int Ei_counter = nep; // licznik wykorzystanych elitarnych pszczół
            //cout<<"tak";
            for (auto permutacja : Elitarne)
            {
                int e_i;
                //int e_i = nep / e + rand() % (nep % e);
                if (nep % Elitarne.size() == 0)
                {
                    e_i = nep / Elitarne.size();
                }
                else
                {
                    e_i = nep / Elitarne.size() + rand() % (nep % Elitarne.size());
                }
                Ei_counter -= e_i;
                vector<pair<int, int>>zmiany;
                for (int j = 0; j < e_i; j++)
                {
                    for (int i = 0; i < k; i++)
                    {
                        int a, b;
                        a = rand() % V;
                        b = rand() % V;
                        swap(permutacja.second[a], permutacja.second[b]);
                        zmiany.push_back({ a,b });
                    }
                    Populacja.push_back(permutacja.second);  //dodajemy e_i rozwiązań eliternego wyniku
                    for (int i = k - 1; i >= 0; i--)
                    {
                        swap(permutacja.second[zmiany[i].first], permutacja.second[zmiany[i].second]); //tutaj cofamy zmiany
                    }
                }
            }
            for (int i = 0; i < Ei_counter; i++)
            {
                for (int i = 0; i < k; i++)
                {
                    int a, b;
                    a = rand() % V;
                    b = rand() % V;
                    swap(Elitarne[0].second[a], Elitarne[0].second[b]);
                }
                Populacja.push_back(Elitarne[0].second);
            }
            int mi_counter = nsp;
            for (int i = 0; i < nsp; i++)
            {
                int numer_permutacji = rand() % (m);
                vector<pair<int, int>>zmiany;
                for (int i = 0; i < k; i++)
                {
                    int a, b;
                    a = rand() % V;
                    b = rand() % V;
                    swap(Mocne[numer_permutacji].second[a], Mocne[numer_permutacji].second[b]);
                    zmiany.push_back({ a,b });
                }
                Populacja.push_back(Mocne[numer_permutacji].second);
                for (int i = k - 1; i >= 0; i--)
                {
                    swap(Mocne[numer_permutacji].second[zmiany[i].first], Mocne[numer_permutacji].second[zmiany[i].second]);
                }
            }


        }
    }
};
int funkcja(int n)
{
    return n & (n / 3) | (n + 3);
}

int main()
{
    vector<thread>threads;
    int wyniki[4];
    int V, E;
    cin >> V;//>> E;
    Graph graf0(V);
    Graph graf1(V);
    Graph graf2(V);
    Graph graf3(V);
    int a, b;
    while (cin >> a >> b)
    {
        graf0.add_edges(a, b);
        graf1.add_edges(a, b);
        graf2.add_edges(a, b);
        graf3.add_edges(a, b);
    }

    int a0 = -1, a1 = -1, a2 = -1, a3 = -1;
    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            threads.push_back(thread([&]()
                {
                    a0 = graf0.Heurystyka(100, 20, 30, 100, 70, 1).first;
                    //  a0 = funkcja(10);
                }));
        }
        if (i == 1)
        {
            threads.push_back(thread([&]()
                {
                    a1 = graf1.Heurystyka(100, 20, 30, 100, 70, 1).first;
                    // a1 = funkcja(11);
                }));
        }
        if (i == 2)
        {
            threads.push_back(thread([&]()
                {
                    a2 = graf2.Heurystyka(100, 20, 30, 100, 70, 1).first;
                    // a2 = funkcja(12);
                }));
        }
        if (i == 3)
        {
            threads.push_back(thread([&]()
                {
                    a3 = graf3.Heurystyka(100, 20, 30, 100, 70, 1).first;
                    // a3 = funkcja(15);
                }));
        }
    }
    for (auto& thread : threads)
    {
        thread.join();
    }
    vector<int>v = { a0,a1,a2,a3 };
    sort(v.begin(), v.end());
    //cout << v[0] << "\n";
    cout << graf0.greedy_solution() << ":" << v[0] << "\n";
    //pair<int, vector<int>> Heurystyka(int pocz, int m, int e, int nep, int nsp, int k)
    //nep+nsp>=m+e
    //pocz>=m+e
    return 0;
}