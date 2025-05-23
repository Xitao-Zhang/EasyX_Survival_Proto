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
	Atlas(Atlas* target, processtype type); // ��תtarget�õ��µ�ͼ��Ŀ���ǲ���Ҫ׼������ͼƬ

public:
	std::vector<std::unique_ptr<IMAGE>> frame_list;
};