// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FXCODEC_GIF_CFX_GIF_H_
#define CORE_FXCODEC_GIF_CFX_GIF_H_

#include <memory>
#include <vector>

class CFX_GifContext;

extern const char* kGifSignature87;
extern const char* kGifSignature89;

#define GIF_SIG_EXTENSION 0x21
#define GIF_SIG_IMAGE 0x2C
#define GIF_SIG_TRAILER 0x3B
#define GIF_BLOCK_GCE 0xF9
#define GIF_BLOCK_PTE 0x01
#define GIF_BLOCK_CE 0xFE
#define GIF_BLOCK_TERMINAL 0x00
#define GIF_MAX_LZW_EXP 12
#define GIF_MAX_LZW_CODE 4096
#define GIF_DATA_BLOCK 255
#define GIF_D_STATUS_SIG 0x01
#define GIF_D_STATUS_TAIL 0x02
#define GIF_D_STATUS_EXT 0x03
#define GIF_D_STATUS_EXT_CE 0x05
#define GIF_D_STATUS_EXT_GCE 0x06
#define GIF_D_STATUS_EXT_PTE 0x07
#define GIF_D_STATUS_EXT_UNE 0x08
#define GIF_D_STATUS_IMG_INFO 0x09
#define GIF_D_STATUS_IMG_DATA 0x0A

#pragma pack(1)
typedef struct {
  uint8_t pal_bits : 3;
  uint8_t sort_flag : 1;
  uint8_t color_resolution : 3;
  uint8_t global_pal : 1;
} CFX_GifGlobalFlags;

typedef struct {
  uint8_t pal_bits : 3;
  uint8_t reserved : 2;
  uint8_t sort_flag : 1;
  uint8_t interlace : 1;
  uint8_t local_pal : 1;
} CFX_GifLocalFlags;

typedef struct { char signature[6]; } CFX_GifHeader;

typedef struct {
  uint16_t width;
  uint16_t height;
  CFX_GifGlobalFlags global_flags;
  uint8_t bc_index;
  uint8_t pixel_aspect;
} CFX_GifLocalScreenDescriptor;

typedef struct {
  uint16_t left;
  uint16_t top;
  uint16_t width;
  uint16_t height;
  CFX_GifLocalFlags local_flags;
} CFX_CFX_GifImageInfo;

typedef struct {
  uint8_t transparency : 1;
  uint8_t user_input : 1;
  uint8_t disposal_method : 3;
  uint8_t reserved : 3;
} CFX_GifControlExtensionFlags;

typedef struct {
  uint8_t block_size;
  CFX_GifControlExtensionFlags gce_flags;
  uint16_t delay_time;
  uint8_t trans_index;
} CFX_GifGraphicControlExtension;

typedef struct {
  uint8_t block_size;
  uint16_t grid_left;
  uint16_t grid_top;
  uint16_t grid_width;
  uint16_t grid_height;

  uint8_t char_width;
  uint8_t char_height;

  uint8_t fc_index;
  uint8_t bc_index;
} CFX_GifPlainTextExtension;

typedef struct {
  uint8_t block_size;
  uint8_t app_identify[8];
  uint8_t app_authentication[3];
} GifApplicationExtension;

typedef struct { uint8_t r, g, b; } CFX_GifPalette;
#pragma pack()

enum class CFX_GifDecodeStatus {
  Error,
  Success,
  Unfinished,
  InsufficientDestSize,  // Only used internally by CGifLZWDecoder::Decode()
};

typedef struct {
  std::unique_ptr<CFX_GifGraphicControlExtension> image_GCE;
  std::vector<CFX_GifPalette> local_palettes;
  std::vector<uint8_t> row_buffer;
  CFX_CFX_GifImageInfo image_info;
  uint8_t local_pallette_exp;
  uint8_t code_exp;
  uint32_t data_pos;
  int32_t row_num;
} CFX_GifImage;

#endif  // CORE_FXCODEC_GIF_CFX_GIF_H_
