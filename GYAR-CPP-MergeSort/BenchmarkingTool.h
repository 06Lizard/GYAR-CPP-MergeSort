#pragma once
#include "List.h"

class BenchmarkingTool
{
private:
	static const short MenueItmesNum = 11;

	List<int> list;

public:
	BenchmarkingTool() {}
	void run();

private:
	int navigateMenu();
	void printMenu();
	void updateMenu(short selectedIndex);
	void addRandomElements();
	void addRandomElements(int num, int min, int max);
	void addElement();
	void removeElement();
	void printElement();
	void benchmarkSorts();
};

