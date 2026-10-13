#include <type_traits>

#include "pack.h"

using P = Pack<int, char, double, char>;
using Empty = Pack<>;

static_assert(P::size == 4);
static_assert(Empty::size == 0);
static_assert(pack_detail::packSize<int, bool> == 2);

static_assert(std::is_same_v<P::type<0>, int>);
static_assert(std::is_same_v<P::type<1>, char>);
static_assert(std::is_same_v<P::type<2>, double>);
static_assert(std::is_same_v<P::type<3>, char>);
static_assert(std::is_same_v<pack_detail::packIndexToType<0, float>, float>);


static_assert(P::index<int> == 0);
static_assert(P::index<char> == 1);  
static_assert(P::index<double> == 2);
static_assert(P::index<float> == -1);
static_assert(Empty::index<int> == -1);

int main() { return 0; }