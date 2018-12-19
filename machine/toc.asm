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
; MERKE: ret returned dahin wo der Stackpointer hinschreibt
; MERKE: rbp zeigt auf den Anfang der Funktion, der aufgerufene kopiert den sp in den bp
; C Prototyp: void toc_go (struct toc* regs);

toc_go:

	mov rbx, [rdi+rbx_offset]
	mov r12, [rdi+r12_offset]
	mov r13, [rdi+r13_offset]
	mov r14, [rdi+r14_offset]
	mov r15, [rdi+r15_offset]
	mov rbp, [rdi+rbp_offset]
	mov rsp, [rdi+rsp_offset]

	ret

; TOC_SWITCH : Prozessumschaltung. Der aktuelle Registersatz wird
;              gesichert und der Registersatz des neuen "thread of control"
;              wird in den Prozessor eingelesen.
;
; MERKE: rdi enthält ersten Adress-Parameter, rsi zweiten
; C Prototyp: void toc_switch (struct toc* regs_now,
;                              struct toc* reg_then);

toc_switch:

; Save registry content to regs_now
	mov [rdi+rbx_offset], rbx
	mov [rdi+r12_offset], r12
	mov [rdi+r13_offset], r13
	mov [rdi+r14_offset], r14
	mov [rdi+r15_offset], r15
	mov [rdi+rbp_offset], rbp
	mov [rdi+rsp_offset], rsp
; Load content of regs_then into registries
	mov rbx, [rsi+rbx_offset]
	mov r12, [rsi+r12_offset]
	mov r13, [rsi+r13_offset]
	mov r14, [rsi+r14_offset]
	mov r15, [rsi+r15_offset]
	mov rbp, [rsi+rbp_offset]
	mov rsp, [rsi+rsp_offset]

	ret