#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query {
    bool active = false;
    string type, name;
    int number;
};

class OptionalQuery {
public:
    OptionalQuery(std::string s) : active(true), s(std::move(s)) {}
    OptionalQuery() : active(false), s() {}
    operator bool() {
        return active;
    }
    void reset() {
        active = false;
    }
    std::string get() const {
        return s; 
    }
private:
    bool active;
    string s;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<OptionalQuery> contacts(10000000);
    for (size_t i = 0; i < queries.size(); ++i) {
        if (queries[i].type == "add") {
            contacts[queries[i].number] = queries[i].name;
        } else if (queries[i].type == "del") {
            if(contacts[queries[i].number]) {
                contacts[queries[i].number].reset();
            }
        } else {
            string response = "not found";
            if(contacts[queries[i].number]) {
                response = contacts[queries[i].number].get();
            }
            result.push_back(response);
        }
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
