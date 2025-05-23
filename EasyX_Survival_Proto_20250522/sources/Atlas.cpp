#include "../includes/Atlas.hpp"

Atlas::Atlas(LPCTSTR path, int num)
{
	TCHAR path_file[256];
	for (size_t i = 0; i < num; i++)
	{
		_stprintf_s(path_file, path, i + 1);
		auto frame = std::make_unique<IMAGE>(); // 使用智能指针，不需要再手动清理
		loadimage(frame.get(), path_file);
		frame_list.push_back(std::move(frame));
	}
}

Atlas::Atlas(Atlas* target, processtype type)
{
	int frame_num = target->frame_list.size();
	int width = target->frame_list[0].get()->getwidth();
	int height = target->frame_list[0].get()->getheight();
	switch (type)
	{
	case processtype::flip:
		for (size_t i = 0; i < frame_num; i++)
		{
			auto frame_right = std::make_unique<IMAGE>();
			Resize(frame_right.get(), width, height);
			frame_list.push_back(std::move(frame_right));

			DWORD* color_buffer_raw_img = GetImageBuffer(target->frame_list[i].get());
			DWORD* color_buffer_flip_img = GetImageBuffer(frame_list[i].get());
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					int index_left_img = y * width + x;
					int index_right_img = y * width + (width - x - 1);
					color_buffer_flip_img[index_right_img] = color_buffer_raw_img[index_left_img];
				}
			}
		}
		break;
	case processtype::white:
		for (size_t i = 0; i < frame_num; i++)
		{
			auto frame_right = std::make_unique<IMAGE>();
			Resize(frame_right.get(), width, height);
			frame_list.push_back(std::move(frame_right));

			DWORD* color_buffer_raw_img = GetImageBuffer(target->frame_list[i].get());
			DWORD* color_buffer_sketch_img = GetImageBuffer(frame_list[i].get());
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					int idx = y * width + x;
					if ((color_buffer_raw_img[idx] & 0xFF000000) >> 24)
						color_buffer_sketch_img[idx] = BGR(RGB(255, 255, 255)) | (((DWORD)(BYTE)(255)) << 24);
				}
			}
		}
		break;
	}
}