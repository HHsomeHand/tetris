#include "AutoHBrush.h"

namespace corn {

    // 构造函数实现
    AutoHBrush::AutoHBrush(HBRUSH hBrush) : m_hBrush(hBrush) {}

    // 析构函数实现
    AutoHBrush::~AutoHBrush() {
        Release();
    }

    // 移动构造函数实现
    AutoHBrush::AutoHBrush(AutoHBrush&& other) noexcept : m_hBrush(other.m_hBrush) {
        other.m_hBrush = nullptr;
    }

    // 移动赋值运算符实现
    AutoHBrush& AutoHBrush::operator=(AutoHBrush&& other) noexcept {
        if (this != &other) {
            Release();
            m_hBrush = other.m_hBrush;
            other.m_hBrush = nullptr;
        }
        return *this;
    }

    // get 函数实现（简单函数可内联，也可放 cpp）
    HBRUSH AutoHBrush::Get() const {
        return m_hBrush;
    }

    // reset 函数实现
    void AutoHBrush::Reset(HBRUSH hBrush) {
        Release();
        m_hBrush = hBrush;
    }

    // release 私有函数实现
    void AutoHBrush::Release() {
        if (m_hBrush) {
            ::DeleteObject(m_hBrush);
            m_hBrush = nullptr;
        }
    }
}