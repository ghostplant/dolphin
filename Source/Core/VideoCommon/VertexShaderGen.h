// Copyright 2008 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "Common/CommonTypes.h"
#include "VideoCommon/LightingShaderGen.h"
#include "VideoCommon/ShaderGenCommon.h"

enum class APIType;
enum class TexInputForm : u32;
enum class TexGenType : u32;
enum class SourceRow : u32;
enum class VSExpand : u32;

// TODO should be reordered
enum : int
{
  SHADER_POSITION_ATTRIB = 0,
  SHADER_POSMTX_ATTRIB = 1,
  SHADER_NORMAL_ATTRIB = 2,
  SHADER_TANGENT_ATTRIB = 3,
  SHADER_BINORMAL_ATTRIB = 4,
  SHADER_COLOR0_ATTRIB = 5,
  SHADER_COLOR1_ATTRIB = 6,

  SHADER_TEXTURE0_ATTRIB = 8,
  SHADER_TEXTURE1_ATTRIB = 9,
  SHADER_TEXTURE2_ATTRIB = 10,
  SHADER_TEXTURE3_ATTRIB = 11,
  SHADER_TEXTURE4_ATTRIB = 12,
  SHADER_TEXTURE5_ATTRIB = 13,
  SHADER_TEXTURE6_ATTRIB = 14,
  SHADER_TEXTURE7_ATTRIB = 15
};

#pragma pack(1)

struct vertex_shader_uid_data
{
  u32 NumValues() const { return sizeof(vertex_shader_uid_data); }
  u32 components : 23;
  u32 numTexGens : 4;
  u32 numColorChans : 2;
  u32 dualTexTrans_enabled : 1;
  VSExpand vs_expand : 2;
  u32 position_has_3_elems : 1;

  u16 texcoord_elem_count;      // 2 bits per texcoord input
  u16 texMtxInfo_n_projection;  // Stored separately to guarantee that the texMtxInfo struct is
                                // 8 bits wide

  struct
  {
    TexInputForm inputform : 2;
    TexGenType texgentype : 3;
    SourceRow sourcerow : 5;
    u32 embosssourceshift : 3;
    u32 embosslightshift : 3;
  } texMtxInfo[8];

  struct
  {
    u32 index : 6;
    u32 normalize : 1;
    u32 pad : 1;
  } postMtxInfo[8];

  LightingUidData lighting;
};
#pragma pack()

using VertexShaderUid = ShaderUid<vertex_shader_uid_data>;

VertexShaderUid GetVertexShaderUid();
ShaderCode GenerateVertexShaderCode(APIType api_type, const ShaderHostConfig& host_config,
                                    const vertex_shader_uid_data* uid_data);
