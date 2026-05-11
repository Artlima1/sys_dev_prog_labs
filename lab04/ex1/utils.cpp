
#include <string>
#include <fstream>

using std::string;

void read_file_to_arr(int** out, int* n_out, const string& file_name) {
    const string file_path = "../ex1/files/" + file_name;
    std::ifstream input_fs(file_path, std::ios::binary);
    if (!input_fs) return;

    int n_elements;
    input_fs.read(reinterpret_cast<char*>(&n_elements), sizeof(int));

    *out = new int[n_elements];
    input_fs.read(reinterpret_cast<char*>(*out), n_elements * sizeof(int));
    *n_out = n_elements;
    input_fs.close();
}

void write_arr_to_file(const int* data, int size, const string& file_name) {
    const string file_path = "../ex1/files/" + file_name;
    std::ofstream output_fs(file_path, std::ios::out | std::ios::binary);
    if (!output_fs.is_open()) return;

    output_fs.write(reinterpret_cast<const char*>(&size), sizeof(int));
    output_fs.write(reinterpret_cast<const char*>(data), size * sizeof(int));
    output_fs.close();
}
