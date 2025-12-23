#pragma once
// 引入 Windows 相关的类型定义（HBRUSH 等）
#include <Windows.h>
namespace corn {

    class AutoHBrush {
    public:
        // 构造函数声明
        AutoHBrush(HBRUSH hBrush = nullptr);
        // 析构函数声明
        ~AutoHBrush();

        // 禁止拷贝（声明）
        AutoHBrush(const AutoHBrush&) = delete;
        AutoHBrush& operator=(const AutoHBrush&) = delete;

        // 移动语义声明
        AutoHBrush(AutoHBrush&& other) noexcept;
        AutoHBrush& operator=(AutoHBrush&& other) noexcept;

        // 成员函数声明
        HBRUSH Get() const;
        void Reset(HBRUSH hBrush);

    private:
        // 私有函数声明
        void Release();
        // 成员变量
        HBRUSH m_hBrush;
    };
}