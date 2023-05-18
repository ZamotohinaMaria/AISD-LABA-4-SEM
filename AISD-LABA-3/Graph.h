#pragma once
#include <vector>
#include <stdio.h>

using namespace std;
struct Edge
{
    int id_to;
    double weight;
    Edge* next;
    Edge(int id, double weight, Edge* next) : id_to(id), weight(weight), next(next) {}
};

enum Color
{
    white = 0,
    gray = 1,
    black = 2
};

struct Vertex
{
    int id_v;
    Color color;
    vector<Edge> edges;
    Vertex(int id_v): id_v(id_v)
    {
        color = white;
    }
};

//������ Distance ������������ double
class Graph {
private:
    vector<Vertex> vertexes;
public:
    ~Graph();
    //��������-����������-�������� ������
    bool contain_vertex(int id_find_v) const;
    int find_vertex(int id_find_v) const;
    void add_vertex(int id_v);
    bool remove_vertex(int id_remove_v);
    vector<Vertex> vertices() const;

    //��������-����������-�������� �����
    void add_edge(const Vertex& from, const Vertex& to,
        const double& d);
    bool remove_edge(int id_from, int id_to);
    bool remove_edge(const Edge& e); //c ������ ����������
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge(const Edge& e); //c ������ ���������� � Edge

    //��������� ���� �����, ��������� �� �������
    vector<Edge> edges(const Vertex& vertex);

    size_t order() const; //�������
    size_t degree() const; //�������


    //����� ����������� ����
    vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const;
    //�����
    vector<Vertex>  walk(const Vertex& start_vertex)const;
};

