#include "Compressor.h"
#include "LogManager.h"
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>
#include <direct.h>
#include <Shlwapi.h>
#include <iterator>

Compressor Compressor::m_instance;


void Compressor::compress( std::string path, std::string targetFile ) {

	std::vector<std::string> files;
	fillRecursively(files, path);

	/*
		file format:
			int		item count

			for every item n < item count :
			int			filesize
			MAX_PATH*sizeof(char)		Path name
			<filesize> bytes			data
	*/

	int fCount = files.size();
	std::ofstream outFile(targetFile, std::ios::binary | std::ios::trunc);

	outFile.write((char*)(&fCount), 4); //Item count

	for(int i = 0; i < files.size(); ++i) {
		std::ifstream inFile(files[i], std::ios::binary);
		int fLen = 0;
		inFile.seekg(0, inFile.end);
		fLen = inFile.tellg();
		inFile.seekg(0, inFile.beg);
		char* buf = new char[fLen];
		inFile.read(buf, fLen);
		inFile.close();

		outFile.write((char*)(&fLen), 4);
		outFile.write(files[i].c_str(), MAX_PATH * sizeof(char));
		outFile.write(buf, fLen);
		delete buf;
	}
	
	outFile.flush();
	outFile.close();
}

void Compressor::extract(std::string file, std::string targetPath) {

	std::ifstream inFile(file, std::ios::binary);

	if(inFile.is_open()) {

		Log::Write("Extracting from " + file + " ");
		checkPath(targetPath);

		int fCount;
		int cExists = 0;
		int cExtracted = 0;
		int cRepaired = 0;
		inFile.read((char*)&fCount, 4);

		for(int i = 0; i < fCount; ++i) {

			int fSize;
			inFile.read((char*)&fSize, 4);

			char* fName = new char[MAX_PATH];
			inFile.read(fName, sizeof(char)*MAX_PATH);

			std::string strName(fName);

			std::ifstream file(targetPath + "\\" + strName, std::ios::binary);
			if(file.is_open()) { //File already exists
				file.seekg(0, file.end);
				int size = file.tellg();
				file.close();
				
				if(size == fSize) { //Sizes match
					inFile.seekg(fSize, inFile.cur);
					Log::Write(".", Log::COLOR_LIGHT_AQUA);
					cExists++;
					continue;
				} else {
					cRepaired++;
					Log::Write(".", Log::COLOR_LIGHT_YELLOW);
				}
			} else {
				cExtracted++;
				Log::Write(".", Log::COLOR_LIGHT_PURPLE);
			}

			char* data = new char[fSize];
			inFile.read(data, fSize);

			std::string rest = strName;
			std::string fullPath = targetPath + "\\";
			size_t pos;
			while( (pos = rest.find("\\")) != std::string::npos ) {
				std::string path = rest.substr(0, pos);
				fullPath += path;
				checkPath(fullPath); //Guarantees that all paths exists before extracting file data
				fullPath += "\\";
				rest = rest.substr(pos+1);
			}

			std::ofstream outFile(targetPath + "\\" + strName, std::ios::binary);
			outFile.write(data, fSize);
			outFile.flush();
			outFile.close();
		}

		std::stringstream ss1,ss2,ss3,ss4;
		Log::Write(" done (");
		ss1 << cExists << " untouched ";
		Log::Write(ss1.str(), Log::COLOR_LIGHT_AQUA);
		ss2 << cRepaired << " repaired ";
		Log::Write(ss2.str(), Log::COLOR_LIGHT_YELLOW);
		ss3 << cExtracted << " extracted ";
		Log::Write(ss3.str(), Log::COLOR_LIGHT_PURPLE);
		ss4 << fCount << " total";
		Log::Write(ss4.str(), Log::COLOR_LIGHT_GREEN);
		Log::Writeln(")");
	}
}

void Compressor::fillRecursively( std::vector<std::string>& arr, std::string path ) {

	LPWIN32_FIND_DATAA fd = new _WIN32_FIND_DATAA;
	HANDLE hfind = FindFirstFileA(path.c_str(), fd);

	if(hfind == INVALID_HANDLE_VALUE) return;
	while(FindNextFileA(hfind, fd) != FALSE) {
		std::string fPath = path.substr(0, path.size()-1) + fd->cFileName;
		if(fd->cFileName[0] == '.' && fd->cFileName[1] == '.') continue;
		if(fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			fillRecursively(arr, fPath + "\\*");
		} else {
			arr.push_back( std::string(fPath) );
		}
	}

	FindClose(hfind);
}

void Compressor::checkPath( std::string path ) {

	if(!PathIsDirectoryA(path.c_str())) {

		_mkdir(path.c_str());
	}
}
