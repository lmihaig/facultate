.model small
.stack
.data
 mod_vechi db ?
.code
start:
mov ax,@stack
mov ds,ax
mov ax,@data
mov ds,ax
mov es,ax

 ;testez existenta modului 13h
 mov ax,1a00h
 int 10h
 cmp al,1ah
 je ok
 jmp sfarsit
 ok:

 ;salvez modul vechi
 mov ah,0fh
 int 10h
 mov mod_vechi,al

 ;setez modul 13h
 mov ah,0
 mov al,13h
 int 10h

 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 ; segmentul vga este 0a000h
 ; offsetul pixelului (x,y) (de pe linia y si coloana x) este x+(y*320)
 ; punctul (0,0) este in coltul din stanga sus
 mov ax,0a000h
 mov es,ax

 ;linie (1,10) -> (100,10) cu intreruperea 10h
 mov ah,0ch
 mov al,3     ; culoare
 mov cx,100   ; x (coloana)
 mov dx,10    ; y (linia)
 et1:
 int 10h
 loop et1

 ; linie (10,20) -> (109,20) cu "rep stosb" in memoria video
 mov di,6410 ; 10+20*320
 mov cx,100
 mov al,3
 rep stosb

 ; linie (10,30) -> (109,30) cu "mov" in memoria video (e mai rapid)
 mov di,9610 ; 10+30*320
 mov cx,100
 et2:
 mov byte ptr es:[di],3
 inc di
 loop et2

 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

 mov ah,0
 int 16h  ; getch

 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

 ;restaurez modul vechi
 mov ah,0
 mov al,mod_vechi
 int 10h

 sfarsit:
mov ah,4ch
int 21h
end start

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;Aplicatii (se vor implementa ca macro-uri sau proceduri, cu parametri):
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;1. Desenarea unui dreptunghi plin.
;
; Ideea: pentru a obtine un dreptunghi plin de latime w si inaltime h avand
;varful din stanga sus la coord. (x0,y0), se deseneaza h linii orizontale
;de lungme w, una sub alta; toate liniile vor incepe de la aceeasi abscisa x0
;si de la ordonate succesive y0, y0+1, ..., y0+h-1.
; Vom avea doua cicluri incluse unul in altul; pt. a le putea implementa cu
;LOOP/REP vom salva/restaura CX folosit de ciclul exterior ca sa putem face
;ciclul interior.
; Obtinem algoritmul (presupunem ca ES contine 0a000h):
;
; AL:=culoarea
; DI:=offsetul corespunzator lui (x0,y0), adica y0*320+x0
; CX:=h
; linie_noua:
; push CX     ;salvam contorul ciclului exterior
; push DI
;   CX:=w
;   rep stosb ;acum DI=offsetul pct. (x0+w-1,y), y fiind ordonata curenta
; pop DI      ;acum DI=offsetul pct. (x0,y)
; DI:=DI+320  ;acum DI=offsetul pct. (x0,y+1)
; pop CX      ;restauram contorul ciclului exterior
; loop linie_noua
;
;2. Trasare linie (obliga) de la (x0,y0) la (x1,y1).
;
; Nu merge sa punem puncte la ordonate sau abscise succesive, caci iese o
;linie intrerupta (mai ales la liniile f. apropiate de oriz. sau verticala).
; O idee: trasam o succesiune de segmente orizontale la ordonate succesive,
;sau o succesiune de segmente verticale la abscise succesive:
;
;                   ---*(x1,y1)
;                 ---
;              ----
;    (x0,y0) *--
;
;Comentarii:
;- sunt ny:=1+abs(y1-y0) segmente, deci ny iteratii, fiecare iteratie
; deseneaza segm. de pe ordonata y, y parcurgand succesiv valorile de la y0
; la y1, iar fiecare segment incepe deasupra/dedesubtul locului unde se
; termina precedentul;
;- segmentele ar avea lungimea nx:=1+(abs(x1-x0) div ny);
;  ramane insa pe orizontala un spatiu de rx:=abs(x1-x0) mod ny care trebuie
; repartizat uniform intre cele ny segmente; pentru aceasta luam o variabila
; r care este initial 0, apoi la fiecare din cele ny iteratii facem r:=r+rx
; iar daca r>=ny (asta se va intampla de rx ori) facem r:=r-ny si mai adaugam
; un pixel la segmentul curent desenat (el va avea lungime nx+1);
;- trecerea de la un y la altul (de la o iteratie la alta) se face adunand la
; offsetul curent in segmentul video +/- 320 (dupa cum y1>=y0 sau y1<y0); la
; aceasta se adauga o corectie de +/-1 deoarece stosb lasa DI in stanga sau
; dreapta ultimului pixel desenat (in functie de DF) si nu pe ultimul pixel
; desenat; notam cantitatea totala adunata la offsetul curent cu saltx;
;  segmentul de ordonata y se trage spre dreapta/stanga (deci se face DF=0/1)
; dupa cum x1>=x0 sau x1<x0;
;
; Obtinem algoritmul (presupunem ca ES contine 0a000h):
;
; variabile noi: ny,nx,rx,saltx
;
; ny:=1+abs(y1-y0)
; nx:=1+abs(x1-x0)div ny
; rx:=abs(x1-x0)mod ny
; daca y1>=y0 atunci saltx:=320 altfel saltx:=-320
; daca x1>=x0 atunci {DF:=0; saltx:=saltx-1} altfel {DF:=1; saltx:=saltx+1}
; DI:=offsetul corespunzator lui (x0,y0)
; AL:=culoarea de desenare
;
; DX:=0  // DX tine loc de r
; CX:=ny
; segment_nou:
; push CX
;   CX:=nx
;   DX:=DX+rx; daca DX>=ny atunci {DX:=DX-ny; CX:=CX+1}
;   rep stosb
;   DI:=DI+saltx
; pop CX
; loop segment_nou
;
;- algoritmul nu este cel mai performant si nu produce neaparat linia franta
;  cea mai apropiata de dreapta ideala (asta se vede de exemplu in cazul unei
;  drepte f. apropiata de verticala); un algoritm mai bun este algoritmul lui
;  J.Bresenham, care poate fi gasit in cartea:
;    M.Vlada, I.Nistor,A.Posea,C.Constantinescu,
;    "Grafica pe calculator in limbajele Pascal si C",
;    ed. Tehnica, 1992, vol. II
;
;Daniel Dragulici
;ianuarie 2006
;actualizat: 10 februarie 2006 si 11 decembrie 2007
