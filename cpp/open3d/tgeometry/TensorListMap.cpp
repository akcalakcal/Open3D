// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include <fmt/format.h>
#include <sstream>
#include <string>
#include <unordered_map>

#include "open3d/tgeometry/TensorListMap.h"
#include "open3d/utility/Console.h"

namespace open3d {
namespace tgeometry {

bool TensorListMap::IsSizeSynchronized() const {
    for (auto& kv : *this) {
        if (kv.second.GetSize() != GetMasterSize()) {
            return false;
        }
    }
    return true;
}

void TensorListMap::AssertSizeSynchronized() const {
    if (!IsSizeSynchronized()) {
        std::stringstream ss;
        ss << fmt::format("Master TensorList {} has size {}, however: \n",
                          master_key_, GetMasterSize());
        for (auto& kv : *this) {
            if (kv.first != master_key_ &&
                kv.second.GetSize() != GetMasterSize()) {
                fmt::format("    TensorList {} has size {}\n", kv.first,
                            kv.second.GetSize());
            }
        }
        utility::LogError("{}", ss.str());
    }
}

}  // namespace tgeometry
}  // namespace open3d
