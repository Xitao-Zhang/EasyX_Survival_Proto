#pragma once
#include <vector>
#include <graphics.h>
#include <string>
#include <memory>
#include "utils.hpp"
#include "Enums.hpp"

class Atlas
{
public:
	Atlas(LPCTSTR path, int num);
	Atlas(Atlas* target, processtype type); // 翻转target得到新的图像，目的是不需要准备两套图片

public:
	std::vector<std::unique_ptr<IMAGE>> frame_list;
};