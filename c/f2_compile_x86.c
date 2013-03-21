// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
// 
// Permission to use, copy, modify and distribute this software and its
// documentation is hereby granted, provided that both the copyright
// notice and this permission notice appear in all copies of the
// software, derivative works or modified versions, and any portions
// thereof, and that both notices appear in supporting documentation.
// 
// BO MORGAN ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION.
// BO MORGAN DISCLAIMS ANY LIABILITY OF ANY KIND FOR ANY DAMAGES
// WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
// 
// Bo Morgan requests users of this software to return to bo@mit.edu any
// improvements or extensions that they make and grant Bo Morgan the
// rights to redistribute these changes.
// 

#include "funk2.h"
#include "f2_ptypes_memory.h"

void raw__chunk__compile_x86__value_bit8( f2ptr this, u64 index, f2ptr cause, u64* next_index, u8  value) {
  if (this) {
    f2chunk__bit8__elt__set(this, index, cause, value);
  }
  *next_index = index + 1;
}

void raw__chunk__compile_x86__value_bit16(f2ptr this, u64 index, f2ptr cause, u64* next_index, u16 value) {
  if (this) {
    f2chunk__bit16__elt__set(this, index, cause, value);
  }
  *next_index = index + 2;
}

void raw__chunk__compile_x86__value_bit32(f2ptr this, u64 index, f2ptr cause, u64* next_index, u32 value) {
  if (this) {
    f2chunk__bit32__elt__set(this, index, cause, value);
  }
  *next_index = index + 4;
}

//80483dc:	50                   	push   %eax
//80483dd:	51                   	push   %ecx
//80483de:	52                   	push   %edx
//80483df:	53                   	push   %ebx
//80483e0:	54                   	push   %esp
//80483e1:	55                   	push   %ebp
//80483e2:	56                   	push   %esi
//80483e3:	57                   	push   %edi

void raw__chunk__compile_x86__push_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x50); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x51); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x52); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x53); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x54); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x55); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x56); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x57); break;
  }
}

//80483e4:	58                   	pop    %eax
//80483e5:	59                   	pop    %ecx
//80483e6:	5a                   	pop    %edx
//80483e7:	5b                   	pop    %ebx
//80483e8:	5c                   	pop    %esp
//80483e9:	5d                   	pop    %ebp
//80483ea:	5e                   	pop    %esi
//80483eb:	5f                   	pop    %edi

void raw__chunk__compile_x86__pop_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x58); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x59); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x5A); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x5B); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x5C); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x5D); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x5E); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x5F); break;
  }
}

//80483d1:	c3                   	ret    

void raw__chunk__compile_x86__ret(f2ptr this, u64 index, f2ptr cause, u64* next_index) {
  raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0xC3);
}

//80483ff:	e8 b0 ff ff ff       	call   80483b4 <test1>

void raw__chunk__compile_x86__call(f2ptr this, u64 index, f2ptr cause, u64* next_index, s32 relative_address) {
  raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, 0xE8); index = *next_index;
  raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, relative_address);
}

void raw__chunk__compile_x86__call_absolute(f2ptr this, u64 index, f2ptr cause, u64* next_index, u32 absolute_address) {
  s32 relative_jump_addr;
  if (this != nil) {
    u64 after_call_index;
    raw__chunk__compile_x86__call(nil, index, cause, &after_call_index, 0);
    relative_jump_addr = (s32)absolute_address - ((s32)(to_ptr(ptype_chunk__bytes(this, cause))) + after_call_index);
  } else {
    relative_jump_addr = 0;
  }
  raw__chunk__compile_x86__call(this, index, cause, next_index, relative_jump_addr);
}

//  17:	ff d0                	call   *%eax

void raw__chunk__compile_x86__call_eax(f2ptr this, u64 index, f2ptr cause, u64* next_index) {
  raw__chunk__compile_x86__value_bit16( this, index, cause, next_index, 0xD0FF);
}


//804840e:	83 c4 10             	add    $0x10,%esp

void raw__chunk__compile_x86__add(f2ptr this, u64 index, f2ptr cause, u64* next_index, u8 value) {
  raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, (u16)0xC483); index = *next_index;
  raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, value);
}

//80483d6:	83 ec 10             	sub    $0x10,%esp

void raw__chunk__compile_x86__sub__const_from_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, u8 value) {
  raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, (u16)0xEC83); index = *next_index;
  raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, value);
}

//80483da:	c9                   	leave  

void raw__chunk__compile_x86__leave(f2ptr this, u64 index, f2ptr cause, u64* next_index) {
  raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0xC9);
}

//'80483b7:	c7 05 c8 96 04 08 00 	movl   $0x0,0x80496c8'
//'80483be:	00 00 00 '
//'80483c1:	c7 05 cc 96 04 08 01 	movl   $0x1,0x80496cc'
//'80483c8:	00 00 00 '

void raw__chunk__compile_x86__movl(f2ptr this, u64 index, f2ptr cause, u64* next_index, u32 constant, u32 addr) {
  raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x05C7); index = *next_index;
  raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, addr);   index = *next_index;
  raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, constant);
}

//8048573:	b8 c8 96 04 08       	mov    $0x80496c8,%eax'
//8048578:	b9 c8 96 04 08       	mov    $0x80496c8,%ecx'
//804857d:	ba c8 96 04 08       	mov    $0x80496c8,%edx'
//8048582:	bb c8 96 04 08       	mov    $0x80496c8,%ebx'
//8048587:	bc c8 96 04 08       	mov    $0x80496c8,%esp'
//804858c:	bd c8 96 04 08       	mov    $0x80496c8,%ebp'
//8048591:	be c8 96 04 08       	mov    $0x80496c8,%esi'
//8048596:	bf c8 96 04 08       	mov    $0x80496c8,%edi'

void raw__chunk__compile_x86__mov_const_to_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, u32 constant, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0xB8); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0xB9); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0xBA); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0xBB); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0xBC); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0xBD); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0xBE); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0xBF); break;
  }
  index = *next_index;
  raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, constant);
}

// mov reg to reg

//80483ee:	89 c0                	mov    %eax,%eax
//80483ec:	89 c1                	mov    %eax,%ecx
//80483f0:	89 c2                	mov    %eax,%edx
//80483f2:	89 c3                	mov    %eax,%ebx
//80483f4:	89 c4                	mov    %eax,%esp
//80483f6:	89 c5                	mov    %eax,%ebp
//80483f8:	89 c6                	mov    %eax,%esi
//80483fa:	89 c7                	mov    %eax,%edi

void raw__chunk__compile_x86__mov_eax_to_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xC089); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xC189); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xC289); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xC389); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xC489); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xC589); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xC689); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xC789); break;
  }
}

//80483dc:	89 c9                	mov    %ecx,%ecx 
//80483de:	89 c8                	mov    %ecx,%eax
//80483e0:	89 ca                	mov    %ecx,%edx
//80483e2:	89 cb                	mov    %ecx,%ebx
//80483e4:	89 cc                	mov    %ecx,%esp
//80483e6:	89 cd                	mov    %ecx,%ebp
//80483e8:	89 ce                	mov    %ecx,%esi
//80483ea:	89 cf                	mov    %ecx,%edi

void raw__chunk__compile_x86__mov_ecx_to_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xC889); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xC989); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xCA89); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xCB89); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xCC89); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xCD89); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xCE89); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xCF89); break;
  }
}


//80483fe:	89 d0                	mov    %edx,%eax
//80483fc:	89 d1                	mov    %edx,%ecx
//8048400:	89 d2                	mov    %edx,%edx
//8048402:	89 d3                	mov    %edx,%ebx
//8048404:	89 d4                	mov    %edx,%esp
//8048406:	89 d5                	mov    %edx,%ebp
//8048408:	89 d6                	mov    %edx,%esi
//804840a:	89 d7                	mov    %edx,%edi

void raw__chunk__compile_x86__mov_edx_to_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xD089); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xD189); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xD289); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xD389); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xD489); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xD589); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xD689); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xD789); break;
  }
}


//804840e:	89 d8                	mov    %ebx,%eax
//804840c:	89 d9                	mov    %ebx,%ecx
//8048410:	89 da                	mov    %ebx,%edx
//8048412:	89 db                	mov    %ebx,%ebx
//8048414:	89 dc                	mov    %ebx,%esp
//8048416:	89 dd                	mov    %ebx,%ebp
//8048418:	89 de                	mov    %ebx,%esi
//804841a:	89 df                	mov    %ebx,%edi

void raw__chunk__compile_x86__mov_ebx_to_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xD889); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xD989); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xDA89); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xDB89); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xDC89); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xDD89); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xDE89); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xDF89); break;
  }
}


//804841e:	89 e0                	mov    %esp,%eax
//804841c:	89 e1                	mov    %esp,%ecx
//8048420:	89 e2                	mov    %esp,%edx
//8048422:	89 e3                	mov    %esp,%ebx
//8048424:	89 e4                	mov    %esp,%esp
//8048426:	89 e5                	mov    %esp,%ebp
//8048428:	89 e6                	mov    %esp,%esi
//804842a:	89 e7                	mov    %esp,%edi

void raw__chunk__compile_x86__mov_esp_to_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xE089); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xE189); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xE289); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xE389); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xE489); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xE589); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xE689); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xE789); break;
  }
}


//804842e:	89 e8                	mov    %ebp,%eax
//804842c:	89 e9                	mov    %ebp,%ecx
//8048430:	89 ea                	mov    %ebp,%edx
//8048432:	89 eb                	mov    %ebp,%ebx
//8048434:	89 ec                	mov    %ebp,%esp
//8048436:	89 ed                	mov    %ebp,%ebp
//8048438:	89 ee                	mov    %ebp,%esi
//804843a:	89 ef                	mov    %ebp,%edi

void raw__chunk__compile_x86__mov_ebp_to_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xE889); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xE989); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xEA89); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xEB89); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xEC89); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xED89); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xEE89); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xEF89); break;
  }
}


//804843e:	89 f0                	mov    %esi,%eax
//804843c:	89 f1                	mov    %esi,%ecx
//8048440:	89 f2                	mov    %esi,%edx
//8048442:	89 f3                	mov    %esi,%ebx
//8048444:	89 f4                	mov    %esi,%esp
//8048446:	89 f5                	mov    %esi,%ebp
//8048448:	89 f6                	mov    %esi,%esi
//804844a:	89 f7                	mov    %esi,%edi

void raw__chunk__compile_x86__mov_esi_to_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xF089); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xF189); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xF289); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xF389); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xF489); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xF589); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xF689); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xF789); break;
  }
}


//804844e:	89 f8                	mov    %edi,%eax
//804844c:	89 f9                	mov    %edi,%ecx
//8048450:	89 fa                	mov    %edi,%edx
//8048452:	89 fb                	mov    %edi,%ebx
//8048454:	89 fc                	mov    %edi,%esp
//8048456:	89 fd                	mov    %edi,%ebp
//8048458:	89 fe                	mov    %edi,%esi
//804845a:	89 ff                	mov    %edi,%edi

void raw__chunk__compile_x86__mov_edi_to_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xF889); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xF989); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xFA89); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xFB89); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xFC89); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xFD89); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xFE89); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xFF89); break;
  }
}


void raw__chunk__compile_x86__mov_reg_to_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t src_reg, x86_reg_t dest_reg) {
  switch(src_reg) {
  case x86_reg__eax: raw__chunk__compile_x86__mov_eax_to_reg(this, index, cause, next_index, dest_reg); break;
  case x86_reg__ecx: raw__chunk__compile_x86__mov_ecx_to_reg(this, index, cause, next_index, dest_reg); break;
  case x86_reg__edx: raw__chunk__compile_x86__mov_edx_to_reg(this, index, cause, next_index, dest_reg); break;
  case x86_reg__ebx: raw__chunk__compile_x86__mov_ebx_to_reg(this, index, cause, next_index, dest_reg); break;
  case x86_reg__esp: raw__chunk__compile_x86__mov_esp_to_reg(this, index, cause, next_index, dest_reg); break;
  case x86_reg__ebp: raw__chunk__compile_x86__mov_ebp_to_reg(this, index, cause, next_index, dest_reg); break;
  case x86_reg__esi: raw__chunk__compile_x86__mov_esi_to_reg(this, index, cause, next_index, dest_reg); break;
  case x86_reg__edi: raw__chunk__compile_x86__mov_edi_to_reg(this, index, cause, next_index, dest_reg); break;
  }
}

//80483b4:	89 40 0c             	mov    %eax,0xc(%eax)
//80483b7:	89 48 0c             	mov    %ecx,0xc(%eax)
//80483ba:	89 50 0c             	mov    %edx,0xc(%eax)
//80483bd:	89 58 0c             	mov    %ebx,0xc(%eax)
//80483c0:	89 60 0c             	mov    %esp,0xc(%eax)
//80483c3:	89 68 0c             	mov    %ebp,0xc(%eax)
//80483c6:	89 70 0c             	mov    %esi,0xc(%eax)
//80483c9:	89 78 0c             	mov    %edi,0xc(%eax)

void raw__chunk__compile_x86__mov_reg_to_eax_offset(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4089); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4889); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5089); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5889); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6089); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6889); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7089); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7889); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//80483cc:	89 41 0c             	mov    %eax,0xc(%ecx)
//80483cf:	89 49 0c             	mov    %ecx,0xc(%ecx)
//80483d2:	89 51 0c             	mov    %edx,0xc(%ecx)
//80483d5:	89 59 0c             	mov    %ebx,0xc(%ecx)
//80483d8:	89 61 0c             	mov    %esp,0xc(%ecx)
//80483db:	89 69 0c             	mov    %ebp,0xc(%ecx)
//80483de:	89 71 0c             	mov    %esi,0xc(%ecx)
//80483e1:	89 79 0c             	mov    %edi,0xc(%ecx)

void raw__chunk__compile_x86__mov_reg_to_ecx_offset(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4189); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4989); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5189); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5989); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6189); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6989); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7189); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7989); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//80483e4:	89 42 0c             	mov    %eax,0xc(%edx)
//80483e7:	89 4a 0c             	mov    %ecx,0xc(%edx)
//80483ea:	89 52 0c             	mov    %edx,0xc(%edx)
//80483ed:	89 5a 0c             	mov    %ebx,0xc(%edx)
//80483f0:	89 62 0c             	mov    %esp,0xc(%edx)
//80483f3:	89 6a 0c             	mov    %ebp,0xc(%edx)
//80483f6:	89 72 0c             	mov    %esi,0xc(%edx)
//80483f9:	89 7a 0c             	mov    %edi,0xc(%edx)

void raw__chunk__compile_x86__mov_reg_to_edx_offset(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4289); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4A89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5289); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5A89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6289); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6A89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7289); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7A89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//80483fc:	89 43 0c             	mov    %eax,0xc(%ebx)
//80483ff:	89 4b 0c             	mov    %ecx,0xc(%ebx)
//8048402:	89 53 0c             	mov    %edx,0xc(%ebx)
//8048405:	89 5b 0c             	mov    %ebx,0xc(%ebx)
//8048408:	89 63 0c             	mov    %esp,0xc(%ebx)
//804840b:	89 6b 0c             	mov    %ebp,0xc(%ebx)
//804840e:	89 73 0c             	mov    %esi,0xc(%ebx)
//8048411:	89 7b 0c             	mov    %edi,0xc(%ebx)

void raw__chunk__compile_x86__mov_reg_to_ebx_offset(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4389); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4B89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5389); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5B89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6389); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6B89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7389); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7B89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//8048414:	89 44 24 0c          	mov    %eax,0xc(%esp)
//8048418:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
//804841c:	89 54 24 0c          	mov    %edx,0xc(%esp)
//8048420:	89 5c 24 0c          	mov    %ebx,0xc(%esp)
//8048424:	89 64 24 0c          	mov    %esp,0xc(%esp)
//8048428:	89 6c 24 0c          	mov    %ebp,0xc(%esp)
//804842c:	89 74 24 0c          	mov    %esi,0xc(%esp)
//8048430:	89 7c 24 0c          	mov    %edi,0xc(%esp)

void raw__chunk__compile_x86__mov_reg_to_esp_offset(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4489); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4C89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5489); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5C89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6489); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6C89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7489); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7C89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//8048434:	89 45 0c             	mov    %eax,0xc(%ebp)
//8048437:	89 4d 0c             	mov    %ecx,0xc(%ebp)
//804843a:	89 55 0c             	mov    %edx,0xc(%ebp)
//804843d:	89 5d 0c             	mov    %ebx,0xc(%ebp)
//8048440:	89 65 0c             	mov    %esp,0xc(%ebp)
//8048443:	89 6d 0c             	mov    %ebp,0xc(%ebp)
//8048446:	89 75 0c             	mov    %esi,0xc(%ebp)
//8048449:	89 7d 0c             	mov    %edi,0xc(%ebp)

void raw__chunk__compile_x86__mov_reg_to_ebp_offset(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4589); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4D89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5589); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5D89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6589); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6D89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7589); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7D89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//804844c:	89 46 0c             	mov    %eax,0xc(%esi)
//804844f:	89 4e 0c             	mov    %ecx,0xc(%esi)
//8048452:	89 56 0c             	mov    %edx,0xc(%esi)
//8048455:	89 5e 0c             	mov    %ebx,0xc(%esi)
//8048458:	89 66 0c             	mov    %esp,0xc(%esi)
//804845b:	89 6e 0c             	mov    %ebp,0xc(%esi)
//804845e:	89 76 0c             	mov    %esi,0xc(%esi)
//8048461:	89 7e 0c             	mov    %edi,0xc(%esi)

void raw__chunk__compile_x86__mov_reg_to_esi_offset(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4689); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4E89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5689); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5E89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6689); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6E89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7689); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7E89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//8048464:	89 47 0c             	mov    %eax,0xc(%edi)
//8048467:	89 4f 0c             	mov    %ecx,0xc(%edi)
//804846a:	89 57 0c             	mov    %edx,0xc(%edi)
//804846d:	89 5f 0c             	mov    %ebx,0xc(%edi)
//8048470:	89 67 0c             	mov    %esp,0xc(%edi)
//8048473:	89 6f 0c             	mov    %ebp,0xc(%edi)
//8048476:	89 77 0c             	mov    %esi,0xc(%edi)
//8048479:	89 7f 0c             	mov    %edi,0xc(%edi)

void raw__chunk__compile_x86__mov_reg_to_edi_offset(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4789); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4F89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5789); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5F89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6789); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6F89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7789); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7F89); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}

void raw__chunk__compile_x86__mov_reg_to_reg_offset(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t src_reg, x86_reg_t dest_reg, u8 offset) {
  switch(dest_reg) {
  case x86_reg__eax: raw__chunk__compile_x86__mov_reg_to_eax_offset(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__mov_reg_to_ecx_offset(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__mov_reg_to_edx_offset(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__mov_reg_to_ebx_offset(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__mov_reg_to_esp_offset(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__mov_reg_to_ebp_offset(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__mov_reg_to_esi_offset(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__mov_reg_to_edi_offset(this, index, cause, next_index, src_reg, offset); break;
  }
}

//804847c:	8b 40 0d             	mov    0xd(%eax),%eax
//804847f:	8b 41 0d             	mov    0xd(%ecx),%eax
//8048482:	8b 42 0d             	mov    0xd(%edx),%eax
//8048485:	8b 43 0d             	mov    0xd(%ebx),%eax
//8048488:	8b 44 24 0d          	mov    0xd(%esp),%eax
//804848c:	8b 45 0d             	mov    0xd(%ebp),%eax
//804848f:	8b 46 0d             	mov    0xd(%esi),%eax
//8048492:	8b 47 0d             	mov    0xd(%edi),%eax

void raw__chunk__compile_x86__mov_reg_offset_to_eax(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x408B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x418B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x428B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x438B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x448B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x458B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x468B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x478B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//8048495:	8b 48 0d             	mov    0xd(%eax),%ecx
//8048498:	8b 49 0d             	mov    0xd(%ecx),%ecx
//804849b:	8b 4a 0d             	mov    0xd(%edx),%ecx
//804849e:	8b 4b 0d             	mov    0xd(%ebx),%ecx
//80484a1:	8b 4c 24 0d          	mov    0xd(%esp),%ecx
//80484a5:	8b 4d 0d             	mov    0xd(%ebp),%ecx
//80484a8:	8b 4e 0d             	mov    0xd(%esi),%ecx
//80484ab:	8b 4f 0d             	mov    0xd(%edi),%ecx

void raw__chunk__compile_x86__mov_reg_offset_to_ecx(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x488B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x498B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4A8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4B8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4C8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4D8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4E8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x4F8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//80484ae:	8b 50 0d             	mov    0xd(%eax),%edx
//80484b1:	8b 51 0d             	mov    0xd(%ecx),%edx
//80484b4:	8b 52 0d             	mov    0xd(%edx),%edx
//80484b7:	8b 53 0d             	mov    0xd(%ebx),%edx
//80484ba:	8b 54 24 0d          	mov    0xd(%esp),%edx
//80484be:	8b 55 0d             	mov    0xd(%ebp),%edx
//80484c1:	8b 56 0d             	mov    0xd(%esi),%edx
//80484c4:	8b 57 0d             	mov    0xd(%edi),%edx

void raw__chunk__compile_x86__mov_reg_offset_to_edx(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x508B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x518B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x528B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x538B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x548B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x558B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x568B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x578B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//80484c7:	8b 58 0d             	mov    0xd(%eax),%ebx
//80484ca:	8b 59 0d             	mov    0xd(%ecx),%ebx
//80484cd:	8b 5a 0d             	mov    0xd(%edx),%ebx
//80484d0:	8b 5b 0d             	mov    0xd(%ebx),%ebx
//80484d3:	8b 5c 24 0d          	mov    0xd(%esp),%ebx
//80484d7:	8b 5d 0d             	mov    0xd(%ebp),%ebx
//80484da:	8b 5e 0d             	mov    0xd(%esi),%ebx
//80484dd:	8b 5f 0d             	mov    0xd(%edi),%ebx

void raw__chunk__compile_x86__mov_reg_offset_to_ebx(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x588B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x598B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5A8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5B8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5C8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5D8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5E8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x5F8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//80484e0:	8b 60 0d             	mov    0xd(%eax),%esp
//80484e3:	8b 61 0d             	mov    0xd(%ecx),%esp
//80484e6:	8b 62 0d             	mov    0xd(%edx),%esp
//80484e9:	8b 63 0d             	mov    0xd(%ebx),%esp
//80484ec:	8b 64 24 0d          	mov    0xd(%esp),%esp
//80484f0:	8b 65 0d             	mov    0xd(%ebp),%esp
//80484f3:	8b 66 0d             	mov    0xd(%esi),%esp
//80484f6:	8b 67 0d             	mov    0xd(%edi),%esp

void raw__chunk__compile_x86__mov_reg_offset_to_esp(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x608B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x618B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x628B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x638B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x648B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x658B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x668B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x678B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//80484f9:	8b 68 0d             	mov    0xd(%eax),%ebp
//80484fc:	8b 69 0d             	mov    0xd(%ecx),%ebp
//80484ff:	8b 6a 0d             	mov    0xd(%edx),%ebp
//8048502:	8b 6b 0d             	mov    0xd(%ebx),%ebp
//8048505:	8b 6c 24 0d          	mov    0xd(%esp),%ebp
//8048509:	8b 6d 0d             	mov    0xd(%ebp),%ebp
//804850c:	8b 6e 0d             	mov    0xd(%esi),%ebp
//804850f:	8b 6f 0d             	mov    0xd(%edi),%ebp

void raw__chunk__compile_x86__mov_reg_offset_to_ebp(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x688B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x698B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6A8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6B8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6C8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6D8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6E8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x6F8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//8048512:	8b 70 0d             	mov    0xd(%eax),%esi
//8048515:	8b 71 0d             	mov    0xd(%ecx),%esi
//8048518:	8b 72 0d             	mov    0xd(%edx),%esi
//804851b:	8b 73 0d             	mov    0xd(%ebx),%esi
//804851e:	8b 74 24 0d          	mov    0xd(%esp),%esi
//8048522:	8b 75 0d             	mov    0xd(%ebp),%esi
//8048525:	8b 76 0d             	mov    0xd(%esi),%esi
//8048528:	8b 77 0d             	mov    0xd(%edi),%esi

void raw__chunk__compile_x86__mov_reg_offset_to_esi(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x708B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x718B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x728B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x738B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x748B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x758B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x768B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x778B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}


//804852b:	8b 78 0d             	mov    0xd(%eax),%edi
//804852e:	8b 79 0d             	mov    0xd(%ecx),%edi
//8048531:	8b 7a 0d             	mov    0xd(%edx),%edi
//8048534:	8b 7b 0d             	mov    0xd(%ebx),%edi
//8048537:	8b 7c 24 0d          	mov    0xd(%esp),%edi
//804853b:	8b 7d 0d             	mov    0xd(%ebp),%edi
//804853e:	8b 7e 0d             	mov    0xd(%esi),%edi
//8048541:	8b 7f 0d             	mov    0xd(%edi),%edi

void raw__chunk__compile_x86__mov_reg_offset_to_edi(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t reg, u8 offset) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x788B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x798B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7A8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7B8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7C8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7D8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7E8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x7F8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, offset); break;
  }
}

void raw__chunk__compile_x86__mov_reg_offset_to_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, x86_reg_t src_reg, u8 offset, x86_reg_t dest_reg) {
  switch(dest_reg) {
  case x86_reg__eax: raw__chunk__compile_x86__mov_reg_offset_to_eax(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__ecx: raw__chunk__compile_x86__mov_reg_offset_to_ecx(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__edx: raw__chunk__compile_x86__mov_reg_offset_to_edx(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__ebx: raw__chunk__compile_x86__mov_reg_offset_to_ebx(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__esp: raw__chunk__compile_x86__mov_reg_offset_to_esp(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__ebp: raw__chunk__compile_x86__mov_reg_offset_to_ebp(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__esi: raw__chunk__compile_x86__mov_reg_offset_to_esi(this, index, cause, next_index, src_reg, offset); break;
  case x86_reg__edi: raw__chunk__compile_x86__mov_reg_offset_to_edi(this, index, cause, next_index, src_reg, offset); break;
  }
}


//8048674:	c7 00 25 88 04 08    	movl   $0x8048825,(%eax)
//804867a:	c7 01 25 88 04 08    	movl   $0x8048825,(%ecx)
//8048680:	c7 02 25 88 04 08    	movl   $0x8048825,(%edx)
//8048686:	c7 03 25 88 04 08    	movl   $0x8048825,(%ebx)
//804868c:	c7 04 24 25 88 04 08 	movl   $0x8048825,(%esp)
//8048693:	c7 45 00 25 88 04 08 	movl   $0x8048825,0x0(%ebp)
//804869a:	c7 06 25 88 04 08    	movl   $0x8048825,(%esi)
//80486a0:	c7 07 25 88 04 08    	movl   $0x8048825,(%edi)

void raw__chunk__compile_x86__mov_const_to_reg_addr(f2ptr this, u64 index, f2ptr cause, u64* next_index, u32 constant, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x00C7); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, constant); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x01C7); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, constant); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x02C7); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, constant); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x03C7); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, constant); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x04C7); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x24); index = *next_index; raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, constant); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x45C7); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, 0x00); index = *next_index; raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, constant); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x06C7); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, constant); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x07C7); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, constant); break;
  }
}

//     80483ec:	c7 44 24 08 ef cd ab 89	movl   $0x89abcdef,0x8(%esp)
//     80483f4:	c7 44 24 0c 67 45 23 01	movl   $0x01234567,0xc(%esp)
//
// warning: not verified for other registers...

void raw__chunk__compile_x86__mov_const_to_reg_offset(f2ptr this, u64 index, f2ptr cause, u64* next_index, u32 constant, x86_reg_t reg, s8 offset) {
  switch(reg) {
  case x86_reg__eax:
    raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x40C7); index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, 0x24);   index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, offset); index = *next_index;
    raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, constant);
    break;
  case x86_reg__ecx:
    raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x41C7); index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, 0x24);   index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, offset); index = *next_index;
    raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, constant);
    break;
  case x86_reg__edx:
    raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x42C7); index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, 0x24);   index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, offset); index = *next_index;
    raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, constant);
    break;
  case x86_reg__ebx:
    raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x43C7); index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, 0x24);   index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, offset); index = *next_index;
    raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, constant);
    break;
  case x86_reg__esp:
    raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x44C7); index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, 0x24);   index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, offset); index = *next_index;
    raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, constant);
    break;
  case x86_reg__ebp:
    raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x45C7); index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, 0x24);   index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, offset); index = *next_index;
    raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, constant);
    break;
  case x86_reg__esi:
    raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x46C7); index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, 0x24);   index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, offset); index = *next_index;
    raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, constant);
    break;
  case x86_reg__edi:
    raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x47C7); index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, 0x24);   index = *next_index;
    raw__chunk__compile_x86__value_bit8( this, index, cause, next_index, offset); index = *next_index;
    raw__chunk__compile_x86__value_bit32(this, index, cause, next_index, constant);
    break;
  }
}



//8048544:	a1 c8 96 04 08       	mov    0x80496c8,%eax
//8048549:	8b 0d c8 96 04 08    	mov    0x80496c8,%ecx
//804854f:	8b 15 c8 96 04 08    	mov    0x80496c8,%edx
//8048555:	8b 1d c8 96 04 08    	mov    0x80496c8,%ebx
//804855b:	8b 25 c8 96 04 08    	mov    0x80496c8,%esp
//8048561:	8b 2d c8 96 04 08    	mov    0x80496c8,%ebp
//8048567:	8b 35 c8 96 04 08    	mov    0x80496c8,%esi
//804856d:	8b 3d c8 96 04 08    	mov    0x80496c8,%edi

void raw__chunk__compile_x86__mov_addr_to_reg(f2ptr this, u64 index, f2ptr cause, u64* next_index, u32 addr, x86_reg_t reg) {
  switch(reg) {
  case x86_reg__eax: raw__chunk__compile_x86__value_bit8( this, index, cause, next_index,   0xA1); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, addr); break;
  case x86_reg__ecx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x0D8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, addr); break;
  case x86_reg__edx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x158B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, addr); break;
  case x86_reg__ebx: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x1D8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, addr); break;
  case x86_reg__esp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x258B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, addr); break;
  case x86_reg__ebp: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x2D8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, addr); break;
  case x86_reg__esi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x358B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, addr); break;
  case x86_reg__edi: raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x3D8B); index = *next_index; raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, addr); break;
  }
}

//[defunk call_raw_c_funktion-x86_compile [chunk index cfunk_ptr :rest args]
//  [let [[args-len  [length args]]
//	  [arg-index 0]]
//    [set             index [x86_sub_bit8_from_esp-x86_compile chunk index [* 4 args-len]]]
//    [mapc [funk [arg]
//		  [set index [x86_mov_arg_to_arg-x86_compile    chunk index arg  `eax]]
//		  [set index [x86_mov_arg_to_arg-x86_compile    chunk index `eax [x86_arg-rel_to_reg `esp [* arg-index 4]]]]
//		  [set arg-index [+ arg-index 1]]]
//	    args]
//    [let [[after_call_index [x86_call_relative-x86_compile    nil   index nil]]]
//      [set           index [x86_call_relative-x86_compile     chunk index [if chunk [- cfunk_ptr [+ [chunk-bytes chunk] after_call_index]] nil]]]]
//    [set             index [x86_sub_bit8_from_esp-x86_compile chunk index [- [* 4 args-len]]]]
//    index]]


//execute_bytecodes is a function of type bytecode_jump_t.  it executes three different types of bytecodes (with 0, 1, and 2 constant f2ptr arguments).
//this is unoptimized code (gcc used without -O flag).  optimized code is not *that* much shorter than this code, so for sake of understandability, we use unoptimized machine code as a template for our compiler (this process could probably be automated with linux string processing tools...).
//
//080483c8 <execute_bytecodes>:
//
// **

// **
//
// prepare stack with one f2ptr argument (the fiber pointer)
//
//   80483c8:	55                   	push   %ebp
//   80483c9:	89 e5                	mov    %esp,%ebp
//   80483cb:	83 ec 20             	sub    $0x20,%esp
//   80483ce:	8b 45 08             	mov    0x8(%ebp),%eax
//   80483d1:	89 45 f8             	mov    %eax,0xfffffff8(%ebp)
//   80483d4:	8b 45 0c             	mov    0xc(%ebp),%eax
//   80483d7:	89 45 fc             	mov    %eax,0xfffffffc(%ebp)
//
// **

// **
//
// cleanup and return from our execute_bytecodes function
//
//   8048440:	c9                   	leave  
//   8048441:	c3                   	ret    
//
// **
// **

// **
//
// prepare to call bytecode__fiber function
//
//   mov fiber argument to call stack
//
//     80483da:	8b 45 f8             	mov    0xfffffff8(%ebp),%eax
//     80483dd:	8b 55 fc             	mov    0xfffffffc(%ebp),%edx
//     80483e0:	89 04 24             	mov    %eax,(%esp)
//     80483e3:	89 54 24 04          	mov    %edx,0x4(%esp)
//
// call bytecode__fiber
//
//   80483e7:	e8 58 ff ff ff       	call   8048344 <bytecode__fiber>
//
// **

// **
//
// prepare to call bytecode__fiber_arg0
//
//   mov arg0 constant to call stack
//
//     80483ec:	c7 44 24 08 ef cd ab 89	movl   $0x89abcdef,0x8(%esp)
//     80483f4:	c7 44 24 0c 67 45 23 01	movl   $0x01234567,0xc(%esp)
//
//   mov fiber argument to call stack
//
//     80483fc:	8b 45 f8             	mov    0xfffffff8(%ebp),%eax
//     80483ff:	8b 55 fc             	mov    0xfffffffc(%ebp),%edx
//     8048402:	89 04 24             	mov    %eax,(%esp)
//     8048405:	89 54 24 04          	mov    %edx,0x4(%esp)
//
// call bytecode__fiber_arg0
//
//   8048409:	e8 50 ff ff ff       	call   804835e <bytecode__fiber_arg0>
//
// **

// **
//
// prepare to call bytecode__fiber_arg0_arg1
//
//   mov arg1 constant to call stack
//
//     804840e:	c7 44 24 10 cd ab 89 67	movl   $0x6789abcd,0x10(%esp)
//     8048416:	c7 44 24 14 45 23 01 ef	movl   $0xef012345,0x14(%esp)
//
//   mov arg0 constant to call stack
//
//     804841e:	c7 44 24 08 de bc 9a 78	movl   $0x789abcde,0x8(%esp)
//     8048426:	c7 44 24 0c 56 34 12 f0	movl   $0xf0123456,0xc(%esp)
//
//   mov fiber argument to call stack
//
//     804842e:	8b 45 f8             	mov    0xfffffff8(%ebp),%eax
//     8048431:	8b 55 fc             	mov    0xfffffffc(%ebp),%edx
//     8048434:	89 04 24             	mov    %eax,(%esp)
//     8048437:	89 54 24 04          	mov    %edx,0x4(%esp)
//
// call bytecode__fiber_arg0_arg1
//
//   804843b:	e8 4a ff ff ff       	call   804838a <bytecode__fiber_arg0_arg1>
//
// **

//this is a hand optimized version of the above code
//
//080483c8 <execute_bytecodes>:
//
// **

// **
//
// prepare to call bytecode__fiber function
//
// call bytecode__fiber
//
//   80483e7:	e8 58 ff ff ff       	call   8048344 <bytecode__fiber>
//
// **

void raw__chunk__compile_x86__jump_bytecode(f2ptr this, u64 index, f2ptr cause, u64* next_index, bytecode_jump_t jump_bytecode) {
  
  raw__chunk__compile_x86__mov_const_to_reg(this, index, cause, next_index, (u32)to_ptr(jump_bytecode), x86_reg__eax); index = *next_index;
  raw__chunk__compile_x86__call_eax(        this, index, cause, next_index);
  //raw__chunk__compile_x86__call_absolute(this, index, next_index, (u32)jump_bytecode);
}

// **
//
// prepare to call bytecode__fiber_arg0
//
//   mov arg0 constant to call stack
//
//     80483ec:	c7 44 24 08 ef cd ab 89	movl   $0x89abcdef,0x8(%esp)
//     80483f4:	c7 44 24 0c 67 45 23 01	movl   $0x01234567,0xc(%esp)
//
// call bytecode__fiber_arg0
//
//   8048409:	e8 50 ff ff ff       	call   804835e <bytecode__fiber_arg0>
//
// **

void raw__chunk__compile_x86__jump_bytecode__f2ptr(f2ptr this, u64 index, f2ptr cause, u64* next_index,
						  bytecode_jump__f2ptr_t jump_bytecode,
						  f2ptr arg0) {
  raw__chunk__compile_x86__mov_const_to_reg_offset(this, index, cause, next_index, (u32)(((u64)arg0) & 0xffffffff), x86_reg__esp, 0x08); index = *next_index;
  raw__chunk__compile_x86__mov_const_to_reg_offset(this, index, cause, next_index, (u32)(((u64)arg0) >> 32),        x86_reg__esp, 0x0C); index = *next_index;
  
  raw__chunk__compile_x86__mov_const_to_reg(this, index, cause, next_index, (u32)to_ptr(jump_bytecode), x86_reg__eax); index = *next_index;
  raw__chunk__compile_x86__call_eax(        this, index, cause, next_index);
  //raw__chunk__compile_x86__call_absolute(this, index, next_index, (u32)jump_bytecode);
}

// **
//
// prepare to call bytecode__fiber_arg0_arg1
//
//   mov arg1 constant to call stack
//
//     804840e:	c7 44 24 10 cd ab 89 67	movl   $0x6789abcd,0x10(%esp)
//     8048416:	c7 44 24 14 45 23 01 ef	movl   $0xef012345,0x14(%esp)
//
//   mov arg0 constant to call stack
//
//     804841e:	c7 44 24 08 de bc 9a 78	movl   $0x789abcde,0x8(%esp)
//     8048426:	c7 44 24 0c 56 34 12 f0	movl   $0xf0123456,0xc(%esp)
//
// call bytecode__fiber_arg0_arg1
//
//   804843b:	e8 4a ff ff ff       	call   804838a <bytecode__fiber_arg0_arg1>
//
// **

void raw__chunk__compile_x86__jump_bytecode__f2ptr_f2ptr(f2ptr this, u64 index, f2ptr cause, u64* next_index, bytecode_jump__f2ptr_f2ptr_t jump_bytecode, f2ptr arg0, f2ptr arg1) {
  raw__chunk__compile_x86__mov_const_to_reg_offset(this, index, cause, next_index, (u32)(((u64)arg1) & 0xffffffff), x86_reg__esp, 0x10); index = *next_index;
  raw__chunk__compile_x86__mov_const_to_reg_offset(this, index, cause, next_index, (u32)(((u64)arg1) >> 32),        x86_reg__esp, 0x14); index = *next_index;
  raw__chunk__compile_x86__mov_const_to_reg_offset(this, index, cause, next_index, (u32)(((u64)arg0) & 0xffffffff), x86_reg__esp, 0x08); index = *next_index;
  raw__chunk__compile_x86__mov_const_to_reg_offset(this, index, cause, next_index, (u32)(((u64)arg0) >> 32),        x86_reg__esp, 0x0C); index = *next_index;
  
  raw__chunk__compile_x86__mov_const_to_reg(this, index, cause, next_index, (u32)to_ptr(jump_bytecode), x86_reg__eax); index = *next_index;
  raw__chunk__compile_x86__call_eax(        this, index, cause, next_index);
  //raw__chunk__compile_x86__call_absolute(          this, index, next_index, (u32)jump_bytecode);
}


void raw__chunk__compile_x86__bytecode(f2ptr this, u64 index, f2ptr cause, u64* next_index, f2ptr bytecode) {
  debug__assert(raw__bytecode__is_type(cause, bytecode), nil, "raw__chunk__compile_x86__bytecode error: bytecode type assertion failed.");
  f2ptr command = f2bytecode__command(bytecode, cause);
  if      (command == __funk2.bytecode.bytecode__push__symbol)               {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index,  f2__compile__bytecode__push(cause, f2bytecode__arg0(bytecode, cause)));}
  else if (command == __funk2.bytecode.bytecode__pop__symbol)                {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index,  f2__compile__bytecode__pop( cause, f2bytecode__arg0(bytecode, cause)));}
  else if (command == __funk2.bytecode.bytecode__copy__symbol)               {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index,  f2__compile__bytecode__copy(cause, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause)));}
  else if (command == __funk2.bytecode.bytecode__swap__symbol)               {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index,  f2__compile__bytecode__swap(cause, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause)));}
  else if (command == __funk2.bytecode.bytecode__cons__symbol)               {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index, &f2__fiber__bytecode__cons);}
  else if (command == __funk2.bytecode.bytecode__car__set__symbol)           {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index, &f2__fiber__bytecode__car__set);}
  else if (command == __funk2.bytecode.bytecode__funk__symbol)               {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index, &f2__fiber__bytecode__funk);}
  else if (command == __funk2.bytecode.bytecode__jump_funk__symbol)          {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index, &f2__fiber__bytecode__jump_funk);}
  else if (command == __funk2.bytecode.bytecode__set__symbol)                {raw__chunk__compile_x86__jump_bytecode__f2ptr(      this, index, cause, next_index,  f2__compile__bytecode__set(cause, f2bytecode__arg0(bytecode, cause)), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__cdr__set__symbol)           {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index, &f2__fiber__bytecode__cdr__set);}
  else if (command == __funk2.bytecode.bytecode__lookup__symbol)             {raw__chunk__compile_x86__jump_bytecode__f2ptr_f2ptr(this, index, cause, next_index, &f2__fiber__bytecode__lookup, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__define__symbol)             {raw__chunk__compile_x86__jump_bytecode__f2ptr_f2ptr(this, index, cause, next_index, &f2__fiber__bytecode__define, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__else_jump__symbol)          {raw__chunk__compile_x86__jump_bytecode__f2ptr(      this, index, cause, next_index, &f2__fiber__bytecode__else_jump, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__car__symbol)                {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index, &f2__fiber__bytecode__car);}
  else if (command == __funk2.bytecode.bytecode__cdr__symbol)                {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index, &f2__fiber__bytecode__cdr);}
  else if (command == __funk2.bytecode.bytecode__type_var__mutate__symbol)   {raw__chunk__compile_x86__jump_bytecode__f2ptr_f2ptr(this, index, cause, next_index, &f2__fiber__bytecode__type_var__mutate, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__globalize_type_var__symbol) {raw__chunk__compile_x86__jump_bytecode__f2ptr_f2ptr(this, index, cause, next_index, &f2__fiber__bytecode__globalize_type_var, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__jump__symbol)               {raw__chunk__compile_x86__jump_bytecode__f2ptr(      this, index, cause, next_index, &f2__fiber__bytecode__jump, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__nop__symbol)                {}
  else if (command == __funk2.bytecode.bytecode__debug__symbol)              {raw__chunk__compile_x86__jump_bytecode__f2ptr(      this, index, cause, next_index, &f2__fiber__bytecode__debug, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__tracer__symbol)             {raw__chunk__compile_x86__jump_bytecode__f2ptr_f2ptr(this, index, cause, next_index, &f2__fiber__bytecode__tracer, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__compile__symbol)            {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index,  f2__compile__bytecode__compile(f2bytecode__arg0(bytecode, cause)));}
  else if (command == __funk2.bytecode.bytecode__yield__symbol)              {}
  else if (command == __funk2.bytecode.bytecode__newenv__symbol)             {raw__chunk__compile_x86__jump_bytecode(             this, index, cause, next_index, &f2__fiber__bytecode__newenv);}
  else if (command == __funk2.bytecode.bytecode__machine_code__symbol)       {raw__chunk__compile_x86__jump_bytecode__f2ptr(      this, index, cause, next_index, &f2__fiber__bytecode__machine_code, f2bytecode__arg0(bytecode, cause));}
  else {f2__print(nil, command); fflush(stdout); error(nil, "raw__chunk__compile_x86__bytecode error: unrecognized bytecode command.");}
}

//  b5:	85 c0                	test   %eax,%eax
//  b7:	74 0e                	je     c7 <return_if_not_eq+0x36>

void raw__chunk__compile_x86__return_if_eax_is_true(f2ptr this, u64 index, f2ptr cause, u64* next_index, f2ptr expected_pc) {
  raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xC085); index = *next_index;
  raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0x0274); index = *next_index;
  raw__chunk__compile_x86__value_bit16(this, index, cause, next_index, 0xC3C9); // leave, ret
}

void raw__chunk__compile_x86__bytecodes(f2ptr this, u64 index, f2ptr cause, u64* next_index, f2ptr bytecodes) {
  f2ptr iter = bytecodes;
  while (iter) {
    f2ptr bytecode = f2cons__car(iter, cause);
    raw__chunk__compile_x86__bytecode(             this, index, cause, next_index, bytecode); index = *next_index;
    raw__chunk__compile_x86__return_if_eax_is_true(this, index, cause, next_index, iter);     index = *next_index;
    iter = f2cons__cdr(iter, cause);
  }
}

// **
//
// prepare stack with one f2ptr argument (the fiber pointer)
//
//   80483c8:	55                   	push   %ebp
//   80483c9:	89 e5                	mov    %esp,%ebp
//   80483cb:	83 ec 20             	sub    $0x20,%esp
//   80483ce:	8b 45 08             	mov    0x8(%ebp),%eax
//   80483d1:	89 45 f8             	mov    %eax,0xfffffff8(%ebp)
//   80483d4:	8b 45 0c             	mov    0xc(%ebp),%eax
//   80483d7:	89 45 fc             	mov    %eax,0xfffffffc(%ebp)
//
//   mov fiber argument to call stack
//
//     80483da:	8b 45 f8             	mov    0xfffffff8(%ebp),%eax
//     80483dd:	8b 55 fc             	mov    0xfffffffc(%ebp),%edx
//     80483e0:	89 04 24             	mov    %eax,(%esp)
//     80483e3:	89 54 24 04          	mov    %edx,0x4(%esp)
//
//
// ... a sequence of different types of bytecode jumps go here ...
//
//
// cleanup and return from our execute_bytecodes function
//
//   8048440:	c9                   	leave  
//   8048441:	c3                   	ret    
//
// **

const int compile_x86__funk__header__length = 31;
u8        compile_x86__funk__header[] = {
  0x55,
  0x89, 0xe5,
  0x83, 0xec, 0x20,
  0x8b, 0x45, 0x08,
  0x89, 0x45, 0xf8,
  0x8b, 0x45, 0x0c,
  0x89, 0x45, 0xfc,
  0x8b, 0x45, 0xf8,
  0x8b, 0x55, 0xfc,
  0x89, 0x04, 0x24,
  0x89, 0x54, 0x24, 0x04
};

const int compile_x86__funk__footer__length = 2;
u8        compile_x86__funk__footer[] = {
  0xc9,
  0xc3
};

void raw__chunk__compile_x86__funk(f2ptr this, u64 index, f2ptr cause, u64* next_index, f2ptr funk) {
  u8* iter;
  iter = compile_x86__funk__header;
  int i;
  for (i = compile_x86__funk__header__length; i > 0; i --) {
    raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, *iter); index = *next_index;
    iter ++;
  }
  
  raw__chunk__compile_x86__bytecodes(this, index, cause, next_index, f2funk__body_bytecodes(funk, cause)); index = *next_index;
  
  iter = compile_x86__funk__footer;
  for (i = compile_x86__funk__footer__length; i > 0; i --) {
    raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, *iter); index = *next_index;
    iter ++;
  }
}

f2ptr f2chunk__new_compiled_from_funk(f2ptr cause, f2ptr funk) {
  u64 chunk_length;
  u64 next_index;
  raw__chunk__compile_x86__funk(nil, 0, cause, &chunk_length, funk);
  f2ptr this = f2chunk__new(cause, chunk_length, NULL);
  raw__chunk__compile_x86__funk(this, 0, cause, &next_index, funk);
  return this;
}

void raw__chunk__compile_x86__metro(f2ptr this, u64 index, f2ptr cause, u64* next_index, f2ptr metro) {
  u8* iter;
  iter = compile_x86__funk__header;
  int i;
  for (i = compile_x86__funk__header__length; i > 0; i --) {
    raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, *iter); index = *next_index;
    iter ++;
  }
  
  raw__chunk__compile_x86__bytecodes(this, index, cause, next_index, raw__metro__body_bytecodes(cause, metro)); index = *next_index;
  
  iter = compile_x86__funk__footer;
  for (i = compile_x86__funk__footer__length; i > 0; i --) {
    raw__chunk__compile_x86__value_bit8(this, index, cause, next_index, *iter); index = *next_index;
    iter ++;
  }
}

f2ptr f2chunk__new_compiled_from_metro(f2ptr cause, f2ptr metro) {
  u64 chunk_length;
  u64 next_index;
  raw__chunk__compile_x86__metro(nil, 0, cause, &chunk_length, metro);
  f2ptr this = f2chunk__new(cause, chunk_length, NULL);
  raw__chunk__compile_x86__metro(this, 0, cause, &next_index, metro);
  return this;
}


// machine_code_jump

def_primobject_4_slot(machine_code_jump,
		      index,
		      command,
		      label,
		      arguments);

f2ptr raw__machine_code_jump__new(f2ptr cause, f2ptr index, f2ptr command, f2ptr label, f2ptr arguments) {
  return f2machine_code_jump__new(cause, index, command, label, arguments);
}

f2ptr f2__machine_code_jump__new(f2ptr cause, f2ptr index, f2ptr command, f2ptr label, f2ptr arguments) {
  assert_argument_type(integer,  index);
  assert_argument_type(symbol,   command);
  assert_argument_type(symbol,   label);
  assert_argument_type(conslist, arguments);
  return raw__machine_code_jump__new(cause, index, command, label, arguments);
}
def_pcfunk4(machine_code_jump__new, index, command, label, arguments,
	    "",
	    return f2__machine_code_jump__new(this_cause, index, command, label, arguments));


f2ptr raw__machine_code_jump__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "machine_code_jump"),
						new__symbol(cause, "index"),             f2__machine_code_jump__index(    cause, this),
						new__symbol(cause, "command"),           f2__machine_code_jump__command(  cause, this),
						new__symbol(cause, "label"),             f2__machine_code_jump__label(    cause, this),
						new__symbol(cause, "arguments"),         f2__machine_code_jump__arguments(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__machine_code_jump__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(machine_code_jump,            this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__machine_code_jump__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(machine_code_jump__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__machine_code_jump__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2machine_code_jump__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2machine_code_jump__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_machine_code_jump.terminal_print_with_frame__funk);}
  return this;
}


// machine_code_chunk

def_primobject_3_slot(machine_code_chunk,
		      chunk,
		      index_label_ptypehash,
		      jumps);

f2ptr raw__machine_code_chunk__new(f2ptr cause, f2ptr chunk, f2ptr index_label_ptypehash, f2ptr jumps) {
  return f2machine_code_chunk__new(cause, chunk, index_label_ptypehash, jumps);
}

f2ptr f2__machine_code_chunk__new(f2ptr cause, f2ptr chunk) {
  assert_argument_type(chunk, chunk);
  f2ptr index_label_ptypehash = f2__ptypehash__new(cause);
  return raw__machine_code_chunk__new(cause, chunk, index_label_ptypehash, nil);
}
def_pcfunk1(machine_code_chunk__new, chunk,
	    "",
	    return f2__machine_code_chunk__new(this_cause, chunk));


f2ptr raw__machine_code_chunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list8__new(cause,
					       new__symbol(cause, "print_object_type"),     new__symbol(cause, "machine_code_chunk"),
					       new__symbol(cause, "chunk"),                 f2__machine_code_chunk__chunk(cause, this),
					       new__symbol(cause, "index_label_ptypehash"), f2__machine_code_chunk__index_label_ptypehash(cause, this),
					       new__symbol(cause, "jumps"),                 f2__machine_code_chunk__jumps(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

// 48 b8 00 00 64 a7 b3 b6 e0 0d 	movabs $0x0de0b6b3a7640000,%rax

void raw__expression__compile_x86_to_chunk__movabs__constant_rax(f2ptr cause, f2ptr chunk, s64 start_index, u64 constant_value) {
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, 0xB8);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 2, (constant_value >>  0) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 3, (constant_value >>  8) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 4, (constant_value >> 16) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 5, (constant_value >> 24) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 6, (constant_value >> 32) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 7, (constant_value >> 40) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 8, (constant_value >> 48) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 9, (constant_value >> 56) & 0xFF);
}

f2ptr raw__expression__compile_x86__movabs__constant_rax(f2ptr cause, u64 constant_value) {
  f2ptr chunk = raw__chunk__new(cause, 10);
  raw__expression__compile_x86_to_chunk__movabs__constant_rax(cause, chunk, 0, constant_value);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ac:	48 bf ef be ad de ef 	movabs $0xdeadbeefdeadbeef,%rdi
//  4000b3:	be ad de 

void raw__expression__compile_x86_to_chunk__movabs__constant_rdi(f2ptr cause, f2ptr chunk, s64 start_index, u64 constant_value) {
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, 0xBF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 2, (constant_value >>  0) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 3, (constant_value >>  8) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 4, (constant_value >> 16) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 5, (constant_value >> 24) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 6, (constant_value >> 32) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 7, (constant_value >> 40) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 8, (constant_value >> 48) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 9, (constant_value >> 56) & 0xFF);
}

f2ptr raw__expression__compile_x86__movabs__constant_rdi(f2ptr cause, u64 constant_value) {
  f2ptr chunk = raw__chunk__new(cause, 10);
  raw__expression__compile_x86_to_chunk__movabs__constant_rdi(cause, chunk, 0, constant_value);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b6:	48 be ef be ad de ef 	movabs $0xdeadbeefdeadbeef,%rsi
//  4000bd:	be ad de 

void raw__expression__compile_x86_to_chunk__movabs__constant_rsi(f2ptr cause, f2ptr chunk, s64 start_index, u64 constant_value) {
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, 0xBE);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 2, (constant_value >>  0) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 3, (constant_value >>  8) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 4, (constant_value >> 16) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 5, (constant_value >> 24) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 6, (constant_value >> 32) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 7, (constant_value >> 40) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 8, (constant_value >> 48) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 9, (constant_value >> 56) & 0xFF);
}

f2ptr raw__expression__compile_x86__movabs__constant_rsi(f2ptr cause, u64 constant_value) {
  f2ptr chunk = raw__chunk__new(cause, 10);
  raw__expression__compile_x86_to_chunk__movabs__constant_rsi(cause, chunk, 0, constant_value);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000c0:	48 ba ef be ad de ef 	movabs $0xdeadbeefdeadbeef,%rdx
//  4000c7:	be ad de 

void raw__expression__compile_x86_to_chunk__movabs__constant_rdx(f2ptr cause, f2ptr chunk, s64 start_index, u64 constant_value) {
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, 0xBA);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 2, (constant_value >>  0) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 3, (constant_value >>  8) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 4, (constant_value >> 16) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 5, (constant_value >> 24) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 6, (constant_value >> 32) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 7, (constant_value >> 40) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 8, (constant_value >> 48) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 9, (constant_value >> 56) & 0xFF);
}

f2ptr raw__expression__compile_x86__movabs__constant_rdx(f2ptr cause, u64 constant_value) {
  f2ptr chunk = raw__chunk__new(cause, 10);
  raw__expression__compile_x86_to_chunk__movabs__constant_rdx(cause, chunk, 0, constant_value);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ca:	48 b9 ef be ad de ef 	movabs $0xdeadbeefdeadbeef,%rcx
//  4000d1:	be ad de 

void raw__expression__compile_x86_to_chunk__movabs__constant_rcx(f2ptr cause, f2ptr chunk, s64 start_index, u64 constant_value) {
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, 0xB9);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 2, (constant_value >>  0) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 3, (constant_value >>  8) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 4, (constant_value >> 16) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 5, (constant_value >> 24) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 6, (constant_value >> 32) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 7, (constant_value >> 40) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 8, (constant_value >> 48) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 9, (constant_value >> 56) & 0xFF);
}

f2ptr raw__expression__compile_x86__movabs__constant_rcx(f2ptr cause, u64 constant_value) {
  f2ptr chunk = raw__chunk__new(cause, 10);
  raw__expression__compile_x86_to_chunk__movabs__constant_rcx(cause, chunk, 0, constant_value);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000d4:	49 b8 ef be ad de ef 	movabs $0xdeadbeefdeadbeef,%r8
//  4000db:	be ad de 

void raw__expression__compile_x86_to_chunk__movabs__constant_r8(f2ptr cause, f2ptr chunk, s64 start_index, u64 constant_value) {
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x49);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, 0xB8);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 2, (constant_value >>  0) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 3, (constant_value >>  8) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 4, (constant_value >> 16) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 5, (constant_value >> 24) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 6, (constant_value >> 32) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 7, (constant_value >> 40) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 8, (constant_value >> 48) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 9, (constant_value >> 56) & 0xFF);
}

f2ptr raw__expression__compile_x86__movabs__constant_r8(f2ptr cause, u64 constant_value) {
  f2ptr chunk = raw__chunk__new(cause, 10);
  raw__expression__compile_x86_to_chunk__movabs__constant_r8(cause, chunk, 0, constant_value);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000de:	49 b9 ef be ad de ef 	movabs $0xdeadbeefdeadbeef,%r9
//  4000e5:	be ad de 

void raw__expression__compile_x86_to_chunk__movabs__constant_r9(f2ptr cause, f2ptr chunk, s64 start_index, u64 constant_value) {
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x49);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, 0xB9);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 2, (constant_value >>  0) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 3, (constant_value >>  8) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 4, (constant_value >> 16) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 5, (constant_value >> 24) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 6, (constant_value >> 32) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 7, (constant_value >> 40) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 8, (constant_value >> 48) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, start_index + 9, (constant_value >> 56) & 0xFF);
}

f2ptr raw__expression__compile_x86__movabs__constant_r9(f2ptr cause, u64 constant_value) {
  f2ptr chunk = raw__chunk__new(cause, 10);
  raw__expression__compile_x86_to_chunk__movabs__constant_r9(cause, chunk, 0, constant_value);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4007e5:	74 07                	je     4007ee <test_if+0x16>

f2ptr raw__expression__compile_x86_to_chunk__je__constant(f2ptr cause, f2ptr chunk, s64 start_index, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x74);
    raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, relative_offset);
    return nil;
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-je-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

f2ptr raw__expression__compile_x86__je__constant(f2ptr cause, s64 relative_offset) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  assert_value(raw__expression__compile_x86_to_chunk__je__constant(cause, chunk, 0, relative_offset));
  return f2__machine_code_chunk__new(cause, chunk);
}

//  400809:	75 07                	jne    400812 <test_if_equal+0x1d>

f2ptr raw__expression__compile_x86_to_chunk__jne__constant(f2ptr cause, f2ptr chunk, s64 start_index, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x75);
    raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, relative_offset);
    return nil;
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-jne-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

f2ptr raw__expression__compile_x86__jne__constant(f2ptr cause, s64 relative_offset) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  assert_value(raw__expression__compile_x86_to_chunk__jne__constant(cause, chunk, 0, relative_offset));
  return f2__machine_code_chunk__new(cause, chunk);
}

//  400851:	7e 07                	jle    40085a <test_if_greater_than+0x1d>

f2ptr raw__expression__compile_x86_to_chunk__jle__constant(f2ptr cause, f2ptr chunk, s64 start_index, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x7E);
    raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, relative_offset);
    return nil;
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-jle-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

f2ptr raw__expression__compile_x86__jle__constant(f2ptr cause, s64 relative_offset) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  assert_value(raw__expression__compile_x86_to_chunk__jle__constant(cause, chunk, 0, relative_offset));
  return f2__machine_code_chunk__new(cause, chunk);
}

//  400875:	7c 07                	jl     40087e <test_if_greater_than_or_equal+0x1d>

f2ptr raw__expression__compile_x86_to_chunk__jl__constant(f2ptr cause, f2ptr chunk, s64 start_index, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x7C);
    raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, relative_offset);
    return nil;
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-jl-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

f2ptr raw__expression__compile_x86__jl__constant(f2ptr cause, s64 relative_offset) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  assert_value(raw__expression__compile_x86_to_chunk__jl__constant(cause, chunk, 0, relative_offset));
  return f2__machine_code_chunk__new(cause, chunk);
}

//  400899:	7d 07                	jge    4008a2 <test_if_less_than+0x1d>

f2ptr raw__expression__compile_x86_to_chunk__jge__constant(f2ptr cause, f2ptr chunk, s64 start_index, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x7D);
    raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, relative_offset);
    return nil;
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-jge-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

f2ptr raw__expression__compile_x86__jge__constant(f2ptr cause, s64 relative_offset) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  assert_value(raw__expression__compile_x86_to_chunk__jge__constant(cause, chunk, 0, relative_offset));
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4008bd:	7f 07                	jg     4008c6 <test_if_less_than_or_equal+0x1d>

f2ptr raw__expression__compile_x86_to_chunk__jg__constant(f2ptr cause, f2ptr chunk, s64 start_index, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    raw__chunk__bit8__elt__set(cause, chunk, start_index + 0, 0x7F);
    raw__chunk__bit8__elt__set(cause, chunk, start_index + 1, relative_offset);
    return nil;
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-jg-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

f2ptr raw__expression__compile_x86__jg__constant(f2ptr cause, s64 relative_offset) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  assert_value(raw__expression__compile_x86_to_chunk__jg__constant(cause, chunk, 0, relative_offset));
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__machine_code_chunk__finalize_jumps(f2ptr cause, f2ptr this) {
  f2ptr index_label_ptypehash = f2machine_code_chunk__index_label_ptypehash(this, cause);
  f2ptr chunk                 = f2machine_code_chunk__chunk(                this, cause);
  f2ptr jumps                 = f2machine_code_chunk__jumps(                this, cause);
  {
    f2ptr iter = jumps;
    while (iter != nil) {
      f2ptr jump = f2cons__car(iter, cause);
      {
	f2ptr jump__index     = f2machine_code_jump__index(    jump, cause);
	f2ptr jump__command   = f2machine_code_jump__command(  jump, cause);
	f2ptr jump__label     = f2machine_code_jump__label(    jump, cause);
	f2ptr jump__arguments = f2machine_code_jump__arguments(jump, cause);
	s64   jump__index__i  = f2integer__i(jump__index, cause);
	f2ptr label__index    = raw__ptypehash__lookup(cause, index_label_ptypehash, jump__label);
	if (label__index == nil) {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),   new__symbol(cause, "machine_code_chunk-finalize_jumps-undefined_label"),
					 new__symbol(cause, "this"),       this,
					 new__symbol(cause, "jump_label"), jump__label));
	}
	s64 label__index__i = f2integer__i(label__index, cause);
	u64 jump_location   = raw__chunk__bytes(cause, chunk) + label__index__i;
	if (raw__eq(cause, jump__command, new__symbol(cause, "movabs"))) {
	  f2ptr register_name = f2cons__car(jump__arguments, cause);
	  if      (raw__eq(cause, register_name, new__symbol(cause, "rax"))) {raw__expression__compile_x86_to_chunk__movabs__constant_rax(cause, chunk, jump__index__i, jump_location);}
	  else if (raw__eq(cause, register_name, new__symbol(cause, "rdi"))) {raw__expression__compile_x86_to_chunk__movabs__constant_rdi(cause, chunk, jump__index__i, jump_location);}
	  else if (raw__eq(cause, register_name, new__symbol(cause, "rsi"))) {raw__expression__compile_x86_to_chunk__movabs__constant_rsi(cause, chunk, jump__index__i, jump_location);}
	  else if (raw__eq(cause, register_name, new__symbol(cause, "rdx"))) {raw__expression__compile_x86_to_chunk__movabs__constant_rdx(cause, chunk, jump__index__i, jump_location);}
	  else if (raw__eq(cause, register_name, new__symbol(cause, "rcx"))) {raw__expression__compile_x86_to_chunk__movabs__constant_rcx(cause, chunk, jump__index__i, jump_location);}
	  else if (raw__eq(cause, register_name, new__symbol(cause, "r8")))  {raw__expression__compile_x86_to_chunk__movabs__constant_r8( cause, chunk, jump__index__i, jump_location);}
	  else if (raw__eq(cause, register_name, new__symbol(cause, "r9")))  {raw__expression__compile_x86_to_chunk__movabs__constant_r9( cause, chunk, jump__index__i, jump_location);}
	  else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "machine_code_chunk-finalize_jumps-unknown_movabs_register"),
					   new__symbol(cause, "this"),          this,
					   new__symbol(cause, "register_name"), register_name));
	  }
	} else if (raw__eq(cause, jump__command, new__symbol(cause, "je"))) {
	  assert_value(raw__expression__compile_x86_to_chunk__je__constant(cause, chunk, jump__index__i, label__index__i - (jump__index__i + 2)));
	} else if (raw__eq(cause, jump__command, new__symbol(cause, "jne"))) {
	  assert_value(raw__expression__compile_x86_to_chunk__jne__constant(cause, chunk, jump__index__i, label__index__i - (jump__index__i + 2)));
	} else if (raw__eq(cause, jump__command, new__symbol(cause, "jle"))) {
	  assert_value(raw__expression__compile_x86_to_chunk__jle__constant(cause, chunk, jump__index__i, label__index__i - (jump__index__i + 2)));
	} else if (raw__eq(cause, jump__command, new__symbol(cause, "jl"))) {
	  assert_value(raw__expression__compile_x86_to_chunk__jl__constant(cause, chunk, jump__index__i, label__index__i - (jump__index__i + 2)));
	} else if (raw__eq(cause, jump__command, new__symbol(cause, "jge"))) {
	  assert_value(raw__expression__compile_x86_to_chunk__jge__constant(cause, chunk, jump__index__i, label__index__i - (jump__index__i + 2)));
	} else if (raw__eq(cause, jump__command, new__symbol(cause, "jg"))) {
	  assert_value(raw__expression__compile_x86_to_chunk__jg__constant(cause, chunk, jump__index__i, label__index__i - (jump__index__i + 2)));
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),     new__symbol(cause, "machine_code_chunk-finalize_jumps-unknown_jump_command"),
					 new__symbol(cause, "this"),         this,
					 new__symbol(cause, "jump_command"), jump__command));
	}
      }
      iter = f2cons__cdr(iter, cause);
    }
  }
  return nil;
}

f2ptr f2__machine_code_chunk__finalize_jumps(f2ptr cause, f2ptr this) {
  assert_argument_type(machine_code_chunk, this);
  return raw__machine_code_chunk__finalize_jumps(cause, this);
}
def_pcfunk1(machine_code_chunk__finalize_jumps, this,
	    "",
	    return f2__machine_code_chunk__finalize_jumps(this_cause, this));


f2ptr f2__machine_code_chunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(machine_code_chunk,            this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__machine_code_chunk__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(machine_code_chunk__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__machine_code_chunk__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2machine_code_chunk__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2machine_code_chunk__primobject_type__new(cause);
  {char* slot_name = "finalize_jumps";            f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.finalize_jumps__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.terminal_print_with_frame__funk);}
  return this;
}


boolean_t raw__machine_code_chunk_list__is_type(f2ptr cause, f2ptr object) {
  f2ptr iter = object;
  while (iter != nil) {
    if (! raw__cons__is_type(cause, iter)) {
      return boolean__false;
    }
    f2ptr element = f2cons__car(iter, cause);
    if (! raw__machine_code_chunk__is_type(cause, element)) {
      return boolean__false;
    }
    iter = f2cons__cdr(iter, cause);
  }
  return boolean__true;
}

f2ptr raw__machine_code_chunk_list__concat(f2ptr cause, f2ptr these) {
  f2ptr new_index_label_ptypehash = f2__ptypehash__new(cause);
  f2ptr chunk_list                = nil;
  f2ptr new_jumps                 = nil;
  f2ptr new_jumps_iter            = nil;
  {
    s64   index_offset    = 0;
    f2ptr chunk_list_iter = nil;
    f2ptr iter            = these;
    while (iter != nil) {
      f2ptr machine_code_chunk = f2cons__car(iter, cause);
      {
	f2ptr chunk                 = f2machine_code_chunk__chunk(                machine_code_chunk, cause);
	f2ptr index_label_ptypehash = f2machine_code_chunk__index_label_ptypehash(machine_code_chunk, cause);
	f2ptr jumps                 = f2machine_code_chunk__jumps(                machine_code_chunk, cause);
	{
	  f2ptr new_cons = f2cons__new(cause, chunk, nil);
	  if (chunk_list == nil) {
	    chunk_list = new_cons;
	  } else {
	    f2cons__cdr__set(chunk_list_iter, cause, new_cons);
	  }
	  chunk_list_iter = new_cons;
	}
	ptypehash__iteration(cause, index_label_ptypehash, label, index,
			     s64   index__i  = f2integer__i(index, cause);
			     f2ptr new_index = f2integer__new(cause, index_offset + index__i);
			     raw__ptypehash__add(cause, new_index_label_ptypehash, label, new_index);
			     );
	{
	  f2ptr jumps_iter = jumps;
	  while (jumps_iter != nil) {
	    f2ptr jump = f2cons__car(jumps_iter, cause);
	    {
	      f2ptr jump__index     = f2machine_code_jump__index(    jump, cause);
	      f2ptr jump__command   = f2machine_code_jump__command(  jump, cause);
	      f2ptr jump__label     = f2machine_code_jump__label(    jump, cause);
	      f2ptr jump__arguments = f2machine_code_jump__arguments(jump, cause);
	      s64   jump__index__i  = f2integer__i(jump__index, cause);
	      f2ptr new_jump__index = f2integer__new(cause, jump__index__i + index_offset);
	      f2ptr new_jump        = raw__machine_code_jump__new(cause, new_jump__index, jump__command, jump__label, jump__arguments);
	      f2ptr new_cons        = f2cons__new(cause, new_jump, nil);
	      if (new_jumps == nil) {
		new_jumps = new_cons;
	      } else {
		f2cons__cdr__set(new_jumps_iter, cause, new_cons);
	      }
	      new_jumps_iter = new_cons;
	    }
	    jumps_iter = f2cons__cdr(jumps_iter, cause);
	  }
	}
	index_offset += raw__chunk__length(cause, chunk);
      }
      iter = f2cons__cdr(iter, cause);
    }
  }
  f2ptr new_chunk              = raw__chunklist__concat(cause, chunk_list);
  f2ptr new_machine_code_chunk = raw__machine_code_chunk__new(cause, new_chunk, new_index_label_ptypehash, new_jumps);
  return new_machine_code_chunk;
}

f2ptr f2__machine_code_chunk_list__concat(f2ptr cause, f2ptr these) {
  assert_argument_type(machine_code_chunk_list, these);
  return raw__machine_code_chunk_list__concat(cause, these);
}
def_pcfunk1(machine_code_chunk_list__concat, these,
	    "",
	    return f2__machine_code_chunk_list__concat(this_cause, these));



f2ptr raw__expression__compile_x86__retq(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 1) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-retq-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0xC3);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__rawcode(f2ptr cause, f2ptr expression) {
  f2ptr subexpressions       = f2cons__cdr(expression, cause);
  f2ptr subexpression_chunks = nil;
  {
    f2ptr iter                       = subexpressions;
    f2ptr subexpression_chunks__iter = nil;
    while (iter != nil) {
      f2ptr subexpression       = f2cons__car(iter, cause);
      f2ptr subexpression_chunk = assert_value(raw__expression__compile_x86(cause, subexpression));
      f2ptr new_cons = f2cons__new(cause, subexpression_chunk, nil);
      if (subexpression_chunks == nil) {
	subexpression_chunks = new_cons;
      } else {
	f2cons__cdr__set(subexpression_chunks__iter, cause, new_cons);
      }
      subexpression_chunks__iter = new_cons;
      iter                       = f2cons__cdr(iter, cause);
    }
  }
  return raw__machine_code_chunk_list__concat(cause, subexpression_chunks);
}

//  4004b4:	55                   	push   %rbp
//  4004b5:	48 89 e5             	mov    %rsp,%rbp
//  4004b8:	48 b8 00 00 64 a7 b3 	movabs $0xde0b6b3a7640000,%rax
//  4004bf:	b6 e0 0d 
//  4004c2:	5d                   	pop    %rbp
//  4004c3:	c3                   	retq   


f2ptr raw__expression__is_register_expression(f2ptr cause, f2ptr expression) {
  if (raw__cons__is_type(cause, expression)) {
    f2ptr command = f2cons__car(expression, cause);
    if (raw__eq(cause, command, new__symbol(cause, "register"))) {
      if (raw__simple_length(cause, expression) == 2) {
	return boolean__true;
      }
    }
  }
  return boolean__false;
}

f2ptr raw__register_expression__register_name(f2ptr cause, f2ptr expression) {
  return f2cons__car(f2cons__cdr(expression, cause), cause);
}


f2ptr raw__expression__is_constant_expression(f2ptr cause, f2ptr expression) {
  if (raw__cons__is_type(cause, expression)) {
    f2ptr command = f2cons__car(expression, cause);
    if (raw__eq(cause, command, new__symbol(cause, "constant"))) {
      if (raw__simple_length(cause, expression) == 2) {
	return boolean__true;
      }
    }
  }
  return boolean__false;
}

f2ptr raw__constant_expression__constant_value(f2ptr cause, f2ptr expression) {
  return f2cons__car(f2cons__cdr(expression, cause), cause);
}




//  4000a2:	50                   	push   %rax

f2ptr raw__expression__compile_x86__push_rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x50);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a6:	51                   	push   %rcx

f2ptr raw__expression__compile_x86__push_rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x51);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a5:	52                   	push   %rdx

f2ptr raw__expression__compile_x86__push_rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x52);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__push_rbp(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x55);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a4:	56                   	push   %rsi

f2ptr raw__expression__compile_x86__push_rsi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x56);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a3:	57                   	push   %rdi

f2ptr raw__expression__compile_x86__push_rdi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x57);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a7:	41 50                	push   %r8

f2ptr raw__expression__compile_x86__push_r8(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x41);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x50);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a9:	41 51                	push   %r9

f2ptr raw__expression__compile_x86__push_r9(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x41);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x51);
  return f2__machine_code_chunk__new(cause, chunk);
}








f2ptr raw__expression__compile_x86__push(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr cdr      = f2cons__cdr(expression, cause);
  f2ptr argument = f2cons__car(cdr,        cause);
  if (raw__expression__is_register_expression(cause, argument)) {
    f2ptr register_name = raw__register_expression__register_name(cause, argument);
    if      (raw__eq(cause, register_name, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__push_rax(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__push_rcx(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__push_rdx(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__push_rbp(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rsi"))) {return raw__expression__compile_x86__push_rsi(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rdi"))) {return raw__expression__compile_x86__push_rdi(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "r8")))  {return raw__expression__compile_x86__push_r8(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "r9")))  {return raw__expression__compile_x86__push_r9(cause);}
    else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-push-unknown_register_name"),
				     new__symbol(cause, "register_name"), register_name,
				     new__symbol(cause, "expression"),    expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}



//  4000ab:	58                   	pop    %rax

f2ptr raw__expression__compile_x86__pop_rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x58);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000af:	59                   	pop    %rcx

f2ptr raw__expression__compile_x86__pop_rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x59);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ae:	5a                   	pop    %rdx

f2ptr raw__expression__compile_x86__pop_rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x5A);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__pop_rbp(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x5D);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ac:	5f                   	pop    %rdi

f2ptr raw__expression__compile_x86__pop_rdi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x5F);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ad:	5e                   	pop    %rsi

f2ptr raw__expression__compile_x86__pop_rsi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x5E);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b0:	41 58                	pop    %r8

f2ptr raw__expression__compile_x86__pop_r8(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x41);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x58);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b2:	41 59                	pop    %r9

f2ptr raw__expression__compile_x86__pop_r9(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x41);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x59);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__pop(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-pop-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr cdr      = f2cons__cdr(expression, cause);
  f2ptr argument = f2cons__car(cdr,        cause);
  if (raw__expression__is_register_expression(cause, argument)) {
    f2ptr register_name = raw__register_expression__register_name(cause, argument);
    if      (raw__eq(cause, register_name, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__pop_rax(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__pop_rcx(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__pop_rdx(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__pop_rbp(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rdi"))) {return raw__expression__compile_x86__pop_rdi(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rsi"))) {return raw__expression__compile_x86__pop_rsi(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "r8")))  {return raw__expression__compile_x86__pop_r8(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "r9")))  {return raw__expression__compile_x86__pop_r9(cause);}
    else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-pop-unknown_register_name"),
				     new__symbol(cause, "register_name"), register_name,
				     new__symbol(cause, "expression"),    expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-pop-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}



f2ptr raw__expression__compile_x86__mov__rsp__rbp(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xE5);
  return f2__machine_code_chunk__new(cause, chunk);
}

//   4004c8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)

boolean_t raw__expression__is_relative_expression(f2ptr cause, f2ptr expression) {
  if (raw__cons__is_type(cause, expression)) {
    f2ptr car = f2cons__car(expression, cause);
    if (raw__eq(cause, car, new__symbol(cause, "relative"))) {
      if (raw__simple_length(cause, expression) == 3) {
	return boolean__true;
      }
    }
  }
  return boolean__false;
}

f2ptr raw__relative_expression__relative_offset(f2ptr cause, f2ptr expression) {
  return f2cons__car(f2cons__cdr(expression, cause), cause);
}

f2ptr raw__relative_expression__argument(f2ptr cause, f2ptr expression) {
  return f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
}

boolean_t raw__expression__is_minus_expression(f2ptr cause, f2ptr expression) {
  if (raw__cons__is_type(cause, expression)) {
    f2ptr car = f2cons__car(expression, cause);
    if (raw__eq(cause, car, new__symbol(cause, "-"))) {
      if (raw__simple_length(cause, expression) == 2) {
	return boolean__true;
      }
    }
  }
  return boolean__false;
}

s64 raw__minus_expression__argument(f2ptr cause, f2ptr expression) {
  return f2cons__car(f2cons__cdr(expression, cause), cause);
}

boolean_t raw__expression__is_deref_expression(f2ptr cause, f2ptr expression) {
  if (raw__cons__is_type(cause, expression)) {
    f2ptr car = f2cons__car(expression, cause);
    if (raw__eq(cause, car, new__symbol(cause, "deref"))) {
      if (raw__simple_length(cause, expression) == 2) {
	return boolean__true;
      }
    }
  }
  return boolean__false;
}

f2ptr raw__deref_expression__argument(f2ptr cause, f2ptr expression) {
  return f2cons__car(f2cons__cdr(expression, cause), cause);
}

f2ptr raw__expression__compile_x86__mov__rax__relative_rbp(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-rdi-relative_rbp-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

f2ptr raw__expression__compile_x86__mov__rdi__relative_rbp(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x7D);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-rdi-relative_rbp-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

f2ptr raw__expression__compile_x86__mov__rsi__relative_rbp(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x75);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-rdi-relative_rbp-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

//  4000a2:	48 8b 45 e0          	mov    -0x20(%rbp),%rax

f2ptr raw__expression__compile_x86__mov__relative_rbp__rax(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x8B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-relative_rbp-rax-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

//  4000ae:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx

f2ptr raw__expression__compile_x86__mov__relative_rbp__rdx(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x8B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x55);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-relative_rbp-rdx-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}







//  4000a6:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi

f2ptr raw__expression__compile_x86__mov__relative_rbp__rdi(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x8B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x7D);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-relative_rbp-rdx-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

//  4000aa:	48 8b 75 e0          	mov    -0x20(%rbp),%rsi

f2ptr raw__expression__compile_x86__mov__relative_rbp__rsi(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x8B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x75);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-relative_rbp-rdx-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

//  4000b2:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx

f2ptr raw__expression__compile_x86__mov__relative_rbp__rcx(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x8B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x4D);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-relative_rbp-rdx-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

//  4000b6:	4c 8b 45 e0          	mov    -0x20(%rbp),%r8

f2ptr raw__expression__compile_x86__mov__relative_rbp__r8(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x4C);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x8B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-relative_rbp-rdx-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

//  4000ba:	4c 8b 4d e0          	mov    -0x20(%rbp),%r9

f2ptr raw__expression__compile_x86__mov__relative_rbp__r9(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x4C);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x8B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x4D);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-relative_rbp-rdx-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}











f2ptr raw__expression__compile_x86__mov__relative_rax__rax(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x8B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x40);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-relative_rax-rax-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

f2ptr raw__expression__compile_x86__add__relative_rbp__rax(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x03);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-add-relative_rpb-rax-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

f2ptr raw__expression__compile_x86__cmp__relative_rbp__rax(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x3B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmp-relative_rpb-rax-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}


f2ptr raw__expression__compile_x86__subq__constant__relative_rbp(f2ptr cause, s64 constant_value, s64 relative_offset_value) {
  if ((constant_value <   128) &&
      (constant_value >= -128)) {
    if ((relative_offset_value <   128) &&
	(relative_offset_value >= -128)) {
      f2ptr chunk = raw__chunk__new(cause, 5);
      raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
      raw__chunk__bit8__elt__set(cause, chunk, 1, 0x83);
      raw__chunk__bit8__elt__set(cause, chunk, 2, 0x6D);
      raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
      raw__chunk__bit8__elt__set(cause, chunk, 4, (u8)((signed char)constant_value));
      return f2__machine_code_chunk__new(cause, chunk);
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-subq-constant-relative_rbp-unknown_relative_offset_range"),
				     new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-subq-constant-relative_rbp-unknown_constant_value_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, constant_value)));
  }
}

f2ptr raw__expression__compile_x86__addq__constant__relative_rbp(f2ptr cause, s64 constant_value, s64 relative_offset_value) {
  if ((constant_value <   128) &&
      (constant_value >= -128)) {
    if ((relative_offset_value <   128) &&
	(relative_offset_value >= -128)) {
      f2ptr chunk = raw__chunk__new(cause, 5);
      raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
      raw__chunk__bit8__elt__set(cause, chunk, 1, 0x83);
      raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
      raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
      raw__chunk__bit8__elt__set(cause, chunk, 4, (u8)((signed char)constant_value));
      return f2__machine_code_chunk__new(cause, chunk);
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-addq-constant-relative_rbp-unknown_relative_offset_range"),
				     new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-addq-constant-relative_rbp-unknown_constant_value_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, constant_value)));
  }
}

f2ptr raw__expression__compile_x86__cmpq__constant__relative_rbp(f2ptr cause, s64 constant_value, s64 relative_offset_value) {
  if ((constant_value <   128) &&
      (constant_value >= -128)) {
    if ((relative_offset_value <   128) &&
	(relative_offset_value >= -128)) {
      f2ptr chunk = raw__chunk__new(cause, 5);
      raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
      raw__chunk__bit8__elt__set(cause, chunk, 1, 0x83);
      raw__chunk__bit8__elt__set(cause, chunk, 2, 0x7D);
      raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
      raw__chunk__bit8__elt__set(cause, chunk, 4, (u8)((signed char)constant_value));
      return f2__machine_code_chunk__new(cause, chunk);
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-constant-relative_rbp-unknown_relative_offset_range"),
				     new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-constant-relative_rbp-unknown_constant_value_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, constant_value)));
  }
}

f2ptr raw__expression__compile_x86__movq__constant__relative_rbp(f2ptr cause, s64 constant_value, s64 relative_offset_value) {
  if ((constant_value <   (1ll << 31)) &&
      (constant_value >= -(1ll << 31))) {
    if ((relative_offset_value <   128) &&
	(relative_offset_value >= -128)) {
      f2ptr chunk = raw__chunk__new(cause, 8);
      raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
      raw__chunk__bit8__elt__set(cause, chunk, 1, 0xC7);
      raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
      raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
      raw__chunk__bit8__elt__set(cause, chunk, 4, (constant_value >>  0) & 0xFF);
      raw__chunk__bit8__elt__set(cause, chunk, 5, (constant_value >>  8) & 0xFF);
      raw__chunk__bit8__elt__set(cause, chunk, 6, (constant_value >> 16) & 0xFF);
      raw__chunk__bit8__elt__set(cause, chunk, 7, (constant_value >> 24) & 0xFF);
      return f2__machine_code_chunk__new(cause, chunk);
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-movq-constant-relative_rbp-unknown_relative_offset_range"),
				     new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-movq-constant-relative_rbp-unknown_constant_value_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, constant_value)));
  }
}

f2ptr raw__expression__compile_x86__mov__deref_rax__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x8B);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x00);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__movzbl__deref_rax__eax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xB6);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x00);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__movzbl__al__eax(cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xB6);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a2:	48 89 f8             	mov    %rdi,%rax

f2ptr raw__expression__compile_x86__mov__rdi__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xF8);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a2:	48 89 fa             	mov    %rdi,%rdx

f2ptr raw__expression__compile_x86__mov__rdi__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xFA);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a2:	48 89 ff             	mov    %rdi,%rdi

f2ptr raw__expression__compile_x86__mov__rdi__rdi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xFF);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a5:	48 89 f0             	mov    %rsi,%rax

f2ptr raw__expression__compile_x86__mov__rsi__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xF0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a2:	48 89 f1             	mov    %rsi,%rcx

f2ptr raw__expression__compile_x86__mov__rsi__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xF1);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a2:	48 89 f2             	mov    %rsi,%rdx

f2ptr raw__expression__compile_x86__mov__rsi__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xF2);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a2:	48 89 f6             	mov    %rsi,%rsi

f2ptr raw__expression__compile_x86__mov__rsi__rsi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xF6);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a8:	48 89 d0             	mov    %rdx,%rax

f2ptr raw__expression__compile_x86__mov__rdx__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xD0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a2:	48 89 d6             	mov    %rdx,%rsi

f2ptr raw__expression__compile_x86__mov__rdx__rsi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xD6);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ab:	48 89 c8             	mov    %rcx,%rax

f2ptr raw__expression__compile_x86__mov__rcx__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC8);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ae:	4c 89 c0             	mov    %r8,%rax

f2ptr raw__expression__compile_x86__mov__r8__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b1:	4c 89 c8             	mov    %r9,%rax

f2ptr raw__expression__compile_x86__mov__r9__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC8);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b4:	48 89 c7             	mov    %rax,%rdi

f2ptr raw__expression__compile_x86__mov__rax__rdi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC7);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b7:	48 89 c6             	mov    %rax,%rsi

f2ptr raw__expression__compile_x86__mov__rax__rsi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC6);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ba:	48 89 c2             	mov    %rax,%rdx

f2ptr raw__expression__compile_x86__mov__rax__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC2);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000bd:	48 89 c1             	mov    %rax,%rcx

f2ptr raw__expression__compile_x86__mov__rax__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC1);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000c0:	49 89 c0             	mov    %rax,%r8

f2ptr raw__expression__compile_x86__mov__rax__r8(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x49);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000c3:	49 89 c1             	mov    %rax,%r9

f2ptr raw__expression__compile_x86__mov__rax__r9(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x49);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC1);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__mov(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr cdr        = f2cons__cdr(expression, cause);
  f2ptr cddr       = f2cons__cdr(cdr,        cause);
  f2ptr argument_0 = f2cons__car(cdr,        cause);
  f2ptr argument_1 = f2cons__car(cddr,       cause);
  if (raw__expression__is_register_expression(cause, argument_0)) {
    f2ptr register_name_0 = raw__register_expression__register_name(cause, argument_0);
    if (raw__expression__is_register_expression(cause, argument_1)) {
      f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__chunk__new(cause, 0);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdi"))) {return raw__expression__compile_x86__mov__rax__rdi(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rsi"))) {return raw__expression__compile_x86__mov__rax__rsi(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__mov__rax__rdx(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__mov__rax__rcx(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "r8")))  {return raw__expression__compile_x86__mov__rax__r8(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "r9")))  {return raw__expression__compile_x86__mov__rax__r9(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rdi"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__mov__rdi__rax(cause);}
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__mov__rdi__rdx(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdi"))) {return raw__expression__compile_x86__mov__rdi__rdi(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rsi"))) {
	if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	  return raw__expression__compile_x86__mov__rsi__rax(cause);
	} else if (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {
	  return raw__expression__compile_x86__mov__rsi__rcx(cause);
	} else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {
	  return raw__expression__compile_x86__mov__rsi__rdx(cause);
	} else if (raw__eq(cause, register_name_1, new__symbol(cause, "rsi"))) {
	  return raw__expression__compile_x86__mov__rsi__rsi(cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rdx"))) {
	if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	  return raw__expression__compile_x86__mov__rdx__rax(cause);
	} else if (raw__eq(cause, register_name_1, new__symbol(cause, "rsi"))) {
	  return raw__expression__compile_x86__mov__rdx__rsi(cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rcx"))) {
	if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	  return raw__expression__compile_x86__mov__rcx__rax(cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "r8"))) {
	if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	  return raw__expression__compile_x86__mov__r8__rax(cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "r9"))) {
	if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	  return raw__expression__compile_x86__mov__r9__rax(cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rsp"))) {
	if (raw__eq(cause, register_name_1, new__symbol(cause, "rbp"))) {
	  return raw__expression__compile_x86__mov__rsp__rbp(cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    }
    if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
      if (raw__expression__is_relative_expression(cause, argument_1)) {
	f2ptr relative_offset = raw__relative_expression__relative_offset(cause, argument_1);
	f2ptr argument        = raw__relative_expression__argument(       cause, argument_1);
	s64   relative_offset_value = 0;
	if (raw__pointer__is_type(cause, relative_offset)) {
	  relative_offset_value = f2pointer__p(relative_offset, cause);
	} else if (raw__integer__is_type(cause, relative_offset)) {
	  relative_offset_value = f2integer__i(relative_offset, cause);
	} else if (raw__expression__is_minus_expression(cause, relative_offset)) {
	  f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
	  if (raw__pointer__is_type(cause, minus_expression__argument)) {
	    relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
	  } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	    relative_offset_value = -f2integer__i(minus_expression__argument, cause);
	  } else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-mov-invalid_minus_argument_type"),
					   new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
					   new__symbol(cause, "expression"),                expression));
	  }
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-invalid_relative_offset_type"),
					 new__symbol(cause, "relative_offset"), relative_offset,
					 new__symbol(cause, "expression"),      expression));
	}
	if (raw__expression__is_register_expression(cause, argument)) {
	  f2ptr register_name = raw__register_expression__register_name(cause, argument);
	  if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {
	    return raw__expression__compile_x86__mov__rax__relative_rbp(cause, relative_offset_value);
	  } else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					   new__symbol(cause, "register_name"), register_name,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-invalid_argument_type"),
					 new__symbol(cause, "argument"),   argument,
					 new__symbol(cause, "expression"), expression));
	}
      } else {
	return new__error(f2list4__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-invalid_argument_expression_type"),
				       new__symbol(cause, "expression"), expression));
      }
    } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rdi"))) {
      if (raw__expression__is_relative_expression(cause, argument_1)) {
	f2ptr relative_offset = raw__relative_expression__relative_offset(cause, argument_1);
	f2ptr argument        = raw__relative_expression__argument(       cause, argument_1);
	s64   relative_offset_value = 0;
	if (raw__pointer__is_type(cause, relative_offset)) {
	  relative_offset_value = f2pointer__p(relative_offset, cause);
	} else if (raw__integer__is_type(cause, relative_offset)) {
	  relative_offset_value = f2integer__i(relative_offset, cause);
	} else if (raw__expression__is_minus_expression(cause, relative_offset)) {
	  f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
	  if (raw__pointer__is_type(cause, minus_expression__argument)) {
	    relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
	  } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	    relative_offset_value = -f2integer__i(minus_expression__argument, cause);
	  } else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-mov-invalid_minus_argument_type"),
					   new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
					   new__symbol(cause, "expression"),                expression));
	  }
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-invalid_relative_offset_type"),
					 new__symbol(cause, "relative_offset"), relative_offset,
					 new__symbol(cause, "expression"),      expression));
	}
	if (raw__expression__is_register_expression(cause, argument)) {
	  f2ptr register_name = raw__register_expression__register_name(cause, argument);
	  if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {
	    return raw__expression__compile_x86__mov__rdi__relative_rbp(cause, relative_offset_value);
	  } else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					   new__symbol(cause, "register_name"), register_name,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-invalid_argument_type"),
					 new__symbol(cause, "argument"),   argument,
					 new__symbol(cause, "expression"), expression));
	}
      } else {
	return new__error(f2list4__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-invalid_argument_expression_type"),
				       new__symbol(cause, "expression"), expression));
      }
    } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rsi"))) {
      if (raw__expression__is_relative_expression(cause, argument_1)) {
	f2ptr relative_offset = raw__relative_expression__relative_offset(cause, argument_1);
	f2ptr argument        = raw__relative_expression__argument(       cause, argument_1);
	s64   relative_offset_value = 0;
	if (raw__pointer__is_type(cause, relative_offset)) {
	  relative_offset_value = f2pointer__p(relative_offset, cause);
	} else if (raw__integer__is_type(cause, relative_offset)) {
	  relative_offset_value = f2integer__i(relative_offset, cause);
	} else if (raw__expression__is_minus_expression(cause, relative_offset)) {
	  f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
	  if (raw__pointer__is_type(cause, minus_expression__argument)) {
	    relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
	  } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	    relative_offset_value = -f2integer__i(minus_expression__argument, cause);
	  } else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-mov-invalid_minus_argument_type"),
					   new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
					   new__symbol(cause, "expression"),                expression));
	  }
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-invalid_relative_offset_type"),
					 new__symbol(cause, "relative_offset"), relative_offset,
					 new__symbol(cause, "expression"),      expression));
	}
	if (raw__expression__is_register_expression(cause, argument)) {
	  f2ptr register_name = raw__register_expression__register_name(cause, argument);
	  if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {
	    return raw__expression__compile_x86__mov__rsi__relative_rbp(cause, relative_offset_value);
	  } else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					   new__symbol(cause, "register_name"), register_name,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-invalid_argument_type"),
					 new__symbol(cause, "argument"),   argument,
					 new__symbol(cause, "expression"), expression));
	}
      } else {
	return new__error(f2list4__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-invalid_argument_expression_type"),
				       new__symbol(cause, "expression"), expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
				     new__symbol(cause, "register_name"), register_name_0,
				     new__symbol(cause, "expression"),    expression));
    }
  } else if (raw__expression__is_relative_expression(cause, argument_0)) {
    f2ptr relative_offset = raw__relative_expression__relative_offset(cause, argument_0);
    f2ptr argument        = raw__relative_expression__argument(       cause, argument_0);
    s64   relative_offset_value = 0;
    if (raw__pointer__is_type(cause, relative_offset)) {
      relative_offset_value = f2pointer__p(relative_offset, cause);
    } else if (raw__integer__is_type(cause, relative_offset)) {
      relative_offset_value = f2integer__i(relative_offset, cause);
    } else if (raw__expression__is_minus_expression(cause, relative_offset)) {
      f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
      if (raw__pointer__is_type(cause, minus_expression__argument)) {
	relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
      } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	relative_offset_value = -f2integer__i(minus_expression__argument, cause);
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-mov-invalid_minus_argument_type"),
				       new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
				       new__symbol(cause, "expression"),                expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-invalid_relative_offset_type"),
				     new__symbol(cause, "relative_offset"), relative_offset,
				     new__symbol(cause, "expression"),      expression));
    }
    if (raw__expression__is_register_expression(cause, argument)) {
      f2ptr register_name_0 = raw__register_expression__register_name(cause, argument);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "rbp"))) {
	if (raw__expression__is_register_expression(cause, argument_1)) {
	  f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
	  if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__mov__relative_rbp__rax(cause, relative_offset_value);}
	  else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__mov__relative_rbp__rdx(cause, relative_offset_value);}
	  else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdi"))) {return raw__expression__compile_x86__mov__relative_rbp__rdi(cause, relative_offset_value);}
	  else if (raw__eq(cause, register_name_1, new__symbol(cause, "rsi"))) {return raw__expression__compile_x86__mov__relative_rbp__rsi(cause, relative_offset_value);}
	  else if (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__mov__relative_rbp__rcx(cause, relative_offset_value);}
	  else if (raw__eq(cause, register_name_1, new__symbol(cause, "r8")))  {return raw__expression__compile_x86__mov__relative_rbp__r8(cause,  relative_offset_value);}
	  else if (raw__eq(cause, register_name_1, new__symbol(cause, "r9")))  {return raw__expression__compile_x86__mov__relative_rbp__r9(cause,  relative_offset_value);}
	  else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
	if (raw__expression__is_register_expression(cause, argument_1)) {
	  f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
	  if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__mov__relative_rax__rax(cause, relative_offset_value);}
	  else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-invalid_argument_type"),
				     new__symbol(cause, "argument"),   argument,
				     new__symbol(cause, "expression"), expression));
    }
  } else if (raw__expression__is_deref_expression(cause, argument_0)) {
    f2ptr deref_argument = raw__deref_expression__argument(cause, argument_0);
    if (raw__expression__is_register_expression(cause, deref_argument)) {
      f2ptr register_name_0 = raw__register_expression__register_name(cause, deref_argument);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
	if (raw__expression__is_register_expression(cause, argument_1)) {
	  f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	    return raw__expression__compile_x86__mov__deref_rax__rax(cause);
	  } else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-unknown_deref_target_argument_expression_type"),
					 new__symbol(cause, "argument"),   argument_1,
					 new__symbol(cause, "expression"), expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-unknown_deref_argument_expression_type"),
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
  return new__error(f2list4__new(cause,
				 new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-should_never_get_here"),
				 new__symbol(cause, "expression"), expression));
}

f2ptr raw__expression__compile_x86__movzbl(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movzbl-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_register_expression(cause, argument_0)) {
    f2ptr register_name_0 = raw__register_expression__register_name(cause, argument_0);
    if (raw__eq(cause, register_name_0, new__symbol(cause, "al"))) {
      if (raw__expression__is_register_expression(cause, argument_1)) {
	f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
	if (raw__eq(cause, register_name_1, new__symbol(cause, "eax"))) {
	  return raw__expression__compile_x86__movzbl__al__eax(cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movzbl-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_0,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movzbl-invalid_argument_expression_type"),
				       new__symbol(cause, "argument"),   argument_1,
				       new__symbol(cause, "expression"), expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movzbl-unknown_register"),
				     new__symbol(cause, "register_name"), register_name_0,
				     new__symbol(cause, "expression"),    expression));
    }
  } else if (raw__expression__is_deref_expression(cause, argument_0)) {
    f2ptr deref_expression__argument = raw__deref_expression__argument(cause, argument_0);
    if (raw__expression__is_register_expression(cause, deref_expression__argument)) {
      f2ptr register_name_0 = raw__register_expression__register_name(cause, deref_expression__argument);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
	if (raw__expression__is_register_expression(cause, argument_1)) {
	  f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "eax"))) {
	    return raw__expression__compile_x86__movzbl__deref_rax__eax(cause);
	  } else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movzbl-unknown_register"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movzbl-invalid_argument_expression_type"),
					 new__symbol(cause, "argument"),   argument_1,
					 new__symbol(cause, "expression"), expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movzbl-unknown_register"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movzbl-invalid_argument_expression_type"),
				     new__symbol(cause, "argument"),   argument_0,
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movzbl-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}

//   4000a2:	48 01 d0             	add    %rdx,%rax

f2ptr raw__expression__compile_x86__add__rdx__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x01);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xD0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a2:	48 01 c2             	add    %rax,%rdx

f2ptr raw__expression__compile_x86__add__rax__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x01);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC2);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__add(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-add-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_register_expression(cause, argument_0)) {
    f2ptr register_name_0 = raw__register_expression__register_name(cause, argument_0);
    if (raw__eq(cause, register_name_0, new__symbol(cause, "rdx"))) {
      if (raw__expression__is_register_expression(cause, argument_1)) {
	f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
	if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	  return raw__expression__compile_x86__add__rdx__rax(cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-add-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-add-invalid_argument_expression_type"),
				       new__symbol(cause, "argument"),   argument_1,
				       new__symbol(cause, "expression"), expression));
      }
    } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
      if (raw__expression__is_register_expression(cause, argument_1)) {
	f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
	if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {
	  return raw__expression__compile_x86__add__rax__rdx(cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-add-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-add-invalid_argument_expression_type"),
				       new__symbol(cause, "argument"),   argument_1,
				       new__symbol(cause, "expression"), expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-add-unknown_register"),
				     new__symbol(cause, "register_name"), register_name_0,
				     new__symbol(cause, "expression"),    expression));
    }
  } else if (raw__expression__is_relative_expression(cause, argument_0)) {
    f2ptr relative_offset               = raw__relative_expression__relative_offset(cause, argument_0);
    f2ptr relative_expression__argument = raw__relative_expression__argument(       cause, argument_0);
    s64   relative_offset_value = 0;
    if (raw__pointer__is_type(cause, relative_offset)) {
      relative_offset_value = f2pointer__p(relative_offset, cause);
    } else if (raw__integer__is_type(cause, relative_offset)) {
      relative_offset_value = f2integer__i(relative_offset, cause);
    } else if (raw__expression__is_minus_expression(cause, relative_offset)) {
      f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
      if (raw__pointer__is_type(cause, minus_expression__argument)) {
	relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
      } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	relative_offset_value = -f2integer__i(minus_expression__argument, cause);
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-add-invalid_minus_argument_type"),
				       new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
				       new__symbol(cause, "expression"),                expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-add-invalid_relative_offset_type"),
				     new__symbol(cause, "relative_offset"), relative_offset,
				     new__symbol(cause, "expression"),      expression));
    }
    if (raw__expression__is_register_expression(cause, relative_expression__argument)) {
      f2ptr register_name_0 = raw__register_expression__register_name(cause, relative_expression__argument);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "rbp"))) {
	if (raw__expression__is_register_expression(cause, argument_1)) {
	  f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	    return raw__expression__compile_x86__add__relative_rbp__rax(cause, relative_offset_value);
	  } else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-add-unknown_register"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-add-invalid_argument_expression_type"),
					 new__symbol(cause, "argument"),   argument_1,
					 new__symbol(cause, "expression"), expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-add-unknown_register"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-add-invalid_argument_expression_type"),
				     new__symbol(cause, "argument"),   argument_0,
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-add-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}


f2ptr raw__expression__compile_x86__subq(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-subq-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_constant_expression(cause, argument_0)) {
    f2ptr constant_value = raw__constant_expression__constant_value(cause, argument_0);
    s64   constant_value__i = 0;
    if (raw__pointer__is_type(cause, constant_value)) {
      constant_value__i = (s64)f2pointer__p(constant_value, cause);
    } else if (raw__integer__is_type(cause, constant_value)) {
      constant_value__i = f2integer__i(constant_value, cause);
    } else if (raw__expression__is_minus_expression(cause, constant_value)) {
      f2ptr minus_expression__argument = raw__minus_expression__argument(cause, constant_value);
      if (raw__pointer__is_type(cause, minus_expression__argument)) {
	constant_value__i = -(s64)f2pointer__p(minus_expression__argument, cause);
      } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	constant_value__i = -f2integer__i(minus_expression__argument, cause);
      } else {
	return new__error(f2list8__new(cause,
				       new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-subq-invalid_constant_argument_expression_type"),
				       new__symbol(cause, "argument"),       argument_0,
				       new__symbol(cause, "constant_value"), constant_value,
				       new__symbol(cause, "expression"),     expression));
      }
    } else {
      return new__error(f2list8__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-subq-invalid_constant_argument_expression_type"),
				     new__symbol(cause, "argument"),       argument_0,
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
    if (raw__expression__is_relative_expression(cause, argument_1)) {
      f2ptr relative_offset               = raw__relative_expression__relative_offset(cause, argument_1);
      f2ptr relative_expression__argument = raw__relative_expression__argument(       cause, argument_1);
      s64   relative_offset_value = 0;
      if (raw__pointer__is_type(cause, relative_offset)) {
	relative_offset_value = (s64)f2pointer__p(relative_offset, cause);
      } else if (raw__integer__is_type(cause, relative_offset)) {
	relative_offset_value = f2integer__i(relative_offset, cause);
      } else if (raw__expression__is_minus_expression(cause, relative_offset)) {
	f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
	if (raw__pointer__is_type(cause, minus_expression__argument)) {
	  relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
	} else if (raw__integer__is_type(cause, minus_expression__argument)) {
	  relative_offset_value = -f2integer__i(minus_expression__argument, cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-subq-invalid_minus_argument_type"),
					 new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
					 new__symbol(cause, "expression"),                expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-subq-invalid_relative_offset_type"),
				       new__symbol(cause, "relative_offset"), relative_offset,
				       new__symbol(cause, "expression"),      expression));
      }
      if (raw__expression__is_register_expression(cause, relative_expression__argument)) {
	f2ptr register_name = raw__register_expression__register_name(cause, relative_expression__argument);
	if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {
	  return raw__expression__compile_x86__subq__constant__relative_rbp(cause, constant_value__i, relative_offset_value);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-subq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-subq-invalid_argument_expression_type"),
				       new__symbol(cause, "argument"),   argument_1,
				       new__symbol(cause, "expression"), expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-subq-invalid_argument_expression_type"),
				     new__symbol(cause, "argument"),   argument_1,
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-subq-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}

f2ptr raw__expression__compile_x86__addq(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-addq-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_constant_expression(cause, argument_0)) {
    f2ptr constant_value = raw__constant_expression__constant_value(cause, argument_0);
    s64   constant_value__i = 0;
    if (raw__pointer__is_type(cause, constant_value)) {
      constant_value__i = (s64)f2pointer__p(constant_value, cause);
    } else if (raw__integer__is_type(cause, constant_value)) {
      constant_value__i = f2integer__i(constant_value, cause);
    } else if (raw__expression__is_minus_expression(cause, constant_value)) {
      f2ptr minus_expression__argument = raw__minus_expression__argument(cause, constant_value);
      if (raw__pointer__is_type(cause, minus_expression__argument)) {
	constant_value__i = -(s64)f2pointer__p(minus_expression__argument, cause);
      } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	constant_value__i = -f2integer__i(minus_expression__argument, cause);
      } else {
	return new__error(f2list8__new(cause,
				       new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-addq-invalid_constant_argument_expression_type"),
				       new__symbol(cause, "argument"),       argument_0,
				       new__symbol(cause, "constant_value"), constant_value,
				       new__symbol(cause, "expression"),     expression));
      }
    } else {
      return new__error(f2list8__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-addq-invalid_constant_argument_expression_type"),
				     new__symbol(cause, "argument"),       argument_0,
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
    if (raw__expression__is_relative_expression(cause, argument_1)) {
      f2ptr relative_offset               = raw__relative_expression__relative_offset(cause, argument_1);
      f2ptr relative_expression__argument = raw__relative_expression__argument(       cause, argument_1);
      s64   relative_offset_value = 0;
      if (raw__pointer__is_type(cause, relative_offset)) {
	relative_offset_value = (s64)f2pointer__p(relative_offset, cause);
      } else if (raw__integer__is_type(cause, relative_offset)) {
	relative_offset_value = f2integer__i(relative_offset, cause);
      } else if (raw__expression__is_minus_expression(cause, relative_offset)) {
	f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
	if (raw__pointer__is_type(cause, minus_expression__argument)) {
	  relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
	} else if (raw__integer__is_type(cause, minus_expression__argument)) {
	  relative_offset_value = -f2integer__i(minus_expression__argument, cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-addq-invalid_minus_argument_type"),
					 new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
					 new__symbol(cause, "expression"),                expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-addq-invalid_relative_offset_type"),
				       new__symbol(cause, "relative_offset"), relative_offset,
				       new__symbol(cause, "expression"),      expression));
      }
      if (raw__expression__is_register_expression(cause, relative_expression__argument)) {
	f2ptr register_name = raw__register_expression__register_name(cause, relative_expression__argument);
	if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {
	  return raw__expression__compile_x86__addq__constant__relative_rbp(cause, constant_value__i, relative_offset_value);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-addq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-addq-invalid_argument_expression_type"),
				       new__symbol(cause, "argument"),   argument_1,
				       new__symbol(cause, "expression"), expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-addq-invalid_argument_expression_type"),
				     new__symbol(cause, "argument"),   argument_1,
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-addq-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}

//  4000a2:	48 39 c0             	cmpq    %rax,%rax

f2ptr raw__expression__compile_x86__cmpq__rax__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a5:	48 39 c1             	cmpq    %rax,%rcx

f2ptr raw__expression__compile_x86__cmpq__rax__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC1);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a8:	48 39 c2             	cmpq    %rax,%rdx

f2ptr raw__expression__compile_x86__cmpq__rax__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC2);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ab:	48 39 c6             	cmpq    %rax,%rsi

f2ptr raw__expression__compile_x86__cmpq__rax__rsi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC6);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ae:	48 39 c7             	cmpq    %rax,%rdi

f2ptr raw__expression__compile_x86__cmpq__rax__rdi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC7);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b1:	49 39 c0             	cmpq    %rax,%r8

f2ptr raw__expression__compile_x86__cmpq__rax__r8(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x49);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b4:	49 39 c1             	cmpq    %rax,%r9

f2ptr raw__expression__compile_x86__cmpq__rax__r9(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x49);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC1);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b7:	48 39 c8             	cmpq    %rcx,%rax

f2ptr raw__expression__compile_x86__cmpq__rcx__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC8);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ba:	48 39 d0             	cmpq    %rdx,%rax

f2ptr raw__expression__compile_x86__cmpq__rdx__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xD0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000bd:	48 39 f0             	cmpq    %rsi,%rax

f2ptr raw__expression__compile_x86__cmpq__rsi__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xF0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000c0:	48 39 f8             	cmpq    %rdi,%rax

f2ptr raw__expression__compile_x86__cmpq__rdi__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xF8);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000c3:	4c 39 c0             	cmpq    %r8,%rax

f2ptr raw__expression__compile_x86__cmpq__r8__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x4C);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000c6:	4c 39 c8             	cmpq    %r9,%rax

f2ptr raw__expression__compile_x86__cmpq__r9__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x4C);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC8);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000be:	48 3b 45 e0          	cmp    -0x20(%rbp),%rax

f2ptr raw__expression__compile_x86__cmpq__relative_rbp__rax(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x3B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000c2:	48 3b 4d e0          	cmp    -0x20(%rbp),%rcx

f2ptr raw__expression__compile_x86__cmpq__relative_rbp__rcx(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x3B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x4D);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000c6:	48 3b 55 e0          	cmp    -0x20(%rbp),%rdx

f2ptr raw__expression__compile_x86__cmpq__relative_rbp__rdx(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x3B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x55);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000ca:	48 3b 75 e0          	cmp    -0x20(%rbp),%rsi

f2ptr raw__expression__compile_x86__cmpq__relative_rbp__rsi(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x3B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x75);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000ce:	48 3b 7d e0          	cmp    -0x20(%rbp),%rdi

f2ptr raw__expression__compile_x86__cmpq__relative_rbp__rdi(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x3B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x7D);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000d2:	4c 3b 45 e0          	cmp    -0x20(%rbp),%r8

f2ptr raw__expression__compile_x86__cmpq__relative_rbp__r8(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x4C);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x3B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000d6:	4c 3b 4d e0          	cmp    -0x20(%rbp),%r9

f2ptr raw__expression__compile_x86__cmpq__relative_rbp__r9(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x4C);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x3B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x4D);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000a2:	48 39 45 e0          	cmp    %rax,-0x20(%rbp)

f2ptr raw__expression__compile_x86__cmpq__rax__relative_rbp(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000a6:	48 39 4d e0          	cmp    %rcx,-0x20(%rbp)

f2ptr raw__expression__compile_x86__cmpq__rcx__relative_rbp(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x4D);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000aa:	48 39 55 e0          	cmp    %rdx,-0x20(%rbp)

f2ptr raw__expression__compile_x86__cmpq__rdx__relative_rbp(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x55);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000ae:	48 39 75 e0          	cmp    %rsi,-0x20(%rbp)

f2ptr raw__expression__compile_x86__cmpq__rsi__relative_rbp(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x75);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000b2:	48 39 7d e0          	cmp    %rdi,-0x20(%rbp)

f2ptr raw__expression__compile_x86__cmpq__rdi__relative_rbp(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x7D);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000b6:	4c 39 45 e0          	cmp    %r8,-0x20(%rbp)

f2ptr raw__expression__compile_x86__cmpq__r8__relative_rbp(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x4C);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

//  4000ba:	4c 39 4d e0          	cmp    %r9,-0x20(%rbp)

f2ptr raw__expression__compile_x86__cmpq__r9__relative_rbp(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128) &&
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x4C);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x39);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x4D);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
}

f2ptr raw__expression__compile_x86__cmpq(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-cmpq-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_register_expression(cause, argument_0)) {
    f2ptr register_name_0 = raw__register_expression__register_name(cause, argument_0);
    if (raw__expression__is_register_expression(cause, argument_1)) {
      f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__cmpq__rax__rax(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__cmpq__rax__rcx(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__cmpq__rax__rdx(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rsi"))) {return raw__expression__compile_x86__cmpq__rax__rsi(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdi"))) {return raw__expression__compile_x86__cmpq__rax__rdi(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "r8")))  {return raw__expression__compile_x86__cmpq__rax__r8(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "r9")))  {return raw__expression__compile_x86__cmpq__rax__r9(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rcx"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__cmpq__rcx__rax(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rdx"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__cmpq__rdx__rax(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rsi"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__cmpq__rsi__rax(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rdi"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__cmpq__rdi__rax(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "r8"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__cmpq__r8__rax(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "r9"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__cmpq__r9__rax(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    } else if (raw__expression__is_relative_expression(cause, argument_1)) {
      f2ptr relative_offset               = raw__relative_expression__relative_offset(cause, argument_1);
      f2ptr relative_expression__argument = raw__relative_expression__argument(       cause, argument_1);
      s64   relative_offset_value = 0;
      if (raw__pointer__is_type(cause, relative_offset)) {
	relative_offset_value = (s64)f2pointer__p(relative_offset, cause);
      } else if (raw__integer__is_type(cause, relative_offset)) {
	relative_offset_value = f2integer__i(relative_offset, cause);
      } else if (raw__expression__is_minus_expression(cause, relative_offset)) {
	f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
	if (raw__pointer__is_type(cause, minus_expression__argument)) {
	  relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
	} else if (raw__integer__is_type(cause, minus_expression__argument)) {
	  relative_offset_value = -f2integer__i(minus_expression__argument, cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-cmpq-invalid_minus_argument_type"),
					 new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
					 new__symbol(cause, "expression"),                expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-invalid_relative_offset_type"),
				       new__symbol(cause, "relative_offset"), relative_offset,
				       new__symbol(cause, "expression"),      expression));
      }
      if (raw__expression__is_register_expression(cause, relative_expression__argument)) {
	f2ptr register_name_1 = raw__register_expression__register_name(cause, relative_expression__argument);
	if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__cmpq__rax__relative_rbp(cause, relative_offset_value);}
	  else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else if (raw__eq(cause, register_name_0, new__symbol(cause, "rcx"))) {
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__cmpq__rcx__relative_rbp(cause, relative_offset_value);}
	  else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else if (raw__eq(cause, register_name_0, new__symbol(cause, "rdx"))) {
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__cmpq__rdx__relative_rbp(cause, relative_offset_value);}
	  else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else if (raw__eq(cause, register_name_0, new__symbol(cause, "rsi"))) {
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__cmpq__rsi__relative_rbp(cause, relative_offset_value);}
	  else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else if (raw__eq(cause, register_name_0, new__symbol(cause, "rdi"))) {
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__cmpq__rdi__relative_rbp(cause, relative_offset_value);}
	  else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else if (raw__eq(cause, register_name_0, new__symbol(cause, "r8"))) {
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__cmpq__r8__relative_rbp(cause, relative_offset_value);}
	  else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else if (raw__eq(cause, register_name_0, new__symbol(cause, "r9"))) {
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__cmpq__r9__relative_rbp(cause, relative_offset_value);}
	  else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_0,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-cmpq-invalid_argument_expression_type"),
				       new__symbol(cause, "argument"),   argument_1,
				       new__symbol(cause, "expression"), expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-cmpq-invalid_argument_expression_type"),
				     new__symbol(cause, "argument"),   argument_1,
				     new__symbol(cause, "expression"), expression));
    }
  } else if (raw__expression__is_constant_expression(cause, argument_0)) {
    f2ptr constant_value = raw__constant_expression__constant_value(cause, argument_0);
    s64   constant_value__i = 0;
    if (raw__pointer__is_type(cause, constant_value)) {
      constant_value__i = (s64)f2pointer__p(constant_value, cause);
    } else if (raw__integer__is_type(cause, constant_value)) {
      constant_value__i = f2integer__i(constant_value, cause);
    } else if (raw__expression__is_minus_expression(cause, constant_value)) {
      f2ptr minus_expression__argument = raw__minus_expression__argument(cause, constant_value);
      if (raw__pointer__is_type(cause, minus_expression__argument)) {
	constant_value__i = -(s64)f2pointer__p(minus_expression__argument, cause);
      } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	constant_value__i = -f2integer__i(minus_expression__argument, cause);
      } else {
	return new__error(f2list8__new(cause,
				       new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-cmpq-invalid_constant_argument_expression_type"),
				       new__symbol(cause, "argument"),       argument_0,
				       new__symbol(cause, "constant_value"), constant_value,
				       new__symbol(cause, "expression"),     expression));
      }
    } else {
      return new__error(f2list8__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-cmpq-invalid_constant_argument_expression_type"),
				     new__symbol(cause, "argument"),       argument_0,
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
    if (raw__expression__is_relative_expression(cause, argument_1)) {
      f2ptr relative_offset               = raw__relative_expression__relative_offset(cause, argument_1);
      f2ptr relative_expression__argument = raw__relative_expression__argument(       cause, argument_1);
      s64   relative_offset_value = 0;
      if (raw__pointer__is_type(cause, relative_offset)) {
	relative_offset_value = (s64)f2pointer__p(relative_offset, cause);
      } else if (raw__integer__is_type(cause, relative_offset)) {
	relative_offset_value = f2integer__i(relative_offset, cause);
      } else if (raw__expression__is_minus_expression(cause, relative_offset)) {
	f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
	if (raw__pointer__is_type(cause, minus_expression__argument)) {
	  relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
	} else if (raw__integer__is_type(cause, minus_expression__argument)) {
	  relative_offset_value = -f2integer__i(minus_expression__argument, cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-cmpq-invalid_minus_argument_type"),
					 new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
					 new__symbol(cause, "expression"),                expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-invalid_relative_offset_type"),
				       new__symbol(cause, "relative_offset"), relative_offset,
				       new__symbol(cause, "expression"),      expression));
      }
      if (raw__expression__is_register_expression(cause, relative_expression__argument)) {
	f2ptr register_name = raw__register_expression__register_name(cause, relative_expression__argument);
	if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {
	  return raw__expression__compile_x86__cmpq__constant__relative_rbp(cause, constant_value__i, relative_offset_value);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-cmpq-invalid_argument_expression_type"),
				       new__symbol(cause, "argument"),   argument_1,
				       new__symbol(cause, "expression"), expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-cmpq-invalid_argument_expression_type"),
				     new__symbol(cause, "argument"),   argument_1,
				     new__symbol(cause, "expression"), expression));
    }
  } else if (raw__expression__is_relative_expression(cause, argument_0)) {
    f2ptr relative_offset               = raw__relative_expression__relative_offset(cause, argument_0);
    f2ptr relative_expression__argument = raw__relative_expression__argument(       cause, argument_0);
    s64   relative_offset_value = 0;
    if (raw__pointer__is_type(cause, relative_offset)) {
      relative_offset_value = (s64)f2pointer__p(relative_offset, cause);
    } else if (raw__integer__is_type(cause, relative_offset)) {
      relative_offset_value = f2integer__i(relative_offset, cause);
    } else if (raw__expression__is_minus_expression(cause, relative_offset)) {
      f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
      if (raw__pointer__is_type(cause, minus_expression__argument)) {
	relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
      } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	relative_offset_value = -f2integer__i(minus_expression__argument, cause);
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-cmpq-invalid_minus_argument_type"),
				       new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
				       new__symbol(cause, "expression"),                expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmpq-invalid_relative_offset_type"),
				     new__symbol(cause, "relative_offset"), relative_offset,
				     new__symbol(cause, "expression"),      expression));
    }
    if (raw__expression__is_register_expression(cause, relative_expression__argument)) {
      f2ptr register_name = raw__register_expression__register_name(cause, relative_expression__argument);
      if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {
	if (raw__expression__is_register_expression(cause, argument_1)) {
	  f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
	  if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__cmpq__relative_rbp__rax(cause, relative_offset_value);}
	  else if (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__cmpq__relative_rbp__rcx(cause, relative_offset_value);}
	  else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__cmpq__relative_rbp__rdx(cause, relative_offset_value);}
	  else if (raw__eq(cause, register_name_1, new__symbol(cause, "rsi"))) {return raw__expression__compile_x86__cmpq__relative_rbp__rsi(cause, relative_offset_value);}
	  else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdi"))) {return raw__expression__compile_x86__cmpq__relative_rbp__rdi(cause, relative_offset_value);}
	  else if (raw__eq(cause, register_name_1, new__symbol(cause, "r8")))  {return raw__expression__compile_x86__cmpq__relative_rbp__r8( cause, relative_offset_value);}
	  else if (raw__eq(cause, register_name_1, new__symbol(cause, "r9")))  {return raw__expression__compile_x86__cmpq__relative_rbp__r9( cause, relative_offset_value);}
	  else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-cmpq-invalid_argument_expression_type"),
					 new__symbol(cause, "argument"),   argument_1,
					 new__symbol(cause, "expression"), expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmpq-unknown_register"),
				       new__symbol(cause, "register_name"), register_name,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-cmpq-invalid_argument_expression_type"),
				     new__symbol(cause, "argument"),   argument_0,
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-cmpq-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}


f2ptr raw__expression__compile_x86__cmp(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-cmp-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_relative_expression(cause, argument_0)) {
    f2ptr relative_offset               = raw__relative_expression__relative_offset(cause, argument_0);
    f2ptr relative_expression__argument = raw__relative_expression__argument(       cause, argument_0);
    s64   relative_offset_value = 0;
    if (raw__pointer__is_type(cause, relative_offset)) {
      relative_offset_value = (s64)f2pointer__p(relative_offset, cause);
    } else if (raw__integer__is_type(cause, relative_offset)) {
      relative_offset_value = f2integer__i(relative_offset, cause);
    } else if (raw__expression__is_minus_expression(cause, relative_offset)) {
      f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
      if (raw__pointer__is_type(cause, minus_expression__argument)) {
	relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
      } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	relative_offset_value = -f2integer__i(minus_expression__argument, cause);
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-cmp-invalid_minus_argument_type"),
				       new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
				       new__symbol(cause, "expression"),                expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-cmp-invalid_relative_offset_type"),
				     new__symbol(cause, "relative_offset"), relative_offset,
				     new__symbol(cause, "expression"),      expression));
    }
    if (raw__expression__is_register_expression(cause, relative_expression__argument)) {
      f2ptr register_name_0 = raw__register_expression__register_name(cause, relative_expression__argument);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "rbp"))) {
	if (raw__expression__is_register_expression(cause, argument_1)) {
	  f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	    return raw__expression__compile_x86__cmp__relative_rbp__rax(cause, relative_offset_value);
	  } else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmp-unknown_register"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-cmp-invalid_argument_expression_type"),
					 new__symbol(cause, "argument"),   argument_0,
					 new__symbol(cause, "expression"), expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-cmp-unknown_register"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-cmp-invalid_argument_expression_type"),
				     new__symbol(cause, "argument"),   argument_1,
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-cmp-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}









//  4000b6:	66 48 0f 6e c0       	movq   %rax,%xmm0

f2ptr raw__expression__compile_x86__movq__rax__xmm0(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 5);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x66);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x6E);
  raw__chunk__bit8__elt__set(cause, chunk, 4, 0xC0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000bb:	66 48 0f 6e c1       	movq   %rcx,%xmm0

f2ptr raw__expression__compile_x86__movq__rcx__xmm0(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 5);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x66);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x6E);
  raw__chunk__bit8__elt__set(cause, chunk, 4, 0xC1);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000c0:	66 48 0f 6e c2       	movq   %rdx,%xmm0

f2ptr raw__expression__compile_x86__movq__rdx__xmm0(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 5);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x66);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x6E);
  raw__chunk__bit8__elt__set(cause, chunk, 4, 0xC2);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000c5:	66 48 0f 6e c8       	movq   %rax,%xmm1

f2ptr raw__expression__compile_x86__movq__rax__xmm1(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 5);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x66);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x6E);
  raw__chunk__bit8__elt__set(cause, chunk, 4, 0xC8);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ca:	66 48 0f 6e c9       	movq   %rcx,%xmm1

f2ptr raw__expression__compile_x86__movq__rcx__xmm1(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 5);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x66);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x6E);
  raw__chunk__bit8__elt__set(cause, chunk, 4, 0xC9);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000cf:	66 48 0f 6e ca       	movq   %rdx,%xmm1

f2ptr raw__expression__compile_x86__movq__rdx__xmm1(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 5);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x66);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x6E);
  raw__chunk__bit8__elt__set(cause, chunk, 4, 0xCA);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000d4:	66 48 0f 7e c0       	movq   %xmm0,%rax

f2ptr raw__expression__compile_x86__movq__xmm0__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 5);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x66);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x7E);
  raw__chunk__bit8__elt__set(cause, chunk, 4, 0xC0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000d9:	66 48 0f 7e c1       	movq   %xmm0,%rcx

f2ptr raw__expression__compile_x86__movq__xmm0__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 5);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x66);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x7E);
  raw__chunk__bit8__elt__set(cause, chunk, 4, 0xC1);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000de:	66 48 0f 7e c2       	movq   %xmm0,%rdx

f2ptr raw__expression__compile_x86__movq__xmm0__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 5);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x66);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x7E);
  raw__chunk__bit8__elt__set(cause, chunk, 4, 0xC2);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000e3:	66 48 0f 7e c8       	movq   %xmm1,%rax

f2ptr raw__expression__compile_x86__movq__xmm1__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 5);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x66);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x7E);
  raw__chunk__bit8__elt__set(cause, chunk, 4, 0xC8);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000e8:	66 48 0f 7e c9       	movq   %xmm1,%rcx

f2ptr raw__expression__compile_x86__movq__xmm1__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 5);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x66);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x7E);
  raw__chunk__bit8__elt__set(cause, chunk, 4, 0xC9);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ed:	66 48 0f 7e ca       	movq   %xmm1,%rdx

f2ptr raw__expression__compile_x86__movq__xmm1__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 5);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x66);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x7E);
  raw__chunk__bit8__elt__set(cause, chunk, 4, 0xCA);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__movq(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movq-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_register_expression(cause, argument_0)) {
    f2ptr register_name_0 = raw__register_expression__register_name(cause, argument_0);
    if (raw__expression__is_register_expression(cause, argument_1)) {
      f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "xmm0"))) {return raw__expression__compile_x86__movq__rax__xmm0(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "xmm1"))) {return raw__expression__compile_x86__movq__rax__xmm1(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_0,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rcx"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "xmm0"))) {return raw__expression__compile_x86__movq__rcx__xmm0(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "xmm1"))) {return raw__expression__compile_x86__movq__rcx__xmm1(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_0,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rdx"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "xmm0"))) {return raw__expression__compile_x86__movq__rdx__xmm0(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "xmm1"))) {return raw__expression__compile_x86__movq__rdx__xmm1(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_0,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "xmm0"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__movq__xmm0__rax(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__movq__xmm0__rcx(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__movq__xmm0__rdx(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_0,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "xmm1"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__movq__xmm1__rax(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__movq__xmm1__rcx(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__movq__xmm1__rdx(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name_0,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movq-unknown_register"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movq-invalid_argument_expression_type"),
				     new__symbol(cause, "argument"),   argument_1,
				     new__symbol(cause, "expression"), expression));
    }
  } else if (raw__expression__is_constant_expression(cause, argument_0)) {
    f2ptr constant_value = raw__constant_expression__constant_value(cause, argument_0);
    s64   constant_value__i = 0;
    if (raw__pointer__is_type(cause, constant_value)) {
      constant_value__i = (s64)f2pointer__p(constant_value, cause);
    } else if (raw__integer__is_type(cause, constant_value)) {
      constant_value__i = f2integer__i(constant_value, cause);
    } else if (raw__expression__is_minus_expression(cause, constant_value)) {
      f2ptr minus_expression__argument = raw__minus_expression__argument(cause, constant_value);
      if (raw__pointer__is_type(cause, minus_expression__argument)) {
	constant_value__i = -(s64)f2pointer__p(minus_expression__argument, cause);
      } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	constant_value__i = -f2integer__i(minus_expression__argument, cause);
      } else {
	return new__error(f2list8__new(cause,
				       new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-movq-invalid_constant_argument_expression_type"),
				       new__symbol(cause, "argument"),       argument_0,
				       new__symbol(cause, "constant_value"), constant_value,
				       new__symbol(cause, "expression"),     expression));
      }
    } else {
      return new__error(f2list8__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-movq-invalid_constant_argument_expression_type"),
				     new__symbol(cause, "argument"),       argument_0,
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
    if (raw__expression__is_relative_expression(cause, argument_1)) {
      f2ptr relative_offset               = raw__relative_expression__relative_offset(cause, argument_1);
      f2ptr relative_expression__argument = raw__relative_expression__argument(       cause, argument_1);
      s64   relative_offset_value = 0;
      if (raw__pointer__is_type(cause, relative_offset)) {
	relative_offset_value = (s64)f2pointer__p(relative_offset, cause);
      } else if (raw__integer__is_type(cause, relative_offset)) {
	relative_offset_value = f2integer__i(relative_offset, cause);
      } else if (raw__expression__is_minus_expression(cause, relative_offset)) {
	f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
	if (raw__pointer__is_type(cause, minus_expression__argument)) {
	  relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
	} else if (raw__integer__is_type(cause, minus_expression__argument)) {
	  relative_offset_value = -f2integer__i(minus_expression__argument, cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-movq-invalid_minus_argument_type"),
					 new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
					 new__symbol(cause, "expression"),                expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-movq-invalid_relative_offset_type"),
				       new__symbol(cause, "relative_offset"), relative_offset,
				       new__symbol(cause, "expression"),      expression));
      }
      if (raw__expression__is_register_expression(cause, relative_expression__argument)) {
	f2ptr register_name = raw__register_expression__register_name(cause, relative_expression__argument);
	if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {
	  return raw__expression__compile_x86__movq__constant__relative_rbp(cause, constant_value__i, relative_offset_value);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movq-unknown_register"),
					 new__symbol(cause, "register_name"), register_name,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movq-invalid_argument_expression_type"),
				       new__symbol(cause, "argument"),   argument_1,
				       new__symbol(cause, "expression"), expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movq-invalid_argument_expression_type"),
				     new__symbol(cause, "argument"),   argument_1,
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movq-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}




f2ptr raw__expression__compile_x86__jmp__relative(f2ptr cause, s64 relative_jump_distance) {
  if ((relative_jump_distance <   128) &&
      (relative_jump_distance >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 2);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0xEB);
    raw__chunk__bit8__elt__set(cause, chunk, 1, (u8)((signed char)relative_jump_distance));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-jmp-relative_rax-rax-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_jump_distance)));
  }
}

f2ptr raw__expression__compile_x86__jb__relative(f2ptr cause, s64 relative_jump_distance) {
  if ((relative_jump_distance <   128) &&
      (relative_jump_distance >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 2);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x72);
    raw__chunk__bit8__elt__set(cause, chunk, 1, (u8)((signed char)relative_jump_distance));
    return f2__machine_code_chunk__new(cause, chunk);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-jb-relative_rax-rax-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_jump_distance)));
  }
}

boolean_t raw__expression__is_label_expression(f2ptr cause, f2ptr expression) {
  if (! raw__cons__is_type(cause, expression)) {
    return boolean__false;
  }
  f2ptr command = f2cons__car(expression, cause);
  if (! raw__eq(cause, command, new__symbol(cause, "label"))) {
    return boolean__false;
  }
  if (raw__simple_length(cause, expression) != 2) {
    return boolean__false;
  }
  return boolean__true;
}

f2ptr raw__label_expression__label_name(f2ptr cause, f2ptr expression) {
  f2ptr label_name = f2cons__car(f2cons__cdr(expression, cause), cause);
  return label_name;
}


f2ptr raw__expression__compile_x86__movabs(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-mov-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr cdr        = f2cons__cdr(expression, cause);
  f2ptr cddr       = f2cons__cdr(cdr,        cause);
  f2ptr argument_0 = f2cons__car(cdr,        cause);
  f2ptr argument_1 = f2cons__car(cddr,       cause);
  if (raw__expression__is_constant_expression(cause, argument_0)) {
    f2ptr constant_value    = raw__constant_expression__constant_value(cause, argument_0);
    u64   constant_value__p = 0;
    if (raw__pointer__is_type(cause, constant_value)) {
      constant_value__p = f2pointer__p(constant_value, cause);
    } else if (raw__integer__is_type(cause, constant_value)) {
      constant_value__p = f2integer__i(constant_value, cause);
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-movabs-constant_value_must_be_pointer_or_integer"),
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
    if (raw__expression__is_register_expression(cause, argument_1)) {
      f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
      if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__movabs__constant_rax(cause, constant_value__p);}
      else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdi"))) {return raw__expression__compile_x86__movabs__constant_rdi(cause, constant_value__p);}
      else if (raw__eq(cause, register_name_1, new__symbol(cause, "rsi"))) {return raw__expression__compile_x86__movabs__constant_rsi(cause, constant_value__p);}
      else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__movabs__constant_rdx(cause, constant_value__p);}
      else if (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__movabs__constant_rcx(cause, constant_value__p);}
      else if (raw__eq(cause, register_name_1, new__symbol(cause, "r8")))  {return raw__expression__compile_x86__movabs__constant_r8( cause, constant_value__p);}
      else if (raw__eq(cause, register_name_1, new__symbol(cause, "r9")))  {return raw__expression__compile_x86__movabs__constant_r9( cause, constant_value__p);}
      else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movabs-unknown_register_name"),
				       new__symbol(cause, "register_name"), register_name_1,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movabs-invalid_argument_expression_type"),
				     new__symbol(cause, "expression"), expression));
    }
  } else if (raw__expression__is_label_expression(cause, argument_0)) {
    f2ptr label_name           = raw__label_expression__label_name(cause, argument_0);
    u64   label_constant_value = 0;
    if (raw__expression__is_register_expression(cause, argument_1)) {
      f2ptr register_name_1    = raw__register_expression__register_name(cause, argument_1);
      f2ptr machine_code_chunk = nil;
      if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {machine_code_chunk = raw__expression__compile_x86__movabs__constant_rax(cause, label_constant_value);}
      else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdi"))) {machine_code_chunk = raw__expression__compile_x86__movabs__constant_rdi(cause, label_constant_value);}
      else if (raw__eq(cause, register_name_1, new__symbol(cause, "rsi"))) {machine_code_chunk = raw__expression__compile_x86__movabs__constant_rsi(cause, label_constant_value);}
      else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {machine_code_chunk = raw__expression__compile_x86__movabs__constant_rdx(cause, label_constant_value);}
      else if (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {machine_code_chunk = raw__expression__compile_x86__movabs__constant_rcx(cause, label_constant_value);}
      else if (raw__eq(cause, register_name_1, new__symbol(cause, "r8")))  {machine_code_chunk = raw__expression__compile_x86__movabs__constant_r8( cause, label_constant_value);}
      else if (raw__eq(cause, register_name_1, new__symbol(cause, "r9")))  {machine_code_chunk = raw__expression__compile_x86__movabs__constant_r9( cause, label_constant_value);}
      else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movabs-unknown_register_name"),
				       new__symbol(cause, "register_name"), register_name_1,
				       new__symbol(cause, "expression"),    expression));
      }
      f2ptr machine_code_jump__index     = f2integer__new(cause, 0);
      f2ptr machine_code_jump__command   = new__symbol(cause, "movabs");
      f2ptr machine_code_jump__label     = label_name;
      f2ptr machine_code_jump__arguments = f2list1__new(cause, register_name_1);
      f2ptr machine_code_jump            = raw__machine_code_jump__new(cause, machine_code_jump__index, machine_code_jump__command, machine_code_jump__label, machine_code_jump__arguments);
      f2machine_code_chunk__jumps__set(machine_code_chunk, cause, f2cons__new(cause, machine_code_jump, f2machine_code_chunk__jumps(machine_code_chunk, cause)));
      return machine_code_chunk;
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movabs-invalid_argument_expression_type"),
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movabs-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}

f2ptr raw__expression__compile_x86__jmp(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jmp-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 = f2cons__car(f2cons__cdr(expression, cause), cause);
  s64 relative_jump_distance = 0;
  if (raw__pointer__is_type(cause, argument_0)) {
    relative_jump_distance = (s64)f2pointer__p(argument_0, cause);
  } else if (raw__integer__is_type(cause, argument_0)) {
    relative_jump_distance = f2integer__i(argument_0, cause);
  } else if (raw__expression__is_minus_expression(cause, argument_0)) {
    f2ptr minus_expression__argument = raw__minus_expression__argument(cause, argument_0);
    if (raw__pointer__is_type(cause, minus_expression__argument)) {
      relative_jump_distance = -(s64)f2pointer__p(minus_expression__argument, cause);
    } else if (raw__integer__is_type(cause, minus_expression__argument)) {
      relative_jump_distance = -f2integer__i(minus_expression__argument, cause);
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-jmp-invalid_minus_expression_argument_expression_type"),
				     new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
				     new__symbol(cause, "expression"),                expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jmp-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
  return raw__expression__compile_x86__jmp__relative(cause, relative_jump_distance);
}

f2ptr raw__expression__compile_x86__jb(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jb-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 = f2cons__car(f2cons__cdr(expression, cause), cause);
  s64 relative_jump_distance = 0;
  if (raw__pointer__is_type(cause, argument_0)) {
    relative_jump_distance = (s64)f2pointer__p(argument_0, cause);
  } else if (raw__integer__is_type(cause, argument_0)) {
    relative_jump_distance = f2integer__i(argument_0, cause);
  } else if (raw__expression__is_minus_expression(cause, argument_0)) {
    f2ptr minus_expression__argument = raw__minus_expression__argument(cause, argument_0);
    if (raw__pointer__is_type(cause, minus_expression__argument)) {
      relative_jump_distance = -(s64)f2pointer__p(minus_expression__argument, cause);
    } else if (raw__integer__is_type(cause, minus_expression__argument)) {
      relative_jump_distance = -f2integer__i(minus_expression__argument, cause);
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-jb-invalid_minus_expression_argument_expression_type"),
				     new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
				     new__symbol(cause, "expression"),                expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jb-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
  return raw__expression__compile_x86__jb__relative(cause, relative_jump_distance);
}

//  4000a2:	48 d3 e0             	shl    %cl,%rax

f2ptr raw__expression__compile_x86__shl__cl__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xD3);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xE0);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__shl(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-shl-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_register_expression(cause, argument_0)) {
    f2ptr register_name_0 = raw__register_expression__register_name(cause, argument_0);
    if (raw__expression__is_register_expression(cause, argument_1)) {
      f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "cl"))) {
	if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	  return raw__expression__compile_x86__shl__cl__rax(cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-shl-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-shl-unknown_register_name"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-shl-invalid_argument_expression_type"),
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-shl-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}

//  4000a2:	48 d3 e8             	shr    %cl,%rax

f2ptr raw__expression__compile_x86__shr__cl__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xD3);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xE8);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__shr(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-shr-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_register_expression(cause, argument_0)) {
    f2ptr register_name_0 = raw__register_expression__register_name(cause, argument_0);
    if (raw__expression__is_register_expression(cause, argument_1)) {
      f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "cl"))) {
	if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	  return raw__expression__compile_x86__shr__cl__rax(cause);
	} else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-shr-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-shr-unknown_register_name"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-shr-invalid_argument_expression_type"),
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-shr-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}

//  4000a2:	48 29 c1             	sub    %rax,%rcx

f2ptr raw__expression__compile_x86__sub__rax__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x29);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC1);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a5:	48 29 c2             	sub    %rax,%rdx

f2ptr raw__expression__compile_x86__sub__rax__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x29);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC2);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a8:	48 29 c8             	sub    %rcx,%rax

f2ptr raw__expression__compile_x86__sub__rcx__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x29);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC8);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ab:	48 29 ca             	sub    %rcx,%rdx

f2ptr raw__expression__compile_x86__sub__rcx__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x29);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xCA);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ae:	48 29 d0             	sub    %rdx,%rax

f2ptr raw__expression__compile_x86__sub__rdx__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x29);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xD0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b1:	48 29 d1             	sub    %rdx,%rcx

f2ptr raw__expression__compile_x86__sub__rdx__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x29);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xD1);
  return f2__machine_code_chunk__new(cause, chunk);
}



f2ptr raw__expression__compile_x86__sub(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-sub-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_register_expression(cause, argument_0)) {
    f2ptr register_name_0 = raw__register_expression__register_name(cause, argument_0);
    if (raw__expression__is_register_expression(cause, argument_1)) {
      f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__sub__rax__rcx(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__sub__rax__rdx(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-sub-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rcx"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__sub__rcx__rax(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__sub__rcx__rdx(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-sub-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rdx"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__sub__rdx__rax(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__sub__rdx__rcx(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-sub-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-sub-unknown_register_name"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-sub-invalid_argument_expression_type"),
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-sub-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}

//  4000a2:	48 0f af c8          	imul   %rax,%rcx

f2ptr raw__expression__compile_x86__imul__rax__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 4);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xAF);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0xC8);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a6:	48 0f af d0          	imul   %rax,%rdx

f2ptr raw__expression__compile_x86__imul__rax__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 4);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xAF);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0xD0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000aa:	48 0f af c1          	imul   %rcx,%rax

f2ptr raw__expression__compile_x86__imul__rcx__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 4);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xAF);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0xC1);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ae:	48 0f af d1          	imul   %rcx,%rdx

f2ptr raw__expression__compile_x86__imul__rcx__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 4);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xAF);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0x41);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b2:	48 0f af c2          	imul   %rdx,%rax

f2ptr raw__expression__compile_x86__imul__rdx__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 4);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xAF);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0xC2);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b6:	48 0f af ca          	imul   %rdx,%rcx

f2ptr raw__expression__compile_x86__imul__rdx__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 4);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xAF);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0xCA);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__imul(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-imul-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_register_expression(cause, argument_0)) {
    f2ptr register_name_0 = raw__register_expression__register_name(cause, argument_0);
    if (raw__expression__is_register_expression(cause, argument_1)) {
      f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__imul__rax__rcx(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__imul__rax__rdx(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-imul-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rcx"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__imul__rcx__rax(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__imul__rcx__rdx(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-imul-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rdx"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__imul__rdx__rax(cause);}
	else if (raw__eq(cause, register_name_1, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__imul__rdx__rcx(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-imul-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-imul-unknown_register_name"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-imul-invalid_argument_expression_type"),
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-imul-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}

//  4000a2:	48 c1 f8 3f          	sar    $0x3f,%rax

f2ptr raw__expression__compile_x86__sar__constant__rax(f2ptr cause, u8 constant) {
  f2ptr chunk = raw__chunk__new(cause, 4);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xC1);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xF8);
  raw__chunk__bit8__elt__set(cause, chunk, 3, constant);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a6:	48 c1 f9 3f          	sar    $0x3f,%rcx

f2ptr raw__expression__compile_x86__sar__constant__rcx(f2ptr cause, u8 constant) {
  f2ptr chunk = raw__chunk__new(cause, 4);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xC1);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xF9);
  raw__chunk__bit8__elt__set(cause, chunk, 3, constant);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000aa:	48 c1 fa 3f          	sar    $0x3f,%rdx

f2ptr raw__expression__compile_x86__sar__constant__rdx(f2ptr cause, u8 constant) {
  f2ptr chunk = raw__chunk__new(cause, 4);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xC1);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xFA);
  raw__chunk__bit8__elt__set(cause, chunk, 3, constant);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__sar(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-sar-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_constant_expression(cause, argument_0)) {
    f2ptr constant_value    = raw__constant_expression__constant_value(cause, argument_0);
    s64   constant_value__i = 0;
    if (raw__integer__is_type(cause, constant_value)) {
      constant_value__i = f2integer__i(constant_value, cause);
    } else if (raw__pointer__is_type(cause, constant_value)) {
      constant_value__i = (s64)f2pointer__p(constant_value, cause);
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-sar-constant_number_must_be_integer_or_pointer"),
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
    if (raw__expression__is_register_expression(cause, argument_1)) {
      f2ptr register_name = raw__register_expression__register_name(cause, argument_1);
      if      (raw__eq(cause, register_name, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__sar__constant__rax(cause, constant_value__i);}
      else if (raw__eq(cause, register_name, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__sar__constant__rcx(cause, constant_value__i);}
      else if (raw__eq(cause, register_name, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__sar__constant__rdx(cause, constant_value__i);}
      else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-sar-unknown_register_name"),
				       new__symbol(cause, "register_name"), register_name,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-sar-invalid_argument_expression_type"),
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-sar-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}

//  4000a2:	48 f7 f8             	idiv   %rax

f2ptr raw__expression__compile_x86__idivq__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xF7);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xF8);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a5:	48 f7 f9             	idiv   %rcx

f2ptr raw__expression__compile_x86__idivq__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xF7);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xF9);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a8:	48 f7 fa             	idiv   %rdx

f2ptr raw__expression__compile_x86__idivq__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xF7);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xFA);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__idivq(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-idivq-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument = f2cons__car(f2cons__cdr(expression, cause), cause);
  if (raw__expression__is_register_expression(cause, argument)) {
    f2ptr register_name = raw__register_expression__register_name(cause, argument);
    if      (raw__eq(cause, register_name, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__idivq__rax(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__idivq__rcx(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__idivq__rdx(cause);}
    else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-idivq-unknown_register_name"),
				       new__symbol(cause, "register_name"), register_name,
				       new__symbol(cause, "expression"),    expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-idivq-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}

//  4000a2:	f2 0f 58 c8          	addsd  %xmm0,%xmm1

f2ptr raw__expression__compile_x86__addsd__xmm0__xmm1(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 4);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0xF2);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x58);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0xC8);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a6:	f2 0f 58 c1          	addsd  %xmm1,%xmm0

f2ptr raw__expression__compile_x86__addsd__xmm1__xmm0(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 4);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0xF2);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x58);
  raw__chunk__bit8__elt__set(cause, chunk, 3, 0xC1);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__addsd(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 3) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-addsd-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 =             f2cons__car(f2cons__cdr(expression, cause), cause);
  f2ptr argument_1 = f2cons__car(f2cons__cdr(f2cons__cdr(expression, cause), cause), cause);
  if (raw__expression__is_register_expression(cause, argument_0)) {
    f2ptr register_name_0 = raw__register_expression__register_name(cause, argument_0);
    if (raw__expression__is_register_expression(cause, argument_1)) {
      f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
      if (raw__eq(cause, register_name_0, new__symbol(cause, "xmm0"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "xmm1"))) {return raw__expression__compile_x86__addsd__xmm0__xmm1(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-addsd-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "xmm1"))) {
	if      (raw__eq(cause, register_name_1, new__symbol(cause, "xmm0"))) {return raw__expression__compile_x86__addsd__xmm1__xmm0(cause);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-addsd-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-addsd-unknown_register_name"),
				       new__symbol(cause, "register_name"), register_name_0,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-addsd-invalid_argument_expression_type"),
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-addsd-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}

//  4000a2:	ff d0                	callq  *%rax

f2ptr raw__expression__compile_x86__callq__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xD0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a4:	ff d1                	callq  *%rcx

f2ptr raw__expression__compile_x86__callq__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xD1);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a6:	ff d2                	callq  *%rdx

f2ptr raw__expression__compile_x86__callq__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xD2);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__callq(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-callq-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument = f2cons__car(f2cons__cdr(expression, cause), cause);
  if (raw__expression__is_register_expression(cause, argument)) {
    f2ptr register_name = raw__register_expression__register_name(cause, argument);
    if (raw__eq(cause, register_name, new__symbol(cause, "rax"))) {
      return raw__expression__compile_x86__callq__rax(cause);
    } else if (raw__eq(cause, register_name, new__symbol(cause, "rcx"))) {
      return raw__expression__compile_x86__callq__rcx(cause);
    } else if (raw__eq(cause, register_name, new__symbol(cause, "rdx"))) {
      return raw__expression__compile_x86__callq__rdx(cause);
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-callq-unknown_register_name"),
				     new__symbol(cause, "register_name"), register_name,
				     new__symbol(cause, "expression"),    expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-callq-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}

//  4000a2:	48 ff c0             	incq    %rax

f2ptr raw__expression__compile_x86__incq__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a5:	48 ff c1             	incq    %rcx

f2ptr raw__expression__compile_x86__incq__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC1);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a8:	48 ff c2             	incq    %rdx

f2ptr raw__expression__compile_x86__incq__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC2);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ab:	48 ff c6             	incq    %rsi

f2ptr raw__expression__compile_x86__incq__rsi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC6);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000ae:	48 ff c7             	incq    %rdi

f2ptr raw__expression__compile_x86__incq__rdi(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC7);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b1:	49 ff c0             	incq    %r8

f2ptr raw__expression__compile_x86__incq__r8(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x49);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000b4:	49 ff c1             	incq    %r9

f2ptr raw__expression__compile_x86__incq__r9(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x49);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC1);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a2:	48 ff 45 e0          	incq   -0x20(%rbp)

f2ptr raw__expression__compile_x86__incq__relative_rbp(f2ptr cause, s64 relative_offset) {
  if ((relative_offset >= -128)
      (relative_offset <   128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0xFF);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
    raw__chunk__bit8__elt__set(cause, chunk, 3, relative_offset);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-incq-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset)));
  }
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__incq(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-incq-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument = f2cons__car(f2cons__cdr(expression, cause), cause);
  if (raw__expression__is_register_expression(cause, argument)) {
    f2ptr register_name = raw__register_expression__register_name(cause, argument);
    if      (raw__eq(cause, register_name, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__incq__rax(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__incq__rcx(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__incq__rdx(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rsi"))) {return raw__expression__compile_x86__incq__rsi(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rdi"))) {return raw__expression__compile_x86__incq__rdi(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "r8")))  {return raw__expression__compile_x86__incq__r8( cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "r9")))  {return raw__expression__compile_x86__incq__r9( cause);}
    else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-incq-unknown_register_name"),
				     new__symbol(cause, "register_name"), register_name,
				     new__symbol(cause, "expression"),    expression));
    }
  } else if (raw__expression__is_relative_expression(cause, argument)) {
    f2ptr relative_offset               = raw__relative_expression__relative_offset(cause, argument);
    f2ptr relative_expression__argument = raw__relative_expression__argument(       cause, argument);
    s64   relative_offset_value = 0;
    if (raw__pointer__is_type(cause, relative_offset)) {
      relative_offset_value = (s64)f2pointer__p(relative_offset, cause);
    } else if (raw__integer__is_type(cause, relative_offset)) {
      relative_offset_value = f2integer__i(relative_offset, cause);
    } else if (raw__expression__is_minus_expression(cause, relative_offset)) {
      f2ptr minus_expression__argument = raw__minus_expression__argument(cause, relative_offset);
      if (raw__pointer__is_type(cause, minus_expression__argument)) {
	relative_offset_value = -((s64)f2pointer__p(minus_expression__argument, cause));
      } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	relative_offset_value = -f2integer__i(minus_expression__argument, cause);
      } else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-movq-invalid_minus_argument_type"),
				       new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
				       new__symbol(cause, "expression"),                expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-movq-invalid_relative_offset_type"),
				     new__symbol(cause, "relative_offset"), relative_offset,
				     new__symbol(cause, "expression"),      expression));
    }
    if (raw__expression__is_register_expression(cause, relative_expression__argument)) {
      f2ptr register_name = raw__register_expression__register_name(cause, relative_expression__argument);
      if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__incq__relative_rbp(cause, relative_offset_value);}
      else {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-movq-unknown_register"),
				       new__symbol(cause, "register_name"), register_name,
				       new__symbol(cause, "expression"),    expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-movq-invalid_argument_expression_type"),
				     new__symbol(cause, "argument"),   argument,
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-incq-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}


f2ptr raw__expression__compile_x86__leaveq__chunk(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0xC9);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__leaveq(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 1) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-leaveq-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  return raw__expression__compile_x86__leaveq__chunk(cause);
}

//  4000a2:	ff e0                	jmpq   *%rax

f2ptr raw__expression__compile_x86__jmpq__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xE0);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a4:	ff e1                	jmpq   *%rcx

f2ptr raw__expression__compile_x86__jmpq__rcx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xE1);
  return f2__machine_code_chunk__new(cause, chunk);
}

//  4000a6:	ff e2                	jmpq   *%rdx

f2ptr raw__expression__compile_x86__jmpq__rdx(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 2);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xE2);
  return f2__machine_code_chunk__new(cause, chunk);
}

f2ptr raw__expression__compile_x86__jmpq(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jmpq-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument = f2cons__car(f2cons__cdr(expression, cause), cause);
  if (raw__expression__is_register_expression(cause, argument)) {
    f2ptr register_name = raw__register_expression__register_name(cause, argument);
    if      (raw__eq(cause, register_name, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__jmpq__rax(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rcx"))) {return raw__expression__compile_x86__jmpq__rcx(cause);}
    else if (raw__eq(cause, register_name, new__symbol(cause, "rdx"))) {return raw__expression__compile_x86__jmpq__rdx(cause);}
    else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-jmpq-unknown_register_name"),
				     new__symbol(cause, "register_name"), register_name,
				     new__symbol(cause, "expression"),    expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jmpq-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
}



f2ptr raw__expression__compile_x86__integer(f2ptr cause, f2ptr expression) {
  f2ptr pointer = f2pointer__new(cause, f2integer__i(expression, cause));
  return raw__expression__compile_x86(cause, f2list3__new(cause, new__symbol(cause, "movabs"), f2list2__new(cause, new__symbol(cause, "constant"), pointer), f2list2__new(cause, new__symbol(cause, "register"), new__symbol(cause, "rax"))));
}

f2ptr raw__expression__compile_x86__pointer(f2ptr cause, f2ptr expression) {
  return raw__expression__compile_x86(cause, f2list3__new(cause, new__symbol(cause, "movabs"), f2list2__new(cause, new__symbol(cause, "constant"), expression), f2list2__new(cause, new__symbol(cause, "register"), new__symbol(cause, "rax"))));
}

boolean_t raw__expression__is_funkvar_expression(f2ptr cause, f2ptr expression) {
  if (raw__cons__is_type(cause, expression)) {
    f2ptr command = f2cons__car(expression, cause);
    if (raw__eq(cause, command, new__symbol(cause, "funkvar"))) {
      if (raw__simple_length(cause, expression) == 2) {
	return boolean__true;
      }
    }
  }
  return boolean__false;
}

f2ptr raw__funkvar_expression__funkvar_name(f2ptr cause, f2ptr expression) {
  return f2cons__car(f2cons__cdr(expression, cause), cause);
}

f2ptr raw__expression__compile_x86__funkall(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) < 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-funkall-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 = f2cons__car(f2cons__cdr(expression, cause), cause);
  if (raw__expression__is_funkvar_expression(cause, argument_0)) {
    f2ptr funktion_name = raw__funkvar_expression__funkvar_name(cause, argument_0);
    f2ptr fiber         = f2__this__fiber(cause);
    f2ptr funktion      = assert_value(f2__fiber__lookup_type_variable_value(cause, fiber, __funk2.primobject__frame.funk_variable__symbol, funktion_name));
    if (raw__x86_funk__is_type(cause, funktion)) {
      f2ptr variables                = f2x86_funk__variables(               funktion, cause);
      u64   variables__length        = raw__simple_length(cause, variables);
      f2ptr arguments                = f2cons__cdr(f2cons__cdr(expression, cause), cause);
      u64   arguments__length        = raw__simple_length(cause, arguments);
      if (variables__length != arguments__length) {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-funkall-wrong_number_of_arguments_to_x86_funk"),
				       new__symbol(cause, "funktion"),   funktion,
				       new__symbol(cause, "expression"), expression));
      }
      f2ptr compiled_argument_chunks = nil;
      {
	s64   argument_index                = 0;
	f2ptr argument_iter                 = arguments;
	f2ptr compiled_argument_chunks_iter = nil;
	while (argument_iter != nil) {
	  f2ptr argument = f2cons__car(argument_iter, cause);
	  {
	    {
	      f2ptr compiled_argument_chunk = catch_value(raw__expression__compile_x86(cause, argument),
							  f2list4__new(cause,
								       new__symbol(cause, "bug_name"), new__symbol(cause, "expression-compile_x86-funkall-error_compiling_argument"),
								       new__symbol(cause, "argument"), argument));
	      f2ptr new_cons                = f2cons__new(cause, compiled_argument_chunk, nil);
	      if (compiled_argument_chunks == nil) {
		compiled_argument_chunks = new_cons;
	      } else {
		f2cons__cdr__set(compiled_argument_chunks_iter, cause, new_cons);
	      }
	      compiled_argument_chunks_iter = new_cons;
	    }
	    {
	      f2ptr new_chunk = nil;
	      switch (argument_index) {
	      case 0: new_chunk = raw__expression__compile_x86__mov__rax__rdi(cause); break;
	      case 1: new_chunk = raw__expression__compile_x86__mov__rax__rsi(cause); break;
	      case 2: new_chunk = raw__expression__compile_x86__mov__rax__rdx(cause); break;
	      case 3: new_chunk = raw__expression__compile_x86__mov__rax__rcx(cause); break;
	      case 4: new_chunk = raw__expression__compile_x86__mov__rax__r8(cause);  break;
	      case 5: new_chunk = raw__expression__compile_x86__mov__rax__r9(cause);  break;
	      default:
		return new__error(f2list6__new(cause,
					       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-funkall-too_many_arguments_to_x86_funk"),
					       new__symbol(cause, "funktion"),   funktion,
					       new__symbol(cause, "expression"), expression));
	      }
	      f2ptr new_cons = f2cons__new(cause, new_chunk, nil);
	      if (compiled_argument_chunks == nil) {
		compiled_argument_chunks = new_cons;
	      } else {
		f2cons__cdr__set(compiled_argument_chunks_iter, cause, new_cons);
	      }
	      compiled_argument_chunks_iter = new_cons;
	    }
	  }
	  argument_index ++;
	  argument_iter = f2cons__cdr(argument_iter, cause);
	}
      }
      f2ptr stack_machine_code_chunk = f2x86_funk__stack_machine_code_chunk(funktion, cause);
      if (! raw__machine_code_chunk__is_type(cause, stack_machine_code_chunk)) {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-funkall-x86_funk_is_not_compiled"),
				       new__symbol(cause, "funktion"),   funktion,
				       new__symbol(cause, "expression"), expression));
      }
      f2ptr chunk                        = f2machine_code_chunk__chunk(stack_machine_code_chunk, cause);
      u64   jump_ptr                     = raw__chunk__bytes(cause, chunk);
      f2ptr movabs__rdx__jump_ptr__chunk = raw__expression__compile_x86__movabs__constant_rdx(cause, jump_ptr);
      f2ptr movabs__rax__zero__chunk     = raw__expression__compile_x86__movabs__constant_rax(cause, 0x00);
      f2ptr callq__rdx__chunk            = raw__expression__compile_x86__callq__rdx(cause);
      return f2__machine_code_chunk_list__concat(cause, f2list4__new(cause,
								     f2__machine_code_chunk_list__concat(cause, compiled_argument_chunks),
								     movabs__rdx__jump_ptr__chunk,
								     movabs__rax__zero__chunk,
								     callq__rdx__chunk));
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-funkall-invalid_funktion_type"),
				     new__symbol(cause, "funktion"),   funktion,
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-funkall-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}

f2ptr raw__expression__compile_x86__je(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-je-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 = f2cons__car(f2cons__cdr(expression, cause), cause);
  if (raw__expression__is_constant_expression(cause, argument_0)) {
    f2ptr constant_value    = raw__constant_expression__constant_value(cause, argument_0);
    s64   constant_value__i = 0;
    if (raw__integer__is_type(cause, constant_value)) {
      constant_value__i = f2integer__i(constant_value, cause);
    } else if (raw__pointer__is_type(cause, constant_value)) {
      constant_value__i = (s64)f2pointer__p(constant_value, cause);
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-je-constant_number_must_be_integer_or_pointer"),
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
    return raw__expression__compile_x86__je__constant(cause, constant_value__i);
  } else if (raw__expression__is_label_expression(cause, argument_0)) {
    f2ptr label_name                   = raw__label_expression__label_name(cause, argument_0);
    f2ptr machine_code_chunk           = raw__expression__compile_x86__je__constant(cause, 0);
    f2ptr machine_code_jump__index     = f2integer__new(cause, 0);
    f2ptr machine_code_jump__command   = new__symbol(cause, "je");
    f2ptr machine_code_jump__label     = label_name;
    f2ptr machine_code_jump__arguments = nil;
    f2ptr machine_code_jump            = raw__machine_code_jump__new(cause, machine_code_jump__index, machine_code_jump__command, machine_code_jump__label, machine_code_jump__arguments);
    f2machine_code_chunk__jumps__set(machine_code_chunk, cause, f2cons__new(cause, machine_code_jump, f2machine_code_chunk__jumps(machine_code_chunk, cause)));
    return machine_code_chunk;
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-je-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}

f2ptr raw__expression__compile_x86__jne(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jne-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 = f2cons__car(f2cons__cdr(expression, cause), cause);
  if (raw__expression__is_constant_expression(cause, argument_0)) {
    f2ptr constant_value    = raw__constant_expression__constant_value(cause, argument_0);
    s64   constant_value__i = 0;
    if (raw__integer__is_type(cause, constant_value)) {
      constant_value__i = f2integer__i(constant_value, cause);
    } else if (raw__pointer__is_type(cause, constant_value)) {
      constant_value__i = (s64)f2pointer__p(constant_value, cause);
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-jne-constant_number_must_be_integer_or_pointer"),
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
    return raw__expression__compile_x86__jne__constant(cause, constant_value__i);
  } else if (raw__expression__is_label_expression(cause, argument_0)) {
    f2ptr label_name                   = raw__label_expression__label_name(cause, argument_0);
    f2ptr machine_code_chunk           = raw__expression__compile_x86__jne__constant(cause, 0);
    f2ptr machine_code_jump__index     = f2integer__new(cause, 0);
    f2ptr machine_code_jump__command   = new__symbol(cause, "jne");
    f2ptr machine_code_jump__label     = label_name;
    f2ptr machine_code_jump__arguments = nil;
    f2ptr machine_code_jump            = raw__machine_code_jump__new(cause, machine_code_jump__index, machine_code_jump__command, machine_code_jump__label, machine_code_jump__arguments);
    f2machine_code_chunk__jumps__set(machine_code_chunk, cause, f2cons__new(cause, machine_code_jump, f2machine_code_chunk__jumps(machine_code_chunk, cause)));
    return machine_code_chunk;
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jne-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}

f2ptr raw__expression__compile_x86__jle(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jle-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 = f2cons__car(f2cons__cdr(expression, cause), cause);
  if (raw__expression__is_constant_expression(cause, argument_0)) {
    f2ptr constant_value    = raw__constant_expression__constant_value(cause, argument_0);
    s64   constant_value__i = 0;
    if (raw__integer__is_type(cause, constant_value)) {
      constant_value__i = f2integer__i(constant_value, cause);
    } else if (raw__pointer__is_type(cause, constant_value)) {
      constant_value__i = (s64)f2pointer__p(constant_value, cause);
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-jle-constant_number_must_be_integer_or_pointer"),
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
    return raw__expression__compile_x86__jle__constant(cause, constant_value__i);
  } else if (raw__expression__is_label_expression(cause, argument_0)) {
    f2ptr label_name                   = raw__label_expression__label_name(cause, argument_0);
    f2ptr machine_code_chunk           = raw__expression__compile_x86__jle__constant(cause, 0);
    f2ptr machine_code_jump__index     = f2integer__new(cause, 0);
    f2ptr machine_code_jump__command   = new__symbol(cause, "jle");
    f2ptr machine_code_jump__label     = label_name;
    f2ptr machine_code_jump__arguments = nil;
    f2ptr machine_code_jump            = raw__machine_code_jump__new(cause, machine_code_jump__index, machine_code_jump__command, machine_code_jump__label, machine_code_jump__arguments);
    f2machine_code_chunk__jumps__set(machine_code_chunk, cause, f2cons__new(cause, machine_code_jump, f2machine_code_chunk__jumps(machine_code_chunk, cause)));
    return machine_code_chunk;
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jle-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}

f2ptr raw__expression__compile_x86__jl(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jl-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 = f2cons__car(f2cons__cdr(expression, cause), cause);
  if (raw__expression__is_constant_expression(cause, argument_0)) {
    f2ptr constant_value    = raw__constant_expression__constant_value(cause, argument_0);
    s64   constant_value__i = 0;
    if (raw__integer__is_type(cause, constant_value)) {
      constant_value__i = f2integer__i(constant_value, cause);
    } else if (raw__pointer__is_type(cause, constant_value)) {
      constant_value__i = (s64)f2pointer__p(constant_value, cause);
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-jl-constant_number_must_be_integer_or_pointer"),
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
    return raw__expression__compile_x86__jl__constant(cause, constant_value__i);
  } else if (raw__expression__is_label_expression(cause, argument_0)) {
    f2ptr label_name                   = raw__label_expression__label_name(cause, argument_0);
    f2ptr machine_code_chunk           = raw__expression__compile_x86__jl__constant(cause, 0);
    f2ptr machine_code_jump__index     = f2integer__new(cause, 0);
    f2ptr machine_code_jump__command   = new__symbol(cause, "jl");
    f2ptr machine_code_jump__label     = label_name;
    f2ptr machine_code_jump__arguments = nil;
    f2ptr machine_code_jump            = raw__machine_code_jump__new(cause, machine_code_jump__index, machine_code_jump__command, machine_code_jump__label, machine_code_jump__arguments);
    f2machine_code_chunk__jumps__set(machine_code_chunk, cause, f2cons__new(cause, machine_code_jump, f2machine_code_chunk__jumps(machine_code_chunk, cause)));
    return machine_code_chunk;
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jl-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}

f2ptr raw__expression__compile_x86__jge(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jge-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 = f2cons__car(f2cons__cdr(expression, cause), cause);
  if (raw__expression__is_constant_expression(cause, argument_0)) {
    f2ptr constant_value    = raw__constant_expression__constant_value(cause, argument_0);
    s64   constant_value__i = 0;
    if (raw__integer__is_type(cause, constant_value)) {
      constant_value__i = f2integer__i(constant_value, cause);
    } else if (raw__pointer__is_type(cause, constant_value)) {
      constant_value__i = (s64)f2pointer__p(constant_value, cause);
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-jge-constant_number_must_be_integer_or_pointer"),
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
    return raw__expression__compile_x86__jge__constant(cause, constant_value__i);
  } else if (raw__expression__is_label_expression(cause, argument_0)) {
    f2ptr label_name                   = raw__label_expression__label_name(cause, argument_0);
    f2ptr machine_code_chunk           = raw__expression__compile_x86__jge__constant(cause, 0);
    f2ptr machine_code_jump__index     = f2integer__new(cause, 0);
    f2ptr machine_code_jump__command   = new__symbol(cause, "jge");
    f2ptr machine_code_jump__label     = label_name;
    f2ptr machine_code_jump__arguments = nil;
    f2ptr machine_code_jump            = raw__machine_code_jump__new(cause, machine_code_jump__index, machine_code_jump__command, machine_code_jump__label, machine_code_jump__arguments);
    f2machine_code_chunk__jumps__set(machine_code_chunk, cause, f2cons__new(cause, machine_code_jump, f2machine_code_chunk__jumps(machine_code_chunk, cause)));
    return machine_code_chunk;
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jge-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}

f2ptr raw__expression__compile_x86__jg(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jg-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr argument_0 = f2cons__car(f2cons__cdr(expression, cause), cause);
  if (raw__expression__is_constant_expression(cause, argument_0)) {
    f2ptr constant_value    = raw__constant_expression__constant_value(cause, argument_0);
    s64   constant_value__i = 0;
    if (raw__integer__is_type(cause, constant_value)) {
      constant_value__i = f2integer__i(constant_value, cause);
    } else if (raw__pointer__is_type(cause, constant_value)) {
      constant_value__i = (s64)f2pointer__p(constant_value, cause);
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-jg-constant_number_must_be_integer_or_pointer"),
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
    return raw__expression__compile_x86__jg__constant(cause, constant_value__i);
  } else if (raw__expression__is_label_expression(cause, argument_0)) {
    f2ptr label_name                   = raw__label_expression__label_name(cause, argument_0);
    f2ptr machine_code_chunk           = raw__expression__compile_x86__jg__constant(cause, 0);
    f2ptr machine_code_jump__index     = f2integer__new(cause, 0);
    f2ptr machine_code_jump__command   = new__symbol(cause, "jg");
    f2ptr machine_code_jump__label     = label_name;
    f2ptr machine_code_jump__arguments = nil;
    f2ptr machine_code_jump            = raw__machine_code_jump__new(cause, machine_code_jump__index, machine_code_jump__command, machine_code_jump__label, machine_code_jump__arguments);
    f2machine_code_chunk__jumps__set(machine_code_chunk, cause, f2cons__new(cause, machine_code_jump, f2machine_code_chunk__jumps(machine_code_chunk, cause)));
    return machine_code_chunk;
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-jg-invalid_argument_expression_type"),
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}

f2ptr raw__expression__compile_x86__symbol(f2ptr cause, f2ptr expression) {
  if (! raw__cause__is_type(cause, cause)) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-symbol-no_cause_object"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr x86_variable_name_ptypehash = f2__cause__lookup_type_var_value(cause, cause, new__symbol(cause, "variable"), new__symbol(cause, "x86_variable_name_ptypehash"));
  if (! raw__ptypehash__is_type(cause, x86_variable_name_ptypehash)) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-symbol-x86_variable_name_ptypehash_not_defined"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr variable_definition = raw__ptypehash__lookup(cause, x86_variable_name_ptypehash, expression);
  if (variable_definition == nil) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-symbol-variable_not_defined"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr variable_command = f2list3__new(cause,
					new__symbol(cause, "mov"),
					variable_definition,
					f2list2__new(cause,
						     new__symbol(cause, "register"),
						     new__symbol(cause, "rax")));
  return raw__expression__compile_x86(cause, variable_command);
}

f2ptr raw__expression__compile_x86__label(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 2) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-label-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr label_name = f2cons__car(f2cons__cdr(expression, cause), cause);
  if (! raw__symbol__is_type(cause, label_name)) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-label-label_name_must_be_symbol"),
				   new__symbol(cause, "label_name"), label_name,
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr machine_code_chunk    = f2__machine_code_chunk__new(cause, raw__chunk__new(cause, 0));
  f2ptr index_label_ptypehash = f2machine_code_chunk__index_label_ptypehash(machine_code_chunk, cause);
  raw__ptypehash__add(cause, index_label_ptypehash, label_name, f2integer__new(cause, 0));
  return machine_code_chunk;
}

f2ptr raw__expression__compile_x86(f2ptr cause, f2ptr expression) {
  if (raw__integer__is_type(cause, expression)) {
    return raw__expression__compile_x86__integer(cause, expression);
  } else if (raw__pointer__is_type(cause, expression)) {
    return raw__expression__compile_x86__pointer(cause, expression);
  } else if (raw__symbol__is_type(cause, expression)) {
    return raw__expression__compile_x86__symbol(cause, expression);
  } else if (raw__cons__is_type(cause, expression)) {
    f2ptr command = f2cons__car(expression, cause);
    if      (raw__eq(cause, command, new__symbol(cause, "retq")))    {return raw__expression__compile_x86__retq(   cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "push")))    {return raw__expression__compile_x86__push(   cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "pop")))     {return raw__expression__compile_x86__pop(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "mov")))     {return raw__expression__compile_x86__mov(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "movq")))    {return raw__expression__compile_x86__movq(   cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "movzbl")))  {return raw__expression__compile_x86__movzbl( cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "incq")))    {return raw__expression__compile_x86__incq(   cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "add")))     {return raw__expression__compile_x86__add(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "subq")))    {return raw__expression__compile_x86__subq(   cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "addq")))    {return raw__expression__compile_x86__addq(   cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "addsd")))   {return raw__expression__compile_x86__addsd(  cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "cmpq")))    {return raw__expression__compile_x86__cmpq(   cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "cmp")))     {return raw__expression__compile_x86__cmp(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "movabs")))  {return raw__expression__compile_x86__movabs( cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "jmp")))     {return raw__expression__compile_x86__jmp(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "je")))      {return raw__expression__compile_x86__je(     cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "jne")))     {return raw__expression__compile_x86__jne(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "jle")))     {return raw__expression__compile_x86__jle(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "jl")))      {return raw__expression__compile_x86__jl(     cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "jge")))     {return raw__expression__compile_x86__jge(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "jg")))      {return raw__expression__compile_x86__jg(     cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "jb")))      {return raw__expression__compile_x86__jb(     cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "shl")))     {return raw__expression__compile_x86__shl(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "shr")))     {return raw__expression__compile_x86__shr(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "sub")))     {return raw__expression__compile_x86__sub(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "imul")))    {return raw__expression__compile_x86__imul(   cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "idivq")))   {return raw__expression__compile_x86__idivq(  cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "sar")))     {return raw__expression__compile_x86__sar(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "callq")))   {return raw__expression__compile_x86__callq(  cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "jmpq")))    {return raw__expression__compile_x86__jmpq(   cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "leaveq")))  {return raw__expression__compile_x86__leaveq( cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "rawcode"))) {return raw__expression__compile_x86__rawcode(cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "funkall"))) {return raw__expression__compile_x86__funkall(cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "label")))   {return raw__expression__compile_x86__label(  cause, expression);}
    else {
      f2ptr funkall_command = f2cons__new(cause,
					  new__symbol(cause, "funkall"),
					  f2cons__new(cause, f2list2__new(cause, new__symbol(cause, "funkvar"), command),
						      f2cons__cdr(expression, cause)));
      return raw__expression__compile_x86(cause, funkall_command);
    }
  } else {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-unknown_expression_type"),
				   new__symbol(cause, "expression-type"), f2__object__type(cause, expression),
				   new__symbol(cause, "expression"),      expression));
  }
}

f2ptr f2__expression__compile_x86(f2ptr cause, f2ptr expression) {
  return raw__expression__compile_x86(cause, expression);
}
def_pcfunk1(expression__compile_x86, expression,
	    "Compile x86 assembly expression to machine code chunk.",
	    return f2__expression__compile_x86(this_cause, expression));



// x86_funk

def_primobject_8_slot(x86_funk,
		      return_type,
		      name,
		      variables,
		      body,
		      stack_demetropolized_body,
		      heap_demetropolized_body,
		      stack_machine_code_chunk,
		      heap_machine_code_chunk);

f2ptr raw__x86_funk__new(f2ptr cause, f2ptr return_type, f2ptr name, f2ptr variables, f2ptr body, f2ptr stack_demetropolized_body, f2ptr heap_demetropolized_body, f2ptr stack_machine_code_chunk, f2ptr heap_machine_code_chunk) {
  return f2x86_funk__new(cause,
			 return_type,
			 name,
			 variables,
			 body,
			 stack_demetropolized_body,
			 heap_demetropolized_body,
			 stack_machine_code_chunk,
			 heap_machine_code_chunk);
}

boolean_t raw__expression__is_x86_funk_variable_type(f2ptr cause, f2ptr expression) {
  if (raw__eq(cause, expression, new__symbol(cause, "u64")) ||
      raw__eq(cause, expression, new__symbol(cause, "s64")) ||
      raw__eq(cause, expression, new__symbol(cause, "u32")) ||
      raw__eq(cause, expression, new__symbol(cause, "s32")) ||
      raw__eq(cause, expression, new__symbol(cause, "u16")) ||
      raw__eq(cause, expression, new__symbol(cause, "s16")) ||
      raw__eq(cause, expression, new__symbol(cause, "u8")) ||
      raw__eq(cause, expression, new__symbol(cause, "s8")) ||
      raw__eq(cause, expression, new__symbol(cause, "double")) ||
      raw__eq(cause, expression, new__symbol(cause, "float")) ||
      raw__eq(cause, expression, new__symbol(cause, "f2ptr"))) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__x86_funk__new(f2ptr cause, f2ptr return_type, f2ptr name, f2ptr variables, f2ptr body) {
  assert_argument_type(symbol,   return_type);
  assert_argument_type(symbol,   name);
  assert_argument_type(conslist, variables);
  assert_argument_type(conslist, body);
  if (! raw__expression__is_x86_funk_variable_type(cause, return_type)) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),    new__symbol(cause, "x86_funk-new-invalid_return_type"),
				   new__symbol(cause, "return_type"), return_type));
  }
  {
    f2ptr iter = variables;
    while (iter != nil) {
      f2ptr variable = f2cons__car(iter, cause);
      if ((! raw__conslist__is_type(cause, variable)) ||
	  (raw__simple_length(cause, variable) != 2)) {
	return new__error(f2list4__new(cause,
				       new__symbol(cause, "bug_name"),            new__symbol(cause, "x86_funk-new-variable_definition_must_have_type_and_name"),
				       new__symbol(cause, "variable_definition"), variable));
      }
      f2ptr variable_type =             f2cons__car(variable, cause);
      f2ptr variable_name = f2cons__car(f2cons__cdr(variable, cause), cause);
      if (! raw__expression__is_x86_funk_variable_type(cause, variable_type)) {
	return new__error(f2list4__new(cause,
				       new__symbol(cause, "bug_name"),      new__symbol(cause, "x86_funk-new-invalid_variable_type"),
				       new__symbol(cause, "variable_type"), variable_type));
      }
      if (! raw__symbol__is_type(cause, variable_name)) {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"),           new__symbol(cause, "x86_funk-new-variable_name_must_be_symbol"),
				       new__symbol(cause, "variable_name-type"), f2__object__type(cause, variable_name),
				       new__symbol(cause, "variable_name"),      variable_name));
      }
      iter = f2cons__cdr(iter, cause);
    }
  }
  return raw__x86_funk__new(cause, return_type, name, variables, body, nil, nil, nil, nil);
}
def_pcfunk4(x86_funk__new, return_type, name, variables, body,
	    "Returns a new x86_funk object.",
	    return f2__x86_funk__new(this_cause, return_type, name, variables, body));


f2ptr raw__x86_funk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"),       new__symbol(cause, "x86_funk"),
						new__symbol(cause, "print_object_slot_order"), f2list3__new(cause,
													    new__symbol(cause, "return_type"),
													    new__symbol(cause, "name"),
													    new__symbol(cause, "variables")),
						new__symbol(cause, "return_type"),             f2__x86_funk__return_type(cause, this),
						new__symbol(cause, "name"),                    f2__x86_funk__name(       cause, this),
						new__symbol(cause, "variables"),               f2__x86_funk__variables(  cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__x86_funk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(x86_funk,             this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__x86_funk__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(x86_funk__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints this x86_funk to the given terminal.",
	    return f2__x86_funk__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2x86_funk__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2x86_funk__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_x86_funk.terminal_print_with_frame__funk);}
  return this;
}



// **

void f2__compile_x86__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --

  // machine_code_jump
  
  initialize_primobject_4_slot__defragment__fix_pointers(machine_code_jump, index, command, label, arguments);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_machine_code_jump.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(machine_code_jump__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_machine_code_jump.terminal_print_with_frame__funk);
  
  
  // machine_code_chunk
  
  initialize_primobject_3_slot__defragment__fix_pointers(machine_code_chunk, chunk, index_label_ptypehash, jumps);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.finalize_jumps__symbol);
  f2__primcfunk__init__defragment__fix_pointers(machine_code_chunk__finalize_jumps);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.finalize_jumps__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(machine_code_chunk__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.terminal_print_with_frame__funk);
  
  
  // machine_code_chunk_list
  
  f2__primcfunk__init__defragment__fix_pointers(machine_code_chunk_list__concat);
  
  // compile_x86 funks
  
  f2__primcfunk__init__defragment__fix_pointers(expression__compile_x86);
  

  // x86_funk
  
  initialize_primobject_8_slot__defragment__fix_pointers(x86_funk,
							 return_type,
							 name,
							 variables,
							 body,
							 stack_demetropolized_body,
							 heap_demetropolized_body,
							 stack_machine_code_chunk,
							 heap_machine_code_chunk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_x86_funk.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(x86_funk__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_x86_funk.terminal_print_with_frame__funk);
  
}

void f2__compile_x86__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  reinitialize_primobject(machine_code_chunk);
  
  // machine_code_jump
  
  initialize_primobject_4_slot(machine_code_jump, index, command, label, arguments);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_machine_code_jump.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(machine_code_jump__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_machine_code_jump.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // machine_code_chunk
  
  initialize_primobject_3_slot(machine_code_chunk, chunk, index_label_ptypehash, jumps);
  
  {char* symbol_str = "finalize_jumps"; __funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.finalize_jumps__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(machine_code_chunk__finalize_jumps, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.finalize_jumps__funk = never_gc(cfunk);}
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(machine_code_chunk__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // machine_code_chunk_list
  
  f2__primcfunk__init__1(machine_code_chunk_list__concat, these);

  // compile_x86 funks
  
  f2__primcfunk__init__1(expression__compile_x86, expression);
  
  // x86_funk
  
  initialize_primobject_8_slot(x86_funk,
			       return_type,
			       name,
			       variables,
			       body,
			       stack_demetropolized_body,
			       heap_demetropolized_body,
			       stack_machine_code_chunk,
			       heap_machine_code_chunk);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_x86_funk.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(x86_funk__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_x86_funk.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__compile_x86__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "compile_x86", "", &f2__compile_x86__reinitialize_globalvars, &f2__compile_x86__defragment__fix_pointers);
  
  f2__compile_x86__reinitialize_globalvars();
}

