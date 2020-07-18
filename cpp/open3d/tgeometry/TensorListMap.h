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

#pragma once

#include <string>
#include <unordered_map>

#include "open3d/core/TensorList.h"

namespace open3d {
namespace tgeometry {

/// Map of string -> TensorList. Provides helper function to maintain
/// synchronized size (length) for the tensorlists.
///
/// The master key's tensorlist's size is used as the master size and master
/// device. Other tensorlist's size and device should be synchronized according
/// to the master.
class TensorListMap : public std::unordered_map<std::string, core::TensorList> {
public:
    /// Create empty TensorListMap and set master key.
    TensorListMap(const std::string& master_key)
        : std::unordered_map<std::string, core::TensorList>(),
          master_key_(master_key) {}

    TensorListMap() = delete;

    bool IsSizeSynchronized() const;

    void AssertSizeSynchronized() const;

    std::string GetMasterKey() const { return master_key_; }

    void SetMasterKey(const std::string& key) { master_key_ = key; }

    int64_t GetMasterSize() const { return at(master_key_).GetSize(); }

private:
    ///
    std::string master_key_ = "UNDEFINED";
};

}  // namespace tgeometry
}  // namespace open3d
