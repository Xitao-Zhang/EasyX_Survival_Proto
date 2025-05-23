#pragma once
#include <vector>
#include <graphics.h>
#include <string>
#include <memory>
#include "utils.hpp"

class Button
{
public:
	Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);
	void Draw() const;
	void ProcessEvent(const ExMessage& msg);
	virtual void OnClick() = 0;

private:
	bool CheckCursorHit(int x, int y) const;

private:
	RECT region;
	IMAGE img_idle;
	IMAGE img_hovered;
	IMAGE img_pushed;
	enum class Status
	{
		Idle = 0,
		Hovered,
		Pushed
	};
	Status status = Status::Idle;
};