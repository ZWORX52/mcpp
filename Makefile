CPPFLAGS=-std=gnu++20 -Wall -Wextra -Werror -Itomlplusplus/include
LDFLAGS=-lfmt
mc: mc.cpp
	g++ -O3 -DNDEBUG $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f mcpp
