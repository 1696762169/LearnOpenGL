#pragma once


/**
 * \brief 渲染接口
 */
class IRender
{
public:
	virtual ~IRender() = default;
	virtual void Render() = 0;
};
