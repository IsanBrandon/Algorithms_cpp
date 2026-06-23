#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

const int T = 2099;

string readFile(const string& path) {
    ifstream file(path, ios::binary);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./dupdetect <directory>\n";
        return 1;
    }

    vector<vector<pair<size_t, string>>> table(T);
    string root = argv[1];

    for (const auto& entry : fs::recursive_directory_iterator(root)) {
        if (!entry.is_regular_file()) continue;

        string path = entry.path().string();
        string content = readFile(path);

        size_t hashcode = hash<string>{}(content);
        int address = hashcode % T;

        bool duplicate = false;

        for (const auto& item : table[address]) {
            if (item.first == hashcode) {
                cout << "#Removing " << path
                     << " (duplicate of " << item.second << ").\n";
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            table[address].push_back({hashcode, path});
        }
    }

    return 0;
}