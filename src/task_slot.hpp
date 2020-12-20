#ifndef SOURCE_SINK_HPP
#define SOURCE_SINK_HPP

#include <functional>
#include <queue>
#include <vector>
#include <boost/noncopyable.hpp>
#include <cassert>

namespace simple_ss::core
{
    template <size_t hwm = 100, typename FunType = std::function<void()>,
              typename Cont = std::vector<FunType>>
    class task_slot : public boost::noncopyable
    {
    public:
        static_assert(hwm > 0, "HWM muster greater than 0");
        using container_type = Cont;
        using value_type = FunType;

        void run()
        {
            for (auto &fun : *current_slot)
            {
                if (fun != nullptr)
                {
                    fun();
                }
            }
            current_slot->clear();
            std::swap(current_slot, next_slot);
        }

        void insert(value_type fun)
        {
            this->next_slot->push_back(fun);
            assert(next_slot->size() <= hwm);
        }

        template <typename Iter>
        void insert(Iter b, Iter e)
        {
            std::copy(b, e, std::back_inserter<Cont>(*next_slot));
            assert(next_slot->size() <= hwm);
        }

    private:
        container_type _container[2];
        container_type *current_slot = &_container[0];
        container_type *next_slot = &_container[1];
    };
} // namespace simple_ss::core

#endif
