#include <bits/stdc++.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

static constexpr char COMMAND_END = 0;
static constexpr char COMMAND_SETLIGHT = 1;
static constexpr char COMMAND_TAKEPATH = 2;

static vector<int> prep_paths(vector<vector<int>>& adjlist, const int* levels, int room, mt19937_64& rng) {
    shuffle(adjlist[room].begin(), adjlist[room].end(), rng);
    vector<int> ret;
    ret.reserve(adjlist[room].size());
    for (int x : adjlist[room]) {
        ret.push_back(levels[x]);
    }
    return ret;
}

struct pipes {
    int child_output, child_input;
};

template <typename T>
static void write_integral(char*& buf, T val) {
    buf = copy_n(reinterpret_cast<char*>(&val), sizeof(val), buf);
}

static void write_vector(char*& buf, const vector<int>& vec) {
    write_integral(buf, static_cast<int>(vec.size()));
    for (int x : vec){
        write_integral(buf, x);
    }
}

static size_t vector_bytes(const vector<int>& vec) {
    return sizeof(int) + vec.size() * sizeof(int);
}

int wrong() {
	cout << "0.0" << endl;
    cerr << "translate:wrong" << endl;
    return 0;
}

int correct() {
	cout << "1.0" << endl;
    cerr << "translate:success" << endl;
    return 0;
}

int rte_setlight() {
	cout << "0.0" << endl;
    cerr << "Invalid argument passed to set_light()" << endl;
    return 0;
}

int rte_takepath() {
	cout << "0.0" << endl;
    cerr << "Invalid argument passed to take_path()" << endl;
    return 0;
}

int rte() {
	return wrong();
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    signal(SIGPIPE, SIG_IGN);
    int num_children = (argc - 1)/2;
    uint64_t seed;
    cin >> seed;
    mt19937_64 rng(seed);
    int N, K, L;
    cin >> N >> K >> L;
    vector<vector<int>> adjlist(N, vector<int>());
    vector<int> levels(N, 0);
    vector<bool> explored(N, false);
    vector<int> parent(N, 0);
    parent[0] = -1;
    for (int i = 1; i < N; ++i) {
        cin >> parent[i];
        adjlist[parent[i]].push_back(i);
    }
    for (int i = 0; i < N; ++i) {
        levels[i] = 0;
    }
    vector<pipes> children;
    for (int i = 0; i < num_children; ++i) {
        pipes& p = children.emplace_back();
        p.child_input = open(argv[i*2 + 2], O_WRONLY);
        p.child_output = open(argv[i*2 + 1], O_RDONLY);
    }
    for (int i = 0; i < K; ++i) {
        int child = uniform_int_distribution<int>(0, num_children - 1)(rng);
        pipes& p = children[child];
        vector<int> paths = prep_paths(adjlist, levels.data(), 0, rng);
        explored[0] = true;
        int archaeologist_room = 0;
        // send starting data
        const size_t buf_sz = sizeof(N) + sizeof(K) + sizeof(L) + sizeof(int) * N + sizeof(int) + vector_bytes(paths);
        char* buffer = new char[buf_sz];
        char* buffer_end = buffer;
        write_integral(buffer_end, N);
        write_integral(buffer_end, K);
        write_integral(buffer_end, L);
        for (int j=0;j<N;++j){
            write_integral(buffer_end, parent[j]);
        }
        write_integral(buffer_end, levels[0]);
        write_vector(buffer_end, paths);
        assert(buffer + buf_sz == buffer_end);
        if (write(p.child_input, buffer, buf_sz) != static_cast<ssize_t>(buf_sz)) return rte();
        while (true) {
            // child output syntax:
            // done: 1 byte '0'
            // set_light: 1 byte '1', 4-byte int
            // take_path: 1 byte '2', 4-byte int
            // returns: 4-byte curr room, 4-byte number of paths, n*4 byte list of paths
            char type;
            if (read(p.child_output, &type, 1) <= 0) return rte();
            if (type == COMMAND_END) {
                break;
            }
            else if (type == COMMAND_SETLIGHT) {
                int level;
                if (read(p.child_output, &level, sizeof(int)) <= 0) return rte();
                if (!(0 <= level && level <= L)) return rte_setlight();
                levels[archaeologist_room] = level;
            }
            else if (type == COMMAND_TAKEPATH){
                int corridor;
                if (read(p.child_output, &corridor, sizeof(int)) <= 0) return rte();
                if (!(0 <= corridor && corridor < static_cast<int>(adjlist[archaeologist_room].size()))) return rte_takepath();
                archaeologist_room = adjlist[archaeologist_room][corridor];
                vector<int> paths = prep_paths(adjlist, levels.data(), archaeologist_room, rng);
                explored[archaeologist_room] = true;
                const size_t buf_sz = sizeof(archaeologist_room) + vector_bytes(paths);
                char* buffer = new char[buf_sz];
                char* buffer_end = buffer;
                write_integral(buffer_end, archaeologist_room);
                write_vector(buffer_end, paths);
                assert(buffer + buf_sz == buffer_end);
                if (write(p.child_input, buffer, buf_sz) != static_cast<ssize_t>(buf_sz)) return rte();
            }
        }
    }
    for (int i = 0; i < num_children; ++i) {
        close(children[i].child_input);
        close(children[i].child_output);
    }
    if (!all_of(explored.begin(), explored.end(), [](bool e) { return e; })) {
		return wrong();
    }
    return correct();
}
