#include <vector>
#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include "alphanum.h"

using namespace Spikes;

//--------------------------------------------------------------
//
//						Constructors
//
//--------------------------------------------------------------

FileReader::FileReader(std::string loc) {
    location = loc;
}

FileReader::~FileReader() {

}

//--------------------------------------------------------------
//
//						Private Methods
//
//--------------------------------------------------------------

/// Returns a matrix after loading from the file.
Eigen::MatrixXd FileReader::load_csv(const std::string &path) {
    this->rows = 0;
    this->columns = 0;

    std::ifstream in_data;
    in_data.open(path);
    std::string line;
    std::vector<double> values;

    while (getline(in_data, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        while (std::getline(lineStream, cell, ',')) {
            values.push_back(std::stod(cell));
        }
        ++rows;

        if (this->rows == 1) {
            this->columns = (int) values.size();
        }
    }

    return Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(values.data(),
                                                                                                    this->rows,
                                                                                                    this->columns);
}

/// Return an Eigen 2D Vector with number of rows and columns.
Eigen::Vector2d FileReader::shape() {

    try {
        has_zero(this->rows, this->columns);
    } catch (const std::invalid_argument &e) {
        std::cout << e.what();
    }

    Eigen::Vector2d data(this->rows, this->columns);
    return data;
}

/// Returns a vector of all sorted file names from the folder.
std::vector<std::string> FileReader::list_dir() {
    std::vector<std::string> file_names;

    char *chr = const_cast<char *>(location.c_str());

    struct dirent *entry;
    DIR *dir = opendir(chr);
    while ((entry = readdir(dir)) != NULL) {
        file_names.push_back(
                (std::basic_string<char, std::char_traits<char>, std::allocator<char>> &&) (entry->d_name));
    }

    closedir(dir);

    std::sort(file_names.begin(), file_names.end(), doj::alphanum_less<std::string>());

    return file_names;
}

/// Checks if the string contains numbers
// TODO: Change this to check for file with "sam%d"
bool FileReader::contains_number(const std::string &c) {
    return (c.find_first_of("0123456789") != std::string::npos);
}


//--------------------------------------------------------------
//
//						Exceptions/Exits
//
//--------------------------------------------------------------


int FileReader::has_zero(int rows, int columns) {

    if (rows == 0 || columns == 0) {
        std::cout << "Matrix should be of two dimension or a CSV file is not loaded." << '\n';
        exit(1);
    }
}


//--------------------------------------------------------------
//
//						Public Methods
//
//--------------------------------------------------------------

///// Returns a vector of MatrixXd objects sample wise. If the sample size is know then the process is much quicker else the memory consumption is much higher.
std::vector<Eigen::MatrixXd> FileReader::get_data() {
    std::vector<Eigen::MatrixXd> data;
    for (auto i : list_dir()) {
        if (contains_number(i)) {
            data.push_back(load_csv(location + "/" + i));
        }
    }

    return data;
}
