//#pragma once
//#ifndef _HULU_BASE_LSIGNAL_H_
//#define _HULU_BASE_LSIGNAL_H_
//
//#include "../gvals.h"
//
//#include <functional>
//#include <memory>
//#include <vector>
//
//_HULU_BEGIN
//
///**
// * �󶨲���ռλ��
// */
//template <int>
//struct placeholder_lsignal
//{
//};
//
//_HULU_END
//
//_STD_BEGIN
//
///**
// * ƫ�ػ���ģ��is_placeholder<>, ����placeholder_lsignal<>��ģ��Ϊ������λ��(ע��������1)
// */
//template<int N>
//struct is_placeholder<hulu::placeholder_lsignal<N>> : public integral_constant<int, N + 1>
//{
//};
//
//_STD_END
//
//_HULU_BEGIN
//
//template <int ...Ns>
//struct int_sequence
//{
//};
//
//template <int N, int ...Ns>
//struct make_int_sequence : make_int_sequence<N - 1, N - 1, Ns...>
//{
//};
//
//template <int ...Ns>
//struct make_int_sequence<0, Ns...> : int_sequence<Ns...>
//{
//};
//
///**
// * connection
// */
//struct connection_data
//{
//    bool locked;
//};
//
//struct connection_cleaner
//{
//    std::function<void(std::shared_ptr<connection_data>)> deleter;
//    std::shared_ptr<connection_data> data;
//};
//
//class connection
//{
//    template <typename>
//    friend class signal;
//
//public:
//    connection(std::shared_ptr<connection_data>&& data)
//    {
//
//    }
//
//private:
//    std::shared_ptr<connection_data> _data;
//    std::vector<connection_cleaner> _cleaners;
//};
//
//_HULU_END
//
//#endif /* _HULU_BASE_LSIGNAL_H_ */