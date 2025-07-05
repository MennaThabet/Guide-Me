#include <bits/stdc++.h>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
int nodes_cnt, city_id;
string source, destination;
int budget;
vector<vector<pair<int, pair<string, int>>>> adj;
vector<vector<int>> adj_traversal;
vector<int> dfs_sequence, bfs_sequence, vis;
unordered_map<string, int> City_ID;
unordered_map<int, string> City_Name;
set<pair<int, vector<string>>> All_Paths;
deque<pair<int, int>> city_city;
vector<vector<bool>> is_there_edge;
void dfs_traversal(int u)
{
    vis[u] = 1;
    dfs_sequence.push_back(u);
    for (auto& v : adj_traversal[u])
    {
        if (!vis[v])
            dfs_traversal(v);
    }
}

void bfs_traversal(int src)
{
    queue<int> q;
    q.push(src);
    vis[src] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto& v : adj_traversal[u])
        {
            if (!vis[v])
            {
                q.push(v);
                vis[v] = 1;
            }
        }
        bfs_sequence.push_back(u);
    }
}
void User_Traversing()
{
    cout << "Please enter the start city: \n";
    string st;
    cin >> st;

    transform(st.begin(), st.end(), st.begin(), ::tolower);
    st[0] = toupper(st[0]);

    if (City_ID[st])
    {
        cout << "Choose your preferred algorithm to traverse the graph: (for BFS press 0 & for DFS press 1)\n";
        int choice;
        cin >> choice;
        if (!choice)
        {
            cout << "The order of the cities with BFS is: \n";
            bfs_traversal(City_ID[st]);
            for (auto& node : bfs_sequence)
                cout << City_Name[node] << ' ';
            cout << endl;
            bfs_sequence.clear();
        }
        else
        {
            cout << "The order of the cities with DFS is: \n";
            dfs_traversal(City_ID[st]);
            for (auto& node : dfs_sequence)
                cout << City_Name[node] << ' ';
            cout << endl;

            dfs_sequence.clear();
        }
    }
    else
    {
        cout << "\n     please enter a valid city name\n"
            << endl;
    }
}

void dfs_paths(int u, int total_cost, string transportation, vector<string> curr_path)
{
    vis[u] = 1;
    if (u != City_ID[source])
        curr_path.push_back("(" + transportation + ")");
    curr_path.push_back(City_Name[u]);
    if (City_Name[u] == destination)
        All_Paths.insert({ total_cost, curr_path });
    for (auto& v : adj[u])
    {
        if (!vis[v.first])
            dfs_paths(v.first, total_cost + v.second.second, v.second.first, curr_path);
    }
    vis[u] = 0;
}

void Find_Paths_Between_Cities()
{

    cout << "PLease enter the source and destination cities you want to travel and your total budget: \n";
    cout << "Source: ";
    cin >> source;
    cout << "Destination: ";
    cin >> destination;

    transform(source.begin(), source.end(), source.begin(), ::tolower);
    source[0] = toupper(source[0]);
    transform(destination.begin(), destination.end(), destination.begin(), ::tolower);
    destination[0] = toupper(destination[0]);

    if (City_ID[source] && City_ID[destination])
    {
        cout << "Your Budget: ";
        cin >> budget;
        vector<string> parameter_path;
        dfs_paths(City_ID[source], 0, "", parameter_path);
        for (auto& path : All_Paths)
        {
            if (path.first > budget)
                break;
            for (auto& city_or_trans : path.second)
            {
                cout << city_or_trans << ' ';
            }
            cout << path.first << endl;
        }
    }
    else
    {
        cout << "\n     please enter a valid city name\n"
            << endl;
    }
}

bool is_connected(int u)
{
    dfs_traversal(u);
    for (int i = 1; i <= city_id; i++)
    {
        if (!vis[city_id])
            return false;
    }
    return true;
}

bool is_complete() {
    for (int i = 1; i <= city_id; i++) {
        for (int j = 1; j <= city_id; j++) {
            if (!is_there_edge[i][j] && !is_there_edge[j][i])
                return false;
        }
    }
    return true;
}

void Print_all_transportations(int u, int v)
{
    int cnt = 0;
    for (auto& ch : adj[u])
    {
        if (ch.first == v)
            cout << "Transportation " << ++cnt << " = " << ch.second.first << ' ' << ch.second.second << endl;
    }
}

bool update_transportations(int u, int v, pair<string, int> trans1, pair<string, int> trans2)
{
    for (auto& ch : adj[u])
    {
        if (ch.first == v && ch.second.first == trans1.first && ch.second.second == trans1.second)
        {
            ch.second.first = trans2.first, ch.second.second = trans2.second;
            return true;
        }
    }
    return false;
}

void add_transportation(int u, int v, pair<string, int> trans)
{
    bool is_new_neighbour_city = true;
    for (auto& city : adj[u]) {
        if (city.first == v)
            is_new_neighbour_city = false;
    }
    if (is_new_neighbour_city) {
        adj_traversal[u].push_back(v);
        adj_traversal[v].push_back(u);
        is_there_edge[u][v] = is_there_edge[u][v] = 1;
    }
    adj[u].push_back({ v, {trans.first, trans.second} });
    adj[v].push_back({ u, {trans.first, trans.second} });
}

bool delete_transportation(int u, int v, pair<string, int> trans)
{
    bool changed = false;

    for (int i = 0; i < adj[u].size(); i++)
    {
        if (v == adj[u][i].first && trans.first == adj[u][i].second.first && trans.second == adj[u][i].second.second)
        {
            adj[u].erase(adj[u].begin() + i);
            changed = true;
        }
    }
    for (int i = 0; i < adj[v].size(); i++)
    {
        if (u == adj[v][i].first && trans.first == adj[v][i].second.first && trans.second == adj[v][i].second.second)
        {
            adj[v].erase(adj[v].begin() + i);
            changed = true;
        }
    }
    bool neighbour_city_deleted = true;
    for (auto& city : adj[u]) {
        if (city.first == v)
            neighbour_city_deleted = false;
    }
    if (neighbour_city_deleted) {
        for (int i = 0; i < adj_traversal[u].size(); i++)
        {
            if (v == adj_traversal[u][i])
            {
                adj_traversal[u].erase(adj_traversal[u].begin() + i);
                changed = true;
            }
        }
        for (int i = 0; i < adj_traversal[v].size(); i++)
        {
            if (u == adj_traversal[v][i])
            {
                adj_traversal[v].erase(adj_traversal[v].begin() + i);
                changed = true;
            }
        }
        is_there_edge[u][v] = is_there_edge[u][v] = 0;
    }
    return changed;
}

void ReSize(int nodes_cnt)
{
    vis.resize(nodes_cnt + 5);
    adj_traversal.resize(nodes_cnt + 5);
    adj.resize(nodes_cnt + 5);
    is_there_edge.resize(nodes_cnt + 5, vector<bool>(nodes_cnt + 5));
}

void write_data()
{
    string line;

    ofstream file("TransportationMap.txt");

    if (!file.is_open())
    {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    file << nodes_cnt << endl;

    for (auto it = city_city.begin(); it != city_city.end(); it++)
    {
        auto cities = *it;
        line = City_Name[cities.first] + " - " + City_Name[cities.second];
        for (auto& child : adj[cities.first])
        {
            if (child.first == cities.second)
            {
                line = line + " " + child.second.first + " " + to_string(child.second.second);
            }
        }

        file << line << "\n";
        line = "";
    }

    file.close();
}

void reading_input()
{
    int linesNum;
    string source, destination, line, dash;
    ifstream file;
    file.open("TransportationMap.txt");

    if (!file.is_open())
    {
        cout << "Error: Unable to open file." << endl;
        return;
    }



    file >> linesNum;
    file.ignore();
    nodes_cnt = linesNum;
    ReSize(nodes_cnt);
    while (getline(file, line))
    {
        istringstream iss(line);

        iss >> source;
        iss >> dash;
        iss >> destination;

        if (!City_ID[source])
        {
            City_ID[source] = ++city_id;
            City_Name[city_id] = source;
        }
        if (!City_ID[destination])
        {
            City_ID[destination] = ++city_id;
            City_Name[city_id] = destination;
        }
        city_city.push_back({ City_ID[source], City_ID[destination] });

        adj_traversal[City_ID[source]].push_back(City_ID[destination]);
        adj_traversal[City_ID[destination]].push_back(City_ID[source]);
        is_there_edge[City_ID[destination]][City_ID[source]] = 1;
        is_there_edge[City_ID[source]][City_ID[destination]] = 1;

        string transportation;

        int cost;
        while (iss >> transportation >> cost)
        {

            adj[City_ID[source]].push_back({ City_ID[destination], {transportation, cost} });
            adj[City_ID[destination]].push_back({ City_ID[source], {transportation, cost} });
        }
        break;
    }

    file.close();
}

void Menu(bool admin)
{
    bool loggedIn = true;
    int choice, c = 1;
    while (loggedIn)
    {
        cout << "------------------------------------------------------------------------------------------------\n"
            << endl;
        cout << "\n\nPlease choose from the following menu:" << endl;
        cout << "\n"
            << c++ << ". Traverse the transportation graph using BFS or DFS" << endl;
        cout << "\n"
            << c++ << ". Check if the transportaion map is connected or not." << endl;
        cout << "\n"
            << c++ << ". Check if the transportaion map is complete or not." << endl;
        cout << "\n"
            << c++ << ". Find all the possible routes and transportations from  one city to another with the cost of every option." << endl;
        if (admin)
            cout << "\n"
            << c++ << ". Update, Delete, or Add a transportation in the graph" << endl;
        cout << "\n"
            << c++ << ". Logout." << endl;
        cout << "\nChoice:";
        cin >> choice;

        if (choice == 1)
        {
            User_Traversing();
            vis.assign(vis.size(), 0);
        }
        else if (choice == 2)
        {
            if (is_connected(1))
            {
                cout << "------------------------------------------------------------------------------------------------\n"
                    << endl;
                cout << "The Transportation Graph is connected\n"
                    << endl;
                cout << "------------------------------------------------------------------------------------------------\n"
                    << endl;
            }
            else
            {
                cout << "------------------------------------------------------------------------------------------------\n"
                    << endl;
                cout << "The Transportation Graph is not connected\n"
                    << endl;
                cout << "------------------------------------------------------------------------------------------------\n"
                    << endl;
            }
            vis.assign(vis.size(), 0);
        }
        else if (choice == 3)
        {
            if (is_complete())
            {
                cout << "------------------------------------------------------------------------------------------------\n"
                    << endl;
                cout << "The Transportation Graph is complete\n"
                    << endl;
                cout << "------------------------------------------------------------------------------------------------\n"
                    << endl;
            }
            else
            {
                cout << "------------------------------------------------------------------------------------------------\n"
                    << endl;
                cout << "The Transportation Graph is not complete\n"
                    << endl;
                cout << "------------------------------------------------------------------------------------------------\n"
                    << endl;
            }
            vis.assign(vis.size(), 0);
        }
        else if (choice == 4)
        {
            Find_Paths_Between_Cities();
            vis.assign(vis.size(), 0);
        }
        else if (choice == 5 && !admin)
        {
            loggedIn = false;
        }
        else if (choice == 5 && admin)
        {
            string transportation, newTransportation;
            int cost, newCost;

            cout << "------------------------------------------------------------------------------------------------\n"
                << endl;
            cout << "1. View all transportations between two cities" << endl;
            cout << "2. Update" << endl;
            cout << "3. Delete" << endl;
            cout << "4. Add" << endl;
            cout << "5. Cancel" << endl;
            cout << "Choice:";
            cin >> choice;
            switch (choice)
            {
            case 1:

                cout << "Enter the source:";
                cin >> source;
                cout << "Enter the destination:";
                cin >> destination;

                transform(source.begin(), source.end(), source.begin(), ::tolower);
                source[0] = toupper(source[0]);
                transform(destination.begin(), destination.end(), destination.begin(), ::tolower);
                destination[0] = toupper(destination[0]);

                if (City_ID[source] && City_ID[destination])
                {
                    cout << "\n------------------------------------------------------------------------------------------------\n"
                        << endl;
                    Print_all_transportations(City_ID[source], City_ID[destination]);
                    cout << "\n------------------------------------------------------------------------------------------------\n"
                        << endl;
                }
                else
                {
                    cout << "\n     please enter a valid city name" << endl;
                }
                break;
            case 2:

                cout << "Enter the source:";
                cin >> source;
                cout << "Enter the destination:";
                cin >> destination;

                transform(source.begin(), source.end(), source.begin(), ::tolower);
                source[0] = toupper(source[0]);
                transform(destination.begin(), destination.end(), destination.begin(), ::tolower);
                destination[0] = toupper(destination[0]);

                if (City_ID[source] && City_ID[destination])
                {

                    cout << "\n------------------------------------------------------------------------------------------------\n"
                        << endl;
                    Print_all_transportations(City_ID[source], City_ID[destination]);
                    cout << "\n------------------------------------------------------------------------------------------------\n"
                        << endl;

                    cout << "Enter the transportation you want to change:";
                    cin >> transportation;
                    cout << "Enter its cost:";
                    cin >> cost;
                    cout << "Enter the new transportation:";
                    cin >> newTransportation;
                    cout << "Enter its cost:";
                    cin >> newCost;

                    transform(transportation.begin(), transportation.end(), transportation.begin(), ::tolower);
                    transportation[0] = toupper(transportation[0]);
                    transform(newTransportation.begin(), newTransportation.end(), newTransportation.begin(), ::tolower);
                    newTransportation[0] = toupper(newTransportation[0]);
                    if (update_transportations(City_ID[source], City_ID[destination], { transportation, cost }, { newTransportation, newCost }))
                    {
                        cout << "\n     Update done successfully\n"
                            << endl;
                        write_data();
                    }
                    else
                    {
                        cout << "\n     please enter a valid transportation name and valid cost\n"
                            << endl;
                    }
                }
                else
                {
                    cout << "\n     please enter a valid city name\n"
                        << endl;
                }
                break;
            case 3:

                cout << "Enter the source:";
                cin >> source;
                cout << "Enter the destination:";
                cin >> destination;

                transform(source.begin(), source.end(), source.begin(), ::tolower);
                source[0] = toupper(source[0]);
                transform(destination.begin(), destination.end(), destination.begin(), ::tolower);
                destination[0] = toupper(destination[0]);

                if (City_ID[source] && City_ID[destination])
                {
                    cout << "\n------------------------------------------------------------------------------------------------\n"
                        << endl;
                    Print_all_transportations(City_ID[source], City_ID[destination]);
                    cout << "\n------------------------------------------------------------------------------------------------\n"
                        << endl;
                    cout << "Enter the transportation you want to delete:";
                    cin >> transportation;
                    cout << "Enter its cost:";
                    cin >> cost;

                    transform(transportation.begin(), transportation.end(), transportation.begin(), ::tolower);
                    transportation[0] = toupper(transportation[0]);

                    if (delete_transportation(City_ID[source], City_ID[destination], { transportation, cost }))
                    {
                        cout << "\n     Deletion done successfully\n"
                            << endl;

                        write_data();
                    }
                    else
                    {
                        cout << "\n     please enter a valid transportation name and valid cost\n"
                            << endl;
                    }
                }
                else
                {
                    cout << "\n     please enter a valid city name\n"
                        << endl;
                }
                break;
            case 4:

                cout << "Enter the source:";
                cin >> source;
                cout << "Enter the destination:";
                cin >> destination;

                transform(source.begin(), source.end(), source.begin(), ::tolower);
                source[0] = toupper(source[0]);
                transform(destination.begin(), destination.end(), destination.begin(), ::tolower);
                destination[0] = toupper(destination[0]);

                if (City_ID[source] && City_ID[destination])
                {
                    cout << "\n------------------------------------------------------------------------------------------------\n"
                        << endl;
                    Print_all_transportations(City_ID[source], City_ID[destination]);
                    cout << "\n------------------------------------------------------------------------------------------------\n"
                        << endl;
                    cout << "Enter the new transportation:";
                    cin >> newTransportation;
                    cout << "Enter its cost:";
                    cin >> newCost;

                    transform(newTransportation.begin(), newTransportation.end(), newTransportation.begin(), ::tolower);
                    newTransportation[0] = toupper(newTransportation[0]);

                    add_transportation(City_ID[source], City_ID[destination], { newTransportation, newCost });
                    write_data();
                }
                else
                {
                    cout << "\n     please enter a valid city name\n"
                        << endl;
                }
                break;
            default:
                break;
            }
        }
        else if (choice == 6 && admin)
        {
            loggedIn = false;
        }
        else
        {
            cout << "Please enter a valid number (1 -> " << --c << ")" << endl;
        }
        c = 1;
    }
}

int main()
{
    reading_input();
    string newLines = "\n\n\n", space = "\t\t\t\t\t";

    int Choice;
    while (true)
    {
        cout << "------------------------------------------------------------------------------------------------\n"
            << endl;
        cout << newLines << space << "Welcome to Guide Me" << endl;

        cout << newLines;

        cout << "To login as a User enter 1, or to login as an Admin enter 2" << endl;
        cout << "Choice:";
        cin >> Choice;

        switch (Choice)
        {
        case 1:
            Menu(false);
            break;
        case 2:
            Menu(true);
            break;

        default:
            cout << "Please enter a valid number ( 1 -> 2)" << endl;
            break;
        }
    }

    return 0;
}
