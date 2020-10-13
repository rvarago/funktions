#include <funktions/all.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace rvarago::funktions;
using namespace rvarago::funktions::dsl;

namespace {

using identifier = long;
using vendor_identifier = long;

enum class status { Idle, Waiting, Busy };

struct device {
    identifier id;
    vendor_identifier vendor_id;
    status current_status;
};

}

int main(int, char *[]) {
    auto const device_registry = std::vector<device>{
        {identifier{1}, vendor_identifier{1}, status::Idle},    {identifier{2}, vendor_identifier{1}, status::Busy},
        {identifier{3}, vendor_identifier{2}, status::Idle},    {identifier{4}, vendor_identifier{2}, status::Busy},
        {identifier{5}, vendor_identifier{2}, status::Waiting},
    };

    // Given a device d: d.vendor_id == 2 and d.current_status == status::Idle
    auto const search_query = fn(&device::vendor_id) >> eq(2) & fn(&device::current_status) >> ne(status::Busy);

    auto const device_found = std::find_if(device_registry.cbegin(), device_registry.cend(), search_query);

    assert(device_found->id == 3);

    std::cout << "Device ID: " << device_found->id << '\n';
}