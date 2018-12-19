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
	push rbp
	mov rbp,rsp

	mov rbx, [rbp+rbx_offset]
	mov r12, [rbp+r12_offset]
	mov r13, [rbp+r13_offset]
	mov r14, [rbp+r14_offset]
	mov r15, [rbp+r15_offset]
	mov rbp, [rbp+rbp_offset]
	mov rsp, [rbp+rsp_offset]

	pop rbp
	ret

; TOC_SWITCH : Prozessumschaltung. Der aktuelle Registersatz wird
;              gesichert und der Registersatz des neuen "thread of control"
;              wird in den Prozessor eingelesen.
;
; C Prototyp: void toc_switch (struct toc* regs_now,
;                              struct toc* reg_then);

toc_switch:
	push rbp
	mov rbp,rsp
	
; Save registry content to regs_now
	mov [rbp+rbx_offset], rbx
	mov [rbp+r12_offset], r12
	mov [rbp+r13_offset], r13
	mov [rbp+r14_offset], r14
	mov [rbp+r15_offset], r15
	mov [rbp+rbp_offset], rbp
	mov [rbp+rsp_offset], rsp
; Load content of regs_then into registries
	mov rbx, [rbp+rsp_offset+rbx_offset]
	mov r12, [rbp+rsp_offset+r12_offset]
	mov r13, [rbp+rsp_offset+r13_offset]
	mov r14, [rbp+rsp_offset+r14_offset]
	mov r15, [rbp+rsp_offset+r15_offset]
	mov rbp, [rbp+rsp_offset+rbp_offset]
	mov rsp, [rbp+rsp_offset+rsp_offset]

	pop rbp
	ret