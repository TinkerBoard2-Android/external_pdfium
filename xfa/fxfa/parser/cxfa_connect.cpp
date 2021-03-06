// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "xfa/fxfa/parser/cxfa_connect.h"

#include "fxjs/xfa/cjx_connect.h"
#include "third_party/base/ptr_util.h"

namespace {

const CXFA_Node::PropertyData kPropertyData[] = {
    {XFA_Element::Picture, 1, 0},
    {XFA_Element::ConnectString, 1, 0},
    {XFA_Element::User, 1, 0},
    {XFA_Element::Password, 1, 0},
    {XFA_Element::Unknown, 0, 0}};
const CXFA_Node::AttributeData kAttributeData[] = {
    {XFA_Attribute::Id, XFA_AttributeType::CData, nullptr},
    {XFA_Attribute::Name, XFA_AttributeType::CData, nullptr},
    {XFA_Attribute::Ref, XFA_AttributeType::CData, nullptr},
    {XFA_Attribute::Use, XFA_AttributeType::CData, nullptr},
    {XFA_Attribute::Timeout, XFA_AttributeType::Integer, (void*)15},
    {XFA_Attribute::Connection, XFA_AttributeType::CData, nullptr},
    {XFA_Attribute::Usage, XFA_AttributeType::Enum,
     (void*)XFA_AttributeEnum::ExportAndImport},
    {XFA_Attribute::Usehref, XFA_AttributeType::CData, nullptr},
    {XFA_Attribute::DelayedOpen, XFA_AttributeType::CData, nullptr},
    {XFA_Attribute::Unknown, XFA_AttributeType::Integer, nullptr}};

constexpr wchar_t kName[] = L"connect";

}  // namespace

CXFA_Connect::CXFA_Connect(CXFA_Document* doc, XFA_PacketType packet)
    : CXFA_Node(doc,
                packet,
                (XFA_XDPPACKET_SourceSet | XFA_XDPPACKET_Template |
                 XFA_XDPPACKET_Form),
                XFA_ObjectType::Node,
                XFA_Element::Connect,
                kPropertyData,
                kAttributeData,
                kName,
                pdfium::MakeUnique<CJX_Connect>(this)) {}

CXFA_Connect::~CXFA_Connect() {}
