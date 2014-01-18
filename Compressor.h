#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>
#include <vector>

class Compressor {

	public:

		static Compressor* instance() { return &m_instance; }

		void extract(std::string file, std::string targetPath);
		void compress(std::string path, std::string targetFile);

	private:

		static Compressor m_instance;

		void fillRecursively(std::vector<std::string>& arr, std::string path);
		void checkPath(std::string path);
};

#endif // !COMPRESSOR_H
