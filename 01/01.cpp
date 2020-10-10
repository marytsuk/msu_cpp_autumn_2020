#include <iostream>
#include <stdio.h>
using namespace std;
class Allocator
{
	char* start;
	char* end;
	char* offset;
public:
	void makeAllocator(size_t maxsize);
	char* alloc(size_t size);
	void reset();
	~Allocator();
};
void Allocator::makeAllocator(size_t maxsize)
{
	start = new char[maxsize];
	end = start + maxsize;
	offset = start;
}
char* Allocator::alloc(size_t size)
{
	if (size == 0)
	{
		return nullptr;
	}
	else
	{
		if (offset + size <= end)
		{
		
			offset += size;
			return offset - size;
		}
		else
		{
			return nullptr;
		}
	}
}
void Allocator::reset()
{
	offset = start;
}
Allocator::~Allocator()
{
	delete[] start;
}
int main(int argc, char** argv)
{
     if (argc < 2 || atoi(argv[1]) == 0)
     {
	     cout << "No arguments!" << endl;
	     return 0;
     }
     Allocator test;
     size_t maxSize = atoi(argv[1]);
     int allocsNum = atoi(argv[2]);

     test.makeAllocator(maxSize);
    
    
     for (int i = 0; i < allocsNum; i++)
     {
	     char* ptr = test.alloc(atoi(argv[3 + i]));
	     if (ptr == nullptr)
	     {
		     cout << "Out of size!" << endl << "Wanted to alloc + "<< atoi(argv[3 + i]) << ", step: " << i + 1 << endl;
		     return 0;
	     }

     }
     return 0;

}
