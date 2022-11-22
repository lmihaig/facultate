img segment
 w dw 5
 h dw 10
 i db 3,3,3,3,3
   db 3,3,3,3,3
   db 3,3,3,3,3
   db 3,3,3,3,3
   db 3,3,3,3,3
   db 3,3,3,3,3
   db 3,3,3,3,3
   db 3,3,3,3,3
   db 3,3,3,3,3
   db 3,3,3,3,3
img ends

vbuff segment
   vb db 64000 dup(?)
vbuff ends

stiva segment stack
      dw 512 dup(?)
   sv label word
stiva ends

program segment
assume cs:program
  mod_vechi db ?
  x dw ?
  y dw ?
  xmin dw ?
  ymin dw ?
  xmax dw ?
  ymax dw ?
  saltx dw ?
  salty dw ?
start:
mov ax,stiva
mov ss,ax
mov sp,ss:sv

 ;testez existenta modului 13h
 mov ax,1a00h
 int 10h
 cmp al,1ah
 je ok
 jmp sfarsit
 ok:

 ;salvez modul vechi
 mov ax,program
 mov ds,aX
 mov ah,0fh
 int 10h
 mov ds:mod_vechi,al

 ;setez modul 13h
 mov ah,0
 mov al,13h
 int 10h

 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 ;initializare desen
 mov ax,program
 mov ds,ax
 mov ax,img
 mov es,ax
 mov ds:xmin,0
 mov ax,319
 sub ax,es:w
 mov ds:xmax,ax
 mov ymin,0
 mov ax,199
 sub ax,es:h
 mov ds:ymax,ax
 mov ds:x,17
 mov ds:y,0
 mov ds:saltx,1
 mov ds:salty,1
 
 continua:
 ;desenez frame nou si actualizez coordonatele
   ;sterg bufferul noului frame
 mov ax,vbuff
 mov es,ax
 mov di,offset vb
 mov cx,64000
 mov al,0
 rep stosb
   ;desenez figura in bufferul noului frame
 mov ax,program
 mov ds,ax
 mov di,ds:x
 mov cx,ds:y
 et1:
 add di,320
 loop et1
 mov si,offset i
 mov ax,img
 mov ds,ax
 mov ax,vbuff
 mov es,ax
 mov cx,ds:h
 et2:
 push cx
 push di
 mov cx,ds:w
 rep movsb
 pop di
 add di,320
 pop cx
 loop et2
   ;actualizez coordonate
 mov ax,program
 mov ds,ax
 mov ax,ds:x
 add ax,ds:saltx
 cmp ax,0
 jl eet3
 cmp ax,ds:xmax
 jg eet3
 jmp et3
 eet3:
 neg saltx
 add ax,ds:saltx
 add ax,ds:saltx
 et3:
 mov ds:x,ax
 mov ax,ds:y
 add ax,ds:salty
 cmp ax,0
 jl eet4
 cmp ax,ds:ymax
 jg eet4
 jmp et4
 eet4:
 neg salty
 add ax,ds:salty
 add ax,ds:salty
 et4:
 mov ds:y,ax

 ;copiez noul frame in memoria video
 mov ax,seg vb
 mov ds,ax
 mov si,offset vb
 mov ax,0a000h
 mov es,ax
 mov di,0
 mov cx,64000
 rep movsb

 ;testez terminarea
 mov dl,0ffh
 mov ah,6h
 int 21h
 jnz nucontinua
 jmp continua
 nucontinua: 
;  mov ah,0h
;  int 16h
;  cmp al,'e'
;  je nucontinua
;  jmp continua
;  nucontinua:
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

 ;restaurez modul vechi
 mov ax,program
 mov ds,ax
 mov ah,0
 mov al,ds:mod_vechi
 int 10h

 sfarsit:

mov ah,4ch
int 21h
program ends

end start

;Obs: viteza programului va creste daca stergerea frame-ului
; si copierea frame-ului in memoria video se face word cu word
; (facand de 32000 ori stosw/movsw) (tema).
;
;Daniel Dragulici
;decembrie 2007
