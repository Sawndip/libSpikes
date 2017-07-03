#pragma once

#include <vector>
#include <Eigen/Core>

#ifndef LIBSPIKES_FILEREADER_H
#define LIBSPIKES_FILEREADER_H

namespace Spikes {
    class FileReader {
        std::string location;
        int rows = 0;
        int columns = 0;

        int has_zero(int rows, int columns);

        Eigen::MatrixXd load_csv(const std::string &path);

        std::vector<std::string> list_dir(void);

        bool contains_number(const std::string &c);

    public:
        explicit FileReader(std::string);

        std::vector<Eigen::MatrixXd> get_data(void);

        Eigen::Vector2d shape(void);

        ~FileReader();

    };
}

#endif
