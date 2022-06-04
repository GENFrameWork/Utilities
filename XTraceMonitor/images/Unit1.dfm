object Form1: TForm1
  Left = 357
  Top = 287
  Width = 1740
  Height = 900
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object ValueListEditor1: TValueListEditor
    Left = 688
    Top = 360
    Width = 306
    Height = 300
    BorderStyle = bsNone
    Ctl3D = False
    FixedColor = clLime
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goAlwaysShowEditor, goThumbTracking]
    ParentCtl3D = False
    ParentFont = False
    Strings.Strings = (
      'Prueba1=12345'
      'Prueba2=12345'
      'Prueba3=12345'
      'Prueba4=12345'
      'Prueba5=12345'
      'Prueba6=12345'
      'Prueba7=12345'
      'Prueba8=12345')
    TabOrder = 0
    OnDrawCell = ValueListEditor1DrawCell
    ColWidths = (
      150
      154)
  end
end
