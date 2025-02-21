lispvm: LispVM.h main.cpp stack.cpp heap.cpp strings.cpp operations.cpp
	g++ -g -o lispvm main.cpp stack.cpp heap.cpp strings.cpp operations.cpp

sizes: LispVM.h sizes.cpp
	g++ -g -o sizes sizes.cpp
