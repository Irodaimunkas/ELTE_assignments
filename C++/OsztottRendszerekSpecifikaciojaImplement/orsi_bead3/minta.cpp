#include <iostream>
#include <thread>
#include <vector>
#include "pipe.hpp"


void f(Pipe<int>& from, Pipe<int>& to)
{
	int data = from.pop();
	data += 2;
	to.push(data);
}


int main(int argc, char const *argv[])
{
	std::vector<Pipe<int>> pipes(2);
	std::thread t(f, std::ref(pipes[0]), std::ref(pipes[1]));

	int data = 40;
	std::cout << "Data before travelling through the pipe: " << data << std::endl;
	pipes[0].push(data);

	data = pipes[1].pop();
	std::cout << "Data after travelling through the pipe: " << data << std::endl;
	t.join();
	return 0;
}