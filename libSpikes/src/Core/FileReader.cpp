#include <boost/filesystem.hpp>
#include <vector>
#include "FileReader.h"
#include <iostream>
#include <sstream>
#include <Eigen/src/Core/util/ForwardDeclarations.h>
//#include <armadillo>
#include <vector>

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
Eigen::MatrixXd FileReader::load_csv(const std::string &path, const int rows_csv, const int columns_csv) const {
    std::ifstream indata;
    indata.open(path);
    std::string line;
    std::vector<double> values;
    int rows = 0;
    while (getline(indata, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        while (std::getline(lineStream, cell, ',')) {
            values.push_back(std::stod(cell));
        }
        ++rows;
    }

    return Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(values.data(),
                                                                                                    rows_csv,
                                                                                                    columns_csv);;
}

///Another way to load in CSV files and send it as Eigen vector.
Eigen::MatrixXd FileReader::load_csv_arma(const std::string &path) {
    arma::mat X;
    X.load(path, arma::csv_ascii);
    std::cout << X.n_cols << " " << X.n_rows << std::endl;
    return Eigen::Map<const Eigen::MatrixXd>(X.memptr(), X.n_rows, X.n_cols);
}

/// Returns a vector of all the file names loaded from the folder.
std::vector<std::string> FileReader::list_dir(void) const {
    std::vector<std::string> file_names;

    boost::filesystem::path p(location);
    try {
        for (auto i = boost::filesystem::directory_iterator(p); i != boost::filesystem::directory_iterator(); ++i) {
            if (!is_directory(i->path())) //we eliminate directories
            {
                file_names.insert(file_names.end(), i->path().filename().string());
            } else
                continue;
        }
    }
    catch (const boost::filesystem::filesystem_error &e) {
        if (e.code() == boost::system::errc::permission_denied)
            std::cout << "Search permission is denied for one of the directories " << "in the path prefix of " << p
                      << "\n";
        else
            std::cout << "is_directory(" << p << ") failed with "
                      << e.code().message() << '\n';
    }

    sort(file_names.begin(), file_names.end(), doj::alphanum_less<std::string>());

    return file_names;
}

/// Checks if the string contains numbers
bool FileReader::contains_number(const std::string &c) {
    return (c.find_first_of("0123456789") != std::string::npos);
}

//--------------------------------------------------------------
//
//						Public Methods
//
//--------------------------------------------------------------

/// Returns a vector of MatrixXd objects sample wise. If the sample size is know then the process is much quicker else the meory consumption is much higher.
std::vector<Eigen::MatrixXd> FileReader::get_data(int rows, int columns) const {
    std::vector<Eigen::MatrixXd> data;
    std::cout << rows;
    if (rows == 0 || columns == 0) {
        for (auto i : list_dir()) {
            if (contains_number(i)) {
                data.push_back(load_csv_arma(location + "/" + i));
            } else { continue; }
        }
    } else {
        for (auto i : list_dir()) {
            if (contains_number(i)) {
                data.push_back(load_csv(location + "/" + i, rows, columns));
            } else { continue; }
        }
    }

    return data;
}
