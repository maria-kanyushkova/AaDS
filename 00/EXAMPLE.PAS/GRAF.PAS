Program Graf;
(* ᮧ����� � �ᯥ�⪠ ��� *)
uses crt;
Type
  ukaz=^uzel;
  point=^duga;
  uzel=record   (* �⥪ ���設 ��� *)
         nom: integer;
         next: ukaz;
         sv: point
       end;
  duga=record  (* ������� �㣨 ��� *)
         next: point;
         sv:   ukaz
       end;
Var
  a,b: integer;
  l: boolean;
  top,kon,ua,ub: ukaz;
  p,q: point;
  ch: char;
Begin
  l:=true; top:=nil;
  While l do
    Begin
      Write('������ �裡 � ���� ���� ���設 (99-�����) ');
      Read(a);
      if a=99 then
        begin
          Writeln('���� �����祭 !');
          Writeln;
          l:=false
        end
      else
        begin
          Read(b);
          kon:=top;
          ua:=nil; ub:=nil;
          While kon<>nil do
            begin
              if kon^.nom=a then ua:=kon;
              if kon^.nom=b then ub:=kon;
              if (ua<>nil) and (ub<>nil) then kon:=nil;
              if kon<>nil then kon:=kon^.next
            end;
          if ua=nil then  (* a-����� ���設� *)
            begin
              New(ua);
              ua^.nom:=a;
              ua^.next:=top;
              top:=ua;
              ua^.sv:=nil
            end;
          if ub=nil then  (* b-����� ���設� *)
            begin
              New(ub);
              ub^.nom:=b;
              ub^.next:=top;
              top:=ub;
              ub^.sv:=nil
            end;
          if ua^.sv=nil then  (* ��� �� � ���設� a *)
            begin
              New(p);
              ua^.sv:=p;
              p^.next:=nil;
              p^.sv:=ub
            end
          else                (* ���� �㣨 ! *)
            begin
              q:=ua^.sv;  (* ��ࢠ� �㣠 *)
              New(p);
              p^.next:=q^.next;
              q^.next:=p;
              p^.sv:=ub
            end   (* ��⠢�� ��᫥ ��ࢮ� �㣨 *)
        end       (* else *)
    end;          (* ����� While *)
    ua:=top;
    While ua<>nil do
      begin
        Writeln('���設� ',ua^.nom);
        p:=ua^.sv;
        if p<>nil then Write('�뭮���:  ')
        else Write('�뭮��� ��� !');
        While p<>nil do
          begin
            kon:=p^.sv;
            b:=kon^.nom;
            Write(b,' ');
            p:=p^.next
          end;
        Writeln;
        ua:=ua^.next
      end;
    ch:=ReadKey
End.
