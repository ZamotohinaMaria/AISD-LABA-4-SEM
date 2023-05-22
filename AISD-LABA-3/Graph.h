#pragma once
#include <vector>
#include <forward_list>
#include <stdio.h>

using namespace std;
struct Edge
{
    int id_to;
    double weight;
    Edge(int id_to, double weight) : id_to(id_to), weight(weight) {}
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
    double d;
    int id_prev;
    forward_list<Edge> edges;
    Vertex(int id_v): id_v(id_v)
    {
        color = white;
        d = 0;
        id_prev = INT_MAX;
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
    //vector<Vertex> vertices() const;

    //��������-����������-�������� �����
    void add_edge(int id_from, int id_to, double w);
    bool remove_edge(int id_from, int id_to);
    //bool remove_edge(const Edge& e); //c ������ ����������
    bool has_edge(int id_from, int id_to) const;
    //bool has_edge(const Edge& e); //c ������ ���������� � Edge

    //��������� ���� �����, ��������� �� �������
    vector<Vertex> neighbour_of_vertex(int id_v);

    //size_t order() const; //�������
    int degree(int id_v) const; //�������

    //����� - � ������
    void walk();
    void search_in_width(Vertex& v);

    //����� ����������� ���� - ��������
    vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const;
    void Deicstra(Vertex first);
    void Relax(Vertex u, Vertex v);
};

