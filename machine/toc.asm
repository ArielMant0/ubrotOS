; $Id: toc.asm 9719 2018-12-05 09:57:29Z df $

;******************************************************************************
;* Betriebssysteme                                                            *
;*----------------------------------------------------------------------------*
;*                                                                            *
;*                               T O C . A S M                                *
;*                                                                            *
;*----------------------------------------------------------------------------*
;*
;******************************************************************************

%include "machine/toc.inc"

; EXPORTIERTE FUNKTIONEN

[GLOBAL toc_switch]
[GLOBAL toc_go]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; TOC_GO : Startet den ersten Prozess ueberhaupt.
;
; C Prototyp: void toc_go (struct toc* regs);

toc_go:
	mov rbx, [rax+rbx_offset]
	mov r12, [rax+r12_offset]
	mov r13, [rax+r13_offset]
	mov r14, [rax+r14_offset]
	mov r15, [rax+r15_offset]
	mov rbp, [rax+rbp_offset]
	mov rsp, [rax+rsp_offset]

; TOC_SWITCH : Prozessumschaltung. Der aktuelle Registersatz wird
;              gesichert und der Registersatz des neuen "thread of control"
;              wird in den Prozessor eingelesen.
;
; C Prototyp: void toc_switch (struct toc* regs_now,
;                              struct toc* reg_then);

toc_switch:
; Save registry content to regs_now
	mov [rax+rbx_offset], rbx
	mov [rax+r12_offset], r12
	mov [rax+r13_offset], r13
	mov [rax+r14_offset], r14
	mov [rax+r15_offset], r15
	mov [rax+rbp_offset], rbp
	mov [rax+rsp_offset], rsp
; Load content of regs_then into registries
	mov rbx, [rbx+rbx_offset]
	mov r12, [rbx+r12_offset]
	mov r13, [rbx+r13_offset]
	mov r14, [rbx+r14_offset]
	mov r15, [rbx+r15_offset]
	mov rbp, [rbx+rbp_offset]
	mov rsp, [rbx+rsp_offset]
