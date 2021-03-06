Program PoiskPut;  
{ ���� � ��㡨�� ��� ��⥩ �� �ਥ��஢����� ���
  � � �⥪��. ��� � 䠩�� input.txt
�ਬ��
4     �᫮ ���設 ���
1 3   �㣨
3 4
2 3
3 2
�뢮� �� ��࠭ � � 䠩� output.txt
}
Uses Crt;
Const
  Max=20;
Type
  ElemSt=record
           Nv: integer; {����� ���設�}
           Next: integer;
           {����� ᫥���饩 ���設� ��� �த������� ���}
         end;
Var
  Matr : array[1..Max,1..Max] of integer; { ����� ᬥ����� }
  St: array [1..Max] of ElemSt; {�⥪ - ⥪�騩 ����}
  Top: integer;                  {���設� �⥪� }
  N,a,b: integer;
  B1: boolean;
  Fin,Fout: text;
  Ch: char;

Procedure Poisk(S,T: integer);
{���� ��� ��⥩ �� ��� S -> T}
Label Kon;
Var
  k,m,i,j: integer;
  B2: boolean;
Begin
  Top:=1;
  St[Top].Nv:=S;
  St[Top].Next:=0;
  While Top<>0 do
    begin
      St[Top].Next:=St[Top].Next+1;
      k:=St[Top].Nv;
      m:=St[Top].Next;
      if k=T then  { T-����筠� ���設� }
        begin
          For i:=1 to Top do    { �뢮� ��� }
            Write(Fout,St[i].Nv,' ');
          Writeln(Fout);
          For i:=1 to Top do    { �뢮� ��� }
            Write(St[i].Nv,' ');
          Writeln;
          Readln    { ��㧠 }
        end
      else
        For i:=m to N do {������: ����� �� i-� ���設� ���� ᫥���饩}
          begin
            if Matr[k,i]=1 then
              begin
                B2:=true; {�ਧ���: ���設� i ���}
                For j:=1 to Top do
                  if St[j].Nv=i then
                    begin
                      B2:=false; {���設� i 㦥 ���� � ���}
                      Break
                    end;
                if B2 then {����祭�� ���設� i � ⥪�騩 ����}
                  begin
                    St[Top].Next:=i;
                    Top:=Top+1;
                    St[Top].Nv:=i;
                    St[Top].Next:=0;
                    Goto Kon;  {����� 横�� While}
                  end;
              end;
          end;
      {����� ����뢠���� ��᫥ ��宦����� ��।���� ��� }
      {��� � ��砥 ��������� � �㯨�}
      Top:=Top-1;    {������ � �।����� ���設� }
Kon:
    end;
End;

Begin             { �᭮���� �ணࠬ�� }
  ClrScr;
  For i:=1 to N do
    For j:=1 to N do
      begin
        Matr[i,j]:=0;
        Matr[j,i]:=0
      end;
  Assign(Fin,'input.txt');
  Reset(Fin);
  Readln(Fin,N);
  While not eof(Fin) do
    begin
      ReadLn(Fin,i,j);
      Matr[i,j]:=1;
    end;
  Close(Fin);
  Assign(Fout,'output.txt');
  Rewrite(Fout);
  B1:=true;
  While B1 do
    begin
      Write('������ ��砫��� ���設�:  ');
      Readln(A);
      Write('������ ������� ���設�:  ');
      Readln(B);
      WriteLn(Fout,'��� �� ',A,' � ',B);
      WriteLn('��� �� ',A,' � ',B);
      Poisk(A,B);  {����᫥��� ��� ��⥩}
      Writeln('��⥩ ����� ��� ! ');
      Write('������� ����[y/n] ? ');
      Readln(Ch);
      Writeln;
      Writeln(Fout);
      if Ch='n' then B1:=false   { ��� ��室� �� 横�� }
    end;
  Close(Fout);
End.
