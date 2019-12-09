struct Node;

// рейс
struct Edge {
    Node *from;
    Node *to;
    string flight;

    Edge(Node *from, Node *to, string flight) : from(from), to(to), flight(move(flight)) {}
};