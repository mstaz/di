//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "boost/di/detail/creator.hpp"

#include <vector>
#include <boost/test/unit_test.hpp>
#include <boost/function.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/is_same.hpp>

#include "boost/di/aux_/memory.hpp"
#include "common/fakes/fake_dependency.hpp"
#include "common/fakes/fake_binder.hpp"
#include "common/fakes/fake_visitor.hpp"
#include "common/fakes/fake_pool.hpp"
#include "common/data.hpp"

namespace boost {
namespace di {
namespace detail {

class policy
{
public:
    template<typename T>
    void assert_policy()
    { }
};

BOOST_AUTO_TEST_CASE(creator_pod) {
    const int i = 42;

    typedef fake_dependency<scopes::unique<>, int, mpl::int_<i>>::type dependency_type;
    fake_pool<dependency_type> deps;
    std::vector<aux::shared_ptr<void>> refs;

    BOOST_CHECK_EQUAL(i, (
        creator<mpl::vector<dependency_type>>().create<
            int, int, mpl::vector0<>
        >(deps, refs, fake_visitor<mpl::vector<int>>(), fake_pool<>())
    ));
}

//BOOST_AUTO_TEST_CASE(creator_interface_call_stack) {
    //typedef fake_dependency<scopes::unique<>, if0, c0if0>::type dependency_type;
    //fake_pool<dependency_type> deps;
    //std::vector<aux::shared_ptr<void>> refs;
    //struct empty_visitor
    //{
        //template<typename T>
        //void operator()(const T&) const { }
    //} visitor;

    //creator<mpl::vector<dependency_type>>().create<c5, c5, mpl::vector0<>, mpl::vector0<>>(deps, refs, visitor);
//}

} // namespace detail
} // namespace di
} // namespace boost

