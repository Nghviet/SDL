#pragma once
#ifndef THREAD_H_
#define THREAD_H_

#include<future>

void loadThread();

void loadRender(std::future<void> signal);

#endif // !THREAD_H_
