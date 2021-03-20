#include "archaeologist.h"
#include <bits/stdc++.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

static constexpr char COMMAND_END = 0;
static constexpr char COMMAND_SETLIGHT = 1;
static constexpr char COMMAND_TAKEPATH = 2;

static ssize_t read_exact(int fd, char* ptr, size_t count) {
    size_t ret = count;
    while (count > 0) {
        const ssize_t r = read(fd, ptr, count);
        if (r <= 0) return r;
        ptr += r;
        count -= r;
    }
    return ret;
}

template <typename T>
static ssize_t read_exact_integral(int fd, T& arg) {
    return read_exact(fd, reinterpret_cast<char*>(&arg), sizeof(T));
}

static ssize_t read_exact_vector(int fd, vector<int>& vec) {
    int sz;
    int rsp = read_exact_integral(fd, sz);
    if (rsp <= 0) return rsp;
    vec.assign(sz, 0);
    if (sz == 0) return rsp;
    return rsp + read_exact(fd, reinterpret_cast<char*>(vec.data()), sizeof(int) * sz);
}

template <typename T>
static void write_integral(char*& buf, T val) {
    buf = copy_n(reinterpret_cast<char*>(&val), sizeof(val), buf);
}

static int input_fd, output_fd;

pair<int, vector<int>> take_path(int corridor) {
    const size_t buf_sz = 1 + sizeof(int);
    char* buffer = new char[buf_sz];
    char* buffer_end = buffer;
    *buffer_end++ = COMMAND_TAKEPATH;
    write_integral(buffer_end, corridor);
    assert(buffer + buf_sz == buffer_end);
    if (write(output_fd, buffer, buf_sz) != buf_sz) exit(0);
    int curr_room;
    vector<int> paths;
    if (read_exact_integral(input_fd, curr_room) <= 0) exit(0);
    if (read_exact_vector(input_fd, paths) <= 0) exit(0);
    return make_pair(curr_room, move(paths));
}

void set_light(int level) {
    const size_t buf_sz = 1 + sizeof(int);
    char* buffer = new char[buf_sz];
    char* buffer_end = buffer;
    *buffer_end++ = COMMAND_SETLIGHT;
    write_integral(buffer_end, level);
    assert(buffer + buf_sz == buffer_end);
    if (write(output_fd, buffer, buf_sz) != buf_sz) exit(0);
}

int main(int argc, char** argv) {
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);
    assert(argc > 2);
    input_fd = open(argv[1], O_RDONLY);
    output_fd = open(argv[2], O_WRONLY);
    int arr_input[3];
    while (read_exact(input_fd, reinterpret_cast<char*>(arr_input), sizeof(arr_input)) > 0) {
        const int N = arr_input[0], K = arr_input[1], L = arr_input[2];
        vector<int> parent(N, 0);
        if (read_exact(input_fd, reinterpret_cast<char*>(parent.data()), sizeof(int) * N) <= 0) exit(0);
        int initial_level;
        if (read_exact_integral(input_fd, initial_level) <= 0) exit(0);
        vector<int> paths;
        if (read_exact_vector(input_fd, paths) <= 0) exit(0);
        archaeologist(N, K, L, move(parent), initial_level, move(paths));
        if (write(output_fd, &COMMAND_END, 1) != 1) exit(0);
    }
    close(output_fd);
    close(input_fd);
}
