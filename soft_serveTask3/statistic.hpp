#pragma once

#include <string>   
#include <vector>    
#include <atomic>   
#include <mutex>
#include <filesystem>    
#include <fstream>       
#include <thread>       
#include <iostream>  

struct FileData
{
	std::atomic<int> total_files = 0;
	std::atomic<int> blank_lines = 0;
	std::atomic<int> comment_lines = 0;
	std::atomic<int> code_lines = 0;
};

class CodeAnalyzer
{
private:
	std::vector<std::string> file_paths;
	std::mutex mutex;
	struct FileData stats;

	void ParseFilePath(std::string_view main_path);

	void WorkThread();

	void ParseFile(const std::string& path);

	void WriteStats(double execution_time);
public:

	void StartProgram(std::string_view main_path);
};