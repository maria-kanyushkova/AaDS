Program TTT;   { 㤠����� �� �।��� �⥪� }
  Uses crt;
  Type
    ukaz=^stek;
    stek=record
           key: integer;
           next: ukaz
         end;
  Var
    top,p,q,r: ukaz;
    b: boolean;
    k,knew: integer;
  Begin
    ClrScr;
    top:=nil; b:=true;
    While b do
      Begin
        Write('�������-');
        ReadLn(k);
        if k>0 then
          begin
            new(p);
            p^.key:=k;
            p^.next:=top;
            top:=p
          end
        else b:=false
      end;
    p:=top; b:=true;
    k:=1;
    While (p<>nil) and b do
      if p^.key=k then
        begin
          b:=false;
          q:=p^.next;
          p^:=q^;
          if q<>nil then  Dispose(q);
          { if �㦥�, ���� �訡�� �믮������ ! }
        end
      else p:=p^.next;
  End.