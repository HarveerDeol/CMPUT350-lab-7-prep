#ifndef PACK_H
#define PACK_H

namespace pack_detail {

template <typename... Args>
constexpr int packSize = sizeof...(Args);

template <int QueryIndex, typename... Args>
struct _packIndexToType;  

template <typename T, typename... Rest>
struct _packIndexToType<0, T, Rest...> { 
    using type = T;
};

template <int QueryIndex, typename T, typename... Rest>
struct _packIndexToType<QueryIndex, T, Rest...> {  
    using type = typename _packIndexToType<QueryIndex - 1, Rest...>::type;
};

template <int QueryIndex, typename... Args>
using packIndexToType = typename _packIndexToType<QueryIndex, Args...>::type;

template <int Accumulated, typename QueryType, typename... Args>
constexpr int _packTypeToIndex = -1; 

template <int Accumulated, typename QueryType, typename... Rest>
constexpr int _packTypeToIndex<Accumulated, QueryType, QueryType, Rest...> =
    Accumulated; 

template <int Accumulated, typename QueryType, typename T, typename... Rest>
constexpr int _packTypeToIndex<Accumulated, QueryType, T, Rest...> =
    _packTypeToIndex<Accumulated + 1, QueryType, Rest...>;  

template <typename QueryType, typename... Args>
constexpr int packTypeToIndex = _packTypeToIndex<0, QueryType, Args...>;

} 

template <typename... Args>
struct Pack {
    static constexpr int size = pack_detail::packSize<Args...>;

    template <int QueryIndex>
    using type = pack_detail::packIndexToType<QueryIndex, Args...>;

    template <typename QueryType>
    constexpr static int index =
        pack_detail::packTypeToIndex<QueryType, Args...>;
};

#endif  // PACK_H