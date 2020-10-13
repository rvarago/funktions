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

auto fetch_all_devices() -> std::vector<device> {
    return std::vector<device>{
        {identifier{1}, vendor_identifier{1}, status::Idle},    {identifier{2}, vendor_identifier{1}, status::Busy},
        {identifier{3}, vendor_identifier{2}, status::Idle},    {identifier{4}, vendor_identifier{2}, status::Busy},
        {identifier{5}, vendor_identifier{2}, status::Waiting},
    };
}

int main(int, char *[]) {
    auto const device_registry = fetch_all_devices();

    // Given a device d: d.vendor_id == 2 and d.current_status != status::Busy
    auto const search_query = fn(&device::vendor_id) >> eq(2) & fn(&device::current_status) >> ne(status::Busy);

    auto const device = std::find_if(device_registry.cbegin(), device_registry.cend(), search_query);

    assert(device != std::cend(device_registry));
    assert(device->id == 3);

    std::cout << "Device ID: " << device->id << '\n';
}