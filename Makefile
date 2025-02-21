lispvm: LispVM.h main.cpp stack.cpp heap.cpp strings.cpp operations.cpp permsyms.cpp
	g++ -g -o lispvm main.cpp stack.cpp heap.cpp strings.cpp operations.cpp permsyms.cpp

sizes: LispVM.h sizes.cpp
	g++ -g -o sizes sizes.cpp
