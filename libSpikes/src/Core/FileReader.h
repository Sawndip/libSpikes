#pragma once
#include <vector>
#include <Eigen>

#ifndef LIBSPIKES_FILEREADER_H
#define LIBSPIKES_FILEREADER_H

namespace Spikes {
	class FileReader {
		std::string location;
		Eigen::MatrixXd load_csv(const std::string & path, const int rows_csv, const int columns_csv) const;
		static Eigen::MatrixXd FileReader::load_csv_arma(const std::string & path);
		std::vector<std::string> list_dir(void) const;
		static bool contains_number(const std::string &c);
	public:
		explicit FileReader(std::string);
		std::vector<Eigen::MatrixXd> get_data(int rows=0, int columns=0) const;
		~FileReader();
	};
}

#endif
