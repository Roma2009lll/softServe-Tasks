#include "statistic.hpp" 
  
void CodeAnalyzer::ParseFilePath(std::string_view main_path)
{
	file_paths.reserve(8);
	namespace fs = std::filesystem;
	for (const auto& it : fs::recursive_directory_iterator(main_path))
	{
		if (fs::is_regular_file(it.path()))
		{
			auto ext = it.path().extension().string();
			if (ext == ".c" || ext == ".cpp" || ext == ".h" || ext == ".hpp")
			{
				this->file_paths.emplace_back(it.path().string());
			}
		}
	}
}

void CodeAnalyzer::WorkThread()
{
	while (true)
	{
		std::string current_path;
		{
			std::lock_guard<std::mutex> lock(this->mutex);
			if (this->file_paths.empty())
			{
				break;
			}
			current_path = this->file_paths.back();
			this->file_paths.pop_back();
		}
		ParseFile(current_path);
	}
}

void CodeAnalyzer::ParseFile(const std::string& path)
{

	std::ifstream fp(path);
	if (!fp.is_open())
	{
		return;
	}
	int temp_blank_lines = 0,temp_comment_lines=0,temp_code_lines=0;
	std::string line;
	bool is_multiline_comment = false;
	while (std::getline(fp, line))
	{
		size_t first_char = line.find_first_not_of(" \t\r\n");
		if (first_char==std::string::npos)
		{
			if (is_multiline_comment)
			{
				temp_comment_lines++;
			}
			else
			{
				temp_blank_lines++;
			}
			continue;
		}
		if(is_multiline_comment)
		{
			temp_comment_lines++;
			if (line.find("*/") != std::string::npos)
			{
				is_multiline_comment = false;
			}
			continue;
		}
		if (line.substr(first_char, 2) == "//")
		{
			temp_comment_lines++;
			continue;
		}
		if (line.substr(first_char, 2) == "/*")
		{
			temp_comment_lines++;
			if (line.find("*/") == std::string::npos)
			{
				is_multiline_comment = true;
			}
			continue;
		}
		temp_code_lines++;
		size_t hidden_comment0 = line.find("/*");
		if (hidden_comment0 != std::string::npos) {
			if (line.find("*/", hidden_comment0 + 2) == std::string::npos) {
				is_multiline_comment = true;
			}
			continue;
		}
	}
	this->stats.blank_lines += temp_blank_lines;
	this->stats.comment_lines += temp_comment_lines;
	this->stats.code_lines += temp_code_lines;
	this->stats.total_files++;
}

void CodeAnalyzer::WriteStats(double execution_time)
{
	std::ofstream fp("Statistick.txt");
	if (!fp.is_open())
	{
		return;
	}
	fp << "Total files processed:" << this->stats.total_files << "\n";
	fp << "Blank lines:" << this->stats.blank_lines << "\n";
	fp << "Comment lines:" << this->stats.comment_lines << "\n";
	fp << "Code lines:" << this->stats.code_lines << "\n";
	fp << "Time of execution: " << execution_time << " ms\n";
}

void CodeAnalyzer::StartProgram(std::string_view main_path)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	ParseFilePath(main_path);
	std::vector<std::thread> workers;
	int num_threads = std::thread::hardware_concurrency();
	if (num_threads == 0)
	{
		num_threads = 8;
	}
	for (int i = 0; i < num_threads; i++)
	{
		workers.emplace_back(&CodeAnalyzer::WorkThread, this);
	}
	for (auto& it : workers)
	{
		it.join();
	}
	auto end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = end_time - start_time;
	CodeAnalyzer::WriteStats(duration.count());
}
