// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2022 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "pass_level2.h"

namespace pnnx {

class torch_addmm : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
7 6
pnnx.Input              input_0     0 1 input
pnnx.Input              input_1     0 1 mat1
pnnx.Input              input_2     0 1 mat2
pnnx.Input              input_3     0 1 beta
pnnx.Input              input_4     0 1 alpha
aten::addmm             op_0        5 1 input mat1 mat2 beta alpha out
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "torch.addmm";
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_addmm, 90)

class torch_addmm_1 : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
5 4
pnnx.Input              input_0     0 1 input
pnnx.Input              input_1     0 1 mat1
pnnx.Input              input_2     0 1 mat2
aten::addmm             op_0        3 1 input mat1 mat2 out beta=%beta alpha=%alpha
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "torch.addmm";
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_addmm_1, 90)

} // namespace pnnx
