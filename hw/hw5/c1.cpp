#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random> // For Test

struct IMetro {
    virtual void AddConnection(std::string station_name_a, std::string station_name_b) = 0;
    virtual bool IsConnected(std::string station_name_a, std::string station_name_b) = 0;
    virtual bool HasPath(std::string station_name_a, std::string station_name_b) = 0;
    virtual std::vector<std::string> ShortestPath(std::string station_name_a, std::string station_name_b) = 0;
    virtual ~IMetro() {}
};

// [YOUR CODE WILL BE PLACED HERE] 
#include <bits/stdc++.h>

class Metro : public IMetro {
private:
    std::unordered_map<std::string, std::set<std::string>> connections;

public:
    void AddConnection(std::string station_name_a, std::string station_name_b) override {
        connections[station_name_a].insert(station_name_b);
        connections[station_name_b].insert(station_name_a);
    }

    bool IsConnected(std::string station_name_a, std::string station_name_b) override {
        return connections[station_name_a].count(station_name_b) > 0;
    }

    bool HasPath(std::string station_name_a, std::string station_name_b) override {
        if (station_name_a == station_name_b) {
            return true;
        }

        std::unordered_map<std::string, bool> visited_a;
        std::unordered_map<std::string, bool> visited_b;
        std::queue<std::string> q_a;
        std::queue<std::string> q_b;
        q_a.push(station_name_a);
        q_b.push(station_name_b);

        while (!q_a.empty() && !q_b.empty()) {
            std::string current_station_a = q_a.front();
            std::string current_station_b = q_b.front();
            q_a.pop();
            q_b.pop();

            visited_a[current_station_a] = true;
            visited_b[current_station_b] = true;

            if (current_station_a == current_station_b) {
                return true;
            }

            for (const std::string& neighbor_a : connections[current_station_a]) {
                if (visited_b.count(neighbor_a) > 0) {
                    return true;
                }
                if (!visited_a[neighbor_a]) {
                    q_a.push(neighbor_a);
                }
            }

            for (const std::string& neighbor_b : connections[current_station_b]) {
                if (visited_a.count(neighbor_b) > 0) {
                    return true;
                }
                if (!visited_b[neighbor_b]) {
                    q_b.push(neighbor_b);
                }
            }
        }

        return false;
    }

    std::vector<std::string> ShortestPath(std::string station_name_a, std::string station_name_b) override {
        std::unordered_map<std::string, std::string> prev;
        std::unordered_map<std::string, int> dist;
        std::queue<std::string> q;
        q.push(station_name_a);
        dist[station_name_a] = 0;
        prev[station_name_a] = "";

        while (!q.empty()) {
            std::string current_station = q.front();
            q.pop();

            if (current_station == station_name_b) {
                break;
            }
            
            for (const std::string& neighbor : connections[current_station]) {
                if (dist.count(neighbor) == 0) {
                    dist[neighbor] = dist[current_station] + 1;
                    prev[neighbor] = current_station;
                    q.push(neighbor);
                }
            }
        }

        std::vector<std::string> path;
        if (dist.count(station_name_b) == 0) {
            return path;
        }

        std::string current = station_name_b;
        while (current != "") {
            path.push_back(current);
            current = prev[current];
        }

        std::reverse(path.begin(), path.end());
        return path;
    
    }
};

void Dump(const std::vector<std::string>&);

void Test1(); // Sample1
void Test2(); // AddConnection, IsConnected 
void Test3(); // AddConnection, IsConnected 
void Test4(); // AddConnection, HasPath 
void Test5(); // AddConnection, HasPath
void Test6(); // AddConnection, ShortestPath 
void Test7(); // AddConnection, ShortestPath

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6, Test7};
    f[id-1]();
}

void Dump(const std::vector<std::string>& path) {
    bool isFirst = true;
    for (const std::string& s : path) {
        if (!isFirst) {
            std::cout << " -> ";
        } else {
            isFirst = false;
        }
        std::cout << s;
    }
    std::cout << std::endl;
}

namespace Feis {}

void Test1() {
    Metro m;
    m.AddConnection("TaipeiMainStation", "ShandoTemple");
    m.AddConnection("TaipeiMainStation", "Zhongshan");
    m.AddConnection("TaipeiMainStation", "Ximen");
    m.AddConnection("Shuanglian", "Zhongshan");
    m.AddConnection("Beimen", "Zhongshan");
    m.AddConnection("Beimen", "Ximen");
    m.AddConnection("MinquanWRd", "Shuanglian");
    m.AddConnection("MinquanWRd", "Yuanshan");
    m.AddConnection("MinquanWRd", "ZhongshangElementarySchool");
    m.AddConnection("XingtianTample", "ZhongshangElementarySchool");
    m.AddConnection("XingtianTample", "SongjianNanjing");
    m.AddConnection("ZhongxiaoXinsheng", "SongjianNanjing");
    m.AddConnection("ZhongxiaoXinsheng", "Dongmen");
    m.AddConnection("ShandoTemple", "ZhongxiaoXinsheng");
    m.AddConnection("ZhongxiaoXinsheng", "ZhongxiaoFuxing");
    m.AddConnection("ZhongxiaoFuxing", "SunYatSenMemorialHall");
    m.AddConnection("SunYatSenMemorialHall", "TaipeiCityHall");
    m.AddConnection("TaipeiCityHall", "Yongchun");
    m.AddConnection("Yongchun", "Houshanpi");
    m.AddConnection("Houshanpi", "Kunyang");
    m.AddConnection("Kunyang", "Nanggong");

    std::cout << "01) " << std::boolalpha << m.IsConnected("TaipeiMainStation", "Ximen") << std::endl;

    std::cout << "02) " << std::boolalpha << m.IsConnected("TaipeiMainStation", "Beimen") << std::endl;

    std::cout << "03) " << std::boolalpha << m.IsConnected("TaipeiMainStation", "TaipeiMainStation") << std::endl;

    std::cout << "04) " << std::boolalpha << m.HasPath("TaipeiMainStation", "Beimen") << std::endl;

    std::cout << "05) " << std::boolalpha << m.HasPath("TaipeiMainStation", "FuJenUniversity") << std::endl;

    std::cout << "06) " << std::boolalpha << m.HasPath("TaipeiMainStation", "TaipeiMainStation") << std::endl;

    std::cout << "07) ";
    Dump(m.ShortestPath("TaipeiMainStation", "TaipeiCityHall"));

    std::cout << "08) ";
    Dump(m.ShortestPath("TaipeiMainStation", "Nanggong"));

    std::cout << "09) ";
    Dump(m.ShortestPath("TaipeiMainStation", "SongjianNanjing"));

    m.AddConnection("Zhongshan", "SongjianNanjing");

    std::cout << "10) ";
    Dump(m.ShortestPath("TaipeiMainStation", "SongjianNanjing"));

    std::cout << "11) ";
    Dump(m.ShortestPath("TaipeiMainStation", "Beimen"));
}

void Test2() {}
void Test3() {}
void Test4() {}
void Test5() {}
void Test6() {}
void Test7() {}