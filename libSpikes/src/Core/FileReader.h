#pragma once

#include <vector>
#include <map>
#include <Eigen/Core>
#include <boost/any.hpp>
#include <boost/spirit/home/support/detail/hold_any.hpp>

#ifndef LIBSPIKES_FILEREADER_H
#define LIBSPIKES_FILEREADER_H

namespace Spikes {

    inline char separator() {
        #if defined _WIN32 || defined __CYGWIN__
                return '\\';
        #else
                return '/';
        #endif
            }

    struct data {

        data(std::vector<Eigen::MatrixXd> &&rhs, int idx) {
            samples = std::move(rhs);
            index = idx;
        }

        data(std::vector<std::string> &&rhs, int idx) {
            sample_names = std::move(rhs);
            index = idx;
        }

        std::vector<Eigen::MatrixXd> samples;
        std::vector<std::string> sample_names;
        int index = -1;
    };

    class FileReader {
        std::string location;
        int rows = 0;
        int columns = 0;

        int has_zero(int rows, int columns);

        Eigen::MatrixXd load_csv(const std::string &path);

        std::vector<std::string> list_dir();

        bool contains_number(const std::string &c);

        std::pair<std::vector<std::string>, std::vector<Eigen::MatrixXd>> get_data_with_sample_names();

        std::map<std::string, Spikes::data> get_data_with_others();

    public:

        explicit FileReader(std::string);

        Eigen::Vector2d shape();


        ~FileReader();

    };
}

#endif
