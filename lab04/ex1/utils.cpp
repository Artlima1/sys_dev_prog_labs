
#include <set>
#include <string>
#include <fstream>

using std::string;

void read_file_to_set(std::multiset<int> * out, const string &file_name) {
    const string file_path = "../ex1/files/" + file_name;
    std::ifstream input_fs(file_path, std::ios::binary);

    if (!input_fs) return;

    int n_elements, element;
    input_fs.read(reinterpret_cast<char*>(&n_elements), sizeof(int));

    for (int i = 0; i < n_elements; i++) {
        input_fs.read(reinterpret_cast<char*>(&element), sizeof(int));
        out->insert(element);
    }
    input_fs.close();
}


void write_set_to_file(std::multiset<int> * data, const string &file_name) {
    const string file_path = "../ex1/files/" + file_name;
    std::ofstream output_fs(file_path,  std::ios::out|std::ios::binary);
    if (!output_fs.is_open()) return;

    int n_elements = static_cast<int>(data->size());
    output_fs.write(reinterpret_cast<const char*>(&n_elements), sizeof(int));

    for (auto e: *data) {
        output_fs.write(reinterpret_cast<const char*>(&e), sizeof(int));
    }

    output_fs.close();

}