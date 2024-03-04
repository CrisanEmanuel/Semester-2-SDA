#include <exception>
#include "Iterator.h"
#include "DO.h"

using namespace std;

Iterator::Iterator(const DO& d) : dict(d) {
    it = dict.head;
}

void Iterator::prim() {
    it = dict.head;
}

void Iterator::urmator() {
    if (!valid()) throw std::exception();
    it = it -> next;
}

bool Iterator::valid() const {
    if (it != nullptr) return true;
	return false;
}

TElem Iterator::element() const {
    if (!valid()) throw std::exception();
    return make_pair(it -> info.first, it -> info.second);
}