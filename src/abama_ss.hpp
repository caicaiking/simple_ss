#ifndef abama_ss_hpp
#define abama_ss_hpp

#include "arg_at_fun.hpp"
#include <algorithm>
#include <boost/core/noncopyable.hpp>
#include <boost/noncopyable.hpp>
#include <functional>
#include <map>
#include <type_traits>
#include <vector>
#include "task_slot.hpp"

namespace abama_ss
{
    namespace core
    {
        using tag_type = int;
        template <typename fun_type>
        auto get_exe_fun(tag_type data_tag, fun_type fn);

        class abama_core : public boost::noncopyable
        {
        public:
            template <typename fun_type>
            friend auto get_exe_fun(int data_tag, fun_type fn);

            using exe_fn_type = void (*)();

        private:
            std::map<tag_type, const void *> _tag_data_map;
            std::map<tag_type, std::vector<std::function<void()>>> _tag_fun_map;
            std::map<size_t, task_slot<1000>> _task_sink;

        public:
            static abama_core &get_instance()
            {
                static abama_core _instance;
                return _instance;
            }

        public:
            template <typename data_type>
            void bind_tag_to_data(tag_type data_tag, const data_type *p_data)
            {
                _tag_data_map[data_tag] = static_cast<const void *>(p_data);
            }

            template <typename fun_type>
            void connect(tag_type data_tag, fun_type fun)
            {
                auto fun_s = get_exe_fun(data_tag, fun);
                this->_tag_fun_map[data_tag].push_back(fun_s);
            }

            void emit(size_t task_level, tag_type data_tag)
            {
                auto &func_s = _tag_fun_map.at(data_tag);

                auto &task_slot = _task_sink[task_level];
                task_slot.insert(std::begin(func_s), std::end(func_s));
            }

            void run(int task_level)
            {
                auto &task_slot = _task_sink[task_level];
                task_slot.run();
            }
        };

        template <typename fun_type>
        auto get_exe_fun(int data_tag, fun_type fn)
        {
            auto trans_fun = [=]() {
                auto par = static_cast<
                    std::add_const_t<typename arg_at_functions<0, fun_type>::type>>(
                    abama_core::get_instance()._tag_data_map.at(data_tag));

                if (par != nullptr)
                {
                    fn(par);
                }
            };
            return trans_fun;
        }
    } // namespace core
} // namespace abama_ss

#endif
