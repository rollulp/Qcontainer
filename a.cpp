#include "container.h"

void print(const Container<int> &u) {
	for(int i = 0; i < u.size(); i++)
		cout << u[i] << endl;
}

void a() {
Container<int> a;
a.resize(10);
print(a);
}
