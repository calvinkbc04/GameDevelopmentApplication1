#pragma once

#include <map>
#include <string>
#include <vector>

class ResourceManager
{
private:
	std::map<std::string, std::vector<int>> image_container;

public:
	ResourceManager();
	~ResourceManager();

	const std::vector<int>& GetImages(std::string file_path);
	const std::vector<int>& GetImages(std::string file_path, int all_num, int
		x_num, int y_num, int x_size, int y_size);

	void DeleteImages();
};

ResourceManager* GetResourceManager();