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


// machine_code_chunk

def_primobject_2_slot(machine_code_chunk,
		      chunk,
		      index_label_ptypehash);

f2ptr raw__machine_code_chunk__new(f2ptr cause, f2ptr chunk, f2ptr index_label_ptypehash) {
  return f2machine_code_chunk__new(cause, chunk, index_label_ptypehash);
}

f2ptr f2__machine_code_chunk__new(f2ptr cause) {
  f2ptr chunk                 = raw__chunk__new(cause, 0);
  f2ptr index_label_ptypehash = f2__ptypehash__new(cause);
  return raw__machine_code_chunk__new(cause, chunk, index_label_ptypehash);
}
def_pcfunk0(machine_code_chunk__new,
	    "",
	    return f2__machine_code_chunk__new(this_cause));


f2ptr raw__machine_code_chunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"),     new__symbol(cause, "machine_code_chunk"),
					       new__symbol(cause, "chunk"),                 f2__machine_code_chunk__chunk(cause, this),
					       new__symbol(cause, "index_label_ptypehash"), f2__machine_code_chunk__index_label_ptypehash(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

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
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.terminal_print_with_frame__funk);}
  return this;
}


f2ptr raw__expression__compile_x86__retq(f2ptr cause, f2ptr expression) {
  if (raw__simple_length(cause, expression) != 1) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-retq-invalid_expression_length"),
				   new__symbol(cause, "expression"), expression));
  }
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0xC3);
  return chunk;
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
  return raw__chunklist__concat(cause, subexpression_chunks);
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




f2ptr raw__expression__compile_x86__push_rbp(f2ptr cause, f2ptr expression) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x55);
  return chunk;
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
    if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__push_rbp(cause, expression);}
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



f2ptr raw__expression__compile_x86__pop_rbp(f2ptr cause, f2ptr expression) {
  f2ptr chunk = raw__chunk__new(cause, 1);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x5D);
  return chunk;
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
    if (raw__eq(cause, register_name, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__pop_rbp(cause, expression);}
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



f2ptr raw__expression__compile_x86__mov_rsp_rbp(f2ptr cause, f2ptr expression) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x89);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xE5);
  return chunk;
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
    return chunk;
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
    return chunk;
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
    return chunk;
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-rdi-relative_rbp-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

f2ptr raw__expression__compile_x86__mov__relative_rbp__rax(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x8B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return chunk;
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-relative_rbp-rax-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

f2ptr raw__expression__compile_x86__mov__relative_rbp__rdx(f2ptr cause, s64 relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x8B);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x55);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return chunk;
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
    return chunk;
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-mov-relative_rax-rax-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
  }
}

f2ptr raw__expression__compile_x86__add__relative_rbp__rax(cause, relative_offset_value) {
  if ((relative_offset_value <   128) &&
      (relative_offset_value >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 4);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
    raw__chunk__bit8__elt__set(cause, chunk, 1, 0x03);
    raw__chunk__bit8__elt__set(cause, chunk, 2, 0x45);
    raw__chunk__bit8__elt__set(cause, chunk, 3, (u8)((signed char)relative_offset_value));
    return chunk;
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-add-relative_rpb-rax-unknown_relative_offset_range"),
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
      return chunk;
    } else {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-add-relative_rpb-rax-unknown_relative_offset_range"),
				     new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_offset_value)));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-add-relative_rpb-rax-unknown_constant_value_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, constant_value)));
  }
}

f2ptr raw__expression__compile_x86__add__rdx__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x01);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xD0);
  return chunk;
}

f2ptr raw__expression__compile_x86__mov__deref_rax__rax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0x8B);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x00);
  return chunk;
}

f2ptr raw__expression__compile_x86__movzbl__deref_rax__eax(f2ptr cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xB6);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0x00);
  return chunk;
}

f2ptr raw__expression__compile_x86__movzbl__al__eax(cause) {
  f2ptr chunk = raw__chunk__new(cause, 3);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x0F);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xB6);
  raw__chunk__bit8__elt__set(cause, chunk, 2, 0xC0);
  return chunk;
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
    if (raw__eq(cause, register_name_0, new__symbol(cause, "rsp"))) {
      if (raw__expression__is_register_expression(cause, argument_1)) {
	f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
       	if (raw__eq(cause, register_name_1, new__symbol(cause, "rbp"))) {return raw__expression__compile_x86__mov_rsp_rbp(cause, expression);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list4__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-invalid_argument_expression_type"),
				       new__symbol(cause, "expression"), expression));
      }
    } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
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
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-invalid_argument_expression_type"),
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
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-invalid_argument_expression_type"),
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
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-invalid_argument_expression_type"),
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
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	    return raw__expression__compile_x86__mov__relative_rbp__rax(cause, relative_offset_value);
	  } else if (raw__eq(cause, register_name_1, new__symbol(cause, "rdx"))) {
	    return raw__expression__compile_x86__mov__relative_rbp__rdx(cause, relative_offset_value);
	  } else {
	    return new__error(f2list6__new(cause,
					   new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-mov-unknown_register_name"),
					   new__symbol(cause, "register_name"), register_name_1,
					   new__symbol(cause, "expression"),    expression));
	  }
	}
      } else if (raw__eq(cause, register_name_0, new__symbol(cause, "rax"))) {
	if (raw__expression__is_register_expression(cause, argument_1)) {
	  f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
	  if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {
	    return raw__expression__compile_x86__mov__relative_rax__rax(cause, relative_offset_value);
	  } else {
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
					 new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-unknown_deref_target_argument_expression_type"),
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
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-unknown_deref_argument_expression_type"),
				     new__symbol(cause, "expression"), expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
  return new__error(f2list4__new(cause,
				 new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-should_never_get_here"),
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
      constant_value__i = (s64)f2pointer__p(cause, constant_value);
    } else if (raw__integer__is_type(cause, constant_value)) {
      constant_value__i = f2integer__i(cause, constant_value);
    } else if (raw__minus_expression__is_type(cause, constant_value)) {
      f2ptr minus_expression__argument = raw__minus_expression__argument(cause, constant_value);
      if (raw__pointer__is_type(cause, minus_expression__argument)) {
	constant_value__i = -(s64)f2pointer__p(cause, minus_expression__argument);
      } else if (raw__integer__is_type(cause, minus_expression__argument)) {
	constant_value__i = -f2integer__i(cause, minus_expression__argument);
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
					 new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-subq-invalid_argument_expression_type"),
					 new__symbol(cause, "argument"),   argument_1,
					 new__symbol(cause, "expression"), expression));
	}
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
				   new__symbol(cause, "argument"),   argument_0,
				   new__symbol(cause, "expression"), expression));
  }
}




// 48 b8 00 00 64 a7 b3 b6 e0 0d 	movabs $0x0de0b6b3a7640000,%rax


f2ptr raw__expression__compile_x86__absmov_constant_rax(f2ptr cause, f2ptr expression, u64 constant_value) {
  f2ptr chunk = raw__chunk__new(cause, 10);
  raw__chunk__bit8__elt__set(cause, chunk, 0, 0x48);
  raw__chunk__bit8__elt__set(cause, chunk, 1, 0xB8);
  raw__chunk__bit8__elt__set(cause, chunk, 2, (constant_value >>  0) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 3, (constant_value >>  8) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 4, (constant_value >> 16) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 5, (constant_value >> 24) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 6, (constant_value >> 32) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 7, (constant_value >> 40) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 8, (constant_value >> 48) & 0xFF);
  raw__chunk__bit8__elt__set(cause, chunk, 9, (constant_value >> 56) & 0xFF);
  return chunk;
}

f2ptr raw__expression__compile_x86__jmp__relative(f2ptr cause, s64 relative_jump_distance) {
  if ((relative_jump_distance <   128) &&
      (relative_jump_distance >= -128)) {
    f2ptr chunk = raw__chunk__new(cause, 2);
    raw__chunk__bit8__elt__set(cause, chunk, 0, 0xEB);
    raw__chunk__bit8__elt__set(cause, chunk, 1, (u8)((signed char)relative_jump_distance));
    return chunk;
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "expression-compile_x86-jmp-relative_rax-rax-unknown_relative_offset_range"),
				   new__symbol(cause, "relative_offset"), f2integer__new(cause, relative_jump_distance)));
  }
}

f2ptr raw__expression__compile_x86__absmov(f2ptr cause, f2ptr expression) {
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
    f2ptr constant_value = raw__constant_expression__constant_value(cause, argument_0);
    if (raw__pointer__is_type(cause, constant_value)) {
      u64 constant_value__p = f2pointer__p(constant_value, cause);
      if (raw__expression__is_register_expression(cause, argument_1)) {
	f2ptr register_name_1 = raw__register_expression__register_name(cause, argument_1);
	if (raw__eq(cause, register_name_1, new__symbol(cause, "rax"))) {return raw__expression__compile_x86__absmov_constant_rax(cause, expression, constant_value__p);}
	else {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "expression-compile_x86-absmov-unknown_register_name"),
					 new__symbol(cause, "register_name"), register_name_1,
					 new__symbol(cause, "expression"),    expression));
	}
      } else {
	return new__error(f2list4__new(cause,
				       new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-invalid_argument_expression_type"),
				       new__symbol(cause, "expression"), expression));
      }
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),       new__symbol(cause, "expression-compile_x86-push-constant_value_must_be_pointer"),
				     new__symbol(cause, "constant_value"), constant_value,
				     new__symbol(cause, "expression"),     expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-invalid_argument_expression_type"),
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
				     new__symbol(cause, "bug_name"),                  new__symbol(cause, "expression-compile_x86-push-invalid_minus_expression_argument_expression_type"),
				     new__symbol(cause, "minus_expression-argument"), minus_expression__argument,
				     new__symbol(cause, "expression"),                expression));
    }
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-push-invalid_argument_expression_type"),
				   new__symbol(cause, "expression"), expression));
  }
  return raw__expression__compile_x86__jmp__relative(cause, relative_jump_distance);
}

f2ptr raw__expression__compile_x86__integer(f2ptr cause, f2ptr expression) {
  f2ptr pointer = f2pointer__new(cause, f2integer__i(expression, cause));
  return raw__expression__compile_x86(cause, f2list3__new(cause, new__symbol(cause, "absmov"), f2list2__new(cause, new__symbol(cause, "constant"), pointer), f2list2__new(cause, new__symbol(cause, "register"), new__symbol(cause, "rax"))));
}

f2ptr raw__expression__compile_x86__pointer(f2ptr cause, f2ptr expression) {
  return raw__expression__compile_x86(cause, f2list3__new(cause, new__symbol(cause, "absmov"), f2list2__new(cause, new__symbol(cause, "constant"), expression), f2list2__new(cause, new__symbol(cause, "register"), new__symbol(cause, "rax"))));
}

f2ptr raw__expression__compile_x86(f2ptr cause, f2ptr expression) {
  if (raw__integer__is_type(cause, expression)) {
    return raw__expression__compile_x86__integer(cause, expression);
  } else if (raw__pointer__is_type(cause, expression)) {
    return raw__expression__compile_x86__pointer(cause, expression);
  } else if (raw__cons__is_type(cause, expression)) {
    f2ptr command = f2cons__car(expression, cause);
    if      (raw__eq(cause, command, new__symbol(cause, "retq")))    {return raw__expression__compile_x86__retq(   cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "push")))    {return raw__expression__compile_x86__push(   cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "pop")))     {return raw__expression__compile_x86__pop(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "mov")))     {return raw__expression__compile_x86__mov(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "movzbl")))  {return raw__expression__compile_x86__movzbl( cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "add")))     {return raw__expression__compile_x86__add(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "subq")))    {return raw__expression__compile_x86__subq(   cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "absmov")))  {return raw__expression__compile_x86__absmov( cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "jmp")))     {return raw__expression__compile_x86__jmp(    cause, expression);}
    else if (raw__eq(cause, command, new__symbol(cause, "rawcode"))) {return raw__expression__compile_x86__rawcode(cause, expression);}
    else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),   new__symbol(cause, "expression-compile_x86-unknown_command"),
				     new__symbol(cause, "command"),    command,
				     new__symbol(cause, "expression"), expression));
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


// **

void f2__compile_x86__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --

  // machine_code_chunk
  
  initialize_primobject_2_slot__defragment__fix_pointers(machine_code_chunk, chunk, index_label_ptypehash);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(machine_code_chunk__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.terminal_print_with_frame__funk);
  
  
  // compile_x86 funks
  
  f2__primcfunk__init__defragment__fix_pointers(expression__compile_x86);
  
  
}

void f2__compile_x86__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  reinitialize_primobject(machine_code_chunk);
  
  // machine_code_chunk
  
  initialize_primobject_2_slot(machine_code_chunk, chunk, index_label_ptypehash);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(machine_code_chunk__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_machine_code_chunk.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // compile_x86 funks
  
  f2__primcfunk__init__1(expression__compile_x86, expression);
  
}

void f2__compile_x86__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "compile_x86", "", &f2__compile_x86__reinitialize_globalvars, &f2__compile_x86__defragment__fix_pointers);
  
  f2__compile_x86__reinitialize_globalvars();
}

