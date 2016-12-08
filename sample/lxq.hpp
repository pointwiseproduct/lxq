#ifndef LXQ_HPP_
#define LXQ_HPP_

namespace lxq{
    template<class T = void>
    class semantic_data_proto{
    public:
        virtual ~semantic_data_proto() = default;
    };

    using semantic_data = semantic_data_proto<>;
}

#endif
