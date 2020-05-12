#pragma once
#ifndef _HULU_BASE_VARIANT_CASE_H
#define _HULU_BASE_VARIANT_CASE_H

#include "../gvals.h"

#include <variant>

_HULU_BEGIN

// A helper to create overloaded function objects
template <typename... Fs>
struct overloaded : Fs... { using Fs::operator()...; };

template <typename... Fs> overloaded(Fs...)->overloaded<Fs...>;

/**
 * ����std::variant�е�ÿ�����ܵ�����ͨ��ģʽƥ��ķ�ʽ�򻯴���
 (����switch/case)
 */
class Init_state
{
public:
    int count = 0;
};

class Run_state
{
};

class Finished_state
{
};

std::variant<Init_state, Run_state, Finished_state> player;

void checked()
{
    std::visit(
        overloaded{
            [&](const Init_state& state) {},
            [&](const Run_state& state) {},
            [&](const Finished_state& state) {}
        }, player
    );
}

_HULU_END

#endif // _HULU_BASE_VARIANT_CASE_H