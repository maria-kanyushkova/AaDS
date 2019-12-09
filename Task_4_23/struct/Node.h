// город
struct Node {
    int id;
    string city;
    vector<Edge *> from;
    vector<Edge *> to;

    Node(int id, string &const city) : id(id), city(city) {}
};