#include <stdio.h>
#include "dllist.h"
#include "jrb.h"
#include "jval.h"
#include <string.h>
#include <curses.h>
#include "graph.h"
void setParent(int u, int v, int *parent)
{
    parent[u] = v;
}
double shortestPath(Graph graph, int s, int t, int path[], int *length)
{
    JRB PQ;
    PQ = make_jrb();
    int v, n, j, o;
    int visited[100], output[100], parent[100];
    double weight[100], d;
    for (int i = 0; i < 100; i++)
    {
        weight[i] = (double)INFINITIVE_VALUE;
    }
    memset(visited, 0, sizeof(visited));
    jrb_insert_int(PQ, 0, new_jval_i(s));
    weight[s] = 0;
    while (!jrb_empty(PQ))
    {
        v = jval_i(jrb_first(PQ)->val);
        jrb_delete_node(jrb_first(PQ));
        if (!visited[v])
        {
            // printw("duyet %d...\n", v);
            n = outdegree(graph, v, output);
            for (int i = 0; i < n; i++)
            {
                o = output[i];
                d = weight[v] + getEdgeValue(graph, v, o);
                if (d < weight[o])
                {
                    weight[o] = d;
                    setParent(o, v, parent);
                    // printw("weight[%d] = %g\n", o, weight[o]);
                }
                if (!visited[o])
                {
                    jrb_insert_int(PQ, weight[o], new_jval_i(o));
                }
            }
        }
        visited[v] = TRUE;
    }
    j = 0;
    for (int i = t; parent[i] != s; i = parent[i])
    {
        path[j++] = parent[i];
    }
    *length = j;
    free(PQ);
    // printw("%g", weight[t]);
    return weight[t];
}
Graph createGraph()
{
    Graph graph;
    graph = (Graph)malloc(sizeof(struct _graphics));
    graph->edges = make_jrb();
    graph->vertices = make_jrb();
    graph->id = make_jrb();
    return graph;
}
int addVertex(Graph graph, int id, char *name /*Note: strdup*/)
{
    if (!jrb_find_str(graph->id, name))
    {
        JRB node = make_jrb();
        jrb_insert_str(graph->id, name, new_jval_i(id));
        jrb_insert_int(graph->vertices, id, new_jval_s(name));
        jrb_insert_int(graph->edges, id, new_jval_v(node));
        return 1;
    }
    return 0;
}
char *getVertex(Graph graph, int id)
{
    if (id == -1)
        return NULL;
    return (char *)jval_v(jrb_find_int(graph->vertices, id)->val);
}
int getId(Graph g, char *name)
{
    JRB node = jrb_find_str(g->id, name);
    if (node)
    {
        return jval_i(node->val);
    }
    else
        return INFINITIVE_VALUE;
}
void addEdge(Graph graph, int v1, int v2, double weight)
{
    JRB node = (JRB)jval_v(jrb_find_int(graph->edges, v1)->val);
    if (!jrb_find_int(node, v2))
        jrb_insert_int(node, v2, new_jval_d(weight));
}
int hasVertex(Graph g, char *name)
{
    int find = getId(g, name);
    if (find != INFINITIVE_VALUE)
    {
        return 1;
    }
    return 0;
}
int hasEdge(Graph graph, int v1, int v2)
{
    JRB node = jrb_find_int(graph->edges, v1);
    if (!node)
    {
        return 0;
    }
    else
    {
        JRB tree = jrb_find_int((JRB)jval_v(node->val), v2);
        if (!tree)
        {
            return 0;
        }
        return 1;
    }
}
double getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node = (JRB)jval_v(jrb_find_int(graph->edges, v1)->val);
    JRB find = jrb_find_int(node, v2);
    if (find)
    {
        return jval_d(find->val);
    }
    return INFINITIVE_VALUE;
}
int indegree(Graph graph, int v, int *output)
{
    JRB root;
    JRB find;
    int total = 0;
    jrb_traverse(root, graph->edges)
    {
        find = jrb_find_int((JRB)jval_v(root->val), v);
        if (find)
            *(output + total++) = jval_i(root->key);
    }
    return total;
}
int outdegree(Graph graph, int v, int *output)
{
    JRB root, find;
    int total = 0;
    find = jrb_find_int(graph->edges, v);
    if (find)
    {
        JRB tree = (JRB)jval_v(find->val);
        jrb_traverse(root, tree)
        {
            *(output + total++) = jval_i(root->key);
        }
    }
    return total;
}
int DAG(Graph graph)
{
    int visited[1000];
    int n, output[100], i, u, v, start;
    Dllist node, stack;
    JRB vertex;
    jrb_traverse(vertex, graph->vertices)
    {
        memset(visited, 0, sizeof(visited));

        start = jval_i(vertex->key);
        stack = new_dllist();
        dll_append(stack, new_jval_i(start));

        while (!dll_empty(stack))
        {
            node = dll_last(stack);
            u = jval_i(node->val);
            dll_delete_node(node);
            if (!visited[u])
            {
                visited[u] = 1;
                n = outdegree(graph, u, output);
                for (i = 0; i < n; i++)
                {
                    v = output[i];
                    if (v == start)
                        return 0;
                    if (!visited[v])
                        dll_append(stack, new_jval_i(v));
                }
            }
        }
    }
    return 1;
}
void dropGraph(Graph graph)
{
    JRB root, root1, node1;
    JRB node = graph->edges;
    jrb_traverse(root, node)
    {
        jrb_free_tree((JRB)jval_v(root->val));
    }
    jrb_free_tree(node);
    node = graph->vertices;
    jrb_traverse(root, node)
    {
        free(jval_s(root->val));
    }
    jrb_free_tree(graph->vertices);
    jrb_free_tree(graph->id);
}