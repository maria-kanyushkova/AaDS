Program SozdTreeArray; { ᮧ����� ����୮�� ��ॢ� �� �᭮�� ���ᨢ� }
  uses crt;
  Type
    uzel=record
           key: integer;
           left,right: integer; { ������� � ���ᨢ� ���設 }
         end;
  Var
    ver: array [1..100] of uzel; 
    t,kon: integer;
    prizn: char;
  Procedure Sozd(t:integer);
    Begin
      if t<>-1 then { �� ���� }
        begin
          Write('������ ����� ���設� ');
          Readln(ver[t].key);
          Write('� ���設� ',ver[t].key,
                ' ������� ���� ��(�/�) ? ');
          Readln(prizn);
          if prizn='�' then ver[t].left:=-1
          else
            begin
              Writeln('���室�� � ������ ��� ���設� ',ver[t].key);
              kon:=kon+1;
              ver[t].left:=kon
            end;
          Sozd(ver[t].left);
          Write('� ���設� ',ver[t].key,
                ' ������� �ࠢ� ��(�/�) ? ');
          Readln(prizn);
          if prizn='�' then ver[t].right:=-1
          else
            begin
              Writeln('���室�� � �ࠢ��� ��� ���設� ',ver[t].key);
              kon:=kon+1;
              ver[t].right:=kon
            end;
          Sozd(ver[t].right)
        end
    End;
  Procedure PechPr(t:integer);
    Begin
      if t<>-1 then
        Begin
          Writeln('���設� ',ver[t].key);
          PechPr(ver[t].left);
          PechPr(ver[t].right);
        end
    End;
  Procedure PechPo(t:integer);
    Begin
      if t<>-1 then
        Begin
          PechPo(ver[t].left);
          PechPo(ver[t].right);
          Writeln('���設� ',ver[t].key);
        end
    End;
  Procedure PechIn(t:integer);
    Begin
      if t<>-1 then
        Begin
          PechIn(ver[t].left);
          Writeln('���設� ',ver[t].key);
          PechIn(ver[t].right);
        end
    End;
  Begin
    Clrscr;
    { ��७� - 1-� ������� ���ᨢ� }
    kon:=1;  { ������ ��᫥����� ������� }
    Sozd(1);
    Writeln('��ॢ� ᮧ���� !');
    Readln;   { ��㧠 }
    PechPr(1);
    Writeln('����� � ���浪� ᢥ��� ���� ');
    Readln;
    PechPo(1);
    Writeln('����� � ���浪� ᭨�� ����� ');
    Readln;
    PechIn(1);
    Writeln('����� � ���浪� ᫥�� ���ࠢ� ');
    Readln;
  End.
